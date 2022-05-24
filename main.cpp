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
#define KB_UP (72)
#define KB_DOWN (80)
#define KB_LEFT (75)
#define KB_RIGHT (77)
#define KB_ESCAPE (27)
#define KB_ENTER (13)
#define KB_W (119)
#define KB_A (97)
#define KB_S (115)
#define KB_D (100)

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
	int state = 0;
	srand((unsigned)time(NULL));

	char Window[WINDOW_HEIGHT][WINDOW_WIDTH] = { ' ' };

	char preWindow[WINDOW_HEIGHT][WINDOW_WIDTH] = { ' ' };

	int key_code = 0;

	int direction_x = 1;
	int direction_y = 1;

	Rect rect1;
	Rect rect2;
	Rect background_up;
	Rect background_down;
	Rect background_left;
	Rect background_right;
	Rect ball;
	Rect arrow;
	WordPhrase Title;
	WordPhrase SecondTitle;
	WordPhrase GameOver;
	WordPhrase Singleplayer;
	WordPhrase Multiplayer;
	WordPhrase QuitGame;
	
	while (1)
	{
		switch (state)
		{
		case 0:
			//初期化
			direction_x = 1;
			direction_y = 1;
			rect1 = { 0,12,1,4,'*' };
			rect2 = { 79,12,1,4,'*' };
			background_up = { 0,0,80,1,'X' };
			background_down = { 0,24,80,1,'X' };
			background_left = { 0,0,1,25,'X' };
			background_right = { 79,0,1,25,'X' };
			Title = { 33,8, "Ping Pong" };
			SecondTitle = { 29,13,"Press Enter to Start" };
			Singleplayer = { 32,15,"Single Player" };
			Multiplayer = { 32,16,"Multi Player" };
			QuitGame = { 32,17,"Quit Game" };
			arrow = { 30,15,1,1,'>' };

		case 1:
			//Start Menu
			
			while (1)
			{
				key_code = 0;

				if (_kbhit())
					key_code = _getch();

				switch (key_code)
				{
				case KB_ENTER:
					break;
				case KB_UP:
					arrow.StartPoint_y = ((arrow.StartPoint_y - 1) % 3) + 15;
					break;
				case KB_DOWN:
					arrow.StartPoint_y = ((arrow.StartPoint_y + 1) % 3) + 15;
					break;
				default:
					break;
				}
				FillIn(*Window, Title);
				FillIn(*Window, SecondTitle);
				FillIn(*Window, arrow);
				FillIn(*Window, Singleplayer);
				FillIn(*Window, Multiplayer);
				FillIn(*Window, QuitGame);
				Draw(*Window, *preWindow);
				Clear(*Window);
				Sleep(33);

				if (key_code == KB_ENTER && arrow.StartPoint_y == 15)
				{
					state = 2;
					break;
				}
				if (key_code == KB_ENTER && arrow.StartPoint_y == 16)
				{
					state = 3;
					break;
				}
				if (key_code == KB_ENTER && arrow.StartPoint_y == 17)
				{
					return 0;
				}
			}

			break;
		case 2:
			//Single Player Game
			ball = { rand() % 39 + 40,rand() % 23 + 2,1,1,'O' };
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

				ball.StartPoint_x += 1 * direction_x;
				ball.StartPoint_y += 1 * direction_y;

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
					state = 4;
					break;
				}

				Sleep(33);
			}

			break;

		case 3:
			//Multi Player Game
			ball = { 39,rand() % 23 + 2,1,1,'O' };
			while (1)
			{
				key_code = 0;

				if (_kbhit())
					key_code = _getch();

				switch (key_code)
				{
				case KB_RIGHT:
					rect2.StartPoint_x += 1;
					break;
				case KB_LEFT:
					rect2.StartPoint_x += -1;
					break;
				case KB_UP:
					rect2.StartPoint_y += -1;
					break;
				case KB_DOWN:
					rect2.StartPoint_y += 1;
					break;
				case KB_D:
					rect1.StartPoint_x += 1;
					break;
				case KB_A:
					rect1.StartPoint_x += -1;
					break;
				case KB_W:
					rect1.StartPoint_y += -1;
					break;
				case KB_S:
					rect1.StartPoint_y += 1;
					break;
				case KB_ESCAPE:
					return 0;
				}

				if (rect1.StartPoint_x > 39)
				{
					rect1.StartPoint_x = 39;
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
				if (rect2.StartPoint_x < 40)
				{
					rect2.StartPoint_x = 40;
				}
				if (rect2.StartPoint_x > 79)
				{
					rect2.StartPoint_x = 79;
				}
				if (rect2.StartPoint_y > 20)
				{
					rect2.StartPoint_y = 20;
				}
				if (rect2.StartPoint_y < 1)
				{
					rect2.StartPoint_y = 1;
				}

				ball.StartPoint_x += 1 * direction_x;
				ball.StartPoint_y += 1 * direction_y;

				if ((ball.StartPoint_x == rect1.StartPoint_x + 1) && (ball.StartPoint_y >= rect1.StartPoint_y) && (ball.StartPoint_y <= rect1.StartPoint_y + rect1.Height))
				{
					direction_x *= -1;
				}
				if ((ball.StartPoint_x == rect2.StartPoint_x - 1) && (ball.StartPoint_y >= rect2.StartPoint_y) && (ball.StartPoint_y <= rect2.StartPoint_y + rect2.Height))
				{
					direction_x *= -1;
				}
				if (ball.StartPoint_y == 1 || ball.StartPoint_y == 23)
				{
					direction_y *= -1;
				}
				if (ball.StartPoint_x < 0)
				{
					ball.StartPoint_x = 0;
					state = 4;
					break;
				}
				if (ball.StartPoint_x > 79)
				{
					ball.StartPoint_x = 79;
					state = 4;
					break;
				}

				Clear(*Window);
				FillIn(*Window, rect1);
				FillIn(*Window, rect2);
				FillIn(*Window, ball);
				FillIn(*Window, background_down);
				FillIn(*Window, background_up);

				Draw(*Window, *preWindow);
				Sleep(33);
			}

			break;

		case 4:
			//Game Over
			while (1)
			{
				GameOver = { 35,12,"Game Over" };
				SecondTitle = { 28,13,"Press Enter to Continue"};
				FillIn(*Window, GameOver);
				FillIn(*Window, SecondTitle);
				Draw(*Window, *preWindow);
				Sleep(33);

				if (_kbhit())
					key_code = _getch();

				if (key_code == KB_ENTER)
				{
					state = 0;
					break;
				}
			}
			break;
		}
	}

	

	return 0;
}
