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

#include "iris_file.hpp"

namespace Iris
{
    using cv::Mat;
    using Iris::File;

    struct Iris {
        Iris(){};
        Iris(File &file);
        
        inline Mat getIris() {return iris_;}
        inline Mat getBinIris() {return bin_iris_;}
        inline Mat getMask() {return mask_;}
        void shift(int shift_by = 1);
    private:
        Mat iris_, bin_iris_, mask_;

        void shiftMask(int shift_by = 1);
        void shiftBinIris(int shift_by = 1);
    };
}

#endif /* iris_hpp */
