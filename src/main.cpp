#include "Log.h"
#include "NodeHandle.h"
#include "SceneTree.h"
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

int main(void) {
  Core::Log::InitRaylibLogger();
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE |
                 FLAG_WINDOW_MAXIMIZED);
  InitWindow(800, 600, "HYDRO-STATIC");
  SetTargetFPS(500);

  Core::SceneTree &tree = Core::SceneTree::Get();
  Core::NodeHandle root = tree.CreateNode<Core::Node>("root");
  Core::NodeHandle player = tree.CreateNode<Player>("Hero");

  tree.AddChild(root, player);

  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_SPACE) && tree.IsInstanceValid(player)) {
      Core::Log::Info("Space pressed, Freeing Player...");
      tree.Free(player);
    } else if (IsKeyPressed(KEY_SPACE) && !tree.IsInstanceValid(player)) {
      Core::Log::Info("Space pressed, Creating Player...");
      player = tree.CreateNode<Player>("Hero");
      tree.AddChild(root, player);
    }

    BeginDrawing();

    ClearBackground(BLACK);
    DrawFPS(2, 2);
    tree.RunLoop(GetFrameTime());

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
