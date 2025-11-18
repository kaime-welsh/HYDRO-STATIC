#pragma once

#include "Log.h"
#include "NodeHandle.h"
#include <string>
#include <string_view>
#include <vector>

namespace Core {

class SceneTree;

class Node {
  friend class SceneTree;

private:
  NodeHandle _self;
  NodeHandle _parent;
  std::vector<NodeHandle> _children;
  std::string _name;

public:
  Node(std::string_view node_name) : _name(node_name) {}
  virtual ~Node() = default;

  std::string_view GetName() const { return _name; }
  NodeHandle GetParent() const { return _parent; }
  const std::vector<NodeHandle> &GetChildren() const { return _children; }

  virtual void Init() { Log::Info("Node {} is ready.", _name); }
  virtual void Update(float dt) {}
};

} // namespace Core
