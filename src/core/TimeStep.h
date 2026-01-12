#pragma once

class TimeStep {
public:
    void setFixedStep(float step) { m_step = step; }
    void reset() { m_accum = 0.0f; }

    // returns: how many fixed updates to run
    int consume(float dt) {
        m_accum += dt;
        int n = 0;
        while (m_accum >= m_step) { m_accum -= m_step; ++n; }
        return n;
    }

    float step() const { return m_step; }

private:
    float m_step = 1.0f / 60.0f;
    float m_accum = 0.0f;
};
