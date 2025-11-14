/**
 * @file        threetree-private.h
 * @author      CPSC 221
 * @description Declaration of private attributes and/or functions for ThreeTree
 *
 * Add your declarations in this file. There is no need to qualify them with a
 * class name, as this file is entirely included into line 196 of threetree.h
 *
 * THIS FILE WILL BE SUBMITTED
 **/

/* POST: recursively(preOrder) draws the image by manipulating the img pixels
 * when reaching a leaf node.*/
#include <utility>
void drawImg(Node *subRoot, PNG &img) const;

/* POST: recursively find the number of nodes in the tree starting from the
 * subRoot */
int getNumNodes(Node *subRoot) const;

/* POST: recursively finds the number of leaves in the tree starting from the
 * subRoot */
int getNumNodesLeaves(Node *subRoot) const;

/* POST: recursively deallocates the tree (subRoot) by first deallocating all of
 * its leaves */
void removeTree(Node *&subRoot);

/* POST: recursively copies each node starting from subRoot */
Node *copyNode(Node *subRoot);

/* Rotate the subtree rooted at subRoot by 90 degrees clockwise.
 * origRootHeight is the original height of the whole image (root->height
 * before rotation). It is required to compute the new upper-left
 * coordinates for each node: new_ul = { origRootHeight - (old_y + old_h), old_x }.
 */
Node* rotateNode(Node *subRoot, int origRootHeight);
