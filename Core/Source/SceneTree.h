#pragma once

#include "NodeHandle.h"
#include "Nodes/Node.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace Core {

class SceneTree {
private:
  struct NodeSlot {
    std::unique_ptr<Node> node_ptr;
    uint32_t generation = 0;
  };

  std::vector<NodeSlot> m_nodes;
  std::vector<uint32_t> m_freeIndices;
  std::vector<Node *> m_updateList;

  static SceneTree *s_instance;
  NodeHandle m_root;

public:
  SceneTree();
  ~SceneTree();

  static SceneTree &Get() { return *s_instance; }

  Node *GetRoot() { return GetNode(m_root); }
  Node *GetNode(NodeHandle handle);
  bool IsInstanceValid(NodeHandle handle) { return GetNode(handle) != nullptr; }

  template <typename T = Node> NodeHandle CreateNode(std::string_view name) {
    uint32_t index;

    if (!m_freeIndices.empty()) {
      index = m_freeIndices.back();
      m_freeIndices.pop_back();
    } else {
      index = static_cast<uint32_t>(m_nodes.size());
      m_nodes.emplace_back();
    }

    if (m_nodes[index].generation == 0)
      m_nodes[index].generation = 1;
    else
      m_nodes[index].generation++;

    m_nodes[index].node_ptr = std::make_unique<T>(name);
    NodeHandle handle = {index, m_nodes[index].generation};
    m_nodes[index].node_ptr->m_self = handle;
    m_updateList.push_back(m_nodes[index].node_ptr.get());

    return handle;
  }

  void AddChild(NodeHandle parent_h, NodeHandle child_h);
  void Free(NodeHandle handle);
  void RunLoop(float dt);
};
} // namespace Core
