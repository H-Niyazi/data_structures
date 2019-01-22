#include <iostream>
#include "binary_search_tree.h"

#include <queue>    // for level order traversal

using std::cout;
using std::endl;
using std::queue;

// ****************************************************************************

bst_node* get_new_node(double data)
{
  bst_node* new_node = new bst_node();
  new_node->data = data;
  new_node->left = NULL;
  new_node->right = NULL;

  return new_node;
}

// ****************************************************************************

bst_node* insert(bst_node* root, double data)
{
  if (root == NULL)
    root = get_new_node(data);

  else if (data <= root->data)
    root->left = insert(root->left, data);

  else
    root->right = insert(root->right, data);

  return root;
}

// ****************************************************************************

bst_node* search(bst_node* root, double data)
{
  if (root == NULL)
    return NULL;

  else if (root->data == data)
    return root;

  else if (data <= root->data)
    return search(root->left, data);

  else
    return search(root->right, data);
}

// ****************************************************************************

bst_node* iterative_search(bst_node* root, double data)
{
  while(root != NULL && root->data != data)
  {
    if (data < root->data)
      root = root->left;

    else
      root = root->right;
  }

  return root;
}

// ****************************************************************************

bst_node* find_min(bst_node* root)
{
  if (root == NULL)
  {
    cout << "Empty tree!" << endl;
    return NULL;
  }

  else if (root->left == NULL)
    return root;

  else
    return find_min(root->left);
}

// ****************************************************************************

bst_node* find_max(bst_node* root)
{
  if (root == NULL)
  {
    cout << "Empty tree!" << endl;
    return NULL;
  }

  else if (root->right == NULL)
    return root;

  else
    return find_max(root->right);
}

// ****************************************************************************

double find_height(bst_node* root)
{
  if (root == NULL)
    return -1;

  double left_height = find_height(root->left);
  double right_height = find_height(root->right);

  double max = left_height > right_height ? left_height : right_height;

  return max + 1;
}

// ****************************************************************************

void level_order(bst_node* root)
{
  if (root == NULL)
    return;

  queue<bst_node*> Q;
  Q.push(root);

  while(!Q.empty())
  {
    bst_node* current = Q.front();

    cout << current->data << endl;

    if (current->left != NULL)
      Q.push(current->left);

    if (current->right != NULL)
      Q.push(current->right);

    Q.pop();
  }
}

// ****************************************************************************

void pre_order(bst_node* root)
{
  if (root == NULL)
    return;

  cout << root->data << endl;
  pre_order(root->left);
  pre_order(root->right);
}

// ****************************************************************************

void in_order(bst_node* root)
{
  if (root == NULL)
    return;

  in_order(root->left);
  cout << root->data << endl;
  in_order(root->right);
}

// ****************************************************************************

void post_order(bst_node* root)
{
  if (root == NULL)
    return;

  post_order(root->left);
  cout << root->data << endl;
  post_order(root->right);
}

// ****************************************************************************

bool is_bst(bst_node* root, double min_val, double max_val)
{
  if (root == NULL)
    return true;

  if (root->data >= min_val && root->data < max_val &&
      is_bst(root->left, min_val, root->data) &&
      is_bst(root->right, root->data, max_val))
    return true;

  else
    return false;
}

// ****************************************************************************
// I couldn't just call it delete because that is reserved for the operator.

bst_node* bst_delete(bst_node* root, double data)
{
  if (root == NULL)
    return root;

  else if (data < root->data)
    root->left = bst_delete(root->left, data);

  else if (data > root->data)
    root->right = bst_delete(root->right, data);

  else
  {
    // case 1 : no child
    if (root->left == NULL && root->right == NULL)
    {
      delete root;
      root = NULL;
    }

    // case 2 : one child
    else if (root->left == NULL)
    {
      bst_node* temp = root;
      root = root->right;
      delete temp;
    }

    else if (root->right == NULL)
    {
      bst_node* temp = root;
      root = root->left;
      delete temp;
    }

    // case 3 : two children
    else
    {
      bst_node* temp = find_min(root->right);
      root->data = temp->data;
      root->right = bst_delete(root->right, temp->data);
    }
  }

  return root;
}

// ****************************************************************************
// finding the inorder successor (next biggest value)

bst_node* get_successor(bst_node* root, double data)     // O(h)
{
  bst_node* current = search(root, data);

  if (current == NULL)
    return NULL;

  // case 1 : node has right subtree
  if (current->right != NULL)
    return find_min(current->right);

  // case 2 : no right subtree, find the deepest ancestor for which the node is
  // in its left subtree
  else
  {
    bst_node* successor = NULL;
    bst_node* ancestor = root;

    while(ancestor != current)
    {
      if (current->data < ancestor->data)
      {
        successor = ancestor;
        ancestor = ancestor->left;
      }

      else
        ancestor = ancestor->right;
    }

    return successor;
  }
}

// ****************************************************************************
// finding the inorder predecessor (previous smallest value)

bst_node* get_predecessor(bst_node* root, double data)     // O(h)
{
  bst_node* current = search(root, data);

  if (current == NULL)
    return NULL;

  // case 1 : node has left subtree
  if (current->left != NULL)
    return find_max(current->left);

  // case 2 : no left subtree, find the deepest ancestor for which the node is
  // in its right subtree
  else
  {
    bst_node* predecessor = NULL;
    bst_node* ancestor = root;

    while(ancestor != current)
    {
      if (current->data > ancestor->data)
      {
        predecessor = ancestor;
        ancestor = ancestor->right;
      }

      else
        ancestor = ancestor->left;
    }

    return predecessor;
  }
}
