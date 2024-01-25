module xor_32_bit(
	input [31:0] A,
	input [31:0] B,
	output [31:0] Result
);

	xor i0(Result[0], A[0], B[0]);
	xor i1(Result[1], A[1], B[1]);
	xor i2(Result[2], A[2], B[2]);
	xor i3(Result[3], A[3], B[3]);
	xor i4(Result[4], A[4], B[4]);
	xor i5(Result[5], A[5], B[5]);
	xor i6(Result[6], A[6], B[6]);
	xor i7(Result[7], A[7], B[7]);
	xor i8(Result[8], A[8], B[8]);
	xor i9(Result[9], A[9], B[9]);
	xor i10(Result[10], A[10], B[10]);
	xor i11(Result[11], A[11], B[11]);
	xor i12(Result[12], A[12], B[12]);
	xor i13(Result[13], A[13], B[13]);
	xor i14(Result[14], A[14], B[14]);
	xor i15(Result[15], A[15], B[15]);
	xor i16(Result[16], A[16], B[16]);
	xor i17(Result[17], A[17], B[17]);
	xor i18(Result[18], A[18], B[18]);
	xor i19(Result[19], A[19], B[19]);
	xor i20(Result[20], A[20], B[20]);
	xor i21(Result[21], A[21], B[21]);
	xor i22(Result[22], A[22], B[22]);
	xor i23(Result[23], A[23], B[23]);
	xor i24(Result[24], A[24], B[24]);
	xor i25(Result[25], A[25], B[25]);
	xor i26(Result[26], A[26], B[26]);
	xor i27(Result[27], A[27], B[27]);
	xor i28(Result[28], A[28], B[28]);
	xor i29(Result[29], A[29], B[29]);
	xor i30(Result[30], A[30], B[30]);
	xor i31(Result[31], A[31], B[31]);

endmodule
