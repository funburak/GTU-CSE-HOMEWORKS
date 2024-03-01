module full_adder(
	output sum, 
	output cout, 
	input a, 
	input b, 
	input cin
); 

    wire aXORb, and1, and2;

    xor(aXORb, a, b);
    xor(sum, aXORb, cin);

    and(and1, aXORb, cin);
    and(and2, a, b);
    or(cout, and1, and2);

endmodule
