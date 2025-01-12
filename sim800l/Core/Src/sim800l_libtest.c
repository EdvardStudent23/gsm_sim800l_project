///*
// * sim800l_libtest.c
// *
// *  Created on: Jan 8, 2025
// *      Author: user
// */
//
//
/////*
//// * sim800l_lib.c
//// *
//// *  Created on: Jan 7, 2025
//// *      Author: user
//// */
////
////
////// У мене захардкоджені юарт2 та буфери в командах.
//////Буфери треба очищати. ======================================================
////
////
////#include "sim800l_lib.h"
////#include "stm32f3xx_hal.h"
////#include "usart.h"
////#include <string.h>
////#include <stdint.h>
////#include <stdio.h>
////// статична об'єкт конфігур.
////static uint8_t TxData[64];
////static uint8_t RxData[64];
////UART_HandleTypeDef *huart;
////
//////typedef struct {
//////	UART_HandleTypeDef *huart;
//////	uint8_t *TxData;
//////	uint8_t *RxData;
//////	size_t sizeBuffer;
//////} config;
//////
//////static config param;
////
////// an initialization of sim800l. If
//////void sim800l_init() {
//////	memset(TxData, 0, sizeof(TxData));
//////	memset(RxData, 0, sizeof(RxData));
//////
//////	send_ATcommand("AT\n\r");
//////	HAL_Delay(100);
//////	receive_ATcommand();
//////
//////	if (strstr((char *) RxData, "OK"))
//////		  {   // засвітився зелений світлодіод - sim800l відповідає
//////			  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
//////			  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);
//////		  }
//////		  else
//////		  {	  // засвітився червоний світлодіод - sim800l не відповідає
//////			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
//////			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
//////		  }
//////	 memset(RxData, 0, sizeof(RxData));
//////	 HAL_Delay(1000);
//////}
//////
//////void send_ATcommand (char *command) {
//////	// може зробити так, щоб до кожної команди додавалося \n\r, замість того, щоб усе це вписувати вручну
//////	strcpy((char *) TxData, command);          // може це змінити в одну
//////	HAL_UART_Transmit(&huart2, TxData, strlen((char *)TxData), 300); // може тут менший ділей зробити?
//////
//////}
//////
//////void receive_ATcommand() {
//////	HAL_UART_Receive(&huart2, RxData, sizeof(RxData), 800);
//////}
//////
////
////
////void sim800l_init() {
////    memset(TxData, 0, sizeof(TxData));
////    memset(RxData, 0, sizeof(RxData));
////
////    send_ATcommand(&huart2, "AT\r\n");
////    HAL_Delay(2000);  // Delay for response
////    receive_ATcommand(&huart2);
////
////    if (strstr((char *)RxData, "OK")) {
////        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET); // Green LED ON
////        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);  // Red LED OFF
////    } else {
////        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);   // Green LED OFF
////        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET); // Red LED ON
////    }
////
//////    memset(RxData, 0, sizeof(RxData)); // Clear buffer
////}
////
////void send_ATcommand(UART_HandleTypeDef *huart, char *command) {
////    snprintf((char *)TxData, sizeof(TxData), command); // Add \n\r automatically
////    HAL_UART_Transmit(huart, TxData, strlen((char *)TxData), 1000); // Increased timeout
////}
////
////void receive_ATcommand(UART_HandleTypeDef *huart) {
////    memset(RxData, 0, sizeof(RxData)); // Clear buffer before receiving
////    HAL_UART_Receive(huart, RxData, sizeof(RxData), 1000); // Increased timeout
////}
////
//
//
///*
// * sim800l_lib.c
// *
// *  Created on: Jan 7, 2025
// *      Author: user
// */
//
//#include "sim800l_lib.h"
//#include "stm32f3xx_hal.h"
//#include "usart.h"
//#include <string.h>
//#include <stdint.h>
//#include <stdio.h>
//
//// Буфери та змінні для переривань
//static uint8_t TxData[64];
//static uint8_t RxData[64];
//static uint8_t rx_index = 0;
//static uint8_t rx_byte = 0; // Тимчасовий буфер для 1 байту
//static volatile uint8_t data_ready = 0; // Прапорець готовності даних
//UART_HandleTypeDef *huart;
//
//void sim800l_init(UART_HandleTypeDef *uart_handle) {
//    memset(TxData, 0, sizeof(TxData));
//    memset(RxData, 0, sizeof(RxData));
//    rx_index = 0;
//    data_ready = 0;
//
//    // Запуск прийому в режимі переривань
//    HAL_UART_Receive_IT(&huart2, &rx_byte, 1);
//
//    // Надсилаємо тестову команду AT
//    sim800l_send_command("AT\r\n");
//    HAL_Delay(500); // Очікуємо відповіді
//
//    // Перевіряємо відповідь
//    if (data_ready && strstr((char *)RxData, "OK")) {
//        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET); // Зелений LED ON
//        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);  // Червоний LED OFF
//    } else {
//        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);   // Зелений LED OFF
//        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET); // Червоний LED ON
//    }
//
//    memset(RxData, 0, sizeof(RxData)); // Очищаємо буфер
//}
//
//void sim800l_send_command(const char *command) {
//    snprintf((char *)TxData, sizeof(TxData), "%s", command); // Копіюємо команду у буфер
//    HAL_UART_Transmit(&huart2, TxData, strlen((char *)TxData), 1000); // Надсилаємо через UART
//}
//
//bool sim800l_receive_response(char *buffer, size_t size, uint32_t timeout) {
//    uint32_t start_tick = HAL_GetTick();
//    while (!data_ready) {
//        if ((HAL_GetTick() - start_tick) > timeout) {
//            return 0; // Таймаут
//        }
//    }
//
//    // Копіюємо дані у вказаний буфер
//    strncpy(buffer, (char *)RxData, size);
//    buffer[size - 1] = '\0'; // Гарантуємо, що рядок закінчується '\0'
//
//    // Скидаємо прапорець і очищаємо буфер
//    data_ready = 0;
//    memset(RxData, 0, sizeof(RxData));
//    rx_index = 0;
//
//    return 1; // Успіх
//}
//
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
//    if (huart->Instance == USART2) { // Перевірка, що переривання з потрібного UART
//        if (rx_index < sizeof(RxData) - 1) {
//            RxData[rx_index++] = rx_byte; // Додаємо отриманий байт у буфер
//            if (rx_byte == '\n') { // Закінчення рядка
//                RxData[rx_index] = '\0'; // Завершуємо рядок
//                data_ready = 1; // Дані готові
//            }
//        } else {
//            rx_index = 0; // Переповнення буфера, скидаємо індекс
//        }
//
//        // Запускаємо прийом наступного байту
//        HAL_UART_Receive_IT(huart, &rx_byte, 1);
//    }
//}
