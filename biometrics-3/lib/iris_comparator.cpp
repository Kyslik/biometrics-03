//
//  iris_comparator.cpp
//  biometrics-03
//
//  Created by Martin Kiesel on 06/04/16.
//  Copyright © 2016 Martin Kiesel. All rights reserved.
//

#include "iris_comparator.hpp"


namespace Iris
{
    Comparator::Comparator(File image_1, File image_2)
    {
        i1_ = Iris(image_1);
        i2_ = Iris(image_2);
    }

    void Comparator::computeMask()
    {
        mask_ = i1_.getMask() | i2_.getMask();
    }

    int Comparator::calculateHammingDistance()
    {
        computeMask();
        return cv::norm(i1_.getBinIris(), i2_.getBinIris(), cv::NORM_HAMMING, mask_);
    }

    void Comparator::hammingDistance(int spread)
    {
        i2_.shift(spread * (- 1));

        for(int i = 0; i <= spread * 2; i++)
        {

            int temporary_distance = calculateHammingDistance();
            i2_.shift(1);
            if (best_distance_ < temporary_distance) continue;

            best_distance_ = temporary_distance;
            best_shift_ = i - spread;
        }

        i2_.shift(spread * (- 1));
    }

    void Comparator::display()
    {
        using cv::namedWindow;
        using cv::imshow;
        using cv::WINDOW_AUTOSIZE;
        using cv::waitKey;

        i2_.shift(best_shift_);
        computeMask();
        namedWindow("Image 1", WINDOW_AUTOSIZE);
        imshow("Image 1", i1_.getBinIris());
        namedWindow("Image 2", WINDOW_AUTOSIZE);
        imshow("Image 2", i2_.getBinIris());
        namedWindow("Mask", WINDOW_AUTOSIZE);
        imshow("Mask", mask_);
        waitKey(0);
    }
}