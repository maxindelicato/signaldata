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
#include "util.h"


namespace signaldata::technical_indicator {

/**
 * @brief Accumulation/Distribution over a series of values.
 *
 * Formula:
 *      A/D = (Ct - Lt) - (Ht - Ct) / (Ht - Lt) * Vt + A/Dt-1
 *
 * @param close_data
 * @param high_data
 * @param low_data
 * @param volume
 * @return
 */
xt::xtensor<double, 1> upper_bollinger_band(const xt::xtensor<double, 1>& data, int period, double std_mult) {
    xt::xtensor<double, 1> sma = simple_moving_average(data, period);
    xt::xtensor<double, 1> sma_bb_range= xt::view(sma, xt::range(period - 1, sma.size()));
    xt::xtensor<double, 1> upper_bb = xt::zeros<double>({1, static_cast<int>(data.shape()[0])});
    for (auto i = 0; i < data.size() - period + 1; i++) {
        double std_dev = util::standard_deviation(xt::view(data, xt::range(i, i + period)), 0);
        upper_bb(1, i + period - 1) = sma_bb_range(1, i) + std_dev * std_mult;
    }
    return upper_bb;
};

xt::xtensor<double, 1> middle_bollinger_band(const xt::xtensor<double, 1>& data, int period, double std_mult) {
    auto mid_bb = simple_moving_average(data, period);
    return mid_bb;
};

xt::xtensor<double, 1> lower_bollinger_band(const xt::xtensor<double, 1>& data, int period, double std_mult) {
    xt::xtensor<double, 1> sma = simple_moving_average(data, period);
    xt::xtensor<double, 1> sma_bb_range= xt::view(sma, xt::range(period - 1, sma.size()));
    xt::xtensor<double, 1> lower_bb = xt::zeros<double>({1, static_cast<int>(data.shape()[0])});
    for (auto i = 0; i < data.size() - period + 1; i++) {
        double std_dev = util::standard_deviation(xt::view(data, xt::range(i, i + period)), 0);
        lower_bb(1, i + period - 1) = sma_bb_range(1, i) - std_dev * std_mult;
    }
    return lower_bb;
};

xt::xtensor<double, 1> bandwidth(const xt::xtensor<double, 1>& data, int period, double std_mult) {
    xt::xtensor<double, 1> bandwidth = ((upper_bollinger_band(data, period, std_mult)
                                         - lower_bollinger_band(data, period, std_mult))
                                        / middle_bollinger_band(data, period, std_mult));
    return bandwidth;
};

xt::xtensor<double, 1> bb_range(const xt::xtensor<double, 1>& data, int period, double std_mult) {
    xt::xtensor<double, 1> bb_range = (upper_bollinger_band(data, period, std_mult) - lower_bollinger_band(data, period, std_mult));
    return bb_range;
};

xt::xtensor<double, 1> percent_bandwidth(const xt::xtensor<double, 1>& data, int period, double std_mult) {
    xt::xtensor<double, 1> percent_bandwidth = ((data - lower_bollinger_band(data, period, std_mult)) / bb_range(data, period, std_mult));
    return percent_bandwidth;
};

xt::xtensor<double, 1> percent_b(const xt::xtensor<double, 1>& data, int period, double upper_bb_std_mult, double lower_bb_std_mult) {
    xt::xtensor<double, 1> lb = lower_bollinger_band(data, period, lower_bb_std_mult);
    xt::xtensor<double, 1> ub = upper_bollinger_band(data, period, upper_bb_std_mult);
    auto percent_b = ((data - lb) / (ub - lb)) * 100;
    return percent_b;
};

}
