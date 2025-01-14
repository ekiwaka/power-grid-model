// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#ifndef POWER_GRID_MODEL_MAIN_CORE_STATE_HPP
#define POWER_GRID_MODEL_MAIN_CORE_STATE_HPP

#include "../calculation_parameters.hpp"
#include "../container.hpp"

#include <concepts>

namespace power_grid_model::main_core {

template <class CompContainer> struct MainModelState {
    using ComponentContainer = CompContainer;

    ComponentContainer components;

    // calculation parameters
    std::shared_ptr<ComponentTopology const> comp_topo;

    std::vector<std::shared_ptr<MathModelTopology const>> math_topology;
    std::shared_ptr<TopologicalComponentToMathCoupling const> topo_comp_coup;

    ComponentToMathCoupling comp_coup;
};

template <typename ContainerType, typename ComponentType>
concept component_container = requires(ContainerType const& c, ID id) {
                                  { c.template citer<ComponentType>().begin() } -> std::forward_iterator;
                                  { c.template citer<ComponentType>().end() } -> std::forward_iterator;
                                  {
                                      *(c.template citer<ComponentType>().begin())
                                      } -> std::same_as<ComponentType const&>;
                                  { *(c.template citer<ComponentType>().end()) } -> std::same_as<ComponentType const&>;
                                  {
                                      c.template get_item<ComponentType>(id)
                                      } -> std::convertible_to<ComponentType const&>;
                              };

template <template <typename T> class StateType, typename ContainerType, typename ComponentType>
concept model_component_state =
    component_container<typename StateType<ContainerType>::ComponentContainer, ComponentType> &&
    std::same_as<StateType<ContainerType>, MainModelState<ContainerType>>;

} // namespace power_grid_model::main_core

#endif
