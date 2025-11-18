#include "SceneTree.h"
#include "Utils/Log.h"

namespace Core {

SceneTree::SceneTree() {
  if (s_instance) {
    throw std::runtime_error("SceneTree instance already exists!");
  }
  s_instance = this;
  m_root = CreateNode("Root");
  Log::Info("SceneTree instance initialized!");
}

SceneTree::~SceneTree() {
  Log::Info("Destroying SceneTree...");
  Free(m_root);
  Log::Info("SceneTree destroyed.");
}

Node *SceneTree::GetNode(NodeHandle handle) {
  if (handle.index >= m_nodes.size())
    return nullptr;

  auto &slot = m_nodes[handle.index];
  if (slot.generation != handle.generation)
    return nullptr;

  return slot.node_ptr.get();
}

void SceneTree::AddChild(NodeHandle parent_h, NodeHandle child_h) {
  Node *p_node = GetNode(parent_h);
  Node *c_node = GetNode(child_h);

  if (!p_node || !c_node) {
    Log::Error("Invalid parent of child handle during AddChild.");
    return;
  }

  c_node->m_parent = parent_h;
  p_node->m_children.push_back(child_h);
  c_node->Init();
}

void SceneTree::Free(NodeHandle handle) {
  Node *node = GetNode(handle);
  if (!node)
    return;

  auto children_copy = node->m_children;
  for (NodeHandle child : children_copy) {
    Free(child);
  }

  if (node->m_parent.IsValid()) {
    Node *parent = GetNode(node->m_parent);
    if (parent) {
      std::erase(parent->m_children, handle);
    }
  }

  std::erase(m_updateList, node);
  m_nodes[handle.index].node_ptr.reset();
  m_freeIndices.push_back(handle.index);
};

void SceneTree::RunLoop(float dt) {
  for (Node *node : m_updateList) {
    for (Node *node : m_updateList) {
      node->Update(dt);
    }
  }
}
} // namespace Core
