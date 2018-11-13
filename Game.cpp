#include "Game.h"
#include <time.h>
#include <iostream>
#include <Windows.h>
using namespace std;
Game::Game(Board *pBoard, Pieces *pPieces, IO *pIO, int pScreenHeight)
{
	mScreenHeight = pScreenHeight;

	// Get the pointer to the Board and Pieces classes
	mBoard = pBoard;
	mPieces = pPieces;
	mIO = pIO;

	// Game initialization
	InitGame();
}

int Game::GetRand(int pA, int pB)
{
	return rand () % (pB - pA + 1) + pA;
}

void Game::InitGame()
{
	srand ((unsigned int) time(NULL));

	mPiece = GetRand(0, 6);
	mRotation = GetRand(0, 3);
	mPosX = (board_width / 2) + mPieces->GetXInitialPosition(mPiece, mRotation);
	mPosY = mPieces->GetYInitialPosition(mPiece, mRotation);

	//Next Piece
	mNextPiece = GetRand(0, 6);
	mNextRotation = GetRand(0, 3);
	mNextPosX = board_width + 5;
	mNextPosY = 5;
}

void Game::CreateNewPiece()
{
	// The new piece
	mPiece = mNextPiece;
	mRotation = mNextRotation;
	mPosX = (board_width / 2) + mPieces->GetXInitialPosition(mPiece, mRotation);
	mPosY = mPieces->GetYInitialPosition(mPiece, mRotation);

	// Random next piece
	mNextPiece = GetRand(0, 6);
	mNextRotation = GetRand(0, 3);
}

void Game::DrawPiece(int pX, int pY, int pPiece, int pRotation)
{
	color mColor;               // Color of the block 

	// Obtain the position in pixel in the screen of the block we want to draw
	int mPixelsX = mBoard->GetXPosInPixels(pX);
	int mPixelsY = mBoard->GetYPosInPixels(pY);

	// Travel the matrix of blocks of the piece and draw the blocks that are filled
	for (int i = 0; i < piece_blocks; i++)
	{
		for (int j = 0; j < piece_blocks; j++)
		{
			// Get the type of the block and draw it with the correct color
			switch (mPieces->GetBlockType(pPiece, pRotation, j, i))
			{
			case 1: mColor = GREEN; break;  // For each block of the piece except the pivot
			case 2: mColor = BLUE; break;   // For the pivot
			}

			if (mPieces->GetBlockType(pPiece, pRotation, j, i) != 0)
				mIO->DrawRectangle(mPixelsX + i * block_size,
					mPixelsY + j * block_size,
					(mPixelsX + i * block_size) + block_size - 1,
					(mPixelsY + j * block_size) + block_size - 1,
					mColor);
		}
	}
}