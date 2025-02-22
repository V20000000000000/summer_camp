#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 產生範圍內的隨機小數
float randomFloat(float min, float max) {
    return min + (max - min) * ((float)rand() / RAND_MAX);
}

// 遞迴拆分函數
int recursivePartition(float n, int parts, float min, float max, float *result, int index) {
    // Base case: 只剩下最後一個數，確保符合範圍
    if (parts == 1) {
        if (n >= min && n <= max) {
            result[index] = n;
            return 1; // 成功
        } else {
            return 0; // 失敗，回溯
        }
    }

    // 隨機選擇一個數 p，確保剩餘的 n - p 仍可分配給 parts-1 個數
    float p = randomFloat(min, max);
    float remaining = n - p;

    if (remaining < min * (parts - 1) || remaining > max * (parts - 1)) {
        return 0; // 失敗，回溯
    }

    // 存入結果陣列
    result[index] = p;

    // 遞迴處理剩餘的數值
    if (recursivePartition(remaining, parts - 1, min, max, result, index + 1)) {
        return 1; // 成功
    }

    return 0; // 失敗，回溯
}

// 主函數：呼叫遞迴拆分
float* randomPartition(float n, int parts, float min, float max) {
    if (parts <= 0) return NULL;

    // 確保總和 n 可以被拆分
    if (min * parts > n || max * parts < n) return NULL;

    float* result = (float*)malloc(parts * sizeof(float));
    if (result == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    // 嘗試直到找到有效解
    while (!recursivePartition(n, parts, min, max, result, 0));

    return result;
}

// 測試函數
int main() {
    srand(time(NULL));

    float n = 2.88;
    int parts = 20;
    float min_value = 0.05;
    float max_value = 0.4;

    float* result = randomPartition(n, parts, min_value, max_value);
    
    if (result) {
        printf("隨機拆分結果: { ");
        float sum = 0.0;
        for (int i = 0; i < parts; i++) {
            printf("%.2f ", result[i]);
            sum += result[i];
        }
        printf("} (sum = %.2f)\n", sum);
        free(result);
    } else {
        printf("無法拆分，請調整參數。\n");
    }

    return 0;
}
