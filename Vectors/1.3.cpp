/// EXAMPLE 1.3- VECTOR SUBSTRACTION

#include "raylib.h"


class Canvas
{
public:
	Canvas()
		:center{ 500.f,500.f }, mouse{ 500.f,500.f }
	{
		InitWindow(1200, 900, "Vector Subtraction");
		SetTargetFPS(144);
	}

	void run();


private:
	void render();
	void update(float d);



private:
	Vector2 center{};
	Vector2 mouse{};
	Vector2 subtracted{};
	float line_weight{ 7 };
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

void Canvas::render()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
	

	// Draw Lines

	//  From top left to Center
	DrawLineEx({ 0.f,0.f }, center, line_weight, {127,127,127,100});

	// from top left to Mouse Positon
	DrawLineEx({ 0.0f,0.f }, mouse, line_weight, {127,127,127,100});

	// From center to Mouse Positon
	DrawLineEx(center, mouse, line_weight, BLACK);


	DrawFPS(5, 5);
	EndDrawing();

}

void Canvas::update(float d)
{
	// Get Mouse Position
	mouse = GetMousePosition();

	// Get Vector from Center to Mouse COORD
	subtracted = { mouse.x-center.x,mouse.y-center.y };

}


int main()
{

	Canvas canvas{};

	canvas.run();
}