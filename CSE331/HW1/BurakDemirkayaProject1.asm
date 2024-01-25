		.data
StrRow:		.asciiz "Please enter the number of rows: "
StrCol:		.asciiz "Please enter the number of columns: "
StrNumber:	.asciiz "Please enter the number of bombs that will be planted: "
StrCoord:	.asciiz "Please enter the coordinates of the bombs as integer value:  "
StrInitial:	.asciiz "Inıtial state\n"
StrOneSecond:	.asciiz "After 1 second\n"
StrTwoSecond:	.asciiz "After 2 seconds\n"
StrThreeSecond:	.asciiz "After 3 seconds\n"

Matrix:		.space 1024 # Matrix
MatrixRow:	.word 0 # Row number of matrix
MatrixCol:	.word 0 # Col number of matrix

CoordsArray:	.space 100 # Coordinates of array

		.text
		
Main:	
		la $a0, StrRow # Print the StrRow string
		li $v0, 4
		syscall
		
		li $v0, 5 # Read the row number
		syscall
		move $a1, $v0 # Store the row number in register $a1
		
		la $a0, StrCol # Print the StrCol string
		li $v0, 4
		syscall
		
		li $v0, 5 # Read the column number
		syscall
		move $a2, $v0 # Store the column number in register $a2
		
		la $a0, StrNumber # Print the StrNumber string
		li $v0, 4
		syscall
		
		li $v0, 5 # Read bomb count number
		syscall
		move $a3, $v0 # Store bomb count number in register $a3
		
		la $s0, Matrix # Store the base address of Matrix in register $s0
		li $t0, 46 # Store the ASCII value of '.' in register $t0
		
		li $t1, 0 # row index
		li $t2, 0 # column index
		
		mul $t3, $a1, $a2 # total number of cells = row * column
		
		li $t4, 0 # index counter
		
		
		jal CreateMatrix # Create row X column matrix size and fill it with '.' characters
		jal LoopBombCoord # Take the coordinates of the bomb and store it in CoordsArray
		la $s0, Matrix # Store the base address of Matrix in $s0 register
		jal LoopPlaceBomb # Place the bombs to the given coordinates
		la $a0, StrInitial # Print the StrInitial string
		li $v0, 4
		syscall
		jal PrintMatrix # Print the matrix
		li $t1, 0 # reset row index
		li $t2, 0 # reset column index
		
		la $a0, StrOneSecond # Print the StrOneSecond string
		li $v0, 4
		syscall
		li $t1, 0 # Reset row index
		jal PrintMatrix
		
		li $t1, 0 # Reset row index
		jal FillBombs # Place bombs to the empty cells
		la $a0, StrTwoSecond
		li $v0, 4
		syscall
		li $t1, 0 # reset row index
		jal PrintMatrix # Print the matrix
		
		jal DetonateBombs # Detonate the bombs at their positions and 1 cell near them at 4 directions
		la $a0, StrThreeSecond # Print the StrThreeSecond string
		li $v0, 4
		syscall
		li $t1, 0 # Reset row index
		jal PrintMatrix
		j Exit # Terminate program
		
CreateMatrix:	
		sb $t0, 0($s0) # Store the . character to the base address of Matrix
		addi $s0, $s0, 1 # Move to the next address of Matrix
		subi $t3, $t3, 1 # total number of cells - 1
		bnez $t3, CreateMatrix
		
		jr $ra
		
		
LoopBombCoord:
		bge $t4, $a3, LoopCoordExit # If index >= bombCount
		
		la $a0, StrCoord # Print the StrCoord string
		li $v0, 4
		syscall
		
		li $v0, 5 # Read the coordinate integer
		syscall
		
		la $s1, CoordsArray # Store the base address of coordsArrray
		sll $t5, $t4, 2 # Multiply index by 4 in order to get the next word address
		add $s4, $t5, $s1 # Calculate the next word address
		sw $v0, 0($s4) # Store the read integer value at the address
		
		addi $t4, $t4, 1 # index++
		
		j LoopBombCoord
		
LoopCoordExit:
		li $t4, 0 # Reset index
		jr $ra
		
LoopPlaceBomb:
    		bge $t4, $a3, LoopPlaceBombExit # If index >= bomb count, exit loop
    		lw $s2, 0($s1) # Load the current element in CoordsArray into register $s2

    		div $s2, $a2 # Divide coordinate by number of columns
    		mflo $s5 # Quotient is row (coordinate / numberOfColumns = row of the coordinate)
    		mfhi $s6 # Remainder is column (coordinate % numberOfColumns = column of the coordinate)

    		mul $s7, $s5, $a2 # Calculate row * number of columns
    		add $s7, $s7, $s6 # Add column

    		add $t9, $s0, $s7 # Calculate the address for storing the character
    		
    		li $v0, 11
    		li $a0, 79 # ASCII value for 'O' character
    		sb $a0, 0($t9) # Store the byte at the address

    		addi $t4, $t4, 1 # index++
    		addi $s1, $s1, 4 # Move to the next element in CoordsArray
    		j LoopPlaceBomb
    		
LoopPlaceBombExit:
		jr $ra
		
FillBombs:
		bge $t1, $a1, FillBombsExit # If i >= number of rows
		li $t2, 0 # Reset column index
		
FillBombRow:
		bge $t2, $a2, FillBombNextRow # IF j >= number of columns
		mul $t3, $t1, $a2 # Calculate row * number of columns
		add $t3, $t3, $t2 # Add column to it
		
		la $t4, Matrix # Load base address of Matrix at register $t4
		add $t5, $t4, $t3 # Calculate the address of the element
		
		li $v0, 11 # Print 'O' character into the current address
		li $a0, 79
		sb $a0, 0($t5)
		
		addi $t2, $t2, 1 # columnIndex++
		j FillBombRow
		
FillBombNextRow:
		addi $t1, $t1, 1 # rowIndex++
		j FillBombs
	
FillBombsExit:
		jr $ra
		
			
DetonateBombs:
		la $s1, CoordsArray # Load the base address of coordsArray in register $s1
		li $t0, 0 # bombCountIndex
		
DetonateBombsLoop:
		bge $t0, $a3, DetonateBombsLoopExit # If bombCountIndex >= bombCount 
		
		lw $s2, 0($s1) # Load the current element in coordsArray into $s2 register
		
		div $s2, $a2 # Divide coordinate by the number of columns
		mflo $t3 # Quotient is row (coordinate / number of columns)
		mfhi $t4 # Remainder is column (coordinate % number of columns)
		
		mul $t5, $t3, $a2 # Calculate row * number of columns
		add $t5, $t5, $t4 # Add column to it
		
		la $s0, Matrix # Load the base address of Matrix into $s0 register
		add $t6, $t5, $s0 # Add the index to it
		li $v0, 11
		li $a0, 46 # ASCII code for '.' character
		sb $a0, 0($t6) # Store the '.' chracter to the address
		
		# North cell
		subi $t7, $t3, 1 # Calculate (row - 1)
		mul $t8, $t7, $a2 # Calculate (row-1) * number of columns
		add $t9, $t8, $t4 # Add column to it
		bltz $t9, SkipNorth # If the index is less than zero, skip this cell
		add $s4, $t9, $s0 # Get to that index
		li $v0, 11
		li $a0, 46 # ASCII value of '.' character
		sb $a0, 0($s4) # Store the '.' characer to the address
SkipNorth:
		# South cell
		addi $t7, $t3, 1 # Calculate (row + 1)
		mul $t8, $t7, $a2 # Calculate (row+1) * number of columns
		add $t9, $t8, $t4 # Add column to it
		bge $t7, $a1, SkipSouth # If the row coordinate of the South cell exceeds the total number of rows, skip this cell
		add $s4, $t9, $s0 # Get to that index
		li $v0, 11
		li $a0, 46 # ASCII value of '.' character
		sb $a0, 0($s4) # Store the '.' characer to the address
SkipSouth:		
		# East cell
		addi $t7, $t4, 1 # Calculate (column + 1)
		mul $t8, $t3, $a2 # Calculate row * number of column
		add $t6, $t7, $t8 # Add (column + 1) to it
		div $t6, $a2 # Divide the east cell coordinate to the number of columns
		mflo $s6 # Quotient is the row
		mfhi $s7 # Remainder is the column
		bgt $s6, $t3, SkipEast # If the east cell's row coordinate is greater than the current row, skip this cell
		add $s4, $t6, $s0 # Get to that index
		li $v0, 11
		li $a0, 46 # ASCII value of '.' character
		sb $a0, 0($s4) # Store the '.' characer to the address
SkipEast:				
		# West cell
		subi $t7, $t4, 1 # Calculate (column - 1)
		mul $t8, $t3, $a2 # Calculate row * number of columns
		add $t9, $t7, $t8 # Add (column - 1) to it
		div $t9, $a2 # Divide the west cell coordinate to the number of columns
		mflo $s6 # Quotient is the row
		mfhi $s7 # Remainder is the column 
		blt $s6, $t3, SkipWest # If the west cell's row coordinate is less than the current row, skip this cell
		add $s4, $t9, $s0 # Get to that index
		li $v0, 11
		li $a0, 46 # ASCII value of '.' character
		sb $a0, 0($s4) # Store the '.' characer to the address
		
SkipWest:		
		addi $t0, $t0, 1 # Increment index by 1
		addi $s1, $s1, 4 # Get to the next element in coordsArray
		j DetonateBombsLoop
		
DetonateBombsLoopExit:
		jr $ra
				
										
PrintMatrix:
		bge $t1, $a1, EndPrint # If i >= number of rows
		li $t2, 0 # Reset column index
		
PrintRow:
		bge $t2, $a2, NextRow # If j 
		
		mul $t5, $t1, $a2 # Calculate row * number of columns
		add $t5, $t5, $t2 # Add column to it
		
		la $t6, Matrix # Load base address of Matrix
		add $t7, $t6, $t5 # Calculate the address of the element
		lb $t8, 0($t7) # Load the element
		
		li $v0, 11 # Print character
		move $a0, $t8 # Move the current character to $a0 in order to print
		syscall
		
            	li $v0, 11 # Print space character
            	li $a0, 32 # ASCII code for space
            	syscall
            	
            	addi $t2, $t2, 1 # columnIndex++
            	
            	j PrintRow
		
NextRow:
            	# Print a newline character to move to the next row
            	li $v0, 11
            	li $a0, 10         # ASCII code for newline
            	syscall

            	addi $t1, $t1, 1  # Increment i

            	j PrintMatrix
EndPrint:	
		jr $ra
				
Exit:
		li $v0, 10 # Terminate program
		syscall
