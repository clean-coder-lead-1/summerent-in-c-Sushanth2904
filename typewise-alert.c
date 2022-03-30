#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) 
{
  BreachType ReturnVal=NORMAL;	
  if(value < lowerLimit)
  {
    //return TOO_LOW;
	ReturnVal=TOO_LOW;
  }
  if(value > upperLimit)
  {
   // return TOO_HIGH;
   ReturnVal=TOO_HIGH;
  }
  return ReturnVal;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC)
{
  int lowerLimit = 0;
  int upperLimit = 0;
  // switch(coolingType) 
  // {
    // case PASSIVE_COOLING:
	// {
      // lowerLimit = 0;
      // upperLimit = 35;
      // break;
    // }
	// case HI_ACTIVE_COOLING:
	// { 
	  // lowerLimit = 0;
      // upperLimit = 45;
      // break;
    // }
	// case MED_ACTIVE_COOLING:
	// { 
	  // lowerLimit = 0;
      // upperLimit = 40;
	  // break;
	// }
	
  // }
  if(coolingType==PASSIVE_COOLING)
  {
	  upperLimit = 35;
  }
  if(coolingType==HI_ACTIVE_COOLING)
  {
	  upperLimit = 45;
  }
  if(coolingType==MED_ACTIVE_COOLING)
  {
	  upperLimit = 40;
  }
  
 // return inferBreach(temperatureInC, lowerLimit, upperLimit);
  return (temperatureInC<lowerLimit?TOO_LOW:temperatureInC>upperLimit?TOO_HIGH:NORMAL);
}
 
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{

  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  // switch(alertTarget) 
  // {
    // case TO_CONTROLLER:
	// {
      // sendToController(breachType);
      // break;
	// }
    // case TO_EMAIL:
	// {
      // sendToEmail(breachType);
      // break;
	// }
  // }
  if(alertTarget==TO_CONTROLLER)
  {
	  sendToController(breachType);
  }
  else if(alertTarget==TO_EMAIL)
  {
	  sendToEmail(breachType);
  }
  else
  {
	  //do nothing
  }

}

void sendToController(BreachType breachType) 
{
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) 
{
  const char* recepient = "a.b@c.com";
  // switch(breachType) 
  // {
    // case TOO_LOW:
	// {
      // printf("To: %s\n", recepient);
      // printf("Hi, the temperature is too low\n");
      // break;
	// }
    // case TOO_HIGH:
	// {
      // printf("To: %s\n", recepient);
      // printf("Hi, the temperature is too high\n");
      // break;
	// }
    // case NORMAL:
      // break;
  // }
  if(breachType==TOO_LOW)
  {
	  printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
  }
  else if(breachType==TOO_HIGH)
  {
	  printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
  }
  else
  {
  }

}
