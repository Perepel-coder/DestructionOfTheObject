#include "pch.h"
#include "Main.h"
Camera g_Camera;
float speed = 3;
float g_FrameInterval = 0.0f; // �������� ������� � ���������� �����
// ������������� �������, ������, ����. ������ ������
void Camera::PositionCamera(float positionX, float positionY, float positionZ,
	float viewX, float viewY, float viewZ, float up_vectorX,
	float up_vectorY, float up_vectorZ)
{
	VECTOR v_position = VECTOR(positionX, positionY, positionZ);
	VECTOR v_view = VECTOR(viewX, viewY, viewZ);
	VECTOR v_up_vector = VECTOR(up_vectorX, up_vectorY, up_vectorZ);
	mv_position = v_position;
	mv_view = v_view;
	mv_up_vector = v_up_vector;
}
void Camera::MoveCamera(float speed) {
	VECTOR v_vector = mv_view - mv_position;
	// ������ �� ����������� ��� ������ �������, ����� ��������� �� ����. 
	// ��� ���������� ������. ����� ������� �� �� ������ �������� �������, ����� 
	// �����������, �.�. ������ ������� ���� ������������.
	v_vector = Normaliz(v_vector);
	// ��������� ��� ������� ������ ������ ��� �����. 
	// �� ���������� � �������� ��������� ����������� �������, ����������� �� ��������.
	mv_position.x += v_vector.x * speed;
	mv_position.y += v_vector.y * speed;
	mv_position.z += v_vector.z * speed;
	mv_view.x += v_vector.x * speed;
	mv_view.y += v_vector.y * speed;
	mv_view.z += v_vector.z * speed;
}
// ��������� �������� (��������) �� ����������� ������ � ������� ������, ���� ���� �����������
void Camera::CheckCameraCollision_q(VECTOR* vertices, int numOfVerts) {
	for (int i = 0; i < numOfVerts; i += 4) {
		VECTOR poly[4] = { vertices[i], vertices[i + 1], vertices[i + 2], vertices[i + 3] };
		VECTOR normal = Normal(poly) * (-1);
		float distance = 0.0;
		int classification = ClassifySphere(mv_position, normal, poly[0], m_radius, distance);
		if (classification == INTERSECTS) {
			VECTOR Offset = normal * distance;
			VECTOR Intersection = mv_position - Offset;
			bool flag_1 = InsidePolygon(Intersection, poly, 4);
			bool flag_2 = EdgeSphereCollision(mv_position, poly, 4, m_radius / 2);
			if (flag_1 || flag_2) {
				Offset = GetCollisionOffset(normal, m_radius, distance);
				mv_position = mv_position + Offset;
				mv_view = mv_view + Offset;
			}
		}
	}
}
// ��������� �������� (������������) �� ����������� ������ � ������� ������, ���� ���� �����������
void Camera::CheckCameraCollision_t(VECTOR* vertices, int numOfVerts) {
	// ��� ������� ����� ������ �� �� SpherePolygonCollision ().
	// Vertices � ��� ������ ����. � ���� ������� �� �������� �� ���� ������������� �� ������ � ����������, 
	// ������������ �� � ���� �����. ����� �����������, �� ���������
	// �������� ������ � ������������ ����� �� �������, �� ���������� ���������� ��������.
	for (int i = 0; i < numOfVerts; i += 3) {
		// �������� ������� ����������� � ����������
		VECTOR triangle[3] = { vertices[i], vertices[i + 1], vertices[i + 2] };
		// 1) ��� ���� � ������� ��������� �����
		// ������� ������� �������� ������������
		VECTOR normal = Normal(triangle);
		// ���������� � ���������� ����� �� ��������� ������������
		float distance = 0.0;
		// ������� ��������� ����� � �����, �������, ��� ������������ � ����������
		int classification = ClassifySphere(mv_position, normal, triangle[0], m_radius, distance);
		// ���� ����� ���������� ���������, ���������� �������� ������
		if (classification == INTERSECTS) {
			// 2) ��� ��� � ������� ������ ����� �����������
			// ������ ���������� ����� ����� �� ��������� ������������
			VECTOR Offset = normal * distance;
			// ������� �������� �� ���������, ������ �������� ��� �� ������ �����.
			VECTOR Intersection = mv_position - Offset;
			// 3) ��� ��� � ���������, ��������� �� ����� ����������� ������ ������������
			// ������� ���������, ��������� �� ����� ������ ������������, ���� ��� � 
			// ���������� � ���� 4, ��� ��������� �� ����������� ���� ������������.
			/////////
			// ��������� ����� ������ ����� ������ �������, ��� �������� ��������� ������ ����������,
			// ����� ������ �� ����. ��� ������, ��� ���� �������� ����� ���������� ��
			// ��������� ����� �����.
			// ����� ��������� ���, ������ ����� ������ �� 2.
			// ��� ������ ������� �������������� ��� �������� �����.
			if (InsidePolygon(Intersection, triangle, 3) || EdgeSphereCollision(mv_position, triangle, 3, m_radius / 2)) {
				// ���� �� ����� � � ��� ���� �����������! ����� ��������� ���, ��� ��� ��� 
				// ����� � ����� �������, �� ������� ����� �������� � �������, � ���������� 
				// � ����� �� ��� �� ��������. GetCollisionOffset () ������ ��� ������ 
				// ��������, ����������� �� �������, ������� � ��������� ������ ����� 
				// �� ���������:
				Offset = GetCollisionOffset(normal, m_radius, distance);
				// ������, ������� ��������, ����� ��������� ��� � ������� � ������� �������
				mv_position = mv_position + Offset;
				mv_view = mv_view + Offset;
			}
		}
	}
}
void Camera::Rotate_view(float angle, float x, float y, float z) {
	VECTOR new_view;
	VECTOR v_view; // ��� ������ �������
	v_view.x = mv_view.x - mv_position.x;
	v_view.y = mv_view.x - mv_position.y;
	v_view.z = mv_view.x - mv_position.z;
	float cos_theta = cos(angle);
	float sin_theta = sin(angle);
	// ������ ����� ������� X ��� ��������� �����
	new_view.x = (cos_theta + (1 - cos_theta) * x * x) * v_view.x;
	new_view.x += ((1 - cos_theta) * x * y - z * sin_theta) * v_view.y;
	new_view.x += ((1 - cos_theta) * x * z + y * sin_theta) * v_view.z;
	// ������ ������� Y
	new_view.y = ((1 - cos_theta) * x * y + z * sin_theta) * v_view.x;
	new_view.y += (cos_theta + (1 - cos_theta) * y * y) * v_view.y;
	new_view.y += ((1 - cos_theta) * y * z - x * sin_theta) * v_view.z;
	// � ������� Z
	new_view.z = ((1 - cos_theta) * x * z - y * sin_theta) * v_view.x;
	new_view.z += ((1 - cos_theta) * y * z + x * sin_theta) * v_view.y;
	new_view.z += (cos_theta + (1 - cos_theta) * z * z) * v_view.z;
	// ���������� ����� ������ ������.
	mv_view.x = mv_position.x + new_view.x;
	mv_view.y = mv_position.y + new_view.y;
	mv_view.z = mv_position.z + new_view.z;
}
// ���������� �����
void Camera::SetViewByMouse() {
	POINT mousePos;
	RECT rect;
	GetWindowRect(hWnd, &rect);
	int middleX = rect.left + camera_width / 2;
	int middleY = rect.top + camera_height / 2;
	float angleY = 0.0f;		// ����������� ������� �����/����
	float angleZ = 0.0f;    // ��������, ����������� ��� �������� �����-������ (�� ��� Y)
	static float currentRotX = 0.0f;
	// �������� ������� �����. ���� 
	GetCursorPos(&mousePos);
	// ���� ������ ������� � ��� �� ���������, �� �� ������� ������ 
	if ((mousePos.x == middleX) && (mousePos.y == middleY)) { return; }
	// ������, ������� ���������� �������, ���������� ��� ������� � ��������. 
	SetCursorPos(middleX, middleY);
	// ������ ��� ����� ����������� (��� ������), ���� ��������� ������.
	angleY = (float)((middleX - mousePos.x)) / 1500.0f;
	angleZ = (float)((middleY - mousePos.y)) / 1500.0f;
	static float lastRotX = 0.0f; // ��������� ��������� ���� �������� 
	lastRotX = currentRotX;      // � ���������� ������ currentRotX
	// ���� ������� �������� ������ 1 �������, ������� ���, ����� �� ������� ������� ������
	if (currentRotX > 1.0f) {
		currentRotX = 1.0f;
		if (lastRotX != 1.0f) {
			VECTOR vAxis = Cross(mv_view - mv_position, mv_up_vector);
			vAxis = Normaliz(vAxis);
			Rotate_view(1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}
	else if (currentRotX < -1.0f) {
		currentRotX = -1.0;
		if (lastRotX != -1.0) {
			// ����� �� ��������� ��� 
			VECTOR vAxis = Cross(mv_view - mv_position, mv_up_vector);
			vAxis = Normaliz(vAxis); // ������� 
			Rotate_view(-1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}
	else {
		VECTOR vAxis = Cross(mv_view - mv_position, mv_up_vector);
		vAxis = Normaliz(vAxis);
		Rotate_view(angleZ, vAxis.x, vAxis.y, vAxis.z);
	}
	Rotate_view(angleY, 0, 1, 0);
}
// ������ �� 3 ����
void Camera::RotateAroundPoint(VECTOR v_Center, float angle, float x, float y, float z) {
	VECTOR new_position;
	VECTOR v_pos = mv_position - v_Center;
	float cosTheta = cos(angle);
	float sinTheta = sin(angle);
	// ������ �������� X ����� ��������
	new_position.x = (cosTheta + (1 - cosTheta) * x * x) * v_pos.x;
	new_position.x += ((1 - cosTheta) * x * y - z * sinTheta) * v_pos.y;
	new_position.x += ((1 - cosTheta) * x * z + y * sinTheta) * v_pos.z;
	// � �������� Y
	new_position.y = ((1 - cosTheta) * x * y + z * sinTheta) * v_pos.x;
	new_position.y += (cosTheta + (1 - cosTheta) * y * y) * v_pos.y;
	new_position.y += ((1 - cosTheta) * y * z - x * sinTheta) * v_pos.z;
	// � Z...
	new_position.z = ((1 - cosTheta) * x * z - y * sinTheta) * v_pos.x;
	new_position.y += ((1 - cosTheta) * y * z + x * sinTheta) * v_pos.y;
	new_position.y += (cosTheta + (1 - cosTheta) * z * z) * v_pos.z;
	// ������ ������ �������� ����� ������ � ����� �������, 
	// ����� ���������� ����� ������� ������.
	mv_position = v_Center + new_position;
}
// ������ ������
void Camera::StrafeCamera(float speed) {
	// ������� ������ ������� � ������� 
	mv_position.x += mv_strafe.x * speed;
	mv_position.z += mv_strafe.z * speed;
	// ������� ������ � ������� 
	mv_view.x += mv_strafe.x * speed;
	mv_view.z += mv_strafe.z * speed;
}
void Camera::CheckForMovement(float speed) {
	// ������, ���� �������� �������, ��������� � ���������� �����, � ������ ������� 
	// �� �������� ����������� �������� ���������� �������� �� �������� �������:
	float kspeed = speed /** g_FrameInterval*/;
	if (keys['W']) {
		MoveCamera(kspeed);
	}
	if (keys['S']) {
		MoveCamera(-kspeed);
	}
	if (keys['A']) {
		StrafeCamera(-kspeed);
	}
	if (keys['D']) {
		StrafeCamera(kspeed);
	}
}
// ��������� ����� � ���������� �����
//void GetFrameTime() {
//	static float frameTime = 0.0; // ����� ���������� �����
//	float currentTime = timeGetTime() * 0.001f;	// �������� �������, ���������� � �������� �����
//	g_FrameInterval = currentTime - frameTime;
//	frameTime = currentTime;
//}
void Camera::Update(float speed) {
	// ����. ���������� ��� ���������� cross
	VECTOR v_Cross = Cross(mv_view - mv_position, mv_up_vector);
	//����������� ������ �������
	mv_strafe = Normaliz(v_Cross);
	// ���������, ��������� �� ���� 
	//SetViewByMouse();
	// �������� ������� 
	CheckForMovement(speed);
	//GetFrameTime();
}
void Camera::Look() {
	// ����� OpenGL �������, ������ � ����. ������ ������
	gluLookAt(mv_position.x, mv_position.y, mv_position.z, mv_view.x,
		mv_view.y, mv_view.z, mv_up_vector.x, mv_up_vector.y, mv_up_vector.z);
}