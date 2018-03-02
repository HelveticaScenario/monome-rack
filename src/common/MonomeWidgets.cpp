#include "MonomeWidgets.hpp"

extern rack::Plugin* plugin;

WhiteLight::WhiteLight()
{
    addBaseColor(COLOR_WHITE);
}

USBConnectorPort::USBConnectorPort(std::string unpluggedGraphic, std::string pluggedGraphic)
    : unpluggedSvg(unpluggedGraphic)
    , pluggedSvg(pluggedGraphic)
{
    pluggedState = false;
    updatePlugGraphic();
}

void USBConnectorPort::step()
{
    bool active = false;
    if (type == INPUT)
    {
        active = module->inputs[portId].active;
    }
    else if (type == OUTPUT)
    {
        active = module->outputs[portId].active;
    }

    if (active != pluggedState)
    {
        pluggedState = active;
        updatePlugGraphic();
    }

    SVGPort::step();
}

void USBConnectorPort::onDragEnter(rack::EventDragEnter& e)
{
    // Don't allow multiple connections to an output port
    if (type == OUTPUT)
    {
        rack::WireWidget* topWire = rack::gRackWidget->wireContainer->getTopWire(this);
        if (topWire)
            return;
    }

    SVGPort::onDragEnter(e);
}

void USBConnectorPort::updatePlugGraphic()
{
    background->svg = rack::SVG::load(rack::assetPlugin(plugin, pluggedState ? pluggedSvg : unpluggedSvg));
    background->wrap();
    box.size = background->box.size;
    dirty = true;
}

USBAJack::USBAJack()
    : USBConnectorPort("res/USB-A.svg", "res/USB-A-plugged.svg")
{
}

USBBJack::USBBJack()
    : USBConnectorPort("res/USB-B.svg", "res/USB-B-plugged.svg")
{
}

USBMiniBJack::USBMiniBJack()
    : USBConnectorPort("res/USB-Mini-B.svg", "res/USB-Mini-B-plugged.svg")
{
}

MonomeKnob::MonomeKnob()
{
    setSVG(rack::SVG::load(assetPlugin(plugin, "res/MonomeKnob.svg")));
    box.size = rack::Vec(42, 42);
}