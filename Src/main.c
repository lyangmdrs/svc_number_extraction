/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
    printf("Extracting SVC number\n");

    __asm("SVC #42"); 	// Calls a SVC exception.

    uint8_t retrieved_SVC_number;

    __asm("MOV %0, R0": "=r"(retrieved_SVC_number) ::);

    printf("Retrieved SVC number: %d\n", retrieved_SVC_number);

	/* Loop forever */
	for(;;);
}

__attribute__ ((naked)) void SVC_Handler(void)
{
	/*
	 * ((naked)) functions does not have Prologue neither Epilogue sequences, so
	 * it will not corrupt the value of R0.
	 */

	__asm("MRS R0, MSP");		// Move the content of a special register to a GP register.
	__asm("B SVC_Handler_C");	// Branch to C implemented handler.

}

void SVC_Handler_C(uint32_t *pBaseOfStackFrame)
{
	printf("In SVC Handler!\n");

	uint8_t *pReturn_addr = (uint8_t*)pBaseOfStackFrame[6];	// Move from R0 address to PC.
	pReturn_addr-=2; 										// Extract the OPcode.
	pBaseOfStackFrame[0] = *pReturn_addr;					// Return the OPcode in R0.
}
