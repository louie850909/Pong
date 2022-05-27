/*******************************************************************************
* タイトル:		メインプログラム
* プログラム名:	main.cpp
* 作成者:			林劭羲
* 作成日:			2022/05/18
*******************************************************************************/

/*******************************************************************************
* scanf のwarning防止
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
/*******************************************************************************
* 構造体定義
*******************************************************************************/

/*******************************************************************************
* グローバル変数
*******************************************************************************/
int g_State;

/*******************************************************************************
 関数名:	int main( void )
 引数:		void
 戻り値:	正常終了: int型の 0
 説明:		メイン関数
*******************************************************************************/
int main()
{
	
	while (1)
	{
		switch (GetState())
		{
		case 0:
			//初期化
			GetAsyncKeyState(VK_RETURN);
			direction_x = 1;
			direction_y = 1;
			rect1 = { 0,12,1,4,'*' };
			rect2 = { 79,12,1,4,'*' };
			background_up = { 0,0,80,1,'X' };
			background_down = { 0,23,80,1,'X' };
			background_left = { 0,0,1,24,'X' };
			background_right = { 79,0,1,24,'X' };
			Title = { 33,8, "Ping Pong" };
			SecondTitle = { 29,13,"Press Enter to Start" };
			Singleplayer = { 32,15,"Single Player" };
			Multiplayer = { 32,16,"Multi Player" };
			QuitGame = { 32,17,"Quit Game" };
			arrow = { 30,15,1,1,'>' };
			player1_score = 0;
			player2_score = 0;
			Clear(*Window);

		case 1:
			//Start Menu
			while (1)
			{
				if (GetAsyncKeyState(VK_UP))
				{
					arrow.StartPoint_y = ((arrow.StartPoint_y - 1) % 3) + 15;
				}
				if (GetAsyncKeyState(VK_DOWN))
				{
					arrow.StartPoint_y = ((arrow.StartPoint_y + 1) % 3) + 15;
				}
				if ((GetAsyncKeyState(VK_RETURN)) && (arrow.StartPoint_y == 15))
				{
					state = 2;
					break;
				}
				if ((GetAsyncKeyState(VK_RETURN)) && (arrow.StartPoint_y == 16))
				{
					state = 3;
					break;
				}
				if ((GetAsyncKeyState(VK_RETURN)) && (arrow.StartPoint_y == 17))
				{
					return 0;
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

				
			}
			Sleep(100);
			break;
		case 2:
			//Single Player Game
			ball = { rand() % 38 + 40,rand() % 21 + 2,1,1,'O' };

			while (1)
			{
				SecondTitle = { 28,13,"Press Spcae key to Start" };
				FillIn(*Window, rect1);
				FillIn(*Window, background_down);
				FillIn(*Window, background_up);
				FillIn(*Window, background_right);
				FillIn(*Window, SecondTitle);
				Draw(*Window, *preWindow);
				Sleep(33);
				if (GetAsyncKeyState(VK_SPACE))
				{
					Clear(*Window);
					break;
				}
			}

			while (1)
			{
				if (GetAsyncKeyState(VK_UP))
				{
					rect1.StartPoint_y += -1;
				}
				if (GetAsyncKeyState(VK_DOWN))
				{
					rect1.StartPoint_y += 1;
				}
				if (GetAsyncKeyState(VK_LEFT))
				{
					rect1.StartPoint_x += -1;
				}
				if (GetAsyncKeyState(VK_RIGHT))
				{
					rect1.StartPoint_x += 1;
				}
				if (GetAsyncKeyState(VK_ESCAPE))
				{
					return 0;
				}

				ball.StartPoint_x += 1 * direction_x;
				ball.StartPoint_y += 1 * direction_y;

				if (rect1.StartPoint_x > background_right.StartPoint_x - 1)
				{
					rect1.StartPoint_x = background_right.StartPoint_x - 1;
				}
				if (rect1.StartPoint_x < 0)
				{
					rect1.StartPoint_x = 0;
				}
				if (rect1.StartPoint_y > background_down.StartPoint_y - 4)
				{
					rect1.StartPoint_y = background_down.StartPoint_y - 4;
				}
				if (rect1.StartPoint_y < background_up.StartPoint_y + 1)
				{
					rect1.StartPoint_y = background_up.StartPoint_y + 1;
				}

				if (ball.StartPoint_x == rect1.StartPoint_x + 1 && ball.StartPoint_y >= rect1.StartPoint_y && ball.StartPoint_y <= rect1.StartPoint_y + rect1.Height)
				{
					direction_x *= -1;
				}
				if (ball.StartPoint_y <= background_up.StartPoint_y + 1 || ball.StartPoint_y >= background_down.StartPoint_y - 1)
				{
					direction_y *= -1;
				}
				if (ball.StartPoint_x >= background_right.StartPoint_x - 1)
				{
					direction_x *= -1;
				}
				if (ball.StartPoint_x < 0)
				{
					state = 4;
					break;
				}

				Clear(*Window);
				FillIn(*Window, rect1);
				FillIn(*Window, ball);
				FillIn(*Window, background_down);
				FillIn(*Window, background_up);
				FillIn(*Window, background_right);

				Draw(*Window, *preWindow);
				Sleep(33);
			}
			Sleep(100);
			break;

		case 3:
			//Multi Player Game
			ball = { 38,rand() % 21 + 2,1,1,'O' };

			while (1)
			{
				SecondTitle = { 28,13,"Press Spcae key to Start" };
				FillIn(*Window, rect1);
				FillIn(*Window, rect2);
				FillIn(*Window, background_down);
				FillIn(*Window, background_up);
				FillIn(*Window, SecondTitle);
				Draw(*Window, *preWindow);
				Sleep(33);
				if (GetAsyncKeyState(VK_SPACE))
				{
					Clear(*Window);
					break;
				}
			}

			while (1)
			{
				if (GetAsyncKeyState(VK_UP))
				{
					rect2.StartPoint_y += -1;
				}
				if (GetAsyncKeyState(VK_DOWN))
				{
					rect2.StartPoint_y += 1;
				}
				if (GetAsyncKeyState(VK_LEFT))
				{
					rect2.StartPoint_x += -1;
				}
				if (GetAsyncKeyState(VK_RIGHT))
				{
					rect2.StartPoint_x += 1;
				}
				if (GetAsyncKeyState('W'))
				{
					rect1.StartPoint_y += -1;
				}
				if (GetAsyncKeyState('A'))
				{
					rect1.StartPoint_x += -1;
				}
				if (GetAsyncKeyState('S'))
				{
					rect1.StartPoint_y += 1;
				}
				if (GetAsyncKeyState('D'))
				{
					rect1.StartPoint_x += 1;
				}
				if (GetAsyncKeyState(VK_ESCAPE))
				{
					return 0;
				}

				ball.StartPoint_x += 1 * direction_x;
				ball.StartPoint_y += 1 * direction_y;

				if (rect1.StartPoint_x > WINDOW_WIDTH/2 - 1)
				{
					rect1.StartPoint_x = WINDOW_WIDTH/2 - 1;
				}
				if (rect1.StartPoint_x < 0)
				{
					rect1.StartPoint_x = 0;
				}
				if (rect1.StartPoint_y > background_down.StartPoint_y - 4)
				{
					rect1.StartPoint_y = background_down.StartPoint_y - 4;
				}
				if (rect1.StartPoint_y < background_up.StartPoint_y + 1)
				{
					rect1.StartPoint_y = background_up.StartPoint_y + 1;
				}
				if (rect2.StartPoint_x < WINDOW_WIDTH/2)
				{
					rect2.StartPoint_x = WINDOW_WIDTH/2;
				}
				if (rect2.StartPoint_x > 79)
				{
					rect2.StartPoint_x = 79;
				}
				if (rect2.StartPoint_y > background_down.StartPoint_y - 4)
				{
					rect2.StartPoint_y = background_down.StartPoint_y - 4;
				}
				if (rect2.StartPoint_y < background_up.StartPoint_y + 1)
				{
					rect2.StartPoint_y = background_up.StartPoint_y + 1;
				}

				if ((ball.StartPoint_x == rect1.StartPoint_x + 1) && (ball.StartPoint_y >= rect1.StartPoint_y) && (ball.StartPoint_y <= rect1.StartPoint_y + rect1.Height))
				{
					direction_x *= -1;
				}
				if ((ball.StartPoint_x == rect2.StartPoint_x - 1) && (ball.StartPoint_y >= rect2.StartPoint_y) && (ball.StartPoint_y <= rect2.StartPoint_y + rect2.Height))
				{
					direction_x *= -1;
				}
				if (ball.StartPoint_y <= background_up.StartPoint_y + 1 || ball.StartPoint_y >= background_down.StartPoint_y - 1)
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
				SecondTitle = { 28,13,"Press Space to Continue"};
				FillIn(*Window, GameOver);
				FillIn(*Window, SecondTitle);
				Draw(*Window, *preWindow);
				Sleep(33);
				if (GetAsyncKeyState(VK_SPACE))
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

void Init()
{
	srand((unsigned)time(NULL));

	char Window[WINDOW_HEIGHT][WINDOW_WIDTH] = { ' ' };

	char preWindow[WINDOW_HEIGHT][WINDOW_WIDTH] = { ' ' };

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
	int player1_score;
	int player2_score;

	SetState(GAME_TITLE);
}

void Update()
{
	switch (GetState())
	{
	case GAME_TITLE:
		UpdateTitle();
		break;
	}
}

/*******************************************************************************
 関数名:		void Draw(char* Window_p)
 引数:		char* Window_p
 戻り値:		なし
 説明:		window中の内容を画面に表示する
*******************************************************************************/
void Draw(char* window, char* prewindow)
{
	for (int row = 0; row < WINDOW_HEIGHT; row++)
	{
		for (int column = 0; column < WINDOW_WIDTH; column++)
		{
			if (*(window + column + (WINDOW_WIDTH * row)) == *(prewindow + column + (WINDOW_WIDTH * row)))
			{
				continue;
			}

			setCursorPosition(column, row);
			printf("%c", *(window + column + (WINDOW_WIDTH * row)));

			*(prewindow + column + (WINDOW_WIDTH * row)) = *(window + column + (WINDOW_WIDTH * row));
		}
	}
}

void Uninit()
{

}

int GetState()
{
	return g_State;
}

void SetState(int state)
{
	g_State = state;
}

/*******************************************************************************
 関数名:		void FillIn(char* Window_p, Rect rect)
 引数:		char* Window_p, Rect rect
 戻り値:		なし
 説明:		rectをconsole bufferに導入する
*******************************************************************************/
void FillIn(char* window, Rect rect)
{
	for (int row = rect.StartPoint_y; row < rect.StartPoint_y + rect.Height; row++)
	{
		for (int column = rect.StartPoint_x; column < rect.StartPoint_x + rect.Width; column++)
		{
			*(window + column + (WINDOW_WIDTH * row)) = rect.DisplaySymbol;
		}
	}
}

void FillIn(char* window, WordPhrase wordphrase)
{
	size_t length = strlen(wordphrase.word_phrase);
	for (int row = wordphrase.StartPoint_y; row <= wordphrase.StartPoint_y; row++)
	{
		for (int column = wordphrase.StartPoint_x; column < wordphrase.StartPoint_x + length; column++)
		{
			*(window + column + (WINDOW_WIDTH * row)) = *(wordphrase.word_phrase + (column - wordphrase.StartPoint_x));
		}
	}
}

void setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

inline void Clear(char* window)
{
	for (int row = 0; row < WINDOW_HEIGHT; row++)
	{
		for (int column = 0; column < WINDOW_WIDTH; column++)
		{
			*(window + column + (WINDOW_WIDTH * row)) = ' ';
		}
	}
}
