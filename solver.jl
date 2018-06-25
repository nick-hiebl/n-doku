using Base.Profile;

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

function smart_find_empty(m, n, sudoku, used_row, used_col, used_box)
    besti = m * n + 1;
    bestj = m * n + 1;
    best = m * n + 1;
    remaining = 0;
    for i in 1:m*n, j in 1:m*n
        if sudoku[i, j] == 0
            remaining += 1;
            box = div(i-1, m) * m + div(j-1, n) + 1;
            options = 0;
            for v in 1:m*n
                if used_row[i, v] == 0 && used_col[j, v] == 0 &&
                        used_box[box, v] == 0
                    options += 1;
                end
            end
            if options == 0
                return (0, 0);
            end
            if options < best
                besti = i;
                bestj = j;
                best = options;
            end
        end
    end
    if remaining == 0
        return (m * n + 1, m * n + 1);
    end

    return (besti, bestj)
end

function smart_solve(m, n, sudoku, used_row, used_col, used_box)

    i, j = smart_find_empty(m, n, sudoku, used_row, used_col, used_box);
    if i == 0
        return false;
    end
    if i > m * n
        return true;
    end

    bi = div(i-1, m);
    bj = div(j-1, n) + 1;
    box = bi * m + bj;

    for v in 1:m*n
        if used_row[i, v] == 0 && used_col[j, v] == 0 &&
                used_box[box, v] == 0
            sudoku[i, j] = v;
            used_row[i, v] = 1;
            used_col[j, v] = 1;
            used_box[box, v] = 1;
            if smart_solve(m, n, sudoku, used_row, used_col, used_box)
                return true;
            end
            sudoku[i, j] = 0;
            used_row[i, v] = 0;
            used_col[j, v] = 0;
            used_box[box, v] = 0;
        end
    end

    return false;
end

function smart_solve(m, n, sudoku)
    used_row = zeros(Int64, m*n, m*n);
    used_col = zeros(Int64, m*n, m*n);
    used_box = zeros(Int64, m*n, m*n);

    for i in 1:m*n, j in 1:m*n
        if sudoku[i, j] > 0
            used_row[i, sudoku[i, j]] = 1;
            used_col[j, sudoku[i, j]] = 1;
        end
    end
    for i in 1:n, j in 1:m
        bi = (i-1) * m + 1;
        bj = (j-1) * n + 1;
        box = (i - 1) * m + j;
        for k in bi:bi+m-1, l in bj:bj+n-1
            if sudoku[k, l] > 0
                used_box[box, sudoku[k, l]] = 1;
            end
        end
    end

    if smart_solve(m, n, sudoku, used_row, used_col, used_box)
        return true;
    end
    return false;
end

# Dumbest backtracking solver
# Passes over all neighbours each time to check for a colliding value
function solve(m, n, sudoku)
    i, j = find_empty(m, n, sudoku);

    if i > m * n
        return true;
    end

    for v in 1:m*n

        # Determine if v is a valid option for this cell
        valid = true;
        for k in 1:m*n
            if (k != j && sudoku[i, k] == v) ||
                    (k != i && sudoku[k, j] == v)
                valid = false;
                break;
            end
        end
        # Check if v has been used in this box
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

function try_solve(m, n, sudoku)
    s = copy(sudoku);
    smart_solve(m, n, s);
end

f = open("sudokus/8.sudoku");
m, n = [parse(Int64, s) for s = split(readline(f), " ")];

sudoku_raw = round(Int64, readdlm(f));
sudoku = copy(sudoku_raw);

print_sudoku(m, n, sudoku);

x = smart_solve(m, n, sudoku);
println(x);

print_sudoku(m, n, sudoku);
