#include "SerialOscGridConnection.hpp"
#include "GridConnectionManager.hpp"
#include "MonomeModuleBase.hpp"

SerialOscGridConnection::SerialOscGridConnection(const MonomeDevice* const device)
    : device(device)
{
}

void SerialOscGridConnection::updateRow(int x_offset, int y, uint8_t bitfield)
{
    GridConnectionManager::theManager->serialOscDriver->sendDeviceLedRowCommand(device, x_offset, y, bitfield);
}

void SerialOscGridConnection::updateQuadrant(int x, int y, uint8_t* leds)
{
    if (device->protocol == PROTOCOL_40H)
    {
        uint8_t* p = leds;
        for (int i = 0; i < 8; i++)
        {
            uint8_t bits = 0;
            for (int j = 0; j < 8; j++)
            {
                if (*p++)
                {
                    bits |= 1 << j;
                }
            }
            GridConnectionManager::theManager->serialOscDriver->sendDeviceLedRowCommand(device, 0, i, bits);
        }
    }
    else if (device->protocol == PROTOCOL_SERIES)
    {
        uint8_t* p = leds;
        uint8_t map[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (*p++)
                {
                    map[i] |= 1 << j;
                }
            }
        }
        GridConnectionManager::theManager->serialOscDriver->sendDeviceLedMapCommand(device, x, y, map);
    }
    else
    {
        GridConnectionManager::theManager->serialOscDriver->sendDeviceLedLevelMapCommand(device, x, y, leds);
    }
}

void SerialOscGridConnection::clearAll()
{
    GridConnectionManager::theManager->serialOscDriver->sendDeviceLedAllCommand(device, false);
}
