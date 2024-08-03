#include <stdio.h>
#include <stdlib.h>

double** generateHilbertMatrix(int n) {
    // ��̬�����ڴ��Ա��� Hilbert ����
    double** hilbertMatrix = (double**)malloc(n * sizeof(double*));

    for (int i = 0; i < n; i++) {
        // Ϊÿһ�з����ڴ�
        hilbertMatrix[i] = (double*)malloc(n * sizeof(double));

        for (int j = 0; j < n; j++) {
            // ͨ����ʽ���� Hilbert �����ÿ��Ԫ�ص�ֵ
            hilbertMatrix[i][j] = 1.0 / (i + j + 1);
        }
    }

    return hilbertMatrix;
}

void gaussianElimination(double** matrix, double* vector, int n) {
    for (int k = 0; k < n - 1; k++) {
        for (int i = k + 1; i < n; i++) {
            // ������Ԫ����
            double factor = matrix[i][k] / matrix[k][k];

            for (int j = k; j < n; j++) {
                // ִ����Ԫ����
                matrix[i][j] -= factor * matrix[k][j];
            }

            // ��������
            vector[i] -= factor * vector[k];
        }
    }

    // ������������
    double* solution = (double*)malloc(n * sizeof(double));

    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;

        for (int j = i + 1; j < n; j++) {
            // ����������Ĳ��ֺ�
            sum += matrix[i][j] * solution[j];
        }

        // �����������ÿ��Ԫ�ص�ֵ
        solution[i] = (vector[i] - sum) / matrix[i][i];
    }

    printf("Solution:\n");

    for (int i = 0; i < n; i++) {
        // ��ӡ��������ÿ��Ԫ��
        printf("x%d = %lf\n", i + 1, solution[i]);
    }

    // �ͷŽ��������ڴ�
    free(solution);
}

int main() {
    int n;

    printf("������Hilbert����Ĵ�С��");

    // �����û�����ľ����С
    scanf("%d", &n);

    // ���� Hilbert ����
    double** hilbertMatrix = generateHilbertMatrix(n);

    // ��̬�����ڴ��Ա�������
    double* vector = (double*)malloc(n * sizeof(double));

    // ��ʼ��������Ԫ��
    for (int i = 0; i < n; i++) {
        vector[i] = 1.0;
    }

    // ���ø�˹��Ԫ�㷨�����Է�����
    gaussianElimination(hilbertMatrix, vector, n);

    // �ͷ��ڴ�
    for (int i = 0; i < n; i++) {
        free(hilbertMatrix[i]);
    }
    free(hilbertMatrix);
    free(vector);

    return 0;
}
