#pragma once

namespace cfg {

	// Window
	inline constexpr int   WINDOW_W = 1024;
	inline constexpr int   WINDOW_H = 768;

	// Cloth grid
	inline constexpr int   CLOTH_COLS = 20;
	inline constexpr int   CLOTH_ROWS = 10;
	inline constexpr float CLOTH_SPACING = 40.0f;

	// Physics
	inline constexpr float GRAVITY_Y = 900.0f;     // px/sec^2
	inline constexpr bool ENABLE_SELF_COLLISION = false;
	inline constexpr int   SOLVER_ITERS = 14;

	// Rendering
	inline constexpr float POINT_RADIUS = 2.5f;

} // namespace cfg
