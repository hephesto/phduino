/*
 pHduino_basic_code.ino - pHduino basic code.
 Copyright (c) 2015 Carlos A. Neves
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 Author: Carlos A. Neves 
 */

#include <Arduino.h>

// ADC pins
#define PH_PH_ADC_PIN    0
#define PH_REF_ADC_PIN   1
#define PH_TEMP_ADC_PIN  2

// Status led pin
#define PH_LED_PIN  13

// buzzer pin
#define PH_BUZZER_PIN  3

#define PH_PH_LOWER_LIMIT  0.0
#define PH_PH_UPPER_LIMIT  14.0

#define PH_PH_VOLTAGE_ADC_LOWER_LIMIT  0.0
#define PH_PH_VOLTAGE_ADC_UPPER_LIMIT  4.0

// constants
#define PH_R        8.31451 // general gases constant, J * K^-1 * mol^-1
#define PH_F        96485   // Faraday constant, C * mol^-1

// Gain of the non-inverter amplifier (stage1 of the schematic circuit),
// considering a nernstiane glass electrode (delta_E=-59.2mV/pH) and
// no influence from offset voltage divider.
#define PH_GAIN_STAGE1_PH       4.8262 // gain = ((4000mV)/(14*59.2mV)=828.8mV)

// Stage2 gain applyed to VREF.
#define PH_GAIN_STAGE2_REF      2.0

// One 60Hz cycle cycle has 16.66ms or 16666us (limit up to 1,000,000us)
// One 50Hz cycle cycle has 20.00ms or 20000us (limit up to 1,000,000us)
// uncomment the right line.
#define PH_TIME_ADC_READINGS_MICROSECONS     16666 // 60Hz
//#define PH_TIME_ADC_READINGS_MICROSECONS     20000 // 50Hz

// Initial temperature for non temperature sensor mode
#define PH_TEMPERATURE_VALUE_INITIAL_CELCIUS    25.0

// Initial interval between acquisition
#define PH_TIME_BETWEEN_ACQUISITIONS_MS    1000

// ordinary variables
int val_E;
int val_R;
int val_T;
float E;
float R;
float T;
float pH;

unsigned int readADC(unsigned char channel, unsigned reading_time) {
  double d;
  int i;
  unsigned long t0_us;
  d = 0.0;
  i = 0;
  t0_us = micros();
  while((micros()-t0_us)<reading_time){
    i++;
    d += analogRead(channel);
  }
  d /= i;
  return (unsigned int)(d);
}

void setup(void){

  // setup LED and buzzer
  pinMode(PH_LED_PIN, OUTPUT);
  pinMode(PH_BUZZER_PIN, OUTPUT);

  // Init serial port
  Serial.begin(115200);

  //Serial.println("Temp/oC E/V pH");
  Serial.println("Temp/oC pH");

}

void loop(void){

  digitalWrite(PH_LED_PIN, HIGH);

  // Temperature
  // Obs.: You can operate the pHduino without a temperature sensor.
  // In this case, you need setup a temperature value up
  // and comment the readADC and calc lines.

  val_T = readADC(PH_TEMP_ADC_PIN, PH_TIME_ADC_READINGS_MICROSECONS);
  T = 100 * val_T * 5.0 / 1024;
  T = PH_TEMPERATURE_VALUE_INITIAL_CELCIUS; // uncomment this line in case no temperature sensor

  Serial.print(T, 2);
  Serial.print(" ");

  val_R = readADC(PH_REF_ADC_PIN, PH_TIME_ADC_READINGS_MICROSECONS);
  R = PH_GAIN_STAGE2_REF * (val_R * 5.0 / 1024);

  // ADC value and voltage of electrochemical potential
  val_E = readADC(PH_PH_ADC_PIN, PH_TIME_ADC_READINGS_MICROSECONS);
  E = -1 * ((val_E * 5.0 / 1024) - R) / PH_GAIN_STAGE1_PH;

  // print pH
  // delta_pH = -(F/(2.303*R*T))*delta_E
  // <http://en.wikipedia.org/wiki/PH>
  // where,
  // gas constant R = 8.31451 J * K^-1 * mol^-1 <http://en.wikipedia.org/wiki/Gas_constant>
  // Kelvin temperature T = celcius temperature plus 273.15 K <http://en.wikipedia.org/wiki/Kelvin>
  // Faraday constant F = 96485 C <http://en.wikipedia.org/wiki/Faraday_constant>
  pH = (float)((-5038.8 * E / (273.15 + T)) + 7.0);

  Serial.print(pH, 2);
  Serial.println();

  digitalWrite(PH_BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(PH_BUZZER_PIN, LOW);

  digitalWrite(PH_LED_PIN, LOW);

  delay(PH_TIME_BETWEEN_ACQUISITIONS_MS);

}



