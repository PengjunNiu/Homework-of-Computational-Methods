#include <stdio.h>
#include <stdlib.h>

void finalFactor(double *one, double *two, int numOfOne, int numOfTwo, double *ans, int n) {
	for (int i = 0; i <= numOfOne; i++) {
		for (int j = 0; j <= numOfTwo; j++) {
			ans[i + j] += one[i] * two[j];
		}
	}
}

void sum(double **ans, int n, double *qwer) {
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			qwer[i] += ans[j][i];
		}
	}
}

void lagPolynomial(int n, double *X, double *Y, double *a) {
	double *fenmu = (double *)malloc((n + 1) * sizeof(double));
	double *temp = (double *)malloc((n + 1) * sizeof(double));
	double **ans = (double **)malloc((n + 1) * sizeof(double *));
	double *qwer = (double *)malloc((n + 1) * sizeof(double));

	if (fenmu == NULL || temp == NULL || ans == NULL || qwer == NULL) {
		printf("内存分配失败\n");
		exit(1);
	}

	for (int i = 0; i <= n; i++) {
		ans[i] = (double *)malloc((n + 1) * sizeof(double));
		if (ans[i] == NULL) {
			printf("内存分配失败\n");
			exit(1);
		}
	}

	for (int i = 0; i <= n; i++) {
		fenmu[i] = 1.0;
		temp[i] = 1.0;
		qwer[i] = 0.0;
	}

	for (int k = 0; k <= n; k++) {
		for (int j = 0; j <= n; j++) {
			if (j != k) {
				double a[2] = {-X[j], 1};
				finalFactor(a, temp, 1, 1, ans[k], n);
				fenmu[k] *= (X[k] - X[j]);
			}
		}
		for (int i = 0; i <= n; i++) {
			ans[k][i] *= Y[k];
			ans[k][i] /= fenmu[k];
		}
		sum(ans, n, qwer);
	}

	for (int i = 0; i <= n; i++) {
		a[i] = qwer[i];
	}

	free(fenmu);
	free(temp);
	for (int i = 0; i <= n; i++) {
		free(ans[i]);
	}
	free(ans);
	free(qwer);
}

int main() {
	int n;
	double *x, *y, *a;
	printf("输入阶数：\n");
	scanf("%d", &n);

	if (n < 0) {
		printf("阶数必须为非负整数\n");
		return 1;
	}

	// 为 x 和 y 数组分配内存空间
	x = (double *)malloc((n + 1) * sizeof(double));
	y = (double *)malloc((n + 1) * sizeof(double));
	a = (double *)malloc((n + 1) * sizeof(double));

	// 检查内存分配是否成功
	if (x == NULL || y == NULL || a == NULL) {
		printf("内存分配失败\n");
		return 1;
	}

	printf("输入点的数量：\n");
	printf("按顺序输入 xi yi：\n");

	for (int i = 0; i <= n; i++) {
		scanf("%lf %lf", &x[i], &y[i]);
	}

	lagPolynomial(n, x, y, a);

	// 打印结果
	printf("插值多项式的系数：\n");
	for (int i = 0; i <= n; i++) {
		printf("a%d = %lf\n", i, a[i]);
	}

	// 释放内存
	free(x);
	free(y);
	free(a);

	return 0;
}
