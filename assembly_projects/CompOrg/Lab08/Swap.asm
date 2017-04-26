# Start Swap.asm
	.data	# Data declaration sect
	
banner:
	.asciiz "\nLet's swap $t0 and $t1\nBefore: "
t0_text:	
	.asciiz "$t0 = "
t1_text:	
	.asciiz " $t1 = "
after:
	.asciiz "\nAfter: "
	.text
	
main:		# Start of code sect
	li $v0, 4
	la $a0, banner
	syscall
	# Declarations
	li $t0, 2
	li $t1, 4
	
	# Print Contents before
	jal Print_temp

	# Swap $t0 with $t1
	move $t2, $t1
	move $t1, $t0
	move $t0, $t2
	
	# Print contents after
	la $a0, after
	li $v0, 4
	syscall
	jal Print_temp
	
	# Exit Program
	j Exit

Print_temp:
	# Print contents of $t0
	la $a0, t0_text
	li $v0, 4
	syscall
	move $a0, $t0
	li $v0, 1
	syscall
	
	# Print contents of $t1
	la $a0, t1_text
	li $v0, 4
	syscall
	move $a0, $t1
	li $v0, 1
	syscall
	jr $ra
   
Exit:
	li $v0, 10
	syscall

# End Swap.asm