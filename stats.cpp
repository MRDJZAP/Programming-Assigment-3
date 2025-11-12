/**
 * @file            stats.cpp
 * @author          your CWL
 * @description     Implementation of Stats functions
 *
 * THIS FILE WILL BE SUBMITTED
**/

#include "stats.h"
#include "cs221util/RGBAPixel.h"
#include <cstdint>

Stats::Stats(PNG& im) {
    for (int x = 0; x < im.width(); x++) {
        for (int y = 0; y < im.height(); y++) {
            buildRed(x, y, im.getPixel(x, y));
            buildGreen(x, y, im.getPixel(x, y));
            buildBlue(x, y, im.getPixel(x, y));
        }
    }
}


int64_t Stats::GetSum(char channel, pair<int, int> ul, int w, int h) {
    int64_t result = 0;
    bool bothZero = false;
    bool oneZero = false;

    if (ul.first == 0 && ul.second) {
        bothZero = true;
    } else if (ul.first == 0 || ul.second == 0){
        oneZero = true;
    }

    if (channel == 'r') {
        if (bothZero) {
            result = sumRed[w-1][h-1];
        } else if (oneZero) {
            if (ul.second == 0) {
                result = sumRed[ul.first + (w-1)][ul.second + (h-1)] - sumRed[ul.first-1][ul.second + (h-1)];
            } else {
                result = sumRed[ul.first + (w-1)][ul.first + (h-1)] - sumRed[ul.first + (w-1)][ul.second - 1];
            }
        } else {
            result = sumRed[ul.first + (w-1)][ul.second + (h-1)] - sumRed[ul.first - 1][ul.second + (h-1)] -
                (sumRed[ul.first + (w-1)][ul.second -1] - sumRed[ul.first-1][ul.second-1]);
        }
    } else if (channel == 'g') {
        if (bothZero) {
            result = sumGreen[w-1][h-1];
        } else if (oneZero) {
            if (ul.second == 0) {
                result = sumGreen[ul.first + (w-1)][ul.second + (h-1)] - sumGreen[ul.first-1][ul.second + (h-1)];
            } else {
                result = sumGreen[ul.first + (w-1)][ul.first + (h-1)] - sumGreen[ul.first + (w-1)][ul.second - 1];
            }
        } else {
            result = sumGreen[ul.first + (w-1)][ul.second + (h-1)] - sumGreen[ul.first - 1][ul.second + (h-1)] -
                (sumGreen[ul.first + (w-1)][ul.second -1] - sumGreen[ul.first-1][ul.second-1]);
        }
    } else {
        if (bothZero) {
            result = sumBlue[w-1][h-1];
        } else if (oneZero) {
            if (ul.second == 0) {
                result = sumBlue[ul.first + (w-1)][ul.second + (h-1)] - sumBlue[ul.first-1][ul.second + (h-1)];
            } else {
                result = sumBlue[ul.first + (w-1)][ul.first + (h-1)] - sumBlue[ul.first + (w-1)][ul.second - 1];
            }
        } else {
            result = sumBlue[ul.first + (w-1)][ul.second + (h-1)] - sumBlue[ul.first - 1][ul.second + (h-1)] -
                (sumBlue[ul.first + (w-1)][ul.second -1] - sumBlue[ul.first-1][ul.second-1]);
        }
    }

    return  result;
}

int64_t Stats::GetSumSq(char channel, pair<int, int> ul, int w, int h) {
    int64_t result = 0;
    bool bothZero = false;
    bool oneZero = false;

    if (ul.first == 0 && ul.second) {
        bothZero = true;
    } else if (ul.first == 0 || ul.second == 0){
        oneZero = true;
    }

    if (channel == 'r') {
        if (bothZero) {
            result = sumsqRed[w-1][h-1];
        } else if (oneZero) {
            if (ul.second == 0) {
                result = sumsqRed[ul.first + (w-1)][ul.second + (h-1)] - sumsqRed[ul.first-1][ul.second + (h-1)];
            } else {
                result = sumsqRed[ul.first + (w-1)][ul.first + (h-1)] - sumsqRed[ul.first + (w-1)][ul.second - 1];
            }
        } else {
            result = sumsqRed[ul.first + (w-1)][ul.second + (h-1)] - sumsqRed[ul.first - 1][ul.second + (h-1)] -
                (sumsqRed[ul.first + (w-1)][ul.second -1] - sumsqRed[ul.first-1][ul.second-1]);
        }
    } else if (channel == 'g') {
        if (bothZero) {
            result = sumsqGreen[w-1][h-1];
        } else if (oneZero) {
            if (ul.second == 0) {
                result = sumsqGreen[ul.first + (w-1)][ul.second + (h-1)] - sumsqGreen[ul.first-1][ul.second + (h-1)];
            } else {
                result = sumsqGreen[ul.first + (w-1)][ul.first + (h-1)] - sumsqGreen[ul.first + (w-1)][ul.second - 1];
            }
        } else {
            result = sumsqGreen[ul.first + (w-1)][ul.second + (h-1)] - sumsqGreen[ul.first - 1][ul.second + (h-1)] -
                (sumsqGreen[ul.first + (w-1)][ul.second -1] - sumsqGreen[ul.first-1][ul.second-1]);
        }
    } else {
        if (bothZero) {
            result = sumsqBlue[w-1][h-1];
        } else if (oneZero) {
            if (ul.second == 0) {
                result = sumsqBlue[ul.first + (w-1)][ul.second + (h-1)] - sumsqBlue[ul.first-1][ul.second + (h-1)];
            } else {
                result = sumsqBlue[ul.first + (w-1)][ul.first + (h-1)] - sumsqBlue[ul.first + (w-1)][ul.second - 1];
            }
        } else {
            result = sumsqBlue[ul.first + (w-1)][ul.second + (h-1)] - sumsqBlue[ul.first - 1][ul.second + (h-1)] -
                (sumsqBlue[ul.first + (w-1)][ul.second -1] - sumsqBlue[ul.first-1][ul.second-1]);
        }
    }

    return  result;
}

/**
 * Given a rectangle, compute its sum of squared deviations from mean, over all color channels.
 * See written specification for a description of this function.
**/
double Stats::GetVar(pair<int, int> ul, int w, int h) {
	/* Replace the line below with your implementation */
	return 0;
}


RGBAPixel Stats::GetAvg(pair<int, int> ul, int w, int h) {
	/* Replace the line below with your implementation */
	return RGBAPixel();
}

/****************************************************************
* IF YOU HAVE DEFINED ANY PRIVATE FUNCTIONS IN stats-private.h, *
* ADD YOUR IMPLEMENTATIONS BELOW                                *
****************************************************************/

void Stats::buildRed(int x, int y, RGBAPixel* pixel) {
    if (x == 0 && y == 0) {
        sumRed[x][y] = pixel->r;
        sumsqRed[x][y] = pixel->r * pixel->r;
    }

    if (x == 0) {
        sumRed[x][y] = sumRed[x][y-1] + pixel->r;
        sumsqRed[x][y] = sumsqRed[x][y-1] + (pixel->r * pixel->r);
    } else if (y == 0) {
        sumRed[x][y] = sumRed[x-1][y] + pixel->r;
        sumsqRed[x][y] = sumsqRed[x-1][y] + (pixel->r * pixel->r);
    } else {
        sumRed[x][y] = sumRed[x-1][y] + (sumRed[x][y-1] - sumRed[x-1][y-1]) + pixel->r;
        sumsqRed[x][y] = sumsqRed[x-1][y] + (sumsqRed[x][y-1] - sumsqRed[x-1][y-1]) + (pixel->r * pixel->r);
    }
}

void Stats::buildGreen(int x, int y, RGBAPixel* pixel) {
    if (x == 0 && y == 0) {
        sumGreen[x][y] = pixel->g;
        sumsqGreen[x][y] = pixel->g * pixel->g;
    }

    if (x == 0) {
        sumGreen[x][y] = sumGreen[x][y-1] + pixel->g;
        sumsqGreen[x][y] = sumsqGreen[x][y-1] + (pixel->g * pixel->g);
    } else if (y == 0) {
        sumGreen[x][y] = sumGreen[x-1][y] + pixel->g;
        sumsqGreen[x][y] = sumsqGreen[x-1][y] + (pixel->g * pixel->g);
    } else {
        sumGreen[x][y] = sumGreen[x-1][y] + (sumGreen[x][y-1] - sumGreen[x-1][y-1]) + pixel->g;
        sumsqGreen[x][y] = sumsqGreen[x-1][y] + (sumsqGreen[x][y-1] - sumsqGreen[x-1][y-1]) + (pixel->g * pixel->g);
    }
}

void Stats::buildBlue(int x, int y, RGBAPixel* pixel) {
    if (x == 0 && y == 0) {
        sumBlue[x][y] = pixel->b;
        sumsqBlue[x][y] = pixel->b * pixel->b;
    }

    if (x == 0) {
        sumBlue[x][y] = sumBlue[x][y-1] + pixel->b;
        sumsqBlue[x][y] = sumsqBlue[x][y-1] + (pixel->b * pixel->b);
    } else if (y == 0) {
        sumBlue[x][y] = sumBlue[x-1][y] + pixel->b;
        sumsqBlue[x][y] = sumsqBlue[x-1][y] + (pixel->b * pixel->b);
    } else {
        sumBlue[x][y] = sumBlue[x-1][y] + (sumBlue[x][y-1] - sumBlue[x-1][y-1]) + pixel->b;
        sumsqBlue[x][y] = sumsqBlue[x-1][y] + (sumsqBlue[x][y-1] - sumsqBlue[x-1][y-1]) + (pixel->b * pixel->b);
    }
}
