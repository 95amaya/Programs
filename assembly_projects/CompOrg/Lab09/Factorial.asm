#Start Factorial.asm using the stack
	.text
main:	
	# Print Prompt
	la $a0,prompt
	li $v0,4
	syscall

	# Get user input number
	li $v0,5
	syscall
	move $a0,$v0

factorial:
	sub $sp,$sp,12
	sw $ra,0($sp)	#storing address of (n- 1) argument
	sw $a0,4($sp)	#storing n-1 number
	sw $s0,8($sp)	#storing room for 
	
	beqz $a0,basecase #Checks for basecase
	
	sub $a0,$a0,1	#n-1 argument
	jal factorial	#recursion puts answer in $v0
	lw $s0,4($sp)	#loads n-1 number
	mult $v0,$s0	#multiplying n*(n-1)
	mflo $v0		#storing answer in $v0
	j return

basecase:
	li $v0,1

return:	
	lw $s0,8($sp)   
	lw $a0,4($sp)   #retreiving n-1 number
	lw $ra,0($sp)	#retreiving address of (n- 1) argument
	add $sp,$sp,12
	beq $ra,0x400018,done
	jr $ra

done:
	# Print Factorial to console
	move $t0,$v0
	la $a0,answer
	li $v0,4
	syscall
	move $a0,$t0
	li $v0,1
	syscall	
	
	# Exit Program
	li $v0,10
	syscall

	.data
prompt:	.asciiz "Type a number up < 12: "
answer: .asciiz "\nFactorial: "

#End Factorial.asm

