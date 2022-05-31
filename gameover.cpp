#include "gameover.h"
#include "main.h"
#include "draw.h"
#include "multi_player.h"

WordPhrase gGameOver;
WordPhrase gSecondTitle;

int gmode;

void InitGameOver()
{
	gGameOver = { 35,12,"Game Over" };
	gSecondTitle = { 29,13,"Press Space to Continue" };
	ClearWindow(GetWindow());
	gmode = -1;
}

void UpdateGameOver()
{
	switch (GetWinner())
	{
	case P1:
		gGameOver = { 35,12,"P1 WIN!" };
		break;
		
	case P2:
		gGameOver = { 35,12,"P2 WIN!" };
		break;
	default:
		break;
	}

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
		SetWinner(0);//set back to no winner
		SetState(GAME_TITLE);
		break;
		
	default:
		break;
	}
}
