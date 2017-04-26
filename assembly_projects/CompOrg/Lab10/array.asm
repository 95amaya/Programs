# Begin array.asm

	.text
main:
	li $s0,0		#counter i
	li $t1,10		#ending #
	la $t0,array1	#load array address into register

	# Print banner
	la $a0, banner
	li $v0,4
	syscall

loop: 	
	beq $s0,$t1,Exit	# while ( i < 10 ) 
	sw $s0,0($t0)		# array[i] = i (contents = address)

	# Print i
	move $a0,$s0
	li $v0,1
	syscall

	# Load pause timer to allow the user to see output slowly
	lw $t2,pause
	loop1:	
		bltz $t2,continue  # While ( time > 0)		
		sub $t2,$t2,1		# timer--
		j loop1
		
continue:
	# Increment pointer by 4 bytes and counter by 1 int
	add $t0,$t0,4		#each int is 4 bytes
	add $s0,$s0,1		#increment by 1
	j loop				#J Jumps and loops back through

Exit:	
	# Print done & exit program
	la $a0,done
	li $v0,4
	syscall

	li $v0,10
	syscall

	.data
array1:	.space	48 # 12 int elements * 4 bytes / int = 48 bytes
array2: .space	48
banner:	.asciiz	"Store Arrays\nIndex: "
done:	.asciiz "\nStored Numbers!\n"
pause:	.word	0x2ffff	#Pause timer

# End array.asm