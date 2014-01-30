/******************************************************************************

	PortalGameModel.h
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#pragma once

#include "Sprite.h"

const int kMaxLives = 8;

enum SpriteID
{
	kInvalidSpriteID	= ' ',
	kShipSpriteID		= 0,
	kPortalSpriteID,
	kAlien1SpriteID,
	kAlien2SpriteID,
	kAsteroid1SpriteID,
	kAsteroid2SpriteID,
	kAsteroid3SpriteID,
	kAsteroid4SpriteID,
	
	kSpriteCount = 8	// Keep this updated
};

enum GameState
{
	kGSGameReset,
	kGSGameReady,
	kGSGameRunning,
	kGSShipDestroyed,
	kGSGameOver,
	kGSInPortal
};

class PortalGameModel
{
private:
	volatile GameState mGameState;
	volatile uint8_t mCurGameBoard[kNumRows][kNumCols];
	Sprite* mSpriteList[kSpriteCount];
	int mCurrentLevel;
	int mLivesRemaining;
	
	void Clear(void);
	int RandRow() { return random(kTopRow, kBottomRow); }
	int RandCol() { return random(kLeftCol, kRightCol); }
	Position RandomFreePosition(void);
	
public:
	PortalGameModel(void);
	~PortalGameModel(void);
	void Init(void);
	
	void MoveSpriteToPosition(uint8_t spriteID, Position newPos);
	void MoveSpriteToPosition(uint8_t spriteID, int row, int col);
	void MoveSpriteLeft(uint8_t spriteID);
	void MoveSpriteRight(uint8_t spriteID);
	void MoveSpriteUp(uint8_t spriteID);
	void MoveSpriteDown(uint8_t spriteID);
		
	void ResetLevel(void);
	int MaxLives(void) { return kMaxLives; }
	int LivesRemaining(void) { return mLivesRemaining; }
	int CurrentLevel(void) { return mCurrentLevel; }
	volatile GameState CurrentGameState(void) { return mGameState; }
	void SetGameState(GameState gs);
	
	int NumSprites(void) { return kSpriteCount; }
	Sprite* SpriteWithID(uint8_t spriteID) { return mSpriteList[spriteID]; }
	Sprite* SpriteAtPosition(int row, int col);
};


/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
