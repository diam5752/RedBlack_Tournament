#include "stdafx.h"
#include "RBtree.h"


/*
* Return Grandparent of Node
*/
node RBTree::grandparent(node n)
{
	assert(n != NULL);
	assert(n->parent != NULL);
	assert(n->parent->parent != NULL);
	return n->parent->parent;
}

/*
* Return Sibling of Node
*/
node RBTree::sibling(node n)
{
	assert(n != NULL);
	assert(n->parent != NULL);
	if (n == n->parent->left)   // elegxei an einai aristero i deksi node
		return n->parent->right;
	else
		return n->parent->left;
}

/*
* Return Uncle of Node
*/
node RBTree::uncle(node n)
{
	assert(n != NULL);
	assert(n->parent != NULL);
	assert(n->parent->parent != NULL);
	return sibling(n->parent);
}

/*
* Verifying Properties of Red black Tree
*/
void RBTree::verify_properties(rbtree t)
{
	verify_property_1(t->root);
	verify_property_2(t->root);
	verify_property_4(t->root);
	verify_property_5(t->root);
}
/*
* Verifying Property 1
*/
void RBTree::verify_property_1(node n)
{
	assert(node_color(n) == RED || node_color(n) == BLACK);
	if (n == NULL)
		return;
	verify_property_1(n->left);
	verify_property_1(n->right);
}
/*
* Verifying Property 2
*/
void RBTree::verify_property_2(node root)
{
	assert(node_color(root) == BLACK);
}
/*
* Returns color of a node
*/
color RBTree::node_color(node n)
{
	return n == NULL ? BLACK : n->color;
}
/*
* Verifying Property 4
*/
void RBTree::verify_property_4(node n)
{
	if (node_color(n) == RED)
	{
		assert(node_color(n->left) == BLACK);
		assert(node_color(n->right) == BLACK);
		assert(node_color(n->parent) == BLACK);
	}
	if (n == NULL)
		return;
	verify_property_4(n->left);
	verify_property_4(n->right);
}
/*
* Verifying Property 5
*/
void RBTree::verify_property_5(node root)
{
	int black_count_path = -1;
	verify_property_5_helper(root, 0, &black_count_path);
}

void RBTree::verify_property_5_helper(node n, int black_count, int* path_black_count)
{
	if (node_color(n) == BLACK)
	{
		black_count++;
	}
	if (n == NULL)
	{
		if (*path_black_count == -1)
		{
			*path_black_count = black_count;
		}
		else
		{
			assert(black_count == *path_black_count);
		}
		return;
	}
	verify_property_5_helper(n->left, black_count, path_black_count);
	verify_property_5_helper(n->right, black_count, path_black_count);
}

/*
* Create Red Black Tree
*/
rbtree RBTree::rbtree_create()
{
	rbtree t = new rbtree_t;
	t->root = NULL;
	verify_properties(t);
	return t;
}

/*
* Creating New Node of Reb Black Tree
*/
node RBTree::new_node(float k, float v, float y, color n_color, node left, node right)
{
	node result = new rbtree_node;
	result->x = k;
	//cout << "----------------------------------------------->  result -> x = " << result->x << endl;
	result->x_dummy = v;
	//cout << "----------------------------------------------->  result -> x_dummy = " << result->x_dummy << endl;
	result->color = n_color;
	result->left = left;
	result->right = right;
	result->y = y;
	//cout << "----------------------------------------------->  result -> y = " << result->y << endl;
	if (left != NULL)
		left->parent = result;
	if (right != NULL)
		right->parent = result;
	result->parent = NULL;
	return result;
}
/*
* Look Up through Node
*/
node RBTree::lookup_node(rbtree t, float x, compare_func compare)
{
	node n = t->root;
	while (n != NULL)
	{
		float comp_result = compare(x, n->x);
		if (comp_result == 0)
		{
			return n;
		}
		else if (comp_result < 0)
		{
			n = n->left;
		}
		else
		{
			assert(comp_result > 0);
			n = n->right;
		}
	}
	return n;
}
/*
* RbTree Look Up
*/
float RBTree::rbtree_lookup(rbtree t, float x, compare_func compare)
{
	node n = lookup_node(t, x, compare);
	return n == NULL ? NULL : n->x_dummy;
}

/*
* Rotate left
*/
void RBTree::rotate_left(rbtree t, node n)
{
	node r = n->right;
	replace_node(t, n, r);
	n->right = r->left;
	if (r->left != NULL)
	{
		r->left->parent = n;
	}
	r->left = n;
	n->parent = r;
}
/*
* Rotate right
*/
void RBTree::rotate_right(rbtree t, node n)
{
	node L = n->left;
	replace_node(t, n, L);
	n->left = L->right;
	if (L->right != NULL)
	{
		L->right->parent = n;
	}
	L->right = n;
	n->parent = L;
}
/*
* Replace a node
*/
void RBTree::replace_node(rbtree t, node oldn, node newn)
{
	if (oldn->parent == NULL)
	{
		t->root = newn;
	}
	else
	{
		if (oldn == oldn->parent->left)
			oldn->parent->left = newn;
		else
			oldn->parent->right = newn;
	}
	if (newn != NULL)
	{
		newn->parent = oldn->parent;
	}
}
/*
* Insert node into RBTree
*/
void RBTree::rbtree_insert(rbtree t, float x, float x_dummy, float y, compare_func compare)
{
	node inserted_node = new_node(x, x_dummy, y, RED, NULL, NULL);
	if (t->root == NULL)
	{
		t->root = inserted_node;
	}
	else
	{
		node n = t->root;
		while (1)
		{
			float comp_result = compare(x, n->x);
			if (comp_result == 0)
			{
				n->x_dummy = x_dummy;
				return;
			}
			else if (comp_result < 0)
			{
				if (n->left == NULL)
				{
					n->left = inserted_node;
					break;
				}
				else
				{
					n = n->left;
				}
			}
			else
			{
				assert(comp_result > 0);
				if (n->right == NULL)
				{
					n->right = inserted_node;
					break;
				}
				else
				{
					n = n->right;
				}
			}
		}
		inserted_node->parent = n;
	}
	insert_case1(t, inserted_node);
	verify_properties(t);
}

/*
* Inserting Case 1
*/
void RBTree::insert_case1(rbtree t, node n)
{
	if (n->parent == NULL)
		n->color = BLACK;
	else
		insert_case2(t, n);
}

/*
* Inserting Case 2
*/
void RBTree::insert_case2(rbtree t, node n)
{

	if (node_color(n->parent) == BLACK) {
		return;
	}
	else
		insert_case3(t, n);
}

/*
* Inserting Case 3
*/
void RBTree::insert_case3(rbtree t, node n)
{
	if (node_color(uncle(n)) == RED)
	{
		n->parent->color = BLACK;
		uncle(n)->color = BLACK;
		grandparent(n)->color = RED;
		insert_case1(t, grandparent(n));
	}
	else
	{
		insert_case4(t, n);
	}
}

/*
* Inserting Case 4
*/
void RBTree::insert_case4(rbtree t, node n)
{
	if (n == n->parent->right && n->parent == grandparent(n)->left)
	{
		rotate_left(t, n->parent);
		n = n->left;
	}
	else if (n == n->parent->left && n->parent == grandparent(n)->right)
	{
		rotate_right(t, n->parent);
		n = n->right;
	}
	insert_case5(t, n);
}

/*
* Inserting Case 5
*/
void RBTree::insert_case5(rbtree t, node n)
{
	n->parent->color = BLACK;
	grandparent(n)->color = RED;
	if (n == n->parent->left && n->parent == grandparent(n)->left)
	{
		rotate_right(t, grandparent(n));
	}
	else
	{
		assert(n == n->parent->right && n->parent == grandparent(n)->right);
		rotate_left(t, grandparent(n));
	}
}

/*
* Delete Node from RBTree
*/
void RBTree::rbtree_delete(rbtree t, float x, compare_func compare)
{
	node child;
	node n = lookup_node(t, x, compare);
	if (n == NULL)
		return;
	if (n->left != NULL && n->right != NULL)
	{
		node pred = maximum_node(n->left);
		n->x = pred->x;
		n->x_dummy = pred->x_dummy;
		n = pred;
	}
	assert(n->left == NULL || n->right == NULL);
	child = n->right == NULL ? n->left : n->right;
	if (node_color(n) == BLACK)
	{
		n->color = node_color(child);
		delete_case1(t, n);
	}
	replace_node(t, n, child);
	free(n);
	verify_properties(t);
}

/*
* Returns Maximum node
*/
node RBTree::maximum_node(node n)
{
	assert(n != NULL);
	while (n->right != NULL)
	{
		n = n->right;
	}
	return n;
}

/*
* Deleting Case 1
*/
void RBTree::delete_case1(rbtree t, node n)
{
	if (n->parent == NULL)
		return;
	else
		delete_case2(t, n);
}

/*
* Deleting Case 2
*/
void RBTree::delete_case2(rbtree t, node n)
{
	if (node_color(sibling(n)) == RED)
	{
		n->parent->color = RED;
		sibling(n)->color = BLACK;
		if (n == n->parent->left)
			rotate_left(t, n->parent);
		else
			rotate_right(t, n->parent);
	}
	delete_case3(t, n);
}

/*
* Deleting Case 3
*/
void RBTree::delete_case3(rbtree t, node n)
{
	if (node_color(n->parent) == BLACK && node_color(sibling(n)) == BLACK &&
		node_color(sibling(n)->left) == BLACK && node_color(sibling(n)->right) == BLACK)
	{
		sibling(n)->color = RED;
		delete_case1(t, n->parent);
	}
	else
		delete_case4(t, n);
}

/*
* Deleting Case 4
*/
void RBTree::delete_case4(rbtree t, node n)
{
	if (node_color(n->parent) == RED && node_color(sibling(n)) == BLACK &&
		node_color(sibling(n)->left) == BLACK && node_color(sibling(n)->right) == BLACK)
	{
		sibling(n)->color = RED;
		n->parent->color = BLACK;
	}
	else
		delete_case5(t, n);
}

/*
* Deleting Case 5
*/
void RBTree::delete_case5(rbtree t, node n)
{
	if (n == n->parent->left && node_color(sibling(n)) == BLACK &&
		node_color(sibling(n)->left) == RED && node_color(sibling(n)->right) == BLACK)
	{
		sibling(n)->color = RED;
		sibling(n)->left->color = BLACK;
		rotate_right(t, sibling(n));
	}
	else if (n == n->parent->right && node_color(sibling(n)) == BLACK &&
		node_color(sibling(n)->right) == RED && node_color(sibling(n)->left) == BLACK)
	{
		sibling(n)->color = RED;
		sibling(n)->right->color = BLACK;
		rotate_left(t, sibling(n));
	}
	delete_case6(t, n);
}

/*
* Deleting Case 6
*/
void RBTree::delete_case6(rbtree t, node n)
{
	sibling(n)->color = node_color(n->parent);
	n->parent->color = BLACK;
	if (n == n->parent->left)
	{
		assert(node_color(sibling(n)->right) == RED);
		sibling(n)->right->color = BLACK;
		rotate_left(t, n->parent);
	}
	else
	{
		assert(node_color(sibling(n)->left) == RED);
		sibling(n)->left->color = BLACK;
		rotate_right(t, n->parent);
	}
}





void RBTree::tournament(rbtree& t) {
	/*cout << "root = " << int(t->root->x) << endl;
	cout << "left = " << int(t->root->left->x) << endl;
	cout << "right = " << int(t->root->right->x) << endl;*/
	cout << " =========================== TOURNAMENT =========================== " << endl;
	tournament_helper(t->root);
	cout << " =================================================================== " << endl;
}

void RBTree::tournament_helper(node& n) {

	if (n == NULL)
	{
		fputs("<empty tree>", stdout);
		return;
	}

	if (n->right != NULL)
	{
		tournament_helper(n->right);
	}
	if (n->left != NULL)
	{
		tournament_helper(n->left);
	}
	cout << " n = " << n->x << "   y = " << n->y;
	//cout << "                                                                       edw  me n =  "<< (int)n->x <<"   y = " << (int)n->y<< endl;
	if (n->parent == NULL) {
		cout << "   case 0 " << endl;

		if (n->left != NULL && (n->y == n->left->y)) {
			n->path.push_back(*n);
			n->path.insert(n->path.end(), n->left->path.begin(), n->left->path.end());
		}
		else if (n->right != NULL && n->y == n->right->y) {
			n->path.push_back(*n);
			n->path.insert(n->path.end(), n->right->path.begin(), n->right->path.end());
		}
		else if (n->right == NULL && n->left == NULL) {
			n->path.push_back(*n);
		}

		return;
	}

	if (n->left == NULL && n->right == NULL && n->parent->left == NULL) {
		n->parent->y = n->y;
		cout << "   case 1 " << endl;

		n->path.push_back(*n);

		return;
	}
	else if (n->left == NULL && n->right == NULL && n->parent->right == NULL) {

		n->parent->y = n->y;
		cout << "   case 2 " << endl;
		return;
	}

	if (n->y >= n->parent->right->y && n->parent != NULL) {
		n->parent->y = n->y;

		if ( n->parent->is_dummy != -1 ) {
			if ( n->left ==NULL && n->right ==NULL ) {
				n->parent->x_dummy = n->x;
			}
			else {
				n->parent->x_dummy = n->x_dummy;
			}

			cout << "      parent dummy ->  " << n->x << "   " << endl;;
		}

		if (n->left != NULL && (n->y == n->left->y)) {
			n->path.push_back(*n);
			n->path.insert(n->path.end(), n->left->path.begin(), n->left->path.end());
		}
		else if (n->right != NULL && n->y == n->right->y) {
			n->path.push_back(*n);
			n->path.insert(n->path.end(), n->right->path.begin(), n->right->path.end());
		}
		else if (n->right == NULL && n->left == NULL) {
			n->path.push_back(*n);
		}

		cout << "   case 3 " << endl;
	}
	else {
		n->parent->y = n->parent->right->y;

		if (n->left != NULL && (n->y == n->left->y)) {
			n->path.push_back(*n);
			n->path.insert(n->path.end(), n->left->path.begin(), n->left->path.end());
		}
		else if (n->right != NULL && n->y == n->right->y) {
			n->path.push_back(*n);
			n->path.insert(n->path.end(), n->right->path.begin(), n->right->path.end());
		}
		else if (n->right == NULL && n->left == NULL) {
			n->path.push_back(*n);
		}

		cout << "   case 4 " << endl;
	}
}

/*
* Compare two nodes
*/
float compare_int(float leftp, float rightp)
{
	float left = leftp;
	float right = rightp;
	if (left < right)
		return -1;
	else if (left > right)
		return 1;
	else
	{
		assert(left == right);
		return 0;
	}
}

node* RBTree::dynamic_tournament(rbtree&t, float x, bool first) {
	node* p_leaf;
	node * ancestor = NULL;
	RBTree rbt;
	node n = rbt.lookup_node(t, x, compare_int);
	//node *pn = &n;
	//cout << "found node : " << (int)(*pn)->x << "," << (int)(*pn)->y << endl;
	//void *y = (*pn)->y;
	cout << "found node : " << n->x << "," << n->y << endl;

	clear_to_parent(t, n, first);
	p_leaf = clear_to_leaf(t, n);
	return p_leaf;
}

//katharizei apo tin korifi tis trixas mexri to node pou psaxnoume
void RBTree::clear_to_parent(rbtree &t, node n, bool first) {

	if (n->parent != NULL && n->parent->y == n->y) {
		//cout << " current n = " << n->x << endl;
		if (first != 1) {
			n->y = CLEAR_Y;
		}
		clear_to_parent(t, n->parent, 0);
		//cout << " parent is : " << n->parent->x << endl;
		n->parent->y = CLEAR_Y;
	}
}

node* RBTree::clear_to_leaf(rbtree &t, node n) {

	if (n->left != NULL && n->left->y == n->y) {
		//cout << " current n = " << n->x << endl;
		n->y = CLEAR_Y;
		clear_to_leaf(t, n->left);
		n->left->y = n->y;
		//cout << " left is : " << n->left->x << "   with y = " << (int)n->left->y << endl;
		return &(n->left);
	}
	else if (n->right != NULL && n->right->y == n->y) {
		//cout << " current n = " << n->x << endl;
		n->y = CLEAR_Y;
		clear_to_leaf(t, n->right);
		n->right->y = n->y;
		//cout << " right is : " << n->right->x << "   with y = " << (int)n->right->y << endl;
		return &(n->right);
	}

	else {
		//cout << "error happened ... returning 0 " << endl;
		return 0;
	}

}

void RBTree::re_tournament(rbtree &t, node &p_leaf, float new_y) {
	cout << " \n ========================================== \n returned : " << (int)(p_leaf)->x << endl;

	while ((p_leaf)->y == CLEAR_Y) {

		if ((p_leaf)->left == NULL && (p_leaf)->right == NULL) {  // prwti periptwsi
			(p_leaf)->y = new_y;
			cout << "first x_dummy =  " << (int)(p_leaf)->y << endl;
		}
		else if ((p_leaf)->left != NULL && (p_leaf)->right == NULL) {
			(p_leaf)->y = (p_leaf)->left->y;
			cout << "left x_dummy =  " << (p_leaf)->left << endl;    // (int) an dn doulevei
		}
		else if ((p_leaf)->left == NULL && (p_leaf)->right != NULL) {
			(p_leaf)->y = (p_leaf)->right->y;
			cout << "right x_dummy =  " << (int)(p_leaf)->right->y << endl;
		}
		else {
			if ((int)(p_leaf)->left->y >= (int)(p_leaf)->right->y) {

				(p_leaf)->y = (p_leaf)->left->y;
			}
			else {
				(p_leaf)->y = (p_leaf)->right->y;
			}

		}
		if ((p_leaf)->parent != NULL) {
			cout << " p_leaf  parent = " << (int)(p_leaf)->parent->x << endl;
			(p_leaf) = (p_leaf)->parent;
			cout << " p_leaf = " << (int)(p_leaf)->x << endl;
			cout << " p_leaf.left = " << (int)(p_leaf)->left->x << endl;
		}
	}

}


/*
* Print RBTRee
*/

void print_tree_helper(node n, int indent)
{
	for (std::vector<rbtree_node>::iterator it = (n->path).begin(); it != (n->path).end(); ++it) {
		//	cout << "for n = " << (int)n->x << "  path = " << (int)(*it).x << endl;
	}

	int i;
	if (n == NULL)
	{
		fputs("<empty tree>", stdout);
		return;
	}
	if (n->right != NULL)
	{
		print_tree_helper(n->right, indent + INDENT_STEP);
	}
	for (i = 0; i < indent; i++)
		fputs(" ", stdout);
	if (n->color == BLACK)  
	{
		cout << n->x << "                                              ( " << n->x << " , " << n->y << " )   dummmy x -> "<< n->x_dummy << endl;
	}
	else
	{
		cout << "<" << n->x << ">" << "                                              ( " << n->x << " , " << n->y << " )  dummy x -> "<< n->x_dummy << endl;
	}
	if (n->left != NULL)
	{
		print_tree_helper(n->left, indent + INDENT_STEP);
	}


}

void print_tree(rbtree& t)
{
	cout << " ========================================================== " << endl << endl;
	print_tree_helper(t->root, 0);

	puts("");
	cout << " ========================================================== " << endl;
}

void print_vec(vector<rbtree_node*>& in) {

	for (int i = 0; i < in.size(); i++) {
		cout << " (" << in[i]->x << " , " << in[i]->y << " ) " << endl;
	}

}


//void find_maxima(vector<node*> &v) {  // vriskw ta maxima apo array pou pairnei ws oris,a
//
//	cout << " item with biggest x : " << (*(v.front()))->x << endl;
//
//	vector<node*> v_max; // tha krataei ta maximal simeia
//
//	int v_size = v.size();
//	cout << "**************************************************************" << endl;
//	for (int i = 0; i < v_size; i++) {
//		int max_desc = 0; // an o ginei iso me ton arithmo twn komvwn, tote einai maximal to node pou koitame
//		cout << "--------------------------------------------------" << endl;
//		cout << "v[" << i << "]  = " << (*v[i])->x << endl; // ektipwsi pou mas voithaei na tsekaroume an einai swsta ta apotelesmata
//
//		for (int j = 0; j < v_size; j++) {  //ksekinaw ti diadikasia elegxou gia maxima. Arxika auti einai i kaki veltiwsi , kai tha 
//											// veltiwthei me xrisi partial queue with attrition
//
//			cout << " x = " << (*v[j])->x << "    y = " << (*v[j])->y << endl;
//			if (((*v[i])->x >= (*v[j])->x) || (((*v[i])->y) >= (*v[j])->y)) {
//				max_desc++;
//			}
//			else { max_desc = 0; }
//		}
//		cout << "                                               max_desc = " << max_desc << endl; // an max_desc isoutai me to megethos tis 
//																								  // v tote einai maxima to simeio
//		if (max_desc == v.size()) {  // an simvainei auto to simeio einai maxima , kai ara allazoume tin metavliti tou maximal se 1  
//			(*(v[i]))->maximal = 1;
//			v_max.push_back(v[i]); // o v_max krataei ta maxima simeia 
//		}
//	}
//
//	cout << "**************************************************************" << endl;
//	for (std::vector<node *>::iterator it = v_max.begin(); it != v_max.end(); ++it)
//	{
//		std::cout << ' ' << (*(*it))->x << " with n->maximal x_dummy = " << (*(*it))->maximal << endl;  // ektipwnoume ta maxima	
//																										// gia na doume an einai swsta ta apotelesmata
//	}
//}
//
//void Rmax(rbtree &t) {
//
//	cout << " -------------------  IN Rmax ------------------- " << endl;
//
//	cout << " root = " << t->root->x << endl;
//	node* p_leaf = &(t->root);  // pointer pou deixnei stin thesi mnimis tis korifis  tou dentrou. Sto telos tha deixnei sto leaf apo to
//								// opoio pire to y i riza tou dentrou
//	vector<node*> v;  // vector pou tha krataei ta Rmax . Ta deksia kremamena diladi, apo to winning path
//
//	while ((*p_leaf)->y == t->root->y) {   // arxika mono gia to paradeigma pou exw. Thelei genikopoiisi
//		cout << "p_leaf = " << (*p_leaf)->x << endl;
//
//		if ((*p_leaf)->right != NULL && (*p_leaf)->right->y != t->root->y) {
//			v.push_back(&(*p_leaf)->right);
//		}
//
//		if ((*p_leaf)->left != NULL) {
//			*p_leaf = (*p_leaf)->left;
//		}
//		else {
//			break;
//		}
//	}
//	for (std::vector<node *>::iterator it = v.begin(); it != v.end(); ++it)
//	{
//		std::cout << ' ' << (*(*it))->x;  // ektipwnw ta dekisa canditates, ta Rmax tou winning path
//	}
//	std::cout << endl;
//
//	cout << " LEAF OF ROOT IS ---> " << (*p_leaf)->x << endl;  // tsekarw an o pointer eftase ekei pou ithela, diladi sto leaf
//																	  // apo opou pire i riza to y tis. O deiktis menei ekei , kai tha mas xreiastei
//	find_maxima(v);  //stelnw stin sinartisi ton vector me ta Rmax, kai apo auta vriskw poia einai maxima.
//}

vector<rbtree_node*> maxima_in_vector(vector<rbtree_node*>& Rchild, vector<rbtree_node*>& Maximal) {

	cout << endl << endl << "=========================== maxima_in_vector  ========================== " << endl << endl;
	vector<rbtree_node*> Rmax;

	
	std::reverse(Rchild.begin(), Rchild.end());

	//cout << endl << " ------------ Rchild edited ------------ " << endl << endl;
	//print_vec(Rchild);


	for (int i = 0; i < Rchild.size(); i++ ) {  // loop inside the array comparing to find the maxima
		
		Rchild[i]->maximal = 1;

		for (int j = i+1 ; j < Rchild.size()  ; j++ ) {

			if (  (Rchild[i]->x  <= Rchild[j]->x) && (Rchild[i]->y <= Rchild[j]->y)  ) {
				Rchild[i]->maximal = 0;
			}
		
		}

	}

	for (int i = 0; i < Rchild.size(); i ++ ) {
		
		if ( Rchild[i]->maximal ==1  ) {
			//cout << "                                                 ( " << Rchild[i]->x << " , " << Rchild[i]->y << " )   inserted to  maxima!" << endl;
			//Maximal.push_back(Rchild[i]); // check it again
			Rchild[i]->maximal = 0;
			Rmax.push_back(Rchild[i]);
		}
	}


	return Rmax;
}


void recursion_for_Rmax( rbtree_node* Rchild, vector<rbtree_node*>& Maximal) {

	vector<rbtree_node*> node_path , Rchild_Vec;
	node_path = {};

	cout << " ==============  RECURSION =============" << endl;
	cout << Rchild->x << " , " << Rchild->y << "   , " << Rchild->x_dummy << endl;


	if (Rchild->left != NULL && Rchild->right != NULL ) {
		while (Rchild->left != NULL && Rchild->right != NULL) {

			if (Rchild->left->y == Rchild->y) {
				node_path.push_back(Rchild);
				Rchild = Rchild->left;
				node_path.push_back(Rchild);
			}
			else {
				cout << "in while : " << Rchild->x << " , " << Rchild->y << "   , " << Rchild->x_dummy << endl;
				node_path.push_back(Rchild);
				Rchild = Rchild->right;
				cout << "in while : " << Rchild->x << " , " << Rchild->y << "   , " << Rchild->x_dummy << endl;
				//node_path.push_back(Rchild);
			}
		}
	}
	else {
		if ( (Rchild->x_dummy != -1 || (Rchild->left==NULL && Rchild->right==NULL)) && Rchild->maximal != 1) {
			cout << "                                                 ( " << Rchild->x << " , " << Rchild->y << " )   inserted to  maxima!   .->maximal = " << Rchild->maximal << endl;
			Rchild->maximal = 1;
			Maximal.push_back(Rchild);
		}
		return;
	}

	for (int i = 0; i < node_path.size(); i++) {

		cout << " path[" << i << "]  ->   ( " << node_path[i]->x << " , " << node_path[i]->y << " )  with dummy :" << node_path[i]->x_dummy << endl;

		if ( (node_path[i]->right != NULL && (node_path[i]->right->x_dummy == -1 && node_path[i]->x_dummy != node_path[i]->right->x) ) && (node_path[i]->x_dummy != node_path[i]->right->x_dummy) ) {
			Rchild_Vec.push_back(node_path[i]->right);
		}
		else if (node_path[i]->right == NULL && node_path[i]->left == NULL && node_path[i]->maximal != 1 ) {
			node_path[i]->maximal = 1;
			cout << "                                                 ( " << node_path[i]->x << " , " << node_path[i]->y << " )   inserted to  maxima! .->maximal = " << node_path[i]->maximal << endl;
			Maximal.push_back(node_path[i]);
		}
		else {
			if ( node_path[i]->x_dummy != -1 && node_path[i]->maximal!=1 && node_path[i]->parent->maximal != 1 ) {
				node_path[i]->maximal = 1;
				cout << "                                                 ( " << node_path[i]->x << " , " << node_path[i]->y << " )   inserted to  maxima!    .->maximal = " << node_path[i]->maximal << endl;
				Maximal.push_back(node_path[i]);
			}
		}
	}

	cout << " ---- Rchild_Vec " << endl;
	print_vec(Rchild_Vec);
	cout << " ---- Maximal " << endl;
	print_vec(Maximal);
	
	for (int i = 0; i < Rchild_Vec.size(); i++) {
		recursion_for_Rmax(Rchild_Vec[i] , Maximal);
	}
	
	return;
}


vector<rbtree_node*> path_to_Rmax( vector<rbtree_node*>& path) {
	
	vector < rbtree_node *> Rchild;
	vector < rbtree_node *> Rmax;
	vector < rbtree_node * > maxima;

	std::cout << endl << endl << "=========================== path_to_Rmax  ========================== " << endl << endl;

	for (int i = 0; i < path.size(); i++) {

		std::cout << " path[" << i << "]  ->   ( " << path[i]->x << " , " << path[i]->y << " )  with dummy :" << path[i]->x_dummy << endl;
		
		if (  (path[i]->right != NULL && path[i]->right->x_dummy != -1 ) && (path[i]->x_dummy != path[i]->right->x_dummy   ) )   {
			Rchild.push_back( path[i]->right);
		}
		else if (path[i]->right != NULL && path[i]->right->right==NULL  && path[i]->right->left == NULL && path[i]->parent->y != path[i]->y) {  //periptwsi pio deksiou paidiou, seed 11
			Rchild.push_back(path[i]->right);
		}
		else {
			
			if ( path[i]->x_dummy != -1 && path[i]->maximal!=1  ) {
				if ( path[i]->parent !=NULL && path[i]->parent->maximal != 1 && (path[i]->right->y != path[i]->y) ) {
					path[i]->maximal = 1;
					cout << "                                                 ( " << path[i]->x << " , " << path[i]->y << " )   inserted to  maxima!    .->maximal = " << path[i]->maximal << endl;
					maxima.push_back(path[i]);
				}
				else if(path[i]->parent != NULL && path[i]->parent->maximal == 1){
					Rchild.push_back( path[i]->right);
				}
				else {
					Rchild.push_back( path[i] );
				}
			}
		}

	}

	cout << endl << " -----------  path -------------------- " << endl << endl;
	print_vec(path);
	
	cout << endl << " ------------ Rchild ------------ " << endl << endl;
	print_vec(Rchild);

	cout << endl << " ------------ Rmax ------------ " << endl << endl;
	Rmax = maxima_in_vector( Rchild , maxima);
	

	for (int i = 0; i < Rmax.size(); i++ ) {
		cout << " Rmax =>  x: " << Rmax[i]->x << "  y: " << Rmax[i]->y << "   x_dump : " << Rmax[i]->x_dummy << endl;
	}
	
	for (int i = 0; i<Rmax.size(); i++) {
		recursion_for_Rmax(Rmax[i], maxima);
	}

	cout << "   ---------------------------------------------------->>>>>  " << endl;

	return maxima;
}


vector < rbtree_node* >  Rmax(rbtree &t) {  //change name to Rmax initializer

	cout << "==================== Rmax ============================" << endl;

	cout << " root is : ( " << t->root->x << " , " << t->root->y << ")  " << endl;
	
	vector < rbtree_node* >  root_path , maxima;
	rbtree_node * parser = t->root;
	parser->maximal = 1;

	root_path.push_back( t->root );

	while ( parser->left != NULL && parser->right != NULL ) {
	
		if (  parser->left->y == parser->y ) {
			parser = parser->left;
			root_path.push_back(parser);
		}
		else {
			parser = parser->right;
			root_path.push_back(parser);
		}
	}

	maxima = path_to_Rmax( root_path);


	parser = t->root;
	while (parser->right != NULL) {

		parser = parser->right;
		if (parser->right == NULL && parser->maximal!=1 ) {
			//parser->maximal = 1;
			//maxima.push_back(parser);
		}

	}
	/* find most right child cos its every time a maximal */
	
	
		int root_adder = 1 ;   // a little bad way to see if we must put the root in maximal. Scanning the current maximals, if x_dummy is not in any of the nodes, then add root
		for (int i = 0; i < maxima.size(); i++) {
			
			if ( t->root->x_dummy == maxima[i]->x_dummy || t->root->y == maxima[i]->y ) {
				root_adder = 0;
			}
		}
		if ( root_adder == 1 ) {
			cout << "                                                 ( " << t->root->x << " , " << t->root->y << " )   inserted to  maxima!    .->maximal = " << t->root->maximal << endl;
			maxima.push_back(t->root);  //  damb way  maybe find a better
		}


	for (int i = 0; i < maxima.size(); i++) {

		if (maxima[i]->x_dummy != -1) {
			cout << "                 ( " << maxima[i]->x_dummy << " , " << maxima[i]->y << "  )    ---> x = " << maxima[i]->x << endl;
		}
		else {
			cout << "                 ( " << maxima[i]->x << " , " << maxima[i]->y << "  ) " << endl;
		}
	}

	return maxima;
}

float compare_int(float leftp, float rightp);
