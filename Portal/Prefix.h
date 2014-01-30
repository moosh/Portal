/******************************************************************************

	Prefix.h
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#pragma once

#include "Arduino.h"

const int kNumRows			= 4;
const int kNumCols			= 16;
const int kLeftCol			= 0;
const int kTopRow			= 0;
const int kRightCol 		= kNumCols - 1;
const int kBottomRow		= kNumRows - 1;
const int kBoardSize		= kNumCols * kNumRows;
const int kCellWidth 		= 5;
const int kCellHeight		= 8;

const uint8_t kClearCharacter	= ' ';

const int kNoButton		= -1;
const int kLeftButton	= 11;
const int kRightButton	= 12;
const int kUpButton		= 14;
const int kDownButton	= 15;
const int kButtonCount	= 4;

typedef struct
{
	int col;
	int row;
}Position;

typedef struct
{
	int x, y;
}Vec2;

typedef struct
{
	Position position;
	Vec2 dirVec;
}PositionVec;

/******************************************************************************

******************************************************************************/
bool PositionsEqual(Position a, Position b);
Position NormalizePosition(Position& inOutPos);
bool IsPositionValid(Position pos);

/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
