	.text
	.file	"main"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	$0, (%rsp)
	movq	$0, 8(%rsp)
	movq	$1, 16(%rsp)
	callq	li@PLT
	movq	%rax, (%rsp)
	testq	$-2, %rax
	jne	.LBB0_2
# %bb.1:                                # %then
	movq	(%rsp), %rdi
	callq	imprimei@PLT
	xorl	%edi, %edi
	callq	termine@PLT
	jmp	.LBB0_2
	.p2align	4, 0x90
.LBB0_3:                                # %loop
                                        #   in Loop: Header=BB0_2 Depth=1
	movq	8(%rsp), %rax
	incq	%rax
	movq	%rax, 8(%rsp)
	imulq	%rax, %rax
	movq	%rax, 16(%rsp)
.LBB0_2:                                # %test
                                        # =>This Inner Loop Header: Depth=1
	movq	16(%rsp), %rax
	cmpq	(%rsp), %rax
	jle	.LBB0_3
# %bb.4:                                # %after
	movq	8(%rsp), %rdi
	decq	%rdi
	callq	imprimei@PLT
	xorl	%edi, %edi
	callq	termine@PLT
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
