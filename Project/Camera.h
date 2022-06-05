#include "Main.h"
#pragma once
class Camera {
public:
	VECTOR mv_view;		// направление камеры
	VECTOR mv_up_vector;	// вертикальный вектор
	VECTOR mv_strafe;
	VECTOR mv_position;	// позиция камеры
	float m_radius = 0;
	Camera() {
		VECTOR vZero = { 0.0, 0.0, 0.0 };
		VECTOR vView = { 0.0, 1.0, 0.5 };     // Иниц. вектор взгляда 
		VECTOR vUp = { 0.0, 0.0, 1.0 };       // Вертикальный вектор 
		VECTOR straf = { 0.0, 0.0, 0.0 };
		float rad = 0;
		mv_position = vZero;
		mv_view = vView;
		mv_up_vector = vUp;
		mv_strafe = straf;
		m_radius = rad;
	}
	void PositionCamera(float positionX, float positionY, float positionZ,
		float viewX, float viewY, float viewZ, float up_vectorX,
		float up_vectorY, float up_vectorZ);	// Тут изменяется положение, направление и верт. вектор камеры.
	void MoveCamera(float speed);	// передвигает камеру вперед/назад
	// эта ф-я вращает камеру вокруг позиции в зависимости от переданных параметров. 
	void Rotate_view(float angle, float x, float y, float z);
	// управление мышью
	void SetViewByMouse();
	// взгляд от 3 лица // vCenter — Точка, вокруг которой она вращается.
	void RotateAroundPoint(VECTOR v_Center, float angle, float x, float y, float z);
	void StrafeCamera(float speed);	// Новая функция — стрейф камеры
	void CheckForMovement(float speed);
	// Функция обновляет взгляд камеры и другие данные
	void Update(float speed);
	// Функция использует gluLookAt (), чтобы сказать OpenGL, куда смотреть 
	void Look();
	/////// предотвращение пересечений (запрет выхода из мира!)
	// Установка радиуса сферы вокруг камеры
	void SetCameraRadius(float radius) { m_radius = radius; };
	// Принимает список вершин+их количество для определения пересечения с ними
	void CheckCameraCollision_t(VECTOR* vertices, int numOfVerts);
	void CheckCameraCollision_q(VECTOR* vertices, int numOfVerts);
};
extern Camera g_Camera;
extern float speed;
extern float g_FrameInterval;
