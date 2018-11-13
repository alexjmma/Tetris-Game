#pragma once
#ifndef _GAME_
#define _GAME_

#include "Board.h"
#include "Pieces.h"
#include "IO.h"
#include <time.h>

constexpr int wait_time = 700;
class Game
{
public:
	Game (Board * pBoard, Pieces * pPieces, IO * pIO, int pScreenHeight);
	
	void DrawScene();
	void CreateNewPiece();

	int mPosX, mPosY; //Position of piece thats falling down
	int mPiece, mRotation; //Kind and rotation the piece that is falling down

private:
	int mScreenHeight;
	int mNextPosX, mNextPosY;
	int mNextPiece, mNextRotation; 

	Board * mBoard;
	Pieces * mPieces;
	IO * mIO;

	int GetRand(int pA, int pB);
	void InitGame();
	void DrawPiece(int pX, int pY, int pPiece, int pRotation);
	void DrawBoard();
};

#endif // _GAME_

