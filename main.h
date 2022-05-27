#pragma once

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

/*******************************************************************************
* マクロ定義
*******************************************************************************/
enum
{
	INIT,
	GAME_TITLE,
	SINGLE_PLAYER_MODE,
	MULTI_PLAYER_MODE,
	GAMEOVER
};

#define WINDOW_WIDTH (80)
#define WINDOW_HEIGHT (25)
#define MAX_WORD_LENGTH (80)

/*******************************************************************************
* 構造体定義
*******************************************************************************/
typedef struct rect
{
	int StartPoint_x;
	int StartPoint_y;
	int Width;
	int Height;
	char DisplaySymbol;
} Rect;

typedef struct word_phrase
{
	int StartPoint_x;
	int StartPoint_y;
	const char* word_phrase;
} WordPhrase;

/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
void Init();
void Update();
void Draw(char* window, char* prewindow);
void Uninit();

int GetState();
void SetState(int state);


void FillIn(char* window, Rect rect);
void FillIn(char* window, WordPhrase word);
void setCursorPosition(int x, int y);
void Clear(char* window);