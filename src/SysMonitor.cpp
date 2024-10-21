#include <iostream>
#include <thread>
#include <chrono>

#include "logger.h"
#include "SysMonitor.h"


SysMonitor::SysMonitor(const MqttCfg &cfg)
    : _cfg{cfg}
{
}

SysMonitor::~SysMonitor()
{
}

int SysMonitor::Initialize()
{
    try
    {
        _client = std::make_unique<MqttClient>(_cfg);
        _client->Initialize();
        _client->Subscribe("test/topic");
        _client->Publish("test/topic", "Hello, MQTT!");

        // Keep the main thread alive to allow the network loop to run
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}

void SysMonitor::Deinit()
{
    _client->Deinit();
    _client.reset();
}