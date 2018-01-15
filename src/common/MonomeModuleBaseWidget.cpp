#include "MonomeModuleBaseWidget.hpp"
#include "MonomeModuleBase.hpp"

using namespace rack;

struct MonomeConnectionItem : rack::MenuItem
{
    MonomeModuleBase* module;
    MonomeDevice* device;

    void onAction(rack::EventAction& e) override
    {
        GridConnectionManager::theManager->connectModuleToDevice(module, device);
    }
};

MonomeModuleBaseWidget::MonomeModuleBaseWidget()
{
}

Menu* MonomeModuleBaseWidget::createContextMenu()
{
    rack::Menu* menu = ModuleWidget::createContextMenu();

    auto module = static_cast<MonomeModuleBase*>(this->module);

    menu->addChild(construct<MenuEntry>());
    menu->addChild(construct<MenuLabel>(&MenuLabel::text, "Device Connection"));

    std::vector<MonomeDevice*> devices;
    GridConnectionManager::theManager->getDevices(devices);

    for (MonomeDevice* device : devices)
    {
        auto* connectionItem = new MonomeConnectionItem();
        connectionItem->text = device->type + " (" + device->id + ")";
        connectionItem->rightText = (module->gridConnection->device == device) ? "✔" : "";
        connectionItem->module = module;
        connectionItem->device = device;
        menu->addChild(connectionItem);
    }

    if (devices.size() > 0)
    {
        menu->addChild(construct<MenuLabel>(&MenuLabel::text, "(no physical or virtual devices found)"));
    }

    return menu;
}