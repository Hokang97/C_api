#include "GameDefine.h"
#include "GameDirector.h"
#include "SceneDefine.h"
#include "FirstScene.h"
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
	director->GetSceneManager()->RegisterScene("MenuScene", new MenuScene);
	director->GetSceneManager()->RegisterScene("GameScene", new GameScene);

}

void LoadScene(int index)
{
	switch (index)
	{
	case 0:
		director->GetSceneManager()->reserveChangeScene("MenuScene");
			break;

	case 1:
		director->GetSceneManager()->reserveChangeScene("GameScene");
		break;
	}
}