/*
 pHduino.pde - pHduino firmware for Arduino.
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

#include <Arduino.h>
//#include "WProgram.h"
#include <LiquidCrystal.h>
#include "pHduino.h"
#include "float2string.h"
#include "commandline.h"
#include "string.h"
#include "stdlib.h"
#include <avr/eeprom.h>
//#include "freemem.h"

// Creates the LCD instance
LiquidCrystal lcd(PH_LCD_RS_PIN, PH_LCD_RW_PIN, PH_LCD_E_PIN, PH_LCD_D4_PIN, PH_LCD_D5_PIN, PH_LCD_D6_PIN, PH_LCD_D7_PIN);

// ordinary variables
char myStr[16];
int val_E;
int val_R;
int val_T;
float E;
float R;
float T;
float pH;
int i;
unsigned long ul;
float f, f2;

unsigned long int my_timer0;
unsigned long int my_timer;

boolean pH_alarm_status = false;

// struct of parameters
struct myRec_T{
  unsigned int magic_number;
  boolean start_flag;
  unsigned int time_between_acquisitions_ms;
  boolean temperature_sensor_flag;
  float temperature_constant_celcius;
  boolean pH_alarm_flag;
  float pH_inf;
  float pH_sup;
} 
myRec;

void parameters_reset(void){

  myRec.magic_number = MAGIC_NUMBER;
  myRec.start_flag = true;
  myRec.time_between_acquisitions_ms = PH_INITIAL_TIME_BETWEEN_ACQUISITIONS_MS;
  myRec.temperature_sensor_flag = true;
  myRec.temperature_constant_celcius = PH_TEMPERATURE_VALUE_INITIAL_CELCIUS;
  myRec.pH_alarm_flag = false;
  myRec.pH_inf = 0.0;
  myRec.pH_sup = 14.0;

  eeprom_write_block(&myRec, (void *)0, sizeof(myRec));
}

void setup(void){

  // Init serial port
  Serial.begin(115200);

  // setup LED, button, and buzzer
  pinMode(PH_LED_PIN, OUTPUT);
  pinMode(PH_BUTTON_CTRL_PIN, INPUT);
  pinMode(PH_BUZZER_PIN, OUTPUT);

  // initialize LED and buzzer
  digitalWrite(PH_LED_PIN, LOW);
  digitalWrite(PH_BUZZER_PIN, LOW);

  // begin LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.noCursor();
  lcd.home();
  lcd.display();

  // Initial messagens.
  digitalWrite(PH_BUZZER_PIN, HIGH);
  delay(200);
  digitalWrite(PH_BUZZER_PIN, LOW);

  digitalWrite(PH_LED_PIN, HIGH);
  lcd.setCursor(0,0);
  lcd.print("pHduino");
  lcd.setCursor(0,1);
  lcd.print(PH_PHDUINO_VERSION); 
  delay(2000);
  digitalWrite(PH_LED_PIN, LOW);

  // read parameters from EEPROM
  eeprom_read_block(&myRec, (void *)0, sizeof(myRec));

  // check for empty memory or different data block
  if (myRec.magic_number != MAGIC_NUMBER){
    parameters_reset();
  }

  lcd.clear();

  // Free memory check
  //Serial.println(availableMemory());
}

void process_data(void){

  digitalWrite(PH_LED_PIN, HIGH);

  // print temperature
  // Obs.: You can operate the pHduino without a temperature sensor.
  // In this case, you need setup a temperature value 
  // and comment the readADC and calc lines.

  if (myRec.temperature_sensor_flag == true){
    val_T = readADC(PH_TEMP_ADC_PIN, PH_TIME_ADC_READINGS_MICROSECONS);
    T = 100 * val_T * 5.0 / 1024;
  }
  else
  {
    T = myRec.temperature_constant_celcius; // celcius temperature to operates without a temperature sensor.
  }

  floatToString(myStr, T, 1);

  lcd.setCursor(0,0);
  lcd.print(myStr);
  lcd.print((char)223); // degree symbol
  lcd.print("C  ");

  //Serial.print(val_T, DEC);
  //Serial.print(" ");
  Serial.print(myStr);
  Serial.print(" ");

  val_R = readADC(PH_REF_ADC_PIN, PH_TIME_ADC_READINGS_MICROSECONS);
  R = PH_GAIN_STAGE2_REF * (val_R * 5.0 / 1024);

  //floatToString(myStr, R, 3);

  //lcd.setCursor(0,0);
  //lcd.print(myStr);
  //lcd.print((char)223); // degree symbol
  //lcd.print("C  ");

  //Serial.print(val_T, DEC);
  //Serial.print(" ");
  //Serial.print(myStr);
  //Serial.print(" ");

  // print ADC value and voltage of electrochemical potential
  val_E = readADC(PH_PH_ADC_PIN, PH_TIME_ADC_READINGS_MICROSECONS);
  E = -1 * ((val_E * 5.0 / 1024) - R) / PH_GAIN_STAGE1_PH;

  //floatToString(myStr, E, 3);

  lcd.setCursor(0, 1);
  lcd.print((int)(E*1000), DEC); // mili volts
  lcd.print("mV  ");

  lcd.setCursor(8, 1);
  lcd.print("AD:");
  lcd.print(val_E, DEC);
  lcd.print("  ");

  Serial.print(val_E);
  Serial.print(" ");  
  Serial.print((int)(E*1000), DEC); // mili volts
  Serial.print(" ");

  // print pH
  // delta_pH = -(F/(2.303*R*T))*delta_E
  // <http://en.wikipedia.org/wiki/PH>
  // where,
  // gas constant R = 8.31451 J * K^-1 * mol^-1 <http://en.wikipedia.org/wiki/Gas_constant>
  // Kelvin temperature T = celcius temperature plus 273.15 K <http://en.wikipedia.org/wiki/Kelvin>
  // Faraday constant F = 96485 C <http://en.wikipedia.org/wiki/Faraday_constant>
  pH = (float)((-5038.8 * E / (273.15 + T)) + 7.0);

  floatToString(myStr, pH, 2);

  lcd.setCursor(8, 0);
  lcd.print("pH:");
  lcd.print(myStr);
  lcd.print("  ");

  Serial.print(myStr);
  Serial.print(" ");

  // print alarm signal
  if (myRec.pH_alarm_flag == true){
    Serial.print(1, DEC);
    Serial.print(" ");
    if ((pH < myRec.pH_inf) || (pH > myRec.pH_sup)){
      Serial.print(1, DEC);
      pH_alarm_status = true;
      lcd.setCursor(7, 0);
      lcd.print("*");
    }
    else{
      Serial.print(0, DEC);
      pH_alarm_status = false;
      lcd.setCursor(7, 0);
      lcd.print(" ");
    }
  }
  else{
    Serial.print(0, DEC);
    Serial.print(" ");
    Serial.print(0, DEC);
    pH_alarm_status = false;
  }

  Serial.println();

  if (pH_alarm_status == false){
    digitalWrite(PH_LED_PIN, LOW);
  }
  else{
    digitalWrite(PH_BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(PH_BUZZER_PIN, LOW);
  }
}

void process_cmd(void){

  if (process_command_line() == 1){

    // cmd
    if (strcmp(cmd_str, "cmd") == 0){
      Serial.println(cmd_parm_str);

      // cmd phduino on|off
      if (strcmp(cmd_parm[0], "phduino") == 0){

        if (strcmp(cmd_parm[1], "start") == 0){
          myRec.start_flag = true;

          digitalWrite(PH_BUZZER_PIN, HIGH);
          delay(200);
          digitalWrite(PH_BUZZER_PIN, LOW);

        }

        if (strcmp(cmd_parm[1], "stop") == 0){
          myRec.start_flag = false;

          lcd.clear();

          digitalWrite(PH_BUZZER_PIN, HIGH);
          delay(200);
          digitalWrite(PH_BUZZER_PIN, LOW);
        }
      }

      // cmd interval_ms INT
      if ((cmd_n_parms > 1) && (strcmp(cmd_parm[0], "interval_ms") == 0)){
        ul = atol(cmd_parm[1]);
        if (ul > 0){
          myRec.time_between_acquisitions_ms = ul;
          my_timer0 = millis(); // reset the timer
        }
      }

      // cmd set_temp_sensor on|off
      if (strcmp(cmd_parm[0], "set_temp_sensor") == 0){

        if (strcmp(cmd_parm[1], "on") == 0){
          myRec.temperature_sensor_flag = true;
        }

        if (strcmp(cmd_parm[1], "off") == 0){
          myRec.temperature_sensor_flag = false;
        }
      }

      // cmd set_temp FLOAT
      if (strcmp(cmd_parm[0], "set_temp") == 0){

        f = (float)atof(cmd_parm[1]);

        if ((f >= 0.0) && (f <= 100.0)){
          myRec.temperature_constant_celcius = f;
        }
        else{
          Serial.println("Error: Temperature range from 0.0 to 100.0");
        }
      }

      // set pH alarm range
      if (strcmp(cmd_parm[0], "set_ph_alarm") == 0){

        f = (float)atof(cmd_parm[1]);
        f2 = (float)atof(cmd_parm[2]);

        if ((f >= 0.0) && (f <= 14.0) && (f2 >= 0.0) && (f2 <= 14.0) && (f2 > f)){
          myRec.pH_inf = f;
          myRec.pH_sup = f2;
        }
        else{
          Serial.println("Error: pH range from 0.0 to 14.0");
        }
      }      

      // pH alarm
      if (strcmp(cmd_parm[0], "ph_alarm") == 0){

        if (strcmp(cmd_parm[1], "on") == 0){
          myRec.pH_alarm_flag = true;
        }

        if (strcmp(cmd_parm[1], "off") == 0){
          myRec.pH_alarm_flag = false;
          digitalWrite(PH_LED_PIN, LOW);
          lcd.setCursor(7, 0);
          lcd.print(" ");
        }
      }

      // reset parameters
      if (strcmp(cmd_parm[0], "reset") == 0){
        parameters_reset();        
      }

      // cmd help
      if (strcmp(cmd_parm[0], "help") == 0){

        Serial.println("cmd help");
        Serial.println("cmd phduino start|stop");
        Serial.println("cmd interval_ms INT");
        Serial.println("cmd set_temp_sensor on|off");
        Serial.println("cmd set_temp FLOAT");
        Serial.println("cmd set_ph_alarm TEMP_INF TEMP_SUP");
        Serial.println("cmd ph_alarm on|off");
        Serial.println("cmd reset");
      }

      // save parameters
      eeprom_write_block(&myRec, (void *)0, sizeof(myRec));
    }
  }
}

void loop(void){

  my_timer = millis();

  if ((my_timer-my_timer0) > myRec.time_between_acquisitions_ms){

    // reset the timer
    my_timer0 = my_timer;

    if (myRec.start_flag == true){
      process_data();  
    }
  }

  process_cmd();  
}

