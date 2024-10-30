#include "raylib.h"
#include  "Randum.hpp"
#include "Veczebra.ipp"
#include <string>


Vector2 random_2d() {
	float x, y;
	float magnitude;

	do {
		// Generate random x and y values between -1 and 1
		x = static_cast<float>(GetRandomValue(-100, 100)) / 100.0f; // Higher precision
		y = static_cast<float>(GetRandomValue(-100, 100)) / 100.0f;

		// Calculate the magnitude of the vector
		magnitude = std::hypotf(x, y);
	} while (magnitude == 0); // Repeat if we get a zero-length vector

	// Normalize the vector
	return { x / magnitude, y / magnitude };
}

class Mover
{
public:
	Mover()
		:coord{ 600.f,450.f }, velocity{ 0.f,0.f }, radius{ 37.f }
		, acceleration{ -0.01f,0.1f }
	{}

	void update(float dt);
	void show()const;
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

	// Get a random unit vector
	acceleration = random_2d();

	// Scale it

	acceleration *= 2.5f;

	// Add Acceleration to Velocity
	velocity += acceleration;

	// Limit Velocity
	velocity = limit(velocity, top_speed);

	// Add Velocity to Postion to make Ball Move
	coord += {velocity* dt};


	check_edges();
}

void Mover::show()const
{
	
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

///////////////////////////////////////////////////////////////////////////////////////////////////////
////				CANVAS														///



class Canvas
{
public:
	Canvas()
	{
		InitWindow(1200, 900, "Motion 101(Velocity & Random Acceleration");
		SetTargetFPS(144);
	}

	~Canvas() { CloseWindow(); }
	void run();

private:

	void update(float dt);
	void render()const;

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

void Canvas::render()const
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawFPS(5, 5);

	mover.show();

	EndDrawing();
}


int main()
{
	Canvas canvas{};

	canvas.run();
}