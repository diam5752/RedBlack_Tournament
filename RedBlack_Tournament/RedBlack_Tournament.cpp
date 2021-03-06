#include <time.h>       /* time */
#include "stdafx.h"
#include "RBtree.h"
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <Windows.h>
#include <chrono>
#include <iomanip>


#define INPUT_NUM 15   //1000
#define X_RANGE 20       //100
#define Y_RANGE 20      //100
#define RAND_MAX 36000 //rand() max value
#define RAND_SEED 19    //18
#define TEST_NUMBER 1

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

float bigInt_extender(int range) {

	float big;
	if ( range > RAND_MAX) {
		int mod = (int) (range / RAND_MAX);
		big = rand() % RAND_MAX;

		for (int i = 0; i < rand()%mod ; i++) {

			big = big + rand() % ((int)((float)range - big));
		}
	}
	else {
		big = rand() % range;
	}
	return big;
}

void example_function(RBTree & rbt, rbtree & t , vector<float> & vec) {  // sinartisi me tixaies korifes, wste na simvainei i periptwsi pou 
												   

	int i;
	//srand(RAND_SEED);

	for (i = 0; i < vec.size() -2; i++)
	{

		float x = vec[i];
		float y = bigInt_extender(Y_RANGE);  
		float x_dummy;

		
			x_dummy = (float) (rand() % X_RANGE + 1);  
			

		if (  i%2 != 0 && i != vec.size() - 1 ) {
			x_dummy = 1;         // this means x is dummy value 
		}
		else {
			x_dummy = -1;         // this means x is not a dummy
		}


		if ( x_dummy == -1) {
		//	cout << "                             Inserting  (" << x << "," << y << ")  " << endl << endl;  // ektipwnw tis korifes pou mpainoun sto dentro
			
			global_input.push_back(x);
			global_input.push_back(y);

		}
		else {
		//	cout << " Inserting  (" << x << "," << y << ")  " << endl << endl;
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

vector<float> take_raw_input(){
	//cout << "---- take_raw_input() -----" << endl;
	//cout << " 1. Random input " << endl << " 2. User input " << endl;
	int chooser;

	
	srand(RAND_SEED);
	vector<float> raw_input;

	//cin >> chooser;
	chooser = 1;
	
	if (chooser == 1)
	{

		for (int i = 0; i < INPUT_NUM; i++) {
			//float v1 = (float) (rand() % X_RANGE ) ;   // initially integer, must change it to float  *issue
			float v1 = bigInt_extender( X_RANGE);
			
			int chooser = 0 ;

			for (int j = 0; j < raw_input.size();j++) {
				if ( raw_input[j] == v1) {
					chooser = -1;
				}
			}
			if (chooser == 0) {
				//cout << "***************** inserting ... " << v1 << endl;
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

void print_Rmax(vector < rbtree_node* > maxima) {

	std::reverse(maxima.begin(), maxima.end());

	std::cout << "----------------------------------- My implementation -----------------------------------" << endl;
	for (int i = 0; i < maxima.size(); i++) {

		if (maxima[i]->x_dummy != -1) {
				cout << "x = " << maxima[i]->x_dummy << " maximal! "<<"   y = "<< maxima[i]->y << endl;
		}
		else {
				cout << "x ="<< maxima[i]->x << " maximal! " << endl;
		}
	}
}

vector< float > brute_force(vector<float> input) {

//	std::cout << "---------------------------------- brute force -----------------------------------" << std::endl;

	vector< float > maximal;
	//std::reverse(input.begin(), input.end());
	print_vec(input);
	int maxima = 0;
	int checker = 1;

	for (int i = 0; i < input.size() - 1; i = i+2 ) {
		int  x_current = input[i];
		int  y_current = input[i + 1];
		
		//std::cout << "                                                  x_current = " << x_current << "    y_current = " << y_current << endl;

		for (int j = 0; j < input.size()-1; j = j +2){
		
			int x_rest = input[j];
			int y_rest = input[j + 1];

			//std::cout << " x = " << x_rest << "    y = " << y_rest << endl;

			if ( ( x_current >= x_rest || y_current >= y_rest)  && checker == 1 ) {
				if (  x_current == x_rest ) {
					if ( y_current != y_rest ) { maxima = 1; }
					else { maxima = 0; }
				}
				else if ( y_current == y_rest) {
					if (x_current != x_rest) { maxima = 1; }
					else { maxima = 0; }
				}
			}
			else {
				maxima = 0;
				checker = 0;  //version 1 , i pio xronovora. Xwris checker einai i veltistopoiimeni brute force. Me checker einai i kanoniki, pio argi. 
				//break;
			}
		}

	if( maxima == 1){
		maximal.push_back(input[i+1]);
		//cout << " x = " << input[i+1] << " maximal!" << endl;
		}

	maxima = 0;
	checker = 1;
	}

	return maximal;
}

vector< float > brute_force_optimized(vector<float> input) {

	vector< float > maximal ;
	std::reverse(input.begin(), input.end());
	//print_vec(input);
	int maxima = 0;

	std::cout << "---------------------------------- brute force optimized -----------------------------------" << std::endl;
	for (int i = 0; i < input.size() - 1; i = i + 2) {
		int  y_current = input[i];
		int x_current = input[i + 1];

		std::cout << "                                                  x_current = " << x_current << "    y_current = " << y_current << endl;

		for (int j = 0; j < input.size() - 1; j = j + 2) {

			int y_rest = input[j];
			int x_rest  = input[j + 1];

			std::cout << " x = " << x_rest << "    y = " << y_rest << endl;

			if ( (x_current > x_rest || y_current > y_rest) ) {
				maxima = 1;
			}
			else {
				maxima = 0;
				if (x_current == x_rest && y_current == y_rest) {
					maxima = 1;
				}
				break;
			}
		}

		if (maxima == 1) {
			maximal.push_back(input[i + 1]);
			//cout << " x = " << input[i + 1] << " maximal!" << endl;
		}
		maxima = 0;

	}
	return maximal;
}

void tester_core(vector<int>& results) {

	RBTree rbt; // neo dentro
	rbtree t = rbt.rbtree_create();  //i korifi tou dentrou 

	vector < rbtree_node* >  Maxima;
	vector<float> in = take_raw_input();
	vector<float> in_modified = manage_input(in);

	print_vec(in_modified);

	example_function(rbt, t, in_modified);  //example apo dimiourgeia dentrou . Arxika mpainoun korifes me x,y se red-black tree morfi
	print_tree(t);  // ektipwsi dentrou 

	rbt.tournament(t);  // kanoume tournament sto dentro me skopo to megalitero y na paei stin korifi

	print_tree(t); // ektipwsi dentrou , me ta nea y pou proekipsan meta to tournament

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	Maxima = Rmax(t);
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	print_Rmax(Maxima);

	rbt.verify_properties(t);

	export_points_to_graph(Maxima);


	std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();
	brute_force(global_input);
	std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();


	std::chrono::steady_clock::time_point begin3 = std::chrono::steady_clock::now();
	brute_force_optimized(global_input);
	std::chrono::steady_clock::time_point end3 = std::chrono::steady_clock::now();

	int RB_results = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
	int bruteforce_results = std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count();
	int bruteforceOpt_results = std::chrono::duration_cast<std::chrono::microseconds>(end3 - begin3).count();

	//std::cout << "elapsed time with red_black = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << std::endl;
	//std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << std::endl;

	//std::cout << "elapsed time with brute force = " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count() << std::endl;
	//std::cout << "Time difference2 = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end2 - begin2).count() << std::endl;

	//std::cout << "elapsed time with brute force optimized = " << std::chrono::duration_cast<std::chrono::microseconds>(end3 - begin3).count() << std::endl;
	//std::cout << "Time difference2 = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end2 - begin2).count() << std::endl;

	results.push_back(RB_results);
	results.push_back(bruteforce_results);
	results.push_back(bruteforceOpt_results);


}

void tester_helper(int reps, vector<int> & results) {

	
	for (int i = 0; i < reps; i++) {
		cout.setf(ios::fixed);
		system("cls");
		cout << endl << "                                               " << setprecision(1) << ( (float)(i + 1) * 100 / reps) << "%" << endl<<endl;
		tester_core(results);
		global_input.clear();
	}

	int RB_results = 0;
	int bruteforce_results = 0;
	int bruteforceOpt_results = 0;

	for (int i = 0; i < results.size(); i = i + 3) {
		RB_results = RB_results + results[i];
	}
	for (int i = 1; i < results.size(); i = i + 3) {
		bruteforce_results = bruteforce_results + results[i];
	}
	for (int i = 2; i < results.size(); i = i + 3) {
		bruteforceOpt_results = bruteforceOpt_results + results[i];
	}
	cout << endl << "*********************************************  TEST  ***************************************************" << endl << endl;;
	cout << "                                  -> number of experiments :  " << TEST_NUMBER << "                         " << endl;
	cout << "                                  -> number of points :  " << INPUT_NUM << "                         " << endl;
	cout << "                                  -> X range :  " << X_RANGE << "                         " << endl;
	cout << "                                  -> Y range :  " << Y_RANGE << "                         " << endl << endl;
	cout << " RB_results = " << (float)RB_results / TEST_NUMBER << endl;
	cout << " bruteforce_results = " << (long long)bruteforce_results / TEST_NUMBER << endl;
	cout << " bruteforceOpt_results = " << (float)bruteforceOpt_results / TEST_NUMBER << endl << endl;
	cout << "                                           performance increment %                                                   " << endl;
	cout << " VS bruteforce Opt= " <<  ( (float)bruteforceOpt_results - (float)RB_results )*100 / (float)RB_results <<"%" << endl << endl;
	cout << " VS bruteforce = " << ( (long long)bruteforce_results - (float)RB_results ) *100/ (float)RB_results  << "%" <<endl << endl;
	cout << "========================================================================================================" << endl << endl << endl;


	std::ofstream out;
	out.open("test_results.txt", std::ios::app);
	out << endl << "*********************************************  TEST  ***************************************************" << endl << endl;;
	out << "                                  -> number of experiments :  " << TEST_NUMBER << "                         " << endl;
	out << "                                  -> number of points :  " << INPUT_NUM << "                         " << endl;
	out << "                                  -> X range :  " << X_RANGE << "                         " << endl;
	out << "                                  -> Y range :  " << Y_RANGE << "                         " << endl << endl;
	out << " RB_results = " << (float)RB_results / TEST_NUMBER << endl;
	out << " bruteforce_results = " << (long long)bruteforce_results / TEST_NUMBER << endl;
	out << " bruteforceOpt_results = " << (float)bruteforceOpt_results / TEST_NUMBER << endl << endl;
	out << "                                           performance increment %                                                   " << endl;
	out << " VS bruteforce Opt= " << ((float)bruteforceOpt_results - (float)RB_results) * 100 / (float)RB_results << "%" << endl << endl;
	out << " VS bruteforce = " << ((long long)bruteforce_results - (float)RB_results) * 100 / (float)RB_results << "%" << endl << endl;
	out << "========================================================================================================" << endl << endl << endl;

}

void correctness_tester(vector < rbtree_node*> maxima , vector<float> brute_maxima) {
	cout << " >>>>>>>>>>>>>>>>>>>>>>  correctness " << endl;

	print_Rmax(maxima);
	cout << " --------------------------------------- " << endl;
	for (int i = 0; i < brute_maxima.size(); i++) {
		cout << "brut_maxima :  " << brute_maxima[i] << endl;
	}

	cout << " size of my_maximal = " << maxima.size() << endl;
	cout << " size of brut_maximal = " << brute_maxima.size() << endl;

}

int main()
{
	//vector<int> results;

	//tester_helper(TEST_NUMBER,results);

	//exit(0);


	RBTree rbt; // neo dentro
	rbtree t = rbt.rbtree_create();  //i korifi tou dentrou 

	vector < rbtree_node* >  Maxima;
	vector<float> in = take_raw_input();
	vector<float> in_modified = manage_input(in);
	vector <float> maximal_for_tester;

	print_vec( in_modified );

	example_function(rbt, t , in_modified);  //example apo dimiourgeia dentrou . Arxika mpainoun korifes me x,y se red-black tree morfi
	print_tree(t);  // ektipwsi dentrou 

	rbt.tournament(t);  // kanoume tournament sto dentro me skopo to megalitero y na paei stin korifi

	print_tree(t); // ektipwsi dentrou , me ta nea y pou proekipsan meta to tournament
	
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	Maxima = Rmax(t);  
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	print_Rmax(Maxima);

	rbt.verify_properties(t);                                                                    

	export_points_to_graph(Maxima);
	

	std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();
	brute_force(global_input);
	std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();


	std::chrono::steady_clock::time_point begin3 = std::chrono::steady_clock::now();
	brute_force_optimized(global_input);
	std::chrono::steady_clock::time_point end3 = std::chrono::steady_clock::now();
	

	std::cout << "elapsed time with red_black = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << std::endl;
	//std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << std::endl;

	std::cout << "elapsed time with brute force = " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count() << std::endl;
	//std::cout << "Time difference2 = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end2 - begin2).count() << std::endl;

	std::cout << "elapsed time with brute force optimized = " << std::chrono::duration_cast<std::chrono::microseconds>(end3 - begin3).count() << std::endl;
	//std::cout << "Time difference2 = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end2 - begin2).count() << std::endl;

	cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>> correctness checker " << endl;
	maximal_for_tester = brute_force_optimized(global_input);
	//correctness_tester(Maxima , maximal_for_tester);


	system("out_test.grf");

	return 0;
}
