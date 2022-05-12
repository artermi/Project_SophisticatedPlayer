#include "soph_PGG.h"
using namespace std;

void soph_PGG::build_specials(){
	memset(dir_name,'\0',sizeof(dir_name));
	strcpy(dir_name,"Org");
}


soph_PGG::soph_PGG(const double rate,const double dens, const double cost){
	r = rate;
	d = dens;
	c = cost;
	above_level = true;

	num_player = (int) (LL * dens);
	Strategy = new int[LL];
	Where = new int[num_player];
	WhichOne = new int[LL];
	Empty = new int[LL - num_player];
	for(int i = 0; i < 4; i++)
		Cate_Player[i] = 0;

	for(int i = 0; i < LL; i++){
		Strategy[i] = (i < num_player) ? i % 2: -1;
		if(i < num_player)
			Cate_Player[i % 2] ++; //How many players play stategy (i % 4)
	}

	/* if x % 2 == 0: defector (0,2) else cooperator (1,3)
	   if x / 2 == 0: fixer (0,1) else mover (2,3)
	*/



	// Initialize the where is the player[i]
	int* temp_Where = new int[LL];
	for(int i = 0; i < LL; i++)
		temp_Where[i] = i;

	for (int i = 0; i < LL; i++){
		int rdm = (rand() % (LL - i)) + i;
		swap(temp_Where[i],temp_Where[rdm]);
	}
	for (int i = 0; i < num_player; ++i)
		Where[i] = temp_Where[i];
	delete [] temp_Where;

	// Indicate which plaer is on place[i]
	for(int i = 0; i < LL; ++i)
		WhichOne[i] = -1;
	for (int i = 0; i < num_player; ++i)
		WhichOne[Where[i]] = i;

	int dummy_j = 0;
	for (int i = 0; i < LL; ++i)
		if(WhichOne[i] == -1)
			Empty[dummy_j++] = i;

	//About the Neighobur Setting, this should not be Alter
	Neighbour = new int *[LL];
	for(int i = 0; i < LL; i++)
		Neighbour[i] = new int[4];
	for(int i = 0; i < LL; i++){
		Neighbour[i][0] = (i - L + LL ) % LL; //North
		Neighbour[i][1] = (i + L) % LL;
		Neighbour[i][2] = (i + 1) % LL;
		Neighbour[i][3] = (i - 1 + LL) % LL;
	}

	build_specials();
}

soph_PGG::~soph_PGG(){
	delete [] Strategy;
	delete [] Where;
	delete [] WhichOne;
	delete [] Empty;
	for(int i = 0; i < LL; i++){
		delete [] Neighbour[i];
	}
	delete [] Neighbour;

}

double soph_PGG::unit_game(const int cent){ // location
	
	if(WhichOne[cent] == -1)
		return 0.0;

	double contrib = (double) (Strategy[WhichOne[cent]] % 2);

	double p_number = 1.0;
	for(int i = 0; i < 4; i++){
		int person = WhichOne[Neighbour[cent][i]];
		if (person == -1)
			continue;
		
		contrib += (double) (Strategy[person] % 2);
		p_number += 1.0;
	}

	return (contrib * r) / p_number;
}


double soph_PGG::centre_game(const int cent){
	// Note cent is the location
	double profit = unit_game(cent) - (double)(Strategy[WhichOne[cent]] % 2);
	for(int i = 0; i < 4; i++){
		profit += unit_game(Neighbour[cent][i]);
		profit -= (WhichOne[Neighbour[cent][i]] == -1) ? 0: (double)(Strategy[WhichOne[cent]] % 2);
	}

	return profit -= ( Strategy[WhichOne[cent]] / 2 == 0) ? 0 : c;
}

bool soph_PGG::have_neighbour(int place){
	for(int i = 0; i < 4; i++)
		if(WhichOne[Neighbour[place][i]] != -1)
			return true;
	return false;
}



void soph_PGG::leave(int ppl){
	if(LL - num_player <= 0)
		return;

	int coor_level = 0;
	int num_ppl = 0;
	for(int i = 0; i < 4; i++){
		int nei = Neighbour[Where[ppl]][i];
		if(WhichOne[nei] != -1){
			coor_level += Strategy[WhichOne[nei]] % 2;
			num_ppl ++;
		}
	}

	if(coor_level * 2 >=  num_ppl && num_ppl != 0){

		return;
	}


	int empty_index = rand() % (LL - num_player);
	int next_place = Empty[empty_index];

	Empty[empty_index] = Where[ppl]; //this person's original place is empty now
	WhichOne[Where[ppl]] = -1; // Now, nobody is on this position

	WhichOne[next_place] = ppl; // Next place is occupied by p_y
	Where[ppl] = next_place; //And indicate where is p_y now.


}

int soph_PGG::game(bool ptf){
	FILE *file;
	if(ptf){
		char path[100];
		//char dirt[100];
		//sprintf(dirt,"%s_%03d",dir_name, (int)(d*100));
		sprintf(path,"dns_%03d_r_%04d_c_%04d.dat", (int)((d+0.00001)*100), (int)((r +0.000001)*1000), (int)((c +0.00001)*1000));
		printf("Now file:%s\n",path);
		//mkdir(dirt,0700);
		file = fopen(path,"w+");
	}
	int itr = 20000;

	double exrate[4][4];
	for(int i = 0; i < 4; i++){
		for(int j = 0; j< 4; j++)
			exrate[i][j] = -0.1;
	}
	double rate[4] ={0.0, 0.0, 0.0, 0.0};
	bool stop_all2 = false;
	for(int i = 0; i < itr + 1; i++){

		if(i % 500 == 0){
			for (int j = 0; j < 4; ++j)
				rate[j] = (double) Cate_Player[j] / (double) num_player;

			if(ptf)
				fprintf(file, "%06d %.3f %.3f %.3f %.3f\n",i,rate[0],rate[1],rate[2],
					rate[3]);
			printf("%06d %.3f %.3f %.3f %.3f\n",i,rate[0],rate[1],rate[2],
					rate[3]);

		}
		if(i == itr){	//remember to remove
			FILE *file2;
			char path2[100];
			sprintf(path2,"SNAP_dns_%03d_r_%04d_t_%03d_a.dat", (int)((d+0.00001)*100), (int)((r +0.000001)*1000), (int)(c+0.00001) );

			
			printf("Now file:%s\n",path2);
			file2 = fopen(path2,"w+");
			for(int j = 0; j < LL; j++){
				int now_strag = (WhichOne[j] == -1) ? 5: Strategy[WhichOne[j]];

				fprintf(file2, "(%d,%d) %d\n", j % L, j / L, now_strag);
			}

			fclose(file2);
			if(i == 100)
				break;
		
		}

		bool stop_all = true;

		for (int j = 0; j < 4; j++)
			if(rate[j] - 0.00000001 >= 0 && rate[j] + 0.00000001 <= 1)
				stop_all = false;
		//Update
		if(i % 500 == 0){
			stop_all2 = true;
			for(int j = 1; j < 4; j++)
				for(int k = 0; k < 4; k++)
					exrate[j - 1][k] = exrate[j][k];
			for(int k = 0; k< 4; k++)
				exrate[3][k] = rate[k];

			for(int j = 1; j < 4; j++)
				for (int k = 0; k < 4; ++k)
				{
					if(rate[k] - exrate[j][k] >= eps || exrate[j][k] - rate[k] >= eps)
						stop_all2 = false;
				}
		}
		if(stop_all || stop_all2)
			continue;
		
		for(int j = 0; j < LL; j++){
			int p_x = rand() % num_player;
			int x = Where[p_x];

			if(Strategy[p_x] / 2 == 1){ //Sophisticated without neighbour
				leave(p_x);
				x = Where[p_x];
				if(!have_neighbour(x)) // if still no neighbour
					continue;
			}

			int y = Neighbour[x][ rand() % 4 ];
			int p_y = WhichOne[y];

			if(p_y == -1) // if place y is empty, just continue
				continue;

			if(Strategy[p_x] == Strategy[p_y]) //No need for same strategy
				continue;

			double x_earn = centre_game(x);
			double y_earn = centre_game(y);

			if ((double)rand()/(double)RAND_MAX < 1.0/( 1.0 + exp( (x_earn - y_earn)/K) ) ){
				Cate_Player[Strategy[p_x]] --;
				Strategy[p_x] = Strategy[p_y];
				Cate_Player[Strategy[p_x]] ++;
			}

		}
	}




	if(ptf)
		fclose(file);

	return 0;
}
