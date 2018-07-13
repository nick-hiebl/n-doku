/*
 * A similar to solver.c, however it uses a stored table to lookup
 * whether certain values have already been used.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE !FALSE

typedef struct {
    int **used_row;
    int **used_col;
    int **used_box;
} table;

int **reader(int *m, int *n);
void free_sudoku(int **sudoku);
void print_sudoku(int m, int n, int **sudoku);

int solve(int m, int n, int **sudoku);

int main() {
    int m, n;
    int **sudoku = reader(&m, &n);

    print_sudoku(m, n, sudoku);

    solve(m, n, sudoku);

    print_sudoku(m, n, sudoku);

    free_sudoku(sudoku);
}

int **reader(int *m_addr, int *n_addr) {
    int m, n;
    scanf("%d %d", &m, &n);

    int **sudoku = malloc(sizeof(int*) * m * n);

    int *grid = malloc(sizeof(int) * m * n * m * n);

    int i;
    for (i = 0; i < m * n; i++) {
        sudoku[i] = &(grid[i * m * n]);
    }

    for (i = 0; i < m * n * m * n; i++) {
        scanf("%d", &(grid[i]));
    }

    *m_addr = m;
    *n_addr = n;

    return sudoku;
}

int **make_matrix(int dimension) {
    int **matrix = malloc(sizeof(int*) * dimension);
    int *grid = malloc(sizeof(int*) * dimension * dimension);

    int i;
    for (i = 0; i < dimension; i++) {
        matrix[i] = &(grid[i * dimension]);
    }
    memset(grid, 0, dimension * dimension * sizeof(int));

    return matrix;
}

table make_lookup_tables(int m, int n, int **sudoku) {
    table t;
    t.used_row = make_matrix(m * n);
    t.used_col = make_matrix(m * n);
    t.used_box = make_matrix(m * n);

    int i, j;
    for (i = 0; i < m * n; i++) {
        for (j = 0; j < m * n; j++) {
            int v = sudoku[i][j];
            if (v > 0) {
                t.used_row[i][v] = 1;
                t.used_col[j][v] = 1;
                int b = (i/m) * n + (j/n);
                t.used_box[b][v] = 1;
            }
        }
    }
    return t;
}

void free_sudoku(int **sudoku) {
    free(sudoku[0]);
    free(sudoku);
}

void print_sudoku(int m, int n, int **sudoku) {
    printf("%d %d\n", m, n);
    int i, j;
    for (i = 0; i < m * n; i++) {
        for (j = 0; j < m * n - 1; j++) {
            printf("%d ", sudoku[i][j]);
        }
        printf("%d\n", sudoku[i][j]);
    }
}

int solve(int m, int n, int **sudoku) {
    int i = 0, j = 0;
    while (i < m * n) {
        if (sudoku[i][j] == 0) break;
        j++;
        if (j == m * n) {
            j = 0;
            i++;
        }
    }
    if (i >= m * n) {
        return TRUE;
    }

    int v;
    for (v = 1; v <= m * n; v++) {
        int k, valid = TRUE;
        for (k = 0; k < m * n; k++) {
            // Scan rows and columns for collisions
            if ((sudoku[i][k] == v && k != j) ||
                    (sudoku[k][j] == v && i != k)) {
                valid = FALSE;
                break;
            }
        }
        if (valid) {
            // Scan box for collisions
            int bx = (i/m) * m, by = (j/n) * n;
            int l;
            for (k = 0; valid && k < m; k++) {
                if (bx + k == i) continue;
                for (l = 0; l < n; l++) {
                    if (by + l == j) continue;
                    if (sudoku[bx + k][by + l] == v) {
                        valid = FALSE;
                        break;
                    }
                }
            }
        }
        if (valid) {
            sudoku[i][j] = v;
            if (solve(m, n, sudoku)) {
                return TRUE;
            }
        }
    }
    // Give up and return
    sudoku[i][j] = 0;
    return FALSE;
}
