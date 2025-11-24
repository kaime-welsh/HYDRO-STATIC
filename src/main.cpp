#include "App.h"
#include "ILayer.h"
#include "Nodes/Node.h"
#include "raylib.h"

class Player : public Core::Node {
public:
  float x = 400.0f;
  float y = 200.0f;
  float speed = 200.0f;

  Player() : Core::Node("Player") {}

  void Init() override {}

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

  void Draw() override { DrawCircle(x, y, 8.0f, GREEN); }

  ~Player() {}
};

class GameLayer : public Core::ILayer {
  Player player;

  void OnWindowReady() override { MaximizeWindow(); }

  void OnAttach() override {
    player.x = 400;
    player.y = 300;
  }

  void Update() override { player.Update(GetFrameTime()); }
  void Render() override { player.Draw(); }
};

int main(void) {
  Core::App app(Core::WindowConfig{800, 600, "HYDRO-STATIC",
                                   FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT});
  app.PushLayer<GameLayer>();
  app.Run();
}
