module Full_Adder( A, B, Cin, Sum, Cout );
    input A, B, Cin;
    output Sum, Cout;
    wire W1, W2, W3;

    xor XOR2X1( .Y(W1), .A(A), .B(B) );
    and AND2X1( .Y(W2), .A(W1), .B(Cin) );
    and AND2X1( .Y(W3), .A(A), .B(B) );
    xor XOR2X1( .Y(Sum), .A(W1), .B(Cin) );
    or  OR2X1( .Y(Cout), .A(W2), .B(W3) );
endmodule
