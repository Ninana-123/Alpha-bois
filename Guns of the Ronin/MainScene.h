/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*
@file main.h
@co-author Teo Sheen Yeoh , Zhi Cheng, Kai Alexander Van Adrichem Boogaert, Sean Ang JiaBao, Zeng ZhiCheng , Vance Tay Jun Feng( 20% each)
@Email t.sheenyeoh@digipen.edu, kaialexander.v@digipen.edu,z.zhicheng@digipen.edu,ang.s@digipen.edu,junfengvance.t@digipen.edu
@course CSD 1451
@section Section A
@date 3 March 2023
@brief This file contains code for the credit screen.
*//*______________________________________________________________________*/
#ifndef MAINSCENE_H
#define MAINSCENE_H

namespace {
	AEGfxVertexList* levelMesh = 0;
}

class Level{
public:
	Transform transform;
};

void Init_Scene();
void Update_Scene();
void Draw_Scene();
void Free_Scene();
void Set_StartingWave(int waveNum);
#endif

