/*
 * Filename: isInBounds.s
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Jan 22th, 2019
 * Source of Help: None.
 */

@ Raspberry Pi directives
	.cpu	cortex-a53	@ Version of our pis
	.syntax	unified		@ Modern ARM syntax

	.equ	FP_OFFSET, 4	@ Offset from sp to set fp

	.global	isInBounds	@ Specify isInBounds as a global symbol

	.text			@ Switch to Text segment
	.align 2		@ Align on evenly divisible by 4 byte address
				@  .align n where 2^n determines alignment

/*
 * Function Name: isInBounds()
 * Function Prototype: int isInBounds( int value, int minBound, int maxBound );
 * Description: Determines whether value is within the bounds of min and max.
 * Parameters: a - the value
 *	       minBound - the inclusive min value
 *	       maxBound - the inclusive max value
 * Side Effects: None
 * Error Conditions: minBound is greater than maxBound
 * Return Value: -1 if an error occured. Otherwise, return 1 if in bounds and 
 *		  0 if not in bounds.
 *
 * Registers used:
 *	r0 - arg 1 -- value
 *	r1 - arg 2 -- minBound
 *	r2 - arg 3 -- maxBound
 *
 */
isInBounds:
@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers

	@ Incoming parameters in r0,r1,r2
	cmp	r1, r2			@ Check error if min > max	
	ble	end_if			@ opposite logic test to branch over
					@  if stmts
	/* If statements */
	mov	r0, -1			@ Set error value
	b	end_if_else		@ branch always over else block
end_if:
	/* Instructions following if blocks */
	cmp	r0, r1			@ check if less than min
	blt	else			@ opposite logic test to branch over 
					@  if stmts fall thru if (v < min)
	cmp	r0, r2			@ check if greater than max
	bgt	else			@ opposite logic test to branch over
					@  if stmts fall thru if ( v > max)
	/* If statements */
	mov	r0, 1			@ Set correct value
	b	end_if_else		@ branch always over else block
	 
 	/* Else statements */
else:
	mov	r0, 0			@ Set no-bound return


end_if_else:
@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@   return
