#ifdef _WIN32
#include <Windows.h>
#endif
#include <sgg/graphics.h>
#include <string>

// Τι mode έχουμε διαλέξει
enum class WindowMode {
    Fullscreen,
    Windowed,
    Custom
};

struct ResolutionOption {
    std::string label;
    WindowMode mode;
    float x, y;      // θέση text
    bool selected;
};

// Μικρή λίστα επιλογών για το panel μας
ResolutionOption g_options[] = {
    { "Fullscreen",        WindowMode::Fullscreen,  80.0f,  60.0f, false },
    { "Windowed 800x600",  WindowMode::Windowed,    80.0f,  90.0f, true  },
    { "Custom 1280x720",   WindowMode::Custom,      80.0f, 120.0f, false }
};

const int g_optionCount = sizeof(g_options) / sizeof(g_options[0]);

// Η τρέχουσα επιλογή (προς το παρόν μόνο για εμφάνιση)
WindowMode g_currentMode = WindowMode::Windowed;


void update(float dt)
{
    graphics::MouseState ms;
    graphics::getMouseState(ms);

    if (ms.button_left_pressed) {
        float mx = ms.cur_pos_x;
        float my = ms.cur_pos_y;

        for (int i = 0; i < g_optionCount; ++i)
        {
            float tx = g_options[i].x;
            float ty = g_options[i].y;
            float w = 200.0f;
            float h = 15.0f;

            bool inside =
                mx > tx - 5 && mx < tx + w &&
                my > ty - 10 && my < ty + h;

            if (inside) {
                // κάνε αυτήν selected
                for (int j = 0; j < g_optionCount; ++j)
                    g_options[j].selected = false;

                g_options[i].selected = true;
                g_currentMode = g_options[i].mode;

                // Προς το παρόν απλά αποθηκεύουμε το mode.
                // Αργότερα εδώ θα βάλουμε logic για
                // fullscreen / window / custom.
            }
        }
    }
}


void draw()
{
    // ---------- BACKGROUND + GRID ----------

    graphics::Brush bg; // brush για background & grid

    // Background χρώμα (σκούρο γκρι–μπλε)
    bg.fill_color[0] = 0.10f;
    bg.fill_color[1] = 0.10f;
    bg.fill_color[2] = 0.16f;
    bg.fill_opacity = 1.0f;
    graphics::drawRect(400, 300, 800, 600, bg);

    // Grid lines
    bg.fill_opacity = 0.0f;
    bg.outline_opacity = 0.15f;
    bg.outline_color[0] = 0.7f;
    bg.outline_color[1] = 0.7f;
    bg.outline_color[2] = 0.7f;

    const float spacing = 25.0f;

    // vertical lines
    for (float x = 0; x <= 800; x += spacing)
        graphics::drawLine(x, 0, x, 600, bg);

    // horizontal lines
    for (float y = 0; y <= 600; y += spacing)
        graphics::drawLine(0, y, 800, y, bg);


    // ---------- PANEL ΓΙΑ ΤΙΣ ΕΠΙΛΟΓΕΣ RESOLUTION ----------

    graphics::Brush panelBr;   // ξεχωριστό brush για το panel

    // φόντο panel
    panelBr.fill_color[0] = 0.05f;
    panelBr.fill_color[1] = 0.05f;
    panelBr.fill_color[2] = 0.08f;
    panelBr.fill_opacity = 0.9f;

    panelBr.outline_color[0] = 1.0f;
    panelBr.outline_color[1] = 1.0f;
    panelBr.outline_color[2] = 1.0f;
    panelBr.outline_opacity = 0.5f;

    graphics::drawRect(150, 100, 220, 90, panelBr); // κουτάκι πάνω αριστερά

    // τίτλος
    graphics::Brush textBrush;
    textBrush.fill_color[0] = 1.0f;
    textBrush.fill_color[1] = 1.0f;
    textBrush.fill_color[2] = 1.0f;
    textBrush.fill_opacity = 1.0f;

    graphics::drawText(60, 70, 12, "RESOLUTION", textBrush);

    // επιλογές
    for (int i = 0; i < g_optionCount; ++i)
    {
        if (g_options[i].selected) {
            // χρώμα για την ενεργή επιλογή
            textBrush.fill_color[0] = 0.2f;
            textBrush.fill_color[1] = 1.0f;
            textBrush.fill_color[2] = 0.2f;
        }
        else {
            textBrush.fill_color[0] = 1.0f;
            textBrush.fill_color[1] = 1.0f;
            textBrush.fill_color[2] = 1.0f;
        }

        graphics::drawText(
            g_options[i].x,
            g_options[i].y,
            12,
            g_options[i].label,
            textBrush
        );
    }
}




int main()
{
#ifdef _WIN32
    // Αν υπάρχει console, αποσύνδεσέ την εντελώς
    HWND hConsole = GetConsoleWindow();
    if (hConsole) {
        FreeConsole();              // κόβει τον δεσμό με την κονσόλα
        // (ShowWindow δεν χρειάζεται πλέον)
    }
#endif
    graphics::createWindow(800, 600, "Connect Labs");

    graphics::setUpdateFunction(update);
    graphics::setDrawFunction(draw);
    graphics::setFont("assets/DejaVuSans.ttf");

    graphics::startMessageLoop();
    return 0;
}
