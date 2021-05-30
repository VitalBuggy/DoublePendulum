#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

class Gui {
public:
  // What the fuck?
  Gui(int origin_x, int origin_y, bool &toggle_condition) : ToggleCondition(toggle_condition) {
    this->origin_x = origin_x;
    this->origin_y = origin_y;
  }

  void render() {
    if (this->ToggleCondition && GuiButton((Rectangle){origin_x, origin_y, 130, 80}, "Pause/Start Simulation")) {
      this->ToggleCondition = false;
    } else if (!this->ToggleCondition && GuiButton((Rectangle){origin_x, origin_y, 130, 80}, "Pause/Start Simulation")) {
      this->ToggleCondition = true;
    }
  }

private:
  bool &ToggleCondition;
  int origin_x, origin_y;
};