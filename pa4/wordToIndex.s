/*
 * Filename: wordToIndex.s
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Mar 5th, 2019
 * Source of Help: None.
 */

@ Raspberry Pi directives
	.cpu	cortex-a53		@ Version of our Pis
	.syntax	unified			@ Modern ARM syntax

	.equ	FP_OFFSET, 4		@ Offset from sp to set fp
	.equ	LOCAL_SPACE, 8
	.equ	PTR_WORD, -8
	.equ	PARAM_SPACE, 8
	.equ	WORD_OFFSET, -16
	.equ	VOCAB_OFFSET, -20
	.equ	FPARAM_SPACE, 8
	.equ	SIZE_CHAR, 4

	.globl	wordToIndex		@ Specify global symbol

	.text				@ Switch to Text segment
	.align 2			@ Align on evenly divisibly by 4 byte
					@   address
/*
 * Function Name: wordToIndex()
 * int wordToIndex( const char * word, vocab_t * vocab );
 * Description: Fine the index in vocab for word given
 * Parameters: word - the word given to find index
 *	       vocab - the struct for searching
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: the index or -1 if not in vocabulary.
 * Registers used:
 *		r0 - arg1 - the word
 *		r1 - arg2 - the vocab struct
 * Stack Variables:
 *		word - [fp - 8] - the word given
 *		vocab - [fp - 12] - the vocab struct
 *		strPtrCmp - [sp - 0] - the fifth param in bsearch
 */
wordToIndex:
	@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers
	sub	sp, sp, LOCAL_SPACE
	sub	sp, sp, PARAM_SPACE
	sub	sp, sp, FPARAM_SPACE

	@ Incoming parameters in r0, r1
	str	r0, [fp, WORD_OFFSET]	@ store word
	str	r1, [fp, VOCAB_OFFSET]	@ store vocab

	@ prepare the 5th argument to bsearch
	ldr	r0, =strPtrCmp		@ load function
	str	r0, [sp, 0]		@ store fifth arg

	@ call function
	add	r0, fp, WORD_OFFSET	@ get &word

	ldr	r1, [fp, VOCAB_OFFSET]	@ get vocab
	ldr	r2, =WORDS_OFFSET_G	@ get address of words
	ldr	r2, [r2]		@ get words value
	ldr	r1, [r1, r2]		@ get vocab -> words
	
	ldr	r2, [fp, VOCAB_OFFSET]	@ get vocab
	ldr	r3, =NUMWORDS_OFFSET_G	@ get address of numWords
	ldr	r3, [r3]		@ get numWords value
	ldr	r2, [r2, r3]		@ get vocab -> numWords

	mov	r3, SIZE_CHAR		@ get sizeof(char *)

	bl	bsearch			@ call function
	str	r0, [fp, PTR_WORD]	@ save the return value

	@ check if null
	ldr	r0, [fp, PTR_WORD]	@ load the return value
	cmp	r0, 0			@ r0 != NULL
	bne	ELSE			@ opposite logic

	mov	r0, -1			@ set return value
	b	END
ELSE:
	ldr	r0, [fp, PTR_WORD]	@ load the return value
	ldr	r1, [fp, VOCAB_OFFSET]
	ldr	r2, =WORDS_OFFSET_G
	ldr	r2, [r2]		@ load value
	ldr	r1, [r1, r2]		@ get vocab -> words
	sub	r0, r0, r1		@ ptrWord - vocab -> words
	mov	r1, SIZE_CHAR
	sdiv	r0, r0, r1		@ for ARM
END:
	@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set fp to top of saved registers
	pop	{fp, pc}		@  return
