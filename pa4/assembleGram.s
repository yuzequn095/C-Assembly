/*
 * Filename: assembleGram.s
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Mar 5th, 2019
 * Source of Help: None.
 */

@ Raspberry Pi directives
	.cpu	cortex-a53		@ Version of our Pis
	.syntax	unified			@ Modern ARM syntax

	.equ	FP_OFFSET, 4		@ Offest from sp to set fp
	.equ	PARAM_SPACE, 8	
	.equ	GRAM_OFFSET, -8
	.equ	IDX_OFFSET, -12

	.global	assembleGram		@ Specify the global name

	.text				@ Switch to Text segment
	.align 2			@ Align on evely divisibly by 4 byte
					@  address
/*
 * Function Name: assembleGram()
 * void assembleGram( gramNode_t * gram, int  wordIndex )
 * Description: This function initializes the gramNode 
 * Parameters: gram - the gram should be initialized
 *             wordIndex - the value of index be set
 * Side Effects: None
 * Error Condition: None
 * Return Value: None.
 * Registers used:
 *		r0 - arg 1 - the gram struct
 *		r1 - arg 2 - the wordIndex
 * Stack Variables: 
 *		gram - [fp - 8] - the struct
 *		wordIndex - [fp - 12] - the value of index
 */
assembleGram:
	@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers
	sub	sp, sp, PARAM_SPACE
	
	str	r0, [fp, GRAM_OFFSET]	@ store param1
	str	r1, [fp, IDX_OFFSET]	@ store param2
	
	@ set gram
	ldr	r2, =INDEX_OFFSET_G	@ load address
	ldr	r2, [r2]
	ldr	r0, [fp, GRAM_OFFSET]	@ load argument1
	ldr	r1, [fp, IDX_OFFSET]	@ get wordIndex
	str	r1, [r0, r2]		@ index = wordIndex

	ldr	r2, =COUNT_OFFSET_G
	ldr	r2, [r2]
	ldr	r0, [fp, GRAM_OFFSET]
	mov	r1, 0
	str	r1, [r0, r2]		@ gram -> count = 0

	ldr	r2, =NEXT_OFFSET_G
	ldr	r2, [r2]
	ldr	r0, [fp, GRAM_OFFSET]	
	mov	r1, 0	
	str	r1, [r0, r2]		@ gram -> next = NULL

	@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set fp to top of saved registers
	pop	{fp, pc}		@  return
