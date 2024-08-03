#include <stdio.h>
#include <stdlib.h>

double** generateHilbertMatrix(int n) {
    // 动态分配内存以保存 Hilbert 矩阵
    double** hilbertMatrix = (double**)malloc(n * sizeof(double*));

    for (int i = 0; i < n; i++) {
        // 为每一行分配内存
        hilbertMatrix[i] = (double*)malloc(n * sizeof(double));

        for (int j = 0; j < n; j++) {
            // 通过公式计算 Hilbert 矩阵的每个元素的值
            hilbertMatrix[i][j] = 1.0 / (i + j + 1);
        }
    }

    return hilbertMatrix;
}

void gaussianElimination(double** matrix, double* vector, int n) {
    for (int k = 0; k < n - 1; k++) {
        for (int i = k + 1; i < n; i++) {
            // 计算消元因子
            double factor = matrix[i][k] / matrix[k][k];

            for (int j = k; j < n; j++) {
                // 执行消元操作
                matrix[i][j] -= factor * matrix[k][j];
            }

            // 更新向量
            vector[i] -= factor * vector[k];
        }
    }

    // 解向量的数组
    double* solution = (double*)malloc(n * sizeof(double));

    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;

        for (int j = i + 1; j < n; j++) {
            // 计算解向量的部分和
            sum += matrix[i][j] * solution[j];
        }

        // 计算解向量的每个元素的值
        solution[i] = (vector[i] - sum) / matrix[i][i];
    }

    printf("Solution:\n");

    for (int i = 0; i < n; i++) {
        // 打印解向量的每个元素
        printf("x%d = %lf\n", i + 1, solution[i]);
    }

    // 释放解向量的内存
    free(solution);
}

int main() {
    int n;

    printf("请输入Hilbert矩阵的大小：");

    // 接收用户输入的矩阵大小
    scanf("%d", &n);

    // 生成 Hilbert 矩阵
    double** hilbertMatrix = generateHilbertMatrix(n);

    // 动态分配内存以保存向量
    double* vector = (double*)malloc(n * sizeof(double));

    // 初始化向量的元素
    for (int i = 0; i < n; i++) {
        vector[i] = 1.0;
    }

    // 调用高斯消元算法解线性方程组
    gaussianElimination(hilbertMatrix, vector, n);

    // 释放内存
    for (int i = 0; i < n; i++) {
        free(hilbertMatrix[i]);
    }
    free(hilbertMatrix);
    free(vector);

    return 0;
}
