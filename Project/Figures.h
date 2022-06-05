#include "Main.h"
#pragma once
class figures {
private:
	struct Qube {
		float length;
		float width;
		float height;
		float radius;
	}qube;
	struct Sphere {
		float radius;
	}sphere;
	struct Pyramid {
		float length;
		float width;
		float height;
		float radius;
	}pyramid;
	struct parameters {
		float angle;
		float height;
		float speed_fall;
		float acceleration = 9.8f;
	}data;
	struct speed {
		float V;
		float Vx;
		float Vy;
	}speed_fal;
	struct coordinates {
		float x = 500.0f;
		float y = 190.0f;
		float z = 500.0f;
		float t = 0.0f;
	}coord;
public:
	void Init_sphere(float rad);
	void Init_qube_or_pyramid(float l, float w, float h, int ID);
	void Draw_qube();
	void Draw_sphere();
	void Draw_pyramid();
	void Draw();
	void Initi(double a, float h, float speed);
	void Initi();
	void Calculation_Coordinates();
	bool CheckCollision(float radius);
	void Mouse_click_L();
	void Mouse_click_R();
	void Shift_Coordinates();
	void Rotation_Wheel(bool Mark);
	void destruct();
	void access(float *x, float *y, float *z, int *count);
	void output(Output* DATA);
};
extern figures parameter;