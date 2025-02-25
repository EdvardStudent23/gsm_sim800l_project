/*
 * sim800l.h
 *
 *  Created on: Jan 7, 2025
 *      Author: Edward Srudent
 */

#ifndef SIM800L_H_
#define SIM800L_H_

#include "stm32f3xx_hal.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

//init sim800l
void sim800l_init(UART_HandleTypeDef *uart_handle);

// Send AT-command
void sim800l_send_command(const char *command);

// Send text (without \r\n)
void sim800l_send_text(const char *text);

// callback for uart interruptions
void sim800l_uart_rx_callback(UART_HandleTypeDef *huart);

void send_pin(const char *pincode); // send pincode if your sim-card needs it
void check_net();
void send_sms();

void clear_buffs_flags();

// check the information about the module
void what_manuf();// check the information about the manufacturer (producer)
void what_model(); // get info about a model of the module
void what_rev(); //get info about a firmware / revision of the module
void what_imei(); //get the imei of the module

// checking the status of the module
void signal_rate(); //check the quality of a signal
void check_net_reg(); // check whether the sim800l is connectd to the net and show the code
void check_sim(); // check the status of the sim-card
void sleep_mode(); // turn on/off the sleep mode

// check uart connection
void get_baud_rate(); // show the current baud rate
void set_baud_rate(); // you can set the baud rate. BUT its recommended
// to set the baud rate to 9600 (standard BR of sim800l)

//Check the operation mode
void get_oper_mode(); //show the current operation mode;
void set_oper_mode(); // set the operation mode;
void set_default(); // set the module to default settings

// network settings
void curr_moper_info(); //show the data about current mobile 2G operator;
void find_moper(); // show available mobile operators in your area;

// module time
void time_check(); // show the system time of the module

// power suppliement
void power_rate(); // show the power rate and a current voltage

// SMS
void sms_send(const char *phone_number, const char *message); // send sms
void sms_set_text_mode(); // set text mode SMS
void sms_check_all(); // show all sms

//Call function
void make_call(const char *phone_number);
void make_call_ext(const char *phone_number); //extended make call

//set echo mode
void sim800l_echo(const char mode);

//lcd output
void change_lcd_output(int enable);

//leds
void sim800l_set_led_pins(
    GPIO_TypeDef *led1_port, uint16_t led1_pin,
    GPIO_TypeDef *led2_port, uint16_t led2_pin,
    GPIO_TypeDef *led3_port, uint16_t led3_pin,
    GPIO_TypeDef *led4_port, uint16_t led4_pin
);

#endif /* SIM800L_H_ */
