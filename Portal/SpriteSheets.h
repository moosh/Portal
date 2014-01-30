/******************************************************************************

	SpriteSheets.h
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#pragma once

const int kSpriteCellWidth		= 5;
const int kSpriteCellHeight		= 8;

const int kShipSpriteLCDCharacter 			= 1;
const int kPortalSpriteLCDCharacter 		= 2;
const int kSolidAsteroidSpriteLCDCharacter 	= 4;
const int kAlienSpriteLCDCharacter			= 5;

const int kShipSpriteCellCount = 4;
const uint8_t kShipSpriteSheet[] =
{
	// 0
	B00100,
	B00100,
	B01110,
	B10101,
	B10011,
	B10111,
	B11111,
	B01010,
	
	// 1
	B00100,
	B00100,
	B01110,
	B10101,
	B10011,
	B10111,
	B11111,
	B01010,
	
	// 2
	B00100,
	B00100,
	B01110,
	B10001,
	B10011,
	B10111,
	B11111,
	B01010,
	
	// 3
	B00100,
	B00100,
	B01110,
	B10001,
	B10011,
	B10111,
	B11111,
	B01010,
};

/******************************************************************************

******************************************************************************/
const int kPortalSpriteCellCount = 9;
const uint8_t kPortalSpriteSheet[] =
{
	// 0
	B01110,
	B10001,
	B10001,
	B10001,
	B10001,
	B10001,
	B10001,
	B01110,

	// 1
	B01110,
	B10001,
	B10001,
	B10001,
	B10001,
	B10001,
	B10001,
	B01110,

	// 2
	B01110,
	B11011,
	B10001,
	B10001,
	B10001,
	B10001,
	B11011,
	B01110,

	// 3
	B01110,
	B11111,
	B11011,
	B10001,
	B10001,
	B11011,
	B11111,
	B01110,

	// 4
	B01110,
	B11111,
	B11111,
	B11011,
	B11011,
	B11111,
	B11111,
	B01110,

	// 5
	B01110,
	B11111,
	B11111,
	B11111,
	B11111,
	B11111,
	B11111,
	B01110,

	// 6
	B01110,
	B10101,
	B11111,
	B11111,
	B11111,
	B11111,
	B10101,
	B01110,

	// 7
	B01110,
	B10001,
	B10101,
	B11111,
	B11111,
	B10101,
	B10001,
	B01110,

	// 8
	B01110,
	B10001,
	B10001,
	B10101,
	B10101,
	B10001,
	B10001,
	B01110,
};

/******************************************************************************

******************************************************************************/
const int kSolidAsteroidSpriteCellCount = 8;
const uint8_t kSolidAsteroidSpriteSheet[] =
{
	// 0
	B00000,
	B01110,
	B11110,
	B11111,
	B11111,
	B11110,
	B01100,
	B00000,
	
	// 1
	B00000,
	B00100,
	B01111,
	B11011,
	B10110,
	B11111,
	B01110,
	B00000,
	
	// 2
	B00000,
	B01110,
	B11011,
	B11111,
	B10111,
	B01111,
	B00110,
	B00000,
	
	// 3
	B00000,
	B00100,
	B11110,
	B10111,
	B11111,
	B11011,
	B00110,
	B00000,

	// 4
	B00000,
	B00110,
	B01111,
	B10111,
	B11111,
	B01011,
	B01110,
	B00000,
		
	// 5
	B00000,
	B01110,
	B11111,
	B01101,
	B11111,
	B01011,
	B01000,
	B00000,
	

	// 6
	B00000,
	B01100,
	B11110,
	B11101,
	B10111,
	B11111,
	B01110,
	B00000,

	// 7
	B00000,
	B01100,
	B11011,
	B11111,
	B10111,
	B01111,
	B00100,
	B00000,
};

/******************************************************************************

******************************************************************************/
const int kAlienSpriteCellCount = 4;
const uint8_t kAlienSpriteSheet[] =
{
	// 0
	B00000,
	B00000,
	B01110,
	B10101,
	B10101,
	B11111,
	B01110,
	B10001,
	
	// 1
	B00000,
	B00000,
	B01110,
	B10011,
	B11001,
	B11111,
	B01110,
	B10001,
	
	// 2
	B00000,
	B00000,
	B01110,
	B10001,
	B10001,
	B11111,
	B01110,
	B10001,
	
	// 3
	B00000,
	B00000,
	B01110,
	B11001,
	B10011,
	B11111,
	B01110,
	B10001,
};

/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
