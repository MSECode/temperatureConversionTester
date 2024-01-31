cmake_minimum_required(VERSION 3.16)
project(TemperatureConvRuleTester)
# set up our program
add_executable(${PROJECT_NAME} ./src/TemperatureConvRuleTester.h ./src/TemperatureConvRuleTester.cpp  ./src/main.cpp )

install(TARGETS ${PROJECT} DESTINATION bin)