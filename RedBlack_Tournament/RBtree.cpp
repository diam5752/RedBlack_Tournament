#include "stdafx.h"
#include "RBtree.h"



/*
RBtree::RBtree()
{
root = NULL;
}


RBtree::~RBtree()
{
}

/*
void RBtree::insert(int x) {

RBtree *node = new RBtree;
node->color = "r";
node->key = x;

if (root==NULL) {  // case 0
node->color = "b";
root = node;
}
}
*/


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
node RBTree::new_node(int k, int v, int yvalue, color n_color, node left, node right)
{
	node result = new rbtree_node;
	result->key = k;
	cout << "----------------------------------------------->  result -> key = " << result->key << endl;
	result->value = v;
	cout << "----------------------------------------------->  result -> value = " << result->value << endl;
	result->color = n_color;
	result->left = left;
	result->right = right;
	result->yvalue = yvalue;
	cout << "----------------------------------------------->  result -> yvalue = " << result->yvalue << endl;
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
node RBTree::lookup_node(rbtree t, int key, compare_func compare)
{
	node n = t->root;
	while (n != NULL)
	{
		int comp_result = compare(key, n->key);
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
int RBTree::rbtree_lookup(rbtree t, int key, compare_func compare)
{
	node n = lookup_node(t, key, compare);
	return n == NULL ? NULL : n->value;
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
void RBTree::rbtree_insert(rbtree t, int key, int value, int yvalue, compare_func compare)
{
	node inserted_node = new_node(key, value, yvalue, RED, NULL, NULL);
	if (t->root == NULL)
	{
		t->root = inserted_node;
	}
	else
	{
		node n = t->root;
		while (1)
		{
			int comp_result = compare(key, n->key);
			if (comp_result == 0)
			{
				n->value = value;
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
void RBTree::rbtree_delete(rbtree t, int key, compare_func compare)
{
	node child;
	node n = lookup_node(t, key, compare);
	if (n == NULL)
		return;
	if (n->left != NULL && n->right != NULL)
	{
		node pred = maximum_node(n->left);
		n->key = pred->key;
		n->value = pred->value;
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
	/*cout << "root = " << int(t->root->key) << endl;
	cout << "left = " << int(t->root->left->key) << endl;
	cout << "right = " << int(t->root->right->key) << endl;*/
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
	cout << " n = " << (int)n->key << "   y = " << (int)n->yvalue;
	//cout << "                                                                       edw  me n =  "<< (int)n->key <<"   y = " << (int)n->yvalue<< endl;
	if (n->parent == NULL) {
		cout << "   case 0 " << endl;

		if (n->left != NULL && (n->yvalue == n->left->yvalue)) {
			n->path.push_back(*n);
			n->path.insert(n->path.end(), n->left->path.begin(), n->left->path.end());
		}
		else if (n->right != NULL && n->yvalue == n->right->yvalue) {
			n->path.push_back(*n);
			n->path.insert(n->path.end(), n->right->path.begin(), n->right->path.end());
		}
		else if (n->right == NULL && n->left == NULL) {
			n->path.push_back(*n);
		}

		return;
	}

	if (n->left == NULL && n->right == NULL && n->parent->left == NULL) {
		n->parent->yvalue = n->yvalue;
		cout << "   case 1 " << endl;

		n->path.push_back(*n);

		return;
	}
	else if (n->left == NULL && n->right == NULL && n->parent->right == NULL) {

		n->parent->yvalue = n->yvalue;
		cout << "   case 2 " << endl;
		return;
	}

	if (n->yvalue >= n->parent->right->yvalue &&n->parent != NULL) {
		n->parent->yvalue = n->yvalue;

		if (n->left != NULL && (n->yvalue == n->left->yvalue)) {
			n->path.push_back(*n);
			n->path.insert(n->path.end(), n->left->path.begin(), n->left->path.end());
		}
		else if (n->right != NULL && n->yvalue == n->right->yvalue) {
			n->path.push_back(*n);
			n->path.insert(n->path.end(), n->right->path.begin(), n->right->path.end());
		}
		else if (n->right == NULL && n->left == NULL) {
			n->path.push_back(*n);
		}

		cout << "   case 3 " << endl;
	}
	else {
		n->parent->yvalue = n->parent->right->yvalue;

		if (n->left != NULL && (n->yvalue == n->left->yvalue)) {
			n->path.push_back(*n);
			n->path.insert(n->path.end(), n->left->path.begin(), n->left->path.end());
		}
		else if (n->right != NULL && n->yvalue == n->right->yvalue) {
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
int compare_int(int leftp, int rightp)
{
	int left = (int)leftp;
	int right = (int)rightp;
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

node* RBTree::dynamic_tournament(rbtree&t, int key, bool first) {
	node* p_leaf;
	node * ancestor = NULL;
	RBTree rbt;
	node n = rbt.lookup_node(t, key, compare_int);
	//node *pn = &n;
	//cout << "found node : " << (int)(*pn)->key << "," << (int)(*pn)->yvalue << endl;
	//void *y = (*pn)->yvalue;
	cout << "found node : " << (int)n->key << "," << (int)n->yvalue << endl;

	clear_to_parent(t, n, first);
	p_leaf = clear_to_leaf(t, n);
	return p_leaf;
}

//katharizei apo tin korifi tis trixas mexri to node pou psaxnoume
void RBTree::clear_to_parent(rbtree &t, node n, bool first) {

	if (n->parent != NULL && n->parent->yvalue == n->yvalue) {
		cout << " current n = " << (int)n->key << endl;
		if (first != 1) {
			n->yvalue = CLEAR_Y;
		}
		clear_to_parent(t, n->parent, 0);
		cout << " parent is : " << (int)n->parent->key << endl;
		n->parent->yvalue = CLEAR_Y;
	}
}

node* RBTree::clear_to_leaf(rbtree &t, node n) {

	if (n->left != NULL && n->left->yvalue == n->yvalue) {
		cout << " current n = " << (int)n->key << endl;
		n->yvalue = CLEAR_Y;
		clear_to_leaf(t, n->left);
		n->left->yvalue = n->yvalue;
		cout << " left is : " << (int)n->left->key << "   with y = " << (int)n->left->yvalue << endl;
		return &(n->left);
	}
	else if (n->right != NULL && n->right->yvalue == n->yvalue) {
		cout << " current n = " << (int)n->key << endl;
		n->yvalue = CLEAR_Y;
		clear_to_leaf(t, n->right);
		n->right->yvalue = n->yvalue;
		cout << " right is : " << (int)n->right->key << "   with y = " << (int)n->right->yvalue << endl;
		return &(n->right);
	}

	else {
		cout << "error happened ... returning 0 " << endl;
		return 0;
	}

}

void RBTree::re_tournament(rbtree &t, node &p_leaf, int new_y) {
	cout << " \n ========================================== \n returned : " << (int)(p_leaf)->key << endl;

	while ((p_leaf)->yvalue == CLEAR_Y) {

		if ((p_leaf)->left == NULL && (p_leaf)->right == NULL) {  // prwti periptwsi
			(p_leaf)->yvalue = new_y;
			cout << "first value =  " << (int)(p_leaf)->yvalue << endl;
		}
		else if ((p_leaf)->left != NULL && (p_leaf)->right == NULL) {
			(p_leaf)->yvalue = (p_leaf)->left->yvalue;
			cout << "left value =  " << (p_leaf)->left << endl;    // (int) an dn doulevei
		}
		else if ((p_leaf)->left == NULL && (p_leaf)->right != NULL) {
			(p_leaf)->yvalue = (p_leaf)->right->yvalue;
			cout << "right value =  " << (int)(p_leaf)->right->yvalue << endl;
		}
		else {
			if ((int)(p_leaf)->left->yvalue >= (int)(p_leaf)->right->yvalue) {

				(p_leaf)->yvalue = (p_leaf)->left->yvalue;
			}
			else {
				(p_leaf)->yvalue = (p_leaf)->right->yvalue;
			}

		}
		if ((p_leaf)->parent != NULL) {
			cout << " p_leaf  parent = " << (int)(p_leaf)->parent->key << endl;
			(p_leaf) = (p_leaf)->parent;
			cout << " p_leaf = " << (int)(p_leaf)->key << endl;
			cout << " p_leaf.left = " << (int)(p_leaf)->left->key << endl;
		}
	}

}


/*
* Print RBTRee
*/

void print_tree_helper(node n, int indent)
{
	for (std::vector<rbtree_node>::iterator it = (n->path).begin(); it != (n->path).end(); ++it) {
		//	cout << "for n = " << (int)n->key << "  path = " << (int)(*it).key << endl;
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
		cout << (int)n->key << "                                              ( " << (int)n->key << " , " << (int)n->yvalue << " )" << endl;
	}
	else
	{
		cout << "<" << (int)n->key << ">" << "                                              ( " << (int)n->key << " , " << (int)n->yvalue << " )" << endl;
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

void find_maxima(vector<node*> &v) {  // vriskw ta maxima apo array pou pairnei ws oris,a

	cout << " item with biggest x : " << (*(v.front()))->key << endl;

	vector<node*> v_max; // tha krataei ta maximal simeia

	int v_size = (int)v.size();
	cout << "**************************************************************" << endl;
	for (int i = 0; i < v_size; i++) {
		int max_desc = 0; // an o ginei iso me ton arithmo twn komvwn, tote einai maximal to node pou koitame
		cout << "--------------------------------------------------" << endl;
		cout << "v[" << i << "]  = " << (*v[i])->key << endl; // ektipwsi pou mas voithaei na tsekaroume an einai swsta ta apotelesmata

		for (int j = 0; j < v_size; j++) {  //ksekinaw ti diadikasia elegxou gia maxima. Arxika auti einai i kaki veltiwsi , kai tha 
											// veltiwthei me xrisi partial queue with attrition

			cout << " x = " << (*v[j])->key << "    y = " << (*v[j])->yvalue << endl;
			if (((*v[i])->key >= (*v[j])->key) || (((*v[i])->yvalue) >= (*v[j])->yvalue)) {
				max_desc++;
			}
			else { max_desc = 0; }
		}
		cout << "                                               max_desc = " << max_desc << endl; // an max_desc isoutai me to megethos tis 
																								  // v tote einai maxima to simeio
		if (max_desc == v.size()) {  // an simvainei auto to simeio einai maxima , kai ara allazoume tin metavliti tou maximal se 1  
			(*(v[i]))->maximal = 1;
			v_max.push_back(v[i]); // o v_max krataei ta maxima simeia 
		}
	}

	cout << "**************************************************************" << endl;
	for (std::vector<node *>::iterator it = v_max.begin(); it != v_max.end(); ++it)
	{
		std::cout << ' ' << (*(*it))->key << " with n->maximal value = " << (*(*it))->maximal << endl;  // ektipwnoume ta maxima	
																										// gia na doume an einai swsta ta apotelesmata
	}
}

void Rmax(rbtree &t) {

	cout << " -------------------  IN Rmax ------------------- " << endl;

	cout << " root = " << (int)t->root->key << endl;
	node* p_leaf = &(t->root);  // pointer pou deixnei stin thesi mnimis tis korifis  tou dentrou. Sto telos tha deixnei sto leaf apo to
								// opoio pire to y i riza tou dentrou
	vector<node*> v;  // vector pou tha krataei ta Rmax . Ta deksia kremamena diladi, apo to winning path

	while ((*p_leaf)->yvalue == t->root->yvalue) {   // arxika mono gia to paradeigma pou exw. Thelei genikopoiisi
		cout << "p_leaf = " << (int)(*p_leaf)->key << endl;

		if ((*p_leaf)->right != NULL && (*p_leaf)->right->yvalue != t->root->yvalue) {
			v.push_back(&(*p_leaf)->right);
		}

		if ((*p_leaf)->left != NULL) {
			*p_leaf = (*p_leaf)->left;
		}
		else {
			break;
		}
	}
	for (std::vector<node *>::iterator it = v.begin(); it != v.end(); ++it)
	{
		std::cout << ' ' << (*(*it))->key;  // ektipwnw ta dekisa canditates, ta Rmax tou winning path
	}
	std::cout << endl;

	cout << " LEAF OF ROOT IS ---> " << (int)(*p_leaf)->key << endl;  // tsekarw an o pointer eftase ekei pou ithela, diladi sto leaf
																	  // apo opou pire i riza to y tis. O deiktis menei ekei , kai tha mas xreiastei
	find_maxima(v);  //stelnw stin sinartisi ton vector me ta Rmax, kai apo auta vriskw poia einai maxima.
}

int compare_int(int leftp, int rightp);






