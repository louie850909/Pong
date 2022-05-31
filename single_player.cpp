#include "single_player.h"
#include "main.h"
#include "draw.h"

Rect sRect1;
Rect sBackground_up;
Rect sBackground_down;
Rect sBackground_right;
Rect sBall;

WordPhrase sTitle;
WordPhrase sScore;
WordPhrase sScoreNum;

int sdirection_x;
int sdirection_y;

int sPlayerScore;
char sstrScore[12];

int smode;

void InitSinglePlayer()
{
	sPlayerScore = 0;
	
	sRect1 = { 0,12,1,4,'*' };
	sBackground_up = { 0,0,80,1,'X' };
	sBackground_down = { 0,23,80,1,'X' };
	sBackground_right = { 79,0,1,24,'X' };
	sBall = { rand() % 38 + 40,rand() % 19 + 3,1,1,'O' };
	sTitle = { 29,13,"Press Space to Start" };

	sScore = { 28,24,"Score : " };
	sprintf_s(sstrScore, "%d", sPlayerScore); //change int to char
	sScoreNum = { 40,24,sstrScore };//store score number

	sdirection_x = 1;
	sdirection_y = 1;
	smode = GAME_INIT;
	
	ClearWindow(GetWindow());
}

void UpdateSinglePlayer()
{
	if (smode == GAME_INIT) // Only show on when first time get in the game
	{
		sBall = { 0,0,1,1,' ' };
		while (1)
		{
			if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
				sBall = { 39,rand() % 19 + 3,1,1,'O' };
				break;
			}
			FillIn(GetWindow(), sTitle);
			DrawSinglePlayer();
		}
		smode = GAME_RUNNING; // Game Start
	}

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
		sPlayerScore += 1;
		sprintf_s(sstrScore, "%d", sPlayerScore);
		sScoreNum.word_phrase = sstrScore;
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
	FillIn(GetWindow(), sScore);
	FillIn(GetWindow(), sScoreNum);
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
