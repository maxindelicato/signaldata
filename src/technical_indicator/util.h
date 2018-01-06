#pragma once

#include <algorithm>
#include <iostream>
#include <list>
#include <numeric>
#include <string>
#include <vector>
#include "xtensor/xarray.hpp"
#include "xtensor/xeval.hpp"
#include "xtensor/xindex_view.hpp"
#include "xtensor/xio.hpp"
#include "xtensor/xmath.hpp"
#include "xtensor/xtensor.hpp"
#include "simple_moving_average.h"

namespace signaldata::technical_indicator::util {

/**
 * @brief Reverse sorts a series of values.
 *
 * @param data
 * @return
 */
xt::xtensor<double, 1> reverse(xt::xtensor<double, 1> data) {
    xt::xtensor<double, 1> rd = xt::zeros<double>({1, static_cast<int>(data.shape()[0])});
    for (auto i = 0; i < data.size(); i++)
        rd(1, i) = data(1, data.size() - i - 1);
    return rd;
};

/**
 * @brief Finds the first index of a value over a series of values.
 *
 * @param data
 * @param val
 * @return
 */
int index(xt::xtensor<double, 1> data, double val) {
    for (auto i = 0; i < data.size(); i++)
        if (data(1, i) == val)
            return i;
    return -1;
}

}
