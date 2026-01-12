#include "input/InputState.h"
#include "sgg/graphics.h"

namespace input
{
    void updateInput(InputState& in)
    {
        graphics::MouseState ms;
        graphics::getMouseState(ms);

        in.lmb_pressed = ms.button_left_pressed;
        in.lmb_released = ms.button_left_released;
        in.lmb_down = ms.button_left_down;

        in.pmx = in.mx;
        in.pmy = in.my;

        in.mx = graphics::windowToCanvasX((float)ms.cur_pos_x);
        in.my = graphics::windowToCanvasY((float)ms.cur_pos_y);
    }
}
