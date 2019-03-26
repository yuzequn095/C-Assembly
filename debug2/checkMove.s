/*
 * Filename: checkMove.s
 * Description: check if a move in the game is valid or not
 */
	.cpu	cortex-a53
	.syntax	unified

	.equ	MININD, 0
	.equ	MAXIND, 2
	.equ	ARRAYSIZ, 12
	.equ	LONGSIZ, 4

	.equ	FP_OFFSET, 4

	.global checkMove

	.text
	.align	2

/*
 * Function name: checkMove
 * Function prototype: long checkMove(long board[] [3], long xIndex,
 *                                    long yIndex);
 * Description: check if the move to board[xIndex][yIndex] is a valid
 *              position
 * Parameters: 
 *	arg 1 - board - a 3x3 board for tic tac toe
 *	arg 2 - xIndex - the row number on the board
 *	arg 3 - yIndex - the col number on the board
 * Side Effects: None
 * Error Conditions: None
 * Return Value: 1 if the move is valid, 0 if not valid
 *
 * Registers Used::
 *	r0 - holds the game board 2D array
 *	r1 - holds the xIndex of the move (row number) / used for tmp var later
 *	r2 - holds the yIndex of the move (col number)
 *	r3 - tmp var for calculating position on the board
 */
checkMove:

	push	{fp, lr}
	add	fp, sp, FP_OFFSET
	
	cmp	r1, MININD	@ Check if the X index is less than the min
	blt	INVALID		@ Branch to invalid if true

	cmp	r1, MAXIND	@ Check if the X index is larger than the max
	bgt	INVALID		@ Branch to invalid if true
	
	cmp	r2, MININD	@ Check if the Y index is less than the min
	blt	INVALID		@ Branch to invalid if true

	cmp	r2, MAXIND	@ Check if the Y index is larger than the max
	bgt	INVALID		@ Branch to invalid if true

	mov	r3, ARRAYSIZ	@ Get the row in memory
	mul	r3, r1, r3	@ Done using X index
	add	r0, r0, r3	@ Get the mem location of board[Xindex][0]

	mov	r1, LONGSIZ	@ Get the column in memory
	mul	r1, r2, r1

	add	r3, r0, r1	@ Get the mem location of board[Xindex][Yindex]
	ldr	r3, [r3]	@ Load board[Xindex][Yindex]
	
	cmp	r3, 0		@ Check if the cell is empty
	bne	INVALID		@ If it is not empty branch to invalid

	mov	r0, 1		@ Return 1 if valid
	b	end
INVALID:
	mov	r0, 0		@ Return 0 if invalid

end:
	sub	sp, fp, FP_OFFSET
	pop	{fp, pc}

	
