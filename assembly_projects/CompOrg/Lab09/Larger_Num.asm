# Start Large_Num.asm
	.text
main:				# Start of code sect
	# Declare Variables
	li $t0, 0  		# num1
	li $t1, 10  	# num2
	li $t2, 0 		# Store larger num
	
	# Print Header
	jal Print_header
	
	# Get Greater than
	beq $t0, $t1, Equal 	# num1 == num2
	bgt $t0, $t1, Greater	# num1 > num2
	blt $t0, $t1, Less		# num1 < num2
	j Exit

# Branch Routines	
Equal:
	move $t2, $t0
	# Print t2
	jal Print_t2
	# Print result
	la $a0, equal
	li $v0, 4
	syscall
	# Exit program
	j Exit
	
Greater:
	move $t2, $t0
	# Print t2
	jal Print_t2
	# Print result
	la $a0, greater
	li $v0, 4
	syscall
	# Exit program
	j Exit
	
Less:
	move $t2, $t0
	# Print t2
	jal Print_t2
	# Print result
	la $a0, less
	li $v0, 4
	syscall
	# Exit program
	j Exit

# Exit Routine
Exit:
	# Exit Function
	li $v0, 10
	syscall

####################################################
# Subroutines
Print_header:
	# Print Banner
	li $v0, 4
	la $a0, banner
	syscall
	
	# Print contents of $t0
	la $a0, t0_text
	li $v0, 4
	syscall
	move $a0, $t0
	li $v0, 1
	syscall
	
	# Print sign 
	la $a0, sign
	li $v0, 4
	syscall
	
	# Print contents of $t1
	la $a0, t1_text
	li $v0, 4
	syscall
	move $a0, $t1
	li $v0, 1
	syscall
	
	# Return
	jr $ra
	
# Print contents of t2
Print_t2:
	la $a0, result
	li $v0, 4
	syscall
	move $a0, $t2
	li $v0, 1
	syscall
	jr $ra

########################################
# Data Declarations
	.data
banner:
	.asciiz	"Compare 2 nums:\n"	
t0_text:	
	.asciiz "$t0 = "
t1_text:	
	.asciiz "$t1 = "
sign:
	.asciiz " > "
result:
	.asciiz " ? : $t2 = "
equal:
	.asciiz " Equal\n"
greater:
	.asciiz " Greater Than\n"
less:
	.asciiz " Less Than\n"

# End Large_Num.asm

