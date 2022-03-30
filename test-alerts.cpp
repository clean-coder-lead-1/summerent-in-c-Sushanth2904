#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
}
TEST_CASE("Check and Alert") 
{
	BatteryCharacter batteryChar;
	batteryChar.coolingType=PASSIVE_COOLING;
  checkAndAlert(TO_CONTROLLER,batteryChar,30);
}