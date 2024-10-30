#include "raylib.h"
#include "Algebra.ipp"


class Canvas
{
public:
	Canvas()
	{
		InitWindow(1200, 900, "Normalizing a Vector");
		SetTargetFPS(144);

	}

	~Canvas() { CloseWindow();}

	void run();

private:
	void update();
	void render()const;

private:
	Vector2 mouse{};
	Vector2 unit{};
	const Vector2 center{ 600.f,450.f };
};

void Canvas::run()
{
	while (!WindowShouldClose())
	{
		update();
		render();
	}
}

void Canvas::update()
{
	mouse = GetMousePosition();
	// First get vector from center to mouse
	Vector2 vector = { mouse.x - center.x, mouse.y - center.y };

	// Then normalize it
	unit = normalize(vector); //Vector2Normalize(vector)
	
	// scale it for proper visibility
	unit = { unit.x * 150.f,unit.y * 150.f };

	// Add center back for final position
	unit = { center.x + unit.x, center.y + unit.y };

}

void Canvas::render()const
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawFPS(5, 5);

	// Draw the line from center to the mouse position
	DrawLineEx(center, mouse, 4, GRAY);

	// Draw the normalized and scaled vector from center
	DrawLineEx(center, unit, 10, BLACK);

	EndDrawing();
}


int main()
{

	Canvas canvas{};
	canvas.run();
}