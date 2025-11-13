/**
 * @file        stats-private.h
 * @author      CPSC 221
 * @description Declaration of private attributes and/or functions for Stats
 *
 * Add your declarations in this file. There is no need to qualify them with a
 * class name, as this file is entirely included into line 85 of stats.h
 *
 * THIS FILE WILL BE SUBMITTED
 **/

/* PRE: x and y >= 0
 * MOD: this
 * POST: builds the sum of all the red chanells sumRed including the sumSqRed
 * starting from (0,0) to (x,y)
 */
#include "cs221util/RGBAPixel.h"
void buildRed(int x, int y, cs221util::RGBAPixel *pixel);

/* PRE: x and y >= 0
 * MOD: this
 * POST: builds the sum of all the green channels sumGreen including the
 * sumSqGreen starting from (0,0) to (x,y)
 */
void buildGreen(int x, int y, cs221util::RGBAPixel *pixel);

/* PRE: x and y >= 0
 * MOD: this
 * POST: builds the sum of all the blue channels subBlue including the sumSqBlue
 * starting from (0,0) to (x,y)
 */
void buildBlue(int x, int y, cs221util::RGBAPixel *pixel);

// Private helper function to compute sum over a rectangle from a summed-area table
int64_t get_sum_from_table(const vector<vector<int64_t>> &table,
                                 pair<int, int> ul, int w, int h);
