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
 * @brief Standard Deviation over a series of values.
 *
 * Formula:
 *      std = sqrt(avg(abs(x - avg(x))^2))
 *
 * @param data
 * @param period
 * @return
 */
xt::xtensor<double, 1> standard_deviation(xt::xtensor<double, 1> data, int period) {
    xt::xtensor<double, 1> sds = xt::zeros<double>({1, static_cast<int>(data.shape()[0])});
    for (auto i = 0; i < data.size(); i++) {
        if (i < period -1)
            continue;

        xt::xtensor<double, 1> x = xt::view(data, xt::range(i + 1 - period, i + 1));
        xt::xtensor<double, 1> sd = xt::sqrt(xt::mean_ddof(xt::pow(xt::abs(x - xt::mean(x)), 2), 1));
        sds(1, i) = sd[0];
    }
    return sds;
};

}
