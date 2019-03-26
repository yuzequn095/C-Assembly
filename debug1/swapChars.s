/*
 * Filename: swapChars.s
 * Description: Assembly function that swaps two chars and determines how many
 *              unique characters had the same value
 */
	.cpu	cortex-a53
 	.syntax	unified

	.equ	FP_OFFSET, 4
	.equ	SAME_CHAR_DIFF_PTR, 2

	.global	swapChars
	.text
	.align	2

/*
 * Function name: swapChars()
 * Function prototype: int swapChars(char* c1, char* c2)
 * Description: Takes two pointers to chars and swaps the values.  Then compares
 *              values and ptrs to determine if the characters were the same and,
 *              if so, if the ptrs were pointing to the same place.
 * Parameters: r0 - first char to swap
 *             r1 - second char to swap
 * Side Effects: Swaps two characters in memory
 * Return Value: 0 if chars were different
 *               1 if chars were same, but ptrs were to the same address
 *               2 if chars were same and ptrs were to different addresses
 */

swapChars:
@ Standard prologue
	push	{fp, lr}
	add	fp, sp, FP_OFFSET

	ldrb	r2, [r0]	@ load first char
	ldrb	r3, [r1]	@ load second char

	strb	r2, [r1]	@ store first char in second spot
	strb	r3, [r0]
	
	cmp	r2, r3		@ if first char and second char arent same,
	bne	notSame		@ return 0

	cmp	r0, r1		@ chars are same and ptrs are the same, return 1
	beq	samePtr

	mov	r0, SAME_CHAR_DIFF_PTR	@ chars same, ptrs different, return 2
	bl	end

samePtr:

	mov	r0, 1		@ chars are same, ptrs are same -- return 1
	bl end

notSame:

	mov	r0, 0

end:
@ Standard epilogue
	sub	sp, fp, FP_OFFSET
	pop	{fp, pc}
