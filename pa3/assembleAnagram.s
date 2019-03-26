/*
 * Filename: assembleAnagram.s
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 27th, 2019
 * Source of Help: None.
 */

@ Raspberry Pi directives
	.cpu	cortex-a53	@ Version of our Pis
	.syntax	unified		@ Modern ARM syntax

	.equ	FP_OFFSET, 4	@ Offset from sp to set fp
	
	.equ	LOCAL_SPACE, 16
	.equ	COUNT_OFFSET, -8
	.equ	HASH_OFFSET, -12
	.equ	LEN_OFFSET, -16
	.equ	PARAM_SPACE, 8
	.equ	ORIWORD_OFFSET, -24
	.equ	ANA_OFFSET, -28
	

	.global assembleAnagram	@ Specify assembleAnagram as a global symbol

	.text			@ Switch to Text segment
	.align 2		@  .align n where 2^n determines alignment

/*
 * Function Name: assembleAnagram()
 * Function Prototype: void assembleAnagram( const char *originalWord, 
 *                                           anagram_t *anagram )
 * Description: Assemble an anagram_t struct
 * Parameters: originalWord - the string passed in 
 *             anagram - the struct
 * Side Effects: None.
 * Error Conditions: none.
 * Return Value: None.
 * Registers used:
 *         r0 - arg 1 - originalWord
 *         r1 - arg 2 - anagram
 * Stack Variables:
 *         count - [fp - 8] - the array
 *         hash - [fp - 12] - the hash value
 *         len - [fp - 16] - the length
 */

assembleAnagram:
	@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers
	sub	sp, sp, LOCAL_SPACE	@ Allocate space for local var
	sub	sp, sp, PARAM_SPACE	@ Allocate space for param
	
	@ Incoming param in r0, r1
	str	r0, [fp, ORIWORD_OFFSET]@ store param1	
	str	r1, [fp, ANA_OFFSET]	@ store param2
	
	ldr	r0, [fp, ANA_OFFSET]	@ load ana
	ldr	r1, =ORIGINAL_WORD_OFFSET_G 
	ldr	r1, [r1]		@ load value
	add	r0, r0, r1
	ldr	r1, [fp, ORIWORD_OFFSET]
	ldr	r2, =MAX_WORD_SIZE_G
	ldr	r2, [r2]
	bl	strncpy			@ call function
	
	@ set null terminate
	ldr	r0, [fp, ANA_OFFSET]	@ get struct
	ldr	r1, =ORIGINAL_WORD_OFFSET_G
	ldr	r1, [r1]		@ get word value
	add	r0, r0, r1		@ get adrress
	ldr	r1, =MAX_WORD_SIZE_G	@ get max word
	ldr	r1, [r1]		@ get value
	sub	r1, r1, 1		@ get correct idx
	mov	r2, 0			@ move null in .s
	strb	r2, [r0, r1]
	
	@ Assemble counts
	ldr	r0, [fp, ANA_OFFSET]
	ldr	r1, =COUNTS_OFFSET_G	@ get address
	ldr	r1, [r1]		@ get value
	add	r0, r0, r1
	ldr	r1, [fp, ORIWORD_OFFSET]
	bl	countChars		@ call function and set counts

	@ Assemble hashcode
	ldr	r0, [fp, ANA_OFFSET]
	ldr	r1, =COUNTS_OFFSET_G	@ get address
	ldr	r1, [r1]		@ get value
	add	r0, r0, r1
	bl	getHashcode		@ call function
	ldr	r1, [fp, ANA_OFFSET]
	ldr	r2, =HASHCODE_OFFSET_G
	ldr	r2, [r2]
	str	r0, [r1, r2]		@ store hash in struct

	@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@  return
