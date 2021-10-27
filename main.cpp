#include "soph_PGG.h"
using namespace std;

int main(int argc, char** argv){
	srand(time(NULL));
	double dens = 0.6;
	double r = 3.5;
	if(argc > 2){
		r =    atof(argv[1]);
		dens = atof(argv[2]);
	}
	printf("Now doing sophisticated PGG with r:%f, density:%f \n",r,dens);
	soph_PGG gameOBJ(r,dens);
	gameOBJ.game(false);

	return 0;
}