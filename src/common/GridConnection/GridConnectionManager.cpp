#include "GridConnectionManager.hpp"
#include "MonomeModuleBase.hpp"
#include "SerialOscGridConnection.hpp"
#include "VirtualGridConnection.hpp"
#include "VirtualGridModule.hpp"
#include "VirtualGridWidget.hpp"

GridConnectionManager* GridConnectionManager::theManager = new GridConnectionManager();

GridConnectionManager::GridConnectionManager()
{
    serialOscDriver = new SerialOsc("rack", 13000);
    serialOscDriver->start(this);
}

void GridConnectionManager::deviceFound(const MonomeDevice* const device)
{
    for (auto m : MonomeModuleBase::allModules)
    {
        m->deviceFound(device);
    }
}

void GridConnectionManager::deviceRemoved(const std::string& id)
{
    for (auto m : MonomeModuleBase::allModules)
    {
        m->deviceRemoved(id);
    }
}

void GridConnectionManager::buttonPressMessageReceived(MonomeDevice* device, int x, int y, bool state)
{
    for (auto m : MonomeModuleBase::allModules)
    {
        if (device == m->gridConnection->device)
        {
            m->buttonPressMessageReceived(device, x, y, state);
        }
    }
}

void GridConnectionManager::getDevices(std::vector<MonomeDevice*>& devices)
{
    devices.clear();

    for (MonomeDevice* device : serialOscDriver->getDevices())
    {
        devices.push_back(device);
    }

    for (rack::Widget* w : rack::gRackWidget->moduleContainer->children)
    {
        VirtualGridWidget* gridWidget = dynamic_cast<VirtualGridWidget*>(w);
        if (gridWidget)
        {
            auto gridModule = dynamic_cast<VirtualGridModule*>(gridWidget->module);
            devices.push_back(&(gridModule->device));
        }
    }
}

void GridConnectionManager::connectModuleToDevice(MonomeModuleBase* module, MonomeDevice* device)
{
    if (device->id[1] == 'v')
    {
        for (rack::Widget* w : rack::gRackWidget->moduleContainer->children)
        {
            VirtualGridWidget* gridWidget = dynamic_cast<VirtualGridWidget*>(w);
            if (gridWidget)
            {
                auto gridModule = dynamic_cast<VirtualGridModule*>(gridWidget->module);
                if (&(gridModule->device) == device)
                {
                    module->setGridConnection(new VirtualGridConnection(module, gridModule));
                    return;
                }
            }
        }
    }
    else
    {
        module->setGridConnection(new SerialOscGridConnection(module, device));
    }
}

void GridConnectionManager::connectModuleToDeviceId(MonomeModuleBase* module, std::string deviceId)
{
    // enumerate detected serialosc devices
    for (MonomeDevice* device : serialOscDriver->getDevices())
    {
        if (device->id == deviceId)
        {
            auto connection = new SerialOscGridConnection(module, device);
            module->setGridConnection(connection);
            return;
        }
    }

    // enumerate modules
    for (rack::Widget* w : rack::gRackWidget->moduleContainer->children)
    {
        VirtualGridWidget* gridWidget = dynamic_cast<VirtualGridWidget*>(w);
        if (gridWidget)
        {
            auto gridModule = dynamic_cast<VirtualGridModule*>(gridWidget->module);
            if (gridModule->device.id == deviceId)
            {
                auto connection = new VirtualGridConnection(module, gridModule);
                module->setGridConnection(connection);
                return;
            }
        }
    }
}