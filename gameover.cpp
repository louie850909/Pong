#include "gameover.h"
#include "main.h"
#include "draw.h"

WordPhrase gGameOver;
WordPhrase gSecondTitle;

int gmode;

void InitGameOver()
{
	gGameOver = { 35,12,"Game Over" };
	gSecondTitle = { 28,13,"Press Space to Continue" };
	ClearWindow(GetWindow());
	gmode = -1;
}

void UpdateGameOver()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		gmode = GAME_TITLE;
	}
}

void DrawGameOver()
{
	FillIn(GetWindow(), gGameOver);
	FillIn(GetWindow(), gSecondTitle);
	Draw(GetWindow(), GetPreWindow());
	ClearWindow(GetWindow());
	Sleep(33);
}

void UninitGameOver()
{
	switch (gmode)
	{
	case GAME_TITLE:
		SetGameInited(false);
		SetState(GAME_TITLE);
		break;
		
	default:
		break;
	}
}
