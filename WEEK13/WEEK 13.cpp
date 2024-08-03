#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define TEST_SIZE 26
#define TRAIN_SIZE 124
#define FEATURE_COUNT 4
#define K_NEIGHBORS 6

typedef struct {
    double features[FEATURE_COUNT]; // ÿ�ֻ���4����������
    char species[20];   // ��Ż�������
    int label;       // �������ñ�ǩ Ϊ�˷�����
} Iris;

typedef struct {
    double value;  // ��������
    int label;     // ���ڰ�ѵ������ǩ
} Distance;

Iris testSet[TEST_SIZE];
Iris forecastSet[TEST_SIZE];
Iris trainSet[TRAIN_SIZE];
Distance distances[TRAIN_SIZE];

// ����������ת��Ϊ��ǩ
void labelSpecies(char *type, int *label);
// �������������
void shuffle(Iris iris[], int n);
// ���ļ��м������ݼ�
void loadData(const char *trainPath, const char *testPath);
// ����������֮���ŷ�Ͼ���
double calculateDistance(const Iris *iris1, const Iris *iris2);
// ���ڱȽ����� Distance �ṹ�ĺ�������������
int compareDistances(const void *d1, const void *d2);
// ͳ��ǰ K ������ھ��г��ִ������ı�ǩ
int countMostFrequentLabel(Distance *distances, int k);
// �������ڷ���ָ����ǩ���ַ�����ʾ
const char* getSpeciesLabel(int label);
// ��ӡ�ȽϽ��������ԭʼ��ǩ��Ԥ���ǩ��׼ȷ��
void printResults(int k, int count);

int main() {
    srand((unsigned int)time(NULL));

    // ��������
    loadData("IrisTrain.txt", "IrisTest.txt");
    int count = 0;

    // ��ÿ��������������Ԥ��
    for (int i = 0; i < TEST_SIZE; i++) {
        // �������������ѵ������ÿ�������ľ���
        for (int j = 0; j < TRAIN_SIZE; j++) {
            distances[j].value = calculateDistance(&testSet[i], &trainSet[j]);
            distances[j].label = trainSet[j].label;
        }

        // �Ծ����������
        qsort(distances, TRAIN_SIZE, sizeof(Distance), compareDistances);

        // ͳ������� K ���ھ��г��ִ������ı�ǩ
        forecastSet[i].label = countMostFrequentLabel(distances, K_NEIGHBORS);

        // ���Ԥ�����Ƿ���ȷ
        if (forecastSet[i].label == testSet[i].label) {
            count++;
        }
    }

    // ��ӡ�ȽϽ��
    printResults(K_NEIGHBORS, count);
    return 0;
}

void labelSpecies(char *type, int *label) {
    if (strcmp(type, "Iris-setosa") == 0) *label = 0;
    else if (strcmp(type, "Iris-versicolor") == 0) *label = 1;
    else if (strcmp(type, "Iris-virginica") == 0) *label = 2;
}

void shuffle(Iris iris[], int n) {
    int i;
    for (i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Iris temp = iris[i];
        iris[i] = iris[j];
        iris[j] = temp;
    }
}

void loadData(const char *trainPath, const char *testPath) {
    FILE *fpTrain = fopen(trainPath, "r");
    FILE *fpTest = fopen(testPath, "r");
    char species[20];
    double features[FEATURE_COUNT];
    int i, j;

    if (!fpTrain || !fpTest) {
        fprintf(stderr, "Error opening files.\n");
        exit(1);
    }

    for (i = 0; i < TRAIN_SIZE; i++) {
        fscanf(fpTrain, "%lf,%lf,%lf,%lf,%s", &features[0], &features[1], &features[2], &features[3], species);
        for (j = 0; j < FEATURE_COUNT; j++) {
            trainSet[i].features[j] = features[j];
        }
        labelSpecies(species, &trainSet[i].label);
    }

    for (i = 0; i < TEST_SIZE; i++) {
        fscanf(fpTest, "%lf,%lf,%lf,%lf,%s", &features[0], &features[1], &features[2], &features[3], species);
        for (j = 0; j < FEATURE_COUNT; j++) {
            testSet[i].features[j] = features[j];
        }
        labelSpecies(species, &testSet[i].label);
    }

    fclose(fpTrain);
    fclose(fpTest);
}

double calculateDistance(const Iris *iris1, const Iris *iris2) {
    double sum = 0.0;
    for (int i = 0; i < FEATURE_COUNT; i++) {
        sum += (iris1->features[i] - iris2->features[i]) * (iris1->features[i] - iris2->features[i]);
    }
    return sqrt(sum);
}

int compareDistances(const void *d1, const void *d2) {
    const Distance *distance1 = (const Distance *)d1;
    const Distance *distance2 = (const Distance *)d2;

    if (distance1->value > distance2->value) {
        return 1;
    } else if (distance1->value < distance2->value) {
        return -1;
    } else {
        return 0;
    }
}

int countMostFrequentLabel(Distance *distances, int k) {
    int labelCount[3] = {0};
    for (int i = 0; i < k; i++) {
        labelCount[distances[i].label]++;
    }
    int maxCount = labelCount[0];
    int label = 0;
    for (int i = 1; i < 3; i++) {
        if (labelCount[i] > maxCount) {
            maxCount = labelCount[i];
            label = i;
        }
    }
    return label;
}

const char* getSpeciesLabel(int label) {
    switch(label) {
        case 0:
            return "Iris-setosa";
        case 1:
            return "Iris-versicolor";
        case 2:
            return "Iris-virginica";
        default:
            return "Unknown";
    }
}

void printResults(int k, int count) {
    printf("Comparison Results for K = %d:\n", k);
    for (int i = 0; i < TEST_SIZE; i++) {
        const char* predictedSpecies = getSpeciesLabel(forecastSet[i].label);
        const char* trueSpecies = getSpeciesLabel(testSet[i].label);
        const char* correctness = (forecastSet[i].label == testSet[i].label) ? "Correct" : "Incorrect";

        printf("%-20s%-20s%-10s\n", predictedSpecies, trueSpecies, correctness);
    }
    double accuracy = ((double)count / TEST_SIZE) * 100.0;
    printf("Accuracy:   %.2f%%\n", accuracy);
    printf("ErrorRatio: %.2f%%\n", 100-accuracy);
    printf("Correctly Classified Instances: %d out of %d\n", count, TEST_SIZE);
}


