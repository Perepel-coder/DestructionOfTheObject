#include "pch.h"
#include "Main.h"
class_Particle dyn;
float RANDOM(int min, int max) {
	float result = (float)(min + rand() % (max - min + 1));
	return result;
}
void class_Particle::dell(int index) {
	system[index] = system[amount - 1];
	amount--;
}
void class_Particle::add(parameter_particle now_particle, int index) {
	system[index] = now_particle;
	amount++;
}
void class_Particle::ARGB(int index) {
	srand(time(NULL));
	system[index].color[0] = (float)((5 + rand() % (10 - 4)) * 0.1);	// R
	system[index].color[1] = (float)((rand() % 6) * 0.1);	// G
	system[index].color[2] = (float)((rand() % 6) * 0.1);	// B
	system[index].color[3] = (float)((rand() % 11) * 0.1);	// A
}
// Инициализация частицы
parameter_particle new_particle;
bool class_Particle::init(VECTOR position, int count) {
	amount = 0;
	for (int index = 0; index < MAX_PARTICLES; index++) {
		add(new_particle, index);
		float angle_ = 30;
		float vel_x = (float)(-20 + rand() % 41);
		float vel_y = (float)(-20 + rand() % 41);
		float vel_z = (float)(-20 + rand() % 41);
		float size_ = (float)(5 + rand() % (11));
		VECTOR vell = VECTOR(vel_x, vel_y, vel_z);
		float life_span = (float)(1 + rand() % 6);
		system[index].pos = position; // Установим позицию
		system[index].vel = vell; // Установим скорость
		// Не допустим инициализацию «мертвой» частицы
		system[index].life = life_span; // Установим время жизни частицы в секундах
		system[index].size = size_; // Установим размер 
		system[index].angle = angle_; // Установим угол вращения UV координат
		system[index].color[0] = (float)((5 + rand() % (10 - 4)) * 0.1);	// R
		system[index].color[1] = (float)((rand() % 6) * 0.1);	// G
		system[index].color[2] = (float)((rand() % 6) * 0.1);	// B
		system[index].color[3] = (float)((rand() % 11) * 0.1);	// A
		//system[index].textureID = TID;
	}
	return true;
}
bool class_Particle::isAlive(int index) {
	if (system[index].life > 0) return true;
	return false;
}
// двигает частицу
void class_Particle::process(float dt, int index) {
	// Если частица мертва, сбросим удалим ее
	float LIFE = 0.005f;
	float SPEED = 0.05;
	if (!isAlive(index)) {
		dell(index);
		if (index >= amount) { return; }
	}
	// Применим скорость 
	system[index].pos = system[index].pos + (system[index].vel * SPEED);
	// Применим гравитацию 
	system[index].pos.y = system[index].pos.y + (Gravity * dt);
	// Уменьшим оставшееся время жизни
	system[index].life = system[index].life - LIFE;
	// Применим вращение на «angle» в секунду, если он > 0
	if (system[index].angle != 0.0f) {
		system[index].angleNow += (system[index].angle * SPEED);	// слабое место!!!
	}
}
// рисует частицу
void class_Particle::draw_particles(int index) {
	if (!isAlive(index)) {
		return;
	}
	glEnable(GL_TEXTURE_2D);
	switch (Texture)
	{
	case MARBLE:
		glBindTexture(GL_TEXTURE_2D, Marble[0]);
		break;
	case IRON:
		glBindTexture(GL_TEXTURE_2D, Iron[0]);
		break;
	case OAK:
		glBindTexture(GL_TEXTURE_2D, Oak[0]);
		break;
	default:
		glBindTexture(GL_TEXTURE_2D, Roger[0]);
		break;
	}
	glPushMatrix();
	// Переместим частицы в указанные координаты
	glTranslatef(system[index].pos.x, system[index].pos.y, system[index].pos.z);
	float halfSize = system[index].size;
	// Отрисуем частицы
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.5f, 0.5f); glVertex3f(0.0, 0.0, halfSize);				// центр
	glTexCoord2f(0.0f, 1.0f);  glVertex3f(-halfSize, halfSize, 0.0f); // Верхняя левая вершина 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-halfSize, -halfSize, 0.0f);	// Нижняя левая вершина  
	glTexCoord2f(1.0f, 0.0f); glVertex3f(halfSize, -halfSize, 0.0f); // Нижняя правая вершина 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(halfSize, halfSize, 0.0f); // Верхняя правая вершина 
	glTexCoord2f(0.0f, 0.1f); glVertex3f(-halfSize, halfSize, 0.0f); // Верхняя левая вершина 
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.5f, 0.5f); glVertex3f(0.0, 0.0, -halfSize);				// центр
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-halfSize, halfSize, 0.0f); // Верхняя левая вершина 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-halfSize, -halfSize, 0.0f);	// Нижняя левая вершина  
	glTexCoord2f(1.0f, 0.0f); glVertex3f(halfSize, -halfSize, 0.0f); // Нижняя правая вершина 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(halfSize, halfSize, 0.0f); // Верхняя правая вершина 
	glTexCoord2f(0.0f, 0.1f); glVertex3f(-halfSize, halfSize, 0.0f); // Верхняя левая вершина 
	glEnd();
	glPopMatrix();	// восстанавливает текущую матрицу	(благодаря этому изменения коснуться только этой конкретной частицы а всей сцены)
	glDisable(GL_TEXTURE_2D);
}