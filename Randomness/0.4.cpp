/// GAUSSSIAN BLUR

#include "raylib.h"
#include <vector>

class Blur
{
public:
	Blur(){}
	void update(float dt);
	void show();

private:
	
	float radius{ 20 };
	Vector2 coord{};
	std::vector<Vector2> gauss{};
};


void Blur::show()
{
	for (auto& i : gauss)
	{
		DrawCircleV(i, radius, { 128,128,128,100 });
	}

	DrawCircleV(coord, radius, { 128,128,128,100 });
	
}

void Blur::update(float dt)
{
	gauss.emplace_back((float)GetRandomValue(radius, 1200 - radius), 450);

	if (gauss.size() >200)
		gauss.erase(gauss.begin());

}



class Canvas
{
public:
	Canvas()
	{
		InitWindow(1200, 900, "Gaussian Blur");
		SetTargetFPS(144);
	}

	~Canvas()
	{
		CloseWindow();
	}

	void run();

private:

	void update(float dt);
	void render();

private:
	Blur blur{};
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
	blur.update(dt);
}

void Canvas::render()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
	
	DrawFPS(5, 5);

	blur.show();

	EndDrawing();
}



int main()
{

	Canvas canvas{};
	canvas.run();
}