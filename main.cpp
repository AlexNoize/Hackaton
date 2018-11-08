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

float convert_temperature(float temp);

int main()
{
    gpio_actuator led(2);
    aio_sensor temperature(0);
    float temp_value_raw = 0.0;

    while(1)
    {
        temp_value_raw = temperature.aio_read_float();
        cout << "La temperature est " << convert_temperature(temp_value_raw) << endl;
        led.toggle_actuator();
        sleep(1);
    }
    return 0;
}

float convert_temperature(float temp) {
    float temp_value = 1023.0/temp-1.0;

    // convert to temperature via datasheet
    return 1.0/(log(temp_value)/4275+1/298.15)-273.15;
}
