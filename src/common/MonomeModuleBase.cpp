#include "MonomeModuleBase.hpp"
#include "VirtualGridModule.hpp"
#include "VirtualGridWidget.hpp"
#include "base64.h"

#include <algorithm>

using namespace std;


MonomeModuleBase::MonomeModuleBase(int numParams, int numInputs, int numOutputs, int numLights)
    : Module(numParams, numInputs, numOutputs, numLights)
{
    firstStep = true;
}

void MonomeModuleBase::setUSBInputPort(int portId)
{
    usbPortId = portId;
}

rack::Module* lookupOutputModuleFromInput(rack::Module* inputModule, int inputId)
{
    for (auto wire : rack::gWires)
    {
        if (wire->inputModule == inputModule && wire->inputId == inputId)
        {
            return wire->outputModule;
        }
    }

    return nullptr;
}

void MonomeModuleBase::onUSBConnectionChanged()
{
    IGridDevice* newDevice = nullptr;

    if (usbPortId >= 0 && inputs[usbPortId].active)
    {
        auto module = lookupOutputModuleFromInput(this, usbPortId);
        newDevice = dynamic_cast<IGridDevice*>(module);
    }

    if (newDevice == connectedDevice)
    {
        return;
    }

    connectedDevice = newDevice;

    if (connectedDevice)
    {
        string id = connectedDevice->getDeviceInfo()->id;
        string wide_id;
        for (int i = 0; i < id.length(); i++)
        {
            if (i == 1 && id[1] == 'v')
                i++;

            wide_id.append(id, i, 1);
            wide_id.append(" ");
        }

        firmware.serialConnectionChange(FTDI_BUS, 1, "m o n o m e", "p r o d u c t", wide_id.c_str());

        uint8_t buf[6] = { 0, 1, 0, 0, 0, 0 };
        buf[2] = (connectedDevice->getDeviceInfo()->width * connectedDevice->getDeviceInfo()->height) / 64;
        firmware.writeSerial(FTDI_BUS, buf, 6);
        uint8_t buf2[2] = { 0, 0 };
        firmware.writeSerial(FTDI_BUS, buf2, 2);
    }
    else
    {
        firmware.serialConnectionChange(FTDI_BUS, 0, NULL, NULL, NULL);
    }
}

void MonomeModuleBase::buttonPressMessageReceived(int x, int y, bool state)
{
    uint8_t msg[4] = { 0xF0, 0, 0, 0 };
    msg[1] = (uint8_t)x;
    msg[2] = (uint8_t)y;
    msg[3] = state ? 1 : 0;
    firmware.writeSerial(FTDI_BUS, msg, 4);
}

void MonomeModuleBase::readSerialMessages()
{
    uint8_t* msg;
    uint32_t count;
    firmware.readSerial(FTDI_BUS, &msg, &count);
    while (msg)
    {
        if ((msg[0] & 0xF0) == 0x70 && count >= 2)
        {
            // 40h protocol row update
            uint8_t y = msg[0] & 0x0F;
            uint8_t bitfield = msg[1];
            if (connectedDevice)
            {
                connectedDevice->updateRow(0, y, bitfield);
            }
            if (count > 2) // there are more 0x7x two-byte commands in this serial message
            {
                msg += 2;
                count -= 2;
                continue;
            }
        }
        else if (msg[0] == 0x1A && count >= 35)
        {
            // mext protocol quadrant update
            uint8_t x = msg[1];
            uint8_t y = msg[2];
            uint8_t leds[64];
            for (int i = 0; i < 32; i++)
            {
                leds[2 * i + 0] = msg[3 + i] >> 4;
                leds[2 * i + 1] = msg[3 + i] & 0xF;
            }

            if (connectedDevice)
            {
                connectedDevice->updateQuadrant(x, y, leds);
            }
        }
        else if ((msg[0] & 0x80) == 0x80 && count >= 9)
        {
            // series protocol quadrant update
            int x = (msg[0] & 0x1) * 8;
            int y = (msg[0] & 0x2) * 8;
            uint8_t leds[64];
            for (int j = 0; j < 8; j++)
            {
                for (int i = 0; i < 8; i++)
                {
                    leds[i + 8 * j] = (msg[1 + j] & (0x1 << i)) ? 15 : 0;
                }
            }

            if (connectedDevice)
            {
                connectedDevice->updateQuadrant(x, y, leds);
            }
        }
        else if (msg[0] == 0x01)
        {
            // device info request
            // ignore, we stuffed the response in the message queue in advance
        }
        firmware.readSerial(FTDI_BUS, &msg, &count);
    }
}

void MonomeModuleBase::step()
{
    //if (firstStep)
    {
        onUSBConnectionChanged();
        firstStep = false;
    }

    // Module-specific code to bind Rack inputs to GPIO/ADC
    processInputs();

    // Advance hardware timers
    firmware.advanceClock(rack::engineGetSampleTime());

    // Pump hardware event loop
    firmware.step();

    // Module-specific code to bind GPIO/DAC to Rack outputs & lights
    processOutputs();

    // Act on serial output from module to the outside world (grid LEDs, etc.)
    readSerialMessages();

}

json_t* MonomeModuleBase::toJson()
{
    json_t* rootJ = json_object();

    void* data;
    uint32_t size;

    firmware.readNVRAM(&data, &size);
    if (data && size > 0)
    {
        json_object_set_new(rootJ, "nvram", json_string(base64_encode((unsigned char*)data, size).c_str()));
    }

    firmware.readVRAM(&data, &size);
    if (data && size > 0)
    {
        json_object_set_new(rootJ, "vram", json_string(base64_encode((unsigned char*)data, size).c_str()));
    }

    return rootJ;
}

void MonomeModuleBase::fromJson(json_t* rootJ)
{
    void* data;
    uint32_t size;
    json_t* jd;

    jd = json_object_get(rootJ, "nvram");
    if (jd)
    {
        string decoded = base64_decode(json_string_value(jd));

        firmware.readNVRAM(&data, &size);
        if (data && size == decoded.length())
        {
            firmware.writeNVRAM((void*)decoded.c_str(), size);
        }
    }

    jd = json_object_get(rootJ, "vram");
    if (jd)
    {
        string decoded = base64_decode(json_string_value(jd));

        firmware.readVRAM(&data, &size);
        if (data && size == decoded.length())
        {
            firmware.writeVRAM((void*)decoded.c_str(), size);
        }
    }
}
