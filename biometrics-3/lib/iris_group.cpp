//
//  iris_group.cpp
//  biometrics-03
//
//  Created by Martin Kiesel on 07/04/16.
//  Copyright © 2016 Martin Kiesel. All rights reserved.
//

#include "iris_group.hpp"
#include "iris_comparator.hpp"

namespace Iris
{
    using std::string;
    using std::to_string;

    void Group::compare()
    {
        Comparator comparator;
        int viris_size = static_cast<int>(vifile_.size());
        int compare_count = ((viris_size - 1) * viris_size) / 2;

        for (int i = 0; i < viris_size - 1; i++)
        {
            for (int j = i + 1; j < viris_size; j++)
            {
                comparator.setImages(vifile_[i], vifile_[j]);
                comparator.hammingDistance();
                compare_result_.push_back(comparator.getBestDistance());
                comparator.reset();
            }
        }
    }

    void Group::fillVIFile()
    {
        int subgroup = 1,
            item = 1;

        for (int i = 1; i < 8; i++)
        {
            File file(path_ + formIrisName(subgroup, item));
            if (!file.isValid()) return;

            vifile_.push_back(file);
            if (i % 3 == 0 && i < 4)
            {
                subgroup++;
                item = 1;
                continue;
            }
            else
                item++;
        }

        is_valid_ = true;
    }

    string Group::formIrisName(int subgroup, int item)
    {
        return group_id_padded_
                        + "_" + to_string(subgroup)
                        + "_" + to_string(item)
                        + ".bmp";
    }
}