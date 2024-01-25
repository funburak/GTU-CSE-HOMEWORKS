module tb();
  reg [31:0] A;
  reg [31:0] B;
  reg [2:0] ALUop;
  reg carryIn;
  reg clk;
  reg start;
  reg reset;

  wire carryOutAdd;
  wire carryOutSub;
  wire [31:0] Result;

  alu i0(.A(A), .B(B), .clk(clk), .start(start), .reset(reset), .ALUop(ALUop), .carryIn(carryIn), .carryOutAdd(carryOutAdd), .carryOutSub(carryOutSub), .Result(Result));

  initial begin
    #5 reset = 1'b1;
    start = 1'b0;
	 clk = 1'b0;
    A = -5;
    B = -4;
    ALUop = 3'b000;
    #5 $display("A=%b, B=%b, Result=%b  AND", A, B, Result); // AND

    #5 ALUop = 3'b001;
    #5 $display("A=%b, B=%b, Result=%b  OR", A, B, Result); // OR

    #5 ALUop = 3'b010;
    #5 $display("A=%b, B=%b, Result=%b  XOR", A, B, Result); // XOR

    #5 ALUop = 3'b011;
    #5 $display("A=%b, B=%b, Result=%b  NOR", A, B, Result); // NOR

    #5 ALUop = 3'b100;
    carryIn = 1'b1;
    #5 $display("A=%b, B=%b, Result=%b  LESS THAN", A, B, Result); // LESS THAN

    #5 ALUop = 3'b101;
    carryIn = 1'b0;
    #5 $display("A=%b, B=%b, Result=%b, CarryOut=%b  ADD", A, B, Result, carryOutAdd); // ADD

    #5 ALUop = 3'b110;
    carryIn = 1'b1;
    #5 $display("A=%b, B=%b, Result=%b, CarryOut=%b  SUB", A, B, Result, carryOutSub); // SUB

    #5 A = 23;
    B = 7;
    ALUop = 3'b111;
    #1000 $display("A=%b, B=%b, Result=%b  MOD", A, B, Result); // MOD   In case of very high values entered, since the number of cycle will be high I displayed the result a bit later.
  end

  always #5 clk = ~clk;

  always #80 reset = 1'b0; // Set reset to 0 after some time so that the first state is set to START.

  always #100 start = 1'b1; // Set start to 1 after some time so that the next state is set to SUB.
endmodule
