/**
  ***********************************************************************
  * @file    	Soft_UART.h                                             *
  * @created 	May 29, 2022                                            *
  * @brief   	This file contains all the function prototypes for      *
  *          	the Soft_UART.c file                                    *
  ***********************************************************************
*/

#ifndef __Soft_UART_H__
#define __Soft_UART_H__

/******************* Include Library ************************/
#include "main.h"
#include "string.h"
/****************** Define TIMER 3 *********************/
extern	TIM_HandleTypeDef htim3;
#define TIMER_COUNT					49
#define Timer_Frequency				72000000

/************* Define Parameter for UART  ************/
#define Number_Of_SoftUarts 			2
#define Soft_Uart_Tx_Buffer_Size		32
#define Soft_Uart_Rx_Buffer_Size		64

#define Soft_Uart_BAUD_RATE				9600
#define Soft_Uart_DATA_LEN				7
#define Soft_Uart_STOP_BIT				1
#define Soft_Uart_PARITY_BIT_MODE		0  // 0: None Parity, 1: Even Parity, 2: Odd Parity

#define Soft_Uart_PORT_TX_1				GPIOA
#define Soft_Uart_PIN_TX_1				GPIO_PIN_5

#define Soft_Uart_PORT_TX_2				GPIOA
#define Soft_Uart_PIN_TX_2				GPIO_PIN_4

#define SoftUart_DATA_LEN_C1 			(Soft_Uart_DATA_LEN + 1)
#define SoftUart_DATA_LEN_C2 			(Soft_Uart_DATA_LEN + 2)

/*
 * @brief State of UART
 */
typedef enum {
	SoftUart_OK,
	SoftUart_Error
}SoftUartState_E;

/*
 * @brief  RX and TX Buffer Size for UART
 */
typedef struct{
	uint8_t					Tx[Soft_Uart_Tx_Buffer_Size];
	uint8_t					Rx[Soft_Uart_Rx_Buffer_Size];
}SoftUartBuffer_S;

///*
// * @brief Set parity bit
// */
//typedef enum{
//	None_Prity_Bit,
//	Even_Parity_Bit,
//	Odd_Parity_Bit
//}SoftUartParityBit;

/*
 * @brief 	Parameter for UART: Pin, Port TX and RX, Data Buffer, ...
 */
typedef struct {
	__IO uint8_t			TxNComplated;
	uint8_t					TxEnable;
	uint8_t					TxBitShift, TxBitCounter;
	uint8_t					TxIndex, TxSize;
	SoftUartBuffer_S		*Buffer;
	GPIO_TypeDef			*TxPort;
	uint16_t				TxPin;
} SoftUart_S;

/************************ Define UART Function ***************************/
/*
 * @brief	Calculate Baudrate
 * @param	baudrate of UART
 * @return	Prescaler (PSC)
 * @note	In this project, Timer3 Frequency value is 72MHz and Timer Counter value is 49.
 * 			However, with baud = 11500, the transmitted data may not be correct
 * 			(if TIMER_COUNT = 50 and PSC = 11 then transmitted correct)
 */
uint16_t Soft_Uart_Set_Baudrate(uint16_t baudrate);

/*
 * @brief	Init Port, Pin, Count variable and Buffer for UART
 * @param	Soft UART Number
 * 			Ports to Transmit and Receive Data
 * 			Pins to Transmit and Receive Data
 * @return	State of UART (init OK or Error)
 */
SoftUartState_E		Soft_Uart_Init(uint8_t SoftUartNumber, GPIO_TypeDef *TxPort, uint16_t TxPin);

/*
 * @brief 	Handle UART.
 * @note	This function must call in interrupt every 1/Baudrate (second)
 */
void 				Soft_Uart_Handler(void);
//void				Soft_Uart_Handler_1(void);

/*
 * @brief 	Copy Data to Transmit Buffer and Start Sending
 * @param 	Soft UART Number
 * 			Data you want to transmit
 * 			Length of Data
 * @return	State of UART (OK or Error)
 */
SoftUartState_E 	Soft_Uart_Puts(uint8_t SoftUartNumber, char *str, uint8_t len);

/*
 * @brief 	Soft Uart Transmit Data Process
 * @param 	Soft UART
 * @note	this function is used in Soft_Uart_Handler
 */
void Soft_Uart_TX_Process (SoftUart_S *SU);

#endif /* __Soft_UART_H__ */
