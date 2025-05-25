#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_SIZE 1024

int sudoku[MAX_SIZE][MAX_SIZE];
int N;
int is_valid = 1;

void validate_rows();
void validate_columns();
void validate_subgrids();

int main(int argc, char *argv[]) {
    FILE *file = fopen("inp.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }
    int K;
    // Read K
    if (fscanf(file, "%d", &K) != 1 || K > MAX_SIZE) {
        fprintf(stderr, "Invalid Sudoku size in file.\n");
        fclose(file);
        return -1;
    }

    // Read N
    if (fscanf(file, "%d", &N) != 1 || N > MAX_SIZE) {
        fprintf(stderr, "Invalid Sudoku size in file.\n");
        fclose(file);
        return -1;
    }

    // Read Sudoku grid
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (fscanf(file, "%d", &sudoku[i][j]) != 1) {
                fprintf(stderr, "Invalid Sudoku grid in file.\n");
                fclose(file);
                return -1;
            }
        }
    }
    fclose(file);

    // Print Sudoku grid
    /*printf("Read %dx%d Sudoku grid successfully:\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", sudoku[i][j]);
        }
        printf("\n");
    }*/

    clock_t start_time = clock();

    // Validate rows, columns, and subgrids sequentially
    validate_rows();
    validate_columns();
    validate_subgrids();

    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1e6; // Convert to microseconds

    // Write result to output file
    FILE *output = fopen("outputseq.txt", "a");
    if (output == NULL) {
        perror("Error opening output file");
        return -1;
    }

    if (is_valid) {
        fprintf(output, "Sudoku is valid.\n");
    } else {
        fprintf(output, "Sudoku is invalid.\n");
    }
    fprintf(output, "The total time taken is %.2f microseconds.\n", time_taken);
    fclose(output);

    return 0;
}

void validate_rows() {
    FILE *output = fopen("outputseq.txt", "w");

    for (int i = 0; i < N; i++) {
        int seen[MAX_SIZE + 1] = {0};
        for (int j = 0; j < N; j++) {
            int value = sudoku[i][j];
            if (value > 0 && value <= N) {
                if (seen[value]) {
                    is_valid = 0;
                    fprintf(output,"Row %d is invalid.\n", i + 1);
                    return;
                }
                seen[value] = 1;
            }
        }
        fprintf(output,"Row %d is valid.\n", i + 1);
    }
    fclose(output);
}

void validate_columns() {
    FILE *output = fopen("outputseq.txt", "a");

    for (int i = 0; i < N; i++) {
        int seen[MAX_SIZE + 1] = {0};
        for (int j = 0; j < N; j++) {
            int value = sudoku[j][i];
            if (value > 0 && value <= N) {
                if (seen[value]) {
                    is_valid = 0;
                    fprintf(output,"Column %d is invalid.\n", i + 1);
                    return;
                }
                seen[value] = 1;
            }
        }
        fprintf(output,"Column %d is valid.\n", i + 1);
    }
    fclose(output);
}

void validate_subgrids() {
    FILE *output = fopen("outputseq.txt", "a");

    int n = (int)sqrt(N); // n=sqrt(N)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int seen[MAX_SIZE + 1] = {0};
            for (int r = 0; r < n; r++) {
                for (int c = 0; c < n; c++) {
                    int value = sudoku[i * n + r][j * n + c];
                    if (value > 0 && value <= N) {
                        if (seen[value]) {
                            is_valid = 0;
                            fprintf(output,"Subgrid (%d,%d) is invalid.\n", i + 1, j + 1);
                            return;
                        }
                        seen[value] = 1;
                    }
                }
            }
            fprintf(output,"Subgrid (%d,%d) is valid.\n", i + 1, j + 1);
        }
    }
    fclose(output);
}
