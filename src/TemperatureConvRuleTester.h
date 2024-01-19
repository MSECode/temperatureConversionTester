#ifndef __TEMPERATURECONVRULETESTER__
#define __TEMPERATURECONVRULETESTER__

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>

class TemperatureConvRuleTester
{
private:
    // resistors of the voltage divider bridge
    double _r_1;
    double _r_2;
    double _r_3;
    
    double _ptc_offset;    // offset of the temperature sensor line
    double _ptc_gradient;  // slope/gradient of the temperature sensor line
    double _pga_gain;      // ADC gain set for the tdb (temperature detection board)

    double _vcc;               // vcc that enters the voltage divider bridge
    double _resolution_pga; // resolution of the internal pga of the tdb
    double _resolution_tdb; // resolution used for the raw value for the output of the tdb
    
    // define here and calculate when the class object is built to speed up calculations
    // since the value does not change in the sensor type class object
    double _half_bridge_resistor_coeff;
    double _first_res_coeff;
    double _second_res_coeff;

    std::vector<double> _inputTemperature;
    std::vector<double> _outputTemperature;
    std::vector<double> _inputRawTemperature;
    std::vector<double> _outputRawTemperature;
    std::vector<double> _deltaCelsius;
    std::vector<double> _deltaRaw;

    std::ofstream _celsiusTemperature;
    std::ofstream _convertedTemperatureOut;

public:
    TemperatureConvRuleTester();
    TemperatureConvRuleTester(std::string sensorType = "PT1000");
    ~TemperatureConvRuleTester();

    TemperatureConvRuleTester(const TemperatureConvRuleTester&) = default;
    TemperatureConvRuleTester(TemperatureConvRuleTester&&) = default;
    TemperatureConvRuleTester& operator=(const TemperatureConvRuleTester&) = default;
    TemperatureConvRuleTester& operator=(TemperatureConvRuleTester&&) = default;

    void readInputTemperatures(std::string filename);

    void convertRawToTempCelsius();
    void convertTempCelsiusToRaw();

    void writeInputTemperatures();
    
    void writeOutputTemperatures(std::string filename);
};



#endif