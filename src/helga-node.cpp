/*
 * Project Helga Node
 * Author: Aaron Smulktis
 * Date: 04/28/2024
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "BatteryLevel.h"

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

BatteryLevel batteryMonitor;
int ledPin = A0;

void handleReceivedMessage(const char *event, const char *data);

void setup()
{
  pinMode(ledPin, OUTPUT);
  Particle.subscribe("hook-response/message", handleReceivedMessage, MY_DEVICES);
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  float voltage = batteryMonitor.getBatteryVoltage();
  float charge = batteryMonitor.getBatteryCharge();

  // Convert voltage and charge to string format
  char voltageStr[10]; // Buffer to hold the voltage string
  char chargeStr[10];  // Buffer to hold the charge string

  snprintf(voltageStr, sizeof(voltageStr), "%.2f", voltage); // Format with 2 decimal places
  snprintf(chargeStr, sizeof(chargeStr), "%.1f", charge);    // Format with 1 decimal place

  Log.info("Battery Voltage: %s V", voltageStr);
  Log.info("Battery Charge: %s %%", chargeStr);

  Log.info("Sending a thank you to the cloud!");
  Particle.publish("Thank you for the honk, sir!", PRIVATE);
  delay(60 * 1000); // Update battery level every minute
}

void handleReceivedMessage(const char *event, const char *data)
{
  analogWrite(ledPin, HIGH);
  delay(500);
  analogWrite(ledPin, LOW);

  Particle.publish("Received Message", PRIVATE);
}