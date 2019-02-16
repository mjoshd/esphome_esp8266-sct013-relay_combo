#include "esphomelib.h"

#include "EmonLib.h"                   // Include Emon Library
#define analogIn A0                    // Analog Input Pin
#define calVal 111.1                   // Calibration Value

using namespace esphomelib;

class MyCustomSensor : public PollingComponent, public sensor::Sensor {
 public:
  
  EnergyMonitor emon1;          // Create an instance of EnergyMonitor
  
  // constructor
  MyCustomSensor() : PollingComponent(1000) { }

  void setup() override {
    // This will be called by App.setup()
    // think of it as the setup() call in Arduino
    emon1.current(analogIn, calVal);          // Current: input pin, calibration value
  }

  void update() override {
    // This will be called every "PollingComponent" milliseconds.
    // think of it as the loop() call in Arduino
    double Irms = emon1.calcIrms(1480.0);          // Calculate Irms only
    double watts = round(Irms * 115.0 / 4.0);      // Inaccurate watts calculation, but adequate sensing on/off
    publish_state(watts);                          // Send value to custom sensor 

    ESP_LOGD("Analog Input Sensor Value", "%f", watts);          // Send message to logging component

  }
};
