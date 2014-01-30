/******************************************************************************

	ButtonDebouncer.h
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#pragma once

#include "Prefix.h"

class ButtonDebouncer
{
private:
	static ButtonDebouncer* mSharedInstance;
	unsigned long mButtonBounceLastPressTime[kButtonCount];

	ButtonDebouncer(void);	// nope

public:
	static ButtonDebouncer* SharedInstance(void);
	~ButtonDebouncer(void);
	int IsAnyButtonPressed(void);
	bool IsPressed(int buttonID);
};

/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
