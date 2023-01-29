/******************************************************************************
* Authors:    Michael Myer, David Olah                                        *
* Emails:     mmyer488@mtroyal.ca, dolah663@mtroyal.ca                        *
* Course:     COMP 2659                                                       *
* Instructor: Paul Pospisil                                                   *
* File Name:  psg.c                                                           *
******************************************************************************/

#include "psg.h"


/******************************************************************************
 *	Function: writePSG                                                        *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Loads the requested register of the sound generator with a given value*
 *                                                                            *
 *****************************************************************************/
void writePSG(int reg, UINT8 value)
{
	long old_ssp = Super(0);
	
	*PSG_reg_select = reg;
	*PSG_reg_write = value;
	
	Super(old_ssp);
	return;
}

/******************************************************************************
 *	Function: readPSG                                                         *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Reads the current value of the given register on the sound generator  *
 *                                                                            *
 *****************************************************************************/
UINT8 readPSG(int reg)
{
	UINT8 value;
	long old_ssp = Super(0);
	
	*PSG_reg_select = reg;
	value = *PSG_reg_select;
	
	Super(old_ssp);
	return value;
}

/******************************************************************************
 *	Function: setTone                                                         *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Changes the tone value for one of the sound generators 3 channels     *
 *                                                                            *
 *****************************************************************************/
void setTone(int channel, int tuning)
{
	int fine = tuning & 0xFF;
	int rough = tuning >> 8;
	switch (channel)
	{
		case CH_A:
			writePSG(A_TONE_FINE, fine);
			writePSG(A_TONE_ROUGH, rough);
			break;
		case CH_B:
			writePSG(B_TONE_FINE, fine);
			writePSG(B_TONE_ROUGH, rough);
			break;
		case CH_C:
			writePSG(C_TONE_FINE, fine);
			writePSG(C_TONE_ROUGH, rough);
			break;
	}
	
	return;
}

/******************************************************************************
 *	Function: setNoise                                                        *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Changes the noise setting of the sound generator                      *
 *                                                                            *
 *****************************************************************************/
void setNoise(int tuning)
{
	writePSG(NOISE_REG, tuning);
	
	return;
}

/******************************************************************************
 *	Function: enableChannel                                                   *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Enables/Disables a channel's tone, noise, or both                     *
 *                                                                            *
 *****************************************************************************/
void enableChannel(int channel, int toneOn, int noiseOn)
{
	int setting = 0x3F;
	
	
	switch (channel)
	{
		case CH_A:
			if(toneOn == 1)
				setting &= 0x3E;
			
			if(noiseOn == 1)
				setting &= 0x37;
			
			break;
		case CH_B:
			if(toneOn == 1)
				setting &= 0x3D;
			
			if(noiseOn == 1)
				setting &= 0x2F;
			
			break;
		case CH_C:
			if(toneOn == 1)
				setting &= 0x3B;
			
			if( noiseOn == 1)
				setting &= 0x1F;
			
			break;
	}
	
	setting &= readPSG(MIXER_REG);
	writePSG(MIXER_REG, setting);
	
	return;
}

/******************************************************************************
 *	Function: disableChannel                                                  *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Turns off a channel on the sound generator                            *
 *                                                                            *
 *****************************************************************************/
void disableChannel(int channel)
{
	int setting;
	
	setting = readPSG(MIXER_REG);
	
	switch (channel)
	{
		case CH_A:
			setting |= 0x9;
			break;
			
		case CH_B:
			setting |= 0x12;
			break;
			
		case CH_C:
			setting |= 0x24;
			break;
	}
	
	writePSG(MIXER_REG, setting);
	
	return;
}

/******************************************************************************
 *	Function: setVolume                                                       *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Changes the volume setting on one of the sound generators channels    *
 *                                                                            *
 *****************************************************************************/
void setVolume(int channel, int volume)
{
	switch (channel)
	{
		case CH_A:
			writePSG(A_VOLUME, volume);
			break;
		case CH_B:
			writePSG(B_VOLUME, volume);
			break;
		case CH_C:
			writePSG(C_VOLUME, volume);
			break;
	}
	
	return;
};

/******************************************************************************
 *	Function: setEnvelope                                                     *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Changes the settings on the sound generator's envelope                *
 *                                                                            *
 *****************************************************************************/
void setEnvelope(int shape, unsigned int sustain)
{
	writePSG(ENV_FINE, sustain);
	writePSG(ENV_COARSE, sustain);
	writePSG(ENV_SHAPE, shape);
	
	return;
}

/******************************************************************************
 *	Function: stopSound                                                       *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Disables every channel on the sound generator                         *
 *                                                                            *
 *****************************************************************************/
void stopSound()
{
	setVolume(CH_A, 0);
	setVolume(CH_B, 0);
	setVolume(CH_C, 0);
	enableChannel(CH_A, 0, 0);
	enableChannel(CH_B, 0, 0);
	enableChannel(CH_C, 0, 0);
	
	return;
}
