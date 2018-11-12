#include "Board.h"

void Board::InitBoard()
{
	for (int i = 0; i < board_width; i++)
	{
		for (int j = 0; j < board_height; j++)
		{
			mBoard[i][j] = POS_FREE;
		}
	}
}

/*
Storing a Piece:
Paramters
pX: Horionzal Position in blocks
pY: Vertical
pPiece: Piece to draw
pRotation: 1 of 4 roations
*/

void Board::StorePiece(int pX, int pY, int pPiece, int pRotation)
{
	//Store each block of the piece into the board
	for (int i1 = pX, i2 = 0; i1 < pX + piece_blocks; i1++, i2++)
	{
		for (int j1 = pY, j2 = 0; j1 < pY + piece_blocks; j1++, j2++)
		{
			//store only blocks of piece that not holes
			if (mPieces->GetBlockType(pPiece, pRotation, j2, i2) != 0) //"->" to access the pointer mPiece and determine GetBlockType function
			{
				mBoard[i1][j1] = POS_FILLED;
			}
		}
	}
}

//Check if game is over when the upper piece touches the very top of the board
bool Board::IsGameOver()
{
	//first line has blocks = game over
	for (int i = 0; i < board_width; i++)
	{
		if (mBoard[i][0] == POS_FILLED)
		return true;
	}
	return false;
}

void Board::DeleteLine(int pY)
{
	for (int j = pY; j > 0; j--) 
	{
		for (int i = 0; i < board_width; i++) //goes from left to right side of game board until it reaches the end
		{
			mBoard[i][j] = mBoard[i][j - 1]; //goes down one block
		}
	}
}

void Board::DeletePossibleLines()
{
	for (int j = 0; j < board_height; j++)
	{
		int i = 0;
		while (i < board_width)
		{
			if (mBoard[i][j] != POS_FILLED) break;
			i++;
		}

		if (i == board_width) DeleteLine(j);
	}
}

//Determines if the block of the board is full or empty
bool Board::IsFreeBlock(int pX, int pY)
{
	if (mBoard[pX][pY] == POS_FREE)
		return true;
	else
		return false;
}

//pPos = Horizontal Position of block on the board
int Board::GetXPosInPixels(int pPos)
{
	return ((board_position - (block_size * (board_width / 2))) + (pPos * block_size));
}

int Board::GetYPosInPixels(int pPos)
{
	return ((mScreenHeight - (block_size * board_height)) + (pPos * block_size));
}

bool Board::IsPossibleMovement(int pX, int pY, int pPiece, int pRotation)
{
	//Check collision with other pieces and the border of the board
	for (int i1 = pX, i2 = 0; i1 < pX + piece_blocks; i1++, i2++)
	{
		for (int j1 = pY, j2 = 0; j1 < pY + piece_blocks; j1++, j2++)
		{
			//checks if piece is outside the limit of the board
			if (i1 < 0 || i1 > board_width - 1 || j1 > board_height - 1)
			{
				if (mPieces->GetBlockType(pPiece, pRotation, j2, i2) != 0)
					return 0;
			}
			//checks if the pieces collide with a block already stored in the board
			if (j1 >= 0)
			{
				if ((mPieces->GetBlockType(pPiece, pRotation, j2, i2) != 0) && (!IsFreeBlock(i1, j1)))
					return false;
			}
		}
	}
	//if not collision return true
	return true;
}