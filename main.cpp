#include "soph_PGG.h"
using namespace std;

int main(int argc, char** argv){
	srand(time(NULL));
//	double dens = 0.6;
//	double r = 3.0;
  double c = 1;
//	if(argc > 2){
//		r =    atof(argv[1]);
//		dens = atof(argv[2]);
//	}

	for (double r = 3.0; r < 5; r +=0.1){
		for(double dens = 0.6; dens < 1.001; dens += 0.05){
			printf("Now doing sophisticated PGG with r:%f, density:%f, cost:%f\n",r,dens,c);
			soph_PGG gameOBJ(r,dens,c);
			gameOBJ.game(true);
		}
	}

	return 0;
}