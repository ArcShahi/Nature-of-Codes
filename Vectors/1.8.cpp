#include "raylib.h"
#include  "Randum.hpp"
#include "Veczebra.ipp"
#include <string>

class Mover
{
public:
	Mover()
		:coord{600.f,450.f }, velocity{0.f,0.f }, radius{ 37.f }
		,acceleration{-0.01f,0.1f}
	{}

	void update(float dt);
	void show();
	void reset();

private:
	void check_edges();

private:
	Vector2 coord{};
	Vector2 velocity{};
	Vector2 acceleration{};
	float radius{};
	const float top_speed = 2000.f;
};

void Mover::update(float dt)
{
	
	// Add Acceleration to Velocity
	velocity += acceleration;

	// Limit Velocity
	velocity = limit(velocity,top_speed);

	// Add Velocity to Postion to make Ball Move
	coord += {velocity* dt};


	check_edges();
}

void Mover::show()
{
	// Render Speed (only Y Component )
	std::string speed_text{ "Speed " + std::to_string(velocity.y) };
	DrawText(speed_text.c_str(), 5, 30, 25, BLACK);

	// Draw Ball
	DrawCircleGradient(coord.x, coord.y, radius, PINK, RED);
	DrawCircleLinesV(coord, radius, BLACK);
}

void Mover::check_edges()
{
	// Check Y Axis
	if (coord.x > GetScreenWidth())
	{
		coord.x = 0.0f;
	}
	else if (coord.x < 0.0f)
	{
		coord.x = GetScreenWidth();
	}

	// CHECK Y AXIS
	if (coord.y > GetScreenHeight())
	{
		coord.y = 0.f;
	}
	else if (coord.y < 0.0f)
	{
		coord.y = GetScreenHeight();
	}
}

void Mover::reset()
{
	Mover();
}

class Canvas
{
public:
	Canvas()
	{
		InitWindow(1200, 900, "Motion 101(Velocity & Const Acceleration");
		SetTargetFPS(144);
	}

	~Canvas() { CloseWindow(); }
	void run();

private:

	void update(float dt);
	void render();

private:
	Mover mover{};

};

void Canvas::run()
{
	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		update(dt);
		render();
	}
}

void Canvas::update(float dt)
{
	
	if (IsKeyPressed(KEY_ENTER))
		mover.reset();

	mover.update(dt);
}

void Canvas::render()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawFPS(5, 5);

	DrawRectangleLines(5, 5, 1200, 900, BLACK);

	mover.show();

	EndDrawing();
}


int main()
{
	Canvas canvas{};

	canvas.run();
}