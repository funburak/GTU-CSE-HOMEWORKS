module mod(
	input [31:0] A,
	input [31:0] B,
	input clk,
	input start,
	input reset,
	output [31:0] Result
);

	wire isLessThan, writeTemp, writeResult;
	
	mod_cu io(.start(start), .reset(reset), .clk(clk), .lessThan(isLessThan), .writeTemp(writeTemp), .writeResult(writeResult));
	mod_dp i1(.clk(clk), .A(A), .B(B), .writeTemp(writeTemp), .writeResult(writeResult), .lessThan(isLessThan), .Result(Result));



endmodule
