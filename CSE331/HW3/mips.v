module mips(
	input clock
);

	reg [31:0] pc = 32'b0;
	wire [31:0] instruction;
	wire [31:0] pc_temp;
	wire regDst, branch, memRead, memWrite,ALUsrc,regWrite,jump,byteOperations,move;
	wire [2:0] ALUop;
	wire [4:0] writeRegister;
	wire [31:0] readData1, readData2;
	wire [31:0] writeData;
	wire [31:0] signExtended;
	wire [2:0] aluControl;
	wire [31:0] aluResult;
	wire zeroBit;
	wire [31:0] aluSrc2;
	wire [31:0] shiftedAddress;
	wire [31:0] pcAdded;
	wire [31:0] pcAdded1;
	wire pcSelect;
	wire [31:0] memoryRead;
	wire [31:0] moveData;
	wire [31:0] writeData1;
	wire [31:0] jumpTo;
	wire [31:0] jumpAddress;
		
	instruction_block i0(.instruction(instruction), .pc(pc));
		
	control_unit i1(.regDst(regDst), 
							.branch(branch), 
							.memRead(memRead), 
							.memWrite(memWrite), 
							.ALUop(ALUop), 
							.ALUsrc(ALUsrc), 
							.regWrite(regWrite), 
							.jump(jump), 
							.byteOperations(byteOperations), 
							.move(move), 
							.opcode(instruction[31:26]));
	
	// 2x1 mux to choose the register destination						
	assign writeRegister = (regDst) ? instruction[15:11] : instruction[20:16];
		 
	 register_block i2(.read_data1(readData1), 
								.read_data2(readData2), 
								.byteOperations(byteOperations), 
								.write_data(writeData), 
								.read_reg1(instruction[25:21]), 
								.read_reg2(instruction[20:16]),
								.write_reg(writeRegister),
								.regWrite(regWrite));
															
	sign_extend i3(.sign_ext_imm(signExtended), .imm(instruction[15:0]));
		
	alu_control i4(.alu_ctr(aluControl), .function_code(instruction[5:0]), .ALUop(ALUop));
	
	// 2x1 mux to choose the alusrc2
	assign aluSrc2 = (ALUsrc) ? signExtended : readData2;
	
	alu i5(.alu_result(aluResult), .zero_bit(zeroBit), .alu_src1(readData1), .alu_src2(aluSrc2), .alu_ctr(aluControl));
		 
	shift_left_2 i6(.shifted_address(shiftedAddress), .address(signExtended));
	
	adder_32_bit i7(.Result(pc_temp), .carryOut(cout), .A(pc), .B(32'd4), .carryIn(1'b0)); // pc = pc + 4
	
	adder_32_bit i8(.Result(pcAdded1), .carryOut(cout), .A(shiftedAddress), .B(pc_temp), .carryIn(1'b0));
	
	// branch check stage (only beq is working)
	and i9(pcSelect, zeroBit, branch);
	
	// 2x1 mux to choose what will be next program counter
	assign pcAdded = (pcSelect) ? pcAdded1 : pc_temp;
			
	// set the jump address to 32 bits by concatenating with 0's
	assign jumpAddress = {4'b0,instruction[25:0], 2'b0};
	
	// 2x1 mux to choose the next program counter (only jump instruction is working)
	assign jumpTo = (jump) ? jumpAddress : pcAdded;
	
	always @ (posedge clock) begin
		pc <= jumpTo;
		$display("pc = %b, instruction=%b", pc,instruction);
	end
	
	memory_block i10(.read_data(memoryRead), 
							.byteOperations(byteOperations), 
							.address(aluResult[17:0]), 
							.write_data(readData2), 
							.memRead(memRead), 
							.memWrite(memWrite));
							
	// 2x1 mux to choose what to write back to the register
	assign writeData1 = (memRead) ? memoryRead : aluResult;
	
	// 2x1 mux to support move operation
	assign writeData = (move) ? readData1 : writeData1;	
endmodule
