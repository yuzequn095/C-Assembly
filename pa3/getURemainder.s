/*
 * Filename: getURemainder.s
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 27th, 2019
 * Source of Help: None.
 */


@ Paspberry Pi directives
	.cpu	cortex-a53		@ Version of our Pis
	.syntax	unified			@ Modern ARM syntax

	.equ	FP_OFFSET, 4

	.global	getURemainder		@ Specify the global name

	.text				@ Switch to Text segment
	.align 2			@ Align on evenly divisibly by 4 byte
					@   address
/*
 * Function Name: getUReminder()
 * Function Prototype: unsigned int getURemainder( unsigned int divided,
 *                     unsigned int divisor)
 * Description: Get the unsigned remainder 
 * Parameters: dividend - the value of dividend
 *             divisor - the value of divisor
 * Side Effects: None
 * Error Condition: None
 * Return Value: the unsigned division
 */

getURemainder:
	@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers
	
	@ Incoming parameters
	udiv	r2, r0, r1		@ get quotient
	mul	r3, r2, r1		@ get tmp-result
	sub	r2, r0, r3		@ get remainder

	mov	r0, r2			@ Set return

	@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@   return
