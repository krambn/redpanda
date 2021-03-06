/*
 * Copyright 2020 Vectorized, Inc.
 *
 * Use of this software is governed by the Business Source License
 * included in the file licenses/BSL.md
 *
 * As of the Change Date specified in that file, in accordance with
 * the Business Source License, use of this software will be governed
 * by the Apache License, Version 2.0
 */

#pragma once

#include "kafka/errors.h"
#include "model/fundamental.h"
#include "model/metadata.h"

#include <fmt/core.h>

#include <exception>

namespace pandaproxy::client {

struct broker_error final : std::exception {
    broker_error(model::node_id n_id, kafka::error_code err)
      : std::exception{}
      , msg{fmt::format("{{ node: {} }}, {}", n_id, err)}
      , node_id{n_id}
      , error{err} {}
    const char* what() const noexcept final { return msg.c_str(); }
    std::string msg;
    model::node_id node_id;
    kafka::error_code error;
};

struct partition_error final : std::exception {
    partition_error(model::topic_partition tp, kafka::error_code e)
      : std::exception{}
      , msg{fmt::format("{}, {}", tp, e)}
      , tp{std::move(tp)}
      , error{e} {}
    const char* what() const noexcept final { return msg.c_str(); }
    std::string msg;
    model::topic_partition tp;
    kafka::error_code error;
};

} // namespace pandaproxy::client
