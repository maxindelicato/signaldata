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
#include "average_true_range.h"

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
xt::xtensor<double, 1> average_true_range_percent(xt::xtensor<double, 1> data, int period) {
    xt::xtensor<double, 1> atrp = (average_true_range(data, period) / data) * 100;
    return atrp;
};

}
