#include <stdio.h>
#include <math.h>
/*=========================================================================
  Constants and definitions:
==========================================================================*/

#define N 50
#define M 50
#define RECT 4
#define TOP 0
#define LEFT 1
#define BOTTOM 2
#define RIGHT 3


/* put your #defines and typedefs here*/
void compute_integral_image(int image[][M], int n, int m, int integral_image[][M]);

int sum_rect(int integral_image[][M], int rect[RECT]);

void sliding_average(int integral_image[][M], int n, int m, int h, int w, int average[][M]);

void print_array(int a[N][M], int n, int m);


/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/


int main() {
    int n = 0, m = 0;
    printf("Enter image dimensions:\n");
    scanf("%d%d", &n, &m);

    int image[N][M] = {{0}};
    printf("Enter image:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &image[i][j]);
        }
    }

    int h = 0, w = 0;
    printf("Enter sliding window dimensions:\n");
    scanf("%d%d", &h, &w);

    int integral_image[N][M];
    compute_integral_image(image, n, m, integral_image);
    printf("Integral image is:\n");
    print_array(integral_image, n, m);

    int average[N][M];
    sliding_average(integral_image, n, m, h, w, average);
    printf("Smoothed image is:\n");
    print_array(average, n, m);

    return 0;
}

void print_array(int a[N][M], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%d", a[i][j]);
            if (j != m - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void compute_integral_image(int image[][M], int n, int m, int integral_image[][M]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j == 0) {
                // This is the first column
                if (i == 0) {
                    // This is the first cell of the matrix, needs to take only his value
                    integral_image[i][j] = image[i][j];
                } else {
                    // This is a cell in the first column of the matrix, need to take only his value, and the value
                    // of cells above it (so the previous cell in this column, in the integral_image matrix)
                    integral_image[i][j] = image[i][j] + integral_image[i - 1][j];
                }
            } else if (i == 0) {
                // This is a cell in the first row, need to take only his value, and the value
                // of the cells before it (so the previous cell in this row, in the integral_image matrix)
                integral_image[i][j] = image[i][j] + integral_image[i][j - 1];
            } else {
                // This is a general cell in the matrix, need to take the values of all cells to the left of it,
                // above it, and the cell itself (so the cell, the cell above it in integral matrix, and the cell to it's
                // right in the integral matrix, then, need to remove the cell diagonal to it)
                integral_image[i][j] = image[i][j] + integral_image[i - 1][j] + integral_image[i][j - 1] - integral_image[i - 1][j - 1];
            }
        }
    }
}

int sum_rect(int integral_image[][M], int rect[RECT]) {
    // Calculate the correct value according to the formula
    int sum = 0;
    if (rect[TOP] == 0) {
        if (rect[LEFT] == 0) {
            // Top and left will overflow
            sum = integral_image[rect[BOTTOM]][rect[RIGHT]];
        } else {
            // Top will overflow
            int bottomRight = integral_image[rect[BOTTOM]][rect[RIGHT]];
            int bottomLeft = integral_image[rect[BOTTOM]][rect[LEFT] - 1];
            sum = bottomRight - bottomLeft;
        }
    } else {
        if (rect[LEFT] == 0) {
            // Left will overflow
            int bottomRight = integral_image[rect[BOTTOM]][rect[RIGHT]];
            int topRight = integral_image[rect[TOP] - 1][rect[RIGHT]];
            sum = bottomRight - topRight;
        } else {
            // No overflows, calculate full sum
            int bottomRight = integral_image[rect[BOTTOM]][rect[RIGHT]];
            int bottomLeft = integral_image[rect[BOTTOM]][rect[LEFT] - 1];
            int topRight = integral_image[rect[TOP] - 1][rect[RIGHT]];
            int topLeft = integral_image[rect[TOP] - 1][rect[LEFT] - 1];
            sum = bottomRight - topRight - bottomLeft + topLeft;
        }
    }
    return sum;
}

void sliding_average(int integral_image[][M], int n, int m, int h, int w, int average[][M]) {
    int hDiv = h / 2;
    int wDiv = w / 2;
    int rect[RECT] = {0};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i - hDiv - 1 < 0) {
                // Top will overflow
                rect[TOP] = 0;
            } else {
                rect[TOP] = i - hDiv;
            }
            if (j - wDiv - 1 < 0) {
                // Left will overflow
                rect[LEFT] = 0;
            } else {
                rect[LEFT] = j - wDiv;
            }
            if (i + hDiv >= n) {
                // Bottom will overflow
                rect[BOTTOM] = n - 1;
            } else {
                rect[BOTTOM] = i + hDiv;
            }
            if (j + wDiv >= m) {
                // Right will overflow
                rect[RIGHT] = m - 1;
            } else {
                rect[RIGHT] = j + wDiv;
            }
            double slidingWindowAverage = (double) sum_rect(integral_image, rect) / (h * w);
            int roundedAverage = round(slidingWindowAverage);
            average[i][j] = roundedAverage;
        }
    }
}