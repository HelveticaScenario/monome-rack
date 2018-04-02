#include "GridConnection.hpp"

#pragma once

struct SerialOscGridConnection : IGridDevice
{
    SerialOscGridConnection(const MonomeDevice* const device);

    void updateRow(int x_offset, int y, uint8_t bitfield) override;
    void updateQuadrant(int x, int y, uint8_t* leds) override;
    void clearAll() override;

    const MonomeDevice* const device;
};