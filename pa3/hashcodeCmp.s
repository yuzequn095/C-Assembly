/* 
 * Filename: hashcodeCmp.s
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 27th, 2019
 * Source of Help: None.
 */

@ Raspberry Pi directives
	.cpu	cortex-a53		@ Version of our Pis
	.syntax	unified			@ Modern ARM syntax

	.equ	FP_OFFSET, 4		@ Offset from sp to set fp

	.equ	LOCAL_SPACE, 8
	.equ	FIRST_HASH, -8
	.equ	SECOND_HASH, -12

	.global	hashcodeCmp		@ Specify hashcodeCmp as a global

	.text				@ Switch to Text segment
	.align 2			@ Align on evenly divisibly by 4 byte
					@  address, .align 2^n alignment
/*
 * Function Name: hashcodeCmp.s
 * Function Prototype: int hashcodeCmp( const void * p1, const void * p2 )
 * Description: Compare two hash code
 * Parameters: p1 - hash code 1
 *             p2 - hash code 2
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: -1 if smaller hash code
 *               +1 if larger hash code
 *                0 if same hash code
 * Registers used:
 *               r0 - arg 1 - the fisrt code
 *               r1 - arg 2 - the second code
 * Stack Variables:
 *               first - [fp -8] - the hash 1
 *               second - [fp - 12] - the hash 2
 */
hashcodeCmp:
	@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers
	sub	sp, sp, LOCAL_SPACE	@ Allocate space for parameter

	@ Incoming parameters in r0, r1
	ldr	r2, =HASHCODE_OFFSET_G
	ldr	r2, [r2]		@ get value of hashcode

	ldr	r0, [r0, r2]		@ get a1.hashcode
	ldr	r1, [r1, r2]		@ get a2.hashcode
	str	r0, [fp, FIRST_HASH]	@ store a1
	str	r1, [fp, SECOND_HASH]	@ store a2
	ldr	r0, [fp, FIRST_HASH]
	ldr	r1, [fp, SECOND_HASH]
	cmp	r0, r1			@ a1.hashcode <= a2.hashcode
	bls	END_IF			@ opposite logic to skip
IF:
	mov	r0, 1			@ >
	b	END_CMP			@ branch always over rest block

END_IF:
	ldr     r0, [fp, FIRST_HASH]
	ldr     r1, [fp, SECOND_HASH]
	cmp	r0, r1			@ a1 < a2
	blo	ELSE			@ opposite logic to skip

	mov	r0, 0			@ =
	b	END_CMP	
ELSE:
	mov	r0, -1			@ <
	b END_CMP			@ branch skip
	
END_CMP:
	@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@  return
