/**
  ***********************************************************************
  * @file    	Soft_UART.h                                             *
  * @author 	BIG SIX (ET1_05 K63 HUST)                               *
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
#define Timer_Frequency					72000000

/******************* Define Parameter for UART  ************/
#define Number_Of_SoftUarts 			2
#define Soft_Uart_Tx_Buffer_Size		32
#define Soft_Uart_Rx_Buffer_Size		64

#define Soft_Uart_DATA_LEN				15
#define SoftUart_DATA_LEN_C1 			(Soft_Uart_DATA_LEN + 1)
#define SoftUart_DATA_LEN_C2 			(Soft_Uart_DATA_LEN + 2)

/**
  * @brief State of UART
  */
typedef enum {
	SoftUart_OK,
	SoftUart_Error
}SoftUartState_E;

/**
  * @brief  RX and TX Buffer Size for UART
  */
typedef struct{
	uint8_t					Tx[Soft_Uart_Tx_Buffer_Size];
	uint8_t					Rx[Soft_Uart_Rx_Buffer_Size];
}SoftUartBuffer_S;

/**
  * @brief 	Parameter for UART: Pin, Port TX and RX, Data Buffer, ...
  */
typedef struct {
	__IO uint8_t			TxNComplated;
	uint8_t					TxEnable;
	uint8_t					RxEnable;
	uint8_t					TxBitShift, TxBitCounter;
	uint8_t					RxBitShift, RxBitCounter;
	uint8_t					TxIndex, TxSize;
	uint8_t					RxIndex;
	SoftUartBuffer_S		*Buffer;
	GPIO_TypeDef			*TxPort;
	uint16_t				TxPin;
	GPIO_TypeDef			*RxPort;
	uint16_t				RxPin;
	uint8_t					RxTimingFlag;
	uint8_t 				RxBitOffset;
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
SoftUartState_E		Soft_Uart_Init(uint8_t SoftUartNumber, GPIO_TypeDef *TxPort, uint16_t TxPin, GPIO_TypeDef *RxPort, uint16_t RxPin);

/*
 * @brief 	Handle UART.
 * @note	This function must call in interrupt every 1/Baudrate (second)
 *
 */
void 				Soft_Uart_Handler(void);

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
