// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#ifndef POWER_GRID_MODEL_MAIN_CORE_CALCULATION_INFO_HPP
#define POWER_GRID_MODEL_MAIN_CORE_CALCULATION_INFO_HPP

#include "../power_grid_model.hpp"

namespace power_grid_model::main_core {

inline CalculationInfo merge_calculation_info(std::vector<CalculationInfo> const& infos) {
    CalculationInfo result;

    auto const key = Timer::make_key(2226, "Max number of iterations");
    for (auto const& info : infos) {
        for (auto const& [k, v] : info) {
            if (k == key) {
                result[k] = std::max(result[k], v);
            } else {
                result[k] += v;
            }
        }
    }

    return result;
}

} // namespace power_grid_model::main_core

#endif
