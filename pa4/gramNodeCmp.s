/*
 * Filename: gramNodeCmp.s
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Mar 5th, 2019
 * Source of Help: None
 */

@ Raspberry Pi directives
	.cpu	cortex-a53		@ Version of our Pis
	.syntax	unified			@ Modern ARM syntax

	.equ	FP_OFFSET, 4		@ Offset from sp to set fp
	.equ	LOCAL_SPACE, 8
	.equ	V1_OFFSET, -8
	.equ	V2_OFFSET, -12
	.equ	PARAM_SPACE, 8		
	.equ	P1_OFFSET, -16
	.equ	P2_OFFSET, -20

	.global	gramNodeCmp		@ Specify the global symbol

	.text				@ Switch to Text segment
	.align 2			@ Align on evenly divisibly by 4 byte
					@   address

/*
 * Function Name: gramNodeCmp()
 * int gramNodeCmp( const void * p1, const void * p2 );
 * Description: This function takes two pointers to gramNode_t and compare
 * Parammeters: p1 - the first struct pointer
 *              p2 - the second struct pointer
 * Side Effects: None.
 * Error Condition: None.
 * Return Value: -1 if p1 < p2; 0 if equal; 1 if p1 > p2
 * Registers used: 
 *              r0 - the pointer to first struct
 *              r1 - the pointer to second struct
 * Stack Variables:
 *		v1 - [fp - 8] - the first value
 *		v2 - [fp - 12] - the second value
 *              p1 - [fp - 16] - the first struct
 *              p2 - [fp - 20] - the second struct
 */
 gramNodeCmp:
 	@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers
	sub	sp, sp, LOCAL_SPACE	@ Allocate space for local
	sub	sp, sp, PARAM_SPACE	@ Allocate space for param

	@ Incoming parameters in r0, r1
	str	r0, [fp, P1_OFFSET]	@ store p1
	str	r1, [fp, P2_OFFSET]	@ store p2

	ldr	r0, [fp, P1_OFFSET]	@ load p1
	ldr	r2, =INDEX_OFFSET_G	@ get index to compare
	ldr	r2, [r2]	
	ldr	r0, [r0, r2]		@ get value of p1.index
	str	r0, [fp, V1_OFFSET]	@ store v1

	ldr	r1, [fp, P2_OFFSET]	@ load p2
	ldr	r2, =INDEX_OFFSET_G	@ get index to compare
	ldr	r2, [r2]		
	ldr	r1, [r1, r2]		@ get value of p2.index
	str	r1, [fp, V2_OFFSET]	@ store v2
	
	ldr	r0, [fp, V1_OFFSET]	@ load v1
	ldr	r1, [fp, V2_OFFSET]	@ load v2
	cmp	r0, r1			@ r0 >= r1
	bge	ELSE_IF			@ opposite logic
	
	mov	r0, -1			@ set return value
	b	END
ELSE_IF:
	ldr	r0, [fp, V1_OFFSET]	@ load v1
	ldr	r1, [fp, V2_OFFSET]	@ load v2
	cmp	r0, r1			@ r0 != r1
	bne	ELSE			@ opposite logic

	mov	r0, 0			@ set return value
	b	END
ELSE:
	mov	r0, 1			@ set return value
END:
	@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set fp to top of saved registers
	pop	{fp, pc}		@   return
