#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <opencv2/opencv.hpp>
using namespace cv;

int nx, ny, nz, N, maxrun;
double J, kb, T;
double h, h0, p;
int count=0;
int order[8][2] = {{-1, -1}, {-1, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, 0}, {0, 1}};

void display(Mat image);
Mat rgb2greyscale(Mat image, int nx, int ny);
void printoutput(Mat image, int nx, int ny);