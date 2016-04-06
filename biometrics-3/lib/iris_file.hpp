//
//  iris_file.hpp
//  biometrics-03
//
//  Created by Martin Kiesel on 06/04/16.
//  Copyright © 2016 Martin Kiesel. All rights reserved.
//

#ifndef iris_file_hpp
#define iris_file_hpp

#include <iostream>

namespace Iris
{
    using std::string;
    
    struct File
    {
        File(const string &file_name);
        inline bool isValid() {return is_valid_;}
        inline string getIris() {return getFullName(iris_);}
        inline string getBinIris() {return getFullName(bin_iris_);};
        inline string getMask() {return getFullName(mask_);};

    private:
        string iris_, bin_iris_, mask_, path_;
        bool is_valid_ = false;

        string getFullName(const string &file);
        inline string getDirectory(const string &path);
        inline string getFileName(const string &path);
        inline string getIrisFile(const string &file);
        inline string removeExtension(const string &file);
    };

}


#endif /* iris_file_hpp */