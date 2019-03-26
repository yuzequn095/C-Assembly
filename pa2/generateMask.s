/* 
 * Filename: generateMask.s
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 5th, 2019
 * Source of Help: Slide form DI
 */

@ Raspberry Pi directives
	.cpu	cortex-a53		@ Version of our Pis
	.syntax	unified			@ Modern ARM syntax

	.equ	FP_OFFSET, 4

	.equ	PARAM_SPACE, 16
	.equ	KEY_OFFSET, -8
	.equ	PP_OFFSET, -12
	.equ	MASK_OFFSET, -16
	
	.equ	MASK_SIZE, 8

	.global	generateMask		@ Specify the global symbol

	.text				@ Switch to text segment
	.align 2			@ Align on evenly divisibly by 4 byte
					@  address .align n where 2^n
					@  determines alignment

/*
 * Function Name: generateMask()
 * Function Prototype: void generateMask( unsigned char keys[], unsigned char
 * 					passphrase[], unsigned char mask[] );
 * Description: Generates the 64-bit mask used for encryption from keys and
 * 		passphrase.
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: None.
 * Registers used:
 *	r0 - arg 1 -- key
 *	r1 - arg 2 -- passphrase
 *	r2 - arg 3 -- mask
 *
 * Stack Variables:
 *	key - [fp - 8] -- holds the key array
 *	passphrase - [fp - 12] -- holds the passphrase array
 *	mask - [fp - 16] -- holds the mask array
 */

generateMask:
	@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers

	sub	sp, sp, PARAM_SPACE	@ Set param space

	@ Incoming parameters 
	str	r0, [fp, KEY_OFFSET]	@ Store key
	str	r1, [fp, PP_OFFSET]	@ Store passphrase
	str	r2, [fp, MASK_OFFSET]	@ Store mask

	@ Call function
	ldr	r0, [fp, KEY_OFFSET]	@ get key
	ldr	r1, [fp, PP_OFFSET]	@ get passphrase
	ldr	r2, [fp, MASK_OFFSET]	@ get mask
	mov	r3, MASK_SIZE		@ get byte num
	bl	xorBytes		@ call xorBytes

	@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore lr into for 
					@   return
