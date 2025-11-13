/**
 * @file            stats.cpp
 * @author          your CWL
 * @description     Implementation of Stats functions
 *
 * THIS FILE WILL BE SUBMITTED
 **/

#include "stats.h"
#include "cs221util/RGBAPixel.h"
#include <cmath>
#include <cstdint>
#include <vector>

using namespace std;

// Private helper function to compute sum over a rectangle from a summed-area table
int64_t Stats::get_sum_from_table(const vector<vector<int64_t>> &table,
                                 pair<int, int> ul, int w, int h) {
  int x0 = ul.first;
  int y0 = ul.second;
  int x1 = x0 + w - 1;
  int y1 = y0 + h - 1;

  int64_t D = table[x1][y1];
  int64_t B = (x0 > 0) ? table[x0 - 1][y1] : 0;
  int64_t C = (y0 > 0) ? table[x1][y0 - 1] : 0;
  int64_t A = (x0 > 0 && y0 > 0) ? table[x0 - 1][y0 - 1] : 0;

  return D - B - C + A;
}

Stats::Stats(PNG &im) {
  // Resize all vectors to match image dimensions
  sumRed.resize(im.width(), vector<int64_t>(im.height(), 0));
  sumGreen.resize(im.width(), vector<int64_t>(im.height(), 0));
  sumBlue.resize(im.width(), vector<int64_t>(im.height(), 0));
  sumsqRed.resize(im.width(), vector<int64_t>(im.height(), 0));
  sumsqGreen.resize(im.width(), vector<int64_t>(im.height(), 0));
  sumsqBlue.resize(im.width(), vector<int64_t>(im.height(), 0));

  for (unsigned int x = 0; x < im.width(); x++) {
    for (unsigned int y = 0; y < im.height(); y++) {
      RGBAPixel *pixel = im.getPixel(x, y);
      buildRed(x, y, pixel);
      buildGreen(x, y, pixel);
      buildBlue(x, y, pixel);
    }
  }
}

int64_t Stats::GetSum(char channel, pair<int, int> ul, int w, int h) {
  switch (channel) {
  case 'r':
    return get_sum_from_table(sumRed, ul, w, h);
  case 'g':
    return get_sum_from_table(sumGreen, ul, w, h);
  case 'b':
    return get_sum_from_table(sumBlue, ul, w, h);
  default:
    return 0;
  }
}

int64_t Stats::GetSumSq(char channel, pair<int, int> ul, int w, int h) {
  switch (channel) {
  case 'r':
    return get_sum_from_table(sumsqRed, ul, w, h);
  case 'g':
    return get_sum_from_table(sumsqGreen, ul, w, h);
  case 'b':
    return get_sum_from_table(sumsqBlue, ul, w, h);
  default:
    return 0;
  }
}

/**
 * Given a rectangle, compute its sum of squared deviations from mean, over all
 * color channels. See written specification for a description of this function.
 **/
double Stats::GetVar(pair<int, int> ul, int w, int h) {
  double area = w * h;
  if (area <= 0) {
    return 0.0;
  }

  double redSum = GetSum('r', ul, w, h);
  double greenSum = GetSum('g', ul, w, h);
  double blueSum = GetSum('b', ul, w, h);

  double redSumSq = GetSumSq('r', ul, w, h);
  double greenSumSq = GetSumSq('g', ul, w, h);
  double blueSumSq = GetSumSq('b', ul, w, h);

  double redVar = redSumSq - (redSum * redSum) / area;
  double greenVar = greenSumSq - (greenSum * greenSum) / area;
  double blueVar = blueSumSq - (blueSum * blueSum) / area;

  return redVar + greenVar + blueVar;
}

RGBAPixel Stats::GetAvg(pair<int, int> ul, int w, int h) {
  double area = w * h;
  if (area <= 0) {
    return RGBAPixel(0, 0, 0);
  }
  uint8_t redAvg = GetSum('r', ul, w, h) / area;
  uint8_t greenAvg = GetSum('g', ul, w, h) / area;
  uint8_t blueAvg = GetSum('b', ul, w, h) / area;

  return RGBAPixel(redAvg, greenAvg, blueAvg);
}

/****************************************************************
 * IF YOU HAVE DEFINED ANY PRIVATE FUNCTIONS IN stats-private.h, *
 * ADD YOUR IMPLEMENTATIONS BELOW                                *
 ****************************************************************/

void Stats::buildRed(int x, int y, RGBAPixel *pixel) {
  if (x == 0 && y == 0) {
    sumRed[x][y] = pixel->r;
    sumsqRed[x][y] = pixel->r * pixel->r;
  } else if (x == 0) {
    sumRed[x][y] = sumRed[x][y - 1] + pixel->r;
    sumsqRed[x][y] = sumsqRed[x][y - 1] + (pixel->r * pixel->r);
  } else if (y == 0) {
    sumRed[x][y] = sumRed[x - 1][y] + pixel->r;
    sumsqRed[x][y] = sumsqRed[x - 1][y] + (pixel->r * pixel->r);
  } else {
    sumRed[x][y] =
        sumRed[x - 1][y] + (sumRed[x][y - 1] - sumRed[x - 1][y - 1]) + pixel->r;
    sumsqRed[x][y] = sumsqRed[x - 1][y] +
                     (sumsqRed[x][y - 1] - sumsqRed[x - 1][y - 1]) +
                     (pixel->r * pixel->r);
  }
}

void Stats::buildGreen(int x, int y, RGBAPixel *pixel) {
  if (x == 0 && y == 0) {
    sumGreen[x][y] = pixel->g;
    sumsqGreen[x][y] = pixel->g * pixel->g;
  } else if (x == 0) {
    sumGreen[x][y] = sumGreen[x][y - 1] + pixel->g;
    sumsqGreen[x][y] = sumsqGreen[x][y - 1] + (pixel->g * pixel->g);
  } else if (y == 0) {
    sumGreen[x][y] = sumGreen[x - 1][y] + pixel->g;
    sumsqGreen[x][y] = sumsqGreen[x - 1][y] + (pixel->g * pixel->g);
  } else {
    sumGreen[x][y] = sumGreen[x - 1][y] +
                     (sumGreen[x][y - 1] - sumGreen[x - 1][y - 1]) + pixel->g;
    sumsqGreen[x][y] = sumsqGreen[x - 1][y] +
                       (sumsqGreen[x][y - 1] - sumsqGreen[x - 1][y - 1]) +
                       (pixel->g * pixel->g);
  }
}

void Stats::buildBlue(int x, int y, RGBAPixel *pixel) {
  if (x == 0 && y == 0) {
    sumBlue[x][y] = pixel->b;
    sumsqBlue[x][y] = pixel->b * pixel->b;
  } else if (x == 0) {
    sumBlue[x][y] = sumBlue[x][y - 1] + pixel->b;
    sumsqBlue[x][y] = sumsqBlue[x][y - 1] + (pixel->b * pixel->b);
  } else if (y == 0) {
    sumBlue[x][y] = sumBlue[x - 1][y] + pixel->b;
    sumsqBlue[x][y] = sumsqBlue[x - 1][y] + (pixel->b * pixel->b);
  } else {
    sumBlue[x][y] = sumBlue[x - 1][y] +
                    (sumBlue[x][y - 1] - sumBlue[x - 1][y - 1]) + pixel->b;
    sumsqBlue[x][y] = sumsqBlue[x - 1][y] +
                      (sumsqBlue[x][y - 1] - sumsqBlue[x - 1][y - 1]) +
                      (pixel->b * pixel->b);
  }
}
