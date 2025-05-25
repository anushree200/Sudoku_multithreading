#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_SIZE 1024   // Maximum allowed Sudoku size
#define MAX_BUFFER 100 // Maximum log lines per thread
#define LINE_SIZE 256  // log message size

typedef struct {
    char message[LINE_SIZE];
    double timestamp;
} LogEntry;

int sudoku[MAX_SIZE][MAX_SIZE];
int N, K, K1, K2, K3;
int is_valid = 1;

LogEntry log_buffer[MAX_SIZE * MAX_BUFFER];
int log_index = 0;


// Function to compare log entries by timestamps
int compare_logs(const void *a, const void *b) {
    LogEntry *log1 = (LogEntry *)a;
    LogEntry *log2 = (LogEntry *)b;
    return (log1->timestamp > log2->timestamp) - (log1->timestamp < log2->timestamp);
}

// Validate a row
void validate_row(int row, int thread_id) {
    int seen[MAX_SIZE + 1] = {0};
    for (int i = 0; i < N; i++) {
        if (sudoku[row][i] < 1 || sudoku[row][i] > N || seen[sudoku[row][i]]) {
            is_valid = 0;
        }
        seen[sudoku[row][i]] = 1;
    }
    // Log result
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    double timestamp = ts.tv_sec * 1e6 + ts.tv_nsec / 1e3;

    snprintf(log_buffer[log_index].message, LINE_SIZE,
             "Thread %d checks row %d and is %s.\n", thread_id + 1, row + 1, is_valid ? "valid" : "invalid");
    log_buffer[log_index].timestamp = timestamp;
    log_index++;
}

// Validate a column
void validate_column(int col, int thread_id) {
    int seen[MAX_SIZE + 1] = {0};
    for (int i = 0; i < N; i++) {
        if (sudoku[i][col] < 1 || sudoku[i][col] > N || seen[sudoku[i][col]]) {
            is_valid = 0;
        }
        seen[sudoku[i][col]] = 1;
    }

    // Log result
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    double timestamp = ts.tv_sec * 1e6 + ts.tv_nsec / 1e3;

    snprintf(log_buffer[log_index].message, LINE_SIZE,
             "Thread %d checks column %d and is %s.\n", thread_id + 1, col + 1, is_valid ? "valid" : "invalid");
    log_buffer[log_index].timestamp = timestamp;
    log_index++;
}

void validate_subgrid(int start_row, int start_col, int grid, int thread_id) {
    int seen[MAX_SIZE + 1] = {0};
    int grid_size = sqrt(N);
    for (int i = start_row; i < start_row + grid_size; i++) {
        for (int j = start_col; j < start_col + grid_size; j++) {
            if (sudoku[i][j] < 1 || sudoku[i][j] > N || seen[sudoku[i][j]]) {
                is_valid = 0;
            }
            seen[sudoku[i][j]] = 1;
        }
    }

    // Log result
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    double timestamp = ts.tv_sec * 1e6 + ts.tv_nsec / 1e3;

    snprintf(log_buffer[log_index].message, LINE_SIZE,
             "Thread %d checks grid %d and is %s.\n", thread_id + 1, grid + 1, is_valid ? "valid" : "invalid");
    log_buffer[log_index].timestamp = timestamp;
    log_index++;
}


// runner func for row validation
void *row_runner(void *param) {
    int *params = (int *)param;
    int thread_id = params[0];
    int start_index = params[1];
    int end_index = params[2];
    for (int row = start_index; row <= end_index; row++) {
        validate_row(row, thread_id);
    }
    free(param);
    pthread_exit(0);
}

// runner func for column validation
void *col_runner(void *param) {
    int *params = (int *)param;
    int thread_id = params[0];
    int start_index = params[1];
    int end_index = params[2];
    for (int col = start_index; col <= end_index; col++) {
        validate_column(col, thread_id);
    }
    free(param);
    pthread_exit(0);
}

// runner func for subgrid validation
void *subgrid_runner(void *param) {
    int *params = (int *)param;
    int thread_id = params[0];
    int start_index = params[1];
    int end_index = params[2];
    int grid_size = sqrt(N);
    for (int grid = start_index; grid <= end_index; grid++) {
        int start_row = (grid / grid_size) * grid_size;
        int start_col = (grid % grid_size) * grid_size;
        validate_subgrid(start_row, start_col,grid, thread_id);
    }
    free(param);
    pthread_exit(0);
}


int main(int argc, char *argv[]) {
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_REALTIME, &start_time); // Start timing

    FILE *file = fopen("inp.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    if (fscanf(file, "%d", &K) != 1 || K <= 0) {
        fprintf(stderr, "Invalid number of threads in file.\n");
        fclose(file);
        return -1;
    }

    if (fscanf(file, "%d", &N) != 1 || N > MAX_SIZE) {
        fprintf(stderr, "Invalid Sudoku size in file.\n");
        fclose(file);
        return -1;
    }

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

    // Split K into K1, K2, and K3
    K1 = K / 3;
    K2 = K / 3;
    K3 = K - K1 - K2;

    pthread_t threads[K];
    int thread_idx = 0;
    int rows_per_thread = N / K1;
    for (int i = 0; i < K1; i++) {
        int *params = malloc(3 * sizeof(int));
        params[0] = thread_idx;
        params[1] = i * rows_per_thread;
        params[2] = (i + 1) * rows_per_thread - 1;
        pthread_create(&threads[thread_idx++], NULL, row_runner, params);
    }

    int cols_per_thread = N / K2;
    for (int i = 0; i < K2; i++) {
        int *params = malloc(3 * sizeof(int));
        params[0] = thread_idx;
        params[1] = i * cols_per_thread;
        params[2] = (i + 1) * cols_per_thread - 1;
        pthread_create(&threads[thread_idx++], NULL, col_runner, params);
    }

    int grid_size = sqrt(N);
    int grids_per_thread = (N / grid_size) * (N / grid_size) / K3;
    for (int i = 0; i < K3; i++) {
        int *params = malloc(3 * sizeof(int));
        params[0] = thread_idx;
        params[1] = i * grids_per_thread;
        params[2] = (i + 1) * grids_per_thread - 1;
        pthread_create(&threads[thread_idx++], NULL, subgrid_runner, params);
    }


    // Join all threads
    for (int i = 0; i < thread_idx; i++) {
        pthread_join(threads[i], NULL);
    }

    // Sort the log buffer based on timestamps
    qsort(log_buffer, log_index, sizeof(LogEntry), compare_logs);

    // Print logs to console and write to output file
    FILE *output_file = fopen("outputchunk.txt", "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        return -1;
    }

    for (int i = 0; i < log_index; i++) {
        //printf("%s", log_buffer[i].message);
        fprintf(output_file, "%s", log_buffer[i].message);
    }



    clock_gettime(CLOCK_REALTIME, &end_time); // End timing
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1e6 + (end_time.tv_nsec - start_time.tv_nsec) / 1e3;

    fprintf(output_file,"Sudoku is %s.\n", is_valid ? "valid" : "invalid");
    fprintf(output_file,"The total time taken is %.2f microseconds.\n", elapsed_time);


    fclose(output_file);

    return 0;
}
