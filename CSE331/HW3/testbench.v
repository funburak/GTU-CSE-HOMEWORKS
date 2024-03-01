module testbench();

	 reg clock;
	 
    // Instantiate the MIPS module
    mips uut(
        .clock(clock)
    );

    // Clock generation
    always begin
        #100 clock = ~clock;
    end

    // Initial values
    initial begin
        clock =0;
    end

    initial begin
	 
    end
endmodule
