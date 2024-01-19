#include "TemperatureConvRuleTester.h"

int main(int argc, char * argv[])
{
    TemperatureConvRuleTester tcrt("PT1000");
    // tcrt.writeInputTemperatures();
    // tcrt.convertTempCelsiusToRaw();
    // tcrt.writeOutputTemperatures();
    tcrt.readInputTemperatures("data/inputTempData_PT1000.txt");
    tcrt.convertRawToTempCelsius();
    tcrt.convertTempCelsiusToRaw();
    tcrt.writeOutputTemperatures("data/outputTempData_PT1000.txt");
    return 0;
}