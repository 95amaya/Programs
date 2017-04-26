# Begin StoreArray.asm

	.text
main:
	li $s0, 0		#counter i
	li $t1, 12		#ending #
	la $t0, array1	#*pArray1 = &array1
	la $t2, array2	#*pArray2 = &array2

	# Print banner
	la $a0, banner
	li $v0, 4
	syscall

store: 	
	beq $s0,$t1,Exit	# while ( i < 12 ) 
	lw $t4, 0($t0)		# temp = *pArray1
	
	# Print temp
	move $a0, $t4		# cout << temp
	li $v0, 1
	syscall
	
	# Save temp
	sw $t4, 0($t2)		# *pArray = temp

	# Load pause timer to allow the user to see output slowly
	lw $t3,pause
	pause_run:	
		bltz $t3,continue   # While ( time > 0)		
		sub $t3,$t3,1		# timer--
		j pause_run
		
continue:
	# Increment pointer by 4 bytes and counter by 1 int
	addi $t0,$t0,4		#each int is 4 bytes, pArray1++ (pointer addition)
	addi $t2,$t2,4		#each int is 4 bytes, pArray2++
	addi $s0, $s0, 1	#i++
	j store				#J Jumps and loops back through

Exit:	
	# Print done & exit program
	la $a0,done
	li $v0,4
	syscall

	li $v0,10
	syscall

	.data
array1:	.word	0 1 2 3 4 5 6 7 8 9 10 11 # int array1 = {0,...,11}
array2: .space	48						  # int array2[12]
banner:	.asciiz	"Store Arrays\narray1: "
done:	.asciiz "\nStored Numbers in array2!\n"
pause:	.word	0x2ffff	#Pause timer

# End StoreArray.asm

