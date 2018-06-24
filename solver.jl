
function print_sudoku(m, n, sudoku)
    println(m, " ", n);
    println(sudoku);
end

function find_empty(m, n, sudoku)
    for i in 1:m*n, j in 1:m*n
        if sudoku[i, j] == 0
            return (i, j);
        end
    end
    return (m * n + 1, m * n + 1);
end

function solve(m, n, sudoku)
    i, j = find_empty(m, n, sudoku);

    if i > m * n
        return true;
    end

    for v in 1:m*n

        # Determine if v is a valid option for this cell
        valid = true;
        for k in 1:m*n
            if (k != j && sudoku[i, k] == v) || (k != i && sudoku[k, j] == v)
                valid = false;
                break;
            end
        end
        # Check if we ca
        if valid
            bi = div(i-1, m) * m + 1;
            bj = div(j-1, n) * n + 1;
            for k in bi:bi+m-1, l in bj:bj+n-1
                if sudoku[k, l] == v
                    valid = false;
                    break;
                end
            end
        end

        if valid
            sudoku[i, j] = v
            if (solve(m, n, sudoku))
                return true;
            end
        end

    end

    sudoku[i, j] = 0;
    return false;
end

m, n = [parse(Int64, s) for s = split(readline(STDIN), " ")];

sudoku = round(Int64, readdlm(STDIN));

print_sudoku(m, n, sudoku);

solve(m, n, sudoku);

print_sudoku(m, n, sudoku);
