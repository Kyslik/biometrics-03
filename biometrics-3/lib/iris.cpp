//
//  iris.cpp
//  biometrics-03
//
//  Created by Martin Kiesel on 06/04/16.
//  Copyright © 2016 Martin Kiesel. All rights reserved.
//

#include "iris.hpp"
#include "shift.hpp"

namespace Iris
{
    Iris::Iris(File &file)
    {
        using cv::imread;
        using cv::IMREAD_UNCHANGED;

        iris_ = imread(file.getIris(), IMREAD_UNCHANGED);
        bin_iris_ = imread(file.getBinIris(), IMREAD_UNCHANGED);
        mask_ = imread(file.getMask(), IMREAD_UNCHANGED);
    }

    void Iris::shift(int shift_by)
    {
        shiftMask(shift_by);
        shiftBinIris(shift_by);
    }

    void Iris::shiftMask(int shift_by)
    {
        cv::shift(mask_, mask_, cv::Point(shift_by, 0), cv::BORDER_WRAP);
    }

    void Iris::shiftBinIris(int shift_by)
    {
        cv::shift(bin_iris_, bin_iris_, cv::Point(shift_by, 0), cv::BORDER_WRAP);
    }
}