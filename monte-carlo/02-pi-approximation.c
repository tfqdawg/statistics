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
	FILE *gp = popen("gnuplot -persistent", "w");
	if(gp == NULL){
		perror("popen");
		return 1;
	}
	
	// start inline datablock
	fprintf(gp, "$pts << EOD\n");

	for(int i = 0; i < trials; i++){
		float x = (float) rand() / (float)RAND_MAX;
		float y = (float) rand() / (float)RAND_MAX;
		int hit = (x * x + y * y <= 1);

		if(hit){
			inCircle++;
		}

		if(i < toPlot){
			fprintf(gp, "%f %f %d\n", x, y, hit);
		}
	}

	fprintf(gp, "EOD\n");

	// pi approximation results
	float approx = 4.0 * (float)inCircle / trials;
	printf("Monte Carlo approximation of pi,π: %f\n", approx);

	// plot settings
	fprintf(gp, "set title 'Monte Carlo PI approximation, First %d points shown. (Current approx. %f)'\n", toPlot, approx); // title
	fprintf(gp, "set size ratio 1\n"); // set aspect ratio to 1:1
	fprintf(gp, "set xrange [0:1]\n"); // [0,1] range in x-axis
	fprintf(gp, "set yrange [0:1]\n"); // [0,1] range in y-axis
	fprintf(gp, "set samples 500\n"); // points to use to draw a function
	fprintf(gp, "set palette defined (0 'red', 1 'blue')\n"); //define colors
	fprintf(gp, "set cbrange [0:1]\n"); // pin colors to to exactly 0(red) and 1(blue)
	fprintf(gp, "unset colorbox\n"); // disable color legend bar
	fprintf(gp, "unset key\n"); // disable legend

	// plot command
	fprintf(gp, "plot $pts using 1:2:3 with points pt 7 ps 1 palette, " //data
	            "sqrt(1 - x**2) with lines lw 2 lc rgb 'black'\n"); // boundary curve

	// close gnuplot pipe
	pclose(gp);

	return 0;
}
