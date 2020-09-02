#include <stdio.h>

void bubble_sort(int arr[], int n){
    for (int i = 0;  i < n - 1; i++){
        int temp;
        for (int j = 0; j < n - i - 1; j++){
            if (arr[j] > arr[j + 1]){
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int arr[5] = {100, 10, 15, 2, -100};
    bubble_sort(arr, 5);
    for (int i = 0; i < 5; i++){
        printf("%d ", arr[i]);
    }
    puts("");
    return 0;
}