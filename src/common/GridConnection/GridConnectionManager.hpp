#include "GridConnection.hpp"
#include "SerialOsc.h"

#include <map>
#include <vector>

#pragma once

class SerialOsc;
struct MonomeModuleBase;

struct GridConnectionManager : SerialOsc::Listener
{
    GridConnectionManager();

    static GridConnectionManager* theManager;
    SerialOsc* serialOscDriver;

    // SerialOsc::Listener methods
    void deviceFound(const MonomeDevice* const device) override;
    void deviceRemoved(const std::string& id) override;

    /*
    void buttonPressMessageReceived(MonomeDevice* device, int x, int y, bool state) override;

    void getDevices(std::vector<MonomeDevice*>& devices);
    void connectModuleToDevice(MonomeModuleBase* module, const MonomeDevice* const device);
    void connectModuleToDeviceId(MonomeModuleBase* module, std::string deviceId);
    void disconnectDevice(const MonomeDevice* const device);
    void disconnectDeviceId(std::string deviceId);

protected:
    void createConnection(MonomeModuleBase* module, GridConnection* connection);
    std::map<const MonomeDevice* const, MonomeModuleBase*> activeConnections;
    */
};
