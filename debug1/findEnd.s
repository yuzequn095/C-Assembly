/*
 * Filename: findEnd.s
 * Description: Assembly function that traverses a string and returns the
 *              length of the string and stores a pointer to the last char.
 */

	.cpu	cortex-a53
	.syntax	unified

	.equ	FP_OFFSET, 4
	.equ	LOCAL_VAR_SPACE, 8
	.equ	PARAM_VAR_SPACE, 8

	.equ	STR_LENGTH_OFFSET, -8
	.equ	STR_PTR_OFFSET, -16
	.equ	ENDPTR_OFFSET, -20

	.global	findEnd
	.text
	.align	2

/*
 * Function name: findEnd()
 * Function prototype: int findEnd(char* str, char** endPtr)
 * Description: Takes in a string and a char**.  Traverses string until it
 *              finds the null character.  Stores pointer to the last char
 *              of the string in the endPtr parameter. Returns strLength.
 * Parameters: $r0 - string to find length of
 *             $r1 - char** endPtr, to store ptr to last char, for use in
 *                   calling function
 * Side Effects: Stores ptr to last char of str in char** endPtr
 * Return Value: length of string
 * fp - 8	--- int strLength
 * PADDING
 * fp - 16	--- STR
 * fp - 20	--- ENDPTR
 */

findEnd:
@ Standard prologue
	push	{fp, lr}
	add	fp, sp, FP_OFFSET

	sub	sp, sp, LOCAL_VAR_SPACE		@ local var space
	sub	sp, sp, PARAM_VAR_SPACE		@ formal param space

	str	r0, [fp, STR_PTR_OFFSET]	@ store strPtr
	str	r1, [fp, ENDPTR_OFFSET]		@ store endptr

	mov	r2, 0				@ strLength = 0
	str	r2, [fp, STR_LENGTH_OFFSET]	@ store strLength

	ldr	r0, [fp, STR_PTR_OFFSET]	@ load strPtr
	mov	r3, r0				@ endChar = strPtr

	ldrb	r3, [r3]	@ *strPtr

	cmp	r3, 0		@ if *strPtr == '\0', this is empty string
	beq	emptyStr	@ skip loop to find last char

checkChar:

	add	r0, r0, 1	@ increment strPtr to look at next char
	str	r0, [fp, STR_PTR_OFFSET]	@ store strPtr

	ldr	r2, [fp, STR_LENGTH_OFFSET]	@ load strLength
	add	r2, r2, 1			@ increment strLength
	str	r2, [fp, STR_LENGTH_OFFSET]	@ store strLength

	mov	r3, r0				@ endChar = strPtr
	ldrb	r3, [r3]			@ *strPtr

	cmp	r3, 0				@ if *strPtr == '\0', end loop
	bne	checkChar

	ldr 	r0, [fp, STR_PTR_OFFSET] 	@ load strPtr
	add	r3, r0, -1	@ adjust strPtr to point back to last char

emptyStr:

	ldr	r1, [fp, ENDPTR_OFFSET]		@ load endptr
	str	r3, [r1]			@ store ptr to last char
	ldr	r2, [fp, STR_LENGTH_OFFSET]	@load strLength
	mov	r0, r2				@ return strLength

@ Standard epilogue
	sub	sp, fp, FP_OFFSET
	pop	{fp, pc}
