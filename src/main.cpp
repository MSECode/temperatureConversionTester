#include "TemperatureConvRuleTester.h"

int main(int argc, char * argv[])
{
    std::string inputFilename = "";
    std::string outputFilename = "";
    std::string sensorType = "";
    if (argc < 2)
    {
        std::cerr << "You need to supply at least the type of sensor used for the conversion. Available [PT100/PT1000]\n";
        return -1;
    }
    else if (argc < 4)
    {
        sensorType = argv[1];
        inputFilename = "data/inputTempData_"+sensorType+".txt";
        outputFilename = "data/outputTempData_"+sensorType+".txt";
        std::cout << "Now using the default temperature test files " << inputFilename << " and " << outputFilename << " for the conversion. For specific one pass <inputFilename> and <outputFilename> as third and fourth arguments\n";
    }
    else
    {
        sensorType = argv[1];
        inputFilename = argv[2];
        outputFilename = argv[3];
        std::cout << "Starting conversion program for sensor type " << argv[1] << ", passing values in file " << argv[2] << " and expecting outputs in file " << argv[3] << "\n";
    }
    
    TemperatureConvRuleTester tcrt(sensorType);
    tcrt.readInputTemperatures(inputFilename);
    tcrt.convertRawToTempCelsius();
    tcrt.convertTempCelsiusToRaw();
    tcrt.writeOutputTemperatures(outputFilename);
    return 0;
}