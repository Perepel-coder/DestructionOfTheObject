#pragma once
class VECTOR {
public:
	float x = 0;
	float y = 0;
	float z = 0;
public:
	VECTOR() : x(0.0), y(0.0), z(0.0) {}
	VECTOR(float X, float Y, float Z) {
		x = X; y = Y; z = Z;
	}
	VECTOR operator+(VECTOR v_vector) {
		return VECTOR(v_vector.x + x, v_vector.y + y, v_vector.z + z);
	}
	VECTOR operator-(VECTOR v_vector) {
		return VECTOR(-v_vector.x + x, -v_vector.y + y, -v_vector.z + z);
	}
	VECTOR operator*(float num) {
		return VECTOR(x * num, y * num, z * num);
	}
	VECTOR operator/(float num) {
		return VECTOR(x / num, y / num, z / num);
	}
};
#define PI 3.1415926535897932
VECTOR Cross(VECTOR v1, VECTOR v2);	// ��������  ���������
float Magnitude(VECTOR v_normal);	// �������� �������
float Absolute(float num);	// ������ 
VECTOR Normaliz(VECTOR v);			// ������������
float Distance(VECTOR point_1, VECTOR point_2);	// ���������� ����� �������
VECTOR Normal(VECTOR triangl[]); // ���������� (�������) ���������
VECTOR CreatVector(VECTOR point_1, VECTOR point_2);  // ������� ������
float PlaneDistance(VECTOR normal, VECTOR point);	// ���������� �� ��������� �� ������ ���������
bool IntersectedPlane(VECTOR triangle[], VECTOR line[]); // ������ ������ �������	(���� ����������� � ����������)
bool IntersectedPlane(VECTOR poly[], VECTOR line[], VECTOR& normal, float& originDistance);	// ����� ������ �������
float Dot(VECTOR v1, VECTOR v2);		// ������� ���� ����� ��������� 
double AngleBetweenVectors(VECTOR v1, VECTOR v2);	// ����������, ������� ����
VECTOR IntersectionPoint(VECTOR normal, VECTOR line[], double distance);	//   ���������� ����� ����������� ����� � ���������
bool InsidePolygon(VECTOR intersection, VECTOR poly[], long verticec_count);	//   ���������, ��������� �� ����� ������ ��������
bool IntersectedPolygon(VECTOR poly[], VECTOR line[], int vertice_count);	// ����������
// ��� ����� ������������� ��� ������������ �������� ClassifySphere ().
#define BEHIND      0   // ���� ����� ������ ���������
#define INTERSECTS  1   // ���� ����� ���������� ���������
#define FRONT       2   // ���� ����� ������� ���������
// ���������� ���������� �������� ����������� �����
int ClassifySphere(VECTOR& center, VECTOR& normal, VECTOR& point, float radius, float& distance);
bool EdgeSphereCollision(VECTOR& center, VECTOR polygon[], int vertex_count, float radius);
bool SpherePolygonCollision(VECTOR polygon[], VECTOR& center, int vertex_count, float radius);
VECTOR GetCollisionOffset(VECTOR& normal, float radius, float distance);
float RANDOM(int a, int b);
