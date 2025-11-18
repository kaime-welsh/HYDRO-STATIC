#include "App.h"
#include "ILayer.h"
#include "Nodes/Node.h"
#include "Utils/Log.h"
#include "raylib.h"

class Player : public Core::Node {
public:
  using Node::Node;

  float x = 400.0f;
  float y = 200.0f;
  float speed = 200.0f;

  void Init() override {
    Core::Log::Info("Player {} has spawned at ({}, {})!", GetName(), x, y);
  }

  void Update(float dt) override {
    if (IsKeyDown(KEY_W))
      y -= speed * dt;
    if (IsKeyDown(KEY_S))
      y += speed * dt;
    if (IsKeyDown(KEY_A))
      x -= speed * dt;
    if (IsKeyDown(KEY_D))
      x += speed * dt;
  }

  ~Player() {
    Core::Log::Warning("Player '{}' is being destroyed!", GetName());
  }
};

class GameLayer : public Core::ILayer {
  void OnAttach() override {}
  void OnDetach() override {}

  void Update() override {}
  void Render() override {}
};

int main(void) {
  Core::App app;
  app.PushLayer<GameLayer>();
  app.Run();
}
