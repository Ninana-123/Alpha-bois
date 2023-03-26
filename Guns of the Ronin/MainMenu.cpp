#include "MainMenu.h"

AEGfxTexture* MainMenuBG;

AEGfxTexture* buttonsSprite;

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

//float creditsButtonX;
//float creditsButtonY;

bool left_mouse_pressed;

MainMenu mainMenu;
MainMenu playButton;
MainMenu guideButton;
MainMenu highscoreButton;
MainMenu quitButton;

s8 font;

void Init_Menu() {
	// Changing the window title
	AESysSetWindowTitle("Guns of the Ronin");
	// reset the system modules
	AESysReset();
	MainMenuBG = AEGfxTextureLoad("Assets/MainMenuSakura.png");
	buttonsSprite = AEGfxTextureLoad("Assets/buttonspritesheet.png");

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



}

void Update_Menu() {
	static float frameTimer = 0;
	frameTimer += deltaTime;

	Update_Time();
	AEInputGetCursorPosition(MouseX, MouseY);
	*MouseX = *MouseX - 800;
	*MouseY = (*MouseY - 450) * -1;
	std::cout << "Mouse_X: " << *MouseX << std::endl;
	std::cout << "Mouse_Y: " << *MouseY << std::endl;
	left_mouse_pressed = AEInputCheckReleased(AEVK_LBUTTON);

	if (frameTimer >= 0.3f) {
		mainMenu.sakuraAnim.PlayAnim();
		mainMenu.sakuraAnim.NextFrame(mainMenu.transform);
		mainMenu.sakuraAnim.Update_SpriteAnim(mainMenu.transform);
		frameTimer = 0;
	}


	if (IsButtonHover(playButtonX, buttonsY, buttonScaleX, buttonScaleY, MouseX, MouseY)) {
		playButton.spriteIndex = 1;
		if (left_mouse_pressed) {
			gGameStateNext = GS_LEVEL1;
		}
	}
	else playButton.spriteIndex = 0;

	if (IsButtonHover(guideButtonX,buttonsY,buttonScaleX,buttonScaleY,MouseX,MouseY)) {
		guideButton.spriteIndex = 5;
		if (left_mouse_pressed) {
			gGameStateNext = GS_GUIDE;
		}
	}
	else guideButton.spriteIndex = 4;

	if (IsButtonHover(highscoreButtonX, buttonsY, buttonScaleX, buttonScaleY, MouseX, MouseY)) {
		highscoreButton.spriteIndex = 9;
	}
	else highscoreButton.spriteIndex = 8;

	if (IsButtonHover(quitButtonX, buttonsY, buttonScaleX, buttonScaleY, MouseX, MouseY)) {
		quitButton.spriteIndex = 3;
		if (left_mouse_pressed) {
			gGameStateNext = GS_QUIT;
		}
	}
	else quitButton.spriteIndex = 2;

}

void Draw_Menu() {
	DrawMesh(&mainMenu.transform);
	DrawStaticSprite(&playButton.transform, playButton.spriteIndex);
	DrawStaticSprite(&guideButton.transform, guideButton.spriteIndex);
	DrawStaticSprite(&highscoreButton.transform, highscoreButton.spriteIndex);
	DrawStaticSprite(&quitButton.transform, quitButton.spriteIndex);

}

void Free_Menu() {
	AEGfxMeshFree(BGMesh);
	AEGfxMeshFree(playMesh);
	AEGfxMeshFree(guideMesh);
	AEGfxMeshFree(highscoreMesh);
	AEGfxMeshFree(quitMesh);
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

	int gGameRunning = 1;

	AESysSetWindowTitle("Guns of the Ronin");

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 1600, 900, 1, 60, true, NULL);

	font = AEGfxCreateFont("Assets/Roboto-Regular.ttf", 20);

	GameStateMgrInit(GS_MAINMENU);

	while (gGameStateCurr != GS_QUIT)
	{
		// reset the system modules
		AESysReset();
		// If not restarting, load the gamestate
		if (gGameStateCurr != GS_RESTART)
		{
			GameStateMgrUpdate();
			GameStateInit();

		}
		else
			gGameStateNext = gGameStateCurr = gGameStatePrev;
		// Initialize the gamestate
		GameStateInit();
		while (gGameStateCurr == gGameStateNext)
		{
			AESysFrameStart();

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

	AEGfxDestroyFont(font);
	// free the system
	AESysExit();
}