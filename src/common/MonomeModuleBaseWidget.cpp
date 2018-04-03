#include "MonomeModuleBaseWidget.hpp"
#include "MonomeModuleBase.hpp"

using namespace rack;


// Copied from Rack AddModuleWindow.cpp, where it's otherwise inaccessible
struct UrlItem : rack::MenuItem
{
    std::string url;
    void onAction(EventAction& e) override
    {
        std::thread t(rack::systemOpenBrowser, url);
        t.detach();
    }
};

/*
template <typename C>
bool connectionPtrIsEqual(GridConnection* genericPtr, C* specificPtr)
{
    C* castPtr = static_cast<C*>(genericPtr);
    if (castPtr == NULL || specificPtr == NULL)
    {
        return false;
    }
    else
    {
        return *castPtr == *specificPtr;
    }
}
*/

MonomeModuleBaseWidget::MonomeModuleBaseWidget(MonomeModuleBase* module)
: ModuleWidget(module)
{
}

Menu* MonomeModuleBaseWidget::createContextMenu()
{
    rack::Menu* menu = ModuleWidget::createContextMenu();

    //auto module = static_cast<MonomeModuleBase*>(this->module);

    auto helpItem = new UrlItem();
    helpItem->url = "https://github.com/Dewb/monome-rack/blob/master/README.md";
    helpItem->text = "Help";
    menu->addChild(helpItem);

/*
    menu->addChild(construct<MenuEntry>());
    menu->addChild(construct<MenuLabel>(&MenuLabel::text, "Device Connection"));

    std::vector<MonomeDevice*> devices;
    GridConnectionManager::theManager->getDevices(devices);

    for (MonomeDevice* device : devices)
    {
        auto* connectionItem = new MonomeConnectionItem();
        connectionItem->text = device->type + " (" + device->id + ")";
        connectionItem->rightText = (module->gridConnection && module->gridConnection->device == device) ? "✔" : "";
        connectionItem->module = module;
        connectionItem->device = device;
        menu->addChild(connectionItem);
    }

    if (devices.size() == 0)
    {
        menu->addChild(construct<MenuLabel>(&MenuLabel::text, "(no physical or virtual devices found)"));
    }
*/

    return menu;
}