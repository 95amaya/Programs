# Begin ArrayMin.asm

	.text
main:
	li $s0, 0		# counter i
	la $t0, array	# *pArray = &array
	li $t1, 12		# array length
	li $t2, 0xFFFF	# Starting Min Value

	# Print banner
	la $a0, banner
	li $v0, 4
	syscall

do: 	
	lw $t3, 0($t0)		# temp = *pArray
	
	# Print temp 
	move $a0, $t3		# cout << temp
	li $v0, 1
	syscall

	
	# if ( min < temp ) skip 
	blt $t2, $t3, continue
	move $t2, $t3			# else min = temp
	
continue:
	# Increment pointer by 4 bytes and counter by 1 int
	addi $t0,$t0, 4		#each int is 4 bytes, pArray++ (pointer addition)
	addi $s0, $s0, 1	#i++
	
	beq $s0,$t1,Exit	# do while ( i < 12 ) 	
	# Print Comma
	la $a0, comma
	li $v0, 4
	syscall
	j do				#J Jumps and loops back through

Exit:	
	# Print array min & exit program
	la $a0, done
	li $v0, 4
	syscall

	move $a0, $t2
	li $v0, 1
	syscall
	
	li $v0,10
	syscall

	.data
array:	.word	45 56 23 11 1 67 42 9 34 12 11 45 # int array = {0,...,11}
banner:	.asciiz	"Array Min\narray: ["
comma:	.asciiz ", "
done:	.asciiz "]\nMinimum: "

# End ArrayMin.asm