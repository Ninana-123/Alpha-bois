#include "MainMenu.h"
/*Main Menu audo*/
AEAudio mainmenuSong;
AEAudio buttonHoverSound;
AEAudio buttonClickSound;

/*Main level audio*/
AEAudio mainsceneSong;

/*PLayer Audio*/
AEAudio playerWalkSound;
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


/*Guide Audio*/
AEAudio guideSong;

/*Audio Groups*/
AEAudioGroup mainmenuAudioGroup;
AEAudioGroup mainsceneAudioGroup;
AEAudioGroup guideAudioGroup;
AEAudioGroup playerAudioGroup;

AEAudioGroup buttonsAudioGroup;

bool audioPlayed = false;

void AudioLoad() {
	/*MainMenu*/
	mainmenuAudioGroup = AEAudioCreateGroup();
	mainmenuSong = AEAudioLoadMusic("Assets/Audio/mainmenu_song.wav");
	/*Buttons*/
	buttonsAudioGroup = AEAudioCreateGroup();
	buttonHoverSound = AEAudioLoadSound("Assets/Audio/button_hover.wav");
	buttonClickSound = AEAudioLoadSound("Assets/Audio/button_click.wav");
	/*Player*/
	playerAudioGroup = AEAudioCreateGroup();
	playerWalkSound = AEAudioLoadSound("Assets/Audio/player_walk.wav");
	playerShootSound = AEAudioLoadSound("Assets/Audio/player_shoot.wav");

	/*Guide*/
	guideAudioGroup = AEAudioCreateGroup();
	guideSong = AEAudioLoadMusic("Assets/Audio/guide_song.wav");

	mainsceneAudioGroup = AEAudioCreateGroup();
	//Shrines
	freezeSound = AEAudioLoadMusic("Assets/Audio/freeze_shrine.wav");
	explosionSound = AEAudioLoadMusic("Assets/Audio/explosion.wav");
	healthSound = AEAudioLoadMusic("Assets/Audio/health_shrine.wav");
	godSound = AEAudioLoadMusic("Assets/Audio/god_shrine.wav");
	windSound = AEAudioLoadMusic("Assets/Audio/wind_shrine.wav");
	voidSound = AEAudioLoadMusic("Assets/Audio/void_shrine.wav");
}