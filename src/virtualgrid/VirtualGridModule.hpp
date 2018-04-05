#include "SerialOsc.h"
#include "rack.hpp"
#include "GridConnection.hpp"

#pragma once

#define GRID_MAX_SIZE 256

struct MonomeModuleBase;

struct VirtualGridModule : IGridDevice
{
    enum OutputIds
    {
        USB_OUTPUT,
        NUM_OUTPUTS
    };

    MonomeModuleBase* connectedModule = NULL;
    MonomeDevice device;

    uint8_t ledBuffer[GRID_MAX_SIZE];
    bool pressedState[GRID_MAX_SIZE];

    VirtualGridModule(unsigned w, unsigned h);

    void step() override;

    json_t* toJson() override;
    void fromJson(json_t* rootJ) override;

    virtual MonomeDevice* getDeviceInfo() override { return &device; }
    virtual void updateRow(int x_offset, int y, uint8_t bitfield) override;
    virtual void updateQuadrant(int x_offset, int y_offset, uint8_t* leds) override;
    virtual void clearAll() override;
};


template <unsigned width, unsigned height, unsigned modelIndex>
struct VirtualGridModuleTemplate : VirtualGridModule
{
    VirtualGridModuleTemplate()
        : VirtualGridModule(width, height)
    {
    }
};
