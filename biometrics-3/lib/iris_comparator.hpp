//
//  iris_comparator.hpp
//  biometrics-03
//
//  Created by Martin Kiesel on 06/04/16.
//  Copyright © 2016 Martin Kiesel. All rights reserved.
//

#ifndef iris_comparator_hpp
#define iris_comparator_hpp

#include <iostream>
#include <opencv2/opencv.hpp>

#include "iris.hpp"
#include "iris_file.hpp"

namespace Iris
{
    using cv::Mat;

    class Comparator
    {
        Iris i1_, i2_;
        Mat mask_;
        int best_shift_ = 0, best_distance_ = INT_MAX;

        void computeMask();
        int calculateHammingDistance();
    public:
        Comparator() {};
        Comparator(File image_1, File image_2);
        void setImages(File image_1, File image_2);
        void hammingDistance(int spread = 100);
        void reset();
        void display();
        inline int getBestShift() {return best_shift_;}
        inline int getBestDistance() {return best_distance_;}
    };
}

#endif /* iris_comparator_hpp */
