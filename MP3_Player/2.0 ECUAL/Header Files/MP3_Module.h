/*
 * MP3_Module.h
 *
 * Created: 8/26/2020 7:17:48 PM
 *  Author: Khaled
 */ 


#ifndef MP3_MODULE_H_
#define MP3_MODULE_H_


#include "UART.h"

void Mp3_Init(void);
void Mp3_PlayTrack(unsigned short TrackNumber);
void Mp3_SelectVolume(unsigned short VolumeLevel);
void Mp3_Volume_Up();
void Mp3_Volume_Down();
void Mp3_Pause(void);
void Mp3_Play(void);
void Mp3_Next_track(void);
void Mp3_Previous_track(void);



#endif /* MP3_MODULE_H_ */