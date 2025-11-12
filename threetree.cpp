/**
 * @file            threetree.cpp
 * @author          your CWL
 * @description     Implementation of ThreeTree functions
 *
 * THIS FILE WILL BE SUBMITTED
**/

#include "threetree.h"

/**
 * ThreeTree constructor given tolerance for variance.
**/
ThreeTree::ThreeTree(PNG& imIn, double tol) {
    Stats s(imIn);
    root = BuildTree(s, pair<int, int>(0,0), imIn.width(), imIn.height(), tol);
}

/**
 * Helper for the ThreeTree constructor.
**/
Node* ThreeTree::BuildTree(Stats& s, pair<int, int> ul, int w, int h, double tol) {
    /* Replace the line below with your implementation */
    return nullptr;
}

/**
 * Render ThreeTree and return the resulting image.
**/
PNG ThreeTree::Render() const {
    PNG png(root->width, root->height);
    drawImg(root, png);
    return png;
}

/**
 * Delete allocated memory.
**/
void ThreeTree::Clear() {
    /* Complete your implementation below */

    
}

/**
 * Copy other tree into this tree object.
**/
void ThreeTree::Copy(const ThreeTree& other) {
    /* Complete your implementation below */

    
}

/**
 * Returns the number of nodes in the tree
**/
int ThreeTree::Size() const {
    /* Replace the line below with your implementation */
    return 0;
}

/**
 * Returns the number of leaf nodes in the tree
**/
int ThreeTree::NumLeaves() const {
    /* Replace the line below with your implementation */
    return 0;
}

/**
 * Rearranges the tree contents so that when rendered, the image appears
 * to be rotated 90 degrees clockwise.
 * See threetree.h for specification details.
 *
 * You may want a recursive helper function for this.
**/
void ThreeTree::RotateCW() {
    /* Complete your implementation below */

    
}

/*****************************************************************
* IF YOU HAVE DEFINED ANY PRIVATE FUNCTIONS IN sqtree-private.h, *
* ADD YOUR IMPLEMENTATIONS BELOW                                 *
*****************************************************************/

void ThreeTree::drawImg(Node* subRoot,PNG& img) const {
    if (subRoot == nullptr) {
        return;
    }

    if (subRoot->A == nullptr && subRoot->B == nullptr && subRoot->C) {
        RGBAPixel* pixel = img.getPixel(subRoot->upleft.first, subRoot->upleft.second);
        pixel->r = subRoot->avg.r;
        pixel->b = subRoot->avg.b;
        pixel->g = subRoot->avg.g;
        return;
    }

    drawImg(subRoot->A, img);
    drawImg(subRoot->B, img);
    drawImg(subRoot->C, img);
}
