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
#include "true_range.h"

namespace signaldata::technical_indicator {

/**
 * @brief Average True Range over a series of values.
 *
 * Formula:
 *      ATRt = ATRt-1 * (n - 1) + TRt / n
 *
 * @param data
 * @param period
 * @return
 */
xt::xtensor<double, 1> average_true_range(xt::xtensor<double, 1> data, int period) {
    xt::xtensor<double, 1> tr = true_range(data, period);
    xt::xtensor<double, 1> atr = xt::zeros<double>({1, static_cast<int>(tr.shape()[0])});
    xt::view(atr, xt::range(0, period - 1)) = xt::view(tr, xt::range(0, period - 1));
    xt::view(atr, xt::range(period-1, period - 1 + period - 1)) = xt::view(tr, xt::range(0, period - 1));
    xt::xtensor<double, 1> tr_sum = xt::sum(xt::view(tr, xt::range(period-1, period - 1 + period)));
    atr(1, period-1+period-1) = (1 / static_cast<double>(period)) * tr_sum(1, 0);
    for (auto i = period - 1 + period; i < tr.size(); i++)
        atr(1, i) = (atr(1, i - 1) * (period - 1) + tr(1, i)) / period;
    return atr;
};

}
