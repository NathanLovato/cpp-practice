#ifndef BinaryTree
#define BinaryTree

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
  int value;
  struct node *left;
  struct node *right;
} typedef node;

node *newNode(int value) {
  node *node = (struct node *)malloc(sizeof(node));

  node->value = value;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void BinaryTreePrint(node *treeRoot) {
  if (treeRoot == NULL) {
    return;
  }

  if (treeRoot->left != NULL) {
    BinaryTreePrint(treeRoot->left);
  }
  printf("%d\n", treeRoot->value);
  if (treeRoot->right != NULL) {
    BinaryTreePrint(treeRoot->right);
  }
}

// Inserts a new node in the tree based on its value.
void BinaryTreeInsert(node *treeRoot, node *newNode) {
  if (treeRoot == NULL)
    return;

  int newValue = newNode->value;
  node *currentNode = treeRoot;
  while (true) {
    if (newValue < currentNode->value && currentNode->left != NULL) {
      currentNode = currentNode->left;
      continue;
    }
    if (newValue > currentNode->value && currentNode->right != NULL) {
      currentNode = currentNode->right;
      continue;
    }

    if (newValue == currentNode->value) {
      return;
    }

    if (newValue < currentNode->value) {
      currentNode->left = newNode;
    } else {
      currentNode->right = newNode;
    }
    return;
  }
}

// Search the tree for a node with the given value. Returns NULL if no such node
// exists.
node *BinaryTreeSearch(node *treeRoot, int value) {
  if (treeRoot == NULL)
    return NULL;

  node *currentNode = treeRoot;
  while (true) {
    if (currentNode->value == value) {
      return currentNode;
    }
    if (currentNode->value < value && currentNode->right != NULL) {
      currentNode = currentNode->right;
      continue;
    } else if (currentNode->left != NULL) {
      currentNode = currentNode->left;
      continue;
    }
    return NULL;
  }
}

// TODO: remove one node from the tree and update the other nodes
bool BinaryTreeRemove(node *treeRoot, int value) {
  bool result = false;
  if (treeRoot == NULL)
    return result;

  node *currentNode = treeRoot;
  while (currentNode != NULL) {
    if (currentNode->value == value) {
      node *right = currentNode->right;
      while (right != NULL) {
        currentNode->value = right->value;
      }
      result = true;
      break;
    }
  }
  return result;
}

# define COUNT 6
int main(int argc, char *argv[]) {
  node *tree = newNode(1);
  int values[COUNT] = {12, 5, 9, 22, 3, 16};

  for (int i = 0; i < COUNT; i++) {
    BinaryTreeInsert(tree, newNode(values[i]));
  }
  BinaryTreePrint(tree);
  /* node *node = BinaryTreeSearch(tree, 124); */
  /* if (node != NULL) { */
  /*   printf("Found: %d\n", node->value); */
  /* } else { */
  /*   printf("Node not found\n"); */
  /* } */
}
#endif
