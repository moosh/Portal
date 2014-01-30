/******************************************************************************

	PortalGameController.h
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#pragma once

#include "Queue.h"
#include "PortalGameModel.h"
#include "PortalGameView.h"
#include "ButtonDebouncer.h"

class PortalGameController
{
private:
	ButtonDebouncer* mButtons;
	PortalGameModel* mModel;
	PortalGameView* mView;
	Queue mQueue;
	
	static int AdvanceSpriteCB(unsigned long now, int message, void* ctx);
	void Clear(void);
	void QueueSprites(void);
	int AdvanceSprite(uint8_t spriteID);
	
public:
	PortalGameController(void);
	~PortalGameController(void);
	void Init(PortalGameModel* model, PortalGameView* view);
	void Tick();
};

/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
