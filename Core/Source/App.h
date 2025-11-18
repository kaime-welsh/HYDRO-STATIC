#pragma once

#include <memory>
#include <vector>

namespace Core {

class ILayer;
class SceneTree;

class App {
public:
  static App &Get() { return *s_instance; }

  App();
  ~App();

  void PushLayer(std::unique_ptr<ILayer> layer);
  template <typename T, typename... Args> void PushLayer(Args &&...args) {
    static_assert(std::is_base_of<ILayer, T>::value,
                  "T must derive from ILayer");
    PushLayer(std::make_unique<T>(std::forward<Args>(args)...));
  }
  void PopLayer();

  void Run();
  void Stop();

private:
  static App *s_instance;
  bool m_isRunning = false;
  std::vector<std::unique_ptr<ILayer>> m_layerStack;
};

} // namespace Core
