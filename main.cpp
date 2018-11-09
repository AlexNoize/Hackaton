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

//Variable for Ultrasonic Ranger
timeval t1,t2;
int rise_pulse = 1;

float convert_temperature(int temp);
void mesure_pulse_echo(void * args){
    if(rise_pulse){ //Rising edge
        gettimeofday(&t1,NULL);
        rise_pulse=0;
    }
    else { //Falling edge
        gettimeofday(&t2,NULL);
        rise_pulse=1;
    }

}

int main()
{
    gpio_actuator led(2);
    aio_sensor temperature(0);
    gpio_sensor bouton(3);
    gpio_ultrasonic_echo ultrasonic_echo(4,&mesure_pulse_echo);
    gpio_ultrasonic_trigger ultrasonic_trigger(7);

    int raw_temp_value = 0;
    long Range_In_Cm = 0;

    while(1)
    {
        if(bouton.get_state())
        {
          led.toggle_actuator();
        }
        raw_temp_value = temperature.aio_read();
        ultrasonic_trigger.pulse(10); //10 us pulse
        cout << "La temperature est de : " << convert_temperature(raw_temp_value) << " degree. " << endl;
//        led.toggle_actuator();
        cout << "La distance est de : " << (t2.tv_usec -t1.tv_usec)/58 << " cm. " << endl ;
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
