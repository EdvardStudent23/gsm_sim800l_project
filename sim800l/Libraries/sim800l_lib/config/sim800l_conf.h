/*
 * sim800l_conf.h
 *
 *  Created on: Jan 10, 2025
 *      Author: Edward Student
 */

#ifndef SIM800L_CONF_H_
#define SIM800L_CONF_H_

#include "stm32f3xx_hal.h"
#include "lcd5110.h"

// UART Configuration. Choose uart connected to sim800l
extern UART_HandleTypeDef *SIM800L_UART_INSTANCE;

// default timeout
#define SIM800L_DEFAULT_TIMEOUT 1000;

//buffers sizes
#ifndef SIM800L_TX_BUFFER_SIZE
#define SIM800L_TX_BUFFER_SIZE 64   // Transmit buffer size
#endif

#ifndef SIM800L_RX_BUFFER_SIZE
#define SIM800L_RX_BUFFER_SIZE 256  // Receive buffer size. Such size, because a responce for some commands is big
#endif

#define SIM800L_SMS_BUFFER_SIZE 140  // SMS buffer. 140 is a standard size of sms

// The global buffers configuration.
extern uint8_t TxData[SIM800L_TX_BUFFER_SIZE];
extern uint8_t RxData[SIM800L_RX_BUFFER_SIZE];
extern uint8_t SMSBuffer[SIM800L_SMS_BUFFER_SIZE];

// The LCD Nokia 5110.
extern LCD5110_display lcd1;

// Enable/disable LCD output
extern int SIM800L_LCD_OUTPUT_ENABLED; // 1 = enabled, 0 = disabled

// LED Configuration for status indication
void sim800l_set_led_pins(
    GPIO_TypeDef *led1_port, uint16_t led1_pin,
    GPIO_TypeDef *led2_port, uint16_t led2_pin,
    GPIO_TypeDef *led3_port, uint16_t led3_pin,
    GPIO_TypeDef *led4_port, uint16_t led4_pin
);

#endif /* SIM800L_CONF_H_ */
