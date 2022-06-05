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
VECTOR Cross(VECTOR v1, VECTOR v2);	// векорное  умножение
float Magnitude(VECTOR v_normal);	// величина вектора
float Absolute(float num);	// модудь 
VECTOR Normaliz(VECTOR v);			// нормалтзация
float Distance(VECTOR point_1, VECTOR point_2);	// расстояние между точками
VECTOR Normal(VECTOR triangl[]); // напрвление (нормаль) плоскости
VECTOR CreatVector(VECTOR point_1, VECTOR point_2);  // создает вектор
float PlaneDistance(VECTOR normal, VECTOR point);	// расстояние от плоскости до начала координат
bool IntersectedPlane(VECTOR triangle[], VECTOR line[]); // старая версия функции	(факт пересечения с плоскостью)
bool IntersectedPlane(VECTOR poly[], VECTOR line[], VECTOR& normal, float& originDistance);	// новая версия функции
float Dot(VECTOR v1, VECTOR v2);		// косинус угла между векторами 
double AngleBetweenVectors(VECTOR v1, VECTOR v2);	// собственно, находит угол
VECTOR IntersectionPoint(VECTOR normal, VECTOR line[], double distance);	//   Возвращает точку пересечения линии и плоскости
bool InsidePolygon(VECTOR intersection, VECTOR poly[], long verticec_count);	//   Проверяет, находится ли точка внутри полигона
bool IntersectedPolygon(VECTOR poly[], VECTOR line[], int vertice_count);	// бъединяшка
// Они будут использоватся для возвращаемых значений ClassifySphere ().
#define BEHIND      0   // Если сфера позади плоскости
#define INTERSECTS  1   // Если сфера пересекает плоскость
#define FRONT       2   // Если сфера спереди плоскости
// Возвращает абсолютное значение переданного числа
int ClassifySphere(VECTOR& center, VECTOR& normal, VECTOR& point, float radius, float& distance);
bool EdgeSphereCollision(VECTOR& center, VECTOR polygon[], int vertex_count, float radius);
bool SpherePolygonCollision(VECTOR polygon[], VECTOR& center, int vertex_count, float radius);
VECTOR GetCollisionOffset(VECTOR& normal, float radius, float distance);
float RANDOM(int a, int b);
