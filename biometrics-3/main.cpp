//
//  main.cpp
//  biometrics-3
//
//  Created by Martin Kiesel on 05/04/16.
//  Copyright © 2016 Martin Kiesel. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "shift.hpp"

using namespace std;
using namespace cv;

int main(int argc, const char * argv[])
{
    Mat image, image2, image3;
    image = imread("./data/001_2_4_mask.bmp", IMREAD_UNCHANGED);
    image2 = imread("./data/004_2_2_mask.bmp", IMREAD_UNCHANGED);



    namedWindow("i1", WINDOW_AUTOSIZE );
    imshow("i1", image);
    shift(image, image, Point(150, 0), BORDER_WRAP);
    namedWindow("i2", WINDOW_AUTOSIZE );
    imshow("i2", image);
    waitKey(0);
    return 0;
}