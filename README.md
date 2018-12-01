# ze08-ch2o-Arduino
A driver for the Winsen ZE08-CH2O formaldehyde sensor

It has been tested with ESP8266.

Remember that this sensor requires 5V in Vcc but does NOT tolerate 5V in its RX input.
If you just want to use the default, active mode, you don't even need to
connect this pin, so you can connect directly 5V, GND and Arduino's RX.

# Instalation

```
git clone https://github.com/rsalinas/ze08-ch2o-Arduino.git ~/Arduino/libraries/ze08_ch2o
```

# Feedback welcome

If it helps you in your project, or if you have bug reports or feature requests,
don't hesitate to contact me.

# Links

Sensor website: https://www.winsen-sensor.com/products/formaldehyde-detection-module/ze08-ch2o.html
