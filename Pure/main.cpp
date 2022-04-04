#include "soph_PGG.h"
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
using namespace std;

int main(int argc, char** argv){
	printf("%d\n",getpid());
	srand( (unsigned) (getpid()  * 1000));

//	double dens = 0.98;
//	double r = 3.0;
	double c = 0.00;
//	if(argc > 2){
//		r =    atof(argv[1]);
//		dens = atof(argv[2]);
//	}
	for (double dens = 0.2; dens < 1.001; dens += 0.02){
		for(double r = 3; r < 5; r +=0.1){

			int rand_sleep = rand() % 1000;

			usleep(rand_sleep*3000);

			char file_name [50];
			sprintf (file_name, "dns_%03d_r_%04d_c_%04d.dat",
				(int)((dens+0.00001)*100), (int)((r +0.000001)*1000), (int)((c +0.00001)*1000));

		  FILE *file;
		  file = fopen(file_name, "r");
   		if (file) {
      	fclose(file);
      	printf("file:'%s' exists\n",file_name);
      	continue;
   		}

			printf("Now doing sophisticated PGG with r:%f, density:%f, cost:%f\n",r,dens,c);
			soph_PGG gameOBJ(r,dens,c);
			gameOBJ.game(true);
		}
	}

	return 0;
}
