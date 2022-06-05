#include "Main.h"
#pragma once
const float Gravity = 0;//-9.8/10;
struct parameter_particle {
	VECTOR pos = { 0, 0, 0 }; // Позиция в мире
	VECTOR vel = { 0, 0, 0 }; // Скорость
	float color[4] = { 0, 0, 0, 0 }; // ARGB цвет частицы 
	float size = 0; // Размеры частицы 
	float life = 0; // Время жизни частицы в секундах 
	float angle = 0; // Угол в градусах для вращения текстурных коорд-т каждую секунду 
	float angleNow = 0; // Текущий угол вращения текстуры 
	GLuint textureID = -1;   // Текстура частицы
};
class class_Particle {
public:
	parameter_particle system[MAX_PARTICLES];
	int amount = 0;
public:
	void ARGB(int index);
	// добавляет частицы
	void add(parameter_particle now_particle, int index);
	// удаляет частицы
	void dell(int index);
	// Функция инициализирует частицы
	bool init(VECTOR position, int count);
	void process(float dt, int index); // Двигает частицы каждый кадр
	void draw_particles(int index); // Выводит частицы на экран
	// Если значение «жизнь» частицы больше 0, она активна, иначе — нет
	bool isAlive(int index);
};
extern class_Particle dyn;