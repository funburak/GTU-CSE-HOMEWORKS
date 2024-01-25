module or_32_bit(
	input [31:0] A,
	input [31:0] B,
	output [31:0] Result
);

	or i0(Result[0], A[0], B[0]);
	or i1(Result[1], A[1], B[1]);
	or i2(Result[2], A[2], B[2]);
	or i3(Result[3], A[3], B[3]);
	or i4(Result[4], A[4], B[4]);
	or i5(Result[5], A[5], B[5]);
	or i6(Result[6], A[6], B[6]);
	or i7(Result[7], A[7], B[7]);
	or i8(Result[8], A[8], B[8]);
	or i9(Result[9], A[9], B[9]);
	or i10(Result[10], A[10], B[10]);
	or i11(Result[11], A[11], B[11]);
	or i12(Result[12], A[12], B[12]);
	or i13(Result[13], A[13], B[13]);
	or i14(Result[14], A[14], B[14]);
	or i15(Result[15], A[15], B[15]);
	or i16(Result[16], A[16], B[16]);
	or i17(Result[17], A[17], B[17]);
	or i18(Result[18], A[18], B[18]);
	or i19(Result[19], A[19], B[19]);
	or i20(Result[20], A[20], B[20]);
	or i21(Result[21], A[21], B[21]);
	or i22(Result[22], A[22], B[22]);
	or i23(Result[23], A[23], B[23]);
	or i24(Result[24], A[24], B[24]);
	or i25(Result[25], A[25], B[25]);
	or i26(Result[26], A[26], B[26]);
	or i27(Result[27], A[27], B[27]);
	or i28(Result[28], A[28], B[28]);
	or i29(Result[29], A[29], B[29]);
	or i30(Result[30], A[30], B[30]);
	or i31(Result[31], A[31], B[31]);
	
endmodule
