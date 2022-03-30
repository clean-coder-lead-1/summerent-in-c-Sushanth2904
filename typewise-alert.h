/** \file typewise-alert.h
 * \brief 
 *    This File contails the structures, enumns and functions
 *    used for battery temperature monitoring.
 */

#if !defined(TYPEWISE_ALERT_H)
#define TYPEWISE_ALERT_H

#pragma once

/***************************************************************************************************
**                                    Includes                                                    **
***************************************************************************************************/
#include <stdio.h>

/****************************************************************************************************************
**                                   Enumerations                                                              **
****************************************************************************************************************/
/** \enum CoolingType
* To identify the Cooling type used in the battery
*/
typedef enum
{
    PASSIVE_COOLING = 0,
    HI_ACTIVE_COOLING = 1,
    MED_ACTIVE_COOLING = 2
} CoolingType;

/** \enum BreachType
* To identify the Breach type or the current state of the battery's temperature
*/
typedef enum
{
    NORMAL = 0,
    TOO_LOW = 1,
    TOO_HIGH = 2
} BreachType;

/** \enum AlertTarget
* To identify the the target to be alerted
*/
typedef enum
{
    TO_CONTROLLER = 0,
    TO_EMAIL = 1
} AlertTarget;


/****************************************************************************************************************
**                                   Structures                                                               **
****************************************************************************************************************/
/** \struct BatteryCharacter
* The structure holds the Cooling type and the brand name of the battery
* 
*/
typedef struct
{
    CoolingType coolingType;
    char brand[48];
} BatteryCharacter;

/****************************************************************************************************************
**                          Exposed Function Prototypes                                                        **
****************************************************************************************************************/
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
BreachType inferBreach(double value, double lowerLimit, double upperLimit);

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
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

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
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

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
void sendToController(BreachType breachType);

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
void sendToEmail(BreachType breachType);


#endif /*!defined(TYPEWISE_ALERT_H)*/
