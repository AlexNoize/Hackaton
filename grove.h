#ifndef GROVE_H_INCLUDED
#define GROVE_H_INCLUDED

#include <mraa/i2c.h>
#include <mraa/gpio.h>
#include <mraa/aio.h>
#include <mraa/uart.h>
#include <unistd.h>
#include <string>
#include <iostream>
using namespace std;
/*############ GPIO_GROVE ############## */

class gpio_grove{

 public:
  //CONSTRUCTEUR
  gpio_grove(const int port);

 protected:
  //ATTRIBUTS
  int State; //0 Low - 1 High
  mraa_gpio_context m_gpio;

};//FIN CLASSE GPIO_GROVE

/*############ GPIO_SENSOR ############## */

class gpio_sensor : public gpio_grove {

 public:
  //CONSTRUCTEURS
 gpio_sensor(const int port);

  //METHODE
  int get_state();
};//FIN CLASSE GPIO_SENSOR

/*############ GPIO_ACTUATOR ############## */

class gpio_actuator : public gpio_grove {

 public:
  //CONSTRUCTEURS
 gpio_actuator(const int port);

  //METHODS
  void set_on();
  void set_off();
  void toggle_actuator();

};//FIN CLASSE GPIO_ACTUATOR


/*############ AIO_GROVE ############## */

class aio_grove {

 public:
  //CONSTRUCTEUR
  aio_grove(const int port);

 protected:
  //ATTRIBUTS
  mraa_aio_context m_aio;

};//FIN CLASSE AIO_GROVE

/*############ AIO_SENSOR ############## */

class aio_sensor:public  aio_grove{

 public:
  //CONSTRUCTEURS
  aio_sensor(const int port);

  //METHODS
  int aio_read();
  float aio_read_float();


};//FIN CLASSE AIO_SENSOR

#endif // GROVE_H_INCLUDED
