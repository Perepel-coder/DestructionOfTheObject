#include "Main.h"
#pragma once
class Camera {
public:
	VECTOR mv_view;		// ����������� ������
	VECTOR mv_up_vector;	// ������������ ������
	VECTOR mv_strafe;
	VECTOR mv_position;	// ������� ������
	float m_radius = 0;
	Camera() {
		VECTOR vZero = { 0.0, 0.0, 0.0 };
		VECTOR vView = { 0.0, 1.0, 0.5 };     // ����. ������ ������� 
		VECTOR vUp = { 0.0, 0.0, 1.0 };       // ������������ ������ 
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
		float up_vectorY, float up_vectorZ);	// ��� ���������� ���������, ����������� � ����. ������ ������.
	void MoveCamera(float speed);	// ����������� ������ ������/�����
	// ��� �-� ������� ������ ������ ������� � ����������� �� ���������� ����������. 
	void Rotate_view(float angle, float x, float y, float z);
	// ���������� �����
	void SetViewByMouse();
	// ������ �� 3 ���� // vCenter � �����, ������ ������� ��� ���������.
	void RotateAroundPoint(VECTOR v_Center, float angle, float x, float y, float z);
	void StrafeCamera(float speed);	// ����� ������� � ������ ������
	void CheckForMovement(float speed);
	// ������� ��������� ������ ������ � ������ ������
	void Update(float speed);
	// ������� ���������� gluLookAt (), ����� ������� OpenGL, ���� �������� 
	void Look();
	/////// �������������� ����������� (������ ������ �� ����!)
	// ��������� ������� ����� ������ ������
	void SetCameraRadius(float radius) { m_radius = radius; };
	// ��������� ������ ������+�� ���������� ��� ����������� ����������� � ����
	void CheckCameraCollision_t(VECTOR* vertices, int numOfVerts);
	void CheckCameraCollision_q(VECTOR* vertices, int numOfVerts);
};
extern Camera g_Camera;
extern float speed;
extern float g_FrameInterval;
