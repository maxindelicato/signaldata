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
 * @brief True Range over a series of values.
 *
 * Formula:
 *      TRt = MAX(abs(Ht - Lt), abs(Ht - Ct-1), abs(Lt - Ct-1))
 *
 * @param data
 * @param period
 * @return
 */
xt::xtensor<double, 1> true_range(const xt::xtensor<double, 1>& data, const int period) {
    xt::xtensor<double, 1> tr = xt::zeros<double>({1, static_cast<int>(data.shape()[0])});
    for (auto i = period - 1; i < data.size(); i++) {
        xt::xtensor<double, 1> tr_rollup = xt::zeros<double>({1, 3});
        xt::xtensor<double, 1> tr_max = xt::amax(xt::view(data, xt::range(i + 1 - period, i + 1)));
        xt::xtensor<double, 1> tr_min = xt::amin(xt::view(data, xt::range(i + 1 - period, i + 1)));
        tr_rollup(1, 0) = tr_max(1, 0) - tr_min(1, 0);
        tr_rollup(1, 1) = xt::abs(xt::amax(xt::view(data, xt::range(i + 1 - period, i + 1))))[0] -
            data(1, i - 1);
        tr_rollup(1, 2) = xt::abs(xt::amin(xt::view(data, xt::range(i + 1 - period, i + 1))))[0] -
            data(1, i - 1);
        xt::xtensor<double, 1> tr_rollup_max = xt::amax(tr_rollup);
        tr(1, i) = tr_rollup_max(1, 0);
    }
    return tr;
};

}
