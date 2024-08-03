#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_CITIES 10
#define POPULATION_SIZE 100
#define GENERATIONS 100000 
#define MUTATION_RATE 0.05

// ��������
int cities[NUM_CITIES][2] = {
	{1, 1}, {9, 9}, {8, 0}, {3, 1}, {7, 8},
	{8, 1}, {1, 9}, {1, 5}, {8, 5}, {8, 6}
};

// ��������֮��ľ���
double distance(int x1, int y1, int x2, int y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// ��Ӧ�Ⱥ���������·���ܳ��ȵĵ���
double fitness(int individual[]) {
	double total_distance = 0.0;
	int visited[NUM_CITIES] = {0}; // ��¼�����Ƿ��Ѿ����ʹ�
	visited[0] = 1; // �����б����ʹ�

	for (int i = 0; i < NUM_CITIES - 1; i++) {
		int city1 = individual[i];
		int city2 = individual[i + 1];
		if (visited[city2]) { // ��������Ѿ������ʹ���˵��·�������ظ�
			return 0.0; // ����0��ʾ���Ϸ���·��
		}
		total_distance += distance(cities[city1][0], cities[city1][1], cities[city2][0], cities[city2][1]);
		visited[city2] = 1; // �����б��Ϊ�ѷ���
	}

	return 1.0 / total_distance;
}


// ѡ������������Ӧ��ѡ��һ�����壨���̶�ѡ��
int select_individual(double fitness_values[]) {
	double sum_fitness = 0.0;
	for (int i = 0; i < POPULATION_SIZE; i++) {
		sum_fitness += fitness_values[i];
	}
	double r = ((double) rand() / (RAND_MAX)) * sum_fitness;
	double partial_sum = 0.0;
	for (int i = 0; i < POPULATION_SIZE; i++) {
		partial_sum += fitness_values[i];
		if (partial_sum >= r) {
			return i;
		}
	}
	return POPULATION_SIZE - 1; // ���÷���ֵ
}

// ���溯����˳�򽻲棩
void crossover(int parent1[], int parent2[], int child[]) {
	int start = 1 + rand() % (NUM_CITIES - 1); // ȷ����㲻��0
	int end = start + (rand() % (NUM_CITIES - start));

	// ���Ƹ���1�ĳ��е��Ӵ�
	for (int i = start; i <= end; i++) {
		child[i] = parent1[i];
	}

	// �Ӹ���2��ѡ��δѡ��ĳ�����ӵ��Ӵ���
	int current = (end + 1) % NUM_CITIES;
	for (int i = 0; i < NUM_CITIES; i++) {
		int candidate = parent2[(end + 1 + i) % NUM_CITIES];
		int found = 0;
		for (int j = start; j <= end; j++) {
			if (child[j] == candidate) {
				found = 1;
				break;
			}
		}
		if (!found) {
			child[current] = candidate;
			current = (current + 1) % NUM_CITIES;
		}
	}
	child[0] = 0; // ȷ�����Ϊ����0
}

// ���캯�����������죩
void mutation(int individual[]) {
	if (rand() % 100 < MUTATION_RATE) { // MUTATION_RATE �ٷֱȵı������
		int idx1 = 1 + rand() % (NUM_CITIES - 1); // ȷ�����������0
		int idx2 = 1 + rand() % (NUM_CITIES - 1);
		// ȷ�� idx1 �� idx2 ��ͬ
		while (idx1 == idx2) {
			idx2 = 1 + rand() % (NUM_CITIES - 1);
		}
		// ��������
		int temp = individual[idx1];
		individual[idx1] = individual[idx2];
		individual[idx2] = temp;
	}
}

// ��ʼ����Ⱥ
void initialize_population(int population[][NUM_CITIES]) {
	for (int i = 0; i < POPULATION_SIZE; i++) {
		population[i][0] = 0; // ȷ�����Ϊ����0
		for (int j = 1; j < NUM_CITIES; j++) {
			population[i][j] = j;
		}
		// ���ҳ�������0�������������
		for (int j = 1; j < NUM_CITIES; j++) {
			int swap_idx = 1 + rand() % (NUM_CITIES - 1);
			int temp = population[i][j];
			population[i][j] = population[i][swap_idx];
			population[i][swap_idx] = temp;
		}
	}
}

int main() {
	srand(time(NULL)); // ��ʼ���������

	int population[POPULATION_SIZE][NUM_CITIES];
	int new_population[POPULATION_SIZE][NUM_CITIES];
	double fitness_values[POPULATION_SIZE];

	// ��ʼ����Ⱥ
	initialize_population(population);

	// ������Ⱥ
	for (int generation = 0; generation < GENERATIONS; generation++) {
		// ����ÿ���������Ӧ��
		for (int i = 0; i < POPULATION_SIZE; i++) {
			fitness_values[i] = fitness(population[i]);
		}

		// ��������Ⱥ
		for (int i = 0; i < POPULATION_SIZE; i += 2) {
			int parent1_idx = select_individual(fitness_values);
			int parent2_idx = select_individual(fitness_values);

			crossover(population[parent1_idx], population[parent2_idx], new_population[i]);
			crossover(population[parent2_idx], population[parent1_idx], new_population[i + 1]);

			mutation(new_population[i]);
			mutation(new_population[i + 1]);
		}

		// ������Ⱥ���Ƶ���ǰ��Ⱥ
		for (int i = 0; i < POPULATION_SIZE; i++) {
			for (int j = 0; j < NUM_CITIES; j++) {
				population[i][j] = new_population[i][j];
			}
		}

		// ÿ10000����ӡһ�������Ӧ��
		if (generation % 10000 == 0) {
			double best_fitness = fitness_values[0];
			for (int i = 1; i < POPULATION_SIZE; i++) {
				if (fitness_values[i] > best_fitness) {
					best_fitness = fitness_values[i];
				}
			}
			printf("Generation %d: Best Fitness = %.5f\n", generation, best_fitness);
		}
	}

	// �ҵ�������Ⱥ����õĸ��岢��ӡ
	int best_individual_idx = 0;
	double best_fitness = fitness_values[0];
	for (int i = 1; i < POPULATION_SIZE; i++) {
		if (fitness_values[i] > best_fitness) {
			best_fitness = fitness_values[i];
			best_individual_idx = i;
		}
	}

	printf("Best Path Length: %.2f\n", 1.0 / best_fitness);
	printf("Best Path Sequence: ");
	for (int i = 0; i < NUM_CITIES; i++) {
		printf("%d ", population[best_individual_idx][i]);
	}
	printf("\n");

	return 0;
}
