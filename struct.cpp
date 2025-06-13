#include "SplashKit.h"

// Declare target_data struct here

struct target_data
{
    double x;
    double y;
    double radius;
};

target_data new_target(double x, double y, double radius)
{
    target_data result;
    result.x = x;
    result.y = y;
    result.radius = radius;
    return result;
}

target_data random_target()
{
    int MAX_TARGET_RADIUS = 50;
    int MIN_TARGET_RADIUS = 20;

    int radius = rnd(MAX_TARGET_RADIUS - MIN_TARGET_RADIUS) + MIN_TARGET_RADIUS;
    
    return new_target(
        rnd(radius, screen_width() - radius),
        rnd(radius, screen_height() - radius),
        radius
    );
}

void draw_target(target_data target)
{
    fill_circle(COLOR_BLUE, target.x, target.y, target.radius);
}

bool mouse_over_target(target_data target)
{
    return point_in_circle(mouse_x(), mouse_y(), target.x, target.y, target.radius);
}

int main()
{
  open_window("Reaction Timer", 800, 600);

  target_data target = random_target();

  while (!quit_requested())
  {
    process_events();

    if (mouse_clicked(LEFT_BUTTON) && mouse_over_target(target))
    {
        target = random_target();
    }

    clear_screen(COLOR_WHITE);
    draw_target(target);
    refresh_screen();
  }

  return 0;
}