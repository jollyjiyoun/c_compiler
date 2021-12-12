main:
	pushq	%rbp
	movq %rsp, rbp
	movq	$2, %r8
	movq	$3, %r9
	imulq	%r8, %r9
	movq	$5, %r8
	movq	$8, %r10
	imulq	%r8, %r10
	addq	%r9, %r10
	movq	%r10, %rdi
	call	printint
	movl $0, %eax
	popq %rbp
	ret
