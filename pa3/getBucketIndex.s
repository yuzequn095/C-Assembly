/*
 * Filename: getBucketIndex.s
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 27th, 2019
 * Source of Help: None.
 */

@ Raspberry Pi directives
	.cpu	cortex-a53		@ Version of our Pis
	.syntax	unified			@ Modern ARM syntax

	.equ	FP_OFFSET, 4		

	.global	getBucketIndex		@ Specify the global name

	.text				@ Swtich to Text segment
	.align 2			@ Align on evenly divisibly by 4 byte
					@  addreass

/*
 * Functio Name: getBucketIndex()
 * Function Prototype: unsigned int getBucketIndex( unsigned int hashcode,
 *                    size_t tableSize)
 * Description: calculate the bucket index.
 * Parameters: hashcode - the revalue of hash code
 *             tableSize - the value of table size
 * Side Effects: None
 * Error Conditions: None.
 * Return Value: the index
 * Registers used: 
 *        r0 - arg 1 - hashcode
 *        r1  - arg 2 - tableSize
 */

getBucketIndex:
	@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers

	@ call function with incoming parameters
	bl	getURemainder

	@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@   return
