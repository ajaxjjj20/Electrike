#ifndef Rider_h
#define Rider_h

#include "Arduino.h"
#include "LiquidCrystal.h"

class Rider
{
  public:
	char initials[3];
	uint8_t age;
	uint8_t recommendedHeartRate;
    bool male;
    uint16_t weight; 
	//uint16_t caloriesBurned;
	//uint8_t ID;
	Rider(char letters[3], uint8_t oldness, uint8_t preferredHR, bool genderMale, uint16_t massGravity);
	Rider(void);
	double CalculateCaloriesBurned(uint32_t seconds, uint8_t heartRate);
	void EEPROMwrite(int pos);
	void Print(LiquidCrystal lcd);
	void Load(uint16_t pos);
	//int writeNametoEEPROM(char initials[3], int addr);  //Shouldn't need this will EEPROMAnything header
};

#endif
