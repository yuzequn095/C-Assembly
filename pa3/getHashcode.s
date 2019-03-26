/* 
 * Filename: getHashcode.s
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 27th, 2019
 * Source of Help: None
 */

@ Raspberry Pi directives
	.cpu	cortex-a53		@ Version of our Pis
	.syntax	unified			@ Modern ARM syntax

	.equ	FP_OFFSET, 4		@ Offset from sp to set fp
	
	.equ	PARAM_SPACE, 8
	.equ	LOCAL_SPACE, 8
	.equ	HASH_OFFSET, -8
	.equ	IDX_OFFSET, -12
	.equ	COUNT_OFFSET, -16

	.global	getHashcode		@ Specify getHashcode as a global

	.text				@ Switch to Text segment
	.align 2			@ Align on evenly divisibly by 4 byte
					@  address, .align 2^n alignment

/*
 * Function Name: getHashCode()
 * Funtcion Prototype: unsigned int getHashcode( unsigned char counts[] );
 * Description: Generate a hashcode from the counts array.
 * Parameters: counts - the array will generate hash code
 * Side Effects: None.
 * Error Condition: NOne.
 * Return value: hash - the hash code
 * Registers used:
 *      r0 - arg 1 - counts
 * Stack Variables:
 *      hash - [fp - 8] -- hash value
 *      idx - [fp - 12] -- index in loop
 *      count - [fp - 16] -- counts 
 */
getHashcode:
	@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers
	sub	sp, sp, LOCAL_SPACE	@ Allocate space for local var
	sub	sp, sp, PARAM_SPACE	@ Allocate space for parameter
	
	@ Incoming parameters in r0
	str	r0, [fp, COUNT_OFFSET]	@ Store param counts

	@ Set hash
	ldr	r1, =HASH_START_VAL_G;	@ load address inglobal
	ldr	r1, [r1]		@ load hash_start
	str	r1, [fp, HASH_OFFSET]	@ store hash

	@ For loop
	mov	r1, 0
	str	r1, [fp, IDX_OFFSET]	@ i = 0
	ldr	r1, [fp, IDX_OFFSET]	@ get i
	ldr	r2, =ALPHABET_SIZE_G	@ get address
	ldr	r2,[r2]			@ get alphabet_size
	cmp	r1, r2			@ i >= alphabet_size
	bge	END_LOOP		@ opposite logic
LOOP:
	ldr	r1, [fp, HASH_OFFSET]	@ get hash
	ldr	r2, =HASH_PRIME_G	@ get address
	ldr	r2, [r2]		@ get prime
	mul	r1, r1, r2		@ hash * prime
	ldr	r0, [fp, COUNT_OFFSET]	@ get count
	ldr	r3, [fp, IDX_OFFSET]	@ get i
	ldrb	r0, [r0, r3]		@ get counts[i]
	add	r0, r0, r1		@ hash * prime + counts[i]
	str	r0, [fp, HASH_OFFSET]	@ store hash

	ldr	r1, [fp, IDX_OFFSET]	@ get i
	add	r1, r1, 1		@ i++
	str	r1, [fp, IDX_OFFSET]	@ save idx

	ldr	r1, [fp, IDX_OFFSET]	@ get i
	ldr	r2, =ALPHABET_SIZE_G	@ get address
	ldr	r2, [r2]		@ get value
	cmp	r1, r2			@ i < alphabet
	blt	LOOP			@ positive logic
END_LOOP:
	@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@  return
