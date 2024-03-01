module alu(
	output [31:0] alu_result,
	output zero_bit,
	input [31:0] alu_src1,
	input [31:0] alu_src2,
	input [2:0] alu_ctr
);
	
	wire [31:0] addResult, subResult, orResult, sltResult, andResult;
	wire cout;
	
	and_32_bit i0(.Result(andResult), .A(alu_src1), .B(alu_src2));
	or_32_bit i1(.Result(orResult), .A(alu_src1), .B(alu_src2));
	sub_32_bit i2(.Result(subResult), .carryOut(cout), .A(alu_src1), .B(alu_src2), .carryIn(1'b1));
	less_than_32_bit i3(.Result(sltResult), .A(alu_src1), .B(alu_src2));
	adder_32_bit i4(.Result(addResult), .carryOut(cout), .A(alu_src1), .B(alu_src2), .carryIn(1'b0));
	
	zero_bit_32_bit i5(.zero_bit(zero_bit), .A(subResult));

	mux8x1_32_bit i6(.sel(alu_ctr), .in0(andResult), .in1(orResult), .in2(32'b0), .in3(32'b0), .in4(sltResult), .in5(addResult), .in6(subResult), .in7(32'b0), .Result(alu_result));


endmodule
