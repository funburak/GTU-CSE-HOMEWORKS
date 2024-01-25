module nor_32_bit(
	input [31:0] A,
	input [31:0] B,
	output [31:0] Result
);

	nor i0(Result[0], A[0], B[0]);
	nor i1(Result[1], A[1], B[1]);
	nor i2(Result[2], A[2], B[2]);
	nor i3(Result[3], A[3], B[3]);
	nor i4(Result[4], A[4], B[4]);
	nor i5(Result[5], A[5], B[5]);
	nor i6(Result[6], A[6], B[6]);
	nor i7(Result[7], A[7], B[7]);
	nor i8(Result[8], A[8], B[8]);
	nor i9(Result[9], A[9], B[9]);
	nor i10(Result[10], A[10], B[10]);
	nor i11(Result[11], A[11], B[11]);
	nor i12(Result[12], A[12], B[12]);
	nor i13(Result[13], A[13], B[13]);
	nor i14(Result[14], A[14], B[14]);
	nor i15(Result[15], A[15], B[15]);
	nor i16(Result[16], A[16], B[16]);
	nor i17(Result[17], A[17], B[17]);
	nor i18(Result[18], A[18], B[18]);
	nor i19(Result[19], A[19], B[19]);
	nor i20(Result[20], A[20], B[20]);
	nor i21(Result[21], A[21], B[21]);
	nor i22(Result[22], A[22], B[22]);
	nor i23(Result[23], A[23], B[23]);
	nor i24(Result[24], A[24], B[24]);
	nor i25(Result[25], A[25], B[25]);
	nor i26(Result[26], A[26], B[26]);
	nor i27(Result[27], A[27], B[27]);
	nor i28(Result[28], A[28], B[28]);
	nor i29(Result[29], A[29], B[29]);
	nor i30(Result[30], A[30], B[30]);
	nor i31(Result[31], A[31], B[31]);

endmodule
