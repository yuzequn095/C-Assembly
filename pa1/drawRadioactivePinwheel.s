/* 
 * Filename: drawRadioactivePinwheel.s
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Jan 25th, 2019
 * Source of Help: Link provided in write up. Note.
 */

 @ Raspberry Pi directives
 	.cpu	cortex-a53		@ Version of our Pis
	.syntax	unified			@ Mordern ARM syntax

	.equ	FP_OFFSET, 4

	.equ	LOCAL_VAR_SPACE, 24
	.equ	HALF_SIZE_OFFSET, -8
	.equ	NUM_UPWARD_CHARS_OFFSET, -12
	.equ	NUM_DOWNWARD_CHARS_OFFSET, -16
	.equ	NUM_SPACE_CHARS_OFFSET, -20
	.equ	I_OFFSET, -24
	.equ	ROW_OFFSET, -28	

	.equ	PARAM_SPACE, 16
	.equ	SIZE_OFFSET, -32
	.equ	UPWARD_TRI_CHAR_OFFSET, -36
	.equ	DOWNWARD_TRI_CHAR_OFFSET, -40

	
	.equ	HALF_DIVISOR, 2
	.equ	DOUBLE_FACTOR, 2
	.equ	SPACE_CHAR, ' '
	.equ	NEWLINE_CHAR, '\n'

	.global	drawRadioactivePinwheel	@ Specify global symbol

	.text				@ Switch to text segment
	.align 2			@ Align on evenly divisible by 4 byte
					@  address .align n where 2^n 
					@  determines alignment
	
/*
 * Function Name: drawRadioactivePinwheel()
 * Function Prototype: void drawRadioactivePinwheel( int size, 
 *						     char upwardTriChar, 
 *						     char downwardTriChar );
 * Description: Display the radioactive pinwheerl.
 * Parameters: size - the number of rows
 *	       upwardTriChar - the char in upward triangle
 *	       downwardTriChar - the char in downward triangle
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: Display radioactive pinwheel.
 *
 * Registers used:
 *	r0 - arg 1 - size
 *	r1 - arg 2 - upwardTriChar
 *	r2 - arg 3 - downwardTriChar
 *	r3 - local var - intermediate value
 *
 * Stack Variables:
 * 	haflSize - [fp - 8] -- holds the half value of size
 * 	numUpwardChars - [fp - 12] -- holds the number of upward chars
 *	numDownwardChars - [fp - 16] -- holds the number of downward chars
 *	numSpaceChars - [fp - 20] -- holds the number of space chars
 *	i - [fp - 24] -- holds the value of index
 *	row - [fp-28] -- holds the value of row
 */

 drawRadioactivePinwheel:
	 @ Standard prologue
 	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of  saved registers
	
	sub	sp, sp, LOCAL_VAR_SPACE	@ Set local var space
	sub	sp, sp, PARAM_SPACE	@ Set param space

	@ Incoming parameters in r0, r1
	str	r0, [fp, SIZE_OFFSET]			@ Store size
	str	r1, [fp, UPWARD_TRI_CHAR_OFFSET]	@ Store upward char
	str	r2, [fp, DOWNWARD_TRI_CHAR_OFFSET]	@ Store downward char
		
	ldr	r0, [fp, SIZE_OFFSET]		@ get value of size
	mov	r1, HALF_DIVISOR		@ get half_div
	sdiv	r0, r0, r1			@ size / HALF_DIVISOR
	str	r0, [fp, HALF_SIZE_OFFSET]	@ set halfsize
	
	@ Print the top half of the hexagon one row at a time.
	mov	r0, 0				@ Set r0 as 0
	str	r0, [fp, ROW_OFFSET]		@ set row = 0
	ldr	r0, [fp, ROW_OFFSET]		@ get row
	@ While loop
	ldr	r1, [fp, HALF_SIZE_OFFSET]	@ get halfsize
	cmp	r0, r1				@ row >= halfsize
	bge	end_while			@ opposite logic test to skip
						@  over body of loop
 while:
 	ldr	r0, [fp, ROW_OFFSET]		@ get row
	mov	r1, DOUBLE_FACTOR		@ get 2
	mul	r0, r0, r1			@ 2*row
	add	r0, r0, 1			@ numUpwardChars
	str	r0, [fp, NUM_UPWARD_CHARS_OFFSET]
	
	ldr	r0, [fp, HALF_SIZE_OFFSET]	@ get halfsize
	ldr	r1, [fp, ROW_OFFSET]		@ get row
	sub	r0, r0, r1			@ halfsize - row
	sub	r0, r0, 1			@ halfsize - row - 1
	mov	r1, DOUBLE_FACTOR		@ get 2
	mul	r0, r0, r1			@ double * r1
	add	r0, r0, 1			@ numDownChars
	str	r0, [fp, NUM_DOWNWARD_CHARS_OFFSET]
	
	ldr	r0, [fp, HALF_SIZE_OFFSET]	@ get halfsize
	ldr	r1, [fp, ROW_OFFSET]		@ get row
	sub	r0, r0, r1			@ halfsize - row
	sub	r0, r0, 1			@ numspace
	str	r0, [fp, NUM_SPACE_CHARS_OFFSET]

	/* Left space */
	mov	r3, 0				
	str	r3, [fp, I_OFFSET]		@ i = 0
	ldr	r3, [fp, I_OFFSET]		@  get current i
	ldr	r0, [fp, NUM_SPACE_CHARS_OFFSET]@ get space
	cmp	r3, r0				@ i >= numspace
	bge	end_left_space_loop		@ opposite logic test
left_space_loop:
	/* loop body */
	mov	r0, SPACE_CHAR			@ get SPACE_CHAR	
	bl	printChar			@ call printChar
	ldr	r3, [fp, I_OFFSET]		@ get current i
	add	r3, r3, 1			@ ++i
	str	r3, [fp, I_OFFSET]		@ i = i + 1
	ldr	r3, [fp, I_OFFSET]		@ get current i 
	ldr	r0, [fp, NUM_SPACE_CHARS_OFFSET]
	cmp	r3, r0				@ i < numspace
	blt	left_space_loop			@ positive logic test
 end_left_space_loop:

 	/* Left upward */
	mov	r3, 0				
	str	r3, [fp, I_OFFSET]		@ i = 0
	ldr	r3, [fp, I_OFFSET]		@ get current i 
	ldr	r0, [fp, NUM_UPWARD_CHARS_OFFSET]	@ get upward
	cmp	r3, r0				@ i >= num_upward
	bge	end_left_upward_loop		@ opposite logic test
 left_upward_loop:
 	ldr	r0, [fp, UPWARD_TRI_CHAR_OFFSET]
	bl	printChar			@ call function
	ldr	r3, [fp, I_OFFSET]		@ get current i 
	add	r3, r3, 1			@ ++i
	str	r3, [fp, I_OFFSET]		@ i = i + 1
	ldr	r3, [fp, I_OFFSET]		@ get current i 
	ldr	r0, [fp, NUM_UPWARD_CHARS_OFFSET]
	cmp	r3, r0				@ i < numupward
	blt	left_upward_loop		@ positive logic
 end_left_upward_loop:

 	/* middle downward */
	mov	r3, 0		
	str	r3, [fp, I_OFFSET]		@ i = 0
	ldr	r3, [fp, I_OFFSET]		@ get current i 
	ldr	r0, [fp, NUM_DOWNWARD_CHARS_OFFSET]
	cmp	r3, r0				@ i >= num_down
	bge	end_middle_downward_loop	@ opposite logic test
 middle_downward_loop:
 	ldr	r0, [fp, DOWNWARD_TRI_CHAR_OFFSET]
	bl	printChar			@ call function
	ldr	r3, [fp, I_OFFSET]		@ get current i 
	add	r3, r3, 1			@ ++i
	str	r3, [fp, I_OFFSET]		@ i = i + 1
	ldr	r3, [fp, I_OFFSET]		@ get current i 
	ldr	r0, [fp, NUM_DOWNWARD_CHARS_OFFSET]
	cmp	r3, r0				@ i < num_down
	blt	middle_downward_loop		@ positive logic
 end_middle_downward_loop:

 	/* Right upward */
	mov	r3, 0
	str	r3, [fp, I_OFFSET]		@ i = 0
	ldr	r3, [fp, I_OFFSET]		@ get current i 
	ldr	r0, [fp, NUM_UPWARD_CHARS_OFFSET]
	cmp	r3, r0				@ i >= num_up
	bge	end_right_upward_loop		@ opposite
 right_upward_loop:
 	ldr	r0, [fp, UPWARD_TRI_CHAR_OFFSET]
	bl	printChar			@ call function
	ldr	r3, [fp, I_OFFSET]		@ get current i
	add	r3, r3, 1			@ ++i
	str	r3, [fp, I_OFFSET]		@ i = i + 1
	ldr	r3, [fp, I_OFFSET]		@ get current i 
	ldr	r0, [fp, NUM_UPWARD_CHARS_OFFSET]
	cmp	r3, r0				@ i < num_upward
	blt	right_upward_loop		@ positive logic
 end_right_upward_loop:

 	/* Right space */
	mov	r3, 0
	str	r3, [fp, I_OFFSET]		@ i = 0
	ldr	r3, [fp, I_OFFSET]		@ get current i 
	ldr	r0, [fp, NUM_SPACE_CHARS_OFFSET]
	cmp	r3, r0				@ i >= num_space
	bge	end_right_space_loop		@ opposite logic
 right_space_loop:
 	mov	r0, SPACE_CHAR			@ get space_char
	bl	printChar			@ call function
	ldr	r3, [fp, I_OFFSET]		@ get current i 
	add	r3, r3, 1			@ ++i
	str	r3, [fp, I_OFFSET]		@ i = i + 1
	ldr	r3, [fp, I_OFFSET]		@ get current i 
	ldr	r0, [fp, NUM_SPACE_CHARS_OFFSET]	
	cmp	r3, r0				@ i < num_space
	blt	right_space_loop		@ positive logic
 end_right_space_loop:

	/* end while */
	mov	r0, NEWLINE_CHAR		@ get new_line
	bl	printChar			@ call function
	ldr	r0, [fp, ROW_OFFSET]		@ get row
	add	r0, r0, 1			@ ++row
	str	r0, [fp, ROW_OFFSET]		@ row = row + 1
	ldr	r0, [fp, ROW_OFFSET]		@ get row
	ldr	r1, [fp, HALF_SIZE_OFFSET]	@ get halfsize
	cmp	r0, r1				@ row < halfsize
	blt	while				@ positive logic
 end_while:

 	/* --row */
	ldr	r0, [fp, ROW_OFFSET]		@ get row
	mov	r1, 1				@ get 1
	sub	r0, r0, r1			@ --row
	str	r0, [fp, ROW_OFFSET]		@ row = row - 1

	/* bot half */
	ldr	r3, [fp, ROW_OFFSET]		@ get row
	cmp	r3, 0				@ row < 0
	blt	end_bot_while			@ opposite logic
 bot_while:
 	/* while body */
	ldr	r0, [fp, HALF_SIZE_OFFSET]	@ get halfsize
	ldr	r1, [fp, ROW_OFFSET]		@ get row
	sub	r0, r0, r1			@ halfsize - row
	sub	r0, r0, 1			@ r0 - 1
	mov	r1, DOUBLE_FACTOR		@ get double_factor
	mul	r0, r0, r1			@ double * r0
	add	r0, r0, 1			@ numupward
	str	r0, [fp, NUM_UPWARD_CHARS_OFFSET]
	
	ldr	r0, [fp, ROW_OFFSET]		@ get row
	mov	r1, DOUBLE_FACTOR		@ get double_factor
	mul	r0, r0, r1			@ row * double
	add	r0, r0, 1			@ r0 + 1
	str	r0, [fp, NUM_DOWNWARD_CHARS_OFFSET]

	ldr	r0, [fp, HALF_SIZE_OFFSET]	@ get halfsize
	ldr	r1, [fp, ROW_OFFSET]		@ get row
	sub	r0, r0, r1			@ halfsize - row
	sub	r0, r0, 1			@ r0 - 1
	str	r0, [fp, NUM_SPACE_CHARS_OFFSET]

	/* Left space for */
	mov	r3, 0
	str	r3, [fp, I_OFFSET]		@ i = 0
	ldr	r3, [fp, I_OFFSET]		@ get i 
	ldr	r0, [fp, NUM_SPACE_CHARS_OFFSET]
	cmp	r3, r0				@ i >= num_space
	bge	end_left_space			@ opposite logic
 left_space:
 	mov	r0, SPACE_CHAR			@ get space_char
	bl	printChar			@ call function
	ldr	r3, [fp, I_OFFSET]		@ get current i 
	add	r3, r3, 1			@ ++i
	str	r3, [fp, I_OFFSET]		@ i = i + 1
	ldr	r3, [fp, I_OFFSET]		@ get current i 
	ldr	r0, [fp, NUM_SPACE_CHARS_OFFSET]	
	cmp	r3, r0				@ i < num_space
	blt	left_space
 end_left_space:

 	/* Left downward */
	mov	r3, 0		
	str	r3, [fp, I_OFFSET]		@ i = 0
	ldr	r3, [fp, I_OFFSET]		@ get i 
	ldr	r0, [fp, NUM_DOWNWARD_CHARS_OFFSET]
	cmp	r3, r0				@ i >= num_down
	bge	end_left_downward		@ opposite logic test
 left_downward:
 	ldr	r0, [fp, DOWNWARD_TRI_CHAR_OFFSET]	@ get down_tri
	bl	printChar 			@ call function
	ldr	r3, [fp, I_OFFSET]		@ get current i 
	add	r3, r3, 1			@ ++i
	str	r3, [fp, I_OFFSET]		@ i = i + 1
	ldr	r3, [fp, I_OFFSET]		@ get i 
	ldr	r0, [fp, NUM_DOWNWARD_CHARS_OFFSET]
	cmp	r3, r0				@ i < num_down
	blt	left_downward			@ positive logic
 end_left_downward:

 	/* Middle upward */
	mov	r3, 0				@ i = 0
	str	r3, [fp, I_OFFSET]		@ i = 0
	ldr	r3, [fp, I_OFFSET]		@ get i 
	ldr	r0, [fp, NUM_UPWARD_CHARS_OFFSET]
	cmp	r3, r0				@ i >= num_upward
	bge	end_mid_upward			@ opposite logic
 mid_upward:
 	ldr	r0, [fp, UPWARD_TRI_CHAR_OFFSET]
	bl	printChar			@ call function
	ldr	r3, [fp, I_OFFSET]		@ get i 
	add	r3, r3, 1			@ ++i
	str	r3, [fp, I_OFFSET]		@ i = i + 1
	ldr	r3, [fp, I_OFFSET]		@ get i 
	ldr	r0, [fp, NUM_UPWARD_CHARS_OFFSET]
	cmp	r3, r0				@ i < num_upward
	blt	mid_upward			@ positive logic
 end_mid_upward:

 	/* Right downward */
	mov	r3, 0
	str	r3, [fp, I_OFFSET]		@ i = 0
	ldr	r3, [fp, I_OFFSET]		@ get i 
	ldr	r0, [fp, NUM_DOWNWARD_CHARS_OFFSET]
	cmp	r3, r0				@ i >= num_down
	bge	end_right_downward		@ opposite logic test
 right_downward:
 	ldr	r0, [fp, DOWNWARD_TRI_CHAR_OFFSET]
	bl	printChar			@ call function
	ldr	r3, [fp, I_OFFSET]		@ get i 
	add	r3, r3, 1			@ ++i
	str	r3, [fp, I_OFFSET]		@ i = i + 1
	ldr	r3, [fp, I_OFFSET]		@ get i 
	ldr	r0, [fp, NUM_DOWNWARD_CHARS_OFFSET]
	cmp	r3, r0				@ i < num_down
	blt	right_downward			@ positive logic test
 end_right_downward:

 	/* Right space */
	mov	r3, 0				
	str	r3, [fp, I_OFFSET]		@ i = 0
	ldr	r3, [fp, I_OFFSET]		@ get i 
	ldr	r0, [fp, NUM_SPACE_CHARS_OFFSET]
	cmp	r3, r0				@ i >= num_space
	bge	end_right_space			@ opposite logic test
 right_space:
 	mov	r0, SPACE_CHAR			@ get space_char
	bl	printChar			@ call function
	ldr	r3, [fp, I_OFFSET]		@ get i 
	add	r3, r3, 1			@ ++i
	str	r3, [fp, I_OFFSET]		@ i = i + 1
	ldr	r3, [fp, I_OFFSET]		@ get i 
	ldr	r0, [fp, NUM_SPACE_CHARS_OFFSET]
	cmp	r3, r0				@ i < num_space
	blt	right_space			@ positive
 end_right_space:

 	/* While bot ned */
	mov	r0, NEWLINE_CHAR		@ get newline
	bl	printChar			@ call function
	ldr	r3, [fp, ROW_OFFSET]		@ get row
	sub	r3, r3, 1			@ --row
	str	r3, [fp, ROW_OFFSET]		@ row = row - 1
	ldr	r3, [fp, ROW_OFFSET]		@ get row
	cmp	r3, 0				@ row >= 0
	bge	bot_while			@ positive logic test
 end_bot_while:

 	@ Standard epilogue
 	sub	sp, fp, FP_OFFSET		@ Set sp to top of saved reg
	pop	{fp, pc}			@ Restore fp; restore lr into
						@   for return
