/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file void.cpp
@author Teo Sheen Yeoh
@Email t.sheenyeoh@digipen.edu
@course CSD 1450
@section Section A
@date 3 March 2023
@brief This file contains code for the credit screen.
*//*______________________________________________________________________*/
#pragma once
#ifndef SOUND_H
#define SOUND_H

#include "MainMenu.h"
/*Main Menu audo*/
extern AEAudio mainmenuSong;
extern AEAudio buttonHoverSound;
extern AEAudio buttonClickSound;

/*Main level audio*/
extern AEAudio mainsceneSong;

/*PLayer Audio*/
extern AEAudio playerWalkSound;
extern AEAudio playerShootSound;

//Shrines
extern AEAudio freezeSound;
extern AEAudio explosionSound;
extern AEAudio healthSound;
extern AEAudio godSound;
extern AEAudio windSound;
extern AEAudio voidSound;

//Enemies
extern AEAudio archerShoot;
extern AEAudio cannonShoot;
extern AEAudio samuraiSlash;
extern AEAudio ninjaThrow;


/*Guide Audio*/
extern AEAudio guideSong;

/*Credits Audio*/
extern AEAudio creditsSong;

/*Audio Groups*/
extern AEAudioGroup mainmenuAudioGroup;
extern AEAudioGroup mainsceneAudioGroup;
extern AEAudioGroup guideAudioGroup;
extern AEAudioGroup playerAudioGroup;
extern AEAudioGroup buttonsAudioGroup;
extern AEAudioGroup creditsAudioGroup;

extern bool audioPlayed;

void AudioLoad();


#endif