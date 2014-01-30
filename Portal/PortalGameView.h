/******************************************************************************

	PortalGameView.h
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#pragma once

#include <LiquidCrystal.h>
#include "PortalGameModel.h"
#include "ButtonDebouncer.h"

enum TextAlign
{
	kTextAlignLeft,
	kTextAlignCenter,
	kTextAlignRight
};

class PortalGameView
{
private:
	LiquidCrystal* mLCD;
	PortalGameModel* mModel;
	char mOutputLines[kNumRows][kNumCols+1];	// room for null terminator
	ButtonDebouncer* mButtons;
	
	void Clear(void);
	void ShiftTextLeft(char* text);
	void ShiftTextRight(char* text);
	void ExitStageLeft(void);

	void SetTextForLine(int line, char* text, TextAlign align);
	void WriteLine(int line);
	void WriteAllLines(void);
	
public:
	PortalGameView(void);
	~PortalGameView(void);
	void Init(PortalGameModel* model);
	
	void ClearBoard(uint8_t clearChar);
	void WriteChar(uint8_t c);
	void WriteStringAtPosition(int row, int col, char* text);

	void AnimateSprites(void);
	int AnimateSpritesUntilButtonPress(void);
	void SetCharRAM(int charIndex, const uint8_t* bitmap);
	void SetCursorPosition(Position pos);
	void SetCursorPosition(int row, int col);
	void ShowSplash(void);
	void Refresh(void);
	
	void DoPortalTransition(void);
	void DoGameOverTransition(void);
};

/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
