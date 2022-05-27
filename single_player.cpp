#include "single_player.h"
#include "main.h"
#include "draw.h"

Rect sRect1;
Rect sBackground_up;
Rect sBackground_down;
Rect sBackground_right;
Rect sBall;

int sdirection_x;
int sdirection_y;

int smode;

void InitSinglePlayer()
{
	sRect1 = { 0,12,1,4,'*' };
	sBackground_up = { 0,0,80,1,'X' };
	sBackground_down = { 0,23,80,1,'X' };
	sBackground_right = { 79,0,1,24,'X' };
	sBall = { rand() % 38 + 40,rand() % 20 + 2,1,1,'O' };
	sdirection_x = 1;
	sdirection_y = 1;
	smode = -1;
	ClearWindow(GetWindow());
}

void UpdateSinglePlayer()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		sRect1.StartPoint_y += -1;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		sRect1.StartPoint_y += 1;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		sRect1.StartPoint_x += -1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		sRect1.StartPoint_x += 1;
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		smode = GAME_END;
	}

	sBall.StartPoint_x += 1 * sdirection_x;
	sBall.StartPoint_y += 1 * sdirection_y;

	if (sRect1.StartPoint_x > sBackground_right.StartPoint_x - 1)
	{
		sRect1.StartPoint_x = sBackground_right.StartPoint_x - 1;
	}
	if (sRect1.StartPoint_x < 0)
	{
		sRect1.StartPoint_x = 0;
	}
	if (sRect1.StartPoint_y > sBackground_down.StartPoint_y - 4)
	{
		sRect1.StartPoint_y = sBackground_down.StartPoint_y - 4;
	}
	if (sRect1.StartPoint_y < sBackground_up.StartPoint_y + 1)
	{
		sRect1.StartPoint_y = sBackground_up.StartPoint_y + 1;
	}

	if ((sBall.StartPoint_x == sRect1.StartPoint_x + 1) && 
		(sBall.StartPoint_y >= sRect1.StartPoint_y) && 
		(sBall.StartPoint_y <= sRect1.StartPoint_y + sRect1.Height))
	{
		sdirection_x *= -1;
	}
	if ((sBall.StartPoint_y <= sBackground_up.StartPoint_y + 1) || 
		(sBall.StartPoint_y >= sBackground_down.StartPoint_y - 1))
	{
		sdirection_y *= -1;
	}
	if (sBall.StartPoint_x >= sBackground_right.StartPoint_x - 1)
	{
		sdirection_x *= -1;
	}
	if (sBall.StartPoint_x < 0)
	{
		smode = GAMEOVER;
	}
}

void DrawSinglePlayer()
{
	FillIn(GetWindow(), sRect1);
	FillIn(GetWindow(), sBall);
	FillIn(GetWindow(), sBackground_down);
	FillIn(GetWindow(), sBackground_up);
	FillIn(GetWindow(), sBackground_right);
	Draw(GetWindow(), GetPreWindow());
	ClearWindow(GetWindow());
	Sleep(33);
}

void UninitSinglePlayer()
{
	
	switch (smode)
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
