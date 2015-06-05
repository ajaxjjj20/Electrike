#include "Arduino.h"
#include "Rider.h"
#include <EEPROM.h>

Rider::Rider(char letters[3], uint8_t oldness, uint8_t preferredHR, bool genderMale, uint16_t massGravity)
{
	for(int i = 0; i < 3; i++) {
		initials[i] = letters[i];
	}
	age = oldness;
	recommendedHeartRate = preferredHR;
	male = genderMale;
	weight = massGravity;
}

Rider::Rider(void)
{

}

/*int Rider::writeNametoEEPROM(char initials[3], int addr)
{
  for(int i = 0; i < 3; i++) {
    EEPROM.write(addr, initials[i]);
    addr++;
  }
  return addr;
}*/			//Shouldn't need this function if EEPROMAnything works

double Rider::CalculateCaloriesBurned(uint32_t seconds, uint8_t heartRate)
{
	double caloriesBurned = 0;
	double hours = (double)seconds / 3600.0; 
	double kg = (double) weight * 0.453592;
	//heartRate is in beats per minute
	//weight is in kilograms
	//age is in years
	//time is in hours
	//bpm must be between 124 and 200
	if(male) {
		//caloriesBurned = ((double)age*.2017-(double)weight*.09036+(double)heartRate *.6309 - 55.0969)*(double)seconds/4.184;
		caloriesBurned = ((-55.0969 + 0.6309*(double)heartRate + 0.1988*kg + 0.2017*(double)age)/4.184)*60.0*hours;
	}
	else {
		//caloriesBurned = ((double)age*.074-(double)weight*.05741+(double)heartRate*.4472 - 20.4022)*(double)seconds/4.184;
		caloriesBurned = ((-20.4022 + 0.4472*(double)heartRate - 0.1263*kg +0.074*(double)age)/4.184)*60*hours;
	}
	Serial.print("Hours:	");
	Serial.println(hours);
	Serial.print("Kg:	");
	Serial.println(kg);
	Serial.print("Heart Rate: 	");
	Serial.println((double)heartRate);
	Serial.print("Age:	");
	Serial.println((double) age);
	if(caloriesBurned < 0) {
		caloriesBurned = 0;
	}
	return caloriesBurned;
}

void Rider::EEPROMwrite(int pos)
{
	EEPROM.write(pos, initials[0]);
	EEPROM.write(pos+1,initials[1]);
	EEPROM.write(pos+2,initials[2]);
	EEPROM.write(pos+3,age);
	EEPROM.write(pos+4,recommendedHeartRate);
	EEPROM.write(pos+5,male);
	EEPROM.write(pos+6, (weight >> 8) & 0xFF);		//Store msb of weight first
	EEPROM.write(pos+7, weight & 0xFF);				//Store lsb of weight first
}

void Rider::Load(uint16_t pos)
{
	initials[0] = EEPROM.read(pos);
	initials[1] = EEPROM.read(pos + 1);
	initials[2] = EEPROM.read(pos + 2);
	age = EEPROM.read(pos + 3);
	recommendedHeartRate = EEPROM.read(pos + 4);
	male = EEPROM.read(pos + 5);
	weight = (EEPROM.read(pos + 6) << 8) | EEPROM.read(pos + 7);
}

void Rider::Print(LiquidCrystal lcd)
{
	lcd.clear();
	lcd.print("Rider ID: ");
	lcd.print(initials[0]);
	lcd.print(initials[1]);
	lcd.print(initials[2]);
	lcd.setCursor(0,1);
	lcd.print("HR: ");
	lcd.print(recommendedHeartRate);
	lcd.print(" , Gender: ");
	if(male) {
		lcd.print("M");
	}
	else {
		lcd.print("F");
	}
	lcd.setCursor(0,2);
	lcd.print("Rider Age: ");
	lcd.print(age);
	lcd.setCursor(0,3);
	lcd.print("Weight: ");
	lcd.print(weight);
	delay(5000);
}
