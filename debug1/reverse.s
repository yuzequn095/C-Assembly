/*
 * Filename: reverse.s
 * Description: Assembly function that reverses the characters of a string
 *              and determines whether the string was a palindrome.
 */
	.cpu	cortex-a53
	.syntax unified	
	.equ	FP_OFFSET, 4
	.equ	LOCAL_VAR_SPACE, 16
	.equ	PARAM_VAR_SPACE, 8
	
	.equ	ENDPTR_OFFSET, -8
	.equ	START_PTR_OFFSET, -12
	.equ	STR_LENGTH_OFFSET, -16
	.equ	STR_PTR_OFFSET, -24

	.section	.rodata
palStr:
	.asciz	"PALINDROME!\n"
	.align 2
	.global	reverse

/*
 * Function name: reverse()
 * Function prototype: int reverse(char* str)
 * Description: Takes in a char*, finds the end of the string, and traverses
 *              the string, swapping characters. At the end, if all swapped
 *              characters matched, returns 1 to indicate it was a palindrome.
 * Parameters: %i0 - string to reverse
 * Side Effects: Prints message if the string is a palindrome
 * Return Value: 0 indicating string not a palindrome
 *               1 indicating string is a palindrome
 *	fp - 8  --- char * endptr
 *	fp - 12 --- char * startPtr
 *	fp - 16 --- int strLength
 *	PADDING
 *	fp - 24 --- char* str
 *	PADDING
 */

reverse:
	push	{fp, lr}
	add	fp, sp, FP_OFFSET

	sub	sp, sp, LOCAL_VAR_SPACE		@ local var space
	sub	sp, sp, PARAM_VAR_SPACE		@ formal param space

	str	r0, [fp, STR_PTR_OFFSET]	@ store str ptr

	/* Find length of str and ptr to last char */
	ldr	r0, [fp, STR_PTR_OFFSET]@ ptr to string as first arg to findEnd
	add	r1, fp, ENDPTR_OFFSET	@ ptr to store ptr to
	bl	findEnd			@  last char as second arg

	str	r0, [fp, STR_LENGTH_OFFSET]	@ strLength

	ldr	r0, [fp, STR_PTR_OFFSET]	@ point to the start of str
	str	r0, [fp, START_PTR_OFFSET]	@ startPtr --> str
	ldr	r1, [fp, ENDPTR_OFFSET]		@ endPtr

	cmp	r0, r1		@ while startPtr <= endPtr, swap chars
	bgt	endSwapLoop

swapLoop:

	ldr	r0, [fp, START_PTR_OFFSET]	@ startPtr as first arg
	ldr	r1, [fp, ENDPTR_OFFSET]		@ endPtr as second arg
	bl	swapChars			@ swap 'em

	ldr	r1, [fp, STR_LENGTH_OFFSET]	@ subtract number of same chars
	sub	r1, r1, r0			@ from strLength
	str	r1, [fp, STR_LENGTH_OFFSET]

	ldr	r0, [fp, START_PTR_OFFSET]	@ increment startPtr
	add	r0, r0, 1
	str	r0, [fp, START_PTR_OFFSET]
	
	ldr	r1, [fp, ENDPTR_OFFSET]		@ decrement endPtr
	sub	r1, r1, 1
	
	str	r1, [fp, ENDPTR_OFFSET]

	cmp	r0, r1		@ while startPtr <= endPtr, swap chars
	ble	swapLoop

endSwapLoop:

	ldr	r0, [fp, STR_LENGTH_OFFSET]	@ get the final strLength

	cmp	r0, 0
	bne	not_palindrome	@ if strLength == 0, then all chars were matched

	ldr	r0, =palStr
	bl	printf

	mov	r0, 1		@ set 1 as return value
	b	end

not_palindrome:
	mov	r0, 0
end:
	sub	sp, fp, FP_OFFSET
	pop	{fp, pc}
