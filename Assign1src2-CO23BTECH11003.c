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

volatile int flag[MAX_SIZE] = {0}; // Flag array for thread synchronization

int sudoku[MAX_SIZE][MAX_SIZE];
int N, K;
int K1, K2, K3;
int is_valid = 1;

LogEntry log_buffer[MAX_SIZE * MAX_BUFFER];
int log_index = 0;

void *runner(void *param);

// Function to compare log entries by timestamps
int compare_logs(const void *a, const void *b) {
    LogEntry *log1 = (LogEntry *)a;
    LogEntry *log2 = (LogEntry *)b;
    return (log1->timestamp > log2->timestamp) - (log1->timestamp < log2->timestamp);
}

// Function to validate subgrid
void validate_subgrid(int start_row, int start_col, int task, LogEntry *local_logs, int *local_log_index) {
    int seen[MAX_SIZE + 1];
    memset(seen, 0, sizeof(seen));

    // Validate the subgrid
    for (int i = start_row; i < start_row + sqrt(N); i++) {
        for (int j = start_col; j < start_col + sqrt(N); j++) {
            if (sudoku[i][j] < 1 || sudoku[i][j] > N || seen[sudoku[i][j]]) {
                is_valid = 0;
            }
            seen[sudoku[i][j]] = 1;
        }
    }
	//adding time stamps to buffer
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    double timestamp = ts.tv_sec * 1e6 + ts.tv_nsec / 1e3;

    snprintf(local_logs[*local_log_index].message, LINE_SIZE,
             "Thread %d checks grid %d and is %s.\n", task + 1,
             (start_row / (int)sqrt(N)) * (int)sqrt(N) + (start_col / (int)sqrt(N)) + 1,
             is_valid ? "valid" : "invalid");
    local_logs[*local_log_index].timestamp = timestamp;
    (*local_log_index)++;
}

int main(int argc, char *argv[]) {
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

    // Distribute threads among row, column, and subgrid validation
    K1 = K / 3;
    K2 = K / 3;
    K3 = K - K1 - K2;

    /*printf("Read %dx%d Sudoku grid successfully:\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", sudoku[i][j]);
        }
        printf("\n");
    }*/

    clock_t start_time = clock();

    // Create threads
    pthread_t threads[K];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    for (int i = 0; i < K; i++) {
        int *data = malloc(sizeof(int));
        *data = i;
        pthread_create(&threads[i], &attr, runner, data);
    }

    // Join all threads
    for (int i = 0; i < K; i++) {
        pthread_join(threads[i], NULL);
    }

    // Sort buffer by timestamps
    qsort(log_buffer, log_index, sizeof(LogEntry), compare_logs);

    // write to output file
    FILE *output = fopen("outputmixed.txt", "w");
    if (output == NULL) {
        perror("Error opening output file");
        return -1;
    }

    for (int i = 0; i < log_index; i++) {
        fprintf(output, "%s", log_buffer[i].message);
    }

    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1e6; // Convert to microseconds

    fprintf(output, "Sudoku is %s.\n", is_valid ? "valid" : "invalid");
    fprintf(output, "The total time taken is %.2f microseconds.\n", time_taken);
    fclose(output);

    return 0;
}


void *runner(void *param) {
    int task = *((int *)param);
    free(param);

    int seen[MAX_SIZE + 1];
    LogEntry local_logs[MAX_BUFFER];
    int local_log_index = 0;

    if (task > 0) {
        while (flag[task - 1] == 0);
    }

    // Validate rows assigned cyclically to this thread
    if (task < K1) {
        for (int i = task; i < N; i += K1) {
            memset(seen, 0, sizeof(seen));
            for (int j = 0; j < N; j++) {
                if (sudoku[i][j] < 1 || sudoku[i][j] > N || seen[sudoku[i][j]]) {
                    is_valid = 0;
                }
                seen[sudoku[i][j]] = 1;
            }

            //adding time stamps to buffer
            struct timespec ts;
            clock_gettime(CLOCK_REALTIME, &ts);
            double timestamp = ts.tv_sec * 1e6 + ts.tv_nsec / 1e3;

            snprintf(local_logs[local_log_index].message, LINE_SIZE,
                     "Thread %d checks row %d and is %s.\n", task + 1, i + 1,
                     is_valid ? "valid" : "invalid");
            local_logs[local_log_index].timestamp = timestamp;
            local_log_index++;
        }
    }

    // Validate columns assigned cyclically to this thread
    if (task >= K1 && task < K1 + K2) {
        int col_task = task - K1;
        for (int i = col_task; i < N; i += K2) {
            memset(seen, 0, sizeof(seen));
            for (int j = 0; j < N; j++) {
                if (sudoku[j][i] < 1 || sudoku[j][i] > N || seen[sudoku[j][i]]) {
                    is_valid = 0;
                }
                seen[sudoku[j][i]] = 1;
            }

            //adding time stamps to buffer
            struct timespec ts;
            clock_gettime(CLOCK_REALTIME, &ts);
            double timestamp = ts.tv_sec * 1e6 + ts.tv_nsec / 1e3;

            snprintf(local_logs[local_log_index].message, LINE_SIZE,
                     "Thread %d checks column %d and is %s.\n", task + 1, i + 1,
                     is_valid ? "valid" : "invalid");
            local_logs[local_log_index].timestamp = timestamp;
            local_log_index++;
        }
    }

    // Validate subgrids assigned cyclically to this thread
    if (task >= K1 + K2) {
        int subgrid_task = task - K1 - K2;
        int grid_size = sqrt(N);
        for (int i = subgrid_task; i < N; i += K3) {
            int start_row = (i / grid_size) * grid_size;
            int start_col = (i % grid_size) * grid_size;

            validate_subgrid(start_row, start_col, task, local_logs, &local_log_index);
        }
    }

    // Copy local logs to the global buffer
    for (int i = 0; i < local_log_index; i++) {
        log_buffer[log_index++] = local_logs[i];
    }

    // Set the flag to indicate this thread's completion
    flag[task] = 1;

    pthread_exit(0);
}
