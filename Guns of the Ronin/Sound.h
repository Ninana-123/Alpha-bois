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

/*Audio Groups*/
extern AEAudioGroup mainmenuAudioGroup;
extern AEAudioGroup mainsceneAudioGroup;
extern AEAudioGroup guideAudioGroup;
extern AEAudioGroup playerAudioGroup;
extern AEAudioGroup buttonsAudioGroup;

extern bool audioPlayed;

void AudioLoad();


#endif