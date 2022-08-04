# AnyWire

Arduino abstraction layer to support both Wire and SoftwareWire.

Included in this repo are forked copies of [SoftwareWire](https://github.com/Testato/SoftwareWire) and HTU2xD_SHT2x_Si70xx,
which have been modified to support AnyWire.

See the included `demo.ino`, which reads from both hardware and software I2C sensors.

```cpp
// an SHT21 sensor using hardware I2C:
HTU2xD_SHT2x_SI70xx hw_sht21(HTU2xD_SENSOR, HUMD_12BIT_TEMP_14BIT);

// an SHT21 sensor using software I2C:
uint8_t sw_sda_pin = 12;
uint8_t sw_scl_pin = 11;
SoftwareWire swire(sw_sda_pin, sw_scl_pin);
HTU2xD_SHT2x_SI70xx sw_sht21(HTU2xD_SENSOR, HUMD_12BIT_TEMP_14BIT, &swire);
```

```
Found hardware I2C device with id: 7021
Found software I2C device with id: 7021
CSV output:
time_s,hw_temp_c,hw_temp_f,hw_humid,sw_temp_c,sw_temp_f,sw_humid
1,24.88,76.78,45.03,24.29,75.72,49.22
2,24.87,76.76,45.00,24.28,75.70,49.19
3,24.91,76.84,45.00,24.28,75.70,49.21
4,24.91,76.84,45.02,24.29,75.72,49.21
5,24.90,76.82,45.03,24.30,75.74,49.22
```


## License

AnyWire.h, AnyWire.cpp and demo.ino are copyright 2022 Jason Pepas,
released under the terms of the MIT License.  See https://opensource.org/licenses/MIT.

SoftwareWire.h and SoftwareWire.cpp are forked from https://github.com/Testato/SoftwareWire,
which is GPL-3.0 licensed.

HTU2xD_SHT2x_Si70xx.h and HTU2xD_SHT2x_Si70xx.cpp are forked from https://github.com/enjoyneering/HTU2xD_SHT2x_Si70xx,
which is GPL-3.0 licensed.
