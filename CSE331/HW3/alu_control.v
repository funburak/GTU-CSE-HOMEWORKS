module alu_control(
	output [2:0] alu_ctr,
	input [5:0] function_code,
	input [2:0] ALUop
);

	wire r_add, r_sub, r_and, r_or, r_slt, r_jr;
	wire addi, subi, andi, ori, lw, sw, lb, sb, slti, beq, bne;
	
	wire [5:0] function_code_not;
	wire [2:0] ALUop_not;
	
	wire andOp,subOp,orOp;
	
	not not1(function_code_not[0],function_code[0]);
	not not2(function_code_not[1],function_code[1]);
	not not3(function_code_not[2],function_code[2]);
	not not4(function_code_not[3],function_code[3]);
	not not5(function_code_not[4],function_code[4]);
	not not6(function_code_not[5],function_code[5]);
	
	
	not not7(ALUop_not[0],ALUop[0]);
	not not8(ALUop_not[1],ALUop[1]);
	not not9(ALUop_not[2],ALUop[2]);
	
	// add -> func code 000010
	and is_add(r_add, function_code_not[5], function_code_not[4], function_code_not[3], function_code_not[2], function_code[1], function_code_not[0]);
	
	// sub -> func code 000011
	and is_sub(r_sub,function_code_not[5], function_code_not[4], function_code_not[3], function_code_not[2], function_code[1], function_code[0]);
	
	// and 000100
	and is_and(r_and,function_code_not[5], function_code_not[4], function_code_not[3], function_code[2], function_code_not[1], function_code_not[0]);
	
	// or 000101
	and is_or(r_or,function_code_not[5], function_code_not[4], function_code_not[3], function_code[2], function_code_not[1], function_code[0]);
	
	// slt 000111
	and is_slt(r_slt,function_code_not[5], function_code_not[4], function_code_not[3], function_code[2], function_code[1], function_code[0]);
	
	// jr 001000
	and is_jr(r_jr,function_code_not[5], function_code_not[4], function_code[3], function_code_not[2], function_code_not[1], function_code_not[0]);
	

	// andi aluop 000
	and is_andi(andi,ALUop_not[2], ALUop_not[1], ALUop_not[0]);
	
	// ori 001
	and is_ori(ori,ALUop_not[2], ALUop_not[1], ALUop[0]);
	
	// slti 100
	and is_slti(slti,ALUop[2], ALUop_not[1], ALUop[0]);
	
	// addi,lb,sb,lw,sw 101
	and is_addi(addi,ALUop[2], ALUop_not[1], ALUop[0]);
	and is_lb(lb,addi,1'b1);
	and is_sb(sb,addi,1'b1);
	and is_lw(lw,addi,1'b1);
	and is_sw(sw,addi,1'b1);
	
	// subi,bne,beq 110
	and is_subi(subi,ALUop[2], ALUop[1], ALUop_not[0]);
	and is_bne(bne,subi,1'b1);
	and is_beq(beq,subi,1'b1);
	
	
	or andOperation(andOp,r_and,andi,r_or,ori);
	nor aluctr2(alu_ctr[2],andOp,1'b0);
	
	or subOperation(subOp,r_sub,subi,beq,bne);
	and aluctr1(alu_ctr[1],subOp,1'b1);
	
	or orOperation(orOp,ori,addi,lb,sb,lw,sw,r_or,r_add);
	and aluctr0(alu_ctr[0],orOp,1'b1);
	
endmodule
