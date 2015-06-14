#include "Music.h"
#include "derivative.h"

void Music_init()
{
	
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);
	SIM_SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK;
	//≈‰÷√PORTB
	PORTB_PCR18 = 0x300;
	
	//≥ı ºªØPWMƒ£øÈ
	TPM2_CNT = 0;
	TPM2_MOD = 0x00;
	TPM2_SC = 0x0F;
	TPM2_C0SC = 0x28;
	TPM2_C0V = 0x00;
}

void Music_handler();
void Music_playFrequency(unsigned int frequency)
{
	TPM2_MOD = 164000 / frequency;
	TPM2_C0V = 164000 / frequency / 2;
}
