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
#include "typical_price.h"

namespace signaldata::technical_indicator {

/**
 * @brief Money Flow over a series of values.
 *
 * Formula:
 *      MF = VOLUME * TYPICAL PRICE
 *
 * @param data
 * @param period
 * @return
 */
xt::xtensor<double, 1> money_flow(xt::xtensor<double, 1> volume, xt::xtensor<double, 1> close_data, xt::xtensor<double, 1> high_data, xt::xtensor<double, 1> low_data) {
    xt::xtensor<double, 1> tps = typical_price(close_data, high_data, low_data);
    xt::xtensor<double, 1> mfs = volume * tps;
    return mfs;
};

}
