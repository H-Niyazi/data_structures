#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

struct bst_node
{
  double data;
  bst_node* left;
  bst_node* right;
};

bst_node* get_new_node(double data);

bst_node* insert(bst_node* root, double data);

bst_node* search(bst_node* root, double data);

bst_node* iterative_search(bst_node* root, double data);

bst_node* find_min(bst_node* root);

bst_node* find_max(bst_node* root);

double find_height(bst_node* root);

void level_order(bst_node* root);

void pre_order(bst_node* root);

void in_order(bst_node* root);

void post_order(bst_node* root);

bool is_bst(bst_node* root, double min_val, double max_val);

bst_node* bst_delete(bst_node* root, double data);

bst_node* get_successor(bst_node* root, double data);

bst_node* get_predecessor(bst_node* root, double data);

#endif
