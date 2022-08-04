// demo.ino: demo of using both hardware and software I2C simultaneously,
// to read from two GY-21 (SHT21) boards from eBay.
// See https://github.com/pepaslabs/AnyWire.

// Copyright 2022 Jason Pepas.
// Released under the terms of the MIT License.
// See https://opensource.org/licenses/MIT.

#include <Wire.h>
#include "HTU2xD_SHT2x_Si70xx.h"

// a hardware I2C sensor:
HTU2xD_SHT2x_SI70xx hw_sht21(HTU2xD_SENSOR, HUMD_12BIT_TEMP_14BIT);

// a software I2C sensor:
uint8_t sw_sda_pin = 12;
uint8_t sw_scl_pin = 11;
SoftwareWire swire(sw_sda_pin, sw_scl_pin);
HTU2xD_SHT2x_SI70xx sw_sht21(HTU2xD_SENSOR, HUMD_12BIT_TEMP_14BIT, &swire);

float c_to_f(float c) {
    return (c * 9.0f/5.0f) + 32.0f;
}

void reset_and_wait_for_sht21(HTU2xD_SHT2x_SI70xx* sensor, __FlashStringHelper* message) {
    while (sensor->begin() != true) {
        Serial.print(message);
        delay(1000);
    }
}

void setup() {
    delay(500);
    Serial.begin(9600);
    Serial.print(F("\n"));

    reset_and_wait_for_sht21(&hw_sht21, F("Error: hw_sht21.begin().\n"));
    reset_and_wait_for_sht21(&sw_sht21, F("Error: sw_sht21.begin().\n"));

    float id;
    id = hw_sht21.readDeviceID();
    while (true) {
        if (id == HTU2XD_SHT2X_SI70XX_ERROR) {
            reset_and_wait_for_sht21(&hw_sht21, F("Error: hw_sht21.readDeviceID().\n"));
            continue;
        } else {
            Serial.print(F("Found hardware I2C device with id: "));
            Serial.print((int)id);
            Serial.print(F("\n"));
            break;
        }
    }

    id = sw_sht21.readDeviceID();
    while (true) {
        if (id == HTU2XD_SHT2X_SI70XX_ERROR) {
            reset_and_wait_for_sht21(&sw_sht21, F("Error: sw_sht21.readDeviceID().\n"));
            continue;
        } else {
            Serial.print(F("Found software I2C device with id: "));
            Serial.print((int)id);
            Serial.print(F("\n"));
            break;
        }
    }

    Serial.print("CSV output:\n");
    Serial.print("time_s,hw_temp_c,hw_temp_f,hw_humid,sw_temp_c,sw_temp_f,sw_humid\n");
}

void loop() {
    while (millis() % 1000 > 1) {
        continue;
    }

    float hw_humidity = hw_sht21.readHumidity();
    float hw_temp_c = hw_sht21.readTemperature(READ_TEMP_AFTER_RH);
    if (hw_humidity == HTU2XD_SHT2X_SI70XX_ERROR || hw_temp_c == HTU2XD_SHT2X_SI70XX_ERROR) {
        reset_and_wait_for_sht21(&hw_sht21, F("Error: hw_sht21.readHumidity() or hw_sht21.readTemperature()\n"));
        hw_sht21.begin();
        return;
    }

    float sw_humidity = sw_sht21.readHumidity();
    float sw_temp_c = sw_sht21.readTemperature(READ_TEMP_AFTER_RH);
    if (sw_humidity == HTU2XD_SHT2X_SI70XX_ERROR || sw_temp_c == HTU2XD_SHT2X_SI70XX_ERROR) {
        reset_and_wait_for_sht21(&sw_sht21, F("Error: sw_sht21.readHumidity() or sw_sht21.readTemperature()\n"));
        sw_sht21.begin();
        return;
    }

    Serial.print(millis() / 1000);
    Serial.print(F(","));
    Serial.print(hw_temp_c);
    Serial.print(F(","));
    Serial.print(c_to_f(hw_temp_c));
    Serial.print(F(","));
    Serial.print(hw_humidity);
    Serial.print(F(","));
    Serial.print(sw_temp_c);
    Serial.print(F(","));
    Serial.print(c_to_f(sw_temp_c));
    Serial.print(F(","));
    Serial.print(sw_humidity);
    Serial.print(F("\n"));
}
