#include "multi_player.h"
#include "main.h"
#include "draw.h"

int mdirection_x = 1;
int mdirection_y = 1;

Rect mRect1;
Rect mRect2;
Rect mBackground_up;
Rect mBackground_down;
Rect mBall;

int mmode;

void InitMultiPlayer()
{
	mdirection_x = 1;
	mdirection_y = 1;
	mRect1 = { 0,12,1,4,'*' };
	mRect2 = { 79,12,1,4,'*' };
	mBall = { 20,rand() % 20 + 2,1,1,'O' };
	mBackground_up = { 0,0,80,1,'X' };
	mBackground_down = { 0,23,80,1,'X' };
	mmode = -1;
	ClearWindow(GetWindow());
}

void UpdateMultiPlayer()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		mRect2.StartPoint_y += -1;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		mRect2.StartPoint_y += 1;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		mRect2.StartPoint_x += -1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		mRect2.StartPoint_x += 1;
	}
	if (GetAsyncKeyState('W') & 0x8000)
	{
		mRect1.StartPoint_y += -1;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		mRect1.StartPoint_x += -1;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		mRect1.StartPoint_y += 1;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		mRect1.StartPoint_x += 1;
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		mmode = GAME_END;
	}

	mBall.StartPoint_x += 1 * mdirection_x;
	mBall.StartPoint_y += 1 * mdirection_y;

	if (mRect1.StartPoint_x > WINDOW_WIDTH / 2 - 1)
	{
		mRect1.StartPoint_x = WINDOW_WIDTH / 2 - 1;
	}
	if (mRect1.StartPoint_x < 0)
	{
		mRect1.StartPoint_x = 0;
	}
	if (mRect1.StartPoint_y > mBackground_down.StartPoint_y - 4)
	{
		mRect1.StartPoint_y = mBackground_down.StartPoint_y - 4;
	}
	if (mRect1.StartPoint_y < mBackground_up.StartPoint_y + 1)
	{
		mRect1.StartPoint_y = mBackground_up.StartPoint_y + 1;
	}
	if (mRect2.StartPoint_x < WINDOW_WIDTH / 2)
	{
		mRect2.StartPoint_x = WINDOW_WIDTH / 2;
	}
	if (mRect2.StartPoint_x > 79)
	{
		mRect2.StartPoint_x = 79;
	}
	if (mRect2.StartPoint_y > mBackground_down.StartPoint_y - 4)
	{
		mRect2.StartPoint_y = mBackground_down.StartPoint_y - 4;
	}
	if (mRect2.StartPoint_y < mBackground_up.StartPoint_y + 1)
	{
		mRect2.StartPoint_y = mBackground_up.StartPoint_y + 1;
	}

	if ((mBall.StartPoint_x == mRect1.StartPoint_x + 1) && 
		(mBall.StartPoint_y >= mRect1.StartPoint_y) && 
		(mBall.StartPoint_y <= mRect1.StartPoint_y + mRect1.Height))
	{
		mdirection_x *= -1;
	}
	if ((mBall.StartPoint_x == mRect2.StartPoint_x - 1) && 
		(mBall.StartPoint_y >= mRect2.StartPoint_y) && 
		(mBall.StartPoint_y <= mRect2.StartPoint_y + mRect2.Height))
	{
		mdirection_x *= -1;
	}
	if (mBall.StartPoint_y <= mBackground_up.StartPoint_y + 1 || 
		mBall.StartPoint_y >= mBackground_down.StartPoint_y - 1)
	{
		mdirection_y *= -1;
	}
	if (mBall.StartPoint_x < 0)
	{
		mBall.StartPoint_x = 0;
		
		mmode = GAMEOVER;
	}
	if (mBall.StartPoint_x > 79)
	{
		mBall.StartPoint_x = 79;
		
		mmode = GAMEOVER;
	}
}

void DrawMultiPlayer()
{
	FillIn(GetWindow(), mRect1);
	FillIn(GetWindow(), mRect2);
	FillIn(GetWindow(), mBall);
	FillIn(GetWindow(), mBackground_down);
	FillIn(GetWindow(), mBackground_up);
	Draw(GetWindow(), GetPreWindow());
	ClearWindow(GetWindow());
	Sleep(33);
}

void UninitMultiPlayer()
{
	switch (mmode)
	{
	case GAMEOVER:
		SetGameInited(false);
		SetState(GAMEOVER);
		break;

	case GAME_END:
		SetGameInited(false);
		SetState(GAME_END);
		break;
		
	default:
		break;
	}
}
