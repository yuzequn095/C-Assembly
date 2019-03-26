/* 
 * Filename: rotate.s
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 5th, 2019
 * Source of Help: DI slides.
 */

@ Raspberry Pi directives
	.cpu	cortex-a53		@ Version of our Pis
	.syntax	unified			@ Modren ARM syntax

	.equ	FP_OFFSET, 4		@ Offset from sp to set fp

	.equ	LOCAL_SPACE, 32
	.equ	TOP_HALF, -8
	.equ	BOT_HALF, -12
	.equ	TOP_LSB, -16
	.equ	BOT_LSB, -20
	.equ	TOP_MSB, -24
	.equ	BOT_MSB, -28
	.equ	I_OFFSET, -32

	.equ	PARAM_SPACE, 8
	.equ	MASK_OFFSET, -40
	.equ	ROT_OFFSET, -44
	
	.equ	MOV_THREE, 24
	.equ	MOV_TWO, 16
	.equ	MOV_ONE, 8
	.equ	BIT_OFFSET, 32
	.equ	ZERO_FIL, 0xFF000000
	.equ	ONE_FIL, 0xFF0000
	.equ	TWO_FIL, 0xFF00
	.equ	THREE_FIL, 0xFF
	.equ	ROT_AROUND, 64	

	.global	rotate			@ Specify rotate as a global symbol

	.text				@ Switch to Text segment
	.align 2			@ Align on evenly divisibly by 4 byte
					@ address, .align 2^n alignment

/*
 * Function Name: rotate()
 * Function Prototype: void rotate( unsigned char mask[], int rotateValue );
 * Description: This function will rotate the bits in the 64-bit crypto mask. 
 * Parameters: mask - the mask array
 *	       rotateValue - the value to rotate
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: None.
 *
 * Register used:
 *	r0 - arg 1 -- mask
 *	r1 - arg 2 -- rotateValue
 *
 * Stack Variables:
 *	mask - [fp - 8] -- mask array
 *	rotateValue - [fp - 12] -- the value of rotate
 */
rotate:
	@ Standard prologue
	push	{fp, lr}		@ Save registers:fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers

	sub	sp, sp, LOCAL_SPACE	@ Set local var space 
	sub	sp, sp, PARAM_SPACE	@ Set param space

	@ Incoming parameters in r0, r1
	str	r0, [fp, MASK_OFFSET]	@ store mask
	str	r1, [fp, ROT_OFFSET]	@ store rotateValue


	/* Get mask[0] - mask[3] */
	mov	r3, 0
	str	r3, [fp, I_OFFSET]	@ i = 0
	ldr	r0, [fp, I_OFFSET]	@ get current value of i 
	ldr	r3, [fp, MASK_OFFSET]	@ get array ptr
	ldrb	r3, [r3, r0]		@ get mask[0]
	lsl	r3, r3, MOV_THREE	@ move left 3 byte (XOOO) in r3

	ldr	r0, [fp, I_OFFSET]	@ get current i 
	add	r0, r0, 1		@ i++
	str	r0, [fp, I_OFFSET]	@ i = i + 1
	ldr	r0, [fp, I_OFFSET]	@ get i
	ldr	r2, [fp, MASK_OFFSET]	@ get array ptr
	ldrb	r2, [r2, r0]		@ get mask[1]
	lsl	r2, r2, MOV_TWO		@ mov left 2 byte (OXOO) in r2

	orr	r3, r3, r2		@ merge, (XXOO) in r3

	ldr	r0, [fp, I_OFFSET]	@ get current i 
	add	r0, r0, 1		@ i++
	str	r0, [fp, I_OFFSET]	@ i = i + 1
	ldr	r0, [fp, I_OFFSET]	@ get i 
	ldr	r2, [fp, MASK_OFFSET]	@ get array ptr
	ldrb	r2, [r2, r0]		@ get mask[2]
	lsl	r2, r2, MOV_ONE		@ move left 1 byte (00X0) in r2

	orr	r3, r3, r2		@ merge, (XXX0) in r3

	ldr	r0, [fp, I_OFFSET]	@ get current i 
	add	r0, r0, 1		@ i++
	str	r0, [fp, I_OFFSET]	@ i = i + 1
	ldr	r0, [fp, I_OFFSET]	@ get i
	ldr	r2, [fp, MASK_OFFSET]	@ get array ptr
	ldrb	r2, [r2, r0]		@ get mask[3], (000X) in r2

	orr	r3, r3, r2		@ merge, (XXXX) in r3

	str	r3, [fp, TOP_HALF]	@ save mask[0 - 3] in topHalf

	/* Get mask[4] - mask[7] */
	ldr	r0, [fp, I_OFFSET]	@ get cuurrent i 
	add	r0, r0, 1		@ i++
	str	r0, [fp, I_OFFSET]	@ i = i + 1
	ldr	r0, [fp, I_OFFSET]	@ get current i 
	ldr	r3, [fp, MASK_OFFSET]	@ get array ptr
	ldrb	r3, [r3, r0]		@ get mask[4]
	lsl	r3, r3, MOV_THREE	@ move left 3 byte (X000) in r3

	ldr     r0, [fp, I_OFFSET]      @ get current i
	add     r0, r0, 1               @ i++
	str     r0, [fp, I_OFFSET]      @ i = i + 1
	ldr     r0, [fp, I_OFFSET]      @ get i
	ldr     r2, [fp, MASK_OFFSET]   @ get array ptr
	ldrb    r2, [r2, r0]            @ get mask[5]
	lsl     r2, r2, MOV_TWO         @ mov left 2 byte (OXOO) in r2

	orr     r3, r3, r2              @ merge, (XXOO) in r3

	ldr     r0, [fp, I_OFFSET]      @ get current i
	add     r0, r0, 1               @ i++
	str     r0, [fp, I_OFFSET]      @ i = i + 1
	ldr     r0, [fp, I_OFFSET]      @ get i
	ldr     r2, [fp, MASK_OFFSET]   @ get array ptr
	ldrb    r2, [r2, r0]            @ get mask[6]
	lsl     r2, r2, MOV_ONE         @ move left 1 byte (00X0) in r2

	orr     r3, r3, r2              @ merge, (XXX0) in r3

	ldr     r0, [fp, I_OFFSET]      @ get current i
	add     r0, r0, 1               @ i++
	str     r0, [fp, I_OFFSET]      @ i = i + 1
	ldr     r0, [fp, I_OFFSET]      @ get i
	ldr     r2, [fp, MASK_OFFSET]   @ get array ptr
	ldrb    r2, [r2, r0]            @ get mask[7], (000X) in r2

	orr     r3, r3, r2              @ merge, (XXXX) in r3

	str     r3, [fp, BOT_HALF]      @ save mask[4 - 7] in botHalf

	/* Check right or left */
	ldr     r0, [fp, ROT_OFFSET]    @ Get rotateValue
	/* check if > 64 */
	mov	r1, ROT_AROUND		@ set 64
	cmp	r0, r1			@ value < 64
	blt	END_CHECK		@ opposite logic
	sdiv	r2, r0, r1
	mul	r3, r2, r1
	sub	r2, r0, r3
	str	r2, [fp, ROT_OFFSET]	@ save new rotvalue
END_CHECK:
	ldr	r0, [fp, ROT_OFFSET]
	bl      isOdd                   @ call function
	cmp     r0, 1                   @ rotateValue != 1
	bne     EVEN_CASE               @ opposite logic test to branch over if
	
	/* If Statements - odd turn left */
	ldr	r0, [fp, ROT_OFFSET]	@ get rotate value
	mov	r1, BIT_OFFSET		@ get the number of reg bit: 32
	sub	r0, r1, r0		@ 32 - rotateValue

	ldr	r1, [fp, TOP_HALF]	@ get top half : mask[0 - 3]
	lsr	r1, r1, r0		@ move rotatevalue bits to lsb
	str	r1, [fp, TOP_LSB]	@ save rotate part from top

	ldr	r0, [fp, ROT_OFFSET]	@ get rotate value
	mov	r1, BIT_OFFSET		@ get the number of reg bit: 32
	sub	r0, r1, r0		@ 32 - rotateValue

	ldr	r1, [fp, BOT_HALF]	@ get bot half: mask[4 - 7]
	lsr	r1, r1, r0		@ move rotatevalue bits to lsb
	str	r1, [fp, BOT_LSB]	@ save rotate part from bot

	ldr	r0, [fp, TOP_HALF]	@ get tophalf
	ldr	r1, [fp, ROT_OFFSET]	@ get rotate value
	lsl	r0, r0, r1		@ rotate to left as rotatevalue
	ldr	r1, [fp, BOT_LSB]	@ get lsb part in bot
	orr	r0, r0, r1		@ get new top half
	str	r0, [fp, TOP_HALF]	@ store new TOP_HALF

	ldr     r0, [fp, BOT_HALF]      @ get bothalf
	ldr     r1, [fp, ROT_OFFSET]    @ get rotate value
	lsl     r0, r0, r1              @ rotate to left as rotatevalue
	ldr     r1, [fp, TOP_LSB]       @ get lsb part in top
	orr     r0, r0, r1              @ get new bot half
	str     r0, [fp, BOT_HALF]      @ store new BOT_HALF
	
	b	END_IF			@ breanch always over else block

EVEN_CASE:
	/* Else Statements - even turn right */
	@ldr     r0, [fp, ROT_OFFSET]    @ get rotate value
	@mov	r1, ROT_AROUND
	@sdiv	r2, r0, r1		@ get quotient
	@mul	r3, r2, r1		@ get result
	@sub	r2, r0, r3		@ get remainder
	@cmp	r2, 0			@ r2 == 0
	@beq	AROUND_END		@ opposite logic

	/* Check rotate around */
	ldr	r0, [fp, ROT_OFFSET]
	mov     r1, BIT_OFFSET          @ get the number of reg bit: 32
	sub     r0, r1, r0              @ 32 - rotateValue

	ldr     r1, [fp, TOP_HALF]      @ get top half : mask[0 - 3]
	lsl     r1, r1, r0              @ move rotatevalue bits to lsb
	lsr	r1, r1, r0		@ back to msb
	str     r1, [fp, TOP_MSB]       @ save rotate part from top

	ldr     r0, [fp, ROT_OFFSET]    @ get rotate value
	mov     r1, BIT_OFFSET          @ get the number of reg bit: 32
	sub     r0, r1, r0              @ 32 - rotateValue

	ldr     r1, [fp, BOT_HALF]      @ get bot half: mask[4 - 7]
	lsl     r1, r1, r0              @ move rotatevalue bits to lsb
	lsr     r1, r1, r0              @ back to msb
	str     r1, [fp, BOT_MSB]       @ save rotate part from bot

	ldr     r0, [fp, TOP_HALF]      @ get tophalf
	ldr     r1, [fp, ROT_OFFSET]    @ get rotate value
	lsr     r0, r0, r1              @ rotate to right as rotatevalue
	ldr     r1, [fp, BOT_MSB]       @ get msb part in bot
	ldr	r2, [fp, ROT_OFFSET]	@ get rotate value
	mov	r3, BIT_OFFSET		@ get the number 32
	sub	r3, r3, r2		@ 32 - rv
	lsl	r1, r1, r3		@ rotate msb to left
	orr     r0, r0, r1              @ get new top half
	str     r0, [fp, TOP_HALF]      @ store new TOP_HALF

	ldr     r0, [fp, BOT_HALF]      @ get bothalf
	ldr     r1, [fp, ROT_OFFSET]    @ get rotate value
	lsr     r0, r0, r1              @ rotate to right as rotatevalue
	ldr     r1, [fp, TOP_MSB]       @ get msb part in top
	ldr     r2, [fp, ROT_OFFSET]    @ get rotate value
	mov     r3, BIT_OFFSET          @ get the number 32
	sub     r3, r3, r2              @ 32 - rv
	lsl     r1, r1, r3              @ rotate msb to left
	orr     r0, r0, r1              @ get new bot half
	str     r0, [fp, BOT_HALF]      @ store new BOT_HALF

END_IF:
    
    	/* store mask[0 - 3] */
	ldr	r1, [fp,  TOP_HALF]	@ get topHalf
	mov	r2, ZERO_FIL		@ 0xFF000000
	and	r1, r1, r2		
	lsr	r1, r1, MOV_THREE	@ get mask[0]
	mov     r3, 0
	str     r3, [fp, I_OFFSET]      @ i = 0
	ldr     r0, [fp, I_OFFSET]      @ get current value of i
	ldr     r3, [fp, MASK_OFFSET]  @ get array ptr
	strb	r1, [r3, r0]		@ mask[0] = newvalue

	ldr     r1, [fp,  TOP_HALF]     @ get topHalf
	mov     r2, ONE_FIL		@ 0xFF0000
	and     r1, r1, r2
	lsr     r1, r1, MOV_TWO		@ get mask[1]
	ldr	r3, [fp, I_OFFSET]	@ get i
	add	r3, r3, 1		@ i++
	str	r3, [fp, I_OFFSET]	@ i = i + 1
	ldr	r0, [fp, I_OFFSET]	@ get i (1)
	ldr     r3, [fp, MASK_OFFSET]  @ get array ptr
	strb    r1, [r3, r0]            @ mask[1] = newvalue

	ldr     r1, [fp,  TOP_HALF]     @ get topHalf
	mov     r2, TWO_FIL             @ 0xFF00
	and     r1, r1, r2
	lsr     r1, r1, MOV_ONE         @ get mask[2]
	ldr     r3, [fp, I_OFFSET]      @ get i
	add     r3, r3, 1               @ i++
	str     r3, [fp, I_OFFSET]      @ i = i + 1
	ldr     r0, [fp, I_OFFSET]      @ get i (2)
	ldr     r3, [fp, MASK_OFFSET]  @ get array ptr
	strb    r1, [r3, r0]            @ mask[2] = newvalue

	ldr     r1, [fp,  TOP_HALF]     @ get topHalf
	mov     r2, THREE_FIL           @ 0xFF
	and     r1, r1, r2
	ldr     r3, [fp, I_OFFSET]      @ get i
	add     r3, r3, 1
	str     r3, [fp, I_OFFSET]      @ i = i + 1
	ldr     r0, [fp, I_OFFSET]      @ get i (3)
	ldr     r3, [fp, MASK_OFFSET]  @ get array ptr
	strb    r1, [r3, r0]            @ mas[3] = newvalue

	/* store mask[4 - 7] */
	ldr     r1, [fp,  BOT_HALF]     @ get botHalf
	mov     r2, ZERO_FIL            @ 0xFF000000
	and     r1, r1, r2
	lsr     r1, r1, MOV_THREE       @ get mask[4]
	ldr     r3, [fp, I_OFFSET]      @ get current value of i
	add     r3, r3, 1
	str     r3, [fp, I_OFFSET]      @ i = i + 1
	ldr     r0, [fp, I_OFFSET]      @ get i (4)
	ldr     r3, [fp, MASK_OFFSET]  @ get array ptr
	strb    r1, [r3, r0]            @ mas[4] = newvalue

	ldr     r1, [fp,  BOT_HALF]     @ get botHalf
	mov     r2, ONE_FIL             @ 0xFF0000
	and     r1, r1, r2
	lsr     r1, r1, MOV_TWO         @ get mask[5]
	ldr     r3, [fp, I_OFFSET]      @ get i
	add     r3, r3, 1               @ i++
	str     r3, [fp, I_OFFSET]      @ i = i + 1
	ldr     r0, [fp, I_OFFSET]      @ get i (5)
	ldr     r3, [fp, MASK_OFFSET]  @ get array ptr
	strb    r1, [r3, r0]            @ mask[5] = newvalue

	ldr     r1, [fp,  BOT_HALF]     @ get botHalf
	mov     r2, TWO_FIL             @ 0xFF00
	and     r1, r1, r2
	lsr     r1, r1, MOV_ONE         @ get mask[6]
	ldr     r3, [fp, I_OFFSET]      @ get i
	add     r3, r3, 1               @ i++
	str     r3, [fp, I_OFFSET]      @ i = i + 1
	ldr     r0, [fp, I_OFFSET]      @ get i (6)
	ldr     r3, [fp, MASK_OFFSET]  @ get array ptr
	strb    r1, [r3, r0]            @ mask[6] = newvalue

	ldr     r1, [fp,  BOT_HALF]     @ get botHalf
	mov     r2, THREE_FIL           @ 0xFF
	and     r1, r1, r2
	ldr     r3, [fp, I_OFFSET]      @ get i
	add     r3, r3, 1
	str     r3, [fp, I_OFFSET]      @ i = i + 1
	ldr     r0, [fp, I_OFFSET]      @ get i (7)
	ldr     r3, [fp, MASK_OFFSET]  @ get array ptr
	strb    r1, [r3, r0]            @ mask[7] = newvalue

@AROUND_END:
	@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registesr
	pop	{fp, pc}		@   return
