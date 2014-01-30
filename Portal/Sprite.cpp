/******************************************************************************

	Sprite.cpp
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#include "Prefix.h"
#include "Sprite.h"

/******************************************************************************

******************************************************************************/
Sprite::Sprite(void)
{
	Clear();
}

/******************************************************************************

******************************************************************************/
Sprite::~Sprite(void)
{
	Clear();
}

/******************************************************************************

******************************************************************************/
void Sprite::Clear(void)
{
	mCurCellIdx			= 0;
	mCellCount			= 0;
	mSpriteSheet		= NULL;
	mLCDCharacter		= 0;
	mSleepMilliseconds	= 0;
	mCurPositionVec.position.row	= -1;
	mCurPositionVec.position.col	= -1;
	mCurPositionVec.dirVec.x		= -1;
	mCurPositionVec.dirVec.y		= -1;
}

/******************************************************************************

******************************************************************************/
void Sprite::InitSpriteSheet(const uint8_t* spriteSheet, int cellCount, int lcdCharacter)
{
	mCurCellIdx		= 0;
	mSpriteSheet 	= spriteSheet;
	mCellCount 		= cellCount;
	mLCDCharacter	= lcdCharacter;
}

/******************************************************************************

******************************************************************************/
void Sprite::AdvanceState(void)
{
}

/******************************************************************************

******************************************************************************/
PositionVec Sprite::NextPositionVec(void)
{
	PositionVec nextPos = CurPositionVec();
	
	nextPos.position.row += nextPos.dirVec.y;
	if (nextPos.position.row < kTopRow)
	{
		nextPos.position.row	= 2 * kTopRow - nextPos.position.row;
		nextPos.dirVec.y 		= -nextPos.dirVec.y;
	}
	else if (nextPos.position.row > kBottomRow)
	{
		nextPos.position.row	= 2 * kBottomRow - nextPos.position.row;
		nextPos.dirVec.y 		= -nextPos.dirVec.y;
	}
	
	nextPos.position.col += nextPos.dirVec.x;
	if (nextPos.position.col < kLeftCol)
	{
		nextPos.position.col	= 2 * kLeftCol - nextPos.position.col;
		nextPos.dirVec.x 		= -nextPos.dirVec.x;
	}
	else if (nextPos.position.col > kRightCol)
	{
		nextPos.position.col	= 2 * kRightCol - nextPos.position.col;
		nextPos.dirVec.x 		= -nextPos.dirVec.x;
	}
	
	return nextPos;
}

/******************************************************************************

******************************************************************************/
const uint8_t* Sprite::CurrentSpriteBitmap(void)
{
	return &(mSpriteSheet[mCurCellIdx * kCellHeight]);
}

/******************************************************************************

******************************************************************************/
const uint8_t* Sprite::NextSpriteBitmap(void)
{
	const uint8_t* spriteBuf = &(mSpriteSheet[mCurCellIdx * kCellHeight]);
	mCurCellIdx++; if (mCurCellIdx >= mCellCount) mCurCellIdx = 0;
	return spriteBuf;
}

/******************************************************************************

******************************************************************************/
const uint8_t* Sprite::PrevSpriteBitmap(void)
{
	const uint8_t* spriteBuf = &(mSpriteSheet[mCurCellIdx * kCellHeight]);
	mCurCellIdx--; if (mCurCellIdx < 0) mCurCellIdx = mCellCount - 1;
	return spriteBuf;
}

/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
