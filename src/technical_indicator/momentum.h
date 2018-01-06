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
 * @brief Momentum over a series of values.
 *
 * Formula:
 *      DATA[i] - DATA[i - period]
 *
 * @param data
 * @param period
 * @return
 */
xt::xtensor<double, 1> momentum(xt::xtensor<double, 1> data, int period) {
    xt::xtensor<double, 1> moms = xt::zeros<double>({1, static_cast<int>(data.shape()[0])});
    for (auto i = 0; i < data.size(); i++)
        moms(1, i) = i < period - 1 ? 0 : data[i] - data[i + 1 - period];
    return moms;
};

}
