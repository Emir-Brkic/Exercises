#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int **moltiply_mx(int **mx1, int **mx2, size_t len_rows1,size_t len_columns1,size_t len_rows2,size_t len_columns2);

int **init_mx(size_t len_rows, size_t len_columns);
void fill_mx(int **mx, size_t len_rows, size_t len_columns);
void print_mx(int **mx, size_t len_rows, size_t len_columns);


int main() {

    srand(time(NULL));
    //========================= 
    int **mx1;
    size_t len_rows1 = 1000;
    size_t len_columns1 = 1000;

    mx1 = init_mx(len_rows1, len_columns1);

    fill_mx(mx1, len_rows1, len_columns1);
    //print_mx(mx1, len_rows1, len_columns1);
    printf("\n");

    int **mx2;
    size_t len_rows2 = 1000;
    size_t len_columns2 = 1000;

    mx2 = init_mx(len_rows2, len_columns2);

    fill_mx(mx2, len_rows2, len_columns2);
    //print_mx(mx2, len_rows2, len_columns2);
    printf("\n");


    int **res_mx;
    size_t len_res_rows = len_rows1;
    size_t len_res_columns = len_columns2;

    res_mx = moltiply_mx(mx1,mx2,len_rows1,len_columns1,len_rows2,len_columns2);

    //print_mx(res_mx, len_res_rows, len_res_columns);

    free(mx1);
    free(mx2);
    free(res_mx);
    return 0;
}

int **moltiply_mx(int **mx1, int **mx2, size_t len_rows1,size_t len_columns1,size_t len_rows2,size_t len_columns2) {
    if(len_rows1 != len_columns2){
        printf("The dimension of the two matrix does not allow multiplications\n");
        return NULL;
    }

    int **res_mx;
    size_t len_res_rows = len_rows1;
    size_t len_res_columns = len_columns2;

    res_mx = calloc(len_res_rows,sizeof(int *));
    if(res_mx == NULL) {
            printf("Memory allocation failed\n");
    }

    for(int i = 0; i < len_res_rows; i ++) {
        res_mx[i] = calloc(len_res_columns,sizeof(int *));
        if(res_mx[i] == NULL) {
            printf("Memory allocation failed\n");
        }
    }

    for(int n_row = 0; n_row < len_res_rows; n_row ++) {
        for(int n_columns = 0; n_columns < len_res_columns; n_columns ++) {

            for(int n = 0; n < len_res_rows; n ++) {
                res_mx[n_row][n_columns] += mx1[n_row][n] * mx2[n][n_columns];
            }

        }
    }


    return res_mx;
}

int **init_mx(size_t len_rows, size_t len_columns) {
    int **mx;
    mx = calloc(len_columns,sizeof(int *));
    if(mx == NULL) {
            printf("Memory allocation failed\n");
    }

    for(int i = 0; i < len_columns; i ++) {
        mx[i] = calloc(len_rows,sizeof(int));
        if(mx[i] == NULL) {
            printf("Memory allocation failed\n");
        }
    }

    return mx;
}

void fill_mx(int **mx, size_t len_rows, size_t len_columns) {
    for(int n_row = 0; n_row < len_rows; n_row ++) {
        for(int n_columns = 0; n_columns < len_columns; n_columns ++) {
            mx[n_row][n_columns] = rand() % 10;
        }
    }
}

void print_mx(int **mx, size_t len_rows, size_t len_columns) {
    for(int n_row = 0; n_row < len_rows; n_row ++) {
        for(int n_columns = 0; n_columns < len_columns; n_columns ++) {
            printf("[%3d]",mx[n_row][n_columns]);
        }
        printf("\n");
    }
}