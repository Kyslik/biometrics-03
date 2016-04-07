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
        setImages(image_1, image_2);
    }

    void Comparator::reset()
    {
        best_shift_ = 0;
        best_distance_ = INT_MAX;
    }

    void Comparator::setImages(File image_1, File image_2)
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
        return cv::countNonZero(((i1_.getBinIris() ^ i2_.getBinIris()) & ~mask_));
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
        using cv::vconcat;
        using std::vector;

        i2_.shift(best_shift_);
        computeMask();

        std::cout   << "Best Masked Hamming Distance: "
                    << best_distance_ << std::endl
                    << "Shifted by: " << best_shift_
                    << " pixels" << std::endl;

        vector<Mat> vmat;
        Mat concatenated_bin, irises;

        vmat.push_back(i1_.getBinIris());
        vmat.push_back(i2_.getBinIris());
        vmat.push_back(mask_);

        cv::hconcat(i1_.getIris(), i2_.getIris(), irises);
        cv::vconcat(vmat, concatenated_bin);

        namedWindow("Concatenated BinIris 1 - 2 & mask", WINDOW_AUTOSIZE);
        imshow("Concatenated BinIris 1 - 2 & mask", concatenated_bin);
        namedWindow("Irises", WINDOW_AUTOSIZE);
        imshow("Irises", irises);

        waitKey(0);
    }
}