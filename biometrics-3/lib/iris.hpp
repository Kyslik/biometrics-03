//
//  iris.hpp
//  biometrics-03
//
//  Created by Martin Kiesel on 06/04/16.
//  Copyright © 2016 Martin Kiesel. All rights reserved.
//

#ifndef iris_hpp
#define iris_hpp

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "iris_file.hpp"

namespace Iris
{
    using cv::Mat;
    using Iris::File;

    struct Iris {
        Mat iris, bin_iris, mask;
        Iris(File &file);
    };
}

#endif /* iris_hpp */
