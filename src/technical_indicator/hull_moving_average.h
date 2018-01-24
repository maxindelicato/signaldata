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
#include "weighted_moving_average.h"

namespace signaldata::technical_indicator {

/**
 * @brief Hull Moving Average over a series of values.
 *
 * Formula:
 *      HMA = WMA(2*WMA(n/2) - WMA(n)), sqrt(n)
 *
 * @param close_data
 * @param high_data
 * @param low_data
 * @param volume
 * @return
 */
xt::xtensor<double, 1> hull_moving_average(const xt::xtensor<double, 1>& data, const int period) {
    xt::xtensor<double, 1> hma = xt::zeros<double>({1, static_cast<int>(data.shape()[0])});
//    hma = wma(
//        2 * wma(data, int(period/2)) - wma(data, period), int(np.sqrt(period))
//    )
    hma = weighted_moving_average(
        2 * weighted_moving_average(data, static_cast<int>(period / 2)) - weighted_moving_average(data, period), static_cast<int>(std::sqrt(period))
    );
    // TODO: Investigate why this hack is necessary
    for (auto i = 0; i < period; i++)
        hma(1, i) = 0.0;
    return hma;
};

}
