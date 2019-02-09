	.file	"Lab1.c"
	.text
	.section	.rodata
.LC0:
	.string	"%s \n"
	.text
	.globl	helloWorld
	.type	helloWorld, @function
helloWorld:
.LFB0:
	.cfi_startproc
	pushq	%rbp                        //push frame base to stack
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp                  //change the frame base to the stack pointer
	.cfi_def_cfa_register 6
	subq	$32, %rsp                   //subtract 32 from stack pointer
	movq	%fs:40, %rax                //change value of rax to value at mem addr 40
	movq	%rax, -8(%rbp)              //change value of mem at addr (rbp-8) to rax
	xorl	%eax, %eax                  //XOR eax with itself
	movabsq	$8022916924116329800, %rax  //set rax to massive constant
	movq	%rax, -21(%rbp)             //change value of mem at addr (rbp-21) to rax
	movl	$560229490, -13(%rbp)       //change value of mem at addr (rbp-13) to constant
	movb	$0, -9(%rbp)                //change value of mem at addr (rbp-9) to 0
	leaq	-21(%rbp), %rax             //change value of rax to (rbp-21)
	movq	%rax, %rsi                  //change value of rsi to rax
	leaq	.LC0(%rip), %rdi            //change value of rdi to rip
	movl	$0, %eax                    //change value of eax to 0
	call	printf@PLT                  //part of stdio.h
	nop                                 //skip instruction
	movq	-8(%rbp), %rax              //change value of rax to mem at addr (rbp-8)
	xorq	%fs:40, %rax                //rax gets rax XOR mem at addr 40
	je	.L2                             //jump if zero to label L2
	call	__stack_chk_fail@PLT
.L2:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	helloWorld, .-helloWorld
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp                        //push frame base to stack
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp                  //change rbp to rsp
	.cfi_def_cfa_register 6
	subq	$16, %rsp                   //subtract 16 from rsp
	movl	$0, -4(%rbp)                //change value of mem at addr (rbp-40) to 0
	jmp	.L4                             //unconditional jump to label L4
.L5:
	movl	$0, %eax                    //change eax to 0
	call	helloWorld                  //run helloWorld subroutine
	addl	$1, -4(%rbp)                //add 1 to mem at addr (rbp-4)
.L4:
	cmpl	$4, -4(%rbp)                //compare mem at addr (rbp-4) with 4
	jle	.L5                             //jump if <= to label L5
	movl	$0, %eax                    //change eax to 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 8.2.0-7ubuntu1) 8.2.0"
	.section	.note.GNU-stack,"",@progbits
