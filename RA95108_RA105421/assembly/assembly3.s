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
	movq	$0, 8(%rsp)
	movq	$0, 16(%rsp)
	callq	li@PLT
	movq	%rax, 16(%rsp)
	jmp	.LBB0_1
	.p2align	4, 0x90
.LBB0_4:                                # %ifcont
                                        #   in Loop: Header=BB0_1 Depth=1
	incq	8(%rsp)
.LBB0_1:                                # %test
                                        # =>This Inner Loop Header: Depth=1
	movq	8(%rsp), %rax
	cmpq	16(%rsp), %rax
	jg	.LBB0_5
# %bb.2:                                # %loop
                                        #   in Loop: Header=BB0_1 Depth=1
	testb	$1, 8(%rsp)
	jne	.LBB0_4
# %bb.3:                                # %then
                                        #   in Loop: Header=BB0_1 Depth=1
	movq	8(%rsp), %rdi
	callq	imprimei@PLT
	jmp	.LBB0_4
.LBB0_5:                                # %after
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
