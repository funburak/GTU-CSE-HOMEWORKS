module alu(
	input [31:0] A,
	input [31:0] B,
	input [2:0] ALUop,
	input clk,
	input start,
	input reset,
	input carryIn,
	output carryOutAdd, // I used seperate carryouts for add and subtract operations because when I try to use common one it give error.
	output carryOutSub,
	output [31:0] Result
);

	wire [31:0] andResult, orResult, xorResult, norResult, lessthanResult, addResult, subResult, modResult;
	
	and_32_bit i0(.A(A), .B(B), .Result(andResult));
	or_32_bit i1(.A(A), .B(B), .Result(orResult));
	xor_32_bit i2(.A(A), .B(B), .Result(xorResult));
	nor_32_bit i3(.A(A), .B(B), .Result(norResult));
	less_than_32_bit i4(.A(A), .B(B), .Result(lessthanResult));
	adder_32_bit i5(.A(A), .B(B), .carryIn(carryIn), .carryOut(carryOutAdd), .Result(addResult));
	sub_32_bit i6(.A(A), .B(B), .carryIn(carryIn), .carryOut(carryOutSub), .Result(subResult));
	mod i7(.A(A), .B(B), .clk(clk), .reset(reset), .start(start), .Result(modResult));
	
	
	mux8x1_32_bit i8(.sel(ALUop), .in0(andResult), .in1(orResult), .in2(xorResult), .in3(norResult), .in4(lessthanResult), .in5(addResult), .in6(subResult), .in7(modResult), .Result(Result));
	
		

endmodule
