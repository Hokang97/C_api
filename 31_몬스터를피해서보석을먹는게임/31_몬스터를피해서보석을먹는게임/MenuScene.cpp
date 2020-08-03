#include "MenuScene.h"


void MenuScene::Init()
{
	RECT rc = { 0,0,650,670 };
	mBackGround.Init(const_cast<char*>("background.bmp"), rc);

	RECT rc2 = { 0,0,500,75 };
	mTitle.Init(const_cast<char*>("title.bmp"), rc2);
	mTitle.SetTransparentColor(RGB(86, 49, 25));

	RECT rc3 = { 20,100,400,500 };
	mBonoBono.Init(const_cast<char*>("bonobono.bmp"), rc3);

	RECT rc4 = { 350,200,600,262 };
	m_StartButton.Init(const_cast<char*>("start_button.bmp"), rc4);
	m_StartButton.SetTag(const_cast<char*>(TAG_START_BUTTON));
	m_StartButton.SetTransparentColor(RGB(255, 0, 255));

	m_StartButton.GetButtonCropRect()[BTN_STATE_NORMAL] = { 0,0,200,72 };
	m_StartButton.GetButtonCropRect()[BTN_STATE_HOVER] = { 0,72,200,72 };
	m_StartButton.GetButtonCropRect()[BTN_STATE_CLICKED] = { 0,142,200,72 };

	RECT rc5 = { 350,300,600,362 };
	m_ExitButton.Init(const_cast<char*>("exit_button.bmp"), rc5);
	m_ExitButton.SetTag(const_cast<char*>(TAG_EXIT_BUTTON));
	m_ExitButton.SetTransparentColor(RGB(255, 0, 255));

	m_ExitButton.GetButtonCropRect()[BTN_STATE_NORMAL] = { 0,0,200,72 };
	m_ExitButton.GetButtonCropRect()[BTN_STATE_HOVER] = { 0,72,200,72 };
	m_ExitButton.GetButtonCropRect()[BTN_STATE_CLICKED] = { 0,142,200,72 };


	
}

void MenuScene::Update(float dt)
{
	mBackGround.Update(dt);
	mTitle.Update(dt);
	mBonoBono.Update(dt);
	m_StartButton.Update(dt);
	m_ExitButton.Update(dt);
}

void MenuScene::Render(HDC hdc, float dt)
{
	mBackGround.Render(hdc, dt);
	mTitle.Render(hdc, dt);
	mBonoBono.Render(hdc, dt);
	m_StartButton.Render(hdc, dt);
	m_ExitButton.Render(hdc, dt);
}

void MenuScene::Destroy()
{
	mBackGround.Destroy();
	mTitle.Destroy();
	mBonoBono.Destroy();
	m_StartButton.Destroy();
	m_ExitButton.Destroy();
}

MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
}
