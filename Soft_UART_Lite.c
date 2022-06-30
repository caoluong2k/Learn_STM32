/**
 * ******************************************************************************
 * @file 		Soft_UART.c
 * @auhtor		BIG SIX
 * @created		May 29, 2022
 * @brief		Soft UART Library for STM32F103C8T6
 * 				This file provides code for the configuration of the UART instances
 * *******************************************************************************
 */

/* Include Library */
#include "Soft_UART_Lite.h"

/* All Soft Uart Config and State */
SoftUart_S				SUart[Number_Of_SoftUarts];

/* TX RX Data Buffer */
SoftUartBuffer_S 		SUartBuffer[Number_Of_SoftUarts];

/* Read RX single Pin Value */
GPIO_PinState Soft_Uart_GPIO_Read_Pin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	return HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
}

/* Calculate Baudrate */

uint16_t Soft_Uart_Set_Baudrate(uint16_t baudrate){
	uint16_t PSC_Value;
	if (baudrate == 115200) {
		return PSC_Value = 11;
	}
	else {
		PSC_Value = (Timer_Frequency/(baudrate*(TIMER_COUNT))) - 1;
		return PSC_Value;
	}
}
/* Init Soft UART */
SoftUartState_E Soft_Uart_Init(uint8_t SoftUartNumber, GPIO_TypeDef *TxPort, uint16_t TxPin, GPIO_TypeDef *RxPort, uint16_t RxPin){
	if (SoftUartNumber >= Number_Of_SoftUarts) {
		return SoftUart_Error;
	}

	SUart[SoftUartNumber].TxNComplated = 0;

	SUart[SoftUartNumber].RxBitCounter = 0;
	SUart[SoftUartNumber].RxBitShift = 0;
	SUart[SoftUartNumber].RxIndex = 0;

	SUart[SoftUartNumber].TxEnable = 0;
	SUart[SoftUartNumber].RxEnable = 0;

	SUart[SoftUartNumber].TxBitCounter = 0;
	SUart[SoftUartNumber].TxBitShift = 0;
	SUart[SoftUartNumber].TxIndex = 0;

	SUart[SoftUartNumber].TxSize = 0;

	SUart[SoftUartNumber].Buffer = &SUartBuffer[SoftUartNumber];

	SUart[SoftUartNumber].RxPort = RxPort;
	SUart[SoftUartNumber].RxPin = RxPin;

	SUart[SoftUartNumber].TxPort = TxPort;
	SUart[SoftUartNumber].TxPin = TxPin;

	SUart[SoftUartNumber].RxTimingFlag = 0;
	SUart[SoftUartNumber].RxBitOffset = 0;

	return SoftUart_OK;
}

/* Write TX single Pin Value */
void Soft_Uart_GPIO_Write_Pin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState){
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, PinState);
}

/* Send one bit to TX pin */
void Soft_Uart_Transmit_Bit(SoftUart_S *SU, uint8_t Bit0_1){
	Soft_Uart_GPIO_Write_Pin(SU->TxPort, SU->TxPin, (GPIO_PinState)Bit0_1);
}

/* Soft Uart Transmit Data Process */
void Soft_Uart_TX_Process(SoftUart_S *SU){
	if (SU->TxEnable) {
		// Start Bit
		if (SU->TxBitCounter == 0) {
			SU->TxNComplated = 1;
			SU->TxBitShift = 0;
			Soft_Uart_Transmit_Bit(SU, 0);
			SU->TxBitCounter++;
		}

		// Data
		else if (SU->TxBitCounter < SoftUart_DATA_LEN_C1) {
			if ((((SU->Buffer->Tx[SU->TxIndex]) >> (SU->TxBitShift)) & 0x01) == 0x1) {
				Soft_Uart_Transmit_Bit(SU, 1);
			}
			else {
				Soft_Uart_Transmit_Bit(SU, 0);
			}
			//Soft_Uart_Transmit_Bit(SU, ((SU->Buffer->Tx[SU->TxIndex]) >> (SU->TxBitShift)) & 0x01);
			SU->TxBitCounter++;
			SU->TxBitShift++;
		}

		// Stop Bit
		else if (SU->TxBitCounter == SoftUart_DATA_LEN_C1) {
			Soft_Uart_Transmit_Bit(SUart, 1);
			SU->TxBitCounter++;
		}

		// Complete
		else if (SU->TxBitCounter == SoftUart_DATA_LEN_C2) {
			// Reset Bit counter
			SU->TxBitCounter = 0;

			// ready to send another data
			SU->TxIndex++;

			// Check Size of Data
			if (SU->TxSize > SU->TxIndex) {
				// Continue Sending Data
				SU->TxNComplated = 1;
				SU->TxEnable = 1;
			}else {
				//Finish
				SU->TxNComplated = 0;
				SU->TxEnable = 0;
			}
		}
	}
}

/* Copy Data to Transmit Buffer and Start Sending */
SoftUartState_E Soft_Uart_Puts(uint8_t SoftUartNumber, char *Str, uint8_t len){
	int i;
	if (SoftUartNumber >= Number_Of_SoftUarts) {
		return SoftUart_Error;
	}

	if (SUart[SoftUartNumber].TxNComplated) {
		return SoftUart_Error;
	}

	SUart[SoftUartNumber].TxIndex = 0;
	SUart[SoftUartNumber].TxSize = len;

	for (i = 0; i < len; i++) {
		SUart[SoftUartNumber].Buffer->Tx[i] = Str[i];
	}

	SUart[SoftUartNumber].TxNComplated = 1;
	SUart[SoftUartNumber].TxEnable = 1;
	return SoftUart_OK;
}

/* Handle UART */
void Soft_Uart_Handler(void){
	int i;

	// Sending always happens in the first time slot
	for (i = 0; i < Number_Of_SoftUarts; i++) {
		if (SUart[i].TxEnable) {
			Soft_Uart_TX_Process(&SUart[i]);
		}
	}

//	// Receive data
//	for (i = 0; i < Number_Of_SoftUarts; i++) {
//		if (SUart[i].RxTimingFlag) {
//			Soft_Uart_RX_Data_Bit_Process(SUart[i], Soft_Uart_GPIO_Read_Pin(SUart[i].RxPort, SUart[i].RxPin));
//		}
//	}
}

// Soft Uart Receive Data Process
//void Soft_Uart_RX_Data_Bit_Process(SoftUart_S *SU, uint8_t B0_1){
//	if (SU->RxEnable) {
//		//Start
//		if (SU->RxBitCounter == 0) {
//			//Start Bit is 0
//			if(B0_1) return; // Nếu B0_1 = 1 thì dừng thực thi hàm
//
//			SU->RxBitShift = 0;
//			SU->RxBitCounter++;
//			SU->Buffer->Rx[SU->RxIndex] = 0;
//		}
//
//		// Data
//		else if ((SU->RxBitCounter) < SoftUart_DATA_LEN_C1) {
//			SU->Buffer->Rx[SU->RxIndex] |= ((B0_1&0x01)<<SU->RxBitShift);
//			SU->RxBitCounter++;
//			SU->RxBitShift++;
//		}
//
//		// Stop and Complete
//		else if (SU->RxBitCounter == SoftUart_DATA_LEN_C2) {
//			SU->RxBitCounter = 0;
//			SU->RxTimingFlag = 0;
//
//			//Stop bit must be 1
//			if (B0_1) {
//				// Receied successfully
//				// Change RX Buffer Index
//				if ((SU->RxIndex) < (Soft_Uart_Rx_Buffer_Size - 1)) {
//					SU->RxIndex++;
//				}
//				// if not: ERROR -> Overwrite data
//			}
//		}
//	}
//}







