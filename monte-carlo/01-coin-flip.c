#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRIALS 10000

int main(void){
	srand(time(NULL));

	int heads_count = 0;

	FILE *gp = popen("gnuplot -persist", "w");
	if(!gp){
		perror("popen");
		return 1;
	}
	fprintf(gp, "set title 'Monte Carlo Coin Flip'\n");
	fprintf(gp, "set xlabel 'No. of trials'\n");
	fprintf(gp, "set ylabel 'Estimated P(heads)'\n");
	fprintf(gp, "set logscale x\n");
	fprintf(gp, "set yrange [0:1]\n");
	fprintf(gp, "plot '-' with lines title 'simulated', "
	            "0.5 with lines dashes 2 title 'true value (0.5)'\n");

	for(int i = 0; i < TRIALS; i++){
		int flip = rand() % 2;
		if(flip == 0){
			heads_count++;
		}
		fprintf(gp, "%d %f\n", i, (double)heads_count / i);
	}
	fprintf(gp, "e\n");
	pclose(gp);

	double probability = (double)heads_count / TRIALS;

	printf("\n##################################\n");
	printf("MONTE CARLO SIMULATION (COIN FLIP)\n");
	printf("##################################\n");

	printf("Total Trials: %d\n", TRIALS);
	printf("Heads counts: %d\n", heads_count);
	printf("Simulated Probability: %.2f\n", probability);

	return 0;
}
