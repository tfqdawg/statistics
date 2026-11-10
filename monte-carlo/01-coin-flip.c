#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRIALS 50000

int main(void){
	srand(time(NULL));
	int heads_count = 0;

	// gnuplot stdin pipe
	FILE *gnuplot = popen("gnuplot -persist", "w");
	if(!gnuplot){
		perror("popen");
		return 1;
	}

	// plot settings
	fprintf(gnuplot, "set title 'Monte Carlo Coin Flip'\n");
	fprintf(gnuplot, "set xlabel 'No. of trials'\n");
	fprintf(gnuplot, "set ylabel 'Estimated P(heads)'\n");
	fprintf(gnuplot, "set logscale x\n");
	fprintf(gnuplot, "set yrange [0:1]\n");
	fprintf(gnuplot, "plot '-' with lines title 'simulated', " // Simulated line
	            		 "0.5 with lines dashes 2 title 'true value (0.5)'\n"); // 0.5 line

	for(int i = 0; i < TRIALS; i++){
		int flip = rand() % 2;
		if(flip == 0){
			heads_count++;
		}
		fprintf(gnuplot, "%d %f\n", i, (double)heads_count / i);
	}
	fprintf(gnuplot, "e\n");
	pclose(gnuplot);

	double probability = (double)heads_count / TRIALS;

	// print results
	printf("\n########################################\n");
	printf("## MONTE CARLO SIMULATION (COIN FLIP) ##\n");
	printf("########################################\n");
	printf("Total Trials: %d\n", TRIALS);
	printf("Heads counts: %d\n", heads_count);
	printf("Simulated Probability: %.4f\n", probability);

	return 0;
}
