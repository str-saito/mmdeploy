// Copyright (c) OpenMMLab. All rights reserved.

#ifndef MMDEPLOY_SRC_GRAPH_COMMON_H_
#define MMDEPLOY_SRC_GRAPH_COMMON_H_

#include "core/graph.h"
#include "core/module.h"
#include "core/registry.h"
#include "core/value.h"

namespace mmdeploy::graph {

namespace {

template <typename T>
inline auto Check(const T& v) -> decltype(!!v) {
  return !!v;
}

template <typename T>
inline std::true_type Check(T&&) {
  return {};
}

}  // namespace

template <typename EntryType, typename RetType = typename Creator<EntryType>::ReturnType>
inline Result<RetType> CreateFromRegistry(const Value& config, const char* key = "type") {
  MMDEPLOY_INFO("config: {}", config);
  auto type = config[key].get<std::string>();
  auto creator = Registry<EntryType>::Get().GetCreator(type);
  if (!creator) {
    MMDEPLOY_ERROR("failed to find module creator: {}", type);
    return Status(eEntryNotFound);
  }
  auto inst = creator->Create(config);
  if (!Check(inst)) {
    MMDEPLOY_ERROR("failed to create module: {}", type);
    return Status(eFail);
  }
  return std::move(inst);
}

class BaseNode : public Node {
 protected:
  explicit BaseNode(const Value& cfg);
};

}  // namespace mmdeploy::graph

#endif  // MMDEPLOY_SRC_GRAPH_COMMON_H_
