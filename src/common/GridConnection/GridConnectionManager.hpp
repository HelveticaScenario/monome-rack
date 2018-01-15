#include "GridConnection.hpp"
#include "SerialOsc.h"

#include <vector>

#pragma once

class SerialOsc;
class MonomeModuleBase;

struct GridConnectionManager : SerialOsc::Listener
{
    GridConnectionManager();

    static GridConnectionManager* theManager;

    // SerialOsc::Listener methods
    void deviceFound(const MonomeDevice* const device) override;
    void deviceRemoved(const std::string& id) override;
    void buttonPressMessageReceived(MonomeDevice* device, int x, int y, bool state) override;

    void getDevices(std::vector<MonomeDevice*>& devices);
    void connectModuleToDevice(MonomeModuleBase* module, MonomeDevice* device);
    void connectModuleToDeviceId(MonomeModuleBase* module, std::string deviceId);

    SerialOsc* serialOscDriver;
};
