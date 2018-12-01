#include <ze08_ch2o.h>
#include <SoftwareSerial.h>

// Instantiate a serial port, whatever Stream you have
SoftwareSerial ch2oSerial(4, SW_SERIAL_UNUSED_PIN); // RX, TX

// Instantiate a sensor connected to the previous port
Ze08CH2O ch2o{&ch2oSerial};

void setup() {
  Serial.begin(115200);  // Console
}

void loop() {
  Ze08CH2O::concentration_t reading;
  if (ch2o.read(reading)) {
    Serial.print("New value: ");
    Serial.println(reading);
  }
}
