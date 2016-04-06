//
//  iris_file.cpp
//  biometrics-03
//
//  Created by Martin Kiesel on 06/04/16.
//  Copyright © 2016 Martin Kiesel. All rights reserved.
//

#include "iris_file.hpp"

#include <sys/stat.h>
#include <unistd.h>

const char kPathSeparator =
#if defined _WIN32 || defined __CYGWIN__
'\\';
#else
'/';
#endif

namespace Iris
{
    using std::count;

    static inline bool fileExists(const string &file_name);

    File::File(const string &file_name)
    {
        if (!fileExists(file_name)) return;
        path_ = getDirectory(file_name);
        iris_ = getIrisFile(getFileName(file_name));

        if (iris_.empty()) return;

        bin_iris_ = iris_ + "_template";
        mask_ = iris_ + "_mask";
        is_valid_ = true;
    }

    inline string File::getDirectory(const string &path)
    {
        return path.substr(0, path.find_last_of(kPathSeparator) + 1);
    }

    inline string File::getFileName(const string &path)
    {
        return removeExtension(path.substr(path.find_last_of(kPathSeparator) + 1));
    }

    //accepting only 001_1_1.bmp or 001_1_1_mask.bmp (2 or 3 underscores)
    inline string File::getIrisFile(const string &file)
    {
        size_t underscores = count(file.begin(), file.end(), '_');
        if (underscores == 2)
            return file;
        else if (underscores == 3)
            return file.substr(0, file.find_last_of('_'));
        else
            return "";

    }

    inline string File::removeExtension(const string &file)
    {
        return file.substr(0, file.find_last_of('.'));
    }

    string File::getFullName(const string &file)
    {
        return path_ + file + ".bmp";
    }

    static inline bool fileExists(const string &file_name)
    {
        struct stat buffer;
        return (stat (file_name.c_str(), &buffer) == 0);
    }
}





















