#include <omp.h>
#include <iostream>
using namespace std;
static long num_steps = 1000000;
double step;
#define NUM_THREADS 2 
void main()
{
	int i[NUM_THREADS];
	double x, pi, sum[NUM_THREADS];
	step = 1.0 / (double)num_steps;
	omp_set_num_threads(NUM_THREADS); //
#pragma omp parallel private(i)
	{
		double x;
		int id;
		id = omp_get_thread_num();
		for (i[id] = id, sum[id] = 0.0; i[id] < num_steps; i[id] = i[id] + NUM_THREADS) {//
			x = (i[id] + 0.5) * step;
			//cout << "i " << i[id] << " id" << id << endl;
			sum[id] += 4.0 / (1.0 + x * x);
		}
	} 
	pi = 0.0;
	for (int i = 0; i < NUM_THREADS; i++)
		pi += sum[i] * step;
	cout << "PI:" << pi << endl;
	system("pause");
}
