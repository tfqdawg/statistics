// This project serves to help me learn to use gnuplot within C
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){
	srand(time(NULL));
	int trials = 1000000;
	int inCircle = 0;

	// open gnuplot stdin pipe
	int toPlot = 5000;
	FILE *gnuplot = popen("gnuplot -persistent", "w");
	if(gnuplot == NULL){
		perror("popen");
		return 1;
	}
	
	// start inline datablock
	fprintf(gnuplot, "$pts << EOD\n");

	for(int i = 0; i < trials; i++){
		float x = (float)rand() / (float)RAND_MAX;
		float y = (float)rand() / (float)RAND_MAX;
		int hit = (x * x + y * y <= 1);

		if(hit){
			inCircle++;
		}

		if(i < toPlot){
			fprintf(gnuplot, "%f %f %d\n", x, y, hit);
		}
	}

	fprintf(gnuplot, "EOD\n");

	// pi approximation results
	float approx = 4.0 * (float)inCircle / trials;
	printf("Monte Carlo approximation of pi,π: %f\n", approx);

	// plot settings
	fprintf(gnuplot, "set title 'Monte Carlo PI approximation, First %d points shown. (Current approx. %f)'\n", toPlot, approx); // title
	fprintf(gnuplot, "set size ratio 1\n"); // set aspect ratio to 1:1
	fprintf(gnuplot, "set xrange [0:1]\n"); // [0,1] range in x-axis
	fprintf(gnuplot, "set yrange [0:1]\n"); // [0,1] range in y-axis
	fprintf(gnuplot, "set samples 500\n"); // points to use to draw a function
	fprintf(gnuplot, "set palette defined (0 'red', 1 'blue')\n"); //define colors
	fprintf(gnuplot, "set cbrange [0:1]\n"); // pin colors to to exactly 0(red) and 1(blue)
	fprintf(gnuplot, "unset colorbox\n"); // disable color legend bar
	fprintf(gnuplot, "unset key\n"); // disable legend

	// plot command
	fprintf(gnuplot, "plot $pts using 1:2:3 with points pt 7 ps 1 palette, " //data
	            "sqrt(1 - x**2) with lines lw 2 lc rgb 'black'\n"); // boundary curve

	// close gnuplot pipe
	pclose(gnuplot);

	return 0;
}
