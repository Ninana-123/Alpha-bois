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
/*TEXTURES*/
AEGfxTexture* mainMenuBG;
AEGfxTexture* buttonsSprite;
AEGfxTexture* splashScreenTexture;
/*MOUSE INPUT*/
s32 mainMenuMousePosX;
s32 mainMenuMousePosY;

/*FILE ROTATION VALUE*/
#define MAIN_MENU_ROTATION 0.0f

/*BG VALUES*/
#define MAIN_MENU_BG_X 1600.0f
#define MAIN_MENU_BG_Y 900.0f
#define MAIN_MENU_BG_HEIGHT 1.0f
#define MAIN_MENU_BG_WIDTH 4.0f

#define SPLASHSCREEN_BG_X 1600.0f
#define SPLASHSCREEN_BG_Y 900.0f
#define SPLASHSCREEN_BG_HEIGHT 1.0f
#define SPLASHSCREEN_BG_WIDTH 1.0f


/*BUTTON VALUES*/
#define MAIN_MENU_BUTTON_SCALE_X  250.0f
#define MAIN_MENU_BUTTON_SCALE_Y  125.0f
#define MAIN_MENU_BUTTON_HIEGHT  1.0f
#define MAIN_MENU_BUTTON_WIDTH  10.0f

#define MAIN_MENU_BUTTON_POS_Y -151.0f

#define MAIN_MENU_PLAY_BUTTON_X -81.0f
#define MAIN_MENU_GUIDE_BUTTON_X 169.0f
#define MAIN_MENU_HIGHSCORE_BUTTON_X 419.0f
#define MAIN_MENU_QUIT_BUTTON_X 669.0f

#define MAIN_MENU_CREDITS_BUTTON_X 669.0f
#define MAIN_MENU_CREDITS_BUTTON_Y -371.0f

#define MAIN_MENU_WINDOW_HALF_X 800
#define MAIN_MENU_WINDOW_HALF_Y 450

/*BUTTON SPRITE INDEX*/
#define PLAY_BUTTON_SPRITE 0
#define PLAY_BUTTON_SPRITE_HOVER 1 
#define QUIT_BUTTON_SPRITE 2
#define QUIT_BUTTON_SPRITE_HOVER 3
#define GUIDE_BUTTON_SPRITE 4
#define GUIDE_BUTTON_SPRITE_HOVER 5
#define CREDIT_BUTTON_SPRITE 6
#define CREDIT_BUTTON_SPRITE_HOVER 7
#define HIGHSCORE_BUTTON_SPRITE 8
#define HIGHSCORE_BUTTON_SPRITE_HOVER 9

/*LEFT CLICK CHECK*/
bool leftMousePressed;

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
	mainMenuBG = AEGfxTextureLoad("Assets/MainMenu.png");
	buttonsSprite = AEGfxTextureLoad("Assets/buttonspritesheet.png");
	splashScreenTexture = AEGfxTextureLoad("Assets/DigiPen_BLACK_rights.png");
	
	Create_QuadMesh(1.f, 1.f, Color(1, 1, 1), splashScreenMesh, SPLASHSCREEN_BG_HEIGHT, SPLASHSCREEN_BG_WIDTH);
	splashScreen.transform.texture = &splashScreenTexture;
	splashScreen.transform.position = { 0.0f,0.0f };
	splashScreen.transform.scale = { SPLASHSCREEN_BG_X,-SPLASHSCREEN_BG_Y };
	splashScreen.transform.height = SPLASHSCREEN_BG_HEIGHT;
	splashScreen.transform.width = SPLASHSCREEN_BG_WIDTH;
	splashScreen.transform.rotation = MAIN_MENU_ROTATION;
	splashScreen.transform.mesh = &splashScreenMesh;
	
	Create_QuadMesh(1.f, 1.f, Color(1, 1, 1), BGMesh, MAIN_MENU_BG_HEIGHT / MAIN_MENU_BG_WIDTH, MAIN_MENU_BG_HEIGHT);
	mainMenu.transform.texture = &mainMenuBG;
	mainMenu.transform.position = { 0.0f,0.0f };
	mainMenu.transform.scale = { MAIN_MENU_BG_X,-MAIN_MENU_BG_Y };
	mainMenu.transform.height = MAIN_MENU_BG_HEIGHT;
	mainMenu.transform.width = MAIN_MENU_BG_WIDTH;
	mainMenu.transform.rotation = MAIN_MENU_ROTATION;
	mainMenu.transform.mesh = &BGMesh;

	Create_QuadMesh(1.f, 1.f, Color(1, 1, 1), playMesh, MAIN_MENU_BUTTON_HIEGHT / MAIN_MENU_BUTTON_WIDTH, MAIN_MENU_BUTTON_HIEGHT);
	playButton.transform.texture = &buttonsSprite;
	playButton.transform.position = { MAIN_MENU_PLAY_BUTTON_X,MAIN_MENU_BUTTON_POS_Y };
	playButton.transform.scale = { MAIN_MENU_BUTTON_SCALE_X,-MAIN_MENU_BUTTON_SCALE_Y };
	playButton.transform.height = MAIN_MENU_BUTTON_HIEGHT;
	playButton.transform.width = MAIN_MENU_BUTTON_WIDTH;
	playButton.transform.rotation = MAIN_MENU_ROTATION;
	playButton.transform.mesh = &playMesh;

	Create_QuadMesh(1.f, 1.f, Color(1, 1, 1), guideMesh, MAIN_MENU_BUTTON_HIEGHT / MAIN_MENU_BUTTON_WIDTH, MAIN_MENU_BUTTON_HIEGHT);
	guideButton.transform.texture = &buttonsSprite;
	guideButton.transform.position = { MAIN_MENU_GUIDE_BUTTON_X,MAIN_MENU_BUTTON_POS_Y };
	guideButton.transform.scale = { MAIN_MENU_BUTTON_SCALE_X,-MAIN_MENU_BUTTON_SCALE_Y };
	guideButton.transform.height = MAIN_MENU_BUTTON_HIEGHT;
	guideButton.transform.width = MAIN_MENU_BUTTON_WIDTH;
	guideButton.transform.rotation = MAIN_MENU_ROTATION;
	guideButton.transform.mesh = &guideMesh;
	
	Create_QuadMesh(1.f, 1.f, Color(1, 1, 1), highscoreMesh, MAIN_MENU_BUTTON_HIEGHT / MAIN_MENU_BUTTON_WIDTH, MAIN_MENU_BUTTON_HIEGHT);
	highscoreButton.transform.texture = &buttonsSprite;
	highscoreButton.transform.position = { MAIN_MENU_HIGHSCORE_BUTTON_X,MAIN_MENU_BUTTON_POS_Y };
	highscoreButton.transform.scale = { MAIN_MENU_BUTTON_SCALE_X,-MAIN_MENU_BUTTON_SCALE_Y };
	highscoreButton.transform.height = MAIN_MENU_BUTTON_HIEGHT;
	highscoreButton.transform.width = MAIN_MENU_BUTTON_WIDTH;
	highscoreButton.transform.rotation = MAIN_MENU_ROTATION;
	highscoreButton.transform.mesh = &highscoreMesh;
	
	Create_QuadMesh(1.f, 1.f, Color(1, 1, 1), quitMesh, MAIN_MENU_BUTTON_HIEGHT / MAIN_MENU_BUTTON_WIDTH, MAIN_MENU_BUTTON_HIEGHT);
	quitButton.transform.texture = &buttonsSprite;
	quitButton.transform.position = { MAIN_MENU_QUIT_BUTTON_X,MAIN_MENU_BUTTON_POS_Y };
	quitButton.transform.scale = { MAIN_MENU_BUTTON_SCALE_X,-MAIN_MENU_BUTTON_SCALE_Y };
	quitButton.transform.height = MAIN_MENU_BUTTON_HIEGHT;
	quitButton.transform.width = MAIN_MENU_BUTTON_WIDTH;
	quitButton.transform.rotation = MAIN_MENU_ROTATION;
	quitButton.transform.mesh = &quitMesh;
	
	Create_QuadMesh(1.f, 1.f, Color(1, 1, 1), creditMesh, MAIN_MENU_BUTTON_HIEGHT / MAIN_MENU_BUTTON_WIDTH, MAIN_MENU_BUTTON_HIEGHT);
	creditButton.transform.texture = &buttonsSprite;
	creditButton.transform.position = { MAIN_MENU_CREDITS_BUTTON_X,MAIN_MENU_CREDITS_BUTTON_Y };
	creditButton.transform.scale = { MAIN_MENU_BUTTON_SCALE_X /2,-MAIN_MENU_BUTTON_SCALE_Y / 2};
	creditButton.transform.height = MAIN_MENU_BUTTON_HIEGHT;
	creditButton.transform.width = MAIN_MENU_BUTTON_WIDTH;
	creditButton.transform.rotation = MAIN_MENU_ROTATION;
	creditButton.transform.mesh = &quitMesh;


	AEAudioPlay(mainmenuSong,mainmenuAudioGroup, 1.f, 1.f, -1);

}

void Update_Menu() {
	AEAudioResumeGroup(mainmenuAudioGroup);
	static float frameTimer = 0.f;
	static float splasScreenTimer = 0.f;
	splasScreenTimer += deltaTime;
	frameTimer += deltaTime;

	Update_TimeMan();
	AEInputGetCursorPosition(&mainMenuMousePosX, &mainMenuMousePosY);
	mainMenuMousePosX = mainMenuMousePosX - MAIN_MENU_WINDOW_HALF_X;
	mainMenuMousePosY = (mainMenuMousePosY - MAIN_MENU_WINDOW_HALF_Y) * -1;
	leftMousePressed = AEInputCheckReleased(AEVK_LBUTTON);

	if (splasScreenTimer >= 2.f) {
		splashScreen.transform.scale = { 0.f,0.f};
	}

	if (frameTimer >= 0.3f) {
		mainMenu.bgAnim.play_Anim();
		mainMenu.bgAnim.next_Frame(mainMenu.transform);
		mainMenu.bgAnim.update_SpriteAnim(mainMenu.transform);
		frameTimer = 0;
	}

	if (Is_ButtonHover(MAIN_MENU_PLAY_BUTTON_X, MAIN_MENU_BUTTON_POS_Y, MAIN_MENU_BUTTON_SCALE_X, -MAIN_MENU_BUTTON_SCALE_Y, &mainMenuMousePosX,&mainMenuMousePosY)) {
		playButton.spriteIndex = PLAY_BUTTON_SPRITE_HOVER;
		if (!audioPlayed) {
			AEAudioPlay(buttonHoverSound, buttonsAudioGroup, 1.f, 1.f, 0);
			audioPlayed = true;
		}
		if (leftMousePressed) {
			AEAudioPlay(buttonClickSound, buttonsAudioGroup, 1.f, 1.f, 0);
			AEAudioPauseGroup(mainmenuAudioGroup);
			gGameStateNext = GS_LEVEL1;
			Set_StartingWave(1);
		}
	}
	else playButton.spriteIndex = PLAY_BUTTON_SPRITE;

	if (Is_ButtonHover(MAIN_MENU_GUIDE_BUTTON_X, MAIN_MENU_BUTTON_POS_Y, MAIN_MENU_BUTTON_SCALE_X, -MAIN_MENU_BUTTON_SCALE_Y, &mainMenuMousePosX, &mainMenuMousePosY)) {
		guideButton.spriteIndex = GUIDE_BUTTON_SPRITE_HOVER;
		if (!audioPlayed) {
			AEAudioPlay(buttonHoverSound, buttonsAudioGroup, 1.f, 1.f, 0);
			audioPlayed = true;
		}
		if (leftMousePressed) {
			AEAudioPlay(buttonClickSound, buttonsAudioGroup, 1.f, 1.f, 0);
			AEAudioPauseGroup(mainmenuAudioGroup);
			gGameStateNext = GS_GUIDE;
		}
	}
	else guideButton.spriteIndex = GUIDE_BUTTON_SPRITE;

	if (Is_ButtonHover(MAIN_MENU_HIGHSCORE_BUTTON_X, MAIN_MENU_BUTTON_POS_Y, MAIN_MENU_BUTTON_SCALE_X, -MAIN_MENU_BUTTON_SCALE_Y, &mainMenuMousePosX, &mainMenuMousePosY)) {
		highscoreButton.spriteIndex = HIGHSCORE_BUTTON_SPRITE_HOVER;
		if (!audioPlayed) {
			AEAudioPlay(buttonHoverSound, buttonsAudioGroup, 1.f, 1.f, 0);
			audioPlayed = true;
		}
		if (leftMousePressed) {
			AEAudioPlay(buttonClickSound, buttonsAudioGroup, 1.f, 1.f, 0);
			AEAudioPauseGroup(mainmenuAudioGroup);
			gGameStateNext = GS_HIGHSCORES;
		}
	}
	else highscoreButton.spriteIndex = HIGHSCORE_BUTTON_SPRITE;

	if (Is_ButtonHover(MAIN_MENU_QUIT_BUTTON_X, MAIN_MENU_BUTTON_POS_Y, MAIN_MENU_BUTTON_SCALE_X, -MAIN_MENU_BUTTON_SCALE_Y, &mainMenuMousePosX, &mainMenuMousePosY)) {
		quitButton.spriteIndex = QUIT_BUTTON_SPRITE_HOVER;
		if (!audioPlayed) {
			AEAudioPlay(buttonHoverSound, buttonsAudioGroup, 1.f, 1.f, 0);
			audioPlayed = true;
		}
		if (leftMousePressed) {
			gGameStateNext = GS_QUIT;
		}
	}
	else quitButton.spriteIndex = QUIT_BUTTON_SPRITE;
	
	if (Is_ButtonHover(MAIN_MENU_CREDITS_BUTTON_X, MAIN_MENU_CREDITS_BUTTON_Y, MAIN_MENU_BUTTON_SCALE_X / 2, -(MAIN_MENU_BUTTON_SCALE_Y / 2), &mainMenuMousePosX, &mainMenuMousePosY)) {
		creditButton.spriteIndex = CREDIT_BUTTON_SPRITE_HOVER;
		if (!audioPlayed) {
			AEAudioPlay(buttonHoverSound, buttonsAudioGroup, 1.f, 1.f, 0);
			audioPlayed = true;
		}
		if (leftMousePressed) {
			AEAudioPlay(buttonClickSound, buttonsAudioGroup, 1.f, 1.f, 0);
			AEAudioPauseGroup(mainmenuAudioGroup);
			gGameStateNext = GS_CREDITS;
		}
	}
	else creditButton.spriteIndex = CREDIT_BUTTON_SPRITE;

	if (!Is_ButtonHover(MAIN_MENU_GUIDE_BUTTON_X, MAIN_MENU_BUTTON_POS_Y, MAIN_MENU_BUTTON_SCALE_X, -MAIN_MENU_BUTTON_SCALE_Y, &mainMenuMousePosX, &mainMenuMousePosY) &&
		!Is_ButtonHover(MAIN_MENU_HIGHSCORE_BUTTON_X, MAIN_MENU_BUTTON_POS_Y, MAIN_MENU_BUTTON_SCALE_X, -MAIN_MENU_BUTTON_SCALE_Y, &mainMenuMousePosX, &mainMenuMousePosY) &&
		!Is_ButtonHover(MAIN_MENU_QUIT_BUTTON_X, MAIN_MENU_BUTTON_POS_Y, MAIN_MENU_BUTTON_SCALE_X, -MAIN_MENU_BUTTON_SCALE_Y, &mainMenuMousePosX, &mainMenuMousePosY) &&
		!Is_ButtonHover(MAIN_MENU_CREDITS_BUTTON_X, MAIN_MENU_CREDITS_BUTTON_Y, MAIN_MENU_BUTTON_SCALE_X, -MAIN_MENU_BUTTON_SCALE_Y, &mainMenuMousePosX, &mainMenuMousePosY) &&
		!Is_ButtonHover(MAIN_MENU_PLAY_BUTTON_X, MAIN_MENU_BUTTON_POS_Y, MAIN_MENU_BUTTON_SCALE_X, -MAIN_MENU_BUTTON_SCALE_Y, &mainMenuMousePosX, &mainMenuMousePosY)) {
		audioPlayed = false;
	}

	if (AEInputCheckReleased(AEVK_1)) {
		AEAudioPlay(buttonClickSound, buttonsAudioGroup, 1.f, 1.f, 0);
		AEAudioPauseGroup(mainmenuAudioGroup);
		gGameStateNext = GS_LEVEL1;
		Set_StartingWave(1);
	}
	if (AEInputCheckReleased(AEVK_2)) {
		AEAudioPlay(buttonClickSound, buttonsAudioGroup, 1.f, 1.f, 0);
		AEAudioPauseGroup(mainmenuAudioGroup);
		gGameStateNext = GS_LEVEL1;
		Set_StartingWave(2);
	}
	if (AEInputCheckReleased(AEVK_3)) {
		AEAudioPlay(buttonClickSound, buttonsAudioGroup, 1.f, 1.f, 0);
		AEAudioPauseGroup(mainmenuAudioGroup);
		gGameStateNext = GS_LEVEL1;
		Set_StartingWave(3);
	}
	if (AEInputCheckReleased(AEVK_4)) {
		AEAudioPlay(buttonClickSound, buttonsAudioGroup, 1.f, 1.f, 0);
		AEAudioPauseGroup(mainmenuAudioGroup);
		gGameStateNext = GS_LEVEL1;
		Set_StartingWave(4);
	}
	if (AEInputCheckReleased(AEVK_5)) {
		AEAudioPlay(buttonClickSound, buttonsAudioGroup, 1.f, 1.f, 0);
		AEAudioPauseGroup(mainmenuAudioGroup);
		gGameStateNext = GS_LEVEL1;
		Set_StartingWave(5);
	}
	if (AEInputCheckReleased(AEVK_6)) {
		AEAudioPlay(buttonClickSound, buttonsAudioGroup, 1.f, 1.f, 0);
		AEAudioPauseGroup(mainmenuAudioGroup);
		gGameStateNext = GS_LEVEL1;
		Set_StartingWave(6);
	}
	if (AEInputCheckReleased(AEVK_7)) {
		AEAudioPlay(buttonClickSound, buttonsAudioGroup, 1.f, 1.f, 0);
		AEAudioPauseGroup(mainmenuAudioGroup);
		gGameStateNext = GS_LEVEL1;
		Set_StartingWave(7);
	}
	if (AEInputCheckReleased(AEVK_8)) {
		AEAudioPlay(buttonClickSound, buttonsAudioGroup, 1.f, 1.f, 0);
		AEAudioPauseGroup(mainmenuAudioGroup);
		gGameStateNext = GS_LEVEL1;
		Set_StartingWave(8);
	}
	if (AEInputCheckReleased(AEVK_9)) {
		AEAudioPlay(buttonClickSound, buttonsAudioGroup, 1.f, 1.f, 0);
		AEAudioPauseGroup(mainmenuAudioGroup);
		gGameStateNext = GS_LEVEL1;
		Set_StartingWave(9);
	}
	if (AEInputCheckReleased(AEVK_0)) {
		AEAudioPlay(buttonClickSound, buttonsAudioGroup, 1.f, 1.f, 0);
		AEAudioPauseGroup(mainmenuAudioGroup);
		gGameStateNext = GS_LEVEL1;
		Set_StartingWave(10);
	}
}

void Draw_Menu() {
	Draw_Mesh(&mainMenu.transform);
	Draw_StaticSprite(&playButton.transform, playButton.spriteIndex);
	Draw_StaticSprite(&guideButton.transform, guideButton.spriteIndex);
	Draw_StaticSprite(&highscoreButton.transform, highscoreButton.spriteIndex);
	Draw_StaticSprite(&quitButton.transform, quitButton.spriteIndex);
	Draw_StaticSprite(&creditButton.transform, creditButton.spriteIndex);
	Draw_Mesh(&splashScreen.transform);
	
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
	AEGfxTextureUnload(mainMenuBG);
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
	AESysInit(hInstance, nCmdShow, 1600, 900, 0, 60, true, NULL);

	font = AEGfxCreateFont("Assets/Fonts/Roboto-Regular.ttf", 50);
	Audio_Load();

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