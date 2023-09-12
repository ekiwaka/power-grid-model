// SPDX-FileCopyrightText: 2022 Contributors to the Power Grid Model project <dynamic.grid.calculation@alliander.com>
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#ifndef POWER_GRID_MODEL_MAIN_CORE_TOPOLOGY_INDEX_HPP
#define POWER_GRID_MODEL_MAIN_CORE_TOPOLOGY_INDEX_HPP

#include "../power_grid_model.hpp"

#include <boost/range.hpp>

namespace power_grid_model::main_core {

class SparseIdxVector {

  public:
    SparseIdxVector(IdxVector const& data) : data_(data) {}

    auto subset(Idx location) { return std::pair<Idx, size_t>{data_[location], data_[location + 1] - data_[location]}; }

  private:
    IdxVector data_;
};

template <class T> class SparseVectorData {
  public:
    SparseVectorData(std::vector<T> const& data) : data_(data) {}

    using iterator_category = std::forward_iterator_tag;

    auto begin() { return data_.begin(); }
    auto end() { return data_.end(); }
    auto size() { return data_.size(); }
    auto operator[](const Idx& sub_location) { return data_[sub_location]; }
    auto at(const Idx& sub_location) { return data_.at(sub_location); }

    auto subset_data(std::pair<Idx, size_t> location_size) {
        auto begin = data_.begin() + location_size.first;
        auto end = data_.begin() + location_size.first + location_size.second;
        return boost::make_iterator_range(begin, end);
    }

  private:
    std::vector<T> data_{};
};

} // namespace power_grid_model::main_core

#endif
