/*
 * Filename: countsCmp.s
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 27th, 2019
 * Source of Help: None.
 */


@ Raspberry Pi directives
	.cpu	cortex-a53		@ Version of our Pis
	.syntax	unified			@ Modern ARM syntax

	.equ	FP_OFFSET, 4		@ Offset from sp to set fp


	.global	countsCmp		@ Specify countsCmp as a global name

	.text				@ Switch to Text segment
	.align 2			@ Alaign on evenly divisibly by 4 byte
					@   address

/*
 * Function Name: countsCmp()
 * Function Prototype: int countsCmp( const void *p1, const void *p2 )
 * Description: Compare two counts.
 * Parameters: p1 - the first counts pointer
 *             p2 - the second counts pointer
 * Side Effect: None.
 * Return Value: value of memcmp.
 * Registers used:
 *      r0 - arg 1 - the first counts pointer
 *      r1 - arg 2 - the second counts pointer
 *
 */
countsCmp:
	@ Standard prologue
	push    {fp, lr}                @ Save registers: fp, lr
	add     fp, sp, FP_OFFSET       @ Set fp to base of saved registers

	@ Incoming parameters in r0, r1
	ldr	r2, =COUNTS_OFFSET_G	@ load address
	ldr	r2, [r2]		@ load value

	add     r0, r0, r2		@ get a1.counts
	add     r1, r1, r2		@ get a2.counts
	ldr	r2, =ALPHABET_SIZE_G	@ load address
	ldr	r2, [r2]		@ load value

	bl	memcmp			@ call function

	@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set fp to top of saved registers
	pop	{fp, pc}		@ return
