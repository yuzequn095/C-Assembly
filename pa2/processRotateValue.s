/*
 * Filename: processRotateValue.s
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 4th, 2019
 * Source of Help: Slide from DI
 */

@ Raspberry Pi directives
	.cpu	cortex-a53		@ Version of our pis
	.syntax	unified			@ Modern ARM syntax

	.equ	FP_OFFSET, 4
	
	.equ	LOCAL_SPACE, 8
	.equ	END_PTR, -8 
	.equ	CON_NUM, -12

	.equ	PARAM_SPACE, 8
	.equ	STR_OFFSET, -16
	.equ	ROTATE_VALUE, -20
	
	.equ	NULL_BYTE, '\0'

	.global	processRotateValue	@ Specify the global symbol

	.text				@ Switch to text segment
	.align 2			@ Align on evenly divisibly by 4 byte
					@  address .align n where 2^n
					@  determines alignment

/*
 * Function Name: processRotateValue()
 * Function Prototype: int processRotateValue( char * str, int * rotateValue );
 * Description: This function will convert the rotate value from string to int.
 * Parameters: str - the value entered
 *	       rotateValue - the value to be stored
 * Side Effects: Functions print error information.
 * Error Conditions: Too large, invalid char and out of range in str.
 * Return Value: If the conversion was successful, the rotate value is stored
 *               in the output parameter (rotateValue), and 0 is returned. 
 *		 Otherwise, return the appropriate error value
 * 
 * Registers used:
 *	r0 - arg 1 - str
 *	r1 - arg 2 - rotateValue
 *
 * Stack Variables:
 *	endPtr - [fp - 8] -- holds the endptr
 *	con_num - [fp - 12] -- holds the converted number
 *	str - [fp - 16] -- holds the str
 *	rotateValue - [fp - 20] -- holds the rotateValue
 */

processRotateValue:
	@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp tp base of saved registers
	
	sub	sp, sp, LOCAL_SPACE	@ Set local var space
	sub	sp, sp, PARAM_SPACE	@ Set param space
	
	@ Incoming parameters in r0, r1
	str	r0, [fp, STR_OFFSET]	@ Store str
	str	r1, [fp, ROTATE_VALUE]	@ Store rotateValue
	
	@ Convert str from string to int
	@ Set errno = 0
	bl	__errno_location	@ Call function; errno now in r0 
	mov	r1, 0			@ Puts 0 in r1
	str	r1, [r0]		@ Set errno = 0 by storing memory
					@  address of errno
	@ call function
	ldr	r0, [fp, STR_OFFSET]	@ Set str as 1st argument
	add	r1, fp, END_PTR		@ Set &endptr as 2nd argument
	mov	r2, 0			@ Set BASE as 3rd argument
	bl	strtol			@ Call function
	str	r0, [fp, CON_NUM]	@ Save number to local var
	
	@ Check errors
	@ Check too large
	@ ldr	r1, =ERANGE_ERR_G	@ Get ERANGE
	@ ldr	r1, [r1]		@ Get value
	bl	__errno_location	@ Load address of errno
	mov	r3, r0			@ Put address of errno in r3
	ldr	r3, [r3]		@ Get the value of errno
	cmp	r3, 0			@ errno != 0
	beq	END_LARGE		@ opposite logic test to branch over if
	/* If Statements */
	ldr	r0, =ERANGE_ERR_G	@ get value
	ldr	r0, [r0]
	b	END_ERROR		@ branch over rest if stmts
END_LARGE:
	@ Check invalid char
	ldr	r0, [fp, END_PTR]	@ Get endPtr
	ldrb	r0, [r0]
	@ldr	r1, [fp, STR_OFFSET]	@ Get str
	@mov	r1, NULL_BYTE
	cmp	r0, 0			@ endPtr != str
	beq	END_CHAR		@ opposite logic test to brach over if
	/* If Statements */
	ldr	r0, =ENDPTR_ERR_G	@ Set return value
	ldr	r0, [r0]
	b	END_ERROR		@ branch over rest if stmts
END_CHAR:
	@ Check bounds
	ldr	r0, [fp, CON_NUM]	@ Get converted number
	ldr	r1, =MIN_ROTATE_G 	@ Set 2nd argument
	ldr	r1, [r1]
	ldr	r2, =MAX_ROTATE_G	@ Set 3rd argument
	ldr	r2, [r2]
	bl	isInBounds		@ call function
	cmp	r0, 1			@ result == 1
	beq	END_RANGE		@ opposite logic test to branch over if
	ldr	r0, =BOUND_ERR_G	@ Set return value
	ldr	r0, [r0]
	@mov	r0, 0
	b	END_ERROR		@ branch
END_RANGE:
	@ldr     r0, =BOUND_ERR_G
	@ldr     r0, [r0]
	mov	r0, 0
END_ERROR:	
	@ update value
	@sub	r1, fp, CON_NUM
	@str	r1, [fp, ROTATE_VALUE]
	ldr	r1, [fp, CON_NUM]
	ldr	r2, [fp, ROTATE_VALUE]
	str	r1, [r2]
	@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore lr into for 
					@   return
