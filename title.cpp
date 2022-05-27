#include "title.h"
#include "main.h"
#include "draw.h"

WordPhrase tTitle;
WordPhrase tSecondTitle;
WordPhrase tSingleplayer;
WordPhrase tMultiplayer;
WordPhrase tQuitGame;
Rect tarrow;
int tmode;

void InitTitle(void)
{
	tTitle = { 33,8, "Ping Pong" };
	tSecondTitle = { 29,13,"Press Enter to Start" };
	tarrow = { 30,15,1,1,'>' };
	tSingleplayer = { 32,15,"Single Player" };
	tMultiplayer = { 32,16,"Multi Player" };
	tQuitGame = { 32,17,"Quit Game" };
	tmode = -1;
	ClearWindow(GetWindow());
	
}

void UninitTitle(void)
{
	switch (tmode)
	{
	case SINGLE_PLAYER_MODE:
		SetGameInited(false);
		SetState(SINGLE_PLAYER_MODE);
		break;
		
	case MULTI_PLAYER_MODE:
		SetGameInited(false);
		SetState(MULTI_PLAYER_MODE);
		break;
		
	case GAME_END:
		SetGameInited(false);
		SetState(GAME_END);
		break;
		
	default:
		break;
	}
}

void UpdateTitle(void)
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		tarrow.StartPoint_y = ((tarrow.StartPoint_y - 1) % 3) + 15;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		tarrow.StartPoint_y = ((tarrow.StartPoint_y + 1) % 3) + 15;
	}
	if ((GetAsyncKeyState(VK_RETURN) & 0x8000) && (tarrow.StartPoint_y == 15))
	{
		tmode = SINGLE_PLAYER_MODE;
	}
	if ((GetAsyncKeyState(VK_RETURN) & 0x8000) && (tarrow.StartPoint_y == 16))
	{
		tmode = MULTI_PLAYER_MODE;
	}
	if ((GetAsyncKeyState(VK_RETURN) & 0x8000) && (tarrow.StartPoint_y == 17))
	{
		tmode = GAME_END;
	}
}

void DrawTitle(void)
{
	FillIn(GetWindow(), tTitle);
	FillIn(GetWindow(), tSecondTitle);
	FillIn(GetWindow(), tarrow);
	FillIn(GetWindow(), tSingleplayer);
	FillIn(GetWindow(), tMultiplayer);
	FillIn(GetWindow(), tQuitGame);
	Draw(GetWindow(), GetPreWindow());
	ClearWindow(GetWindow());
	Sleep(33);
}
