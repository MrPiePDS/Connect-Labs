#include <sgg/graphics.h>

void update(float dt)
{
    // nothing yet
}

void draw()
{
    // Background χρώμα (σκούρο γκρι–μπλε)
    graphics::Brush br;
    br.fill_color[0] = 0.10f;
    br.fill_color[1] = 0.10f;
    br.fill_color[2] = 0.16f;
    br.fill_opacity = 1.0f;
    graphics::drawRect(400, 300, 800, 600, br);

    // Grid lines
    br.fill_opacity = 0.0f;
    br.outline_opacity = 0.15f;
    br.outline_color[0] = 0.7f;
    br.outline_color[1] = 0.7f;
    br.outline_color[2] = 0.7f;

    const float spacing = 25.0f;

    // vertical lines
    for (float x = 0; x <= 800; x += spacing)
        graphics::drawLine(x, 0, x, 600, br);

    // horizontal lines
    for (float y = 0; y <= 600; y += spacing)
        graphics::drawLine(0, y, 800, y, br);
}



int main()
{
    graphics::createWindow(800, 600, "Connect Labs Test");

    graphics::setUpdateFunction(update);
    graphics::setDrawFunction(draw);
    graphics::setFont("assets/DejaVuSans.ttf");

    graphics::startMessageLoop();
    return 0;
}
