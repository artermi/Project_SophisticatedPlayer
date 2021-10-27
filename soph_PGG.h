#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>


#define K 0.5
#define L 200
#define LL (L * L)

class soph_PGG{
public:
	double r;
	double d;
	char dir_name[100];

	int* Strategy;
	int* Where;
	int* WhichOne;
	int* Empty;
	int** Neighbour;
	int num_player;

	void build_specials();
	soph_PGG(const double rate, const double dens);
	double unit_game(const int cent);
	double centre_game(const int cent);
	bool have_neighbour(int place);
	void leave(int ppl);
	int game(bool ptf);
};