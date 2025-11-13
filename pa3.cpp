/**
 * @file		pa3.cpp
 * @author		CPSC 221
 * @description	Partial test of PA3 functionality
 **/

#include "cs221util/PNG.h"
#include "threetree.h"
#include <iostream>

int main() {

  // read in image
  PNG orig;
  // orig.readFromFile("images-orig/small1.png");
  orig.readFromFile("images-orig/rolw-640x360.png");
  // orig.readFromFile("images-orig/et-384x216.png");
  /*
  orig.readFromFile("images-orig/small2.png");
  orig.readFromFile("images-orig/colour.png");
  orig.readFromFile("images-orig/et-384x216.png");
  orig.readFromFile("images-orig/rolw-640x360.png");
  orig.readFromFile("images-orig/ccwe-854x480.png");
  */

  // use it to build a ThreeTree (try other tolerances - use larger tolerances
  // for large images)
  ThreeTree t(orig, 6000.0);

  // copy the tree (to show you can)
  ThreeTree tCopy(t);

  // render the ThreeTree
  PNG pic = t.Render();
  cout << "Number of original pic nodes: " << t.Size() << endl;
  cout << "Number of original pic leaves: " << t.NumLeaves() << endl;
  PNG copyPic = tCopy.Render();
  cout << endl << "Number of copied pic nodes: " << tCopy.Size() << endl;
  cout << "Number of copied pic leaves: " << tCopy.NumLeaves() << endl;

  t.RotateCW();
  PNG rotatedPic = t.Render();

  // write it out
  pic.writeToFile("images-output/small1.png");
  copyPic.writeToFile("images-output/small1Copy.png");
  rotatedPic.writeToFile("images-output/small1Rotated.png");

  return 0;
}
