module parallel_sum;
    parameter N = 8;
    reg [7:0] data [0:N-1];
    integer result;
    integer i;

    task automatic tree_sum(
        input  integer left, 
        input  integer right, 
        output integer sum
    );
        integer mid;
        integer sum_left, sum_right;
        begin
            if (left == right) begin
                sum = data[left];
            end else begin
                mid = (left + right) / 2;
                fork
                    tree_sum(left, mid, sum_left);
                    tree_sum(mid + 1, right, sum_right);
                join
                sum = sum_left + sum_right;
            end
        end
    endtask

    initial begin
        for (i = 0; i < N; i = i + 1)
            data[i] = i + 1;

        tree_sum(0, N-1, result);

        $display(result);
        $finish;
    end
endmodule
