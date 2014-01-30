#!/usr/bin/python
##########################################################
#  Portal.py
#
#  Copyright (c) 2013 onOne Software.
#  All Rights Reserved
#  
##########################################################

import os
import re
import sys
import platform
import datetime
import subprocess

kEmptyCell 		= " "
kBorderCell		= "*"

#-------------------------------------------------------------------------------
#
#-------------------------------------------------------------------------------
class GameBoard:
	mNumRows 		= 10
	mNumCols 		= 10

	#---------------------------------------------------------------------------
	#
	#---------------------------------------------------------------------------
	def __init__(self):
		self.mRowList = []
		for row in range(1,self.mNumRows):
			self.mRowList.append(list(str(kEmptyCell * self.mNumCols)))
			
	#---------------------------------------------------------------------------
	#
	#---------------------------------------------------------------------------
	def rows(self):
		return self.mNumRows
		
	#---------------------------------------------------------------------------
	#
	#---------------------------------------------------------------------------
	def cols(self):
		return self.mNumCols
					
	#---------------------------------------------------------------------------
	#
	#---------------------------------------------------------------------------
	def setCell(self, col, row, cellValue):
		self.mRowList[row][col] = cellValue;
		
	#---------------------------------------------------------------------------
	#
	#---------------------------------------------------------------------------
	def cell(self, col, row):
		return self.mRowList[row][col];
		
	#---------------------------------------------------------------------------
	#
	#---------------------------------------------------------------------------
	def rowString(self, row):
		return "".join(self.mRowList[row])


def read_single_keypress():
    """Waits for a single keypress on stdin.

    This is a silly function to call if you need to do it a lot because it has
    to store stdin's current setup, setup stdin for reading single keystrokes
    then read the single keystroke then revert stdin back after reading the
    keystroke.

    Returns the character of the key that was pressed (zero on
    KeyboardInterrupt which can happen when a signal gets handled)

    """
    import termios, fcntl, sys, os
    fd = sys.stdin.fileno()
    # save old state
    flags_save = fcntl.fcntl(fd, fcntl.F_GETFL)
    attrs_save = termios.tcgetattr(fd)
    # make raw - the way to do this comes from the termios(3) man page.
    attrs = list(attrs_save) # copy the stored version to update
    # iflag
    attrs[0] &= ~(termios.IGNBRK | termios.BRKINT | termios.PARMRK 
                  | termios.ISTRIP | termios.INLCR | termios. IGNCR 
                  | termios.ICRNL | termios.IXON )
    # oflag
    attrs[1] &= ~termios.OPOST
    # cflag
    attrs[2] &= ~(termios.CSIZE | termios. PARENB)
    attrs[2] |= termios.CS8
    # lflag
    attrs[3] &= ~(termios.ECHONL | termios.ECHO | termios.ICANON
                  | termios.ISIG | termios.IEXTEN)
    termios.tcsetattr(fd, termios.TCSANOW, attrs)
    # turn off non-blocking
    fcntl.fcntl(fd, fcntl.F_SETFL, flags_save & ~os.O_NONBLOCK)
    # read a single keystroke
    try:
        ret = sys.stdin.read(1) # returns a single character
    except KeyboardInterrupt: 
        ret = 0
    finally:
        # restore old state
        termios.tcsetattr(fd, termios.TCSAFLUSH, attrs_save)
        fcntl.fcntl(fd, fcntl.F_SETFL, flags_save)
    return ret

#-------------------------------------------------------------------------------
#
#-------------------------------------------------------------------------------
def drawGameBoard(gameBoard):
	numCols = gameBoard.cols()
	numRows = gameBoard.rows()
	
	# Draw top boundary
	print kBorderCell * (numCols+2)
	
	for row in range(0,numRows-1):
		boardRow = gameBoard.rowString(row)
		print kBorderCell + boardRow + kBorderCell
		
	print kBorderCell * (numCols+2)
	
#-------------------------------------------------------------------------------
#
#-------------------------------------------------------------------------------
def main(argv=None):	
	
	mGameBoard = GameBoard()
	mGameBoard.setCell(1,0,"@")
	
	while True:
		c = read_single_keypress()
		if c=='a':
			mGameBoard.setCell(4,6,"&")
		elif c == 'd':
			mGameBoard.setCell(8,6,"#")

		os.system('clear')
		drawGameBoard(mGameBoard)
		
	return 0
		
#-------------------------------------------------------------------------------
#
#-------------------------------------------------------------------------------
if __name__ == "__main__":
	retVal = main()
	if retVal > 127:
		retVal = 127	# most platforms require exit codes between 0 and 127
	sys.exit(retVal)

#-------------------------------------------------------------------------------
#
#-------------------------------------------------------------------------------
#-------------------------------------------------------------------------------
#
#-------------------------------------------------------------------------------
#-------------------------------------------------------------------------------
#
#-------------------------------------------------------------------------------
