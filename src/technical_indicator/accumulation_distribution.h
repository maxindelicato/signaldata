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
xt::xtensor<double, 1> accumulation_distribution(const xt::xtensor<double, 1>& close_data,
    const xt::xtensor<double, 1>& high_data, const xt::xtensor<double, 1>& low_data,
    const xt::xtensor<double, 1>& volume) {
    xt::xtensor<double, 1> ad = xt::zeros<double>({1, static_cast<int>(close_data.shape()[0])});
    for (auto i = 1; i < close_data.size(); i++) {
        ad(1, i) = (
            (((close_data(1, i) - low_data(1, i)) -
              (high_data(1, i) - close_data(1, i))) /
              (high_data(1, i) - low_data(1, i)) *
              volume(1, i)) +
            ad(1, i - 1)
        );
    }
    return ad;
};

}
