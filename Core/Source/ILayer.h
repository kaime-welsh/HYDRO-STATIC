#pragma once

namespace Core {
class App;

class ILayer {
public:
  virtual ~ILayer() = default;

  virtual void OnAttach() {}
  virtual void OnDetach() {}
  virtual void OnWindowReady() {}
  virtual void OnWindowClose() {}

  virtual void Update() = 0;
  virtual void Render() = 0;
};
} // namespace Core
