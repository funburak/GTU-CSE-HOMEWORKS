module sub_32_bit(
	input [31:0] A,
	input [31:0] B,
	input carryIn,
	output carryOut,
	output [31:0] Result
);
	
	wire [31:0] not_B;
	not_32_bit i0(.A(B), .Result(not_B));
	adder_32_bit i1(.A(A), .B(not_B), .carryIn(carryIn), .carryOut(carryOut), .Result(Result));

endmodule
