/**
 * @file            threetree.cpp
 * @author          your CWL
 * @description     Implementation of ThreeTree functions
 *
 * THIS FILE WILL BE SUBMITTED
 **/

#include "threetree.h"
#include <utility>

/**
 * ThreeTree constructor given tolerance for variance.
 **/
ThreeTree::ThreeTree(PNG &imIn, double tol) {
  Stats s(imIn);
  root = BuildTree(s, pair<int, int>(0, 0), imIn.width(), imIn.height(), tol);
}

/**
 * Helper for the ThreeTree constructor.
 **/
Node *ThreeTree::BuildTree(Stats &s, pair<int, int> ul, int w, int h,
                           double tol) {
  // partitions.
  if (w <= 0 || h <= 0) {
    return nullptr;
  }

  // Create the node for the current region
  Node *nd = new Node(s, ul, w, h);

  // Base cases for recursion termination:
  // 1. Variability is within tolerance.
  // 2. The region is a single pixel.
  if (nd->var <= tol || (w == 1 && h == 1)) {
    return nd;
  }

  // Recursive step: split the node
  if (w >= h) { // Split wide (vertically)
    int p = w / 3;
    int r = w % 3;
    int w1 = p, w2 = p, w3 = p;

    if (r == 1) { // 3p+1 case: B gets the extra pixel
      w2 += 1;
    } else if (r == 2) { // 3p+2 case: A and C get an extra pixel
      w1 += 1;
      w3 += 1;
    }

    nd->A = BuildTree(s, ul, w1, h, tol);
    nd->B = BuildTree(s, {ul.first + w1, ul.second}, w2, h, tol);
    nd->C = BuildTree(s, {ul.first + w1 + w2, ul.second}, w3, h, tol);

  } else { // Split tall (horizontally)
    int p = h / 3;
    int r = h % 3;
    int h1 = p, h2 = p, h3 = p;

    if (r == 1) { // 3p+1 case: B gets the extra pixel
      h2 += 1;
    } else if (r == 2) { // 3p+2 case: A and C get an extra pixel
      h1 += 1;
      h3 += 1;
    }

    nd->A = BuildTree(s, ul, w, h1, tol);
    nd->B = BuildTree(s, {ul.first, ul.second + h1}, w, h2, tol);
    nd->C = BuildTree(s, {ul.first, ul.second + h1 + h2}, w, h3, tol);
  }

  return nd;
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
  removeTree(root);
}

/**
 * Copy other tree into this tree object.
 **/
void ThreeTree::Copy(const ThreeTree &other) {
  // Does not free any memory. Called by copy constructor and operator=.
  root = copyNode(other.root);
}

/**
 * Returns the number of nodes in the tree
 **/
int ThreeTree::Size() const { return getNumNodes(root); }

/**
 * Returns the number of leaf nodes in the tree
 **/
int ThreeTree::NumLeaves() const { return getNumNodesLeaves(root); }

/**
 * Rearranges the tree contents so that when rendered, the image appears
 * to be rotated 90 degrees clockwise.
 * See threetree.h for specification details.
 *
 * You may want a recursive helper function for this.
 **/
void ThreeTree::RotateCW() {
  if (root == nullptr) {
    return;
  }
  int original_root_width = root->width;
  root = rotateNode(root, original_root_width);
}

/*****************************************************************
 * IF YOU HAVE DEFINED ANY PRIVATE FUNCTIONS IN sqtree-private.h, *
 * ADD YOUR IMPLEMENTATIONS BELOW                                 *
 *****************************************************************/

void ThreeTree::drawImg(Node *subRoot, PNG &img) const {
  if (subRoot == nullptr) {
    return;
  }

  if (subRoot->A == nullptr && subRoot->B == nullptr && subRoot->C == nullptr) {
    for (int x = subRoot->upleft.first;
         x < subRoot->upleft.first + subRoot->width; x++) {
      for (int y = subRoot->upleft.second;
           y < subRoot->upleft.second + subRoot->height; y++) {
        RGBAPixel *pixel = img.getPixel(x, y);
        *pixel = subRoot->avg;
      }
    }
    return;
  }

  drawImg(subRoot->A, img);
  drawImg(subRoot->B, img);
  drawImg(subRoot->C, img);
}

int ThreeTree::getNumNodes(Node *subRoot) const {
  if (subRoot == nullptr) {
    return 0;
  }

  return 1 + getNumNodes(subRoot->A) + getNumNodes(subRoot->B) +
         getNumNodes(subRoot->C);
}

int ThreeTree::getNumNodesLeaves(Node *subRoot) const {
  if (subRoot == nullptr) {
    return 0;
  }

  if (subRoot->A == nullptr && subRoot->B == nullptr && subRoot->C == nullptr) {
    return 1;
  }

  return getNumNodesLeaves(subRoot->A) + getNumNodesLeaves(subRoot->B) +
         getNumNodesLeaves(subRoot->C);
}

void ThreeTree::removeTree(Node *&subRoot) {
  if (subRoot == nullptr) {
    return;
  }

  removeTree(subRoot->A);
  removeTree(subRoot->B);
  removeTree(subRoot->C);

  delete subRoot;
  subRoot = nullptr;
}

Node *ThreeTree::copyNode(Node *subRoot) {
  if (subRoot == nullptr) {
    return nullptr;
  }

  Node *nd = new Node(subRoot->upleft, subRoot->width, subRoot->height,
                      subRoot->avg, subRoot->var);

  nd->A = copyNode(subRoot->A);
  nd->B = copyNode(subRoot->B);
  nd->C = copyNode(subRoot->C);

  return nd;
}

Node *ThreeTree::rotateNode(Node *node, int original_root_width) {
  if (node == nullptr) {
    return nullptr;
  }

  // Store original properties before modifying the node
  int orig_w = node->width;
  int orig_h = node->height;
  pair<int, int> orig_ul = node->upleft;

  // Update dimensions and position for clockwise rotation
  node->width = orig_h;
  node->height = orig_w;
  node->upleft = {orig_ul.second, original_root_width - orig_ul.first - orig_w};

  // Recurse on children and reorder them based on the original split direction
  if (orig_w >= orig_h) { // Original split was wide (A|B|C). After CW rotation, it's a tall split.
                         // The new order of children is C, B, A from top to bottom.
    Node *tempA = rotateNode(node->A, original_root_width);
    Node *tempB = rotateNode(node->B, original_root_width);
    Node *tempC = rotateNode(node->C, original_root_width);
    node->A = tempC;
    node->B = tempB;
    node->C = tempA;
  } else { // Original split was tall (A/B/C). After CW rotation, it's a wide split.
           // The new order of children is A, B, C from left to right.
    node->A = rotateNode(node->A, original_root_width);
    node->B = rotateNode(node->B, original_root_width);
    node->C = rotateNode(node->C, original_root_width);
  }

  return node;
}
