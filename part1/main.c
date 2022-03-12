#include <stdint.h>
#include <stdio.h>

int main() {
    uint32_t array1[2][3];

    printf("Printed out is the row, column, the memory address, and the distance in bytes from where array1[0][0] is located in memory.\n");
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 3; j++) {
            printf("Row: %d, Col: %d, Mem: %p, Dist: %td\n", i, j, &array1[i][j], (&array1[i][j] - &array1[0][0]) * sizeof(array1[0][0]));
        }
    }
    printf("It looks like the 2D array is 2 3-long 1d arrays laid out directly next to each other.\n");
    printf("Even when the row changes, the distance still increases by 4 bytes.\n");

    uint32_t array2[2][3][4];

    printf("Printed out is the x, y, z, the memory address, and the distance in bytes from where array2[0][0][0] is located in memory.\n");
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 3; j++) {
            for(int k = 0; k < 4; k++) {
                printf("x: %d, y: %d, z: %d, Mem: %p, Dist: %td\n", i, j, k, &array2[i][j][k], (&array2[i][j][k] - &array2[0][0][0]) * sizeof(array2[0][0][0]));
            }
        }
    }
    printf("The 3d array looks like it is 2 3 by 4 2D arrays laid out directly next to each other.\n");

    return 1;
}