#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define A 5.0
#define B 3.0
#define EPSILON 1e-8 // 精度

// 计算函数 f(t, x, y) 的值
double f(double t, double x, double y) {
    return (A * cos(t) - x) * (A * cos(t) - x) + (B * sin(t) - y) * (B * sin(t) - y);
}

// 计算函数 f(t, x, y) 对 t 的导数
double df(double t, double x, double y) {
    return 2 * (A * cos(t) - x) * (-sin(t)) + 2 * (B * sin(t) - y) * B * cos(t);
}

// 使用牛顿法寻找函数 f(t, x, y) 的最小值
double newton_method(double x, double y) {
    double t = atan2(y, x); // 初始化角度为 0
    double Y, d, old, lambda;
    int i = 0, j = 0;

    for (i = 0; i < 64; i++) {
        old = f(t, x, y);
        d = df(t, x, y);

        if (fabs(d) < 1e-100)
            return 0;

        d = old / d; // 牛顿法中的步长

        lambda = 1.0;

        // 二次插值
        for (j = 0; j < 8; j++) {
            Y = f(t - lambda * d, x, y);

            if (fabs(old) > fabs(Y))
                break;

            lambda *= (-0.5); // 缩小步长
        }

        if (j < 8) {
            t -= lambda * d;
        } else {
            t -= d; // 使用步长更新角度
            Y = f(t, x, y);
        }

        return fabs(Y); // 返回函数值的绝对值
    }
    
    return 0;
}

int main() {
    int i;
    time_t t;
    srand((unsigned)time(&t));

    for (i = 0; i < 20; i++) {
        // 生成随机的 (x, y) 坐标
        double x = (double)rand() / RAND_MAX * 10.0 - 5.0; // 生成 -5 到 5 之间的随机数
        double y = (double)rand() / RAND_MAX * 10.0 - 5.0;

        // 使用牛顿法计算最小值
        double t_min = newton_method(x, y);

        // 打印结果
        printf("x=%7.4f  y=%7.4f   distance=%7.4f\n", x, y, sqrt(f(t_min, x, y)));
    }

    return 0;
}
