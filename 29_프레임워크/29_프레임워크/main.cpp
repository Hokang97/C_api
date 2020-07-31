#include "GameDefine.h"
#include "GameDirector.h"
#include "SceneDefine.h"

GameDirector* director = nullptr;

void InitScene();
void LoadScene(int index);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevIns, LPSTR lpCmdLine, int nCmdShow)
{
	InitScene();
	LoadScene(0);

	director->Loop(hInstance, lpCmdLine, nCmdShow);
}

void InitScene()
{
	director = GameDirector::GetGameDirector();
	director->GetSceneManager()->RegisterScene("FirstScene", new FirstScene);
}

void LoadScene(int index)
{
	

	switch (index)
	{
	case 0:
		director->GetSceneManager()->reserveChangeScene("FirstScene");
			break;
	}
}