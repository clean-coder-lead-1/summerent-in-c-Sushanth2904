/** 
 * \file typewise-alert.c  
 * \brief  This file handles battery temperature monitoring and damage prevention.
 *
 * Based on the temperature measured, classify as too high or too low.
 * 1. This classification depends on the type of cooling.
 * With active cooling, the battery can reach higher temperatures before
 * taking action.
 *
 * 2. Transmit the classification to take action: When the system has a 
 * controller, send the classification to it. In the absence of a controller,
 * send the classification via email. In this project, the transmission is 
 * 'simulated' by printing on the console.
 * 
 **/


/***************************************************************************************************
**                                    Includes                                                    **
***************************************************************************************************/
#include "typewise-alert.h"

/**
****************************************************************************************************
 * \fn  BreachType inferBreach(double value, double lowerLimit, double upperLimit)
 * \brief  This function classifies the temperature measured as too low or too high
 *         based on the lower limit and upper limit values and returns the state accordingly.
 *
 * \param : double value
 *          Description : Battery Temperature value that is measured.
 *
 * \param : double lowerLimit
 *          Description : The temperature lower limit value
 *
 * \param : double upperLimit
 *          Description : The temperature upper limit value
 *
 * \return BreachType
****************************************************************************************************
*/
BreachType inferBreach(double value, double lowerLimit, double upperLimit)
{
    BreachType currentState = NORMAL;

    /** Check if the temperature value is below the lower limit */
    if(value < lowerLimit)
    {
        currentState = TOO_LOW;
    }
    /** Check if the temperature value is above the upper limit */
    else if(value > upperLimit)
    {
        currentState = TOO_HIGH;
    }
    else
    {
        /** Do nothing, initial state is NORMAL */
    }

    return currentState;
}

/**
****************************************************************************************************
 * \fn  BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC)
 * \brief  This function sets the lower and upper limit temperatures based upon the cooling type.
 *          With this, inferBreach function is called to classify the current temperature.
 *
 * \param : CoolingType coolingType
 *          Description : Cooling type of the battery
 *
 * \param : double temperatureInC
 *          Description : Battery Temperature value that is measured.
 *
 * \return BreachType
****************************************************************************************************
*/
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC)
{
    BreachType currentState = NORMAL;
    switch(coolingType)
    {
        case PASSIVE_COOLING:
            /** For PASSIVE Cooling, the lower limit is 0 and upper limit is 35 */
            currentState = inferBreach(temperatureInC, 0, 35);
            break;

        case HI_ACTIVE_COOLING:
            /** For HI ACTIVE Cooling, the lower limit is 0 and upper limit is 45 */
            currentState = inferBreach(temperatureInC, 0, 45);
            break;

        default:
            /** The default case is for MED_ACTIVE_COOLING 
              * For HI ACTIVE Cooling, the lower limit is 0 and upper limit is 40
              */
            currentState = inferBreach(temperatureInC, 0, 40);
            break;
    }

    return currentState;
}

/**
****************************************************************************************************
 * \fn  void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC)
 * \brief  This function sends alert to controller or to email based on the temperature classification.
 *
 * \param : AlertTarget alertTarget
 *          Description : Defines where the alert is to be sent.
 *          Possible values are : TO_CONTROLLER
 *                                TO_EMAIL
 *
 * \param : BatteryCharacter batteryChar
 *          Description : Structure which contains Cooling type and the Brand of the battery
 *
 * \param : double temperatureInC
 *          Description : The temperature upper limit value
 *
 * \return void
****************************************************************************************************
*/
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC)
{
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType,
                                                      temperatureInC);

    /** Check if the Alert has to be sent to Controller, else send to EMAIL */
    if(TO_CONTROLLER == alertTarget)
    {
        sendToController(breachType);
    }
    else
    {
        sendToEmail(breachType);
    }
}

/**
****************************************************************************************************
 * \fn  void sendToController(BreachType breachType)
 * \brief  This function sends the temperature state alert to controller.
 *
 * \param : BreachType breachType
 *          Description : Contains the state of the battery temperature
 *          Possible values are : NORMAL,
 *                                TOO_LOW,
 *                                TOO_HIGH
 *
 * \return void
****************************************************************************************************
*/
void sendToController(BreachType breachType)
{
    const unsigned short header = 0xfeed;
    printf("%x : %x\n", header, breachType);
}

/**
****************************************************************************************************
 * \fn  void sendToEmail(BreachType breachType)
 * \brief  This function sends the temperature state alert to email.
 *
 * \param : BreachType breachType
 *          Description : Contains the state of the battery temperature
 *          Possible values are : NORMAL,
 *                                TOO_LOW,
 *                                TOO_HIGH
 *
 * \return void
****************************************************************************************************
*/
void sendToEmail(BreachType breachType)
{
    const char* recepient = "a.b@c.com";
    switch(breachType)
    {
        case TOO_LOW:
            printf("To: %s\n", recepient);
            printf("Hi, the temperature is too low\n");
            break;
        case TOO_HIGH:
            printf("To: %s\n", recepient);
            printf("Hi, the temperature is too high\n");
            break;
        default:
            /** Nothing to be done when the state is NORMAL */
            break;
    }
}
