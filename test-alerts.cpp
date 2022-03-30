#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("Classifying the Battery Temperature", "[inferBreach]" )
{
    REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
    REQUIRE(inferBreach(25, 20, 30) == NORMAL);
    REQUIRE(inferBreach(45, 20, 30) == TOO_HIGH);
}

TEST_CASE("Set limits and classify the Battery Temperature", "[checkAndAlert]" )
{
    REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 25) == NORMAL);
    REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 45) == TOO_HIGH);
    REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -2) == TOO_LOW);

    REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 35) == NORMAL);
    REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50) == TOO_HIGH);
    REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -3) == TOO_LOW);

    REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 30) == NORMAL);
    REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 45) == TOO_HIGH);
    REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -1) == TOO_LOW);
}

TEST_CASE("Checks the temperature state of the battery and alerts accordingly")
{
    BatteryCharacter batteryChar = {PASSIVE_COOLING, {'B','O','S','C','H'}};
    checkAndAlert(TO_CONTROLLER, batteryChar, 25);
    checkAndAlert(TO_CONTROLLER, batteryChar, 45);
    checkAndAlert(TO_CONTROLLER, batteryChar, -2);
    checkAndAlert(TO_EMAIL, batteryChar, 25);
    checkAndAlert(TO_EMAIL, batteryChar, 45);
    checkAndAlert(TO_EMAIL, batteryChar, -2);

    batteryChar.coolingType = HI_ACTIVE_COOLING;
    checkAndAlert(TO_CONTROLLER, batteryChar, 35);
    checkAndAlert(TO_CONTROLLER, batteryChar, 50);
    checkAndAlert(TO_CONTROLLER, batteryChar, -3);
    checkAndAlert(TO_EMAIL, batteryChar, 35);
    checkAndAlert(TO_EMAIL, batteryChar, 50);
    checkAndAlert(TO_EMAIL, batteryChar, -3);

    batteryChar.coolingType = MED_ACTIVE_COOLING;
    checkAndAlert(TO_CONTROLLER, batteryChar, 30);
    checkAndAlert(TO_CONTROLLER, batteryChar, 45);
    checkAndAlert(TO_CONTROLLER, batteryChar, -1);
    checkAndAlert(TO_EMAIL, batteryChar, 30);
    checkAndAlert(TO_EMAIL, batteryChar, 45);
    checkAndAlert(TO_EMAIL, batteryChar, -1);
}