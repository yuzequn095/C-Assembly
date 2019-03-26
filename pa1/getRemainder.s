/*
 * Filename: getRemainder.s
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Jan 22th, 2019
 * Source of Help: None.
 */

 @ Raspberry Pi directives
 	.cpu	cortex-a53	@ Version of our Pis
	.syntax	unified		@ Modern ARM syntax

	.equ	FP_OFFSET, 4	@ Offset from sp to set fp

	.global	getRemainder	@ Specify getRemainder as a global symbol

	.text			@ Switch to text segment
	.align 2		@ Align on evenly divisible by 4 byte address
				@  .align n where 2^n determines alignment

/*
 * Function Name: getRemainder()
 * Function Prototype: int getRemainder( int dividend, int divisor );
 * Description: Returns the remainder of the division between the dividend 
 *		  and the divisor;
 * Parameters: dividend - the value of dividend
 *	       divisor - the value of divisor
 * Side Effects: None
 * Error Conditions: Divisor is zero.
 * Return Value: The remainder as a signed integer.
 *
 * Registers used:
 *	r0 - arg 1 - dividend
 *	r1 - arg 2 - divisor
 *	r2 - local var 1 - quotient and remainder
 *	r3 - local var 2 - tmpResult
 */
 getRemainder:
 @ Standard prologue
 	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers

	@ Incoming parameters in r0, r1
	sdiv	r2, r0, r1		@ r2 = r0 / r1
	mul	r3, r2, r1		@ r3 = r2 * r1
	sub	r2, r0, r3		@ r2 = r0 - r3

	mov	r0, r2			@ Set return value

 @ Standard epilogue
 	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@ Restore sp to top of saved registers
					@  return
