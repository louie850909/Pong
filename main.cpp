/*******************************************************************************
* タイトル:	メインプログラム
* プログラム名:	main.cpp
* 作成者:		林劭羲
* 作成日:			2022/05/18
*******************************************************************************/

/*******************************************************************************
* scanf のwarning防止
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include "draw.h"

/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define KB_UP 72
#define KB_DOWN 80
#define KB_LEFT 75
#define KB_RIGHT 77
#define KB_ESCAPE 27

/*******************************************************************************
* 構造体定義
*******************************************************************************/

/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/


/*******************************************************************************
* グローバル変数
*******************************************************************************/


/*******************************************************************************
 関数名:	int main( void )
 引数:		void
 戻り値:	正常終了: int型の 0
 説明:		メイン関数
*******************************************************************************/
int main()
{
	srand((unsigned)time(NULL));

	int Window[WINDOW_HEIGHT][WINDOW_WIDTH] = { 0 };

	int preWindow[WINDOW_HEIGHT][WINDOW_WIDTH] = { 0 };

	int key_code = 0;

	int direction_x = 1;
	int direction_y = 1;

	Rect rect1 = { 0,1,1,4,STAR_MARK };
	Rect background_up = { 0,0,80,1,X_MARK };
	Rect background_down = { 0,24,80,1,X_MARK };
	Rect background_left = { 0,0,1,25,X_MARK };
	Rect background_right = { 79,0,1,25,X_MARK };
	Rect ball = { rand() % 39 + 40,rand() % 23+1,1,1,BALL_MARK };
	int direction1 = 1;

	while (1)
	{
		key_code = 0;

		if (_kbhit())
			key_code = _getch();

		switch (key_code)
		{
		case KB_RIGHT:
			rect1.StartPoint_x += 1;
			break;
		case KB_LEFT:
			rect1.StartPoint_x += -1;
			break;
		case KB_UP:
			rect1.StartPoint_y += -1;
			break;
		case KB_DOWN:
			rect1.StartPoint_y += 1;
			break;
		case KB_ESCAPE:
			return 0;
		}


		Clear(*Window);

		FillIn(*Window, rect1);
		FillIn(*Window, ball);
		FillIn(*Window, background_down);
		FillIn(*Window, background_up);
		//FillIn(*Window, background_left);
		FillIn(*Window, background_right);

		Draw(*Window, *preWindow);

		

		if (rect1.StartPoint_x > 78)
		{
			rect1.StartPoint_x = 78;
		}
		if (rect1.StartPoint_x < 0)
		{
			rect1.StartPoint_x = 0;
		}
		if (rect1.StartPoint_y > 20)
		{
			rect1.StartPoint_y = 20;
		}
		if (rect1.StartPoint_y < 1)
		{
			rect1.StartPoint_y = 1;
		}

		if (ball.StartPoint_x == rect1.StartPoint_x + 1 && ball.StartPoint_y >= rect1.StartPoint_y && ball.StartPoint_y <= rect1.StartPoint_y + rect1.Height)
		{
			direction_x *= -1;
		}
		if (ball.StartPoint_y == 1 || ball.StartPoint_y == 23)
		{
			direction_y *= -1;
		}
		if (ball.StartPoint_x == 78)
		{
			direction_x *= -1;
		}
		if (ball.StartPoint_x < 0)
		{
			return 0;
		}


		ball.StartPoint_x += 1 * direction_x;
		ball.StartPoint_y += 1 * direction_y;

		Sleep(33);
	}

	return 0;
}
