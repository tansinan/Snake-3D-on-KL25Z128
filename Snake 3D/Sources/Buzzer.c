/*
 * Buzzer.c
 *
 *  Created on: Jun 14, 2015
 *      Author: tansinan
 */

#include "derivative.h"
#include "Types.h"
#include "Buzzer.h"


void Buzzer_init()
{
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);
	SIM_SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK;
	
	PORTB_PCR18 = 0x0300;
	
	TPM2_CNT = 0;
	TPM2_MOD = 0x00;
	TPM2_SC = (0x0008 | 0x0007);
	TPM2_C0SC = (0x0020 | 0x0008);
	TPM2_C0V = 0x00;
}

void Buzzer_set(uint32 frequency, uint8 volume)
{
	if(frequency == 0|| volume == 0)
	{
		TPM2_C0V = 0x00;
		return;
	}
	TPM2_CNT = 0;
	TPM2_MOD = 163828 / frequency;
	TPM2_C0V = 163828 / 2 / frequency;
}
