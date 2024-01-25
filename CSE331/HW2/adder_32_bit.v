module adder_32_bit(
	input [31:0] A,
	input [31:0] B,
	input carryIn,
	output carryOut,
	output [31:0] Result
);

	wire [7:0] G;
	wire [7:0] P;
	wire [6:0] Carry;
	
	wire X1,X2,X3,X4,X5,X6,X7,X8;
	
	cla_4_bit i0(.A(A[3:0]), .B(B[3:0]), .carryIn(carryIn), .G(G[0]), .P(P[0]), .Result(Result[3:0]));
	// c4 = g3:0 + p3:0c0
	and and1(X1, P[0], carryIn);
	or or1(Carry[0], G[0], X1);
	
	cla_4_bit i1(.A(A[7:4]), .B(B[7:4]), .carryIn(Carry[0]), .G(G[1]), .P(P[1]), .Result(Result[7:4]));
	// c8 = g7:4 + p7:4c4);
	and and2(X2, P[1], Carry[0]);
	or or2(Carry[1], G[1], X2);
	
	cla_4_bit i2(.A(A[11:8]), .B(B[11:8]), .carryIn(Carry[1]), .G(G[2]), .P(P[2]), .Result(Result[11:8]));
	// c12 = g11:8 + p11:8c8
	and and3(X3, P[2], Carry[1]);
	or or3(Carry[2], G[2], X3);
	
	cla_4_bit i3(.A(A[15:12]), .B(B[15:12]), .carryIn(Carry[2]), .G(G[3]), .P(P[3]), .Result(Result[15:12]));
	// c16 = g15:12 + p15:12c12
	and and4(X4, P[3], Carry[2]);
	or or4(Carry[3], G[3], X4);
	
	cla_4_bit i4(.A(A[19:16]), .B(B[19:16]), .carryIn(Carry[3]), .G(G[4]), .P(P[4]), .Result(Result[19:16]));
	// c20 = g19:16 + p19:16c16
	and and5(X5, P[4], Carry[3]);
	or or5(Carry[4], G[4], X5);
	
	cla_4_bit i5(.A(A[23:20]), .B(B[23:20]), .carryIn(Carry[4]), .G(G[5]), .P(P[5]), .Result(Result[23:20]));
	// c24 = g23:20 + p23:20c20
	and and6(X6, P[5], Carry[4]);
	or or6(Carry[5], G[5], X6);
	
	cla_4_bit i6(.A(A[27:24]), .B(B[27:24]), .carryIn(Carry[5]), .G(G[6]), .P(P[6]), .Result(Result[27:24]));
	// c28 = g27:24 + p27:24c24
	and and7(X7, P[6], Carry[5]);
	or or7(Carry[6], G[6], X7);
	
	cla_4_bit i7(.A(A[31:28]), .B(B[31:28]), .carryIn(Carry[6]), .G(G[7]), .P(P[7]), .Result(Result[31:28]));
	// c32 = g31:28 + p31:28c28
	and and8(X8, P[7], Carry[6]);
	or or8(carryOut, G[7], X8);

endmodule
