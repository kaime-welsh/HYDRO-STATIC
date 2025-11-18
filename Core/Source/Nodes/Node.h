#pragma once

#include "NodeHandle.h"
#include "Utils/Log.h"
#include <string>
#include <string_view>
#include <vector>

namespace Core {

class SceneTree;

class Node {
  friend class SceneTree;

private:
  NodeHandle m_self;
  NodeHandle m_parent;
  std::vector<NodeHandle> m_children;
  std::string m_name;

public:
  Node(std::string_view node_name) : m_name(node_name) {}
  virtual ~Node() = default;

  std::string_view GetName() const { return m_name; }
  NodeHandle GetParent() const { return m_parent; }
  const std::vector<NodeHandle> &GetChildren() const { return m_children; }

  virtual void Init() { Log::Info("Node {} is ready.", m_name); }
  virtual void Update(float dt) {}
};

} // namespace Core
