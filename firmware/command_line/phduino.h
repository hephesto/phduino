/*
  pHduino.h - pHduino library for Arduino & Wiring
  Copyright (c) 2009 Carlos A. Neves
  http://code.google.com/p/phduino

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
  
  Author: Carlos A. Neves <caneves at google>
*/

// firmware version
#define PH_PHDUINO_VERSION   "0.4.1_20120312"
#define PH_PHDUINO_CODENAME  "acetic acid"

// Magic number
#define MAGIC_NUMBER      0xB45E  // base

// button pin
#define PH_BUTTON_CTRL_PIN  2

// buzzer pin
#define PH_BUZZER_PIN  3

// LCD pins
#define PH_LCD_RS_PIN  6
#define PH_LCD_RW_PIN  7
#define PH_LCD_E_PIN   8
#define PH_LCD_D4_PIN  9
#define PH_LCD_D5_PIN  10
#define PH_LCD_D6_PIN  11
#define PH_LCD_D7_PIN  12

// Status led pin
#define PH_LED_PIN  13

// ADC pins
#define PH_PH_ADC_PIN    0
#define PH_REF_ADC_PIN   1
#define PH_TEMP_ADC_PIN  2

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
#define PH_INITIAL_TIME_BETWEEN_ACQUISITIONS_MS    1000

// Initial pH range to the pH alarm
#define PH_ALARM_INF      0.0
#define PH_ALARM_SUP      14.0

// functions

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
