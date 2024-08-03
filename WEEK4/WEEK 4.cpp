#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define A 5.0
#define B 3.0
#define EPSILON 1e-8 // ����

// ���㺯�� f(t, x, y) ��ֵ
double f(double t, double x, double y) {
    return (A * cos(t) - x) * (A * cos(t) - x) + (B * sin(t) - y) * (B * sin(t) - y);
}

// ���㺯�� f(t, x, y) �� t �ĵ���
double df(double t, double x, double y) {
    return 2 * (A * cos(t) - x) * (-sin(t)) + 2 * (B * sin(t) - y) * B * cos(t);
}

// ʹ��ţ�ٷ�Ѱ�Һ��� f(t, x, y) ����Сֵ
double newton_method(double x, double y) {
    double t = atan2(y, x); // ��ʼ���Ƕ�Ϊ 0
    double Y, d, old, lambda;
    int i = 0, j = 0;

    for (i = 0; i < 64; i++) {
        old = f(t, x, y);
        d = df(t, x, y);

        if (fabs(d) < 1e-100)
            return 0;

        d = old / d; // ţ�ٷ��еĲ���

        lambda = 1.0;

        // ���β�ֵ
        for (j = 0; j < 8; j++) {
            Y = f(t - lambda * d, x, y);

            if (fabs(old) > fabs(Y))
                break;

            lambda *= (-0.5); // ��С����
        }

        if (j < 8) {
            t -= lambda * d;
        } else {
            t -= d; // ʹ�ò������½Ƕ�
            Y = f(t, x, y);
        }

        return fabs(Y); // ���غ���ֵ�ľ���ֵ
    }
    
    return 0;
}

int main() {
    int i;
    time_t t;
    srand((unsigned)time(&t));

    for (i = 0; i < 20; i++) {
        // ��������� (x, y) ����
        double x = (double)rand() / RAND_MAX * 10.0 - 5.0; // ���� -5 �� 5 ֮��������
        double y = (double)rand() / RAND_MAX * 10.0 - 5.0;

        // ʹ��ţ�ٷ�������Сֵ
        double t_min = newton_method(x, y);

        // ��ӡ���
        printf("x=%7.4f  y=%7.4f   distance=%7.4f\n", x, y, sqrt(f(t_min, x, y)));
    }

    return 0;
}
