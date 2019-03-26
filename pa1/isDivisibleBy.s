/*
 * Filename: isDivisibleBy.s
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Jan 22th, 2019
 * Source of Help: None
 */

@ Raspberry Pi directives
	.cpu	cortex-a53	@ Version of our Pis
	.syntax	unified		@ Modern ARM syntax

	.equ	FP_OFFSET, 4	@ Offset from sp to set fp

	.global	isDivisibleBy	@ Specify isDivisibleBy as a global symbol

	.text			@ Switch to Text segment
	.align 2		@ Align on evenly divisible by 4 byte address
				@   .align n where 2^n determines alignment

/* 
 * Function Name: isDivisibleBy()
 * Function Prototype: int isDivisibleBy( int num, int divisor );
 * Description: Determines whether num is evenly divisible by divisor.
 * Parameters: num - the value of num
 *             divisor - the value of divisor
 * Side Effects: None
 * Error Condition: Divisor is negative or zero
 * Return Value: -1 if error occurred. Otherwise, return 1 if num is evenly 
 *		   divisible by divisor, and 0 if not.
 *
 * Registers used:
 *	r0 - arg 1 - the value of num
 *	r1 - arg 2 - the number of divisor
 */
 isDivisibleBy:
 @ Standard prologue
 	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers
 
 	@ Incoming parameters in r0, r1
	cmp	r1, 0			@ divisor > 0
	bgt	else			@ opposite logic test to branch over 
					@  if stmts
	/* If Statements */
	mov	r0, -1			@ Set error return
	b	end_if			@ branch always over else block

else:
	bl	getRemainder		@ call getRemainder
	cmp	r0, 0			@ value != 0
	bne	one_if			@ opposite logic test to branch over 
					@   if stmts
	/* If Statements */
	mov	r0, 1			@ Set 1 as return value
	b	end_if			@ branch always over else block

one_if:
	mov	r0, 0			@ Set 0 as return value

end_if:
 @ Standard epilogue
 	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@   return

