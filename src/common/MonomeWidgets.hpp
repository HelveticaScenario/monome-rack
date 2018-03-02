#include "rack.hpp"

#pragma once

struct WhiteLight : rack::ModuleLightWidget
{
    WhiteLight();
};

struct USBConnectorPort : rack::SVGPort
{
    USBConnectorPort(std::string unpluggedGraphic, std::string PluggedGraphic);
    void step() override;
    void onDragEnter(rack::EventDragEnter& e) override;

    void updatePlugGraphic();

    bool pluggedState;
    std::string unpluggedSvg;
    std::string pluggedSvg;
};

struct USBAJack : USBConnectorPort
{
    USBAJack();
};

struct USBBJack : USBConnectorPort
{
    USBBJack();
};

struct USBMiniBJack : USBConnectorPort
{
    USBMiniBJack();
};

struct MonomeKnob : rack::RoundKnob
{
    MonomeKnob();
};