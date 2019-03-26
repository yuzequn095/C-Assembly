/* 
 * Filename: isOdd.s
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: 4th, Feb, 2019
 * Source of Help: None.
 */

@ Raspberry Pi directives
	.cpu	cortex-a53	@ Version of our pis
	.syntax	unified		@ Modern ARM syntax

	.equ	FP_OFFSET, 4	@ Offset from sp to set fp

	.global	isOdd		@ Specify isOdd as a global symbol

	.text			@ Switch to Text segment
	.align 2		@ Align on evenly divisible by 4 byte address
				@  .align n where 2^n determines alignment

/*
 * Function Name: isOdd()
 * Function Prototype: int isOdd( int num )
 * Description: Decide if the number is odd.
 * Parameters: num - the number will be checked
 * Side Effects: None
 * Error Condistion: None
 * Return Value: 1 if num is Odd, 0 otherwise.
 * Registers used: 
 *	r0 - arg 1 - num
 *	r1 - local var - compare value
 */
isOdd:
@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers
 
	@ Incoming parameters in r0
	mov	r1, 1			@ move 1 to r1
	and	r0, r0, r1		@ num & 1
	cmp	r0, 1			@ Check if r0 != 1
	bne	else			@ opposite logic test to branch over
					@   is stmts
	mov	r0, 1			@ Set r0 as 1, return odd
	b	end_if_else		@ branch always over else block

else:
	mov	r1, 0			@ Set r0 as 0, return even
 
end_if_else:
  
@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@   return
