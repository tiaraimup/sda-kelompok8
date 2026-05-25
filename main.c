#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_INTS 1000
#define MAX_WORDS 10000
#define MAX_WORD_LEN 100
#define DISPLAY_LIMIT 10

// ================= FUNGSI UTILITAS =================

// Mengacak array integer
void shuffleInts(int arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// Mengacak array string
void shuffleStrings(char **arr, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        char *temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// Menampilkan array integer
void printIntArray(int arr[], int n) {
    int limit = (n < DISPLAY_LIMIT) ? n : DISPLAY_LIMIT;

    for (int i = 0; i < limit; i++) {
        printf("%d ", arr[i]);
    }

    printf("... (menampilkan %d data pertama)\n", limit);
}

// Menampilkan array string
void printStringArray(char **arr, int n) {
    int limit = (n < DISPLAY_LIMIT) ? n : DISPLAY_LIMIT;

    for (int i = 0; i < limit; i++) {
        printf("%s ", arr[i]);
    }

    printf("... (menampilkan %d data pertama)\n", limit);
}

// Membaca dataset dari file txt
int loadDataset(const char *filename, char ***arr) {

    FILE *file = fopen(filename, "r");

    if (!file) {
        printf("Gagal membuka file %s\n", filename);
        return 0;
    }

    *arr = (char **)malloc(MAX_WORDS * sizeof(char *));

    char buffer[MAX_WORD_LEN];
    int count = 0;

    while (fscanf(file, "%s", buffer) == 1 && count < MAX_WORDS) {

        (*arr)[count] = (char *)malloc((strlen(buffer) + 1) * sizeof(char));

        strcpy((*arr)[count], buffer);

        count++;
    }

    fclose(file);

    return count;
}

// Membersihkan memory
void freeDataset(char **arr, int n) {

    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }

    free(arr);
}

// ================= SORTING DASAR =================

// Bubble Sort
void bubbleSort(int arr[], int n) {

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            if (arr[j] > arr[j + 1]) {

                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort
void insertionSort(int arr[], int n) {

    for (int i = 1; i < n; i++) {

        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {

            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

// Selection Sort
void selectionSort(int arr[], int n) {

    for (int i = 0; i < n - 1; i++) {

        int min_idx = i;

        for (int j = i + 1; j < n; j++) {

            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

// ================= ADVANCE SORTING =================

// MERGE SORT

void merge(char **arr, int l, int m, int r) {

    int n1 = m - l + 1;
    int n2 = r - m;

    char **L = (char **)malloc(n1 * sizeof(char *));
    char **R = (char **)malloc(n2 * sizeof(char *));

    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }

    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {

        if (strcmp(L[i], R[j]) <= 0) {
            arr[k] = L[i];
            i++;
        }

        else {
            arr[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(char **arr, int l, int r) {

    if (l < r) {

        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// QUICK SORT

void swapStr(char **a, char **b) {

    char *temp = *a;
    *a = *b;
    *b = temp;
}

int partition(char **arr, int low, int high) {

    char *pivot = arr[high];

    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {

        if (strcmp(arr[j], pivot) < 0) {

            i++;
            swapStr(&arr[i], &arr[j]);
        }
    }

    swapStr(&arr[i + 1], &arr[high]);

    return i + 1;
}

void quickSort(char **arr, int low, int high) {

    if (low < high) {

        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// SHELL SORT

void shellSort(char **arr, int n) {

    for (int gap = n / 2; gap > 0; gap /= 2) {

        for (int i = gap; i < n; i++) {

            char *temp = arr[i];

            int j;

            for (j = i; j >= gap && strcmp(arr[j - gap], temp) > 0; j -= gap) {

                arr[j] = arr[j - gap];
            }

            arr[j] = temp;
        }
    }
}

// ================= MENU SORTING DASAR =================

void handleBasicSorting() {

    int arr[NUM_INTS];

    for (int i = 0; i < NUM_INTS; i++) {
        arr[i] = i + 1;
    }

    int choice;

    do {

        printf("\n===== SORTING DASAR =====\n");
        printf("1. Bubble Sort\n");
        printf("2. Insertion Sort\n");
        printf("3. Selection Sort\n");
        printf("4. Kembali\n");

        printf("Pilih metode: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 3) {

            shuffleInts(arr, NUM_INTS);

            printf("\nData Sebelum Sorting:\n");
            printIntArray(arr, NUM_INTS);

            clock_t start = clock();

            if (choice == 1) {
                bubbleSort(arr, NUM_INTS);
            }

            else if (choice == 2) {
                insertionSort(arr, NUM_INTS);
            }

            else if (choice == 3) {
                selectionSort(arr, NUM_INTS);
            }

            clock_t end = clock();

            printf("\nData Setelah Sorting:\n");
            printIntArray(arr, NUM_INTS);

            double time_spent =
            (double)(end - start) / CLOCKS_PER_SEC;

            printf("\nWaktu Eksekusi: %f detik\n", time_spent);
        }

    } while (choice != 4);
}

// ================= MENU ADVANCE SORTING =================

void handleAdvanceSorting() {

    char **words = NULL;

    printf("\nMemuat dataset dari words.txt...\n");

    int numWords = loadDataset("words.txt", &words);

    if (numWords == 0) {
        return;
    }

    printf("Berhasil memuat %d kata.\n", numWords);

    int choice;

    do {

        printf("\n===== ADVANCE SORTING =====\n");
        printf("1. Merge Sort\n");
        printf("2. Quick Sort\n");
        printf("3. Shell Sort\n");
        printf("4. Kembali\n");

        printf("Pilih metode: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 3) {

            shuffleStrings(words, numWords);

            printf("\nData Sebelum Sorting:\n");
            printStringArray(words, numWords);

            clock_t start = clock();

            if (choice == 1) {
                mergeSort(words, 0, numWords - 1);
            }

            else if (choice == 2) {
                quickSort(words, 0, numWords - 1);
            }

            else if (choice == 3) {
                shellSort(words, numWords);
            }

            clock_t end = clock();

            printf("\nData Setelah Sorting:\n");
            printStringArray(words, numWords);

            double time_spent =
            (double)(end - start) / CLOCKS_PER_SEC;

            printf("\nWaktu Eksekusi: %f detik\n", time_spent);
        }

    } while (choice != 4);

    freeDataset(words, numWords);
}

// ================= MAIN PROGRAM =================

int main() {

    srand(time(NULL));

    int choice;

    printf("=====================================\n");
    printf("        PROGRAM SORTING SDA\n");
    printf("=====================================\n");
    printf("Kelompok : 8\n");
    printf("Anggota  : Tiara Balqis & Putri Rahmatul Ulya\n");

    do {

        printf("\n===== MENU UTAMA =====\n");
        printf("1. Sorting Dasar\n");
        printf("2. Advance Sorting\n");
        printf("3. Keluar\n");

        printf("Pilih menu: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                handleBasicSorting();
                break;

            case 2:
                handleAdvanceSorting();
                break;

            case 3:
                printf("Keluar dari program. Terima kasih!\n");
                break;

            default:
                printf("Pilihan tidak valid!\n");
        }

    } while (choice != 3);

    return 0;
}