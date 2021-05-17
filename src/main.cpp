#include <raylib-cpp.hpp>

float l1 = 100, l2 = 200, m1 = 40, m2 = 40, a1 = PI / 2, a2 = PI / 2, a1_dp = 0,
      a2_dp = 0.1, g = 1;

int main(int argc, char *argv[]) {
  int SCREEN_HEIGHT = 600;
  int SCREEN_WIDTH = 800;
  int ORIGIN_X = 400;
  int ORIGIN_Y = 100;
  std::string name = "Double Pendulum";

  raylib::Window *window =
      new raylib::Window(SCREEN_WIDTH, SCREEN_HEIGHT, name);

  SetTargetFPS(50);

  while (!window->ShouldClose()) {

    float x1 = (l1 * sin(a1)) + ORIGIN_X;
    float y1 = (l1 * cos(a1)) + ORIGIN_Y;
    float x2 = (l2 * sin(a2)) + x1;
    float y2 = (l2 * cos(a2)) + y1;

    float num1 = -g * (2 * m1 + m2) * sin(a1);
    float num2 = -m2 * g * sin(a1 - 2 * a2);
    float num3 = -2 * sin(a1 - a2) * m2;
    float num4 = a2_dp * a2_dp * l2 + a1_dp * a1_dp * l1 * cos(a1 - a2);
    float den = l1 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));
    float a1_dv = (num1 + num2 + num3 * num4) / den;

    num1 = 2 * sin(a1 - a2);
    num2 = (a1_dp * a1_dp * l1 * (m1 + m2));
    num3 = g * (m1 + m2) * cos(a1);
    num4 = a2_dp * a2_dp * l2 * m2 * cos(a1 - a2);
    den = l2 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));
    float a2_dv = (num1 * (num2 + num3 + num4)) / den;

    a1_dp += a1_dv;
    a2_dp += a2_dv;
    a1 += a1_dp;
    a2 += a2_dp;

    // Render
    BeginDrawing();

    DrawLine(ORIGIN_X, ORIGIN_Y, x1, y1, BLACK);
    DrawCircle(x1, y1, m1 / 2, BLACK);
    DrawLine(x1, y1, x2, y2, BLACK);
    DrawCircle(x2, y2, m2 / 2, BLACK);

    ClearBackground(RAYWHITE);
    EndDrawing();
  }
}