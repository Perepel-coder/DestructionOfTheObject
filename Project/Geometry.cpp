#include "pch.h"
#include "Main.h"
// ������� ���������
VECTOR Cross(VECTOR v1, VECTOR v2) {	// ���� �������������	(��������� ������������)
	VECTOR v_normal;
	v_normal.x = (v1.y * v2.z) - (v1.z * v2.y);
	v_normal.y = (v1.z * v2.x) - (v1.x * v2.z);
	v_normal.z = (v1.x * v2.y) - (v1.y * v2.x);
	return v_normal;
}
float Magnitude(VECTOR v_normal) {	// ���������� �������� �������
	return sqrt(v_normal.x * v_normal.x + v_normal.y * v_normal.y + v_normal.z * v_normal.z);
}
float Distance(VECTOR point_1, VECTOR point_2) {
	double Distance = sqrt((point_2.x - point_1.x) * (point_2.x - point_1.x) + (point_2.y - point_1.y) * (point_2.y - point_1.y) + (point_2.z - point_1.z) * (point_2.z - point_1.z));
	return (float)Distance;
}
VECTOR Normaliz(VECTOR v) {
	float magnitude = Magnitude(v);
	v = v / magnitude;
	return v;
}
VECTOR CreatVector(VECTOR point_1, VECTOR point_2) {
	VECTOR result;
	result.x = point_1.x - point_2.x;
	result.y = point_1.y - point_2.y;
	result.z = point_1.z - point_2.z;
	// ����� �������� ������ ����� 2 ������� (�����������), ����� ������� ������ 
	// ����� �� ������.
	return result;
}
VECTOR Normal(VECTOR triangl[]) {
	// � ������� ���������� ��� ������� � �����������. �� �������� vVector1 � vVector2 � ��� // �������. ������, ���� 2 ������� ������������, �� ����� �������� �� ��� cross (). 
	// (*���������*) �����: ������ �������� �� ������� ��� ������������, � ������ � ����� 
	// �������. ���� �� �������� �� �������, ������� ����� ��������� � ��������������� 
	// �������. � ����� ������ �� ������� ������� ������ �������� ������ �������.
	VECTOR v1 = CreatVector(triangl[2], triangl[0]);
	VECTOR v2 = CreatVector(triangl[1], triangl[0]);
	VECTOR normal = Cross(v1, v2);
	// ������, ���� ����������� �������, �������� ������� ��������� ����. ������ � 
	// ������ ����������, ��� ����� ���� ����� �������. �� ������� � ������ 1, ��� 
	// ���������� ������������.
	normal = Normaliz(normal);
	return normal;
}
VECTOR ClosePointOnLine(VECTOR va, VECTOR vb, VECTOR point) {
	// ������ ������ �� ����� vA � ����� ������������ vPoint.
	VECTOR v1 = point - va;
	// ������ ����������������� ������ ����������� �� ����� vA �� vB.
	VECTOR v2 = Normaliz(vb - va);
	// ���������� ������� ���������, ����� ����� �������� (magnitude) �������� �����.
	float d = Distance(va, vb);
	// ��������� ��������� ������������, ���������� vVector1 �� vVector2. 
	// ���, �� ��������, ���� ��� ���������� �� ������ ���������������� ������� �� vA.
	float t = Dot(v2, v1);
	// ���� ���� ��������������� ��������� �� vA, "t", ������ ��� ����� ����, ���������
	// ����� � vPoint - vA. ���������� ��� �����.
	if (t <= 0) return va;
	// ���� ��������������� ��������� �� vA, "t", ������ ��� ����� ������ �������� �����,
	// ��������� ����� �� ����� - vB. ������ �.
	if (t >= d) return vb;
	// ����� �� ������ ������ � ������� t � ������������ vector2.
	VECTOR v3 = v2 * t;
	// ����� ����� ��������� ����� �� ������� �����, ������ ���������� vVector3 � ����� vA.
	VECTOR closes_point = va + v3;
	// ������ ��������� ����� �� �����
	return closes_point;
}
// ���������� ���������� ��������� �� ������ ��������� (0,0,0).
// ��������� ������� � ��������� � ����� �����, ������� �� ���� ���������
float PlaneDistance(VECTOR normal, VECTOR point) {
	float distance = 0;	// ���������� ������ ��������� ��������� �� ������ ���������
	// ���������� ��������� ��������� ��� ���������� ��������� (Ax + By + Cz + D = 0).
	// ��� ����� ����� D.
	distance = -(normal.x * point.x + normal.y * point.y + normal.z * point.z);
	return distance;
}
// ���� �����������
bool IntersectedPlane(VECTOR triangle[], VECTOR line[]) {
	float distance_1 = 0; float distance_2 = 0;	// ��������� �� ������ �� 2� ����� ����� �� ���������
	VECTOR normal = Normal(triangle);	// ������� ���������
	// ������, ���� �������, ����� �������� ��������� ������ ������������ �� ������ ���������.
	// ������ ��������� � ��� ����� (0,0,0), ��� ��� ��� ����� ����� ����� �������� ��������� 
	// �� ��������� �� ���� �����. ����� ������� �� ������ ��������� �����������. ����� ����� 
	// ����������� ��������� (�� ������ ��� ��������), �� ��� �� �����, ��� ��� ��������� 
	// ��������� � 3� ����.
	float originDistance = PlaneDistance(normal, triangle[0]);
	// ��� ����� �������� ��������� ������ �� ���������� ����� ����� �� ����� ���������. 
	// ���� �� �������� ��������� ��������� �� ����� ������ 
	// ���������, ������ ����� ��������� ��� ������ ����� �����. ���� ��������� �������������, 
	// ����� ��������� �� ����������, ���� ������������� � �����. �� ���� ���� ����� ���������� 
	// ���������, ��������� ����� �������������.
	// ������ ��� ����� ������������ ����� ��� ��������� �������� ��������� ��� ���������� 
	// ��������� �� ������ ����� �����. ��� ���� �������: (Ax + By + Cz + D = ���������)
	// ���� ��������� == 0, ������ ����� �� ���������.
	// A,B,C � ���������� X,Y � Z �������. x,y,z � ���������� ����� ����� ���������.
	// A,B,C � ���������� X,Y � Z �������. x,y,z � ���������� ����� ����� ���������.
	distance_1 = normal.x * line[0].x + normal.y * line[0].y + normal.z * line[0].z + originDistance;
	distance_2 = normal.x * line[1].x + normal.y * line[1].y + normal.z * line[1].z + originDistance;
	// ��, ������ � ��� ���� 2 ���������� �� ���������.
	// ���� ���� ��������� ������������ � ������ 
	// ������������, ������ 2 ����� ��������� �� ������ ������� ���������.
	if (distance_1 * distance_2 >= 0) {
		return false;
	}
	else {
		return true;
	}
}
// ��� ��� ��������:
// 1) ��� ������ ��� ����� ������� (���� �� 3 �����) � �����. 
// ����� ������� ������� ��������.
// 2) ������� �������, ������� ��������� ��������� �� ������ ���������. 
// ���������� ��� ����� ������� ��������� (Ax + By + Cz + D = 0). 
// ��� ����� ����� D, ��� ��� ���� ������������: D = � (Ax + By + Cz)
// 3) ������ �� ����� ����� ���������� �� ����� ����� �����. 
// ���������� ��� ����� �� �� �������.
// 4) ������� ��������� ���� ����� ���� �� �����, ������� ������������� ��� ������������� ��������. 
// ���� ��� ������������� � �� ����� �����������!
//  ���������� ���������� ������ � ����� �����!
/////////////////////////////////////////////////////////
bool IntersectedPlane(VECTOR poly[], VECTOR line[], VECTOR& normal, float& originDistance) {
	// �� ������� ��� 2 ��������� ��� ������� � ���������
	// ��� ��������, ����� �� ������������� �� ��� ���� � IntersectionPoint () � IntersectedPolygon ().
	float distance_1 = 0; float distance_2 = 0;
	normal = Normal(poly);
	originDistance = PlaneDistance(normal, poly[0]);	// ���������� �� ��������� �� (0, 0, 0)
	// ��������� �� ������ � ������ �����
	distance_1 = normal.x * line[0].x + normal.y * line[0].y + normal.z * line[0].z + originDistance;
	distance_2 = normal.x * line[1].x + normal.y * line[1].y + normal.z * line[1].z + originDistance;
	if (distance_1 * distance_2 >= 0) {
		return false;
	}
	else {
		return true;
	}
}
// ��������� ������� ���������� ��������� ������������ �������� (� ��� ��� cos)
float Dot(VECTOR v1, VECTOR v2) {
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
// ��������� ������� ���������� ���� ����� ���������
double AngleBetweenVectors(VECTOR v1, VECTOR v2) {
	// �������� Dot �� ����� ��������
	float dot_product = Dot(v1, v2);
	// �������� ��������� ������� ����� ��������
	float magnitude = Magnitude(v1) * Magnitude(v2);
	double result = dot_product / magnitude;
	double angle = acos(result);
	return angle;
}
//   ���������� ����� ����������� ����� � ���������
VECTOR IntersectionPoint(VECTOR normal, VECTOR line[], double distance) {
	VECTOR point = { 0, 0, 0 }; VECTOR line_dir = { 0, 0,	0 };
	// ���������� ��� ����� ����������� � ����������� �����
	double Numerator = 0.0, Denominator = 0.0, dist = 0.0;
	// 1) ������� ��� ����� �������� ������ ����� �����, ����� ������������� ���
	line_dir = CreatVector(line[1], line[0]); // ������� ������ �����
	line_dir = Normaliz(line_dir);
	// 2) ���������� ������� ���������  ����� ����� ��������� �� ����� �� 
	// ����� �� ���������. ������ ��������� �������������, �.�. ��� ����� ���� ����� �� ����� ����� 
	// � ���������. ��� �������� ������ ���������� ����� � ���������, ����� ����� ����� �����������.
	Numerator = -(normal.x * line[0].x + normal.y * line[0].y + normal.z * line[0].z);
	// 3) ���� �� ������� Dot ����� �������� ����� ����� � �������� ��������, 
	// ��� ���� ��� ������� ���� ����� ���� (�.�. ��� ��� ������������� � ������ 1). 
	// ����� �� �������� Numerator �� ��� �������� ����� ����� ��������� ��������� �� ��������� �����.
	Denominator = Dot(normal, line_dir);  // cos
	if (Denominator == 0.0) {
		return line[0];	// ����� ��������� �� ���������
	}
	// �� ����� (��������� �� ����� �� ���������) �� (dot product), ����� �������� ��������� 
	// (dist), ������� ����� ��� ��� �������� �� ��������� ����� �����. 
	// ��� ����� �������� ��� ��������� (dist) 
	// �� ������ ����� (line_dir). ����� �� ��������� scalar �� �����, �� ���������� ����� 
	// ����� �������. ��� � ���� ��, ��� �� ������. �� ��������� �� ����� ��������� �����, ��������� 
	// �� �����, ����� � ��������� ����� ������� �����. ������� ���� �� ������ �������� Numerator, 
	// ������� �������� ���������� �� ����� �� �����, � ����� ������ �������� ����� ����� ������� �����. 
	// ��������� �� ��������� � ������� � ���� ����� �������� ���������. ��� ���� ����� ����� ����������� 
	// ��������, � �� ������������ � ��� �� ���������� ����� ������? ���������� �� ��������� ����, �� 
	// ���������� �� ����� ����������� ������� ����� � ���������� ����� ������. ���� �� �������� 
	// ��������� �� dot product �� ������� ����� � ������� ���������, �� ������� ���������� ������.
	dist = Numerator / Denominator;	//	���� �������� ���������� �� ���������
	// ������, ��� � ���������� ����, ����� ��������� �� ������, ����� ��������� ����� �����. 
	// ��� ���������� ����� ����� ������� �� ����� ���������. ��� � ���� ������� ���� 
	// ��� ����� �����������.
	// �������� ����� ����� �� �����������
	point.x = (float)(line[0].x + (line_dir.x * dist));
	point.y = (float)(line[0].y + (line_dir.y * dist));
	point.z = (float)(line[0].z + (line_dir.z * dist));
	return point;
}
//   ���������, ��������� �� ����� ������ ��������
bool InsidePolygon(VECTOR intersection, VECTOR poly[], long vertice_count) {
	const double MATCH_FACTOR = 0.9999;	// ���. ��� �������� ������ ��������� �����
	double Angle = 0.0;             // �������������� ����
	VECTOR v1, v2;	// ��������� �������
	// ���� ��, ��� ����� ���������� ���������, ��� �� ������, ��� ��� ���������� ������� �
	// ���� ���������. ��� ������� ��������� ����� ����������� �� ������� ����, ��������� �� 
	// ��� ������ ��������.
	// ����� ������� ������������ ������ �������� �� ����� �����������,
	// ������� ����� � ������ ������� ��������. ����� ��� ���� 
	// ��������� ������������� ������������. � ���� ����� ����� ����� 360, �� �� ������! 
	// ���� �� �������� ������ 360, �� ������� ��������.
	for (int i = 0; i < vertice_count; i++) {
		// �������� ������ �� ������ ������� � ���������� �� ����
		v1 = CreatVector(poly[i], intersection); //�������� ������ �� ������� � �-�� �����������
		v2 = CreatVector(poly[(i + 1) % vertice_count], intersection);	//�������� ������ �� ������ ������� � �-�� �����������
		// ������� ���� ����� 2�� ��������� � ���������� �� ���
		Angle += AngleBetweenVectors(v1, v2);
	}
	// ������ ���� ����� �����, ��� ����� ���������, ����� �� ��� 360.
	if (Angle >= (MATCH_FACTOR * (2.0 * PI))) {
		return true;
	}
	else {
		return false;
	}
}
//   ���������, ������������ �� ����� � ���������	(���� ������� - ����������� :) )
bool IntersectedPolygon(VECTOR poly[], VECTOR line[], int vertice_count) {
	VECTOR normal = { 0, 0, 0 }; float originDistance = 0;
	// ������� ���������, ���������� �� ���� ����� ���������. ���� ��� � �� �� �����
	// ����������, ������� �� ��������� ��� ���� �� ����������.
	// �������� � ������� ����� vNormal � originDistance, IntersectedPlane �������� �� ��� ���.
	if (!IntersectedPlane(poly, line, normal, originDistance)) {
		return false;
	}
	// ����� ����� ����� �����������, �������� � ������� ������� ���������, ����� ����� � 
	// ��������� ��������� �� ���������.
	VECTOR intersection = IntersectionPoint(normal, line, originDistance);
	// ������, ���� ����� �����������, ����� ���������, ����� �� ��� ������ ��������.
	if (InsidePolygon(intersection, poly, vertice_count)) {
		return true;
	}
	else {
		return false;
	}
}
// 1) �������, ��� ����� ������������ � ����������, ����� �������� ����� �����������. 
// ��� ����� ����� ������������ ������� Dot product. 
// �������, ����� ����� ����� �����������, ����� ����� ���������� ��������� �� ����� �� ���������, 
// ����� ��������� �� ����� ����� ����� ����� ������� �����.
// 2) ����� ����� �����������, ����� ���������, ��������� �� ��� ����� ������ ��������.
/////////////////////////////////////////
// ���������� ������ ����������� �����
float Absolute(float num) {
	if (num < 0) {
		return (0 - num);
	}
	else {
		return num;
	}
}
// ���������� true ���� ����� ���������� ���������� �������.
bool SpherePolygonCollision(VECTOR polygon[], VECTOR& center, int vertex_count, float radius) {
	// ��� - �� ����� ������� ����������� :), �� ����������!
	// ����:
	// 1) ������� ����� ���������, ������������ �� ����� � ����������, �� ������� ��������� 
	// �������. ��� ����� �������� ������� ClassifySphere () �������,
	// ���������� ��������� ����� ������������ ���������.
	// ���� ��� ������ INTERSECTS, ��������� �� ������� ����.
	// 2) ������ ��� � �������� ����� �����������.
	// ��������� �� ����� ����� ������������ �����������
	// ����� �����, ����� ���� �������� ����� �����������.
	// 3) ���� ���� ������-����� �����������, ������ ������� � � InsidePolygon (),
	// ������ � ��������� �������� � �� ������. ������� ������ true, ���� �����
	// ����������� ��������� ������ ��������. 
	// 4) ���� �� ����� ������, ������, �� ����� ����� �����������, � ��� ���������
	// ��� ��������� ��������.
	// ��������� �������� ��������� � ���������� ����� �� ������ ����� ��������, �������
	// ����� ����� � ������ �����.
	// ���� �� ����� ���� � �������������, ����� ������ ��� ����� � ����� �� ��� 
	// ��������� ����� � ������ �����. ����� ����� ������������ ��������� �� ���� ����� 
	// �� ������ �����. ���� ��������� ������, ��� ������, ���� �����������.
	//////////////////////////////////
	VECTOR normal = Normal(polygon);	// ������� ��������
	float distance = 0.0;
	// ����� �� ����������, ��������� �� ����� �������, ����� ���������, ��� ���������� �.
	int classification = ClassifySphere(center, normal, polygon[0], radius, distance);
	// ���� ����� ���������� ��������� ��������, ��� ����� ���������, ���������� �� 
	// ��� ��� �������.
	if (classification == INTERSECTS) {
		// ������� ������ ����� �����������.
		// ������ ����� ������������� ����� ����� �� ��������� ��������, � ����������� 
		// ��� ������. ��� �������� ���������� ������� �� ���������� �� ������ ����� 
		// �� ���������.
		// �� ������� �� ������ ����� � �������� � ����������� ��������� ����� � ������� 
		// ����� � ������ �����������? �����, ����� ��� ��������� �� ������ ����� ������ 
		// ������ ��������� �� ������ ����� �� ���������.�
		VECTOR offset = normal * distance;
		// ������� �������� �offset�, ������ �������� ��� �� ������ �����. �vPosition�
		VECTOR position = center - offset;
		// ��������� �� ����� ����������� ������ ��������
		if (InsidePolygon(position, polygon, vertex_count)) {
			return true; // ���� �����������
		}
		else {
			// ��������, ���������� �� ����� ���� ������������
			if (EdgeSphereCollision(center, polygon, vertex_count, radius)) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}
// ��������� ��������� ����� ������������ ���������, � ��� �� ����������
int ClassifySphere(VECTOR& center, VECTOR& normal, VECTOR& point, float radius, float& distance) {
	// ������� ����� ����� ���������� ��������� �� ������ ���������.
	float d = (float)PlaneDistance(normal, point);
	// ���������� ������ ����� �� ��������� ��������.
	distance = (normal.x * center.x) + (normal.y * center.y) + (normal.z * center.z) + d;
	// ���� ���������� �� ������ �� ��������� ������, ��� ������ 
	// �����, �� �����, ��� ��������� �����.
	if (Absolute(distance) < radius) return INTERSECTS;	// ���� ������ ��������� ������ �������, ����� ���������� ���������.
	else if (distance >= radius) return FRONT;	// ���� ��������� ������ ��� ����� �������, ����� ��������� ����� ����������.
	return BEHIND;	// ���� � �� �������, � �� ���������� � �� �����
}
// ����������, ���������� �� ����� ����� - ���� ����� ������������
bool EdgeSphereCollision(VECTOR& center, VECTOR polygon[], int vertex_count, float radius) {
	VECTOR point;
	// ��� �-� ��������� ����� �����, ������� ��������, �� ��c�� � ������ �����. �� ������ 
	// true, ���� ����� ������������ � �����-���� ������.
	// �������� �� ���� ��������
	for (int i = 0; i < vertex_count; i++) {
		// ��� ������ ��������� � ������ ����� ����� �������� �����.
		point = ClosePointOnLine(polygon[i], polygon[(i + 1) % vertex_count], center);
		// ������ ����� ��������� ���������� ����� ��������� ������ � ������� �����
		float distance = Distance(point, center);
		// ���� ���������� ������ �������, ������ ���� �����������
		if (distance < radius) return true;
	}
	return false;
}
///////////// (��� ��� �������� ������ � ����)
// ���������� �������� ����� �� ��������� ��������
VECTOR GetCollisionOffset(VECTOR& normal, float radius, float distance) {
	VECTOR Offset = VECTOR(0, 0, 0);
	// ����� ����� �����������, ����� ��������, ��� ����� �� ���� � �����.
	// � ��������� ������� ������ ����� ������� � �����, �� �� ����� ��������� ��������
	// ������ ���������, � �������� �� ����� ������� ���������.
	// ������ � ���, ��� ����� �����������, � ������� ����� ������������� �����.
	////////////???????????/////////
	// � ������ ���� ����� ������������ � �������� �������� ��������, 
	// �� ������ �������� ��������� �� �������, � ����� �������� ��������� �� ������� ��������� (�������� ����� �������).
	// ��������� (��� � �����)
	// ��������, ������ � ��� ���� ��������:
	//  vNormal = (1, 0, 0)     radius = 5      distance = 3
	// ���� �� ������ ��������� �� �������, �� ������� (5-3=2)
	// ����, ��� ����� ����������� ����� ����� �� 2 �������. ��� �� �� ������, � �����
	// ������ ����������� ����� � �������? ��� ������. � ��� ���� ������ �������,
	// ������� �������� ��� ����������� ���������.
	// ���� �� ������� ������� �� ���������� ���������, �� �������: (2, 0, 0)
	// ���� ����� ������ �������� � �������� ���, � ����� ����������� � �� ������� ������
	// ������������� �����. ����� �� �������� ��� �������� �� ������� �����, ��� ���� ���
	// ����� ����������, ��� ������� ���� ����� ����� ��������� ����� �� ���������.
	////////////
	// ���� �� ����� ������������ � ������ ������� ��������, �� ������ ��������������� �������
	// ���� ��������� ������ ����, �� ������� ��������
	if (distance > 0) {	// ���� ��������� ������ ����, �� ������� ��������
		// ������ ����������, �� ������� ����� ���������� � ���������, �����
		// ������ ������ ����������� �������������� �����
		float distanceOver = radius - distance;
		Offset = normal * distanceOver;
	}
	else {
		// ���� �� ����� � ������ ������� ��������
		// ������ �� �� �����, �� ������ ����� distance � distanceOver
		float distanceOver = radius + distance;
		Offset = normal * (-distanceOver);
	}
	// ���� ���� �������� ��� �������� ����������� � ������ �������� ��������:
	// ���� �� ���������� ����� ������ � ����� ����� ����� ������ ������ �������.
	// ��������� �� �������� ��� �������, ����������� ����������� � �������� �������.
	return Offset;
}