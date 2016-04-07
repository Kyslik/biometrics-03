//
//  iris_group.hpp
//  biometrics-03
//
//  Created by Martin Kiesel on 07/04/16.
//  Copyright © 2016 Martin Kiesel. All rights reserved.
//

#ifndef iris_group_hpp
#define iris_group_hpp

#include <iostream>
#include <vector>

#include "iris_file.hpp"

typedef std::vector<Iris::File> VIFile;

namespace Iris
{
    using std::string;
    using std::vector;

    class Group
    {
        bool is_valid_ = false;
        int group_id_ = 0;
        string group_id_padded_, path_;
        vector<int> compare_result_;
        VIFile vifile_;


        void fillVIFile();
        string formIrisName(int subgroup, int item);

    public:
        Group();
        Group(string path, int group_id) : path_(path), group_id_(group_id)
        {
            using std::to_string;
            is_valid_ = false;
            group_id_padded_ = to_string(group_id_);
            group_id_padded_ = string(3 - group_id_padded_.length(), '0') + group_id_padded_;

            fillVIFile();
        }
        inline bool isValid() {return is_valid_;}
        inline vector<int> getResult() {return compare_result_;}
        void compare();
    };

}


#endif /* iris_group_hpp */