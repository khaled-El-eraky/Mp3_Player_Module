/*
 * MP3_Module.c
 *
 * Created: 8/26/2020 7:18:09 PM
 *  Author: Khaled
 */ 

#include "Microcontroller_config.h"
#include <util/delay.h>
#include "MP3_Module.h"

#define MP3_CMD_SIZE	    (10)
#define MP3_STARTBYTE       (0x7E)
#define MP3_VERSION		    (0xFF)
#define Mp3_LENGTH          (0x06) 
#define Mp3_CMD             (0x00)
#define MP3_NO_FEEDBACK		(0x00)
#define MP3_RQT_FEEDBACK    (0x01)
#define Mp3_PARA_MSB        (0x00)
#define Mp3_PARA_LSB        (0x00)
#define Mp3_CHECK_MSB       (0x00)
#define Mp3_CHECK_LSB       (0x00)
#define MP3_ENDBYTE			(0xEF)

/* List of MP3 Commands */
#define Mp3_CMD_Next        (0x01)
#define Mp3_CMD_PREVIOUS    (0x02)
#define MP3_CMD_PlAYBACK	(0x03)
#define MP3_CMD_VOLUME_UP  	(0x04)
#define MP3_CMD_VOLUME_Down (0x05)
#define MP3_CMD_SETVOLUME	(0x06)
#define MP3_CMD_RESET       (0x0C)
#define MP3_CMD_PLAY		(0x0D)
#define MP3_CMD_PAUSE		(0x0E)


uint8_t Mp3_DefaultCommand[MP3_CMD_SIZE] = {MP3_STARTBYTE,MP3_VERSION,Mp3_LENGTH,Mp3_CMD,MP3_NO_FEEDBACK,Mp3_PARA_MSB,Mp3_PARA_LSB,Mp3_CHECK_MSB,Mp3_CHECK_LSB,MP3_ENDBYTE};

void SendCMDToMp3(void)
{
	unsigned char i =0;
	unsigned short CheckSum = 0;
	unsigned short Frame_Sum = 0;
	for(i=0 ; i<10 ; i++)
	{
		if ( i > 0 && i < 7 )
		{
			Frame_Sum  += Mp3_DefaultCommand[i];
		}
		else if ( i == 7)
		{
			CheckSum = (0xFFFF  -  Frame_Sum   + 1);
			
			Mp3_DefaultCommand[7] = CheckSum >> 8 ;
			Mp3_DefaultCommand[8] = (unsigned char)CheckSum;
		}
		UART_sendByte(Mp3_DefaultCommand[i]);
	}
}

void Mp3_Init(void)
{
	UART_init();
	Mp3_DefaultCommand[3] = MP3_CMD_RESET;
	SendCMDToMp3();
	/* return To Default Value */
	Mp3_DefaultCommand[3] = 0;
	/* Delay 1 Sec to make Sure Mp3 Module is working */
	_delay_ms(1000);
}

void Mp3_PlayTrack(unsigned short TrackNumber)
{
	Mp3_DefaultCommand[3] = MP3_CMD_PlAYBACK;
	Mp3_DefaultCommand[5] = TrackNumber >> 8;
	Mp3_DefaultCommand[6] = (unsigned char) TrackNumber;
	
	SendCMDToMp3();
	
	Mp3_DefaultCommand[3] = 0;
	Mp3_DefaultCommand[5] = 0;
	Mp3_DefaultCommand[6] = 0;
}

/* select specific volume level from 0 to 30 */
void Mp3_SelectVolume(unsigned short VolumeLevel)
{
	Mp3_DefaultCommand[3] = MP3_CMD_SETVOLUME;
	Mp3_DefaultCommand[5] = VolumeLevel >> 8;
	Mp3_DefaultCommand[6] = (unsigned char) VolumeLevel;
	
	SendCMDToMp3();
	
	Mp3_DefaultCommand[3] = 0;
	Mp3_DefaultCommand[5] = 0;
	Mp3_DefaultCommand[6] = 0;
}

void Mp3_Volume_Up()
{
	Mp3_DefaultCommand[3] = MP3_CMD_VOLUME_UP;
	
	SendCMDToMp3();
	
	Mp3_DefaultCommand[3] = 0;
}

void Mp3_Volume_Down()
{
	Mp3_DefaultCommand[3] = MP3_CMD_VOLUME_Down;
	
	SendCMDToMp3();
	
	Mp3_DefaultCommand[3] = 0;
}

void Mp3_Pause()
{
	Mp3_DefaultCommand[3] = MP3_CMD_PAUSE;
	
	SendCMDToMp3();
	
	Mp3_DefaultCommand[3] = 0;
}

void Mp3_Play()
{
	Mp3_DefaultCommand[3] = MP3_CMD_PLAY;
	
	SendCMDToMp3();
	
	Mp3_DefaultCommand[3] = 0;
}

void Mp3_Next_track(void)
{
	Mp3_DefaultCommand[3] = Mp3_CMD_Next;
	
	SendCMDToMp3();
	
	Mp3_DefaultCommand[3] = 0;
	
	
void Mp3_Previous_track(void)
{
	Mp3_DefaultCommand[3] = Mp3_CMD_PREVIOUS;
	
	SendCMDToMp3();
	
	Mp3_DefaultCommand[3] = 0;
}
}