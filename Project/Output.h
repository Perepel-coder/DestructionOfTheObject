#pragma once
class Output {
public:
	int tex;
	struct parameters_qube {
		float length;
		float width;
		float height;
	}p_qube;
	struct parameters_pyramid {
		float length;
		float width;
		float height;
	}p_pyramid;
	struct parameters_sphere {
		float radius;
	}p_sphere;
	struct fall {
		float x;
		float y;
		float z;
		float h;
		float v;
		float a;
		float t;
		float s;
	}p_fall;
public:
	void destruct() {
		p_fall.x = 0;
		p_fall.y = 0;
		p_fall.z = 0;
		p_fall.h = 0;
		p_fall.v = 0;
		p_fall.a = 0;
		p_fall.t = 0;
		p_fall.s = 0;
		p_sphere.radius = 0;
		p_pyramid.height = 0;
		p_pyramid.length = 0;
		p_pyramid.width = 0;
		p_qube.height = 0;
		p_qube.length = 0;
		p_qube.width = 0;
		tex = -1;
	}
};
extern Output data;