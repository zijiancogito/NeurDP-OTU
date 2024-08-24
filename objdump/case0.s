	.text
	.file	"case0.c"
	.globl	main                    // -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   // @main
// %bb.0:
	stp	x29, x30, [sp, #-80]!   // 16-byte Folded Spill
	stp	x20, x19, [sp, #64]     // 16-byte Folded Spill
	adrp	x20, i
	ldr	w9, [x20, :lo12:i]
	stp	x26, x25, [sp, #16]     // 16-byte Folded Spill
	stp	x24, x23, [sp, #32]     // 16-byte Folded Spill
	stp	x22, x21, [sp, #48]     // 16-byte Folded Spill
	cmp	w9, #31                 // =31
	mov	x29, sp
	b.gt	.LBB0_10
// %bb.1:
	adrp	x21, c
	ldr	w8, [x21, :lo12:c]
	adrp	x22, b
	adrp	x25, a
	adrp	x19, .L.str
	add	x22, x22, :lo12:b
	adrp	x23, j
	mov	w24, #1
	add	x25, x25, :lo12:a
	mov	w26, #9
	add	x19, x19, :lo12:.L.str
.LBB0_2:                                // =>This Loop Header: Depth=1
                                        //     Child Loop BB0_5 Depth 2
	cmp	w9, #31                 // =31
	b.eq	.LBB0_9
// %bb.3:                               // %.preheader
                                        //   in Loop: Header=BB0_2 Depth=1
	sxtw	x1, w9
	b	.LBB0_5
.LBB0_4:                                //   in Loop: Header=BB0_5 Depth=2
	add	x1, x1, #1              // =1
	cmp	w1, #31                 // =31
	str	w1, [x20, :lo12:i]
	b.eq	.LBB0_9
.LBB0_5:                                //   Parent Loop BB0_2 Depth=1
                                        // =>  This Inner Loop Header: Depth=2
	cmp	w8, #15                 // =15
	b.eq	.LBB0_10
// %bb.6:                               //   in Loop: Header=BB0_5 Depth=2
	ldr	w9, [x22, x1, lsl #2]
	cbnz	w9, .LBB0_4
// %bb.7:                               //   in Loop: Header=BB0_5 Depth=2
	ldr	w9, [x23, :lo12:j]
	add	w9, w9, #1              // =1
	cmp	w9, #9                  // =9
	str	w9, [x23, :lo12:j]
	b.ne	.LBB0_4
// %bb.8:                               //   in Loop: Header=BB0_2 Depth=1
	lsl	x8, x1, #2
	mov	x0, x19
	str	w24, [x22, x8]
	str	w26, [x25, x8]
	str	wzr, [x23, :lo12:j]
                                        // kill: def $w1 killed $w1 killed $x1
	bl	printf
	ldr	w8, [x20, :lo12:i]
	ldr	w10, [x21, :lo12:c]
	add	w9, w8, #1              // =1
	add	w8, w10, #1             // =1
	str	w9, [x20, :lo12:i]
	str	w8, [x21, :lo12:c]
	cmp	w9, #32                 // =32
	b.lt	.LBB0_2
	b	.LBB0_10
.LBB0_9:                                //   in Loop: Header=BB0_2 Depth=1
	mov	w9, #1
	str	w9, [x20, :lo12:i]
	cmp	w9, #32                 // =32
	b.lt	.LBB0_2
.LBB0_10:
	ldp	x20, x19, [sp, #64]     // 16-byte Folded Reload
	ldp	x22, x21, [sp, #48]     // 16-byte Folded Reload
	ldp	x24, x23, [sp, #32]     // 16-byte Folded Reload
	ldp	x26, x25, [sp, #16]     // 16-byte Folded Reload
	mov	w0, wzr
	ldp	x29, x30, [sp], #80     // 16-byte Folded Reload
	ret
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
                                        // -- End function
	.type	c,@object               // @c
	.bss
	.globl	c
	.p2align	2
c:
	.word	0                       // 0x0
	.size	c, 4

	.type	i,@object               // @i
	.data
	.globl	i
	.p2align	2
i:
	.word	1                       // 0x1
	.size	i, 4

	.type	j,@object               // @j
	.bss
	.globl	j
	.p2align	2
j:
	.word	0                       // 0x0
	.size	j, 4

	.type	a,@object               // @a
	.globl	a
	.p2align	2
a:
	.zero	120
	.size	a, 120

	.type	b,@object               // @b
	.globl	b
	.p2align	2
b:
	.zero	120
	.size	b, 120

	.type	.L.str,@object          // @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%d\n"
	.size	.L.str, 4

	.ident	"clang version 10.0.0-4ubuntu1 "
	.section	".note.GNU-stack","",@progbits
