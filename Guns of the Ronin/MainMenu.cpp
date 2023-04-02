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
#include "MainMenu.h"
#include "HighScore.h"

AEGfxTexture* MainMenuBG;

AEGfxTexture* buttonsSprite;

AEGfxTexture* splashScreenTexture;

s32 MousePosX;
s32 MousePosY;

s32* MouseX = &MousePosX;
s32* MouseY = &MousePosY;

float BGScaleX = 1600.0f;
float BGScaleY = 900.0f;

float buttonScaleX = 250.0f;
float buttonScaleY = -125.0f;

float buttonsY = -151.0f;

float playButtonX = -81.0f;
float guideButtonX = playButtonX + buttonScaleX;
float highscoreButtonX = guideButtonX + buttonScaleX;
float quitButtonX = highscoreButtonX + buttonScaleX;

float creditsButtonX = quitButtonX;
float creditsButtonY = buttonsY - 220.f;

bool left_mouse_pressed;

MainMenu mainMenu;
MainMenu playButton;
MainMenu guideButton;
MainMenu highscoreButton;
MainMenu quitButton;
MainMenu creditButton;
MainMenu splashScreen;


s8 font;

void Init_Menu() {
	
	// Changing the window title
	AESysSetWindowTitle("Guns of the Ronin");
	// reset the system modules
	AESysReset();
	MainMenuBG = AEGfxTextureLoad("Assets/MainMenu.png");
	buttonsSprite = AEGfxTextureLoad("Assets/buttonspritesheet.png");
	splashScreenTexture = AEGfxTextureLoad("Assets/DigiPen_BLACK_rights.png");
	
	//CreateSpriteMesh(&mainMenu.transform, BGMesh);
	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), splashScreenMesh, 1.0f, 1.0f);
	splashScreen.transform.texture = &splashScreenTexture;
	splashScreen.transform.position = { 0.0f,0.0f };
	splashScreen.transform.scale = { BGScaleX,-BGScaleY };
	splashScreen.transform.height = 1.0f;
	splashScreen.transform.width = 1.0f;
	splashScreen.transform.rotation = 0.0f;
	splashScreen.spriteIndex = 0;
	splashScreen.transform.mesh = &splashScreenMesh;
	
	//CreateSpriteMesh(&mainMenu.transform, BGMesh);
	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), BGMesh, 1.0f/4.0f, 1.0f);
	mainMenu.transform.texture = &MainMenuBG;
	mainMenu.transform.position = { 0.0f,0.0f };
	mainMenu.transform.scale = { BGScaleX,-BGScaleY };
	mainMenu.transform.height = 1.0f;
	mainMenu.transform.width = 4.0f;
	mainMenu.transform.rotation = 0.0f;
	mainMenu.spriteIndex = 0;
	mainMenu.transform.mesh = &BGMesh;

	//CreateSpriteMesh(&playButton.transform, playMesh);
	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), playMesh, 1.0f / 10.0f, 1.0f);
	playButton.transform.texture = &buttonsSprite;
	playButton.transform.position = { playButtonX,buttonsY };
	playButton.transform.scale = { buttonScaleX,buttonScaleY };
	playButton.transform.height = 1.0f;
	playButton.transform.width = 10.0f;
	playButton.transform.rotation = 0.0f;
	playButton.transform.mesh = &playMesh;

	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), guideMesh, 1.0f / 10.0f, 1.0f);
	guideButton.transform.texture = &buttonsSprite;
	guideButton.transform.position = { guideButtonX,buttonsY };
	guideButton.transform.scale = { buttonScaleX,buttonScaleY };
	guideButton.transform.height = 1.0f;
	guideButton.transform.width = 10.0f;
	guideButton.transform.rotation = 0.0f;
	guideButton.transform.mesh = &guideMesh;
	
	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), highscoreMesh, 1.0f / 10.0f, 1.0f);
	highscoreButton.transform.texture = &buttonsSprite;
	highscoreButton.transform.position = { highscoreButtonX,buttonsY };
	highscoreButton.transform.scale = { buttonScaleX,buttonScaleY };
	highscoreButton.transform.height = 1.0f;
	highscoreButton.transform.width = 10.0f;
	highscoreButton.transform.rotation = 0.0f;
	highscoreButton.transform.mesh = &highscoreMesh;
	
	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), quitMesh, 1.0f / 10.0f, 1.0f);
	quitButton.transform.texture = &buttonsSprite;
	quitButton.transform.position = { quitButtonX,buttonsY };
	quitButton.transform.scale = { buttonScaleX,buttonScaleY };
	quitButton.transform.height = 1.0f;
	quitButton.transform.width = 10.0f;
	quitButton.transform.rotation = 0.0f;
	quitButton.transform.mesh = &quitMesh;
	
	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), creditMesh, 1.0f / 10.0f, 1.0f);
	creditButton.transform.texture = &buttonsSprite;
	creditButton.transform.position = { creditsButtonX,creditsButtonY};
	creditButton.transform.scale = { buttonScaleX /2,buttonScaleY / 2};
	creditButton.transform.height = 1.0f;
	creditButton.transform.width = 10.0f;
	creditButton.transform.rotation = 0.0f;
	creditButton.transform.mesh = &quitMesh;


	AEAudioPlay(mainmenuSong,mainmenuAudioGroup, 1.f, 1.f, -1);

}

void Update_Menu() {
	AEAudioResumeGroup(mainmenuAudioGroup);
	static float frameTimer = 0.f;
	static float splasScreenTimer = 0.f;
	splasScreenTimer += deltaTime;
	frameTimer += deltaTime;

	Update_Time();
	AEInputGetCursorPosition(MouseX, MouseY);
	*MouseX = *MouseX - 800;
	*MouseY = (*MouseY - 450) * -1;
	left_mouse_pressed = AEInputCheckReleased(AEVK_LBUTTON);

	if (splasScreenTimer >= 2.f) {
		splashScreen.transform.scale = { 0.f,0.f};
	}

	if (frameTimer >= 0.3f) {
		mainMenu.bgAnim.PlayAnim();
		mainMenu.bgAnim.NextFrame(mainMenu.transform);
		mainMenu.bgAnim.Update_SpriteAnim(mainMenu.transform);
		frameTimer = 0;
	}

	if (IsButtonHover(playButtonX, buttonsY, buttonScaleX, buttonScaleY, MouseX, MouseY)) {
		playButton.spriteIndex = 1;
		if (!audioPlayed) {
			AEAudioPlay(buttonHoverSound, buttonsAudioGroup, 1.f, 1.f, 0);
			audioPlayed = true;
		}
		if (left_mouse_pressed) {
			AEAudioPlay(buttonClickSound, buttonsAudioGroup, 1.f, 1.f, 0);
			AEAudioPauseGroup(mainmenuAudioGroup);
			gGameStateNext = GS_LEVEL1;
		}
	}
	else playButton.spriteIndex = 0;

	if (IsButtonHover(guideButtonX,buttonsY,buttonScaleX,buttonScaleY,MouseX,MouseY)) {
		guideButton.spriteIndex = 5;
		if (!audioPlayed) {
			AEAudioPlay(buttonHoverSound, buttonsAudioGroup, 1.f, 1.f, 0);
			audioPlayed = true;
		}
		if (left_mouse_pressed) {
			AEAudioPlay(buttonClickSound, buttonsAudioGroup, 1.f, 1.f, 0);
			AEAudioPauseGroup(mainmenuAudioGroup);
			gGameStateNext = GS_GUIDE;
		}
	}
	else guideButton.spriteIndex = 4;

	if (IsButtonHover(highscoreButtonX, buttonsY, buttonScaleX, buttonScaleY, MouseX, MouseY)) {
		highscoreButton.spriteIndex = 9;
		if (!audioPlayed) {
			AEAudioPlay(buttonHoverSound, buttonsAudioGroup, 1.f, 1.f, 0);
			audioPlayed = true;
		}
		if (left_mouse_pressed) {
			AEAudioPlay(buttonClickSound, buttonsAudioGroup, 1.f, 1.f, 0);
			AEAudioPauseGroup(mainmenuAudioGroup);
			gGameStateNext = GS_HIGHSCORES;
		}
	}
	else highscoreButton.spriteIndex = 8;

	if (IsButtonHover(quitButtonX, buttonsY, buttonScaleX, buttonScaleY, MouseX, MouseY)) {
		quitButton.spriteIndex = 3;
		if (!audioPlayed) {
			AEAudioPlay(buttonHoverSound, buttonsAudioGroup, 1.f, 1.f, 0);
			audioPlayed = true;
		}
		if (left_mouse_pressed) {
			gGameStateNext = GS_QUIT;
		}
	}
	else quitButton.spriteIndex = 2;
	
	if (IsButtonHover(creditsButtonX, creditsButtonY, buttonScaleX / 2, buttonScaleY / 2, MouseX, MouseY)) {
		creditButton.spriteIndex = 7;
		if (!audioPlayed) {
			AEAudioPlay(buttonHoverSound, buttonsAudioGroup, 1.f, 1.f, 0);
			audioPlayed = true;
		}
		if (left_mouse_pressed) {
			AEAudioPlay(buttonClickSound, buttonsAudioGroup, 1.f, 1.f, 0);
			AEAudioPauseGroup(mainmenuAudioGroup);
			gGameStateNext = GS_CREDITS;
		}
	}
	else creditButton.spriteIndex = 6;

	if (!IsButtonHover(guideButtonX, buttonsY, buttonScaleX, buttonScaleY, MouseX, MouseY) &&
		!IsButtonHover(highscoreButtonX, buttonsY, buttonScaleX, buttonScaleY, MouseX, MouseY) &&
		!IsButtonHover(quitButtonX, buttonsY, buttonScaleX, buttonScaleY, MouseX, MouseY) &&
		!IsButtonHover(creditsButtonX, creditsButtonY, buttonScaleX, buttonScaleY, MouseX, MouseY) &&
		!IsButtonHover(playButtonX, buttonsY, buttonScaleX, buttonScaleY, MouseX, MouseY)) {
		audioPlayed = false;
	}
}

void Draw_Menu() {
	DrawMesh(&mainMenu.transform);
	DrawStaticSprite(&playButton.transform, playButton.spriteIndex);
	DrawStaticSprite(&guideButton.transform, guideButton.spriteIndex);
	DrawStaticSprite(&highscoreButton.transform, highscoreButton.spriteIndex);
	DrawStaticSprite(&quitButton.transform, quitButton.spriteIndex);
	DrawStaticSprite(&creditButton.transform, creditButton.spriteIndex);
	DrawMesh(&splashScreen.transform);
	
}

void Free_Menu() {
	AEGfxMeshFree(splashScreenMesh);
	AEGfxMeshFree(BGMesh);
	AEGfxMeshFree(playMesh);
	AEGfxMeshFree(guideMesh);
	AEGfxMeshFree(highscoreMesh);
	AEGfxMeshFree(quitMesh);
	AEGfxMeshFree(creditMesh);

	AEGfxTextureUnload(splashScreenTexture);
	AEGfxTextureUnload(MainMenuBG);
	AEGfxTextureUnload(buttonsSprite);

}
// ---------------------------------------------------------------------------
// main

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	srand((unsigned int)time(NULL));

	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	srand(static_cast<unsigned>(time(0)));

	AESysSetWindowTitle("Guns of the Ronin");

	Load_HighScoreFile();

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 1600, 900, 1, 60, true, NULL);

	font = AEGfxCreateFont("Assets/Roboto-Regular.ttf", 50);
	AudioLoad();

	GameStateMgrInit(GS_MAINMENU);

	while (gGameStateCurr != GS_QUIT)
	{
		// reset the system modules
		AESysReset();
		// If not restarting, load the gamestate
		if (gGameStateCurr != GS_RESTART)
		{
			GameStateMgrUpdate();
		}
		else
			gGameStateNext = gGameStateCurr = gGameStatePrev;
		// Initialize the gamestate
		GameStateInit();
		while (gGameStateCurr == gGameStateNext)
		{
			AESysFrameStart();
			AEAudioUpdate();
			AEInputUpdate();

			GameStateUpdate();
			GameStateDraw();
			AESysFrameEnd();

			// check if forcing the application to quit
			if ((AESysDoesWindowExist() == false))
				gGameStateNext = GS_QUIT;
		}

		GameStateFree();

		if (gGameStateNext != GS_RESTART)
			GameStateFree;

		gGameStatePrev = gGameStateCurr;
		gGameStateCurr = gGameStateNext;
	}
	Update_HighScoreFile();
	AEGfxDestroyFont(font);
	// free the system
	AESysExit();
}