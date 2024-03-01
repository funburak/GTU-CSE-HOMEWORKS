module zero_bit_32_bit(
	output zero_bit,
	input [31:0] A
);

	or i0(or1,A[0],1'b0);
	or i1(or2,A[1],1'b0);
	or i2(or3,A[2],1'b0);
	or i3(or4,A[3],1'b0);
	or i4(or5,A[4],1'b0);
	or i5(or6,A[5],1'b0);
	or i6(or7,A[6],1'b0);
	or i7(or8,A[7],1'b0);
	or i8(or9,A[8],1'b0);
	or i9(or10,A[9],1'b0);
	or i10(or11,A[10],1'b0);
	or i11(or12,A[11],1'b0);
	or i12(or13,A[12],1'b0);
	or i13(or14,A[13],1'b0);
	or i14(or15,A[14],1'b0);
	or i15(or16,A[15],1'b0);
	or i16(or17,A[16],1'b0);
	or i17(or18,A[17],1'b0);
	or i18(or19,A[18],1'b0);
	or i19(or20,A[19],1'b0);
	or i20(or21,A[20],1'b0);
	or i21(or22,A[21],1'b0);
	or i22(or23,A[22],1'b0);
	or i23(or24,A[23],1'b0);
	or i24(or25,A[24],1'b0);
	or i25(or26,A[25],1'b0);
	or i26(or27,A[26],1'b0);
	or i27(or28,A[27],1'b0);
	or i28(or29,A[28],1'b0);
	or i29(or30,A[29],1'b0);
	or i30(or31,A[30],1'b0);
	or i31(or32,A[31],1'b0);
	


	
	nor i(zero_bit,or1,or2,or3,or4,or5,or6,or7,or8,or9,or10,or11,or12,or13,or14,or15,or16,or17,or18,or19,or20,or21,or22,or23,or24,or25,or26,or27,or28,or29,or30,or31,or32);
	

endmodule
