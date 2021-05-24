#include <raylib-cpp.hpp>

struct DPendulumInitConditions {
  double g;
  double length1, mass1, angle1, angle1_dp;
  double length2, mass2, angle2, angle2_dp;
};

class DoublePendulum {
public:
  DoublePendulum(int sheight, int swidth, DPendulumInitConditions conditions) {
    this->screen_height = sheight;
    this->screen_width = swidth;
    this->origin_y = 0.333333 * this->screen_height;
    this->origin_x = 0.5 * this->screen_width;
    this->init_conditions = new DPendulumInitConditions(conditions);
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
    this->init_conditions->angle1_dp += this->calculate_dv(this->init_conditions).first;
    this->init_conditions->angle2_dp += this->calculate_dv(this->init_conditions).second;
    this->init_conditions->angle1 += this->init_conditions->angle1_dp;
    this->init_conditions->angle2 += this->init_conditions->angle2_dp;
  }

  std::pair<double, double> calculate_dv(DPendulumInitConditions *conditions) {
    double num1 = -(conditions->g) * (2 * (conditions->mass1) + (conditions->mass2)) * sin((conditions->angle1));
    double num2 = -(conditions->mass2) * (conditions->g) * sin((conditions->angle1) - 2 * (conditions->angle2));
    double num3 = -2 * sin((conditions->angle1) - (conditions->angle2)) * (conditions->mass2);
    double num4 = (conditions->angle2_dp) * (conditions->angle2_dp) * (conditions->length2) + (conditions->angle1_dp) * (conditions->angle1_dp) * (conditions->length1) * cos((conditions->angle1) - (conditions->angle2));
    double den = (conditions->length1) * (2 * (conditions->mass1) + (conditions->mass2) - (conditions->mass2) * cos(2 * (conditions->angle1) - 2 * (conditions->angle2)));
    double a1_dv = (num1 + num2 + num3 * num4) / den;

    num1 = 2 * sin((conditions->angle1) - (conditions->angle2));
    num2 = ((conditions->angle1_dp) * (conditions->angle1_dp) * (conditions->length1) * ((conditions->mass1) + (conditions->mass2)));
    num3 = (conditions->g) * ((conditions->mass1) + (conditions->mass2)) * cos((conditions->angle1));
    num4 = (conditions->angle2_dp) * (conditions->angle2_dp) * (conditions->length2) * (conditions->mass2) * cos((conditions->angle1) - (conditions->angle2));
    den = (conditions->length2) * (2 * (conditions->mass1) + (conditions->mass2) - (conditions->mass2) * cos(2 * (conditions->angle1) - 2 * (conditions->angle2)));
    double a2_dv = (num1 * (num2 + num3 + num4)) / den;

    return {a1_dv, a2_dv};
  }

  void render() {
    BeginDrawing();

    x1 = (this->init_conditions->length1 * sin(this->init_conditions->angle1)) + this->origin_x;
    y1 = (this->init_conditions->length1 * cos(this->init_conditions->angle1)) + this->origin_y;
    x2 = (this->init_conditions->length2 * sin(this->init_conditions->angle2)) + x1;
    y2 = (this->init_conditions->length2 * cos(this->init_conditions->angle2)) + y1;

    DrawLine(this->origin_x, this->origin_y, x1, y1, BLACK);
    DrawCircle(x1, y1, this->init_conditions->mass1, BLACK);
    DrawLine(x1, y1, x2, y2, BLACK);
    DrawCircle(x2, y2, this->init_conditions->mass2, BLACK);

    ClearBackground(RAYWHITE);

    EndDrawing();
  }

  void processEvents() {
  }

  void setup(int fps) { SetTargetFPS(fps); }

private:
  DPendulumInitConditions *init_conditions;
  int screen_height, screen_width, origin_y, origin_x;
  double x1, x2, y1, y2;
  raylib::Window *window;
};