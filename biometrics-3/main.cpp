//
//  main.cpp
//  biometrics-3
//
//  Created by Martin Kiesel on 05/04/16.
//  Copyright © 2016 Martin Kiesel. All rights reserved.
//

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#include "lib/iris_comparator.hpp"

const std::string kVersion = "1.0.0";

int main(int argc, const char * argv[])
{
    using std::cout;
    using std::endl;
    using std::string;

    const cv::String keys =
    "{help h usage ? || print this message }"
    "{compare c      || compare mode       }"
    "{img f          || image to compare (provide image to eye ex: 001_1_1.bmp) }"
    "{img-two s      || image2 to compare  }"
    "{experiment e   || experiment number"
        "\n\t\t\t1 - compare pairs from one class"
        "\n\t\t\t2 - compare pairs from all classes}"
    ;

    cv::CommandLineParser parser(argc, argv, keys);

    parser.about("Biometric-03 v" + kVersion);

    if (parser.has("help") || argc == 1)
    {
        parser.printMessage();
        return 0;
    }

    if (parser.has("compare"))
    {
        if (parser.has("img") && parser.has("img-two"))
        {
            using Iris::File;
            using Iris::Comparator;

            string img_1 = parser.get<string>("img");
            string img_2 = parser.get<string>("img-two");

            File image_1 = File(img_1);
            File image_2 = File(img_2);

            if (!image_1.isValid() || !image_2.isValid()) return 1;
            if (image_1.getIris() == image_2.getIris()) return 2;

            Comparator comparator = Comparator(image_1, image_2);
            comparator.hammingDistance(80);
            cout << comparator.getBestDistance() << endl;
            comparator.display();

            return 0;
        }
        else
        {
            cout << "pictures to compare were not provided" << endl;
            return 0;
        }
    }

//    int experiment_no = parser.get<int>("experiment");
//
//    if (!parser.check())
//    {
//        parser.printErrors();
//        return 0;
//    }

    return 0;

//    Mat image, image2, image3;
//    image = imread("./data/001_2_4_mask.bmp", IMREAD_UNCHANGED);
//    image2 = imread("./data/004_2_2_mask.bmp", IMREAD_UNCHANGED);
//
//
//
//    namedWindow("i1", WINDOW_AUTOSIZE );
//    imshow("i1", image);
//    shift(image, image, Point(150, 0), BORDER_WRAP);
//    namedWindow("i2", WINDOW_AUTOSIZE );
//    imshow("i2", image);
//    waitKey(0);
//    return 0;
}