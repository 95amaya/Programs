# Start Powers.asm
	.data	# Data declaration sect
banner:
	.asciiz	"2^n Power Addition\nSum of 2^0 - 2^2: "	
	.text
main:				# Start of code sect
	# Declare Variables
	li $s0, 0  		# Sum
	li $s1, 0  		# Starting Range
	li $s2, 2 		# Ending Range
	move $t0, $s1	# Range Counter i = start_range
	li $s3, 1		# 2^i base
	
	# Print Banner
	li $v0, 4
	la $a0, banner
	syscall
	
	# Get Summation
while:
	bgt $t0, $s2, Print_Exit # While( start_range <= end_range )
	li $t2, 0 			# Initialize temp = 0 
	sllv $t2, $s3, $t0	# temp = 2^i
	add $s0, $s0, $t2	# sum += temp
	addi $t0, $t0, 1	# i++
	j while
	
Print_Exit:
	# Print Answer
	move $a0, $s0
	li $v0, 1
	syscall
	
	# Exit Function
	li $v0, 10
	syscall

# End Powers.asm

