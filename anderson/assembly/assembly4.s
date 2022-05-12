	.text
	.file	"main"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movq	$0, 16(%rsp)
	movq	$0, 24(%rsp)
	movq	$0, 32(%rsp)
	movq	$1, 8(%rsp)
	callq	li@PLT
	movq	%rax, 16(%rsp)
	callq	li@PLT
	movq	%rax, 24(%rsp)
	.p2align	4, 0x90
.LBB0_1:                                # %test
                                        # =>This Inner Loop Header: Depth=1
	movq	32(%rsp), %rax
	cmpq	24(%rsp), %rax
	jge	.LBB0_3
# %bb.2:                                # %loop
                                        #   in Loop: Header=BB0_1 Depth=1
	movq	8(%rsp), %rax
	imulq	16(%rsp), %rax
	movq	%rax, 8(%rsp)
	incq	32(%rsp)
	jmp	.LBB0_1
.LBB0_3:                                # %after
	movq	8(%rsp), %rdi
	callq	imprimei@PLT
	xorl	%edi, %edi
	callq	termine@PLT
	addq	$40, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
