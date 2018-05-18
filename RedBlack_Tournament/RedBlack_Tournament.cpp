#include <time.h>       /* time */
#include "stdafx.h"
#include "RBtree.h"

#define INPUT_NUM 5

void print_vec(vector<float>& in ) {
	for (int i = 0; i < in.size(); i++) {
		cout << " in[" << i << "]  = " << in[i] << endl;
	}
}

void print_tree_helper(node n, int indent);

void print_tree(rbtree& t);

void Rmax(rbtree &t);

float compare_int(float leftp, float rightp);

void find_maxima(vector<node*> &v);

void example_function(RBTree & rbt, rbtree & t , vector<float> & vec) {  // sinartisi me tixaies korifes, wste na simvainei i periptwsi pou 
												   // to y tou pio aristerou leaf sto dentro , nikaei to tournament

	int i;
	srand(14); // random arithmoi, alla idioi kathe fora gia na exoume sigkerkimeno provlima ( auto tha allaksei sta peiramata )

	// seed 40 i was using for recent examples  ,  43

	for (i = 0; i < vec.size() ; i++)
	{
		//int x = rand() % 100 + 1;  // random arithmoi x >0 && <100

		float x = vec[i];
		float y = (float) ( rand() % 100 + 1 );  // random arithmoi y >0 && <100  
		float x_dummy;

		if (x == 1) {            // eidiki peiriptwsi gia na nikisei to tournament, i pio aristeri korifi ( to y tis na ftasei sto root)
			y = 100;
		}
		else {
			x_dummy = (float) (rand() % 100 + 1);  // oles oi alles korifes tha exoun y<100 enw i pio aristeri tha exei y = 100
		}

		if (  i%2 != 0 && i != vec.size() - 1 ) {
			x_dummy = 1;         // this means x is dummy value 
		}
		else {
			x_dummy = -1;         // this means x is not a dummy
		}


		if ( x_dummy == -1) {
			cout << "                             Inserting  (" << x << "," << y << ")  " << endl << endl;  // ektipwnw tis korifes pou mpainoun sto dentro
		}
		else {
			cout << " Inserting  (" << x << "," << y << ")  " << endl << endl;
		}
		rbt.rbtree_insert(t, x, x_dummy, y, compare_int); // vazw tis korifes sto dentro, kanontas ta aparaitita rotations gia na erthei isoropia


														 //assert(rbt.rbtree_lookup(t, x, compare_int) == y); 
														 //print_tree(t);
	}
}


/*
 * Takes Raw input . Random or from User and returns a vector containing them.
 */
vector<float> take_raw_input(){
	cout << "---- take_raw_input() -----" << endl;
	cout << " 1. Random input " << endl << " 2. User input " << endl;
	int chooser;
	srand(1);  
	vector<float> raw_input;

	//cin >> chooser;
	chooser = 1;
	
	if (chooser == 1)
	{

		for (int i = 0; i < INPUT_NUM; i++) {
			float v1 = (float) (rand() % 100 );   // initially integer, must change it to float  *issue
			//cout << " inserting ... " << v1 << endl;
			raw_input.push_back(v1);
		}
	}
	return raw_input;
}

void add_dummies(vector<float>& in, int i , float dummy_factor ) {

	//cout << "---- add_dummies ----" << endl;

	
	float dummy_val = dummy_factor + in[i];

	if (dummy_val != in[i + 1] ) {
		in.push_back(dummy_val);
		//cout << " adding ... " << dummy_val << endl;
	}
	else {
		dummy_factor = (float) (dummy_factor * 0.1);
		add_dummies(in, i, dummy_factor);
	}
	

}

/*
 * Takes a vector with Raw input , and manages it . Meaning, it sorts it and add the dummy x_dummys that we need to help us 
 * balance the red-black with the info we want in the leaves.
*/
vector<float> manage_input( vector<float>& in ) {
	
	//cout << " ---- manage_input(vector<float> in) ----" << endl;
	
	int in_size = (int)in.size();
	float dummy_factor = 0.5;

	float max = *max_element(in.begin(), in.end());
	//cout << "Max x_dummy: " << max << endl;
	//cout << " size = " << in_size << endl;   // *issue   if i want slightly better time, instead of calculate in_size, go with the defined:INPUT_NUM 

	std::sort(in.begin(), in.end() );

	for (int i = 0; i < in_size-1 ; i++ ) {
		
		add_dummies(  in , i , dummy_factor);

	}

	std::sort(in.begin(), in.end());

	return in;
}

int main()
{
	 
	RBTree rbt; // neo dentro
	rbtree t = rbt.rbtree_create();  //i korifi tou dentrou 

	vector<float> in = take_raw_input();
	vector<float> in_modified = manage_input(in);

	print_vec( in_modified );

	example_function(rbt, t , in_modified);  //example apo dimiourgeia dentrou . Arxika mpainoun korifes me x,y se red-black tree morfi
	print_tree(t);  // ektipwsi dentrou 

	rbt.tournament(t);  // kanoume tournament sto dentro me skopo to megalitero y na paei stin korifi

	print_tree(t); // ektipwsi dentrou , me ta nea y pou proekipsan meta to tournament

	Rmax(t);  //vriskoume ta maxima . Vlepe RBtree.cpp gia analitiki epeksigisi tis sinartisis

	rbt.verify_properties(t);                                                                    


	return 0;
}


// na tsekarw periptwsi pou to olo deksia einai to mono maxima. Mpainei oles tis fores sto vector
// seed 12  ( what to do when same y)
// seed 17 little bug with root node