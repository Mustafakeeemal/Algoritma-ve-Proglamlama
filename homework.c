// ****07.04.2025 son tarihli ödev****


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS_A 2
#define COLS_A 3
#define ROWS_B 3
#define COLS_B 2

void randomValueGeneration(int rows, int cols, int matrix[rows][cols]); //RASTGELE MATRİS ELEMANİ
void printMatrix(int rows, int cols, int matrix[rows][cols]); //MATRİSLERİ EKRANA YAZDIRMA
void multiplyMatrix(int arr1[ROWS_A][COLS_A], int arr2[ROWS_B][COLS_B], int result[ROWS_A][COLS_B]); //MATRİS CARPIMI
void transposeMatrix(int rows, int cols, int matrix[rows][cols], int transposed[cols][rows]); //MATRİSLERİN TRANSPOZUNU ALMA

int main() {
    srand(time(NULL));  //cekirdek sifirlama

    int A[ROWS_A][COLS_A]; // A matrisi (2x3)
    int B[ROWS_B][COLS_B]; // B matrisi (3x2)
    int result[ROWS_A][COLS_B];  // (2x2) sonuc matrisi
    int transposedA[COLS_A][ROWS_A]; // A matrisinin transpozu
    int transposedB[ROWS_B][COLS_B];  // B matrisinin transpozu

    // A ve B matrislerini rastgele değerlerle doldurma
    randomValueGeneration(ROWS_A, COLS_A, A);
    randomValueGeneration(ROWS_B, COLS_B, B);

    // Matrisleri ekrana yazdırma
    printf("Matrix A (2x3):\n");
    printMatrix(ROWS_A, COLS_A, A);

    printf("\nMatrix B (3x2):\n");
    printMatrix(ROWS_B, COLS_B, B);

    // Matrislerin çarpımını hesaplama

    multiplyMatrix(A, B, result);

    // Sonuç matrisini yazdırma
    printf("\nResult Matrix (result of A multiply B):\n");
    printMatrix(ROWS_A, COLS_B, result);

    // A ve B matrislerinin transpozunu hesaplama
    transposeMatrix(ROWS_A, COLS_A, A, transposedA);
    transposeMatrix(ROWS_B, COLS_B, B, transposedB);

    // Transpoze matrisleri yazdır
    printf("\nTransposed Matrix A (3x2):\n");
    printMatrix(COLS_A, ROWS_A, transposedA);

    printf("\nTransposed Matrix B (2x3):\n");
    printMatrix(COLS_B, ROWS_B, transposedB);

    return 0;
}

//Matrise rastgele eleman ekleme
void randomValueGeneration(int rows, int cols, int matrix[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() %10 +1;
        }
    }
}

// Matrisi ekrana yazdirma
void printMatrix(int rows, int cols, int matrix[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}
// Matris çarpımı yapma fonksiyonu
void multiplyMatrix(int arr1[ROWS_A][COLS_A], int arr2[ROWS_B][COLS_B], int result[ROWS_A][COLS_B]) {
    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            result[i][j] = 0; // Sonuç matrisini sıfırla
            for (int k = 0; k < COLS_A; k++) { // COLS_A, arr1'in satir sayısı ve arr2'nin sütun sayısı
                result[i][j] += arr1[i][k] * arr2[k][j];
            }
        }
    }
}
// Matrisin transpozunu hesaplayan fonksiyon
void transposeMatrix(int rows, int cols, int matrix[rows][cols], int transposed[cols][rows]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposed[j][i] = matrix[i][j]; // Transpoz işlemi
        }
    }
}
