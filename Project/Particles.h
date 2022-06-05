#include "Main.h"
#pragma once
const float Gravity = 0;//-9.8/10;
struct parameter_particle {
	VECTOR pos = { 0, 0, 0 }; // ������� � ����
	VECTOR vel = { 0, 0, 0 }; // ��������
	float color[4] = { 0, 0, 0, 0 }; // ARGB ���� ������� 
	float size = 0; // ������� ������� 
	float life = 0; // ����� ����� ������� � �������� 
	float angle = 0; // ���� � �������� ��� �������� ���������� �����-� ������ ������� 
	float angleNow = 0; // ������� ���� �������� �������� 
	GLuint textureID = -1;   // �������� �������
};
class class_Particle {
public:
	parameter_particle system[MAX_PARTICLES];
	int amount = 0;
public:
	void ARGB(int index);
	// ��������� �������
	void add(parameter_particle now_particle, int index);
	// ������� �������
	void dell(int index);
	// ������� �������������� �������
	bool init(VECTOR position, int count);
	void process(float dt, int index); // ������� ������� ������ ����
	void draw_particles(int index); // ������� ������� �� �����
	// ���� �������� ������� ������� ������ 0, ��� �������, ����� � ���
	bool isAlive(int index);
};
extern class_Particle dyn;