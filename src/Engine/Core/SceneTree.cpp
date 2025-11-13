#include "SceneTree.hpp"

namespace Engine {
SceneTree *SceneTree::_instance = nullptr;

Node *SceneTree::GetNode(NodeHandle handle) {
  if (handle.index >= _nodes.size())
    return nullptr;

  auto &slot = _nodes[handle.index];
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

  c_node->_parent = parent_h;
  p_node->_children.push_back(child_h);
  c_node->Init();
}

void SceneTree::Free(NodeHandle handle) {
  Node *node = GetNode(handle);
  if (!node)
    return;

  auto children_copy = node->_children;
  for (NodeHandle child : children_copy) {
    Free(child);
  }

  if (node->_parent.IsValid()) {
    Node *parent = GetNode(node->_parent);
    if (parent) {
      std::erase(parent->_children, handle);
    }
  }

  std::erase(_update_list, node);
  _nodes[handle.index].node_ptr.reset();
  _free_indices.push_back(handle.index);
};

void SceneTree::RunLoop(float dt) {
  for (Node *node : _update_list) {
    for (Node *node : _update_list) {
      node->Update(dt);
    }
  }
}
} // namespace Engine
