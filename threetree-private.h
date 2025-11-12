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
void drawImg(Node* subRoot,PNG& img) const;