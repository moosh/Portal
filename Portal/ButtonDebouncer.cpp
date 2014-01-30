/******************************************************************************

	ButtonDebouncer.cpp
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#pragma once

#include "ButtonDebouncer.h"

const unsigned long kBounceDelay = 100;

ButtonDebouncer* ButtonDebouncer::mSharedInstance = NULL;

/******************************************************************************

******************************************************************************/
ButtonDebouncer* ButtonDebouncer::SharedInstance(void)
{
	if (!mSharedInstance) mSharedInstance = new ButtonDebouncer();
	return mSharedInstance;
}

/******************************************************************************

******************************************************************************/
ButtonDebouncer::ButtonDebouncer(void)
{
	memset(mButtonBounceLastPressTime, 0, kButtonCount * sizeof(unsigned long));
}

/******************************************************************************

******************************************************************************/
ButtonDebouncer::~ButtonDebouncer(void)
{
	memset(mButtonBounceLastPressTime, 0, kButtonCount * sizeof(unsigned long));
}

/******************************************************************************

******************************************************************************/
int ButtonDebouncer::IsAnyButtonPressed(void)
{
	if (IsPressed(kLeftButton)) return kLeftButton;
	if (IsPressed(kRightButton)) return kRightButton;
	if (IsPressed(kUpButton)) return kUpButton;
	if (IsPressed(kDownButton)) return kDownButton;
	
	return kNoButton;
}

/******************************************************************************

******************************************************************************/
bool ButtonDebouncer::IsPressed(int buttonID)
{
	unsigned long* lastPressTime = NULL;
	switch (buttonID)
	{
		case kLeftButton:	lastPressTime = &mButtonBounceLastPressTime[0]; break;
		case kRightButton:	lastPressTime = &mButtonBounceLastPressTime[1]; break;
		case kUpButton:		lastPressTime = &mButtonBounceLastPressTime[2]; break;
		case kDownButton:	lastPressTime = &mButtonBounceLastPressTime[3]; break;
	}
	
	if (false == digitalRead(buttonID))
		*lastPressTime = 0;
	else
	{
		int now = millis();
		if ((now - *lastPressTime) > kBounceDelay)
		{
			*lastPressTime = now;
			return true;
		}
	}
	
	return false;
}



/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
