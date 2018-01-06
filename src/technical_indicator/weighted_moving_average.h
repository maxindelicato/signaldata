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
 * @brief Weighted Moving Average over a series of values.
 *
 * Formula:
 *      (P1 + 2 P2 + 3 P3 + ... + n Pn) / K
 *      where K = (1+2+...+n) = n(n+1)/2 and Pn is the most recent price
 *
 * @param data
 * @param period
 * @return
 */
xt::xtensor<double, 1> weighted_moving_average(xt::xtensor<double, 1> data, int period) {
    auto k = (period * (period +1)) / 2.0;
    xt::xtensor<double, 1> wmas = xt::zeros<double>({1, static_cast<int>(data.shape()[0])});
    for (auto i = 0; i < (data.size() - period + 1); i++) {
        std::vector<double> product{};
        for (auto j = 0; j < period; j++)
            product.push_back(data(1, i + j) * (j + 1));
        auto wma = std::accumulate(std::begin(product), std::end(product), 0.0) / k;
        wmas(1, period - 1 + i) = wma;
    }
    return wmas;
};

}
