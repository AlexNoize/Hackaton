#include <mraa/i2c.h>
#include <mraa/gpio.h>
#include <mraa/aio.h>
#include <unistd.h>
#include <math.h>
#include <iostream>
#include <string>
#include <time.h>
#include <sys/time.h>

#include "grove.h"

using namespace std;

//Conversion of the value read by the analog input
const int B = 4275; //B value of the thermistor
const int R0 = 100000; //R0 = 100kOhm
//help : http://wiki.seeedstudio.com/Grove-Temperature_Sensor_V1.2/

float convert_temperature(int temp);

int main()
{
    gpio_actuator led(2);
    aio_sensor temperature(0);
    int temp_value_raw = 0;

    while(1)
    {
        temp_value_raw = temperature.aio_read();
        cout << "La temperature est de " << convert_temperature(temp_value_raw) << endl;
        led.toggle_actuator();
        sleep(1);
    }
    return 0;
}

float convert_temperature(int temp) {
    float R = 1023.0/temp-1.0;
    R=R*R0;

    // convert to temperature via datasheet
    return 1.0/(log(R/R0)/B+1.0/298.15)-273.15;
}
