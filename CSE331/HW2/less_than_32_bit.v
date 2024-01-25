module less_than_32_bit(
	input [31:0] A,
	input [31:0] B,
	output [31:0] Result
);

	wire [31:0] subResult;
	wire carryOut;
	
	sub_32_bit i1(.A(A), .B(B), .carryIn(1'b1), .carryOut(carryOut), .Result(subResult));

	
	or or1(Result[0],1'b0,subResult[31]); // Set the lsb of result to the sign bit of the subResult
	
	and and1(Result[1],1'b0,subResult[31]); // Set the rest of the bits to zero manually
	and and2(Result[2],1'b0,subResult[31]);
	and and3(Result[3],1'b0,subResult[31]);
	and and4(Result[4],1'b0,subResult[31]);
	and and5(Result[5],1'b0,subResult[31]);
	and and6(Result[6],1'b0,subResult[31]);
	and and7(Result[7],1'b0,subResult[31]);
	and and8(Result[8],1'b0,subResult[31]);
	and and9(Result[9],1'b0,subResult[31]);
	and and10(Result[10],1'b0,subResult[31]);
	and and11(Result[11],1'b0,subResult[31]);
	and and12(Result[12],1'b0,subResult[31]);
	and and13(Result[13],1'b0,subResult[31]);
	and and14(Result[14],1'b0,subResult[31]);
	and and15(Result[15],1'b0,subResult[31]);
	and and16(Result[16],1'b0,subResult[31]);
	and and17(Result[17],1'b0,subResult[31]);
	and and18(Result[18],1'b0,subResult[31]);
	and and19(Result[19],1'b0,subResult[31]);
	and and20(Result[20],1'b0,subResult[31]);
	and and21(Result[21],1'b0,subResult[31]);
	and and22(Result[22],1'b0,subResult[31]);
	and and23(Result[23],1'b0,subResult[31]);
	and and24(Result[24],1'b0,subResult[31]);
	and and25(Result[25],1'b0,subResult[31]);
	and and26(Result[26],1'b0,subResult[31]);
	and and27(Result[27],1'b0,subResult[31]);
	and and28(Result[28],1'b0,subResult[31]);
	and and29(Result[29],1'b0,subResult[31]);
	and and30(Result[30],1'b0,subResult[31]);
	and and31(Result[31],1'b0,subResult[31]);
	
	
endmodule
