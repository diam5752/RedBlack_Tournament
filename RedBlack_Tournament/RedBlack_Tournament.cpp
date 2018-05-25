#include <time.h>       /* time */
#include "stdafx.h"
#include "RBtree.h"
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>


#define INPUT_NUM 1000
#define X_RANGE 2000
#define Y_RANGE 2000
#define RAND_SEED 10

vector<float > global_input;

void print_vec(vector<float>& in ) {
	for (int i = 0; i < in.size(); i++) {
		cout << " in[" << i << "]  = " << in[i] << endl;
	}
}

void print_tree_helper(node n, int indent);

void print_tree(rbtree& t);

vector < rbtree_node* >  Rmax(rbtree &t);

float compare_int(float leftp, float rightp);

void example_function(RBTree & rbt, rbtree & t , vector<float> & vec) {  // sinartisi me tixaies korifes, wste na simvainei i periptwsi pou 
												   // to y tou pio aristerou leaf sto dentro , nikaei to tournament

	int i;
	srand(RAND_SEED);


	for (i = 0; i < vec.size() -1; i++)
	{

		float x = vec[i];
		float y = (float) ( rand() % Y_RANGE + 1 );  // random arithmoi y >0 && <100  
		float x_dummy;

		
			x_dummy = (float) (rand() % X_RANGE + 1);  // oles oi alles korifes tha exoun y<100 enw i pio aristeri tha exei y = 100
			

		if (  i%2 != 0 && i != vec.size() - 1 ) {
			x_dummy = 1;         // this means x is dummy value 
		}
		else {
			x_dummy = -1;         // this means x is not a dummy
		}


		if ( x_dummy == -1) {
			cout << "                             Inserting  (" << x << "," << y << ")  " << endl << endl;  // ektipwnw tis korifes pou mpainoun sto dentro
			
			global_input.push_back(x);
			global_input.push_back(y);

		}
		else {
			cout << " Inserting  (" << x << "," << y << ")  " << endl << endl;
		}

		rbt.rbtree_insert(t, x, x_dummy, y, compare_int); // vazw tis korifes sto dentro, kanontas ta aparaitita rotations gia na erthei isoropia


														 //assert(rbt.rbtree_lookup(t, x, compare_int) == y); 
														 //print_tree(t);
	}
}

void export_points_to_graph(vector <rbtree_node*> maxima) {

	fstream inFile , labelFile;
	ofstream outFile , outLabel;

	outLabel.open("out_test.txt");
	inFile.open("test.grf");
	outFile.open("out_test.grf");
	

	outLabel.clear();
	outFile.clear();


	std::string line;
	while (std::getline(inFile, line))
	{

		std::istringstream iss(line);
		std::string token;
		while (std::getline(iss, token, '='))
		{
			if (line[0] == 'P'  && line[5] != 'S') {

				if (token[0] != 'P') {

					token.clear();
					int i;
					for (i = 0; i < global_input.size(); i = i + 2) {
						//cout <<" x = " <<global_input[i] << "   y = " << global_input[i+1] << endl;
						token.append(to_string((int)global_input[i]));
						token.append(",");
						token.append(to_string((int)global_input[i + 1]));
						token.append(";");

						if (i == global_input.size() - 2) {
							token.append("\n");
						}

					}


					outFile << token;
					continue;
				}
				outFile << line;
				continue;
			}

		}
		if (line != "Points = ") {
			outFile << line << endl;
		}

	}

	std::string lineLabel;
	
	string to_file;

	for (int j = 0; j < maxima.size(); j++) {
		
		int i = 0;
		labelFile.open("label.txt");
		//cout << to_file << endl;
		
		while (std::getline(labelFile, lineLabel))
		{
			
			i++;
			if( i ==1 ){
				//outLabel << "[Label" << i << "]" << endl;
				to_file = to_file + "\n"+ "[Label" + to_string(j) + "]" + "\n";
			}

			else if (i == 3) {
				string Pos;
				if ( maxima[j]->x_dummy!=-1 ) {
					Pos = "Pos = " + to_string( maxima[j]->x_dummy -1) + ";" + to_string( maxima[j]->y +2.2);
				}
				else {
					Pos = "Pos = " + to_string( maxima[j]->x -1) + ";" + to_string( maxima[j]->y +2.2 );
				}
				to_file = to_file + Pos + "\n";
				//outLabel << Pos << endl;
				//continue;
			}
			else {
				to_file = to_file + lineLabel + "\n";
			}
			//outLabel << lineLabel << endl;
		}

		labelFile.close();
		
	}
	
	outFile.close();
	outFile.open("out_test.grf", std::ios::app);
	outFile << to_file << endl;

	//cout << to_file << endl;
	

	outLabel.close();
	inFile.close();
	outFile.close();
}

/*
 * Takes Raw input . Random or from User and returns a vector containing them.
 */
vector<float> take_raw_input(){
	cout << "---- take_raw_input() -----" << endl;
	cout << " 1. Random input " << endl << " 2. User input " << endl;
	int chooser;
	srand(RAND_SEED);
	vector<float> raw_input;

	//cin >> chooser;
	chooser = 1;
	
	if (chooser == 1)
	{

		for (int i = 0; i < INPUT_NUM; i++) {
			float v1 = (float) (rand() % X_RANGE );   // initially integer, must change it to float  *issue
			int chooser = 0 ;

			for (int j = 0; j < raw_input.size();j++) {
				if ( raw_input[j] == v1) {
					chooser = -1;
				}
			}
			if (chooser == 0) {
				cout << "***************** inserting ... " << v1 << endl;
				raw_input.push_back(v1);
			}
			
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

	vector < rbtree_node* >  Maxima;
	vector<float> in = take_raw_input();
	vector<float> in_modified = manage_input(in);

	print_vec( in_modified );

	example_function(rbt, t , in_modified);  //example apo dimiourgeia dentrou . Arxika mpainoun korifes me x,y se red-black tree morfi
	print_tree(t);  // ektipwsi dentrou 

	rbt.tournament(t);  // kanoume tournament sto dentro me skopo to megalitero y na paei stin korifi

	print_tree(t); // ektipwsi dentrou , me ta nea y pou proekipsan meta to tournament

	Maxima = Rmax(t);  //vriskoume ta maxima . Vlepe RBtree.cpp gia analitiki epeksigisi tis sinartisis

	rbt.verify_properties(t);                                                                    

	export_points_to_graph(  Maxima);
	system( "out_test.grf" );

	return 0;
}
