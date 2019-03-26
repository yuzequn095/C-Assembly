/*
 * Filename: strPtrCmp.s
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Mar 5th, 2019
 * Source of Help: None.
 */

@ Raspberry Pi directives
	.cpu	cortex-a53		@ Version of our Pis
	.syntax	unified			@ Moder ARM syntax
	
	.equ	FP_OFFSET, 4		@ Offset from sp to set fp
	.equ	PARAM_SPACE, 8
	.equ	P1_OFFSET, -8
	.equ	P2_OFFSET, -12

	.global	strPtrCmp

	.text				@ Switch to Text segment
	.align 2			@ Align on evenly divisibly by 4 byte
					@   address
/*
 * Function Name: strPtrCmp()
 * int strPtrCmp( const void * p1, const void * p2 )
 * Description: This funtion takes two void pointers and compare them
 * Parameters: p1 - the first string pointer
 *             p2 - the second string pointer
 * Side Effects: None.
 * Error Condition: None.
 * Return Value: the return value of comparing the two strings pointed to 
 *                 with strcmp.
 * Registers used:
 *             r0 - the pointer to first string
 *             r1 - the pointer to second string
 * Stack Variables: 
 *             str1 - [fp - 8] - the first string
 *             str2 - [fp - 12] - the second string
 */

strPtrCmp:
	@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers
	sub	sp, sp, PARAM_SPACE	@ Allocate space for param

	@ Incoming parameters in r0, r1
	str	r0, [fp, P1_OFFSET]	@ store the first param
	str	r1, [fp, P2_OFFSET]	@ store the second param

	ldr	r0, [fp, P1_OFFSET]	@ get *
	ldr	r1, [fp, P2_OFFSET]	
	ldr	r0, [r0]		@ get **
	ldr	r1, [r1]

	bl	strcmp			@ call function

	@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set fp to top of saved registers
	pop	{fp, pc}		@   return
