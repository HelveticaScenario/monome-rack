#include <stdint.h>
#include <rack.hpp>

#pragma once

struct MonomeDevice;

struct IGridDevice : rack::Module
{
    IGridDevice(int a, int b, int c, int d) : rack::Module(a, b, c, d) {}
    virtual MonomeDevice* getDeviceInfo() = 0;
    virtual void updateRow(int x_offset, int y, uint8_t bitfield) = 0;
    virtual void updateQuadrant(int x, int y, uint8_t* leds) = 0;
    virtual void clearAll() = 0;
};

struct IGridConsumer
{
    virtual void buttonPressMessageReceived(int x, int y, bool state) = 0;
    virtual IGridDevice* getConnectedDevice() = 0;
};