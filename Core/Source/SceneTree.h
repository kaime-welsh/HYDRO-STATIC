#pragma once

#include "Node.h"
#include "NodeHandle.h"
#include <cstdint>
#include <memory>
#include <vector>

namespace Core {

class Node;

class SceneTree {
private:
  struct NodeSlot {
    std::unique_ptr<Node> node_ptr;
    uint32_t generation = 0;
  };

  std::vector<NodeSlot> _nodes;
  std::vector<uint32_t> _free_indices;
  std::vector<Node *> _update_list;

  NodeHandle _root = {0, 0};
  SceneTree() = default;

public:
  static SceneTree &Get() {
    static SceneTree instance;
    return instance;
  }

  Node *GetNode(NodeHandle handle);
  bool IsInstanceValid(NodeHandle handle) { return GetNode(handle) != nullptr; }

  template <typename T = Node> NodeHandle CreateNode(std::string_view name) {
    uint32_t index;

    if (!_free_indices.empty()) {
      index = _free_indices.back();
      _free_indices.pop_back();
    } else {
      index = static_cast<uint32_t>(_nodes.size());
      _nodes.emplace_back();
    }

    if (_nodes[index].generation == 0)
      _nodes[index].generation = 1;
    else
      _nodes[index].generation++;

    _nodes[index].node_ptr = std::make_unique<T>(name);
    NodeHandle handle = {index, _nodes[index].generation};
    _nodes[index].node_ptr->_self = handle;
    _update_list.push_back(_nodes[index].node_ptr.get());

    return handle;
  }

  void AddChild(NodeHandle parent_h, NodeHandle child_h);
  void Free(NodeHandle handle);
  void RunLoop(float dt);
};
} // namespace Core
