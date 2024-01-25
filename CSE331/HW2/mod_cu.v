module mod_cu (
	input clk,
	input reset,
	input start,
	input lessThan, 
	output reg writeTemp, 
	output reg writeResult
);

reg [1:0] currState, nextState;

localparam 	START 	= 2'b00,
				SUB		= 2'b01,
				END 		= 2'b10;
				
							
// state register
always @ (posedge clk) begin
	if(reset)
		currState <= START;
	else
		currState <= nextState;
	end
	
//next state
always @ (*) begin
  case(currState)
	START: 	if(start)
					nextState = SUB;
				else
					nextState = START;
	SUB: 		if(lessThan)
					nextState = END;
				else
					nextState = SUB;
	END: 		begin
					nextState = END;
				end
	endcase
end


// output 
always @ (*) begin
	case (currState)
		START: 	begin
					writeTemp = 1'b1;
					writeResult = 1'b0;
					end
		SUB:	   begin
					writeTemp = 1'b0;
					writeResult = 1'b0;
					end
		END: 		begin
					writeTemp = 1'b0;
					writeResult = 1'b1;
					end
	endcase
end

	
endmodule
