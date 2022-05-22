#pragma once

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include <stdio.h>
#include <Windows.h>

/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define WINDOW_WIDTH (80)
#define WINDOW_HEIGHT (25)

#define SPACE (0)
#define STAR_MARK (1)
#define BALL_MARK (2)
#define X_MARK (3)

/*******************************************************************************
* 構造体定義
*******************************************************************************/
typedef struct rect
{
	int StartPoint_x;
	int StartPoint_y;
	int Width;
	int Height;
	int Type;
} Rect;

/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
void Draw(int* window, int* prewindow);
void FillIn(int* window, Rect rect);
void setCursorPosition(int x, int y);
void Clear(int* window);

/*******************************************************************************
* グローバル変数
*******************************************************************************/

/*******************************************************************************
 関数名:		void Draw(int* Window_p)
 引数:		int* Window_p
 戻り値:		なし
 説明:		window中の内容を画面に表示する
*******************************************************************************/
void Draw(int* window, int* prewindow)
{
	for (int row = 0; row < WINDOW_HEIGHT; row++)
	{
		for (int column = 0; column < WINDOW_WIDTH; column++)
		{
			if (*(window + column + WINDOW_WIDTH * row) == *(prewindow + column + WINDOW_WIDTH * row))
			{
				continue;
			}

			setCursorPosition(column, row);
			switch (*(window + column + WINDOW_WIDTH * row))
			{
			case SPACE:
				printf(" ");
				break;

			case STAR_MARK:
				printf("*");
				break;

			case BALL_MARK:
				printf("O");
				break;

			case X_MARK:
				printf("X");
				break;
			}

			*(prewindow + column + WINDOW_WIDTH * row) = *(window + column + WINDOW_WIDTH * row);
		}
	}
}

/*******************************************************************************
 関数名:		void FillIn(int* Window_p, Rect rect)
 引数:		int* Window_p, Rect rect
 戻り値:		なし
 説明:		rectをconsole bufferに導入する
*******************************************************************************/
void FillIn(int* window, Rect rect)
{
	for (int row = rect.StartPoint_y; row < rect.StartPoint_y + rect.Height; row++)
	{
		for (int column = rect.StartPoint_x; column < rect.StartPoint_x + rect.Width; column++)
		{
			switch (rect.Type)
			{
			case STAR_MARK:
				*(window + column + WINDOW_WIDTH * row) = STAR_MARK;
				break;

			case BALL_MARK:
				*(window + column + WINDOW_WIDTH * row) = BALL_MARK;
				break;

			case X_MARK:
				*(window + column + WINDOW_WIDTH * row) = X_MARK;
				break;
			}
			
		}
	}
}

void setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

inline void Clear(int* window)
{
	for (int row = 0; row < WINDOW_HEIGHT; row++)
	{
		for (int column = 0; column < WINDOW_WIDTH; column++)
		{
			*(window + column + WINDOW_WIDTH * row) = 0;
		}
	}
}
