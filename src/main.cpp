#include "TemperatureConvRuleTester.h"

int main(int argc, char * argv[])
{
    TemperatureConvRuleTester tcrt("PT100");
    // tcrt.writeInputTemperatures();
    // tcrt.convertTempCelsiusToRaw();
    // tcrt.writeOutputTemperatures();
    tcrt.readInputTemperatures("data/inputTempData_PT100.txt");
    tcrt.convertRawToTempCelsius();
    tcrt.convertTempCelsiusToRaw();
    tcrt.writeOutputTemperatures("data/outputTempData_PT100.txt");
    return 0;
}