#include "MainMenu.h"


AEGfxTexture* MainMenuBG;
//AEGfxVertexList* BGMesh;
//int BGIndex = 0;

AEGfxTexture* buttons;
//AEGfxVertexList* playMesh;

s32 MousePosX;
s32 MousePosY;

s32* MouseX = &MousePosX;
s32* MouseY = &MousePosY;

bool playHover = false;
bool tutHover = false;
bool exitHover = false;
bool left_mouse_pressed;

Menu mainMenu;
Menu playButton;
void Init_Menu() {
	// Changing the window title
	AESysSetWindowTitle("Guns of the Ronin");
	// reset the system modules
	AESysReset();
	MainMenuBG = AEGfxTextureLoad("Assets/MainMenu.png");
	buttons = AEGfxTextureLoad("Assets/buttonsspritesheet.png");
	
	
	CreateSpriteMesh(&mainMenu.transform, BGMesh);
	mainMenu.transform.texture = MainMenuBG;
	mainMenu.transform.position = { 0.0f,0.0f };
	mainMenu.transform.scale = { 1600.0f,900.0f };
	mainMenu.transform.height = 1.0f;
	mainMenu.transform.width = 4.0f;
	mainMenu.transform.rotation = 0.0f;
	mainMenu.transform.mesh = &BGMesh;

	CreateSpriteMesh(&playButton.transform, playMesh);
	playButton.transform.texture = buttons;
	playButton.transform.position = { -81.0f,-151.0f };
	playButton.transform.scale = { 250.0f,125.0f };
	playButton.transform.height = 1.0f;
	playButton.transform.width = 8.0f;
	playButton.transform.rotation = 0.0f;
	playButton.transform.mesh = &playMesh;

}

void Update_Menu() {
	Update_Time();
	AEInputGetCursorPosition(MouseX, MouseY);
	*MouseX = *MouseX - 800;
	*MouseY = (*MouseY - 450) * -1;
	left_mouse_pressed = AEInputCheckTriggered(AEVK_LBUTTON);
	//std::cout << "Mouse_X: " << *MouseX << std::endl;
	//std::cout << "Mouse_Y: " <<*MouseY << std::endl;

	if ((int)*MouseX > -200 && (int)*MouseX < 33 && (int)*MouseY > -195 && (int)*MouseY < -97) {
		playHover = true;
		if (left_mouse_pressed) {
			gGameStateNext = GS_LEVEL1;
		}
	}
	else playHover = false;
	
	if ((int)*MouseX > 176 && (int)*MouseX < 507 && (int)*MouseY > -205 && (int)*MouseY < -91) {
		tutHover = true;
	}
	else tutHover = false;

	if ((int)*MouseX > 546 && (int)*MouseX < 781 && (int)*MouseY > -205 && (int)*MouseY < -91) {
		exitHover = true;
	}
	else exitHover = false;



}

void Draw_Menu(){
	int index = 0;
	DrawSprite(&mainMenu.transform,index);
	DrawSprite(&playButton.transform, index);

	if (playHover == true) {
		//AEGfxTextureUnload(buttons);
		DrawSprite(&playButton.transform, index+1);
	}
	if (tutHover == true) {
		DrawSprite(&mainMenu.transform, index + 2);
	}
	if (exitHover == true) {
		DrawSprite(&mainMenu.transform, index + 3);
	}

}

void Free_Menu() {
	AEGfxMeshFree(BGMesh);
	AEGfxTextureUnload(MainMenuBG);
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
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	#endif

	srand((unsigned int)time(NULL));

	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	srand(static_cast<unsigned>(time(0)));

	int gGameRunning = 1;

	// Initialization of your own variables go here

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 1600, 900, 1, 60, true, NULL);

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
			if ((AESysDoesWindowExist() == false) || AEInputCheckTriggered(AEVK_ESCAPE))
				gGameStateNext = GS_QUIT;
		}

		GameStateFree();

		if (gGameStateNext != GS_RESTART)
			GameStateFree;

		gGameStatePrev = gGameStateCurr;
		gGameStateCurr = gGameStateNext;
	}

	// free the system
	AESysExit();
}