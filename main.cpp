/*******************************************************************************
* �^�C�g��:		���C���v���O����
* �v���O������:	main.cpp
* �쐬��:			�љ��
* �쐬��:			2022/05/18
*******************************************************************************/

/*******************************************************************************
* scanf ��warning�h�~
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"
#include "title.h"
#include "single_player.h"
#include "multi_player.h"
#include "gameover.h"

/*******************************************************************************
* �\���̒�`
*******************************************************************************/

/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
int g_State;
char g_Window[WINDOW_HEIGHT][WINDOW_WIDTH] = { ' ' };
char g_preWindow[WINDOW_HEIGHT][WINDOW_WIDTH] = { ' ' };
bool isGameInited;

/*******************************************************************************
 �֐���:	int main( void )
 ����:		void
 �߂�l:	����I��: int�^�� 0
 ����:		���C���֐�
*******************************************************************************/
int main()
{
	Init();
	
	while (GetState() < GAME_END)
	{
		if (!IsGameInited())
		{
			GameInit();
			SetGameInited(true);
		}
		
		Update();
		
		Draw();
		
		Uninit();
	}
	
	return 0;
}

void Init()
{
	srand((unsigned)time(NULL));
	isGameInited = false;
}

void GameInit()
{
	
	switch (GetState())
	{
	case GAME_TITLE:
		InitTitle();
		break;

	case SINGLE_PLAYER_MODE:
		InitSinglePlayer();
		break;
		
	case MULTI_PLAYER_MODE:
		InitMultiPlayer();
		break;
		
	case GAMEOVER:
		InitGameOver();
		break;
	}
}

void Update()
{
	switch (GetState())
	{
	case GAME_TITLE:
		UpdateTitle();
		break;
		
	case SINGLE_PLAYER_MODE:
		UpdateSinglePlayer();
		break;
	
	case MULTI_PLAYER_MODE:
		UpdateMultiPlayer();
		break;
		
	case GAMEOVER:
		UpdateGameOver();
		break;
	
	default:
		break;
	}
}

void Draw()
{
	switch (GetState())
	{
	case GAME_TITLE:
		DrawTitle();
		break;

	case SINGLE_PLAYER_MODE:
		DrawSinglePlayer();
		break;
		
	case MULTI_PLAYER_MODE:
		DrawMultiPlayer();
		break;
		
	case GAMEOVER:
		DrawGameOver();
		break;
		
	default:
		break;

	}
}

void Uninit()
{
	switch (GetState())
	{
	case GAME_TITLE:
		UninitTitle();
		break;
		
	case SINGLE_PLAYER_MODE:
		UninitSinglePlayer();
		break;

	case MULTI_PLAYER_MODE:
		UninitMultiPlayer();
		break;
		
	case GAMEOVER:
		UninitGameOver();
		break;
		
	default:
		break;
	}
}

int GetState()
{
	return g_State;
}

void SetState(int state)
{
	g_State = state;
}

char* GetWindow()
{
	return *g_Window;
}

char* GetPreWindow()
{
	return *g_preWindow;
}

bool IsGameInited()
{
	return isGameInited;
}

void SetGameInited(bool is_game_inited)
{
	isGameInited = is_game_inited;
}