#include "FirmwareManager.hpp"
#include "GridConnectionManager.hpp"
#include "rack.hpp"

#include <deque>

#pragma once

#define B00 32
#define B01 33
#define B02 34
#define B03 35
#define B04 36
#define B05 37
#define B06 38
#define B07 39
#define B08 40
#define B09 41
#define B10 42
#define NMI 13

struct GridConnection;

struct MonomeModuleBase : rack::Module, IGridConsumer
{
    FirmwareManager firmware;

    MonomeModuleBase(int numParams, int numInputs, int numOutputs, int numLights);

    void buttonPressMessageReceived(MonomeDevice* device, int x, int y, bool state);

    // Rack module methods
    void step() override;
    json_t* toJson() override;
    void fromJson(json_t* rootJ) override;

    // MonomeModuleBase virtual methods
    virtual void processInputs() = 0;
    virtual void processOutputs() = 0;
    virtual void readSerialMessages();

    void setUSBInputPort(int portId);
    void updateConnectedDevice(GridConnection* newConnection);

    std::deque<GridConnection*> connectionEvents;

    MonomeDevice* connectedDevice;
    int usbPortId;
    bool firstStep;
};
