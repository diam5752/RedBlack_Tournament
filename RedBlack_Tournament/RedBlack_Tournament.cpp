#include <time.h>       /* time */
#include "stdafx.h"
#include "RBtree.h"

void print_tree_helper(node n, int indent);

void print_tree(rbtree& t);

void Rmax(rbtree &t);

int compare_int(int leftp, int rightp);

void find_maxima(vector<node*> &v);

void example_function(RBTree & rbt, rbtree & t) {  // sinartisi me tixaies korifes, wste na simvainei i periptwsi pou 
												   // to y tou pio aristerou leaf sto dentro , nikaei to tournament

	int i;
	srand(40); // random arithmoi, alla idioi kathe fora gia na exoume sigkerkimeno provlima ( auto tha allaksei sta peiramata )

	for (i = 0; i < NUM_OF_POINTS; i++)
	{
		int x = rand() % 100 + 1;  // random arithmoi x >0 && <100
		int y = rand() % 100 + 1;  // random arithmoi y >0 && <100  
		int yvalue;

		if (x == 1) {            // eidiki peiriptwsi gia na nikisei to tournament, i pio aristeri korifi ( to y tis na ftasei sto root)
			yvalue = 100;
		}
		else {
			yvalue = rand() % 100 + 1;  // oles oi alles korifes tha exoun y<100 enw i pio aristeri tha exei y = 100
		}


		cout << "Inserting  (" << x << "," << yvalue << ")     with id :" << y << endl << endl;  // ektipwnw tis korifes pou mpainoun sto dentro
		rbt.rbtree_insert(t, x, y, yvalue, compare_int); // vazw tis korifes sto dentro, kanontas ta aparaitita rotations gia na erthei isoropia


														 //assert(rbt.rbtree_lookup(t, x, compare_int) == y); 
														 //	print_tree(t);
	}
}


int main()
{

	RBTree rbt; // neo dentro
	rbtree t = rbt.rbtree_create();  //i korifi tou dentrou 

	example_function(rbt, t);  //example apo dimiourgeia dentrou . Arxika mpainoun korifes me x,y se red-black tree morfi
	print_tree(t);  // ektipwsi dentrou 
	rbt.tournament(t);  // kanoume tournament sto dentro me skopo to megalitero y na paei stin korifi

	print_tree(t); // ektipwsi dentrou , me ta nea y pou proekipsan meta to tournament

	Rmax(t);  //vriskoume ta maxima . Vlepe RBtree.cpp gia analitiki epeksigisi tis sinartisis


	return 0;
}


