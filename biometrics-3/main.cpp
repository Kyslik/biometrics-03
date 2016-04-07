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
#include "lib/iris_group.hpp"

const std::string kVersion = "1.0.0";

int main(int argc, const char * argv[])
{
    using std::cout;
    using std::endl;
    using std::string;

    const cv::String keys =
    "{help h usage ? || print this message }"
    "{compare c      || compare mode       }"
    "{img f          || image to compare (ex: 001_1_1(_*).bmp) }"
    "{img-two s      || image2 to compare  }"
    "{experiment e   || experiment number"
        "\n\t\t\t1 - compare pairs from one class"
        "\n\t\t\t2 - compare pairs from all classes}"
    "{path p         | ./data | path to data (*.bmp files)}"
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
            comparator.display();
            return 0;
        }
        else
        {
            cout << "pictures to compare were not provided" << endl;
            return 0;
        }
    }

    Iris::Group group("./data/", 1);
    group.compare();
    int experiment_no = parser.get<int>("experiment");
    experiment_no;

    if (!parser.check())
    {
        parser.printErrors();
        return 0;
    }

    return 0;
}