#include "Engine/Core/NodeHandle.hpp"
#include "Engine/Core/SceneTree.hpp"
#include "Engine/Log.hpp"
#include "raylib.h"

using namespace Engine;

class Player : public Node {
public:
  using Node::Node;

  float x = 400.0f;
  float y = 200.0f;
  float speed = 200.0f;

  void Init() override {
    Log::Info("Player {} has spawned at ({}, {})!", GetName(), x, y);
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

    DrawCircle(static_cast<int>(x), static_cast<int>(y), 20, BLUE);
    DrawText(GetName().data(), static_cast<int>(x) - 20,
             static_cast<int>(y) - 40, 10, DARKGRAY);
  }

  ~Player() { Log::Warning("Player '{}' is being destroyed!", GetName()); }
};

int main(void) {
  Log::InitRaylibLogger();
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE |
                 FLAG_WINDOW_MAXIMIZED);
  InitWindow(800, 600, "HYDRO-STATIC");
  SetTargetFPS(500);

  SceneTree &tree = SceneTree::Get();
  NodeHandle root = tree.CreateNode<Node>("root");
  NodeHandle player = tree.CreateNode<Player>("Hero");

  tree.AddChild(root, player);

  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_SPACE) && tree.IsInstanceValid(player)) {
      Log::Info("Space pressed, Freeing Player...");
      tree.Free(player);
    } else if (IsKeyPressed(KEY_SPACE) && !tree.IsInstanceValid(player)) {
      Log::Info("Space pressed, Creating Player...");
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
