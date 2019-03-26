/*
 * Filename: xorBytes.s
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 5th, 2019
 * Source of Help: Slide from di
 */

@ Raspberry Pi directives
	.cpu	cortex-a53		@ Version of our Pis
	.syntax	unified			@ Modern ARM syntax

	.equ	FP_OFFSET, 4	

	.equ	LOCAL_SPACE, 8
	.equ	I_OFFSET, -8

	.equ	PARAM_SPACE, 16
	.equ	ORI_OFFSET, -16
	.equ	MASK_OFFSET, -20
	.equ	CIP_OFFSET, -24
	.equ	NUM_OFFSET, -28

	.global	xorBytes		@ Specify the global symbol

	.text				@ Switch to text segment
	.align 2			@ Align on evenly divisibly by 4 byte
					@  address .align n where 2^n
					@  determines alignment

/*
 * Function Name: xorBytes()
 * Function Prototype: void xorBytes( unsigned char originalText[], unsigned
 * 				      char mask[], unsigned char cipherText[],
 *				      unsigned int numBytes );
 * Description: Encrypts by XORing a mask over the original plaintext to
 * 		generate a ciphertext.
 * Parameters: originalText - the array of original text
 *	       mask - the array of mask
 *	       cipherText - the array of cipher text
 *	       numBytes - the number to mask
 * Side Effects: None.
 * Error Condistion: None.
 * Return Value: None.
 * Registers used:
 *	r0 - arg 1 - originalText
 *	r1 - arg 2 - mask
 *	r2 - arg 3 - cipherText
 *	r3 - arg 4 - numByte
 *
 * Stack Variables:
 *	I - [fp - 8] -- loop index
 *	oriText - [fp - 16] -- array of plain text
 *	mask - [fp - 20] -- array of mask
 *	cipText - [fp - 24] -- array of cipher text
 *	numByte - [fp - 28] -- number to encrypt
 */
xorBytes:
	@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers

	sub	sp, sp, LOCAL_SPACE	@ Set local var space
	sub	sp, sp, PARAM_SPACE	@ Set param space

	@ Incoming parameters in r0 - r3
	@ Store params
	str	r0, [fp, ORI_OFFSET]	
	str	r1, [fp, MASK_OFFSET]
	str	r2, [fp, CIP_OFFSET]
	str	r3, [fp, NUM_OFFSET]

	@ Use loop to encrypt
	mov	r3, 0			
	str	r3, [fp, I_OFFSET]	@ i = 0
	ldr	r3, [fp, I_OFFSET]	@ get current value of i
	ldr	r2, [fp, NUM_OFFSET]	@ get current numByte
	cmp	r3, r2			@ i >= numByte
	bge	end_loop		@ opposite logic test to skip over loop
loop:
	/* Loop Body */
	@ get originalText[i]
	ldr	r0, [fp, I_OFFSET]	@ get current value of i 
	@lsl	r3, r3, 0		@ scaled index: sizeof(char) = 1
	@add	r3, r3, ORI_OFFSET	@ array offset from fp + scaled index
	ldr	r3, [fp, ORI_OFFSET]	@ get array ptr 
	ldrb	r3, [r3, r0]		@ get value
	@ldrb	r3, [fp, r3]		@ ldr char

	@ get mask[i]
	ldr	r0, [fp, I_OFFSET]	@ get same i value
	@lsl	r2, r2, 0		@ same as above
	@add	r2, r2, MASK_OFFSET	@ array offset from fp + scaled index
	ldr	r2, [fp, MASK_OFFSET]
	ldrb	r2, [r2, r0]		@ ldr char
	
	@ Encrypt
	eor	r1, r2, r3		@ ori[i] ^ mask[i]

	@ store cipherText[i]
	ldr	r2, [fp, I_OFFSET]	@ same as above
	@lsl	r2, r2, 0		@ same as above
	@@add	r2, r2, CIP_OFFSET	@ array offset from fp + scaled index
	ldr	r3, [fp, CIP_OFFSET]	@ get array ptr
	strb	r1, [r3, r2]		@ store char
	
	@ check I
	ldr	r3, [fp, I_OFFSET]	@ get current value of i 
	add	r3, r3, 1		@ i ++
	str	r3, [fp, I_OFFSET]	@ i = i+1
	ldr	r3, [fp, I_OFFSET]	@ get i 
	ldr	r2, [fp, NUM_OFFSET]	@ get numByte
	cmp	r3, r2			@ i < numByte
	blt	loop			@ positive logic test

end_loop:

	@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore lr into for 
					@  return
	
