#include "soph_PGG.h"
using namespace std;

int main(int argc, char** argv){
	srand(time(NULL));
	double dens = 0.91;
	double r = 3.0;
	double c = 0;
	if(argc > 2){
		r =    atof(argv[1]);
		dens = atof(argv[2]);
		c = atof(argv[3]);
	}

	printf("Now doing sophisticated PGG with r:%f, density:%f, cost:%f\n",r,dens,c);
	soph_PGG gameOBJ(r,dens,c);
	gameOBJ.game(true);
	
	return 0;
}