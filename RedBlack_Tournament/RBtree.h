#pragma once
#include <string>
using namespace std;
// RedBlackTree.cpp : Defines the entry point for the console application.
//
/*
* C++ Program to Implement Red Black Tree
*/
#include "stdafx.h"
#include <time.h>       /* time */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <assert.h>     /* assert */

#define CLEAR_Y -1        // o airhtmos pou tha gemizei to y tis "trixas" otan prokeite na tin katharisoume
#define INDENT_STEP  4
#define NUM_OF_POINTS 15

enum color { RED, BLACK };
/*
* Node RBTree Declaration
*/

typedef struct rbtree_node
{
	enum color color;  // xrwma node (kokkino i mavro)
	float x;
	float x_dummy;
	float y;
	bool maximal;
	float is_dummy;
	vector<rbtree_node> path;
	rbtree_node *left, *right, *parent;
}*node;

typedef struct rbtree_t
{
	node root;
}*rbtree;


class RBTree
{
public:
	typedef float(*compare_func)(float left, float right);
	rbtree rbtree_create();
	float rbtree_lookup(rbtree t, float, compare_func compare);
	void rbtree_insert(rbtree t, float, float, float, compare_func compare);
	void rbtree_delete(rbtree t, float, compare_func compare);
	node grandparent(node n);
	node sibling(node n);
	node uncle(node n);
	void verify_properties(rbtree t);
	void verify_property_1(node root);
	void verify_property_2(node root);
	color node_color(node n);
	void verify_property_4(node root);
	void verify_property_5(node root);
	void verify_property_5_helper(node n, int, int*);
	node new_node(float x, float, float, color, node, node);
	node lookup_node(rbtree t, float, compare_func compare);
	void rotate_left(rbtree t, node n);
	void rotate_right(rbtree t, node n);
	void replace_node(rbtree t, node oldn, node newn);
	void insert_case1(rbtree t, node n);
	void insert_case2(rbtree t, node n);
	void insert_case3(rbtree t, node n);
	void insert_case4(rbtree t, node n);
	void insert_case5(rbtree t, node n);
	node maximum_node(node root);
	void delete_case1(rbtree t, node n);
	void delete_case2(rbtree t, node n);
	void delete_case3(rbtree t, node n);
	void delete_case4(rbtree t, node n);
	void delete_case5(rbtree t, node n);
	void delete_case6(rbtree t, node n);

	//
	void tournament(rbtree &t);
	void tournament_helper(node& n);
	node* dynamic_tournament(rbtree&t, float, bool first); // vlepe katw eksigisi
	void clear_to_parent(rbtree &t, node n, bool first);   // first an einai to prwto pou mpainei stin anazitisi, wste
														   // na apofigoume na paroume 2 fores to stoixeio, mia pros ta panw, mia pros ta katw
	node* clear_to_leaf(rbtree &t, node n);
	void re_tournament(rbtree &t, node &p_leaf, float new_y);
};
