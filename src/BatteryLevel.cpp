#include "BatteryLevel.h"

FuelGauge fuel;

BatteryLevel::BatteryLevel()
{
    // Initialization can be handled here if needed
}

float BatteryLevel::getBatteryVoltage()
{
    return fuel.getVCell(); // Returns the voltage of the LiPo cell
}

float BatteryLevel::getBatteryCharge()
{
    return fuel.getSoC(); // Returns the State of Charge of the LiPo battery as a percentage
}
