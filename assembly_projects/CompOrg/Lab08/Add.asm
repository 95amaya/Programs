# Start Add.asm
	.data	# Data declaration sect
	
banner:
	.asciiz	"Hello World!\n"
	
add_header:
	.ascii "Let's Add: "
	.asciiz "4 + 5 = "
	
	.text
	
main:		# Start of code sect
	li $v0, 4
	la $a0, banner	# Show Banner
	syscall
	la $a0, add_header	# Show add_header
	syscall

	li $s0, 4		
	li $s1, 5
	add $a0, $s0, $s1	# Store in $a0
	
	li $v0, 1			# Print $a0 number to console
	syscall
	j Exit
	
Exit:
	li $v0, 10
	syscall

# End Add.asm

