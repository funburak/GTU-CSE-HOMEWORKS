module control_unit(
	output regDst,
	output branch,
	output memRead,
	output memWrite,
	output [2:0] ALUop,
	output ALUsrc,
	output regWrite,
	output jump,
	output byteOperations,
	output move,
	input [5:0] opcode
);

	wire [5:0] opcode_not;
	wire r_type, i_type, j_type, lw, sw, bne, beq;
	wire andi, ori, slti, addi, subi, lb, sb, j, jal;
	
	not not1(opcode_not[0],opcode[0]);
	not not2(opcode_not[1],opcode[1]);
	not not3(opcode_not[2],opcode[2]);
	not not4(opcode_not[3],opcode[3]);
	not not5(opcode_not[4],opcode[4]);
	not not6(opcode_not[5],opcode[5]);
	
	// R TYPE -> OPCODE 000000
	and is_r_type(r_type,opcode_not[0],opcode_not[1],opcode_not[2],opcode_not[3],opcode_not[4],opcode_not[5]);
	
	// ADDI -> OPCODE 000010
	and is_addi(addi, opcode_not[5], opcode_not[4], opcode_not[3], opcode_not[2], opcode[1], opcode_not[0]);
	
	// ANDI -> OPCODE 000100
	and is_andi(andi, opcode_not[5], opcode_not[4], opcode_not[3], opcode[2], opcode_not[1], opcode_not[0]);
	
	// ORI -> OPCODE 000101
	and is_ori(ori, opcode_not[5], opcode_not[4], opcode_not[3], opcode[2], opcode_not[1], opcode[0]);
	
	// BEQ -> OPCODE 100011
	and is_beq(beq, opcode[5], opcode_not[4], opcode_not[3], opcode_not[2], opcode[1], opcode[0]);
	
	// BNE -> OPCODE 100111
	and is_bne(bne, opcode[5], opcode_not[4], opcode_not[3], opcode[2], opcode[1], opcode[0]);
	
	// SLTI -> OPCODE 000111
	and is_slti(slti, opcode_not[5], opcode_not[4], opcode_not[3], opcode[2], opcode[1], opcode[0]);
	
	// LW -> OPCODE 001000
	and is_lw(lw, opcode_not[5], opcode_not[4], opcode[3], opcode_not[2], opcode_not[1], opcode_not[0]);
	
	// SW -> OPCODE 010000
	and is_sw(sw, opcode_not[5], opcode[4], opcode_not[3], opcode_not[2], opcode_not[1], opcode_not[0]);
	
	// LB -> OPCODE 001001
	and is_lb(lb,opcode_not[5], opcode_not[4], opcode[3], opcode_not[2], opcode_not[1], opcode[0]);
	
	// SB -> OPCODE 010001
	and is_sb(sb,opcode_not[5], opcode[4], opcode_not[3], opcode_not[2], opcode_not[1], opcode[0]);
	
	// subi OPCODE 000011
	and is_subi(subi,opcode_not[5], opcode_not[4], opcode_not[3], opcode_not[2], opcode[1], opcode[0]);
	
	//  j 111000
	and is_j(j,opcode[5], opcode[4], opcode[3], opcode_not[2], opcode_not[1], opcode_not[0]);
	
	// jal 111001
	and is_jal(jal,opcode[5], opcode[4], opcode[3], opcode_not[2], opcode_not[1], opcode[0]);
	
	//move 100000
	and is_move(move,opcode[5], opcode_not[4], opcode_not[3], opcode_not[2], opcode_not[1], opcode_not[0]);
	
	

	and regDestination(regDst,r_type,1'b1);
	or isBranch(branch,bne,beq);
	or isMemRead(memRead,lw,lb);
	or isMemWrite(memWrite,sw,sb);
	nor isALUsrc(ALUsrc,r_type,bne,beq);
	or isRegWrite(regWrite,r_type,lw,andi,ori,slti,addi,subi,lb,move);
	or isJump(jump,j,jal);
	or isByteOperation(byteOperations,sb,lb);
	
	
	nor aluop2(ALUop[2],andi,ori);
	or aluop1(ALUop[1],subi,beq,bne,r_type);
	nor aluop0(ALUop[0],andi,slti,subi,beq,bne);

endmodule
