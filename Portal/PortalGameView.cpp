/******************************************************************************

	PortalGameView.cpp
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#include "Prefix.h"
#include "PortalGameView.h"
#include "SpriteSheets.h"

const int kRS = 0;
const int kRW = 1;
const int kEN = 2;
const int kD0 = 3;
const int kD1 = 4;
const int kD2 = 5;
const int kD3 = 6;
const int kD4 = 7;
const int kD5 = 8;
const int kD6 = 9;
const int kD7 = 10;

/******************************************************************************

******************************************************************************/
PortalGameView::PortalGameView(void)
{
	Clear();
}

/******************************************************************************

******************************************************************************/
PortalGameView::~PortalGameView(void)
{
	Clear();
}

/******************************************************************************

******************************************************************************/
void PortalGameView::Clear(void)
{
	mLCD = NULL;
	mModel = NULL;
	mButtons = NULL;
}

/******************************************************************************

******************************************************************************/
void PortalGameView::Init(PortalGameModel* model)
{
	mModel = model;
	mLCD = new LiquidCrystal(kRS, kRW, kEN, kD0, kD1, kD2, kD3, kD4, kD5, kD6, kD7);
	mLCD->begin(16, 4);
	mButtons = ButtonDebouncer::SharedInstance();
}

/******************************************************************************

******************************************************************************/
void PortalGameView::ClearBoard(uint8_t clearChar)
{
	for (int row = 0; row < kNumRows; ++row)
	{
		for (int col = 0; col < kNumCols; ++col)
		{
			SetCursorPosition(row, col);
			WriteChar(clearChar);
		}
	}	
}

/******************************************************************************

******************************************************************************/
void PortalGameView::WriteChar(uint8_t c)
{
	mLCD->write(c);
}

/******************************************************************************

******************************************************************************/
void PortalGameView::WriteStringAtPosition(int row, int col, char* text)
{
	SetCursorPosition(row, col);
	mLCD->print(text);
}

/******************************************************************************

******************************************************************************/
void PortalGameView::SetCharRAM(int charIndex, const uint8_t* bitmap)
{
	const int kCreateCharDelayUSec = 300;
	
	mLCD->createChar(charIndex, (uint8_t*)bitmap);
	delayMicroseconds(kCreateCharDelayUSec);
}

/******************************************************************************

******************************************************************************/
void PortalGameView::SetCursorPosition(Position pos)
{
	SetCursorPosition(pos.row, pos.col);
}

/******************************************************************************

******************************************************************************/
void PortalGameView::SetCursorPosition(int row, int col)
{
	if (row > 1)
	{
		// LCD library doesn't exactly support setting
		// the cursor by (row, col) when display is 16x4
		// The following fixup handles the conversion.
		row -= 2;
		col += 16;
	}
	
	mLCD->setCursor(col, row);
}

/******************************************************************************

******************************************************************************/
void PortalGameView::SetTextForLine(int line, char* text, TextAlign align)
{
	if ((line < kTopRow) || (line > kBottomRow)) return;
	
	int len = strlen(text);
	if (len > kNumCols)
	{
		text[kNumCols] = 0;
		len = kNumCols;
	}

	int spaceCount = kNumCols - len;
	*(mOutputLines[line]) = 0;	// reset the string
	switch (align)
	{
		case kTextAlignLeft:
		{
			strcpy(mOutputLines[line], text);

			for (int i = 0; i < spaceCount; ++i)
				strcat(mOutputLines[line], " ");
			break;
		}
			
		case kTextAlignCenter:
		{
			int leftSpaceCount = spaceCount / 2;
			for (int i = 0; i < leftSpaceCount; ++i)
				strcat(mOutputLines[line], " ");
				
			strcat(mOutputLines[line], text);

			int rightSpaceCount = spaceCount - leftSpaceCount;
			for (int i = 0; i < rightSpaceCount; ++i)
				strcat(mOutputLines[line], " ");
				
			break;
		}
		
		case kTextAlignRight:
		{
			for (int i = 0; i < spaceCount; ++i)
				strcat(mOutputLines[line], " ");
				
			strcat(mOutputLines[line], text);
			break;
		}
		
		default:
			break;
	}
}

/******************************************************************************

******************************************************************************/
void PortalGameView::WriteLine(int line)
{
	if ((line < kTopRow) || (line > kBottomRow)) return;
	WriteStringAtPosition(line, 0, mOutputLines[line]);
}

/******************************************************************************

******************************************************************************/
void PortalGameView::WriteAllLines(void)
{
	for (int i = 0; i < kNumRows; ++i)
		WriteStringAtPosition(i, 0, mOutputLines[i]);
}

/******************************************************************************

******************************************************************************/
void PortalGameView::ShiftTextLeft(char* text)
{
	if (!text) return;
	
	int len = strlen(text);
	for (int i = 0; i < len-1; ++i) text[i] = text[i+1];
	text[len-1] = ' ';
}

/******************************************************************************

******************************************************************************/
void PortalGameView::ShiftTextRight(char* text)
{
	if (!text) return;
	
	int len = strlen(text);
	for (int i = len-1; i > 0; --i) text[i] = text[i-1];
	text[0] = ' ';
}

/******************************************************************************
	
******************************************************************************/
void PortalGameView::ExitStageLeft(void)
{
	const int kSlideDelay = 1;
	char* line = NULL;
	
	int rowBytes = kNumCols+1;
	for (int col = 0; col < kNumCols; ++col)
	{
		for (int row = 0; row < kNumRows; ++row)
		{
			line = mOutputLines[row];
			SetCursorPosition(row,0); ShiftTextLeft(line);
			mLCD->print(line);
			delay(kSlideDelay);
		}
	}
}

/******************************************************************************

******************************************************************************/
void PortalGameView::AnimateSprites(void)
{
	Sprite* sprite = NULL;
	for (int i = 0; i < mModel->NumSprites(); ++i)
	{
		sprite = mModel->SpriteWithID(i);
		SetCharRAM(sprite->LCDCharacter(), sprite->NextSpriteBitmap());
	}
}

/******************************************************************************

******************************************************************************/
int PortalGameView::AnimateSpritesUntilButtonPress(void)
{
	const int kAnimateDelay	= 50;
	
	int buttonPressed = kNoButton;
	while (kNoButton == buttonPressed)
	{
		AnimateSprites();
		delay(kAnimateDelay);
		buttonPressed = mButtons->IsAnyButtonPressed();
	}
	
	return buttonPressed;
}

/******************************************************************************

******************************************************************************/
void PortalGameView::ShowSplash(void)
{
	const int kShiftDelay 	= 50;
	const int kAnimateDelay	= 50;

	SetTextForLine(0, "Portal LCD", kTextAlignLeft);
	SetTextForLine(1, " ", kTextAlignLeft);
	SetTextForLine(2, "Press any button", kTextAlignCenter);
	SetTextForLine(3, "to continue", kTextAlignCenter);
	
	WriteLine(0);	
	delay(kShiftDelay);
	
	for (int i = 0; i < 5; ++i)
	{
		ShiftTextRight(mOutputLines[0]);
		WriteLine(0);
		delay(kShiftDelay);
	}
	
	for (int i = 0; i < 2; ++i)
	{
		ShiftTextLeft(mOutputLines[0]);
		WriteLine(0);
		delay(kShiftDelay);
	}
	
	WriteLine(1);
	WriteLine(2);
	WriteLine(3);
	while (kNoButton == mButtons->IsAnyButtonPressed()) { }

	ExitStageLeft();

	char workStr[20];
	sprintf(workStr, " %c = Your Ship", kShipSpriteLCDCharacter);
	SetTextForLine(0, workStr, kTextAlignLeft);

	sprintf(workStr, " %c = Portal", kPortalSpriteLCDCharacter);
	SetTextForLine(1, workStr, kTextAlignLeft);

	sprintf(workStr, " %c = Asteroid", kSolidAsteroidSpriteLCDCharacter);
	SetTextForLine(2, workStr, kTextAlignLeft);

	sprintf(workStr, " %c = Alien", kAlienSpriteLCDCharacter);
	SetTextForLine(3, workStr, kTextAlignLeft);
	
	WriteAllLines();
	AnimateSpritesUntilButtonPress();
	ExitStageLeft();

	sprintf(workStr, "Start the game");
	SetTextForLine(0, workStr, kTextAlignCenter);
	
	sprintf(workStr, "by moving %c", kShipSpriteLCDCharacter);
	SetTextForLine(1, workStr, kTextAlignCenter);
	
	sprintf(workStr, "Escape through %c", kPortalSpriteLCDCharacter);
	SetTextForLine(2, workStr, kTextAlignCenter);
	
	sprintf(workStr, "Avoid %c and %c", kSolidAsteroidSpriteLCDCharacter, kAlienSpriteLCDCharacter);
	SetTextForLine(3, workStr, kTextAlignCenter);
	
	WriteAllLines();
	AnimateSpritesUntilButtonPress();
	ExitStageLeft();
}

/******************************************************************************

******************************************************************************/
void PortalGameView::Refresh(void)
{
	uint8_t c;
	Position pos;
	Sprite* sprite;
	
	AnimateSprites();
	
	for (int row = 0; row < kNumRows; ++row)
	{
		for (int col = 0; col < kNumCols; ++col)
		{
			pos.row = row;
			pos.col = col;
			SetCursorPosition(pos);
			
			sprite = mModel->SpriteAtPosition(row, col);
			if (sprite)	WriteChar(sprite->LCDCharacter());
			else		WriteChar(kClearCharacter);
		}
	}
}

/******************************************************************************

******************************************************************************/
void PortalGameView::DoPortalTransition(void)
{
	ClearBoard('*');
	
	Sprite* sprite = mModel->SpriteWithID(kShipSpriteID);
	if (!sprite) return;
	
	PositionVec shipPosVec = sprite->CurPositionVec();
	Position pos, shipPos = shipPosVec.position;
	
	for (int i = 0; i < 10; ++i)
	{
		for (int row = 0; row < kNumRows; ++row)
		{
			for (int col = 0; col < kNumCols; ++col)
			{
				if (random()%2 == 1)
				{
					pos.row = row;
					pos.col = col;
					SetCursorPosition(pos);
					WriteChar('*');
				}
				else
				{
					pos.row = row;
					pos.col = col;
					SetCursorPosition(pos);
					WriteChar(kClearCharacter);
				}
			}			
		}
		
		delay(50);

	}

	//delay(1000);
	
	char workStr[20];
	sprintf(workStr, " ");
	SetTextForLine(0, workStr, kTextAlignCenter);
	
	sprintf(workStr, "Level %d", mModel->CurrentLevel());
	SetTextForLine(1, workStr, kTextAlignCenter);

	sprintf(workStr, " ");
	SetTextForLine(2, workStr, kTextAlignCenter);

	sprintf(workStr, " ");
	SetTextForLine(3, workStr, kTextAlignCenter);

	WriteAllLines();
	delay(500);
	ExitStageLeft();

}

/******************************************************************************

******************************************************************************/
void PortalGameView::DoGameOverTransition(void)
{
	ClearBoard('*');
	
	Sprite* sprite = mModel->SpriteWithID(kShipSpriteID);
	if (!sprite) return;
	
	PositionVec shipPosVec = sprite->CurPositionVec();
	Position shipPos = shipPosVec.position;
	Position pos;
	int radius = 10;
	int radius2 = radius * radius;
	int distance2 = 0;
	while (radius)
	{
		for (int row = 0; row < kNumRows; ++row)
		{
			for (int col = 0; col < kNumCols; ++col)
			{
				distance2 = (row - shipPos.row)*(row - shipPos.row) + (col - shipPos.col)*(col-shipPos.col);
				if (distance2 >= radius2)
				{
					pos.row = row;
					pos.col = col;
					SetCursorPosition(pos);
					WriteChar(kClearCharacter);
				}
			}
		}
		
		radius--;
		radius2 = radius*radius;
		delay(20);
	}

	delay(1000);
	
	char workStr[20];
	sprintf(workStr, " ");
	SetTextForLine(0, workStr, kTextAlignCenter);
	
	if (mModel->CurrentGameState() == kGSGameOver)
	{
		sprintf(workStr, "%c Game  Over %c", kAlienSpriteLCDCharacter, kAlienSpriteLCDCharacter);
		SetTextForLine(1, workStr, kTextAlignCenter);

		sprintf(workStr, " ");
		SetTextForLine(2, workStr, kTextAlignCenter);
	}
	else
	{
		sprintf(workStr, " ");
		SetTextForLine(0, workStr, kTextAlignCenter);
		
		sprintf(workStr, "Ships Remaining");
		SetTextForLine(1, workStr, kTextAlignCenter);

		char shipStr[20];
		workStr[0] = shipStr[0] = 0;
		for (int i = 0; i < mModel->MaxLives(); ++i)
		{
			sprintf(shipStr, "%c", mModel->LivesRemaining() > i ? kShipSpriteLCDCharacter : kClearCharacter);
			strcat(workStr, shipStr);
		}
		SetTextForLine(2, workStr, kTextAlignCenter);
	}

	sprintf(workStr, " ");
	SetTextForLine(3, workStr, kTextAlignCenter);

	WriteAllLines();
	AnimateSpritesUntilButtonPress();
	ExitStageLeft();
}

/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
