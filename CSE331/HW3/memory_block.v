module memory_block(
    output reg [31:0] read_data,
    input byteOperations,
    input [17:0] address,
    input [31:0] write_data,
    input memRead,
    input memWrite
);
    reg [31:0] memory [255:0]; // 256 lines memory, each location 32 bits
	 
	 initial begin
		$readmemb("memory.mem", memory);
	 end
	 
    always @(*) begin
        if(memRead) begin
            if(byteOperations) begin
                read_data <= {24'b0, memory[address][7:0]};
            end else begin
                read_data <= memory[address];
            end
        end
        if(memWrite) begin
            if(byteOperations) begin
                memory[address][7:0] = write_data[7:0];
            end else begin
                memory[address] = write_data;
            end
            $writememb("memory.mem", memory);
        end
    end
endmodule
