#include "multi_player.h"
#include "main.h"
#include "draw.h"

int mdirection_x;
int mdirection_y;
int mPlayer1Score;
int mPlayer2Score;

char mstrScore[12];

Rect mRect1;
Rect mRect2;
Rect mBackground_up;
Rect mBackground_down;
Rect mBall;

WordPhrase mP1Score;
WordPhrase mP1ScoreNum;
WordPhrase mP2Score;
WordPhrase mP2ScoreNum;
WordPhrase mTitle;

int mmode;

void InitMultiPlayer()
{
	mmode = GAME_INIT;// MultiPlayer Game Initialized
	mdirection_x = 1;
	mdirection_y = 1;
	mPlayer1Score = 0;
	mPlayer2Score = 0;
	mRect1 = { 0,12,1,4,'*' };
	mRect2 = { 79,12,1,4,'*' };
	mBall = { 20,rand() % 19 + 3,1,1,'O' };
	mBackground_up = { 0,0,80,1,'X' };
	mBackground_down = { 0,23,80,1,'X' };
	mTitle = { 28,13,"Press Space to Start" };

	mP1Score = { 0,24,"P1 Score : " };
	sprintf_s(mstrScore, "%d", mPlayer1Score); //change int to char
	mP1ScoreNum = { 16,24,mstrScore };//store score number

	mP2Score = { 60,24,"P2 Score : " };
	sprintf_s(mstrScore, "%d", mPlayer2Score); //change int to char
	mP2ScoreNum = { 76,24,mstrScore };//store score number

	ClearWindow(GetWindow());
}

void UpdateMultiPlayer()
{
	if (mmode == GAME_INIT) // Only show on when first time get in the game
	{
		while (1)
		{
			if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
				break;
			}
			FillIn(GetWindow(), mTitle);
			DrawMultiPlayer();
		}
		mmode = GAME_RUNNING; // Game Start
	}

	if (mmode == GAME_RESTART)
	{
		mBall = { 39,rand() % 19 + 3,1,1,'O' };
		if (mPlayer1Score > mPlayer2Score)
		{
			mdirection_x = -1;
			mdirection_y = 1;
		}
		else if (mPlayer1Score < mPlayer2Score)
		{
			mdirection_x = 1;
			mdirection_y = -1;
		}
		mmode = GAME_RUNNING;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		mRect2.StartPoint_y += -1;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		mRect2.StartPoint_y += 1;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		mRect2.StartPoint_x += -1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		mRect2.StartPoint_x += 1;
	}
	if (GetAsyncKeyState('W') & 0x8000)
	{
		mRect1.StartPoint_y += -1;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		mRect1.StartPoint_x += -1;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		mRect1.StartPoint_y += 1;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		mRect1.StartPoint_x += 1;
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		mmode = GAME_END;
	}

	mBall.StartPoint_x += 1 * mdirection_x;
	mBall.StartPoint_y += 1 * mdirection_y;

	if (mRect1.StartPoint_x > WINDOW_WIDTH / 2 - 1)
	{
		mRect1.StartPoint_x = WINDOW_WIDTH / 2 - 1;
	}
	if (mRect1.StartPoint_x < 0)
	{
		mRect1.StartPoint_x = 0;
	}
	if (mRect1.StartPoint_y > mBackground_down.StartPoint_y - 4)
	{
		mRect1.StartPoint_y = mBackground_down.StartPoint_y - 4;
	}
	if (mRect1.StartPoint_y < mBackground_up.StartPoint_y + 1)
	{
		mRect1.StartPoint_y = mBackground_up.StartPoint_y + 1;
	}
	if (mRect2.StartPoint_x < WINDOW_WIDTH / 2)
	{
		mRect2.StartPoint_x = WINDOW_WIDTH / 2;
	}
	if (mRect2.StartPoint_x > 79)
	{
		mRect2.StartPoint_x = 79;
	}
	if (mRect2.StartPoint_y > mBackground_down.StartPoint_y - 4)
	{
		mRect2.StartPoint_y = mBackground_down.StartPoint_y - 4;
	}
	if (mRect2.StartPoint_y < mBackground_up.StartPoint_y + 1)
	{
		mRect2.StartPoint_y = mBackground_up.StartPoint_y + 1;
	}

	if ((mBall.StartPoint_x == mRect1.StartPoint_x + 1) && 
		(mBall.StartPoint_y >= mRect1.StartPoint_y) && 
		(mBall.StartPoint_y <= mRect1.StartPoint_y + mRect1.Height))
	{
		mdirection_x *= -1;
	}
	if ((mBall.StartPoint_x == mRect2.StartPoint_x - 1) && 
		(mBall.StartPoint_y >= mRect2.StartPoint_y) && 
		(mBall.StartPoint_y <= mRect2.StartPoint_y + mRect2.Height))
	{
		mdirection_x *= -1;
	}
	if (mBall.StartPoint_y <= mBackground_up.StartPoint_y + 1 || 
		mBall.StartPoint_y >= mBackground_down.StartPoint_y - 1)
	{
		mdirection_y *= -1;
	}
	if (mBall.StartPoint_x <= 0)
	{
		mBall.StartPoint_x = 0;

		mmode = GAME_RESTART;

		mPlayer2Score += 1;
		sprintf_s(mstrScore, "%d", mPlayer2Score);
		mP2ScoreNum.word_phrase = mstrScore;
	}
	if (mBall.StartPoint_x >= 79)
	{
		mBall.StartPoint_x = 79;
		
		mmode = GAME_RESTART;

		mPlayer1Score += 1;
		sprintf_s(mstrScore, "%d", mPlayer1Score);
		mP1ScoreNum.word_phrase = mstrScore;
	}

	/*if ((abs(mPlayer1Score - mPlayer2Score) >= 2) && (mPlayer2Score > 6))
	{
		
	}*/
}

void DrawMultiPlayer()
{
	FillIn(GetWindow(), mRect1);
	FillIn(GetWindow(), mRect2);
	FillIn(GetWindow(), mBall);
	FillIn(GetWindow(), mBackground_down);
	FillIn(GetWindow(), mBackground_up);
	FillIn(GetWindow(), mP1Score);
	FillIn(GetWindow(), mP1ScoreNum);
	FillIn(GetWindow(), mP2Score);
	FillIn(GetWindow(), mP2ScoreNum);
	Draw(GetWindow(), GetPreWindow());
	ClearWindow(GetWindow());
	Sleep(33);
}

void UninitMultiPlayer()
{
	switch (mmode)
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
