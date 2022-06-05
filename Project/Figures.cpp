#include "pch.h"
#include "Main.h"
#define SIZE (MAP_SIZE/STEP_SIZE) * (MAP_SIZE/STEP_SIZE)
figures parameter;
int ID = -1;
bool start = false;
bool explosion = false;
bool figures::CheckCollision(float radius) {
	VECTOR  vPos = VECTOR(coord.x, coord.y, coord.z);
	int result = Height_for_camera(g_HeightMap, (int)vPos.x, (int)vPos.z);
	if ((result == -1 || coord.x > 973 || coord.x < 13 || coord.z > 1000 || coord.z < 10)	&& ((vPos.y + radius + data.height)	< 200.0f)) {
		return true;
	}
	else {
		if ((vPos.y + radius + data.height <= result + radius)) {
			// Установим новую позицию 
			float distance = (vPos.y + radius + data.height) - (result + radius);
			data.height -= distance;
			return true;
		}
	}
	return false;
}
void figures::Initi(double a, float h, float speed) {	// ИНИЦИАЛИЗИРУЕТ ПАРАМЕТРЫ ПАДЕНИЯ
	data.angle = (float)((a * PI) / 180);
	data.height = h;
	data.speed_fall = speed;
}
void figures::Initi() {								// ЗАДАЕТ ВСЕ ВИДЫ СКОРОСТИ
	speed_fal.Vx = data.speed_fall * cos(data.angle);	// НАЧАЛЬНАЯ СКОРОСТЬ ПО ИКСУ
	speed_fal.Vy = data.speed_fall * sin(data.angle);	// НАЧАЛЬНАЯ СКОРОСТЬ ПО ИГРИКУ
}
void figures::Calculation_Coordinates() {		// РАСЧЕТ ТРАЕКТОРИИ
	static float beginTime = GetTickCount() * 0.001f;
	static float endTime = beginTime;
	static float dt = 0.0f;
	static float t = 0.0;
	if (LockFrameRate) {
		beginTime = GetTickCount() * 0.001f;    // Получаем время начала кадра
		dt = beginTime - endTime;   // Получаем dt
		coord.x += speed_fal.Vx * coord.t;
		coord.y += ((float)(speed_fal.Vy * coord.t) - ((float)(data.acceleration * coord.t * coord.t) / 2.0f));
		//data.height += (speed_fal.Vy * coord.t - ((float)(data.acceleration * coord.t * coord.t) / 2.0));
		t += 0.000001f;
		coord.t += t;
 		endTime = GetTickCount() * 0.001f;
	}
}
void figures::Init_sphere(float rad) {		// ПАРАМЕТРЫ СФЕРЫ
	sphere.radius = rad;
};
void figures::Init_qube_or_pyramid(float l, float w, float h, int ID) {	// ПАРАМЕТРЫ КУБА ИЛИ ПИРАМИДЫ
	switch (ID) {
	case QUBE:
		qube.length = l;
		qube.height = h;
		qube.width = w;
	case PYRAMID:
		pyramid.length = l;
		pyramid.height = h;
		pyramid.width = w;
		break;
	}
}
void figures::Draw() {		// НАБОР ФУНКЦИЙ, КОТОРЫЙ ПОЗВОЛЯЕТ МЕНЯТЬ ПАРАМЕТРЫ ОБЪЕКТА
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
	if (ID >= 0) {
		switch (ID)
		{
		case QUBE:
			Draw_qube();
			break;
		case SPHERE:
			Draw_sphere();
			break;
		case PYRAMID:
			Draw_pyramid();
			break;
		}
	}
	glDisable(GL_TEXTURE_2D);
}
void figures::Draw_qube() {	// ОТРИСОВКА, ИЗМЕНЕНИЕ ПАРАМЕТРОВ КУБА
	Shift_Coordinates();
	float width = qube.width / 2;
	float lenght = qube.height / 2;
	float height = qube.length / 2;
	qube.radius = sqrt(pow(qube.height, 2) + pow(qube.length, 2) + pow(qube.width, 2)) / 2;
	if (start) {
		if (!CheckCollision(qube.radius)) {
			Calculation_Coordinates();
		}
		else {
			explosion = true;
		}
	}
	else {
		CheckCollision(qube.radius);
	}
	glPushName(QUBE_ID);        // Привязываем все следующие примитивы к ID «QUBE»
	glPushMatrix();
	glTranslatef(coord.x, coord.y + height + data.height, coord.z);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, -height, -lenght);	// задняя грань
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, height, -lenght);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width, height, -lenght);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width, -height, -lenght);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, -height, lenght);	// передняя грань
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width, -height, lenght);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width, height, lenght);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, height, lenght);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, -height, -lenght);	// левая грань
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, -height, lenght);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, height, lenght);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, height, -lenght);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(width, -height, -lenght);	// правая грань
	glTexCoord2f(0.0f, 1.0f); glVertex3f(width, height, -lenght);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width, height, lenght);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width, -height, lenght);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, height, -lenght);	// верхняя грань
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, height, lenght);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width, height, lenght);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width, height, -lenght);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, -height, -lenght);	// нижняя грань
	glTexCoord2f(0.0f, 1.0f); glVertex3f(width, -height, -lenght);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(width, -height, lenght);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, -height, lenght);
	glEnd();
	glPopMatrix();
	glPopName();    // Заканчиваем работу с ID «QUBE»
}		
void figures::Draw_sphere() {					// ОТРИСОВКА, ИЗМЕНЕНИЕ ПАРАМЕТРОВ ШАРА
	Shift_Coordinates();
	if (start) {
		if (!CheckCollision(sphere.radius)) {
			Calculation_Coordinates();
		}
		else {
			explosion = true;
		}
	}
	else {
		CheckCollision(sphere.radius);
	}
	GLUquadricObj* pObj = gluNewQuadric();      // Создадим новый quadric-обьект
	gluQuadricNormals(pObj, GLU_SMOOTH); // Создаем плавные нормали
	gluQuadricTexture(pObj, GL_TRUE);          // Включим использование текст. координат в quadric-обьекте
	glPushName(SPHERE_ID);
	glPushMatrix();
	glTranslatef(coord.x, coord.y + data.height + sphere.radius, coord.z);
	gluSphere(pObj, sphere.radius, (GLuint)(sphere.radius * 1.5), (GLuint)(sphere.radius * 1.5));
	glPopMatrix();
	glPopName();    // Заканчиваем работу с ID 
	gluDeleteQuadric(pObj);
}
void figures::Draw_pyramid() {					// ОТРИСОВКА, ИЗМЕНЕНИЕ ПАРАМЕТРОВ ПИРАМИДЫ
	Shift_Coordinates();
	float width = pyramid.width / 2;
	float lenght = pyramid.width / 2;
	float height = pyramid.length / 2;
	pyramid.radius = height;
	if (start) {
		if (!CheckCollision(pyramid.radius)) {
			Calculation_Coordinates();
		}
		else {
			explosion = true;
		}
	}
	else {
		CheckCollision(pyramid.radius);
	}
	glPushName(PYRAMID_ID);
	glPushMatrix();
	glTranslatef(coord.x, coord.y + height + data.height, coord.z);
	glBegin(GL_TRIANGLES);
	// ЗАДНЯЯ СТОРОНА
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, -height, -lenght);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(width, -height, -lenght);
	glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0, height, 0.0);
	glEnd();
	// ПЕРЕДНЯЯ СТОРОНА
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0, height, 0.0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, -height, lenght);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width, -height, lenght);
	glEnd();
	// ПРАВАЯ СТОРОНА
	glBegin(GL_TRIANGLES);
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width, -height, lenght);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(width, -height, -lenght);
	glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0, height, 0.0);
	glEnd();
	// ЛЕВАЯ СТОРОНА
	glBegin(GL_TRIANGLES);
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, -height, -lenght);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, -height, lenght);
	glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0, height, 0.0);
	glEnd();
	/////////////////
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, -height, lenght);	// ближний левый угол
	glTexCoord2f(0.0f, 1.0f); glVertex3f(width, -height, lenght);		// ближний правый угол
	glTexCoord2f(0.0f, 0.0f); glVertex3f(width, -height, -lenght);	// дальний правый угол
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, -height, -lenght);	// дальний левый угол
	glEnd();
	glPopMatrix();
	glPopName();    // Заканчиваем работу с I
}
void figures::Mouse_click_L() {
	///// ОБРАБОТКА СОБЫТИЙ МЫШИ ////////////////
	// Если нажата левая кнопка мыши, нужно обработать X и Y координаты клика
	// и проверить, не найдется ли по этим координатам обьект.
	// LOWORD и HIWORD значения lParam — это x и y координаты мыши. 
	// Вызываем RetrieveObjectID (), 
	// чтобы получить обьект, на который мы кликнули.
	int objectID;
	// передаём координаты курсора в функцию, отыскивающую обьект
	objectID = RetrieveObjectID(LOWORD(Mouse_lParam), HIWORD(Mouse_lParam));
	switch (objectID) {
	case QUBE_ID:
		if (qube.width < 500 && qube.height < 500 && qube.length < 500) {
			qube.width += 10;
			qube.height += 10;
			qube.length += 10;
		}
		break;
	case SPHERE_ID:
		if (sphere.radius < 250) {
			sphere.radius += 10;
		}
		break;
	case PYRAMID_ID:
		if (pyramid.width < 500 && pyramid.height < 500 && pyramid.length < 500) {
			pyramid.width += 10;
			pyramid.height += 10;
			pyramid.length += 10;
		}
		break;
	}
}
void figures::Mouse_click_R() {
	int objectID;
	// передаём координаты курсора в функцию, отыскивающую обьект
	objectID = RetrieveObjectID(LOWORD(Mouse_lParam), HIWORD(Mouse_lParam));
	switch (objectID) {
	case QUBE_ID:
		if (qube.width > 10) {
			qube.width -= 10;
		}
		if (qube.height > 10) {
			qube.height -= 10;
		}
		if (qube.length > 10) {
			qube.length -= 10;
		}
		break;
	case SPHERE_ID:
		if (sphere.radius > 10) {
			sphere.radius -= 10;
		}
		break;
	case PYRAMID_ID:
		if (pyramid.width > 10) {
			pyramid.width -= 10;
		}
		if (pyramid.height > 10) {
			pyramid.height -= 10;
		}
		if (pyramid.length > 10) {
			pyramid.length -= 10;
		}
		break;
	}
}
void figures::Shift_Coordinates() {
	float radius = 0;
	switch (ID)
	{
	case QUBE:
		radius = qube.radius;
		break;
	case SPHERE:
		radius = sphere.radius;
		break;
	case PYRAMID:
		radius = pyramid.radius;
		break;
	}
	if (keys[VK_RIGHT]) {
		if (coord.x + radius < 2400) {
			coord.x++;
		}
	}
	if (keys[VK_UP]) {
		if (coord.y + radius + data.height < 1900) {
			data.height++;
		}
	}
	if (keys[VK_LEFT]) {
		if (coord.x - radius > -1400) {
			coord.x--;
		}
	}
	if (keys[VK_DOWN]) {
		if (coord.y - radius > -1900) {
			data.height--;
		}
	}
}
void figures::Rotation_Wheel(bool Mark) {
	float radius = 0;
	switch (ID)
	{
	case QUBE:
		radius = qube.radius;
		break;
	case SPHERE:
		radius = sphere.radius;
		break;
	case PYRAMID:
		radius = pyramid.radius;
		break;
	}
	if (Mark) {
		if (coord.z + radius < 2500) {
			coord.z+=10;
		}
	}
	else {
		if (coord.z - radius > -1500) {
			coord.z -= 10;
		}
	}
}
void figures::destruct() {
	coord.x = 500.0f;
	coord.y = 190.0f;
	coord.z = 500.0f;
	coord.t = 0.0f;
	qube.height = 0.0f;
	qube.length = 0.0f;
	qube.width = 0.0f;
	pyramid.height = 0.0f;
	pyramid.length = 0.0f;
	pyramid.width = 0.0f;
	sphere.radius = 0.0f;
	data.angle = 0.0f;
	data.angle = 0.0f;
	data.height = 0.0f;
	data.acceleration = 9.8f;
	speed_fal.V = 0.0f;
	speed_fal.Vx = 0.0f;
	speed_fal.Vy = 0.0f;
}
void figures::access(float *x, float *y, float *z, int *count) {
	*x = coord.x;
	*y = coord.y + data.height;
	*z = coord.z;
	switch (ID)
	{
	case QUBE:
		*count = (int)qube.radius;
		break;
	case SPHERE:
		*count = (int)sphere.radius;
		break;
	case PYRAMID:
		*count = (int)pyramid.radius;
		break;
	}
}
void figures::output(Output* DATA) {
	switch (ID)
	{
	case QUBE:
		DATA->p_qube.height = qube.height;
		DATA->p_qube.length = qube.length;
		DATA->p_qube.width = qube.width;
		break;
	case PYRAMID:
		DATA->p_pyramid.height = pyramid.height;
		DATA->p_pyramid.length = pyramid.length;
		DATA->p_pyramid.width = pyramid.width;
		break;
	case SPHERE:
		DATA->p_sphere.radius = sphere.radius;
		break;
	}
	DATA->p_fall.a = data.angle;
	DATA->p_fall.h = data.height;
	DATA->p_fall.v = data.speed_fall;
	DATA->p_fall.x = coord.x;
	DATA->p_fall.y = coord.y;
	DATA->p_fall.z = coord.z;
	DATA->p_fall.t = coord.t;
	DATA->p_fall.s = data.speed_fall * data.speed_fall * sin(2 * data.angle) / data.acceleration;
	DATA->tex = Texture;
}