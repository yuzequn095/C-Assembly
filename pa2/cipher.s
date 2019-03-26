/*
 * Filename: cipher.s
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 12th, 2019
 * Source of Help: Slide form Di.
 */

@ Raspberry Pi directives
	.cpu	cortex-a53		@ Version of our pis
	.syntax	unified			@ Modern ARM syntax

	.equ	FP_OFFSET, 4
	.equ	LOCAL_SPACE, 1040
	.equ	BUFFER_OFFSET, -1028
	.equ	LEN_OFFSET, -1032
	.equ	I_OFFSET, -1036
	.equ	EIGHT_NUM, -1040
	.equ	REMAIN_BYTE, -1044

	.equ	PARAM_SPACE, 16
	.equ	INFILE_OFFSET, -1048
	.equ	MASK_OFFSET, -1052
	.equ	VAL_OFFSET, -1056

	.equ	BUF_SIZE, 1024
	.equ	EIGHT_BYTE, 8
	.equ	LEFT_MOVE, 63

	.global	cipher			@ Specify the global symbol

	.text				@ Switch to text segment
	.align 2			@ Align on evenly divisibly by 4 byte
					@  address .align n where 2^n 
					@  determines alignment

/*
 * Function Name: cipher()
 * Function Prototype: void cipher( FILE * inFile, unsigned char mask[], int
 * 				    rotateValue );
 * Description: Reads input from the file inFile, applies the cipher specified
 *              by mask and rotateValue, and outputs the result to stdout.
 *
 * Parameter: inFile - stdin
 *            mask - the array of mask
 *	      rotateValue - the value of rotating
 * Side Effects: Print output to stdout.
 * Error Conditions: None.
 * Return Value: None.
 * Registers used:
 *	r0 - arg 1 - inFile
 *	r1 - arg 2 - mask
 *	r2 - arg 3 - rotateValue
 *
 * Stack Varibles:
 *	buffer - [fp - 1028] - buffer array
 *	length - [fp - 1032] - the return length
 *	i - [fp - 1036] - the index
 *	eightnum - [fp - 1040] - the number of 8 chunk
 *	remain - [fp - 1044] - the number of non-8 chunk
 *	inFile - [fp - 1048] - the arg 1
 *	mask - [fp - 1052] - arg 2
 *	rotateV - [fp - 1056] - arg 3
 */
cipher:
	@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers

	sub	sp, sp, LOCAL_SPACE	@ set local var space
	sub	sp, sp, PARAM_SPACE	@ set param space

	@ Incoming parameters in r0 - r2
	@ Store params
	str	r0, [fp, INFILE_OFFSET]
	str	r1, [fp, MASK_OFFSET]
	str	r2, [fp, VAL_OFFSET]

	@ Rear input from inFile using fread
	ldr	r1, =BUFFER_OFFSET	@ get address of buffer
	add	r0, fp, r1		@ load pointer
	mov	r1, 1			@ set sizeof(char)
	ldr	r2, =BUF_SIZE		@ set 1024 as 3rd param
	ldr	r3, [fp, INFILE_OFFSET]	@ set infile as 4th param
	bl	fread			@ call function
	str	r0, [fp, LEN_OFFSET]	@ Set length

	@ Check if empty file
	ldr	r0, [fp, LEN_OFFSET]	@ get fread return value
	cmp	r0, 0			@ r0 == 0
	beq	END_WHILE		@ opposite logic

	@ Get how many 8 bytes in buffer
	ldr	r0, [fp, LEN_OFFSET]	@ get buffer size
	mov	r1, EIGHT_BYTE
	sdiv	r2, r0, r1		@ length / 8
	str	r2, [fp, EIGHT_NUM]	@ store how many 8 byte chunk

	@ Get how many non-8 byte left
	ldr	r0, [fp, LEN_OFFSET]	@ get length
	mov	r1, EIGHT_BYTE		@ get 8
	sdiv	r2, r0, r1		@ length / 8
	mul	r3, r2, r1		
	sub	r2, r0, r3		@ get non-8 byte left
	str	r2, [fp, REMAIN_BYTE]	@ store
	
	@ldr	r3, [fp, LEN_OFFSET]	@ get length
	@cmp	r3, 0			@ r3 == 0
	@beq	END_WHILE		@ opposite logic
WHILE:
	@ Check case in example 2
	ldr	r3, [fp, EIGHT_NUM]	@ get number of 8
	cmp	r3, 0			@ r3 != 0
	bne	CASE1
	
	ldr	r2, [fp, REMAIN_BYTE]	@ get remain byte
	cmp	r2, 0			@ r2 == 0
	beq	END_WHILE		@ opposite logic

	/* CASE TWO */
	ldr	r0, [fp, BUFFER_OFFSET]	@ set 1st param
	ldr	r1, [fp, MASK_OFFSET]	@ set 2nd
	ldr	r2, [fp, BUFFER_OFFSET]	@ set 3rd
	ldr	r3, [fp, REMAIN_BYTE]	@ set 4th
	bl	xorBytes		@ call function
	b	END_CASE2
CASE1:
	/* For loop to loop 8 bytes chunk */
	mov	r3, 0
	str	r3, [fp, I_OFFSET]	@ i = 0
	ldr	r3, [fp, I_OFFSET]	@ get current value of i

	ldr	r2, [fp, EIGHT_NUM]	@ get number of eight byte chunk
	cmp	r3, r2			@ i >= num
	bge	END_FOR			@ opposite logic
	
FOR:
	/* FOR LOOP BODY */
	ldr	r3, [fp, I_OFFSET]	@ get current i
	mov	r2, EIGHT_BYTE		@ get 8
	mul	r2, r3, r2		@ get update index
	@ldr	r0, [fp, BUFFER_OFFSET + r2]
	ldr	r1, =BUFFER_OFFSET
	add	r1, r1, r2
	add	r0, fp, r1		@ make pointer to correct idx 
	ldr	r1, [fp, MASK_OFFSET]
	@ldr	r2, [fp, BUFFER_OFFSET + r2]
	ldr	r3, =BUFFER_OFFSET
	add	r2, r3, r2
	add	r2, fp, r2
	mov	r3, EIGHT_BYTE
	bl	xorBytes		@ call function
	
	/* rotat for next time */
	ldr	r0, [fp, MASK_OFFSET]
	mov	r1, EIGHT_BYTE
	bl	rotate			@ call function

	ldr	r3, [fp, I_OFFSET]	@ get current i
	add	r3, r3, 1		@ i++
	str	r3, [fp, I_OFFSET]	@ i = i + 1

	ldr	r3, [fp, I_OFFSET]	@ get current value of i
	ldr	r2, [fp, EIGHT_NUM]	@ get number of 8 byte chunk
	cmp	r3, r2			@ i < num
	blt	FOR			@ positive logic here

	/* Check remain */
	ldr	r3, [fp, REMAIN_BYTE]	@ get remain byte
	cmp	r3, 0			@ remain == 0
	beq	END_CASE1

	/* Check remain part */
	ldr	r3, [fp, EIGHT_NUM]	@ get num of 8 byte
	mov	r2, EIGHT_BYTE	
	mul	r2, r2, r3		@ update all 8 chunk idex
	@ldr	r0, [fp, BUFFER_OFFSET + r2]
	ldr	r1, =BUFFER_OFFSET
	add	r1, r1, r2
	add	r0, fp, r1
	ldr	r1, [fp, MASK_OFFSET]
	@ldr	r2, [fp, BUFFER_OFFSET + r2]
	ldr	r3, =BUFFER_OFFSET
	add	r3, r3, r2
	add	r2, fp, r3
	ldr	r3, [fp, REMAIN_BYTE]
	bl	xorBytes		@ call function
	b 	END_CASE1
END_FOR:
END_CASE1:
END_CASE2:
	/* Check while loop */
	ldr     r1, =BUFFER_OFFSET	@ same as above
	add     r0, fp, r1
	mov     r1, 1
	ldr     r2, =BUF_SIZE
	ldr     r3, [fp, INFILE_OFFSET]
	bl      fread			@ call function
	@str	r0, [fp, LEN_OFFSET]	@ store new length
	@ldr	r0, [fp, LEN_OFFSET]	@ get length
	cmp	r0, 0			@ length != 0
	bne	WHILE			@ positive logic
END_WHILE:

	/* Write out using fwrite */
	ldr	r1, =BUFFER_OFFSET
	add	r0, fp, r1
	mov	r1, 1
	ldr	r2, [fp, LEN_OFFSET]
	ldr	r3, =stdout
	ldr	r3, [r3]
	bl	fwrite			@ call function

	@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore lr into for 
					@   return
