#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include <sys/types.h>


#define K 0.5
#define L 400
#define LL (L * L)
#define eps 0.001

class soph_PGG{
public:
	double c;
	double r;
	double d;
	char dir_name[100];
	bool above_level;

	int Cate_Player[4];
	int* Strategy;
	int* Where;
	int* WhichOne;
	int* Empty;
	int** Neighbour;
	int num_player;

	void build_specials();
	soph_PGG(const double rate, const double dens, const double cost);
	~soph_PGG();
	double unit_game(const int cent);
	double centre_game(const int cent);
	bool have_neighbour(int place);
	void leave(int ppl);
	int game(bool ptf);
};
