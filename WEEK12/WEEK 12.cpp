#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_CITIES 10
#define POPULATION_SIZE 100
#define GENERATIONS 100000 
#define MUTATION_RATE 0.05

// 城市坐标
int cities[NUM_CITIES][2] = {
	{1, 1}, {9, 9}, {8, 0}, {3, 1}, {7, 8},
	{8, 1}, {1, 9}, {1, 5}, {8, 5}, {8, 6}
};

// 计算两点之间的距离
double distance(int x1, int y1, int x2, int y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// 适应度函数：计算路径总长度的倒数
double fitness(int individual[]) {
	double total_distance = 0.0;
	int visited[NUM_CITIES] = {0}; // 记录城市是否已经访问过
	visited[0] = 1; // 起点城市被访问过

	for (int i = 0; i < NUM_CITIES - 1; i++) {
		int city1 = individual[i];
		int city2 = individual[i + 1];
		if (visited[city2]) { // 如果城市已经被访问过，说明路径出现重复
			return 0.0; // 返回0表示不合法的路径
		}
		total_distance += distance(cities[city1][0], cities[city1][1], cities[city2][0], cities[city2][1]);
		visited[city2] = 1; // 将城市标记为已访问
	}

	return 1.0 / total_distance;
}


// 选择函数：基于适应度选择一个个体（轮盘赌选择）
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
	return POPULATION_SIZE - 1; // 备用返回值
}

// 交叉函数（顺序交叉）
void crossover(int parent1[], int parent2[], int child[]) {
	int start = 1 + rand() % (NUM_CITIES - 1); // 确保起点不是0
	int end = start + (rand() % (NUM_CITIES - start));

	// 复制父代1的城市到子代
	for (int i = start; i <= end; i++) {
		child[i] = parent1[i];
	}

	// 从父代2中选择未选择的城市添加到子代中
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
	child[0] = 0; // 确保起点为城市0
}

// 变异函数（交换变异）
void mutation(int individual[]) {
	if (rand() % 100 < MUTATION_RATE) { // MUTATION_RATE 百分比的变异概率
		int idx1 = 1 + rand() % (NUM_CITIES - 1); // 确保不变异起点0
		int idx2 = 1 + rand() % (NUM_CITIES - 1);
		// 确保 idx1 和 idx2 不同
		while (idx1 == idx2) {
			idx2 = 1 + rand() % (NUM_CITIES - 1);
		}
		// 交换城市
		int temp = individual[idx1];
		individual[idx1] = individual[idx2];
		individual[idx2] = temp;
	}
}

// 初始化种群
void initialize_population(int population[][NUM_CITIES]) {
	for (int i = 0; i < POPULATION_SIZE; i++) {
		population[i][0] = 0; // 确保起点为城市0
		for (int j = 1; j < NUM_CITIES; j++) {
			population[i][j] = j;
		}
		// 打乱除起点城市0以外的其他城市
		for (int j = 1; j < NUM_CITIES; j++) {
			int swap_idx = 1 + rand() % (NUM_CITIES - 1);
			int temp = population[i][j];
			population[i][j] = population[i][swap_idx];
			population[i][swap_idx] = temp;
		}
	}
}

int main() {
	srand(time(NULL)); // 初始化随机种子

	int population[POPULATION_SIZE][NUM_CITIES];
	int new_population[POPULATION_SIZE][NUM_CITIES];
	double fitness_values[POPULATION_SIZE];

	// 初始化种群
	initialize_population(population);

	// 进化种群
	for (int generation = 0; generation < GENERATIONS; generation++) {
		// 计算每个个体的适应度
		for (int i = 0; i < POPULATION_SIZE; i++) {
			fitness_values[i] = fitness(population[i]);
		}

		// 创建新种群
		for (int i = 0; i < POPULATION_SIZE; i += 2) {
			int parent1_idx = select_individual(fitness_values);
			int parent2_idx = select_individual(fitness_values);

			crossover(population[parent1_idx], population[parent2_idx], new_population[i]);
			crossover(population[parent2_idx], population[parent1_idx], new_population[i + 1]);

			mutation(new_population[i]);
			mutation(new_population[i + 1]);
		}

		// 将新种群复制到当前种群
		for (int i = 0; i < POPULATION_SIZE; i++) {
			for (int j = 0; j < NUM_CITIES; j++) {
				population[i][j] = new_population[i][j];
			}
		}

		// 每10000代打印一次最佳适应度
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

	// 找到最终种群中最好的个体并打印
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
