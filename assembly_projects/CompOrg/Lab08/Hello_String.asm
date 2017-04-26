# Start Hello_String.asm
	.data	# Data declaration sect
banner:
	.asciiz	"\nMy name is Amaya,\nMichael Amaya\n"
	
	.text
main:		# Start of code sect
	# Print Data
	li $v0, 4
	la $a0, banner
	syscall

	# Exit Program
	li $v0, 10
	syscall

# End Hello_String.asm

