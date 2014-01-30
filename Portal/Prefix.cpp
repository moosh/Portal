/******************************************************************************

	Prefix.cpp
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#pragma once

#include "Prefix.h"

/******************************************************************************

******************************************************************************/
bool PositionsEqual(Position a, Position b)
{
	return ((a.row == b.row) && (a.col == b.col));
}

/******************************************************************************

******************************************************************************/
Position NormalizePosition(Position& inOutPos)
{
	if (inOutPos.col < kLeftCol) 		inOutPos.col = kRightCol;
	else if (inOutPos.col > kRightCol)	inOutPos.col = 0;
	if (inOutPos.row < kTopRow)			inOutPos.row = kBottomRow;
	else if (inOutPos.row > kBottomRow)	inOutPos.row = 0;
}

/******************************************************************************

******************************************************************************/
bool IsPositionValid(Position pos)
{
	if (pos.col < kLeftCol) 	return false;
	if (pos.col > kRightCol)	return false;
	if (pos.row < kTopRow)		return false;
	if (pos.row > kBottomRow)	return false;
	
	return true;
}

/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/