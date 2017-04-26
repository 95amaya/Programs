# Begin ArrayAdd.asm

	.text
main:
	li $s0, 0		# counter i
	li $s1, 0		# counter j
	la $s2, array1	# *pArray1 = &array1
	li $t0, 12		# array length
	la $t1, array1	# *pArray1 = &array1
	la $t2, array2	# *pArray2 = &array2

	# Print banner
	la $a0, banner
	li $v0, 4
	syscall

do: 	
	lw $t3, 0($t1)		# temp1 = *pArray1
	lw $t4, 0($t2)		# temp2 = *pArray2
	
	# Print temp 
	move $a0, $t3		# cout << temp1
	li $v0, 1
	syscall
	
	add $t3, $t3, $t4	# temp1 += temp2
	sw $t3, 0($t1)		# Save to memory

	# Increment pointer by 4 bytes and counter by 1 int
	addi $t1,$t1, 4		#each int is 4 bytes, pArray1++ (pointer addition)
	addi $t2,$t2, 4		#each int is 4 bytes, pArray2++ (pointer addition)
	addi $s0, $s0, 1	#i++
	
	beq $s0,$t0, Jout	# do while ( i < 12 ) 	
	# Print Comma
	la $a0, comma
	li $v0, 4
	syscall
	j do				#J Jumps and loops back through

Jout:
	# Print Header for new Array
	la $a0, after
	li $v0, 4
	syscall
	
print_Array1:
	lw $t3, 0($s2)		# temp1 = *pArray1
	
	# Print temp 
	move $a0, $t3		# cout << temp1
	li $v0, 1
	syscall
	
	# Increment pointer by 4 bytes and counter by 1 int
	addi $s2, $s2, 4		#each int is 4 bytes, pArray++ (pointer addition)
	addi $s1, $s1, 1	#j++
	
	beq $s1,$t0, Exit	# do while ( i < 12 ) 	
	
	# Print Comma
	la $a0, comma
	li $v0, 4
	syscall
	j print_Array1				#J Jumps and loops back through

Exit:
	# Exit program
	la $a0, done
	li $v0, 4
	syscall
	
	li $v0,10
	syscall

	.data
array1:	.word	0 1 2 3 4 5 6 7 8 9 10 11 # int array1 = {0,...,11}
array2:	.word	0 1 2 3 4 5 6 7 8 9 10 11 # int array2 = {0,...,11}
banner:	.asciiz	"Array Add\nArray1 Before: ["
comma:	.asciiz ", "
after:	.asciiz "]\nArray1 After: ["
done:	.asciiz "]\n"

# End ArrayMin.asm



