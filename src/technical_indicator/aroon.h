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
#include "util.h"


namespace signaldata::technical_indicator {

/**
 * @brief Aroon Up over a series of values.
 *
 * Formula:
 *      AROONUP = (((PERIOD) - (PERIODS since PERIOD high)) / (PERIOD)) * 100
 *
 * @param data
 * @param period
 * @return
 */
xt::xtensor<double, 1> aroon_up(xt::xtensor<double, 1> data, int period) {
    xt::xtensor<double, 1> au = xt::zeros<double>({1, static_cast<int>(data.shape()[0])});
    for (auto i = period - 1; i < data.size(); i++) {
        xt::xtensor<double, 1>  rd = util::reverse(xt::view(data, xt::range(i + 1 - period, i + 1)));
        xt::xtensor<double, 1> rd_max = xt::amax(xt::view(data, xt::range(i + 1 - period, i + 1)));
        auto idx = util::index(rd, rd_max(1, 0));
        au(1, i) = ((period - idx) / static_cast<double>(period)) * 100;
    }
    return au;
};


/**
 * @brief Aroon Down over a series of values.
 *
 * Formula:
 *      AROONDWN = (((PERIOD) - (PERIODS SINCE PERIOD LOW)) / (PERIOD)) * 100
 *
 * @param data
 * @param period
 * @return
 */
xt::xtensor<double, 1> aroon_down(xt::xtensor<double, 1> data, int period) {
    xt::xtensor<double, 1> ad = xt::zeros<double>({1, static_cast<int>(data.shape()[0])});
    for (auto i = period - 1; i < data.size(); i++) {
        xt::xtensor<double, 1>  rd = util::reverse(xt::view(data, xt::range(i + 1 - period, i + 1)));
        xt::xtensor<double, 1> rd_min = xt::amin(xt::view(data, xt::range(i + 1 - period, i + 1)));
        auto idx = util::index(rd, rd_min(1, 0));
        ad(1, i) = ((period - idx) / static_cast<double>(period)) * 100;
    }
    return ad;
};

}
