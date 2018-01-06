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
xt::xtensor<double, 1> ichimoku_cloud_tenkansen(xt::xtensor<double, 1> data, int period) {
    xt::xtensor<double, 1> tenkansen = xt::zeros<double>({1, static_cast<int>(data.shape()[0])});
    for (auto i = 0; i < data.size(); i++) {
        if (i > period) {
            xt::xtensor<double, 1> tmax = xt::amax(xt::view(data, xt::range(i + 1 - period, i + 1)));
            xt::xtensor<double, 1> tmin = xt::amin(xt::view(data, xt::range(i + 1 - period, i + 1)));
            double t = (tmax[0] + tmin[0]) / 2;
            tenkansen(1, i) = t;
        }
    }
    return tenkansen;
};


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
xt::xtensor<double, 1> ichimoku_cloud_kijunsen(xt::xtensor<double, 1> data, int period) {
    xt::xtensor<double, 1> kijunsen = xt::zeros<double>({1, static_cast<int>(data.shape()[0])});
    for (auto i = 0; i < data.size(); i++) {
        if (i > period) {
            xt::xtensor<double, 1> kmax = xt::amax(xt::view(data, xt::range(i + 1 - period, i + 1)));
            xt::xtensor<double, 1> kmin = xt::amin(xt::view(data, xt::range(i + 1 - period, i + 1)));
            double k = (kmax[0] + kmin[0]) / 2;
            kijunsen(1, i) = k;
        }
    }
    return kijunsen;
};


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
xt::xtensor<double, 1> ichimoku_cloud_chiku_span(xt::xtensor<double, 1> data, int period) {
    xt::xtensor<double, 1> chiku_span = xt::view(data, xt::range(period - 1, static_cast<int>(data.shape()[0])));
    return chiku_span;
};


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
xt::xtensor<double, 1> ichimoku_cloud_senkou_a(xt::xtensor<double, 1> data, int period) {
    auto tperiod = 9;
    auto kperiod = period;
    xt::xtensor<double, 1> senkou_a = xt::zeros<double>({1, kperiod + static_cast<int>(data.shape()[0])});
    for (auto i = 0; i < data.size(); i++) {
        if (i < kperiod - 1)
            continue;

        xt::xtensor<double, 1> tmax = xt::amax(xt::view(data, xt::range(i + 1 - tperiod, i + 1)));
        xt::xtensor<double, 1> tmin = xt::amin(xt::view(data, xt::range(i + 1 - tperiod, i + 1)));
        double tenkansen = (tmax[0] + tmin[0]) / 2;

        xt::xtensor<double, 1> kmax = xt::amax(xt::view(data, xt::range(i + 1 - kperiod, i + 1)));
        xt::xtensor<double, 1> kmin = xt::amin(xt::view(data, xt::range(i + 1 - kperiod, i + 1)));
        double kijunsen = (kmax[0] + kmin[0]) / 2;

        double s = (tenkansen + kijunsen) / 2;
        senkou_a(1, kperiod + i) = s;
    }
    return senkou_a;
};


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
xt::xtensor<double, 1> ichimoku_cloud_senkou_b(xt::xtensor<double, 1> data, int period) {
    xt::xtensor<double, 1> senkou_b = xt::zeros<double>({1, period + static_cast<int>(data.shape()[0])});
    for (auto i = 0; i < data.size(); i++) {
        if (i < period -1)
            continue;

        xt::xtensor<double, 1> tmax = xt::amax(xt::view(data, xt::range(i + 1 - period, i + 1)));
        xt::xtensor<double, 1> tmin = xt::amin(xt::view(data, xt::range(i + 1 - period, i + 1)));
        double tenkansen = (tmax[0] + tmin[0]) / 2;
        senkou_b(1, period + i) = tenkansen;
    }
    return senkou_b;
};

}
