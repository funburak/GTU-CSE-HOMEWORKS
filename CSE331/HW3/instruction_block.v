module instruction_block(
    output reg [31:0] instruction,
    input [31:0] pc
);
    reg [31:0] instruction_memory [31:0];

    // Initialize the instruction memory from a file
    initial begin
        $readmemb("instructions.mem", instruction_memory);
    end

    // Fetch instruction based on the program counter
    always @(pc[11:2]) begin
        instruction <= instruction_memory[pc[11:2]]; // Indexing with bits [11:2] of PC for word alignment
    end
endmodule
