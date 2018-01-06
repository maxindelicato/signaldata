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

namespace signaldata::technical_indicator {

/**
 * @brief Moving Average Center Band over a series of values.
 *
 * Formula:
 *      SMA(data)
 *
 * @param data
 * @param period
 * @return
 */
xt::xtensor<double, 1> moving_average_envelope_center_band(xt::xtensor<double, 1> data, int period) {
    auto sma = simple_moving_average(data, period);
    return sma;
};


/**
 * @brief Moving Average Upper Band over a series of values.
 *
 * Formula:
 *      ub = cb(t) * (1 + env_percentage)
 *
 * @param data
 * @param period
 * @return
 */
xt::xtensor<double, 1> moving_average_envelope_upper_band(xt::xtensor<double, 1> data, int period, double env_percentage) {
    auto cb = moving_average_envelope_center_band(data, period);
    xt::xtensor<double, 1> ub = xt::zeros<double>({1, static_cast<int>(data.shape()[0])});
    for (auto i = 0; i < data.size(); i++)
        ub(1, i) = cb(1, i) * (1 + env_percentage);
    return ub;
};


/**
 * @brief Moving Average Lower Band over a series of values.
 *
 * Formula:
 *      lb = cb * (1 - env_percentage)
 *
 * @param data
 * @param period
 * @return
 */
xt::xtensor<double, 1> moving_average_envelope_lower_band(xt::xtensor<double, 1> data, int period, double env_percentage) {
    auto cb = moving_average_envelope_center_band(data, period);
    xt::xtensor<double, 1> lb = xt::zeros<double>({1, static_cast<int>(data.shape()[0])});
    for (auto i = 0; i < data.size(); i++)
        lb(1, i) = cb(1, i) * (1 - env_percentage);
    return lb;
};

}
