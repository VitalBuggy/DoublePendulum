#ifndef _DPENDULUMHPP
#define _DPENDULUMHPP

#include "./DPendulumMath.h"
#include <raylib-cpp.hpp>

class DoublePendulum {
public:
  DoublePendulum(int sheight, int swidth, DPMath::DPendulumInitConditions conditions) {
    this->screen_height = sheight;
    this->screen_width = swidth;
    this->origin_y = 0.333333 * this->screen_height;
    this->origin_x = 0.5 * this->screen_width;
    this->init_conditions = new DPMath::DPendulumInitConditions(conditions);
    this->window = new raylib::Window(swidth, sheight, "Double Pendulum");
  }

  void run(int fps = 60) {

    this->setup(fps);

    while (!this->window->ShouldClose()) {
      this->processEvents();
      this->update();
      this->render();
    }
  }

private:
  void update() {
    this->init_conditions->angle1_dp += DPMath::calculate_dv(this->init_conditions).first;
    this->init_conditions->angle2_dp += DPMath::calculate_dv(this->init_conditions).second;
    this->init_conditions->angle1 += init_conditions->angle1_dp;
    this->init_conditions->angle2 += init_conditions->angle2_dp;
  }

  void render() {
    BeginDrawing();

    DPMath::MassPositions mass_positions = DPMath::get_mass_positions(this->init_conditions, this->origin_x, this->origin_y);

    DrawLine(this->origin_x, this->origin_y, mass_positions.x1, mass_positions.y1, BLACK);
    DrawCircle(mass_positions.x1, mass_positions.y1, this->init_conditions->mass1, BLACK);
    DrawLine(mass_positions.x1, mass_positions.y1, mass_positions.x2, mass_positions.y2, BLACK);
    DrawCircle(mass_positions.x2, mass_positions.y2, this->init_conditions->mass2, BLACK);

    ClearBackground(RAYWHITE);

    EndDrawing();
  }

  void processEvents() {
  }

  void setup(int fps) { SetTargetFPS(fps); }

private:
  DPMath::DPendulumInitConditions *init_conditions;
  int screen_height, screen_width, origin_y, origin_x;
  double x1, x2, y1, y2;
  raylib::Window *window;
};

#endif // DoublePendulum.hpp