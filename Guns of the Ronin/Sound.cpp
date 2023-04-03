/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file		Sound.cpp
@author		Kai Alexander Van Adrichem Boogaert
@Email		kaialexander.v@digipen.edu
@course		CSD 1451
@section	Section A
@date		3 March 2023
@brief		This file contains the loaded variables for audio to be used in other files
*//*______________________________________________________________________*/
#include "MainMenu.h"
/*Main Menu audo*/
AEAudio mainmenuSong;
AEAudio buttonHoverSound;
AEAudio buttonClickSound;

/*Main level audio*/
AEAudio mainsceneSong;

/*PLayer Audio*/
AEAudio playerShootSound;

//Shrines
AEAudio freezeSound;
AEAudio explosionSound;
AEAudio healthSound;
AEAudio godSound;
AEAudio windSound;
AEAudio voidSound;

//Enemies
AEAudio archerShoot;
AEAudio cannonShoot;
AEAudio samuraiSlash;
AEAudio ninjaThrow;
AEAudio ninjaVanish;


/*Guide Audio*/
AEAudio guideSong;

/*Credits Audio*/
AEAudio creditsSong;


/*Audio Groups*/
AEAudioGroup mainmenuAudioGroup;
AEAudioGroup mainsceneAudioGroup;
AEAudioGroup guideAudioGroup;
AEAudioGroup playerAudioGroup;
AEAudioGroup creditsAudioGroup;


AEAudioGroup buttonsAudioGroup;

bool audioPlayed = false;

void Audio_Load() {
	/*MainMenu*/
	mainmenuAudioGroup = AEAudioCreateGroup();
	mainmenuSong = AEAudioLoadMusic("Assets/Audio/mainmenu_song.wav");
	/*Buttons*/
	buttonsAudioGroup = AEAudioCreateGroup();
	buttonHoverSound = AEAudioLoadSound("Assets/Audio/button_hover.wav");
	buttonClickSound = AEAudioLoadSound("Assets/Audio/button_click.wav");
	/*Player*/
	playerAudioGroup = AEAudioCreateGroup();
	playerShootSound = AEAudioLoadSound("Assets/Audio/player_shoot.wav");

	/*Guide*/
	guideAudioGroup = AEAudioCreateGroup();
	guideSong = AEAudioLoadMusic("Assets/Audio/guide_song.wav");

	/*Credits*/
	creditsAudioGroup = AEAudioCreateGroup();
	creditsSong = AEAudioLoadMusic("Assets/Audio/credits_song.wav");

	/*Main Scene Audio*/
	mainsceneAudioGroup = AEAudioCreateGroup();
	//Shrines
	freezeSound = AEAudioLoadSound("Assets/Audio/freeze_shrine.wav");
	explosionSound = AEAudioLoadSound("Assets/Audio/explosion.wav");
	healthSound = AEAudioLoadSound("Assets/Audio/health_shrine.wav");
	godSound = AEAudioLoadSound("Assets/Audio/god_shrine.wav");
	windSound = AEAudioLoadSound("Assets/Audio/wind_shrine.wav");
	voidSound = AEAudioLoadSound("Assets/Audio/void_shrine.wav");

	//Enemies
	archerShoot = AEAudioLoadSound("Assets/Audio/archer_shoot.wav");
	cannonShoot = AEAudioLoadSound("Assets/Audio/cannon_shot.wav");
	samuraiSlash = AEAudioLoadSound("Assets/Audio/samurai_slash.wav");
	ninjaThrow = AEAudioLoadSound("Assets/Audio/ninja_throw.wav");
	ninjaVanish = AEAudioLoadSound("Assets/Audio/ninja_vanish.wav");
	
}