module cla_4_bit(
	input [3:0] A,
	input [3:0] B,
	input carryIn,
	output G,
	output P,
	output [3:0] Result
);

	wire [3:0] g;
	wire [3:0] p;
	wire C1,C2,C3;
	wire X,X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11;
		
	// g0 = a0b0
	// p0 = a0 + b0
	and and1(g[0], A[0], B[0]);
	or or1(p[0], A[0], B[0]);
	
	// c1 = g0 + p0c0
	and i0(X0, p[0], carryIn);
	or i1(C1, g[0], X0);
	
	xor xor1(Result[0], A[0], B[0], carryIn);
	
	// g1 = a1b1
	// p1 = a1 + b1
	and and2(g[1], A[1], B[1]);
	or or2(p[1], A[1], B[1]);
	
	// c2 = g1 + p1g0 + p1p0c0
	and i2(X, p[1], p[0], carryIn);
	and i3(X1, p[1], g[0]);
	or i4(C2, g[1], X1, X);
	
	xor xor2(Result[1], A[1], B[1], C1);
	
	// g2 = a2b2
	// p2 = a2 + b2
	and and3(g[2], A[2], B[2]);
	or or3(p[2], A[2], B[2]);
	
	// c3 = g2 + p2g1 + p2p1g0 + p2p1p0c0
	and i5(X2, p[2], p[1], p[0], carryIn);
	and i6(X3, p[2], p[1], g[0]);
	and i7(X4, p[2], g[1]);
	or i8(C3, g[2], X4, X3, X2);
	
	xor xor3(Result[2], A[2], B[2], C2);
	
	// g3 = a3b3
	// p3 = a3 + b3
	and and4(g[3], A[3], B[3]);
	or or4(p[3], A[3], B[3]);
	
	xor xor4(Result[3], A[3], B[3], C3);
	
	// G3:0 = g3 + p3g2 + p3p2g1 + p3p2p1g0
	and and5(X9, p[3], p[2], p[1], g[0]);
	and and6(X10, p[3], p[2], g[1]);
	and and7(X11, p[3], g[2]);
	or or5(G, g[3], X11, X10, X9);
	
	// P3:0 = p3p2p1p0
	and and8(P, p[3], p[2], p[1], p[0]);

endmodule
