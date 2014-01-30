/******************************************************************************

	PortalGameController.cpp
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#include "Prefix.h"
#include "PortalGameController.h"

/******************************************************************************

******************************************************************************/
PortalGameController::PortalGameController(void)
{
	Clear();
}

/******************************************************************************

******************************************************************************/
PortalGameController::~PortalGameController(void)
{
	Clear();
}

/******************************************************************************

******************************************************************************/
void PortalGameController::Clear(void)
{
	mModel 	= NULL;
	mView	= NULL;
	mButtons = NULL;
}

/******************************************************************************

******************************************************************************/
void PortalGameController::Init(PortalGameModel* model, PortalGameView* view)
{
	const int kShortestSpriteDelay = 300;
	const int kLongestSpriteDelay = 900;
	
	mModel = model;
	mView = view;
	mButtons = ButtonDebouncer::SharedInstance();
}

/******************************************************************************

******************************************************************************/
void PortalGameController::QueueSprites(void)
{
	mQueue.removeAll();
	mQueue.scheduleFunction(AdvanceSpriteCB, "Ship", 0, mModel->SpriteWithID(kShipSpriteID)->SleepMilliseconds(), kShipSpriteID, this);
	mQueue.scheduleFunction(AdvanceSpriteCB, "Portal", 0, mModel->SpriteWithID(kPortalSpriteID)->SleepMilliseconds(), kPortalSpriteID, this);
	mQueue.scheduleFunction(AdvanceSpriteCB, "Alien1", 0, mModel->SpriteWithID(kShipSpriteID)->SleepMilliseconds(), kAlien1SpriteID, this);
	mQueue.scheduleFunction(AdvanceSpriteCB, "Alien2", 0, mModel->SpriteWithID(kAlien1SpriteID)->SleepMilliseconds(), kAlien2SpriteID, this);
	mQueue.scheduleFunction(AdvanceSpriteCB, "Aster1", 0, mModel->SpriteWithID(kAsteroid1SpriteID)->SleepMilliseconds(), kAsteroid1SpriteID, this);
	mQueue.scheduleFunction(AdvanceSpriteCB, "Aster2", 0, mModel->SpriteWithID(kAsteroid2SpriteID)->SleepMilliseconds(), kAsteroid2SpriteID, this);
	mQueue.scheduleFunction(AdvanceSpriteCB, "Aster3", 0, mModel->SpriteWithID(kAsteroid3SpriteID)->SleepMilliseconds(), kAsteroid3SpriteID, this);
	mQueue.scheduleFunction(AdvanceSpriteCB, "Aster4", 0, mModel->SpriteWithID(kAsteroid4SpriteID)->SleepMilliseconds(), kAsteroid4SpriteID, this);
	mQueue.scheduleFunction(AdvanceSpriteCB, "Portal", 0, mModel->SpriteWithID(kPortalSpriteID)->SleepMilliseconds(), kPortalSpriteID, this);
}

/******************************************************************************

******************************************************************************/
int PortalGameController::AdvanceSpriteCB(unsigned long now, int message, void* ctx)
{
	PortalGameController* pthis = (PortalGameController*)ctx;
	if (!pthis) return 0;
	
	uint8_t spriteID = (uint8_t)message;
	pthis->AdvanceSprite(spriteID);
}

/******************************************************************************

******************************************************************************/
int PortalGameController::AdvanceSprite(uint8_t spriteID)
{
	Sprite* sprite = mModel->SpriteWithID(spriteID);
	if (!sprite) return 0;
	
	PositionVec curPos, nextPos;
	curPos	= sprite->CurPositionVec();
	nextPos = sprite->NextPositionVec();
	
	sprite->SetDirectionVec(nextPos.dirVec);
	mModel->MoveSpriteToPosition(spriteID, nextPos.position);
}

/******************************************************************************

******************************************************************************/
void PortalGameController::Tick(void)
{	
	// Respond to latest game state
	switch (mModel->CurrentGameState())
	{
		case kGSGameReset:
		{
			mView->ShowSplash();
			mView->ClearBoard(kClearCharacter);
			mModel->SetGameState(kGSGameReady);
			break;
		}
		
		case kGSGameReady:
		{
			mModel->ResetLevel();
			QueueSprites();
			mView->Refresh();
			int buttonPressed = mView->AnimateSpritesUntilButtonPress();
			if (buttonPressed == kLeftButton) 	mModel->MoveSpriteLeft(kShipSpriteID);
			if (buttonPressed == kRightButton)	mModel->MoveSpriteRight(kShipSpriteID);
			if (buttonPressed == kUpButton) 	mModel->MoveSpriteUp(kShipSpriteID);
			if (buttonPressed == kDownButton) 	mModel->MoveSpriteDown(kShipSpriteID);
			mModel->SetGameState(kGSGameRunning);
			break;
		}
		
		case kGSGameRunning:
		{
			if (mButtons->IsPressed(kLeftButton)) 	mModel->MoveSpriteLeft(kShipSpriteID);
			if (mButtons->IsPressed(kRightButton))	mModel->MoveSpriteRight(kShipSpriteID);
			if (mButtons->IsPressed(kUpButton)) 	mModel->MoveSpriteUp(kShipSpriteID);
			if (mButtons->IsPressed(kDownButton)) 	mModel->MoveSpriteDown(kShipSpriteID);
			mQueue.Run(millis());
			break;
		}
			
		case kGSInPortal:
		{
			mView->DoPortalTransition();
			mModel->SetGameState(kGSGameReady);
			break;
		}
			
		case kGSShipDestroyed:
		case kGSGameOver:
		{
			mView->DoGameOverTransition();
			mModel->SetGameState(kGSGameReady);
			break;
		}
		
		default:
			break;
	}
	
	mView->Refresh();
}

/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
