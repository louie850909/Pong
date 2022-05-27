#include "draw.h"

/*******************************************************************************
 �֐���:		void Draw(char* Window_p)
 ����:		char* Window_p
 �߂�l:		�Ȃ�
 ����:		window���̓��e����ʂɕ\������
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

/*******************************************************************************
 �֐���:		void FillIn(char* Window_p, Rect rect)
 ����:		char* Window_p, Rect rect
 �߂�l:		�Ȃ�
 ����:		rect��console buffer�ɓ�������
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

void ClearWindow(char* window)
{
	for (int row = 0; row < WINDOW_HEIGHT; row++)
	{
		for (int column = 0; column < WINDOW_WIDTH; column++)
		{
			*(window + column + (WINDOW_WIDTH * row)) = ' ';
		}
	}
}
