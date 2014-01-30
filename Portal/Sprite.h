/******************************************************************************

	Sprite.h
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#pragma once

class Sprite
{
private:
	int mCurCellIdx;
	int mCellCount;
	PositionVec mCurPositionVec;
	int mSleepMilliseconds; // Milliseconds beween moves
	
	const uint8_t* mSpriteSheet;
	uint8_t	mLCDCharacter;
	
protected:
	void Clear(void);
	void InitSpriteSheet(const uint8_t* spriteSheet, int cellCount, int lcdCharacter);
	
public:
	Sprite(void);
	~Sprite(void);
	
	virtual void Init(void) = 0;
	virtual void AdvanceState(void);
	PositionVec CurPositionVec(void) { return mCurPositionVec; }
	void SetCurPosition(Position pos) { mCurPositionVec.position = pos; }
	PositionVec NextPositionVec(void);
	int SleepMilliseconds(void) { return mSleepMilliseconds; }
	void SetSleepMilliseconds(int sleep) { mSleepMilliseconds = sleep; }
	
	void SetDirectionVec(Vec2 dirVec) { mCurPositionVec.dirVec = dirVec; }
	void SetDirectionVec(int x, int y) { mCurPositionVec.dirVec.x = x; mCurPositionVec.dirVec.y = y; }
		
	const uint8_t LCDCharacter(void) { return mLCDCharacter; }
	const uint8_t* CurrentSpriteBitmap(void);
	const uint8_t* NextSpriteBitmap(void);
	const uint8_t* PrevSpriteBitmap(void);
};

/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
