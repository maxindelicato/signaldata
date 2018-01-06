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
 * @brief Simple Moving Average.
 *
 * Formula:
 *      SUM(data / N)
 *
 * @param data
 * @param period
 * @return
 */
xt::xtensor<double, 1> simple_moving_average(xt::xtensor<double, 1> data, int period) {
    xt::xtensor<double, 1> smas = xt::zeros<double>({1, static_cast<int>(data.shape()[0])});
    for (auto i = 0; i < data.size(); i++)
        smas(1, i) = i < period - 1 ? 0 : xt::mean(xt::view(data, xt::range(i - (period - 1), i + 1)))[0];
    return smas;
}

}
