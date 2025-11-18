#pragma once

namespace Core {
class App;

class ILayer {
public:
  virtual ~ILayer() = default;

  virtual void OnAttach() = 0;
  virtual void OnDetach() = 0;

  virtual void Update() = 0;
  virtual void Render() = 0;
};
} // namespace Core
