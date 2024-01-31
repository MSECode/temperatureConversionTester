#include "TemperatureConvRuleTester.h"


TemperatureConvRuleTester::TemperatureConvRuleTester()
{
    _r_1 = 4700;
    _r_2 = 4700;
    _r_3 = 1000;

    _ptc_offset = 1000;
    _ptc_gradient = 3.851;
    _pga_gain = 2;
    _vcc = 5;
    _resolution_pga = 2.048;
    _resolution_tdb = 32767;
    
    _half_bridge_resistor_coeff = _r_3 / (_r_2 + _r_3);

    _first_res_coeff = _r_1*_r_2 + _r_1*_r_3 + _ptc_offset*_r_2 + _ptc_offset*_r_3;
    _second_res_coeff = _r_3*_r_1 - _r_2*_ptc_offset;    
}

TemperatureConvRuleTester::TemperatureConvRuleTester(std::string sensorType)
{
    if (sensorType == "PT1000")
    {
        _r_1 = 4700;
        _r_2 = 4700;
        _r_3 = 1000;

        _ptc_offset = 1000;
        _ptc_gradient = 3.851;
        _pga_gain = 2;
        _vcc = 5;
        _resolution_pga = 2.048;
        _resolution_tdb = 32767;
        
        _half_bridge_resistor_coeff = _r_3 / (_r_2 + _r_3);

        _first_res_coeff = _r_1*_r_2 + _r_1*_r_3 + _ptc_offset*_r_2 + _ptc_offset*_r_3;
        _second_res_coeff = _r_3*_r_1 - _r_2*_ptc_offset;
    }
    else if (sensorType == "PT100")
    {
        _r_1 = 4700;
        _r_2 = 4700;
        _r_3 = 100; 

        _ptc_offset = 100.0;
        _ptc_gradient = 0.3851;
        _pga_gain = 2;
        _vcc = 5;
        _resolution_pga = 2.048;
        _resolution_tdb = 32767; 

        // define here and calculate when the class object is built to speed up calculations
        // since the value does not change in the sensor type class object
        _half_bridge_resistor_coeff = _r_3 / (_r_2 + _r_3);
        _first_res_coeff = _r_1*_r_2 + _r_1*_r_3 + _ptc_offset*_r_2 + _ptc_offset*_r_3;
        _second_res_coeff = _r_3*_r_1 - _r_2*_ptc_offset;
    }
    else
    {
        std::cout << "Using default";
    }
    
    
    
}

TemperatureConvRuleTester::~TemperatureConvRuleTester()
{;}

void TemperatureConvRuleTester::readInputTemperatures(std::string filename)
{
    std::string line;
    std::ifstream inputFile(filename);
    if (inputFile.is_open())
    {
        while (std::getline(inputFile, line))
        {
            std::stringstream linestream(line);
            std::vector<std::string> temperatures;
            std::string temperature;
            while (std::getline(linestream, temperature, '|'))
            {
                temperatures.push_back(temperature);
            }
            
            _inputTemperature.push_back(std::stod(temperatures[0]));
            _inputRawTemperature.push_back(std::stod(temperatures[1]));
            
        }

        inputFile.close();
        
    }
    else
    {
        std::cout << "Unable to open file";
    }
    
    
}

void TemperatureConvRuleTester::convertRawToTempCelsius()
{
    for (int i = 0; i < _inputRawTemperature.size(); i++)
    {
        double tmp = 0;
        double den = 0;
        tmp = _inputRawTemperature.at(i) * ((_resolution_pga) / (_pga_gain * _vcc * (_resolution_tdb + 1)));
        den = _ptc_gradient * (_r_2 - _r_2*tmp - _r_3*tmp);
        _outputTemperature.push_back((tmp * (_first_res_coeff) / den) + ((_second_res_coeff) / den));
        _deltaCelsius.push_back(std::abs(_outputTemperature.at(i) - _inputTemperature.at(i)));
    }
}


void TemperatureConvRuleTester::convertTempCelsiusToRaw()
{   
    for (int i = 0; i < _inputTemperature.size(); i++)
    {
        double tmp = 0;
        tmp = (( (_ptc_offset + _ptc_gradient * _inputTemperature.at(i)) / (_r_1 + (_ptc_offset + _ptc_gradient * _inputTemperature.at(i)))) - _half_bridge_resistor_coeff) * _vcc;
        tmp = (_resolution_tdb + 1) * ((_pga_gain * tmp) / _resolution_pga);
        _outputRawTemperature.push_back(tmp);
        _deltaRaw.push_back(std::abs(_outputRawTemperature.at(i) - _inputRawTemperature.at(i)));
    }
}


void TemperatureConvRuleTester::writeInputTemperatures()
{
    _celsiusTemperature.open("inputCelsiusTemperature.txt");
    if (_celsiusTemperature.is_open())
    {
        for (double i = -200; i <= 200; i = i+5)
        {
            _celsiusTemperature << i << std::endl;
            _inputTemperature.push_back(i);
        }
        _celsiusTemperature.close();
    }
    else
    {
        std::cout << "Unable to open file";
    }
}

void TemperatureConvRuleTester::writeOutputTemperatures(std::string filename)
{
    _convertedTemperatureOut.open(filename);
    if (_convertedTemperatureOut.is_open())
    {
        _convertedTemperatureOut << 
        std::setw(20) << "iTemp [Celsius]" <<
        std::setw(20) << "iTemp [Raw]" << 
        std::setw(20) << "oTemp [Celsius]" <<
        std::setw(20) << "oTemp [Raw]" <<
        std::setw(20) << "Delta [Celsius]" << 
        std::setw(20) << "Delta [Raw]" << std::endl; 
        for (int i = 0; i < _outputTemperature.size(); ++i)
        {
            _convertedTemperatureOut << 
            std::setw(20) << _inputTemperature.at(i) <<
            std::setw(20) << _inputRawTemperature.at(i) <<
            std::setw(20) << _outputTemperature.at(i) <<
            std::setw(20) << _outputRawTemperature.at(i) <<
            std::setw(20) << _deltaCelsius.at(i) <<
            std::setw(20) << _deltaRaw.at(i) << std::endl;
        }
        _convertedTemperatureOut.close();
    }
    else
    {
        std::cout << "Unable to open file";
    }
}

