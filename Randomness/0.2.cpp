/// A RANDOM-NUMBER DISTRIBUTION

#include "raylib.h"
#include <array>


class Canvas
{
public:
	Canvas()
	{
		InitWindow(1200, 900, "Random Distribution");
		SetTargetFPS(144);

		for (int i=0; i <20; i++)
		{
			bars[i] = { i * width, 900, width, 0.f }; // push rectangle with 0 height
		}
	}

	~Canvas()
	{
		CloseWindow();
	}

	void run();

private:

	void update(float dt);
	void render()const;

private:
	std::array<Rectangle,20> bars{};
	float width = 60.f;

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

	if (bars[0].height >= 0)
	{
		int rand_index = GetRandomValue(0, 19);

		auto& rec = bars[rand_index];
		rec.height++;

		// Set y cuz Objects moves up when y decreases (in Screen )
		rec.y = 900 - rec.height;
	}

	

}

void Canvas::render()const
{
	BeginDrawing();
	ClearBackground(WHITE);
	DrawFPS(5, 5);

	for (const auto& rec : bars)
	{
		DrawRectangle(rec.x,rec.y,rec.width,rec.height,GRAY);
		DrawRectangleLines(rec.x, rec.y, rec.width, rec.height, BLACK);

	}

	EndDrawing();
}

int main()
{

	Canvas canvas{};
	canvas.run();
}
