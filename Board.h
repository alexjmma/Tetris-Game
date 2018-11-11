#pragma once
#define _BOARD_

#include "Pieces.h"

//Defines for Piece Sizes
constexpr int board_line_width = 6; //Width of each of the two lines that delimit the board;
constexpr int block_size = 16; //Width and height of each block of a piece;
constexpr int board_position = 320; //Center Position of the board from the left of the screen;
constexpr int board_width = 10;
constexpr int board_height = 20;
constexpr int min_vertical_margin = 20;
constexpr int min_horizontal_margin = 20;
constexpr int piece_blocks = 5;
class Board
{
public:
	Board(Pieces *pPieces, int pScreenHieght);
	int GetXPosInPixels(int pPost);
	int GetYPosInPixels(int pPost);
	bool IsFreeBlock(int pX, int pY);
	bool IsPossibleMovement(int pX, int pY, int pPiece, int pRotation);
	void StorePiece(int pX, int pY, int pPiece, int pRotation);
	void DeletePossibleLines();
	bool IsGameOver();

private:
	enum {POS_FREE, POS_FILLED}; //user assigned data type
	int mBoard[board_width][board_height];
	Pieces *mPieces; //pointer
	int mScreenHeight;

	void InitBoard();
	void DeleteLine(int pY);
	~Board();
};



