# Start Range_Sum.asm
	.data	
banner:
	.asciiz	"Range Sum 0-100: "	

	.text
main:				# Start of code sect
	# Declare Variables
	li $s0, 0  		# Sum
	li $s1, 0  		# Starting Range
	li $s2, 100 	# Ending Range
	move $t0, $s1	# Range Counter i = start_range
	
	# Print Banner
	li $v0, 4
	la $a0, banner
	syscall
	
	# Get Summation
while:
	bgt $t0, $s2, Print_Exit # While( start_range <= end_range )
	add $s0, $s0, $t0		 # sum += i
	addi $t0, $t0, 1		 # i++
	j while
	
Print_Exit:
	# Print Answer
	move $a0, $s0
	li $v0, 1
	syscall
	
	# Exit Function
	li $v0, 10
	syscall

# End Range_Sum.asm

