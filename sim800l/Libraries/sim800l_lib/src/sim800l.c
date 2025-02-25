/*
 * sim800l.c
 *
 *  Created on: Jan 7, 2025
 *      Author: Edward Student
// */
#include "main.h"
#include "sim800l.h"
#include "stm32f3xx_hal.h"
#include "usart.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>
//nokia 5110 lcd
#include "lcd5110.h"
//#include "lcd_shared.h"
// configuration file
#include "sim800l_conf.h"


static uint8_t rx_index = 0;
static uint8_t rx_byte = 0; // buffer for 1 byte (temporary)
static volatile uint8_t data_ready = 0; // готовність даних, флажок

UART_HandleTypeDef *SIM800L_UART_INSTANCE;
uint8_t RxData[SIM800L_RX_BUFFER_SIZE];
uint8_t TxData[SIM800L_TX_BUFFER_SIZE];

int SIM800L_LCD_OUTPUT_ENABLED = 1;

//for leds in functions
GPIO_TypeDef *SIM800L_LED1_PORT = NULL;
uint16_t SIM800L_LED1_PIN = 0;
GPIO_TypeDef *SIM800L_LED2_PORT = NULL;
uint16_t SIM800L_LED2_PIN = 0;
GPIO_TypeDef *SIM800L_LED3_PORT = NULL;
uint16_t SIM800L_LED3_PIN = 0;
GPIO_TypeDef *SIM800L_LED4_PORT = NULL;
uint16_t SIM800L_LED4_PIN = 0;

void sim800l_send_command(const char *command) {
	printf("Sending command to SIM800L: %s\n", command);
    snprintf((char *)TxData, sizeof(TxData), "%s\r\n", command); // Копіюємо команду у буфер

    if (SIM800L_LCD_OUTPUT_ENABLED) {
		LCD5110_print("Send: ", BLACK, &lcd1);
		LCD5110_print((char *)TxData, BLACK, &lcd1); // the command we sent
    }
    HAL_Delay(1200);

    HAL_UART_Transmit(SIM800L_UART_INSTANCE, TxData, strlen((char *)TxData), 1000); // Надсилаємо через UART
    LCD5110_clear_scr(&lcd1);
}

void sim800l_send_text(const char *text) {
    snprintf((char *)TxData, sizeof(TxData), "%s", text); // Без \r\n
    if (SIM800L_LCD_OUTPUT_ENABLED) {
    		LCD5110_print("Send: ", BLACK, &lcd1);
    		LCD5110_print((char *)TxData, BLACK, &lcd1); // the command we sent
        }
    HAL_Delay(1200);
    HAL_UART_Transmit(SIM800L_UART_INSTANCE, TxData, strlen((char *)TxData), 1000);
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart == SIM800L_UART_INSTANCE) { // check inter from needed UART
        if (rx_index < sizeof(RxData) - 1) {
            RxData[rx_index++] = rx_byte; //+buff
            if (rx_byte == '\n') {
                RxData[rx_index] = '\0'; // term 0
                data_ready = 1;
            }
        } else {
            rx_index = 0; // buffer overflow - 0 index
        }

        // receive next bute
        HAL_UART_Receive_IT(huart, &rx_byte, 1);
    }
}

void clear_buffs_flags(){
	memset(TxData, 0, sizeof(TxData));
	memset(RxData, 0, sizeof(RxData));
	rx_index = 0;
	data_ready = 0;
}

void sim800l_init(UART_HandleTypeDef *uart_handle) {
	if (SIM800L_LCD_OUTPUT_ENABLED) {
		LCD5110_print("Initializing of SIM800L\n", BLACK, &lcd1);
	}
	HAL_Delay(1000);
	LCD5110_clear_scr(&lcd1);
    clear_buffs_flags();

    HAL_UART_Receive_IT(SIM800L_UART_INSTANCE, &rx_byte, 1);
    sim800l_send_command("AT");
    HAL_Delay(500);

    // Перевіряємо відповідь
    if (data_ready && strstr((char *)RxData, "OK")) {
        HAL_GPIO_WritePin(SIM800L_LED2_PORT, SIM800L_LED2_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(SIM800L_LED1_PORT, SIM800L_LED1_PIN, GPIO_PIN_SET);
        if (SIM800L_LCD_OUTPUT_ENABLED) {
			LCD5110_print((char *)RxData, BLACK, &lcd1);
			LCD5110_print("The module is initialised\n", BLACK, &lcd1);
        }
        HAL_Delay(1000);
    } else {
        HAL_GPIO_WritePin(SIM800L_LED2_PORT, SIM800L_LED2_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(SIM800L_LED1_PORT, SIM800L_LED1_PIN, GPIO_PIN_RESET);
        if (SIM800L_LCD_OUTPUT_ENABLED) {
        	LCD5110_print("No response :(\n", BLACK, &lcd1);
        }
        HAL_Delay(1000);
        LCD5110_clear_scr(&lcd1);
    }


}

void send_pin(const char *pincode) {
	char pincom[20];
	snprintf(pincom, sizeof(pincom), "AT+CPIN=\"%s\"", pincode);
	if (SIM800L_LCD_OUTPUT_ENABLED) {
		LCD5110_print("Sending the pincode", BLACK, &lcd1);
	}
	sim800l_send_command(pincom);
}

void check_net() {
	sim800l_send_command("AT+CREG?");
}


void send_sms(const char *phone_number, const char *message) {
	char command[64];
	// Set the module in text mode sms
	sim800l_send_command("AT+CMGF=1");
	HAL_Delay(200);

	snprintf(command, sizeof(command), "AT+CMGS=\"%s\"", phone_number);
	sim800l_send_command(command);
	HAL_Delay(300);

	// send the message and the termination symbols Ctrl+Z (0x1A)
	sim800l_send_command(message);
	HAL_UART_Transmit(SIM800L_UART_INSTANCE, (uint8_t *)"\x1A", 1, HAL_MAX_DELAY); // Ctrl+Z
	HAL_Delay(7000); // time for sending sms

	if (!strstr((char *)RxData, "OK")) {
		if (SIM800L_LCD_OUTPUT_ENABLED) {
			clear_buffs_flags();
			LCD5110_print("SMS Error", BLACK, &lcd1);
		}
		return;
	}

}

void what_manuf() {
	sim800l_send_command("AT+CGMI");
}

void what_model() {
	sim800l_send_command("AT+CGMM");
}

void what_rev() {
	sim800l_send_command("AT+CGMR");
}

void what_imei() {
	sim800l_send_command("AT+GSN");
}

void signal_rate() {
	clear_buffs_flags();
	sim800l_send_command("AT+CSQ");

	int rssi = -1;
	HAL_Delay(200);
	if (SIM800L_LCD_OUTPUT_ENABLED) {
		LCD5110_print((char *)RxData, BLACK, &lcd1);
	}
	sscanf((char *)RxData, "+CSQ: %d,", &rssi);

	// signal rates
	if (rssi > 0 && rssi <= 10) {
		// Bad signal
		printf("Bad signal\n");
		if (SIM800L_LCD_OUTPUT_ENABLED) {
			clear_buffs_flags();
			LCD5110_print("Bad error", BLACK, &lcd1);
		}
		HAL_GPIO_WritePin(SIM800L_LED1_PORT, SIM800L_LED1_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SIM800L_LED3_PORT, SIM800L_LED3_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SIM800L_LED2_PORT, SIM800L_LED2_PIN, GPIO_PIN_RESET);
	} else if (rssi >= 11 && rssi <= 20) {
		// Normal signal
		printf("Normal signal\n");
		if (SIM800L_LCD_OUTPUT_ENABLED) {
			clear_buffs_flags();
			LCD5110_print("Normal signal", BLACK, &lcd1);
		}
		HAL_GPIO_WritePin(SIM800L_LED1_PORT, SIM800L_LED1_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SIM800L_LED3_PORT, SIM800L_LED3_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SIM800L_LED2_PORT, SIM800L_LED2_PIN, GPIO_PIN_RESET);
	} else if (rssi >= 21 && rssi <= 31) {
		// Strong signal
		printf("Strong signal\n");
		if (SIM800L_LCD_OUTPUT_ENABLED) {
			clear_buffs_flags();
			LCD5110_print("Strong signal", BLACK, &lcd1);
		}
		HAL_GPIO_WritePin(SIM800L_LED1_PORT, SIM800L_LED1_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SIM800L_LED3_PORT, SIM800L_LED3_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SIM800L_LED2_PORT, SIM800L_LED2_PIN, GPIO_PIN_SET);
	} else {
		// No signal or Error
		printf("No signal or error\n");
		if (SIM800L_LCD_OUTPUT_ENABLED) {
			clear_buffs_flags();
			LCD5110_print("No signal or error", BLACK, &lcd1);
		}
		HAL_GPIO_WritePin(SIM800L_LED1_PORT, SIM800L_LED1_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SIM800L_LED3_PORT, SIM800L_LED3_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SIM800L_LED2_PORT, SIM800L_LED2_PIN, GPIO_PIN_RESET);
	}
}
void check_net_reg() {
	printf("Checking network registration...\n");
	sim800l_send_command("AT+CREG?");
}
void check_sim() {
	printf("Checking SIM card status...\n");
	sim800l_send_command("AT+CPIN?");
}

void get_baud_rate(){
	printf("Getting current baud rate...\n");
	sim800l_send_command("AT+IPR?");
}

void get_oper_mode() {
	printf("Getting current operational mode...\n");
	sim800l_send_command("AT+CFUN?");
}
void set_default() {
	printf("Resetting to default configuration...\n");
	sim800l_send_command("AT&F");
}

void curr_moper_info(){
	printf("Getting current mobile operator information...\n");
	sim800l_send_command("AT+COPS?");
}
void find_moper() {
	printf("Finding available mobile operators...\n");
	sim800l_send_command("AT+COPS=?");
}

void time_check() {
	printf("Checking time of sim800l...\n");
	sim800l_send_command("AT+CBAND?");
}

void power_rate() {
	printf("Checking power and charging status...\n");
	sim800l_send_command("AT+CBC");
}

void sms_set_text_mode() {
	printf("Setting SMS mode to text...\n");
    sim800l_send_command("AT+CMGF=1");
}

void sms_send(const char *phone_number, const char *message) {
	printf("Sending SMS...\n");
	clear_buffs_flags();
	char command[32];
	snprintf(command, sizeof(command), "AT+CMGS=\"%s\"", phone_number);
	sim800l_send_command(command);
	HAL_Delay(150);
	sim800l_send_text(message);
	HAL_Delay(150);
	sim800l_send_text("\x1A");  // termination symbols
	HAL_Delay(150);
}

void sms_check_all() {
	printf("Checking all SMS...\n");
	sim800l_send_command("AT+CMGL=\"ALL\"");
}

void make_call(const char *phone_number) {
	printf("Making call...\n");
	clear_buffs_flags();
	char command[32];
	snprintf(command, sizeof(command), "ATD%s;", phone_number);
	sim800l_send_command(command);
	HAL_Delay(1000);
}

void make_call_ext(const char *phone_number) {
	printf("Preparetion for making call...\n");
	clear_buffs_flags();

	sim800l_init(SIM800L_UART_INSTANCE);  //Check sim800l - uart - device connection
	HAL_Delay(200);
	sim800l_echo('0'); // turn off the mode echo of sim800l
	HAL_Delay(200);
	signal_rate();
	HAL_Delay(200);
	check_net_reg();
	HAL_Delay(200);
	check_sim();

	make_call(phone_number);
	LCD5110_print("Making call...", BLACK, &lcd1);
	HAL_GPIO_WritePin(SIM800L_LED4_PORT, SIM800L_LED4_PIN, GPIO_PIN_SET); // means calling process is activeted
	HAL_Delay(20000); // time for calling
	HAL_GPIO_WritePin(SIM800L_LED4_PORT, SIM800L_LED4_PIN, GPIO_PIN_RESET); // means calling process is finished
	LCD5110_print("Calling is finished", BLACK, &lcd1);
}

void sim800l_echo(const char mode) {
	if (mode == '0') {
		// Turn echo off
		sim800l_send_command("ATE0");
		printf("Echo is turned off\n");
		HAL_GPIO_WritePin(SIM800L_LED1_PORT, SIM800L_LED1_PIN, GPIO_PIN_RESET);
		if (SIM800L_LCD_OUTPUT_ENABLED) {
			LCD5110_print("Echo is turned off\n", BLACK, &lcd1);
		}
	} else if (mode == '1') {
		// Turn echo on
		sim800l_send_command("ATE1");
		printf("Echo is turned on\n");
		HAL_GPIO_WritePin(SIM800L_LED1_PORT, SIM800L_LED1_PIN, GPIO_PIN_RESET);
		if (SIM800L_LCD_OUTPUT_ENABLED) {
					LCD5110_print("Echo is turned on\n", BLACK, &lcd1);
				}
	} else {
		printf("Invalid mode. Set 1 or 0\n");
		HAL_GPIO_WritePin(SIM800L_LED1_PORT, SIM800L_LED1_PIN, GPIO_PIN_SET);
		if (SIM800L_LCD_OUTPUT_ENABLED) {
			LCD5110_print("Invalid mode. Set 1 or 0\n", BLACK, &lcd1);
		}
	}
}

void change_lcd_output(int enable) {
    if (enable == 1) {
    	printf("LCD output is enabled\n");
        SIM800L_LCD_OUTPUT_ENABLED = 1;
    } else {
    	printf("LCD output is disabled\n");
        SIM800L_LCD_OUTPUT_ENABLED = 0;
    }
}

void sim800l_set_led_pins(
    GPIO_TypeDef *led1_port, uint16_t led1_pin,
    GPIO_TypeDef *led2_port, uint16_t led2_pin,
    GPIO_TypeDef *led3_port, uint16_t led3_pin,
    GPIO_TypeDef *led4_port, uint16_t led4_pin
) {
    SIM800L_LED1_PORT = led1_port;
    SIM800L_LED1_PIN = led1_pin;

    SIM800L_LED2_PORT = led2_port;
    SIM800L_LED2_PIN = led2_pin;

    SIM800L_LED3_PORT = led3_port;
    SIM800L_LED3_PIN = led3_pin;

    SIM800L_LED4_PORT = led4_port;
    SIM800L_LED4_PIN = led4_pin;
}














