#include <mraa/gpio.h>
#include <mraa/aio.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <iostream>

#include "grove.h"

using namespace std;

/*############ GPIO_GROVE ############## */

//CONSTRUCTEURS
gpio_grove::gpio_grove(const int port){
  m_gpio = mraa_gpio_init(port);
  if (m_gpio == NULL) {
    mraa_deinit();
  }
}

/*############ GPIO_SENSOR ############## */

//CONSTRUCTEURS
gpio_sensor::gpio_sensor(const int port):gpio_grove(port){

  int status;
  /* set GPIO to input */
  status = mraa_gpio_dir(m_gpio, MRAA_GPIO_IN);

//  //Levée de l'exception si le gpio ne peut pas être initialisé en input
//  if (status != MRAA_SUCCESS)
//    throw gpio_sensor_init_err;
}

//METHODES
int gpio_sensor::get_state(){
  int status;
  status = mraa_gpio_read(m_gpio);

//  //Levée de l'exception si la lecture de l'état du gpio ne peut pas être faite correctement
//  if (status == -1)
//    throw gpio_sensor_read_err;

  return status;
}

/*############ GPIO_ACTUATOR ############## */

//CONSTRUCTEURS
gpio_actuator::gpio_actuator(const int port):gpio_grove(port){
  int status;
  /* set GPIO to output */
  status = mraa_gpio_dir(m_gpio, MRAA_GPIO_OUT);
  State = 0;

//  //Levée de l'exception si le gpio ne peut pas être initialisé en output
//  if (status != MRAA_SUCCESS)
//    throw gpio_actuator_init_err;
}


//METHODES
void gpio_actuator::set_on(){

  int status;
  status = mraa_gpio_write(m_gpio, 1);
  State = 1;

//  //Levée de l'exception si le changement d'état n'est pas possible
//  if (status != MRAA_SUCCESS)
//    throw gpio_actuator_write_err;
}

void gpio_actuator::set_off(){

  int status;
  status = mraa_gpio_write(m_gpio, 0);
  State = 0;

//  //Levée de l'exception si le changement d'état n'est pas possible
//  if (status != MRAA_SUCCESS)
//    throw gpio_actuator_write_err;
}
void gpio_actuator::toggle_actuator(){
    if (State == 1){
        mraa_gpio_write(m_gpio, 0);
        State = 0;
    }
    else{
        mraa_gpio_write(m_gpio, 1);
        State = 1;
    }
}

/*############ AIO_GROVE ############## */

//CONSTRUCTEURS

aio_grove::aio_grove(const int port){
  m_aio = mraa_aio_init(port);

  //Levée de l'exception lors de l'initialisation du port aio
  if (m_aio == NULL) {
    mraa_deinit();
//    throw aio_grove_init_err;
  }
}

/*############ AIO_SENSOR ############## */

//CONSTRUCTEURS
aio_sensor::aio_sensor(const int port):aio_grove(port){}

//METHODES
int aio_sensor::aio_read() {
  return mraa_aio_read(m_aio);
}

float  aio_sensor::aio_read_float() {
  return mraa_aio_read_float(m_aio); //mraa_aio_read_float(m_aio)
}
