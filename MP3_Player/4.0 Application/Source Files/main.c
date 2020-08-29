/*
 * MP3_Player.c
 *
 * Created: 8/25/2020 5:57:29 PM
 *  Author: Khaled
 */ 
#include "Microcontroller_config.h"
#include <util/delay.h>
#include "MP3_Module.h"

int main(void)
{
	Mp3_Init();
	Mp3_SelectVolume(30);
	Mp3_PlayTrack(3);
	_delay_ms(5000);
	Mp3_Pause();
	_delay_ms(3000);
	Mp3_Play();
	_delay_ms(5000);
	Mp3_Next_track();
	_delay_ms(5000);
	Mp3_Next_track();
	Mp3_SelectVolume(15);
	_delay_ms(15000);
	
	
    while(1)
    {
      
    }
}