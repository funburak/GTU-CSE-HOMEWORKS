module mod_dp (
	input clk, 
	input [31:0] A, 
	input [31:0] B, 
	input writeTemp, 
	input writeResult,
	output reg lessThan, 
	output reg [31:0] Result
);
	reg [31:0] temp;
	wire [31:0] tempResult;
	wire carryOut;
	
	sub_32_bit i0(.A(temp), .B(B), .carryIn(1'b1), .carryOut(carryOut), .Result(tempResult));
	
	always @ (posedge clk) begin
		if(writeTemp)
			temp <= A;
		else if(temp >= B) begin
			lessThan = 1'b0;
			temp <= tempResult;
			end
		else
			lessThan = 1'b1;
			if(writeResult)
				Result <= temp;
	end

endmodule
