/**
 * @file        threetree-private.h
 * @author      CPSC 221
 * @description Declaration of private attributes and/or functions for ThreeTree
 *
 * Add your declarations in this file. There is no need to qualify them with a class name,
 * as this file is entirely included into line 196 of threetree.h
 *
 * THIS FILE WILL BE SUBMITTED
**/

/* POST: recursively(preOrder) draws the image by manipulating the img pixels when reaching a leaf node.*/
void drawImg(Node* subRoot, PNG& img) const;

/* POST: recursively find the number of nodes in the tree starting from the subRoot */
int getNumNodes(Node* subRoot) const;

/* POST: recursively finds the number of leaves in the tree starting from the subRoot */
int getNumNodesLeaves(Node* subRoot) const;

/* POST: recursively deallocates the tree (subRoot) by first deallocating all of its leaves */
void removeTree(Node*& subRoot);

/* POST: recursively copies each node starting from subRoot */
Node* copyNode(Node* subRoot);

/* POST: recursively rotates the tree CW starting from the subRoot by:
 * Switching x, y points
 * Switching w, h
 * Swapping A and C for each subRoot
 */
Node* rotateNode(Node* subRoot, int original_root_height);
