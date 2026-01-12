#include "cloth/ClothSim.h"
#include "math/MathUtil.h"
#include "core/Config.h"
#include "cloth/ClothBuilder.h"
#include "cloth/ClothSolver.h"

#include "sgg/graphics.h"
#include <cmath>

void ClothSim::init(int cols, int rows, float spacing)
{
    m_points.clear();
    m_sticks.clear();
    ClothBuilder::buildGrid(cols, rows, spacing, m_points, m_sticks);
}

void ClothSim::update(float dt)
{
    // clamp first
    if (dt > 1.0f / 60.0f) dt = 1.0f / 60.0f;

    // input
    graphics::MouseState ms;
    graphics::getMouseState(ms);

    if (ms.button_left_down)
    {
        float mx = graphics::windowToCanvasX((float)ms.cur_pos_x);
        float my = graphics::windowToCanvasY((float)ms.cur_pos_y);

        if (m_dragIdx < 0)
        {
            const float pickR = 15.0f;
            for (int i = 0; i < (int)m_points.size(); ++i)
                if (math::dist(m_points[i].pos, { mx, my }) < pickR)
                {
                    m_dragIdx = i;
                    m_dragWasPinned = m_points[m_dragIdx].pinned; // ⬅ αποθήκευση
                    m_points[m_dragIdx].pinned = true;            // ⬅ pin ΟΣΟ drag
                    break;
                }

        }

        if (m_dragIdx >= 0)
        {
            auto& p = m_points[m_dragIdx];
            p.pinned = true;                 // pinned while dragging
            p.pos = { mx, my };
            p.prev = p.pos;                  // avoid extra velocity
        }
    }
    else
    {
        if (m_dragIdx >= 0)
            m_points[m_dragIdx].pinned = m_dragWasPinned; // ⬅ restore
        m_dragIdx = -1;
    }

    // physics AFTER setting dragged point
    ClothSolver::verlet(m_points, dt, cfg::GRAVITY_Y);

    // normal relax
    ClothSolver::satisfy(m_points, m_sticks, cfg::SOLVER_ITERS);

    // EXTRA relax όταν κάνεις drag (CRUCIAL)
    if (m_dragIdx >= 0)
    {
        ClothSolver::satisfy(m_points, m_sticks, cfg::SOLVER_ITERS * 2);
    }
    if constexpr (cfg::ENABLE_SELF_COLLISION)
    {
        for (int k = 0; k < 3; ++k)
        {
            const float r = cfg::POINT_RADIUS * 0.1f;
            const float r2 = r * r;

            for (int i = 0; i < (int)m_points.size(); ++i)
            {
                for (int j = i + 1; j < (int)m_points.size(); ++j)
                {
                    auto& a = m_points[i];
                    auto& b = m_points[j];

                    math::Vec2 d = b.pos - a.pos;
                    float d2 = d.x * d.x + d.y * d.y;
                    if (d2 < 1e-6f || d2 >= r2) continue;

                    float dist = std::sqrt(d2);
                    float push = (r - dist) * 0.5f;
                    math::Vec2 n = d * (1.0f / dist);

                    if (!a.pinned) a.pos = a.pos - n * push;
                    if (!b.pinned) b.pos = b.pos + n * push;
                }
            }
        }
    }

}

void ClothSim::draw() const
{
    using namespace graphics;

    Brush stick_br;
    stick_br.outline_opacity = 1.0f;
    stick_br.fill_opacity = 0.0f;

    // Sticks
    for (const auto& s : m_sticks)
    {
        const auto& a = m_points[s.a].pos;
        const auto& b = m_points[s.b].pos;
        drawLine(a.x, a.y, b.x, b.y, stick_br);
    }

    // Points
    Brush pt_br;
    pt_br.outline_opacity = 1.0f;
    pt_br.fill_opacity = 1.0f;
    pt_br.fill_color[0] = 1.0f;
    pt_br.fill_color[1] = 1.0f;
    pt_br.fill_color[2] = 1.0f;
    stick_br.outline_width = 2.0f;
    /*for (const auto& p : m_points)
    {
        // pinned = πιο “έντονο” (χωρίς χρώματα εδώ για να μη μπλέξουμε)
        drawDisk(p.pos.x, p.pos.y, cfg::POINT_RADIUS, pt_br);
    }*/
    for (int i = 0; i < (int)m_points.size(); ++i)
    {
        const auto& p = m_points[i];
        Brush br = pt_br;

        if (p.pinned) { br.fill_color[0] = 1; br.fill_color[1] = 0.3f; br.fill_color[2] = 0.3f; } // red
        else if (i == m_dragIdx) { br.fill_color[0] = 0.3f; br.fill_color[1] = 1; br.fill_color[2] = 0.3f; } // green

        drawDisk(p.pos.x, p.pos.y, cfg::POINT_RADIUS, br);
    }

}
void ClothSim::cutAt(float x, float y, float radius)
{
    (void)x; (void)y; (void)radius;
    // TODO: στο επόμενο βήμα θα σβήνουμε sticks κοντά στο (x,y)
}
