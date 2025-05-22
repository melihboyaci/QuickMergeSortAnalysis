#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

// Fonksiyon prototipleri
void MergeSort(int arr[], int left, int right);
void Merge(int arr[], int left, int mid, int right);
void QuickSort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
int hoare_partition(int arr[], int low, int high);
void generateRandomArray(int* arr, int size);
double measureTime(void (*sortFunction)(int*, int, int), int* arr, int size);

int main() {

    // Rastgele sayı üreteci için başlangıç
    srand(time(NULL));

    // Sonuçları yazmak için dosya açma
    FILE* fp = fopen("sonuclar.txt", "w");
    if (fp == NULL) {
        printf("Dosya açılamadı.\n");
        return 1;
    }

    fprintf(fp, "n,merge_time,c_merge,quick_time,c_quick\n");
    
    // Dizi boyutları
    int sizes[6] = { 1000, 5000, 10000, 50000, 100000, 200000 };
    
    for (int i = 0; i < 6; i++) {
        int size = sizes[i];
        double totalMergeTime = 0;
        double totalQuickTime = 0;

        for (int j = 0; j < 50; j++) {
            
            // Orijinal dizi
            int* originalArray = (int*)malloc(size * sizeof(int));
            generateRandomArray(originalArray, size);

            // Kopya diziyi oluştur
            int* copy1 = (int*)malloc(size * sizeof(int));
            int* copy2 = (int*)malloc(size * sizeof(int));
            for (int k = 0; k < size; k++) {
                copy1[k] = originalArray[k];
                copy2[k] = originalArray[k];
            }

            // MergeSort ve QuickSort için zaman ölçümü
            totalMergeTime += measureTime(MergeSort, copy1, size);
            totalQuickTime += measureTime(QuickSort, copy2, size); 

            // Belleği temizle
            free(originalArray);
            free(copy1);
            free(copy2);
        }
        
        //MergeSort için ortalama süre
        double averageMergeTime = totalMergeTime / 50; 
        
        //QuickSort için ortalama süre
        double averageQuickTime = totalQuickTime / 50;
        
        // C sabitlerini hesapla
        double c_merge = averageMergeTime / (size * log2(size));
        double c_quick = averageQuickTime / (size * log2(size));
        
        // Sonuçları ekrana yazdır
        printf("Array size: %d\n", size);
        printf("Average Merge Sort time: %.10f saniye\n", averageMergeTime);
        printf("C_merge: %.10f\n", c_merge);
        printf("Average Quick Sort time: %.10f saniye\n", averageQuickTime);
        printf("C_quick: %.10f\n", c_quick);

        // Dosyaya yazdır
        fprintf(fp, "%d,%.10f,%.10f,%.10f,%.10f\n", 
            size, 
            averageMergeTime, 
            c_merge, 
            averageQuickTime, 
            c_quick
        );
    }
    
    fclose(fp);
    printf("Sonuçlar sonuclar.txt dosyasına yazıldı.\n");
    return 0;
}

void MergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        MergeSort(arr, left, mid);
        MergeSort(arr, (mid + 1), right);

        Merge(arr, left, mid, right);
    }
}

void Merge(int arr[], int left, int mid, int right) {

    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
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
    
}

void QuickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = hoare_partition(arr, low, high);

        QuickSort(arr, low, pi);
        QuickSort(arr, pi + 1, high);
    }
}

int hoare_partition(int arr[], int low, int high) {
    int pivot = arr[low]; 
    int i = low - 1;
    int j = high + 1;

    while (1) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j)
            return j;

        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// Rastgele dizi oluşturma fonksiyonu
void generateRandomArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000000; // 0-999999 arasında rastgele sayılar
    }
}

// Zaman ölçme fonksiyonu
double measureTime(void (*sortFunction)(int*, int, int), int* arr, int size) {
    clock_t start = clock();
    sortFunction(arr, 0, size - 1);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC; // saniye cinsinden
}