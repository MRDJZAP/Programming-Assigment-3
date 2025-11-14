/**
 * @file		pa3.cpp
 * @author		CPSC 221
 * @description	Partial test of PA3 functionality
 **/

#include "cs221util/PNG.h"
#include "threetree.h"
#include <iostream>

void printNode(Node* node, int depth = 0) {
  if (node == nullptr) return;
  
  string indent(depth * 2, ' ');
  cout << indent << "Node at (" << node->upleft.first << ", " << node->upleft.second 
       << ") size " << node->width << "x" << node->height << endl;
  
  if (node->A || node->B || node->C) {
    cout << indent << "  A:" << endl;
    printNode(node->A, depth + 2);
    cout << indent << "  B:" << endl;
    printNode(node->B, depth + 2);
    cout << indent << "  C:" << endl;
    printNode(node->C, depth + 2);
  }
}

int main() {

  // read in image
  PNG orig;
  orig.readFromFile("images-orig/et-384x216.png");

  // use it to build a ThreeTree (try other tolerances - use larger tolerances
  // for large images)
  ThreeTree t(orig, 6000.0);

  cout << "=== BEFORE ROTATION ===" << endl;
  cout << "Original image: " << orig.width() << "x" << orig.height() << endl;

  PNG pic = t.Render();
  cout << "Number of original pic nodes: " << t.Size() << endl;
  cout << "Number of original pic leaves: " << t.NumLeaves() << endl;

  cout << "\n=== AFTER ROTATION ===" << endl;
  t.RotateCW();
  PNG rotatedPic = t.Render();
  cout << "After rotation" << endl;

  // write it out
  pic.writeToFile("images-output/debug_before.png");
  rotatedPic.writeToFile("images-output/debug_after.png");

  return 0;
}