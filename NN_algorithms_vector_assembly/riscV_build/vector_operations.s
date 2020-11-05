	.file	"vector_operations.c"
	.option nopic
	.attribute arch, "rv32i2p0_m2p0_c2p0_v2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.align	1
	.globl	vect_add
	.type	vect_add, @function
vect_add:
.LFB0:
	.file 1 "../src/NN_operations/vector_operations.c"
	.loc 1 3 86
	.cfi_startproc
.LVL0:
	.loc 1 4 2
.LBB2:
	.loc 1 4 6
	.loc 1 4 19 is_stmt 0
	li	a5,0
.LVL1:
.L2:
	.loc 1 4 25 is_stmt 1 discriminator 1
	.loc 1 4 2 is_stmt 0 discriminator 1
	bne	a5,a0,.L3
.LBE2:
	.loc 1 7 1
	ret
.L3:
.LBB3:
	.loc 1 5 3 is_stmt 1 discriminator 3
	.loc 1 5 18 is_stmt 0 discriminator 3
	add	a4,a1,a5
	.loc 1 5 28 discriminator 3
	add	a7,a2,a5
	.loc 1 5 22 discriminator 3
	lbu	a4,0(a4)
	lbu	a7,0(a7)
	.loc 1 5 12 discriminator 3
	add	a6,a3,a5
	.loc 1 4 31 discriminator 3
	addi	a5,a5,1
.LVL2:
	.loc 1 5 22 discriminator 3
	add	a4,a4,a7
	.loc 1 5 12 discriminator 3
	sb	a4,0(a6)
	.loc 1 4 30 is_stmt 1 discriminator 3
.LVL3:
	j	.L2
.LBE3:
	.cfi_endproc
.LFE0:
	.size	vect_add, .-vect_add
	.align	1
	.globl	vect_mult
	.type	vect_mult, @function
vect_mult:
.LFB1:
	.loc 1 9 86
	.cfi_startproc
.LVL4:
	.loc 1 10 2
.LBB4:
	.loc 1 10 6
	.loc 1 10 19 is_stmt 0
	li	a5,0
.LVL5:
.L5:
	.loc 1 10 25 is_stmt 1 discriminator 1
	.loc 1 10 2 is_stmt 0 discriminator 1
	bne	a5,a0,.L6
.LBE4:
	.loc 1 13 1
	ret
.L6:
.LBB5:
	.loc 1 11 3 is_stmt 1 discriminator 3
	.loc 1 11 18 is_stmt 0 discriminator 3
	add	a4,a1,a5
	.loc 1 11 28 discriminator 3
	add	a7,a2,a5
	.loc 1 11 22 discriminator 3
	lbu	a4,0(a4)
	lbu	a7,0(a7)
	.loc 1 11 12 discriminator 3
	add	a6,a3,a5
	.loc 1 10 31 discriminator 3
	addi	a5,a5,1
.LVL6:
	.loc 1 11 22 discriminator 3
	mul	a4,a4,a7
	.loc 1 11 12 discriminator 3
	sb	a4,0(a6)
	.loc 1 10 30 is_stmt 1 discriminator 3
.LVL7:
	j	.L5
.LBE5:
	.cfi_endproc
.LFE1:
	.size	vect_mult, .-vect_mult
	.align	1
	.globl	vect_addRecursive
	.type	vect_addRecursive, @function
vect_addRecursive:
.LFB2:
	.loc 1 15 78
	.cfi_startproc
.LVL8:
	.loc 1 16 2
	.loc 1 17 2
.LBB6:
	.loc 1 17 6
	.loc 1 17 19 is_stmt 0
	li	a4,0
.LBE6:
	.loc 1 16 9
	li	a5,0
.LVL9:
.L8:
.LBB7:
	.loc 1 17 25 is_stmt 1 discriminator 1
	.loc 1 17 2 is_stmt 0 discriminator 1
	bne	a4,a0,.L9
.LBE7:
	.loc 1 20 2 is_stmt 1
	.loc 1 20 12 is_stmt 0
	sb	a5,0(a2)
	.loc 1 21 1
	ret
.L9:
.LBB8:
	.loc 1 18 3 is_stmt 1 discriminator 3
	.loc 1 18 21 is_stmt 0 discriminator 3
	add	a3,a1,a4
	.loc 1 18 15 discriminator 3
	lbu	a3,0(a3)
	.loc 1 17 31 discriminator 3
	addi	a4,a4,1
.LVL10:
	.loc 1 18 15 discriminator 3
	add	a5,a5,a3
.LVL11:
	.loc 1 18 8 discriminator 3
	slli	a5,a5,24
	srai	a5,a5,24
.LVL12:
	.loc 1 17 30 is_stmt 1 discriminator 3
	j	.L8
.LBE8:
	.cfi_endproc
.LFE2:
	.size	vect_addRecursive, .-vect_addRecursive
	.align	1
	.globl	vect_maxRecursive
	.type	vect_maxRecursive, @function
vect_maxRecursive:
.LFB3:
	.loc 1 23 78
	.cfi_startproc
.LVL13:
	.loc 1 24 2
	.loc 1 25 2
.LBB9:
	.loc 1 25 6
	.loc 1 25 19 is_stmt 0
	li	a4,0
.LBE9:
	.loc 1 24 9
	li	a5,-128
.LVL14:
.L11:
.LBB10:
	.loc 1 25 25 is_stmt 1 discriminator 1
	.loc 1 25 2 is_stmt 0 discriminator 1
	bne	a4,a0,.L13
.LBE10:
	.loc 1 28 2 is_stmt 1
	.loc 1 28 13 is_stmt 0
	sb	a5,0(a2)
	.loc 1 29 1
	ret
.L13:
.LBB11:
	.loc 1 26 3 is_stmt 1
	.loc 1 26 17 is_stmt 0
	add	a3,a1,a4
	lbu	a3,0(a3)
	slli	a6,a3,24
	srai	a6,a6,24
	bge	a6,a5,.L12
	mv	a3,a5
.L12:
	slli	a5,a3,24
.LVL15:
	srai	a5,a5,24
	.loc 1 25 30 is_stmt 1
	.loc 1 25 31 is_stmt 0
	addi	a4,a4,1
.LVL16:
	j	.L11
.LBE11:
	.cfi_endproc
.LFE3:
	.size	vect_maxRecursive, .-vect_maxRecursive
	.align	1
	.globl	vect_dotProduct
	.type	vect_dotProduct, @function
vect_dotProduct:
.LFB4:
	.loc 1 31 96 is_stmt 1
	.cfi_startproc
.LVL17:
	.loc 1 32 2
	.loc 1 33 2
.LBB12:
	.loc 1 33 6
	.loc 1 33 19 is_stmt 0
	li	a4,0
.LBE12:
	.loc 1 32 9
	li	a5,0
.LVL18:
.L15:
.LBB13:
	.loc 1 33 25 is_stmt 1 discriminator 1
	.loc 1 33 2 is_stmt 0 discriminator 1
	bne	a4,a0,.L16
.LBE13:
	.loc 1 36 2 is_stmt 1
	.loc 1 36 12 is_stmt 0
	sb	a5,0(a3)
	.loc 1 37 1
	ret
.L16:
.LBB14:
	.loc 1 34 3 is_stmt 1 discriminator 3
	.loc 1 34 20 is_stmt 0 discriminator 3
	add	a6,a1,a4
	.loc 1 34 30 discriminator 3
	add	a7,a2,a4
	.loc 1 34 24 discriminator 3
	lbu	a6,0(a6)
	lbu	a7,0(a7)
	.loc 1 33 31 discriminator 3
	addi	a4,a4,1
.LVL19:
	.loc 1 34 24 discriminator 3
	mul	a6,a6,a7
	.loc 1 34 14 discriminator 3
	add	a5,a6,a5
.LVL20:
	.loc 1 34 8 discriminator 3
	slli	a5,a5,24
	srai	a5,a5,24
.LVL21:
	.loc 1 33 30 is_stmt 1 discriminator 3
	j	.L15
.LBE14:
	.cfi_endproc
.LFE4:
	.size	vect_dotProduct, .-vect_dotProduct
	.align	1
	.globl	vect_ReLu
	.type	vect_ReLu, @function
vect_ReLu:
.LFB5:
	.loc 1 39 67
	.cfi_startproc
.LVL22:
	.loc 1 40 2
.LBB15:
	.loc 1 40 6
	.loc 1 40 19 is_stmt 0
	li	a5,0
.LVL23:
.L18:
	.loc 1 40 25 is_stmt 1 discriminator 1
	.loc 1 40 2 is_stmt 0 discriminator 1
	bne	a5,a0,.L21
.LBE15:
	.loc 1 47 1
	ret
.L21:
.LBB16:
	.loc 1 41 3 is_stmt 1
	.loc 1 41 10 is_stmt 0
	add	a4,a1,a5
	lb	a3,0(a4)
	add	a4,a2,a5
	.loc 1 41 5
	bge	a3,zero,.L19
	.loc 1 42 4 is_stmt 1
	.loc 1 42 13 is_stmt 0
	sb	zero,0(a4)
.L20:
	.loc 1 40 30 is_stmt 1 discriminator 2
	.loc 1 40 31 is_stmt 0 discriminator 2
	addi	a5,a5,1
.LVL24:
	j	.L18
.L19:
	.loc 1 44 4 is_stmt 1
	.loc 1 44 13 is_stmt 0
	sb	a3,0(a4)
	j	.L20
.LBE16:
	.cfi_endproc
.LFE5:
	.size	vect_ReLu, .-vect_ReLu
	.align	1
	.globl	vect_ReLu6
	.type	vect_ReLu6, @function
vect_ReLu6:
.LFB6:
	.loc 1 49 68 is_stmt 1
	.cfi_startproc
.LVL25:
	.loc 1 50 2
.LBB17:
	.loc 1 50 6
	.loc 1 50 19 is_stmt 0
	li	a5,0
	.loc 1 53 11
	li	a3,6
.LVL26:
.L23:
	.loc 1 50 25 is_stmt 1 discriminator 1
	.loc 1 50 2 is_stmt 0 discriminator 1
	bne	a5,a0,.L27
.LBE17:
	.loc 1 59 1
	ret
.L27:
.LBB18:
	.loc 1 51 3 is_stmt 1
	.loc 1 51 10 is_stmt 0
	add	a4,a1,a5
	lb	a4,0(a4)
	.loc 1 51 5
	bge	a4,zero,.L24
	.loc 1 52 4 is_stmt 1
	.loc 1 52 13 is_stmt 0
	sb	zero,0(a2)
.L25:
	.loc 1 50 30 is_stmt 1 discriminator 2
	.loc 1 50 31 is_stmt 0 discriminator 2
	addi	a5,a5,1
.LVL27:
	addi	a2,a2,1
	j	.L23
.L24:
	.loc 1 53 9 is_stmt 1
	.loc 1 53 11 is_stmt 0
	ble	a4,a3,.L26
	.loc 1 54 4 is_stmt 1
	.loc 1 54 13 is_stmt 0
	sb	a3,0(a2)
	j	.L25
.L26:
	.loc 1 56 4 is_stmt 1
	.loc 1 56 13 is_stmt 0
	sb	a4,0(a2)
	j	.L25
.LBE18:
	.cfi_endproc
.LFE6:
	.size	vect_ReLu6, .-vect_ReLu6
.Letext0:
	.file 2 "/opt/riscv/riscv32-unknown-elf/include/machine/_default_types.h"
	.file 3 "/opt/riscv/riscv32-unknown-elf/include/sys/_stdint.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x33c
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.byte	0x1
	.4byte	.LASF24
	.byte	0xc
	.4byte	.LASF25
	.4byte	.LASF26
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	.Ldebug_line0
	.byte	0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF0
	.byte	0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.byte	0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF1
	.byte	0x2
	.byte	0x10
	.byte	0x4
	.4byte	.LASF2
	.byte	0x4
	.4byte	.LASF11
	.byte	0x2
	.byte	0x29
	.byte	0x17
	.4byte	0x4d
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF3
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF4
	.byte	0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF5
	.byte	0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF6
	.byte	0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF7
	.byte	0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF8
	.byte	0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF9
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF10
	.byte	0x4
	.4byte	.LASF12
	.byte	0x3
	.byte	0x14
	.byte	0x12
	.4byte	0x41
	.byte	0x5
	.4byte	0x85
	.byte	0x6
	.4byte	.LASF15
	.byte	0x1
	.byte	0x31
	.byte	0x6
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.byte	0x1
	.byte	0x9c
	.4byte	0xeb
	.byte	0x7
	.string	"N"
	.byte	0x1
	.byte	0x31
	.byte	0x1e
	.4byte	0x25
	.byte	0x1
	.byte	0x5a
	.byte	0x8
	.4byte	.LASF13
	.byte	0x1
	.byte	0x31
	.byte	0x2f
	.4byte	0xeb
	.byte	0x1
	.byte	0x5b
	.byte	0x9
	.4byte	.LASF14
	.byte	0x1
	.byte	0x31
	.byte	0x3d
	.4byte	0xf1
	.4byte	.LLST9
	.byte	0xa
	.4byte	.Ldebug_ranges0+0xa8
	.byte	0xb
	.string	"n"
	.byte	0x1
	.byte	0x32
	.byte	0x13
	.4byte	0x25
	.4byte	.LLST10
	.byte	0
	.byte	0
	.byte	0xc
	.byte	0x4
	.4byte	0x91
	.byte	0xc
	.byte	0x4
	.4byte	0x85
	.byte	0x6
	.4byte	.LASF16
	.byte	0x1
	.byte	0x27
	.byte	0x6
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.byte	0x1
	.byte	0x9c
	.4byte	0x14a
	.byte	0x7
	.string	"N"
	.byte	0x1
	.byte	0x27
	.byte	0x1d
	.4byte	0x25
	.byte	0x1
	.byte	0x5a
	.byte	0x8
	.4byte	.LASF13
	.byte	0x1
	.byte	0x27
	.byte	0x2e
	.4byte	0xeb
	.byte	0x1
	.byte	0x5b
	.byte	0x8
	.4byte	.LASF14
	.byte	0x1
	.byte	0x27
	.byte	0x3c
	.4byte	0xf1
	.byte	0x1
	.byte	0x5c
	.byte	0xa
	.4byte	.Ldebug_ranges0+0x90
	.byte	0xb
	.string	"n"
	.byte	0x1
	.byte	0x28
	.byte	0x13
	.4byte	0x25
	.4byte	.LLST8
	.byte	0
	.byte	0
	.byte	0x6
	.4byte	.LASF17
	.byte	0x1
	.byte	0x1f
	.byte	0x6
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.byte	0x1
	.byte	0x9c
	.4byte	0x1bb
	.byte	0x7
	.string	"N"
	.byte	0x1
	.byte	0x1f
	.byte	0x23
	.4byte	0x25
	.byte	0x1
	.byte	0x5a
	.byte	0x8
	.4byte	.LASF13
	.byte	0x1
	.byte	0x1f
	.byte	0x34
	.4byte	0xeb
	.byte	0x1
	.byte	0x5b
	.byte	0x8
	.4byte	.LASF18
	.byte	0x1
	.byte	0x1f
	.byte	0x48
	.4byte	0xeb
	.byte	0x1
	.byte	0x5c
	.byte	0x8
	.4byte	.LASF19
	.byte	0x1
	.byte	0x1f
	.byte	0x56
	.4byte	0xf1
	.byte	0x1
	.byte	0x5d
	.byte	0xd
	.4byte	.LASF20
	.byte	0x1
	.byte	0x20
	.byte	0x9
	.4byte	0x85
	.4byte	.LLST6
	.byte	0xa
	.4byte	.Ldebug_ranges0+0x70
	.byte	0xb
	.string	"n"
	.byte	0x1
	.byte	0x21
	.byte	0x13
	.4byte	0x25
	.4byte	.LLST7
	.byte	0
	.byte	0
	.byte	0x6
	.4byte	.LASF21
	.byte	0x1
	.byte	0x17
	.byte	0x6
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.byte	0x1
	.byte	0x9c
	.4byte	0x21e
	.byte	0x7
	.string	"N"
	.byte	0x1
	.byte	0x17
	.byte	0x25
	.4byte	0x25
	.byte	0x1
	.byte	0x5a
	.byte	0x8
	.4byte	.LASF13
	.byte	0x1
	.byte	0x17
	.byte	0x36
	.4byte	0xeb
	.byte	0x1
	.byte	0x5b
	.byte	0x8
	.4byte	.LASF19
	.byte	0x1
	.byte	0x17
	.byte	0x44
	.4byte	0xf1
	.byte	0x1
	.byte	0x5c
	.byte	0xb
	.string	"max"
	.byte	0x1
	.byte	0x18
	.byte	0x9
	.4byte	0x85
	.4byte	.LLST4
	.byte	0xa
	.4byte	.Ldebug_ranges0+0x50
	.byte	0xb
	.string	"n"
	.byte	0x1
	.byte	0x19
	.byte	0x13
	.4byte	0x25
	.4byte	.LLST5
	.byte	0
	.byte	0
	.byte	0x6
	.4byte	.LASF22
	.byte	0x1
	.byte	0xf
	.byte	0x6
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.byte	0x1
	.byte	0x9c
	.4byte	0x281
	.byte	0x7
	.string	"N"
	.byte	0x1
	.byte	0xf
	.byte	0x25
	.4byte	0x25
	.byte	0x1
	.byte	0x5a
	.byte	0x8
	.4byte	.LASF13
	.byte	0x1
	.byte	0xf
	.byte	0x36
	.4byte	0xeb
	.byte	0x1
	.byte	0x5b
	.byte	0x8
	.4byte	.LASF19
	.byte	0x1
	.byte	0xf
	.byte	0x44
	.4byte	0xf1
	.byte	0x1
	.byte	0x5c
	.byte	0xd
	.4byte	.LASF20
	.byte	0x1
	.byte	0x10
	.byte	0x9
	.4byte	0x85
	.4byte	.LLST2
	.byte	0xa
	.4byte	.Ldebug_ranges0+0x30
	.byte	0xb
	.string	"n"
	.byte	0x1
	.byte	0x11
	.byte	0x13
	.4byte	0x25
	.4byte	.LLST3
	.byte	0
	.byte	0
	.byte	0x6
	.4byte	.LASF23
	.byte	0x1
	.byte	0x9
	.byte	0x6
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.byte	0x1
	.byte	0x9c
	.4byte	0x2e2
	.byte	0x7
	.string	"N"
	.byte	0x1
	.byte	0x9
	.byte	0x1d
	.4byte	0x25
	.byte	0x1
	.byte	0x5a
	.byte	0x8
	.4byte	.LASF13
	.byte	0x1
	.byte	0x9
	.byte	0x2d
	.4byte	0xeb
	.byte	0x1
	.byte	0x5b
	.byte	0x8
	.4byte	.LASF18
	.byte	0x1
	.byte	0x9
	.byte	0x41
	.4byte	0xeb
	.byte	0x1
	.byte	0x5c
	.byte	0x8
	.4byte	.LASF14
	.byte	0x1
	.byte	0x9
	.byte	0x4f
	.4byte	0xf1
	.byte	0x1
	.byte	0x5d
	.byte	0xa
	.4byte	.Ldebug_ranges0+0x18
	.byte	0xb
	.string	"n"
	.byte	0x1
	.byte	0xa
	.byte	0x13
	.4byte	0x25
	.4byte	.LLST1
	.byte	0
	.byte	0
	.byte	0xe
	.4byte	.LASF27
	.byte	0x1
	.byte	0x3
	.byte	0x6
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.byte	0x1
	.byte	0x9c
	.byte	0x7
	.string	"N"
	.byte	0x1
	.byte	0x3
	.byte	0x1c
	.4byte	0x25
	.byte	0x1
	.byte	0x5a
	.byte	0x8
	.4byte	.LASF13
	.byte	0x1
	.byte	0x3
	.byte	0x2d
	.4byte	0xeb
	.byte	0x1
	.byte	0x5b
	.byte	0x8
	.4byte	.LASF18
	.byte	0x1
	.byte	0x3
	.byte	0x41
	.4byte	0xeb
	.byte	0x1
	.byte	0x5c
	.byte	0x8
	.4byte	.LASF14
	.byte	0x1
	.byte	0x3
	.byte	0x4f
	.4byte	0xf1
	.byte	0x1
	.byte	0x5d
	.byte	0xa
	.4byte	.Ldebug_ranges0+0
	.byte	0xb
	.string	"n"
	.byte	0x1
	.byte	0x4
	.byte	0x13
	.4byte	0x25
	.4byte	.LLST0
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.byte	0x1
	.byte	0x11
	.byte	0x1
	.byte	0x25
	.byte	0xe
	.byte	0x13
	.byte	0xb
	.byte	0x3
	.byte	0xe
	.byte	0x1b
	.byte	0xe
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x6
	.byte	0x10
	.byte	0x17
	.byte	0
	.byte	0
	.byte	0x2
	.byte	0x24
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x3e
	.byte	0xb
	.byte	0x3
	.byte	0xe
	.byte	0
	.byte	0
	.byte	0x3
	.byte	0x24
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x3e
	.byte	0xb
	.byte	0x3
	.byte	0x8
	.byte	0
	.byte	0
	.byte	0x4
	.byte	0x16
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x5
	.byte	0x26
	.byte	0
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x6
	.byte	0x2e
	.byte	0x1
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x27
	.byte	0x19
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x6
	.byte	0x40
	.byte	0x18
	.byte	0x97,0x42
	.byte	0x19
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x7
	.byte	0x5
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x18
	.byte	0
	.byte	0
	.byte	0x8
	.byte	0x5
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x18
	.byte	0
	.byte	0
	.byte	0x9
	.byte	0x5
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x17
	.byte	0
	.byte	0
	.byte	0xa
	.byte	0xb
	.byte	0x1
	.byte	0x55
	.byte	0x17
	.byte	0
	.byte	0
	.byte	0xb
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x17
	.byte	0
	.byte	0
	.byte	0xc
	.byte	0xf
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0xd
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x17
	.byte	0
	.byte	0
	.byte	0xe
	.byte	0x2e
	.byte	0x1
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x27
	.byte	0x19
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x6
	.byte	0x40
	.byte	0x18
	.byte	0x97,0x42
	.byte	0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST9:
	.4byte	.LVL25-.Ltext0
	.4byte	.LVL26-.Ltext0
	.2byte	0x1
	.byte	0x5c
	.4byte	.LVL26-.Ltext0
	.4byte	.LFE6-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.byte	0x1
	.byte	0x5c
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST10:
	.4byte	.LVL25-.Ltext0
	.4byte	.LVL26-.Ltext0
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL26-.Ltext0
	.4byte	.LFE6-.Ltext0
	.2byte	0x1
	.byte	0x5f
	.4byte	0
	.4byte	0
.LLST8:
	.4byte	.LVL22-.Ltext0
	.4byte	.LVL23-.Ltext0
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL23-.Ltext0
	.4byte	.LFE5-.Ltext0
	.2byte	0x1
	.byte	0x5f
	.4byte	0
	.4byte	0
.LLST6:
	.4byte	.LVL17-.Ltext0
	.4byte	.LVL18-.Ltext0
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL18-.Ltext0
	.4byte	.LVL20-.Ltext0
	.2byte	0x1
	.byte	0x5f
	.4byte	.LVL21-.Ltext0
	.4byte	.LFE4-.Ltext0
	.2byte	0x1
	.byte	0x5f
	.4byte	0
	.4byte	0
.LLST7:
	.4byte	.LVL17-.Ltext0
	.4byte	.LVL18-.Ltext0
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL18-.Ltext0
	.4byte	.LVL19-.Ltext0
	.2byte	0x1
	.byte	0x5e
	.4byte	.LVL19-.Ltext0
	.4byte	.LVL21-.Ltext0
	.2byte	0x3
	.byte	0x7e
	.byte	0x7f
	.byte	0x9f
	.4byte	.LVL21-.Ltext0
	.4byte	.LFE4-.Ltext0
	.2byte	0x1
	.byte	0x5e
	.4byte	0
	.4byte	0
.LLST4:
	.4byte	.LVL13-.Ltext0
	.4byte	.LVL14-.Ltext0
	.2byte	0x3
	.byte	0x9
	.byte	0x80
	.byte	0x9f
	.4byte	.LVL14-.Ltext0
	.4byte	.LVL15-.Ltext0
	.2byte	0x1
	.byte	0x5f
	.4byte	0
	.4byte	0
.LLST5:
	.4byte	.LVL13-.Ltext0
	.4byte	.LVL14-.Ltext0
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL14-.Ltext0
	.4byte	.LFE3-.Ltext0
	.2byte	0x1
	.byte	0x5e
	.4byte	0
	.4byte	0
.LLST2:
	.4byte	.LVL8-.Ltext0
	.4byte	.LVL9-.Ltext0
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL9-.Ltext0
	.4byte	.LVL11-.Ltext0
	.2byte	0x1
	.byte	0x5f
	.4byte	.LVL12-.Ltext0
	.4byte	.LFE2-.Ltext0
	.2byte	0x1
	.byte	0x5f
	.4byte	0
	.4byte	0
.LLST3:
	.4byte	.LVL8-.Ltext0
	.4byte	.LVL9-.Ltext0
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL9-.Ltext0
	.4byte	.LVL10-.Ltext0
	.2byte	0x1
	.byte	0x5e
	.4byte	.LVL10-.Ltext0
	.4byte	.LVL12-.Ltext0
	.2byte	0x3
	.byte	0x7e
	.byte	0x7f
	.byte	0x9f
	.4byte	.LVL12-.Ltext0
	.4byte	.LFE2-.Ltext0
	.2byte	0x1
	.byte	0x5e
	.4byte	0
	.4byte	0
.LLST1:
	.4byte	.LVL4-.Ltext0
	.4byte	.LVL5-.Ltext0
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL5-.Ltext0
	.4byte	.LVL6-.Ltext0
	.2byte	0x1
	.byte	0x5f
	.4byte	.LVL6-.Ltext0
	.4byte	.LVL7-.Ltext0
	.2byte	0x3
	.byte	0x7f
	.byte	0x7f
	.byte	0x9f
	.4byte	.LVL7-.Ltext0
	.4byte	.LFE1-.Ltext0
	.2byte	0x1
	.byte	0x5f
	.4byte	0
	.4byte	0
.LLST0:
	.4byte	.LVL0-.Ltext0
	.4byte	.LVL1-.Ltext0
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL1-.Ltext0
	.4byte	.LVL2-.Ltext0
	.2byte	0x1
	.byte	0x5f
	.4byte	.LVL2-.Ltext0
	.4byte	.LVL3-.Ltext0
	.2byte	0x3
	.byte	0x7f
	.byte	0x7f
	.byte	0x9f
	.4byte	.LVL3-.Ltext0
	.4byte	.LFE0-.Ltext0
	.2byte	0x1
	.byte	0x5f
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.4byte	.LBB2-.Ltext0
	.4byte	.LBE2-.Ltext0
	.4byte	.LBB3-.Ltext0
	.4byte	.LBE3-.Ltext0
	.4byte	0
	.4byte	0
	.4byte	.LBB4-.Ltext0
	.4byte	.LBE4-.Ltext0
	.4byte	.LBB5-.Ltext0
	.4byte	.LBE5-.Ltext0
	.4byte	0
	.4byte	0
	.4byte	.LBB6-.Ltext0
	.4byte	.LBE6-.Ltext0
	.4byte	.LBB7-.Ltext0
	.4byte	.LBE7-.Ltext0
	.4byte	.LBB8-.Ltext0
	.4byte	.LBE8-.Ltext0
	.4byte	0
	.4byte	0
	.4byte	.LBB9-.Ltext0
	.4byte	.LBE9-.Ltext0
	.4byte	.LBB10-.Ltext0
	.4byte	.LBE10-.Ltext0
	.4byte	.LBB11-.Ltext0
	.4byte	.LBE11-.Ltext0
	.4byte	0
	.4byte	0
	.4byte	.LBB12-.Ltext0
	.4byte	.LBE12-.Ltext0
	.4byte	.LBB13-.Ltext0
	.4byte	.LBE13-.Ltext0
	.4byte	.LBB14-.Ltext0
	.4byte	.LBE14-.Ltext0
	.4byte	0
	.4byte	0
	.4byte	.LBB15-.Ltext0
	.4byte	.LBE15-.Ltext0
	.4byte	.LBB16-.Ltext0
	.4byte	.LBE16-.Ltext0
	.4byte	0
	.4byte	0
	.4byte	.LBB17-.Ltext0
	.4byte	.LBE17-.Ltext0
	.4byte	.LBB18-.Ltext0
	.4byte	.LBE18-.Ltext0
	.4byte	0
	.4byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF13:
	.string	"vec1"
.LASF11:
	.string	"__int8_t"
.LASF27:
	.string	"vect_add"
.LASF14:
	.string	"vecOut"
.LASF25:
	.string	"../src/NN_operations/vector_operations.c"
.LASF6:
	.string	"short unsigned int"
.LASF19:
	.string	"scalarOut"
.LASF12:
	.string	"int8_t"
.LASF4:
	.string	"unsigned char"
.LASF24:
	.string	"GNU C17 10.2.0 -mabi=ilp32 -march=rv32imcv -mtune=rocket -march=rv32imcv -g -Os"
.LASF22:
	.string	"vect_addRecursive"
.LASF20:
	.string	"temp"
.LASF16:
	.string	"vect_ReLu"
.LASF8:
	.string	"long unsigned int"
.LASF26:
	.string	"/home/openhw_ai_accel/nn_software/NN_algorithms_vector_assembly/riscV_build"
.LASF23:
	.string	"vect_mult"
.LASF0:
	.string	"unsigned int"
.LASF18:
	.string	"vec2"
.LASF9:
	.string	"long long unsigned int"
.LASF17:
	.string	"vect_dotProduct"
.LASF15:
	.string	"vect_ReLu6"
.LASF1:
	.string	"long long int"
.LASF10:
	.string	"char"
.LASF21:
	.string	"vect_maxRecursive"
.LASF5:
	.string	"short int"
.LASF7:
	.string	"long int"
.LASF2:
	.string	"long double"
.LASF3:
	.string	"signed char"
	.ident	"GCC: (GNU) 10.2.0"
