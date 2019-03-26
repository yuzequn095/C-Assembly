/* 
 * Filename: printChar.s
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Jan 25th, 2019
 * Source of Help: None.
 */

 @ Raspberry Pi directives
 	.cpu		cortex-a53	@ Version of our Pis
	.syntax		unified		@ Modern ARM syntax

	.equ		FP_OFFSET, 4	@ Offset from sp to set fp
	
	.section	.rodata

fmt:	.asciz		"%c"

	.global	printChar	@ Specify printChar as a global name

	.text			@ Switch to next segment
	.align 2		@ Align on evenly divisible by 4 byte address 
				@  .align n where 2^n determines alignment

/*
 * Function Name: printChar()
 * Function Protytype: void printChar( char c );
 * Description: Prints the character argument to stdout.
 * Parameters: char - the character to be printed
 * Side Effects: Print strings.
 * Error Consitions: None.
 * Return Value: The character.
 * 
 * Registers used:
 *      r0 - arg 1 -- c
 *	r1 - local var -- char to be printed
 */
 printChar:
 	@ Standard prologue
	push	{fp, lr}		@ Save registers on the stack.
	add	fp, sp, FP_OFFSET	@ Sets fp to point at bottom of saved
					@   regs.

	mov	r1, r0			@ Moves string param to r1 as arg to 
					@   printf.
	ldr	r0, =fmt		@ Gets address  of format string.
	bl	printf			@ Calls printf.

	@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Reset sp to point to top of saved 
					@   regs.
	pop	{fp, pc}		@ Returns from function.
