/******************************************************************************

	PortalGameModel.cpp
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#include "Prefix.h"
#include "PortalGameModel.h"
#include "Ship.h"
#include "Portal.h"
#include "AlienSprite.h"
#include "SolidAsteroid.h"

/******************************************************************************

******************************************************************************/
PortalGameModel::PortalGameModel(void)
{
	Clear();
	mGameState = kGSGameReset;
}

/******************************************************************************

******************************************************************************/
PortalGameModel::~PortalGameModel(void)
{
	Clear();
}

/******************************************************************************

******************************************************************************/
void PortalGameModel::Clear(void)
{
	mGameState = kGSGameOver;
	memset(mSpriteList, 0, sizeof(Sprite*) * kSpriteCount);
	memset((void*)mCurGameBoard, kClearCharacter, kBoardSize);
	mCurrentLevel = 1;
	mLivesRemaining = kMaxLives;
}

/******************************************************************************

******************************************************************************/
Position PortalGameModel::RandomFreePosition(void)
{
	Position pos = {0,0};
	for(;;)
	{
		pos.row = RandRow();
		pos.col = RandCol();
		if (mCurGameBoard[pos.row][pos.col] == kClearCharacter)	// free
			return pos;
	}

	// how did we get here?
	pos.row = pos.col = 0;
	return pos;
}

/******************************************************************************

******************************************************************************/
void PortalGameModel::Init(void)
{
	mSpriteList[kShipSpriteID] 		= new Ship();
	mSpriteList[kPortalSpriteID] 	= new Portal();
	mSpriteList[kAlien1SpriteID] 	= new AlienSprite();
	mSpriteList[kAlien2SpriteID]	= new AlienSprite();
	
	mSpriteList[kAsteroid1SpriteID]	= new SolidAsteroid();
	mSpriteList[kAsteroid2SpriteID]	= new SolidAsteroid();
	mSpriteList[kAsteroid3SpriteID]	= new SolidAsteroid();
	mSpriteList[kAsteroid4SpriteID]	= new SolidAsteroid();
	
	for (int i = 0; i < kSpriteCount; ++i)
		mSpriteList[i]->Init();

	ResetLevel();
}

/******************************************************************************

******************************************************************************/
void PortalGameModel::SetGameState(GameState gs)
{
	if (mGameState == gs) return; // nothing to do
	mGameState = gs;
	
	switch (mGameState)
	{
		case kGSShipDestroyed:
			--mLivesRemaining;
			if (mLivesRemaining == 0) SetGameState(kGSGameOver);
			break;
			
		case kGSGameOver:
			mCurrentLevel = 1;
			mLivesRemaining = kMaxLives;	// start anew
			break;
			
		case kGSInPortal:
			++mCurrentLevel;
			break;
			
		default:
			break;
	}
}

/******************************************************************************

******************************************************************************/
void PortalGameModel::ResetLevel(void)
{
	memset((void*)mCurGameBoard, kClearCharacter, kBoardSize);

	Position randPos;
	for (int i = 0; i < kSpriteCount; ++i)
	{
		randPos = RandomFreePosition();
		MoveSpriteToPosition(i, randPos.row, randPos.col);
	}

	const int kSleepLossPerLevel = 100;
	const int kDefaultSleepTime = 1100;
	int sleepTimeForLevel = kDefaultSleepTime - kSleepLossPerLevel * mCurrentLevel;
	mSpriteList[kShipSpriteID]->SetDirectionVec(0,0);
	mSpriteList[kShipSpriteID]->SetSleepMilliseconds(sleepTimeForLevel);
	mSpriteList[kPortalSpriteID]->SetDirectionVec(0,0);
	mSpriteList[kPortalSpriteID]->SetSleepMilliseconds(sleepTimeForLevel);
	mSpriteList[kAlien1SpriteID]->SetDirectionVec(random() % 2 ? 1 : -1, random() % 2 ? 1 : -1);
	mSpriteList[kAlien1SpriteID]->SetSleepMilliseconds(sleepTimeForLevel);
	mSpriteList[kAlien2SpriteID]->SetDirectionVec(random() % 2 ? 1 : -1, random() % 2 ? 1 : -1);
	mSpriteList[kAlien2SpriteID]->SetSleepMilliseconds(sleepTimeForLevel);
	mSpriteList[kAsteroid1SpriteID]->SetDirectionVec(random() % 2 ? 1 : -1, random() % 2 ? 1 : -1);
	mSpriteList[kAsteroid1SpriteID]->SetSleepMilliseconds(sleepTimeForLevel);
	mSpriteList[kAsteroid2SpriteID]->SetDirectionVec(random() % 2 ? 1 : -1, random() % 2 ? 1 : -1);
	mSpriteList[kAsteroid2SpriteID]->SetSleepMilliseconds(sleepTimeForLevel);
	mSpriteList[kAsteroid3SpriteID]->SetDirectionVec(random() % 2 ? 1 : -1, random() % 2 ? 1 : -1);
	mSpriteList[kAsteroid3SpriteID]->SetSleepMilliseconds(sleepTimeForLevel);
	mSpriteList[kAsteroid4SpriteID]->SetDirectionVec(random() % 2 ? 1 : -1, random() % 2 ? 1 : -1);
	mSpriteList[kAsteroid4SpriteID]->SetSleepMilliseconds(sleepTimeForLevel);
}

/******************************************************************************

******************************************************************************/
void PortalGameModel::MoveSpriteToPosition(uint8_t spriteID, int row, int col)
{
	Position newPos;
	newPos.row = row;
	newPos.col = col;
	MoveSpriteToPosition(spriteID, newPos);
}

/******************************************************************************

******************************************************************************/
void PortalGameModel::MoveSpriteToPosition(uint8_t spriteID, Position newPos)
{
	Sprite* sprite = mSpriteList[spriteID];
	
	NormalizePosition(newPos);
	
	PositionVec curPos = sprite->CurPositionVec();
		
	if (IsPositionValid(curPos.position) && ((mCurGameBoard[curPos.position.row][curPos.position.col] == spriteID)))
	{
		// Clean up our soon-to-be previous position
		mCurGameBoard[curPos.position.row][curPos.position.col] = kClearCharacter;
	}

	sprite->SetCurPosition(newPos);
	
	// See if sprite has collided with anything
	switch (spriteID)
	{
		case kShipSpriteID:
		{
			switch (mCurGameBoard[newPos.row][newPos.col])
			{
				case kPortalSpriteID:
					SetGameState(kGSInPortal);
					break;
				
				case kAlien1SpriteID:
				case kAlien2SpriteID:
				case kAsteroid1SpriteID:
				case kAsteroid2SpriteID:
				case kAsteroid3SpriteID:
				case kAsteroid4SpriteID:
					SetGameState(kGSShipDestroyed);
					break;
					
				default:
					break;
			}
			break;
		}

		case kPortalSpriteID:
		{
			if (mCurGameBoard[newPos.row][newPos.col] == kShipSpriteID)
				SetGameState(kGSInPortal);
			break;
		}
		
		default:
		{
			if (mCurGameBoard[newPos.row][newPos.col] == kShipSpriteID)
				SetGameState(kGSShipDestroyed);
			break;
		}
	}
	
	mCurGameBoard[newPos.row][newPos.col] = spriteID;
}

/******************************************************************************

******************************************************************************/
void PortalGameModel::MoveSpriteLeft(uint8_t spriteID)
{
	PositionVec newPos, prevPos;
	Sprite* sprite = mSpriteList[spriteID];
	prevPos = sprite->CurPositionVec();
	
	newPos.position.row = prevPos.position.row;
	newPos.position.col = prevPos.position.col - 1;
	MoveSpriteToPosition(spriteID, newPos.position);
}

/******************************************************************************

******************************************************************************/
void PortalGameModel::MoveSpriteRight(uint8_t spriteID)
{
	PositionVec newPos, prevPos;
	Sprite* sprite = mSpriteList[spriteID];
	prevPos = sprite->CurPositionVec();
	
	newPos.position.row = prevPos.position.row;
	newPos.position.col = prevPos.position.col + 1;
	MoveSpriteToPosition(spriteID, newPos.position);
}

/******************************************************************************

******************************************************************************/
void PortalGameModel::MoveSpriteUp(uint8_t spriteID)
{
	PositionVec newPos, prevPos;
	Sprite* sprite = mSpriteList[spriteID];
	prevPos = sprite->CurPositionVec();
	
	newPos.position.col = prevPos.position.col;
	newPos.position.row = prevPos.position.row - 1;
	MoveSpriteToPosition(spriteID, newPos.position);
}

/******************************************************************************

******************************************************************************/
void PortalGameModel::MoveSpriteDown(uint8_t spriteID)
{
	PositionVec newPos, prevPos;
	Sprite* sprite = mSpriteList[spriteID];
	prevPos = sprite->CurPositionVec();
	
	newPos.position.col = prevPos.position.col;
	newPos.position.row = prevPos.position.row + 1;
	MoveSpriteToPosition(spriteID, newPos.position);
}

/******************************************************************************

******************************************************************************/
Sprite* PortalGameModel::SpriteAtPosition(int row, int col)
{
	int spriteID = mCurGameBoard[row][col];
	if ((spriteID == kInvalidSpriteID) || (spriteID < 0) || (spriteID >= kSpriteCount))
		return NULL;
	
	return mSpriteList[spriteID];
}

/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
