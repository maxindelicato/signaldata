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

namespace signaldata::technical_indicator {

/**
 * @brief Typical Price over a series of values.
 *
 * Formula:
 *      TPt = (HIGHt + LOWt + CLOSEt) / 3
 *
 * @param close_data
 * @param high_data
 * @param low_data
 * @return
 */
xt::xtensor<double, 1> typical_price(xt::xtensor<double, 1> close_data, xt::xtensor<double, 1> high_data, xt::xtensor<double, 1> low_data) {
    xt::xtensor<double, 1> tps = xt::zeros<double>({1, static_cast<int>(close_data.shape()[0])});
    for (auto i = 0; i < close_data.size(); i++)
        tps(1, i) = (high_data(1, i) + low_data(1, i) + close_data(1, i)) / 3;
    return tps;
};

}
