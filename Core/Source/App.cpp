#include "App.h"

#include "App.h"
#include "ILayer.h"
#include "SceneTree.h"
#include "Utils/Log.h"
#include "raylib.h"
#include <memory>
#include <stdexcept>
#include <utility>

namespace Core {
App *App::s_instance = nullptr;

App::App(WindowConfig config) {
  if (s_instance) {
    throw std::runtime_error("Application instance already exists!");
  }
  s_instance = this;

  m_config = config;
}

App::~App() {
  while (!m_layerStack.empty()) {
    PopLayer();
  }
  s_instance = nullptr;
}

void App::PushLayer(std::unique_ptr<ILayer> layer) {
  if (!layer)
    return;

  layer->OnAttach();
  m_layerStack.push_back(std::move(layer));
}

void App::PopLayer() {
  if (m_layerStack.empty())
    return;

  m_layerStack.back()->OnDetach();
  m_layerStack.pop_back();
}

void App::Stop() { m_isRunning = false; }

void App::Run() {
  Log::Info("Initializing SceneTree...");
  auto sceneTree = &SceneTree::Get();

  Log::Info("Initializing Renderer..");
  Core::Log::InitRaylibLogger();

  SetConfigFlags(m_config.flags);
  InitWindow(m_config.width, m_config.height, m_config.title);
  SetTargetFPS(500);

  m_isRunning = true;
  for (auto &layer : m_layerStack) {
    layer->OnWindowReady();
  }
  while (m_isRunning) {
    if (WindowShouldClose()) {
      m_isRunning = false;
    }

    for (auto &layer : m_layerStack) {
      layer->Update();
    }
    for (auto &layer : m_layerStack) {
      BeginDrawing();
      ClearBackground(BLACK);
      layer->Render();
      EndDrawing();
    }
  }
  for (auto &layer : m_layerStack) {
    layer->OnWindowClose();
  }
  CloseWindow();
}

} // namespace Core
