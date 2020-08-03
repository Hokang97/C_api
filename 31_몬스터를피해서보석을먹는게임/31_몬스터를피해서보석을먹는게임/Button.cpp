#include "Button.h"
#pragma warning(disable:4996)
Button::Button()
{
}

Button::~Button()
{
}

void Button::Init(char* imageName, RECT rect)
{
	const char* path = "Resource/";
	char FilePath[256];
	sprintf(FilePath, "%s%s", path, imageName);
	GetBitmap()->LoadBitmapByPath(FilePath);

	SetX(rect.left);
	SetY(rect.top);

	m_Width = rect.right - rect.left;
	m_Height = rect.bottom - rect.top;

	m_BtnState = BTN_STATE_NORMAL;
	m_nowRect = &m_ButtonRC[BTN_STATE_NORMAL];

	m_IsClicked = FALSE;
}

void Button::Init()
{
}

void Button::Update(float dt)
{
	int mX = GameDirector::GetGameDirector()->GetSceneManager()->GetMousePositionX();
	int mY = GameDirector::GetGameDirector()->GetSceneManager()->GetMousePositionY();

	if (mX >= GetX() && mX <= GetX() + m_Width && mY >= GetY() && mY <= GetY() + m_Height)
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			m_IsClicked = TRUE;

			if (m_BtnState != BTN_STATE_CLICKED)
			{
				m_BtnState = BTN_STATE_CLICKED;
				m_nowRect = &m_ButtonRC[BTN_STATE_CLICKED];
			}
			
		}
		else if (m_IsClicked)
		{
			m_IsClicked = FALSE;
			ButtonEvent();
		}
		else if (m_BtnState != BTN_STATE_HOVER	)
		{
			m_IsClicked = FALSE;
			m_BtnState = BTN_STATE_HOVER;
			m_nowRect = &m_ButtonRC[BTN_STATE_HOVER];
		}
		
	}
	else
	{
		m_IsClicked = FALSE;

		if (m_BtnState != BTN_STATE_NORMAL)
		{
			m_BtnState = BTN_STATE_NORMAL;
			m_nowRect = &m_ButtonRC[BTN_STATE_NORMAL];
		}
	}
}

void Button::Render(HDC hdc, float dt)
{
	GetBitmap()->DrawBitmapByCropping(hdc, GetX(), GetY(), m_Width, m_Height,
		m_nowRect->x, m_nowRect->y, m_nowRect->width, m_nowRect->height);
}

void Button::Destroy()
{
}

void Button::SetTag(char* value)
{
	strcpy(m_Tag, value);
}

void Button::SetTransparentColor(DWORD color)
{
	GetBitmap()->SetTransparentColor(color);
}

CRECT* Button::GetButtonCropRect()
{
	return m_ButtonRC;
}

void Button::ButtonEvent()
{
	if (strcmp(m_Tag, TAG_START_BUTTON) == 0)
	{
		GameDirector::GetGameDirector()->GetSceneManager()->reserveChangeScene("GameScene");
	}

	if (strcmp(m_Tag, TAG_EXIT_BUTTON) == 0)
	{
		PostQuitMessage(0);
	}
}


