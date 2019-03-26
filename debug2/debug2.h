/*
 * Filename: debug2.h
 * Description: header file so other files could see methods
 */
#ifndef DEBUG_H
#define DEBUG_H

long checkMove( long board[][3], long xIndex, long yIndex );
long parsePlay( long board[][3], char * input, long * xIndex, long * yIndex );
void printBoard( long board[][3] );
long checkWin( long xIndex, long yIndex, long turn );
            
#endif // DEBUG_H
