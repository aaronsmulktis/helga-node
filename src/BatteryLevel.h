#ifndef BATTERY_LEVEL_H
#define BATTERY_LEVEL_H

#include "Particle.h"

class BatteryLevel
{
public:
    BatteryLevel();
    float getBatteryVoltage();
    float getBatteryCharge();
};

#endif
