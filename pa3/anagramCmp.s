/*
 * Filename: anagramCmp.s
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 27th, 2019
 * Source of Help: None.
 */

@ Raspberry Pi directives
	.cpu	cortex-a53		@ Version of our Pis
	.syntax	unified			@ Modern ARM syntax

	.equ	FP_OFFSET, 4		@ Offset from sp to set fp

	.equ	LOCAL_SPACE, 8
	.equ	RETURN_ONE, -8
	.equ	RETURN_TWO, -12
	.equ	PARAM_SPACE, 8
	.equ	PARAM_ONE, -16
	.equ	PARAM_TWO, -20

	.global	anagramCmp		@ Specify global name

	.text				@ Switch to Text segment
	.align 2			@ Align on evenly divisibly by 4 byte
					@ address

/*
 * Function Name: anagramCmp()
 * int anagramCmp( const void * p1, const void * p2 )
 * Description: compare two anagram
 * Parameters: p1 - the first anagram pointer
 *             p2 - the second anagram pointer
 * Side Effects: None
 * Error Conditions: None.
 * Return Value: -1 - smaller hashcode or same hashcode and smaller countsCmp
 *               +1 - larger hashcode or same hashcode and larger countsCmp
 * Stack Variables:
 *            return1 - [fp - 8] - the first return value
 *            return2 - [fp - 12] - the second return value
 */
anagramCmp:
	@ Standard prologue
	push    {fp, lr}                @ Save registers: fp, lr
	add     fp, sp, FP_OFFSET       @ Set fp to base of saved registers
	sub     sp, sp, LOCAL_SPACE     @ Allocate space for local
	sub	sp, sp, PARAM_SPACE	@ Allocate space for parameter

	@ Incoming parameters in r0, r1
	str	r0, [fp, PARAM_ONE]
	str	r1, [fp, PARAM_TWO]

	ldr	r0, [fp, PARAM_ONE]
	ldr	r1, [fp, PARAM_TWO]

	@ compare hashcode
	bl	hashcodeCmp		@ call function
	str	r0, [fp, RETURN_ONE]	@ save return value
	
	@ complare counts
	ldr	r0, [fp, PARAM_ONE]	
	ldr	r1, [fp, PARAM_TWO]

	bl	countsCmp		@ call function
	str	r0, [fp, RETURN_TWO]	@ save return value

	@ Check return value
	ldr	r0, [fp, RETURN_ONE]
	cmp	r0, -1			@ return1 == -1
	beq	NEG_CASE		@ positive logic
	
	ldr	r0, [fp, RETURN_ONE]
	cmp	r0, 0			@ return 1 != 0
	bne	else			@ opposite logic

	ldr	r1, [fp, RETURN_TWO]
	cmp	r1, -1			@ return 2 != 0
	bne	else			@ opposite logic

	b 	NEG_CASE

else:
	ldr	r0, [fp, RETURN_ONE]
	ldr	r1, [fp, RETURN_TWO]
	cmp	r0, 0			@ return1 != 0
	bne	else_two		@ opposite logic
	
	cmp	r1, 0			@ return 2 != 0
	bne	else_two		@ opposite logic

	b	ZERO_CASE
else_two:
	ldr     r0, [fp, RETURN_ONE]
	ldr     r1, [fp, RETURN_TWO]
	
	cmp	r0, 1			@ return 1 == 1
	beq	ONE_CASE		@ positive

	cmp	r0, 0			@ return 1 != 0
	bne	END			@ consider above

	cmp	r1, 1			@ return 2 != 1
	bne	END			@ consider above

	b	ONE_CASE

NEG_CASE:
	mov	r0, -1
	b	END
ONE_CASE:
	mov	r0, 1
	b	END
ZERO_CASE:
	mov	r0, 0
END:

	@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@   return
