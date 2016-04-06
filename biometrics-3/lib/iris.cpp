//
//  iris.cpp
//  biometrics-03
//
//  Created by Martin Kiesel on 06/04/16.
//  Copyright © 2016 Martin Kiesel. All rights reserved.
//

#include "iris.hpp"

namespace Iris
{
    Iris::Iris(File &file)
    {
        using cv::imread;
        using cv::IMREAD_UNCHANGED;
        
        iris = imread(file.getIris(), IMREAD_UNCHANGED);
        bin_iris = imread(file.getBinIris(), IMREAD_UNCHANGED);
        mask = imread(file.getMask(), IMREAD_UNCHANGED);
    }
}