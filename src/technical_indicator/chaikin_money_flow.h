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
 * @brief Chaikin Money Flow over a series of values.
 *
 * Formula:
 *      CMF = SUM[(((Cn - Ln) - (Hn - Cn)) / (Hn - Ln)) * V] / SUM(Vn)
 *
 * @param close_data
 * @param high_data
 * @param low_data
 * @param volume
 * @param period
 * @return
 */
xt::xtensor<double, 1> chaikin_money_flow(const xt::xtensor<double, 1>& close_data,
    const xt::xtensor<double, 1>& high_data, const xt::xtensor<double, 1>& low_data,
    const xt::xtensor<double, 1>& volume, const int period) {
    xt::xtensor<double, 1> cmf = xt::zeros<double>({1, static_cast<int>(close_data.shape()[0])});
    for (auto i = period - 1; i < close_data.size(); i++) {
        xt::xtensor<double, 1> cd = xt::view(close_data, xt::range(i + 1 - period, i + 1));
        xt::xtensor<double, 1> hd = xt::view(high_data, xt::range(i + 1 - period, i + 1));
        xt::xtensor<double, 1> ld = xt::view(low_data, xt::range(i + 1 - period, i + 1));
        xt::xtensor<double, 1> v = xt::view(volume, xt::range(i + 1 - period, i + 1));

        xt::xtensor<double, 1> s_a = xt::sum((((cd - ld) - (hd - cd)) / (hd - ld)) * v);
        xt::xtensor<double, 1> s_b = xt::sum(v);

        cmf(1, i) = (s_a[0] / s_b[0]);
    }
    return cmf;
};

}
