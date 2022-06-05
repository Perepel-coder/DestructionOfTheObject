#include "pch.h"
#include "Main.h"
Camera g_Camera;
float speed = 3;
float g_FrameInterval = 0.0f; // интервал времени с последнего кадра
// Устанавливает позицию, взгляд, верт. вектор камеры
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
	// Теперь мы нормализуем наш вектор взгляда, когда двигаемся по миру. 
	// Это НЕОБХОДИМО делать. Таким образом вы не будете двигатся быстрее, когда 
	// стрейфитесь, т.к. вектор стрейфа тоже нормализован.
	v_vector = Normaliz(v_vector);
	// Следующий код двигает камеру вперед или назад. 
	// Мы прибавляем к текущему положению направление взгляда, помноженное на скорость.
	mv_position.x += v_vector.x * speed;
	mv_position.y += v_vector.y * speed;
	mv_position.z += v_vector.z * speed;
	mv_view.x += v_vector.x * speed;
	mv_view.y += v_vector.y * speed;
	mv_view.z += v_vector.z * speed;
}
// проверяет полигоны (квадраты) из переданного списка и смещает камеру, если есть пересечение
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
// проверяет полигоны (треугольники) из переданного списка и смещает камеру, если есть пересечение
void Camera::CheckCameraCollision_t(VECTOR* vertices, int numOfVerts) {
	// Эта функция очень похожа на на SpherePolygonCollision ().
	// Vertices — это данные мира. В этой функции мы проходим по всем треугольникам из списка и проверяяем, 
	// пересекается ли с ними сфера. Найдя пересечения, мы вычисляем
	// смещение камеры и «выдавливаем» сферу за полигон, на расстояние найденного смещения.
	for (int i = 0; i < numOfVerts; i += 3) {
		// Сохраним текущий треугольник в переменную
		VECTOR triangle[3] = { vertices[i], vertices[i + 1], vertices[i + 2] };
		// 1) ШАГ ОДИН — находим положение сферы
		// Находим нормаль текущего треугольника
		VECTOR normal = Normal(triangle);
		// Переменная — расстояние сферы от плоскости треугольника
		float distance = 0.0;
		// Находим положение сферы — сзади, спереди, или пересекается с плоскостью
		int classification = ClassifySphere(mv_position, normal, triangle[0], m_radius, distance);
		// Если сфера пересекает плоскость, продолжаем проверку дальше
		if (classification == INTERSECTS) {
			// 2) ШАГ ДВА — находим псевдо точку пересечения
			// Теперь проецируем центр сферы на плоскость треугольника
			VECTOR Offset = normal * distance;
			// Получив смещение от плоскости, просто вычитаем его из центра сферы.
			VECTOR Intersection = mv_position - Offset;
			// 3) ШАГ ТРИ — Проверяем, находится ли точка пересечения внутри треугольника
			// Сначала проверяем, находится ли точка внутри треугольника, если нет — 
			// переходоим к шагу 4, где проверяем на пересечение рёбра треугольника.
			/////////
			// Поскольку сфера вокруг нашей камеры большая, нам придется проходить лишнее расстояние,
			// чтобы пройти за угол. Это потому, что углы полигона могут пересечься со
			// сторонами нашей сферы.
			// Чтобы исправить это, просто делим радиус на 2.
			// Это просто добавит реалистичности при огибании углов.
			if (InsidePolygon(Intersection, triangle, 3) || EdgeSphereCollision(mv_position, triangle, 3, m_radius / 2)) {
				// Если мы здесь — у нас есть пересечение! Чтобы исправить его, все что нам 
				// нужно — найти глубину, на которую сфера проникла в полигон, и вытолкнуть 
				// её назад на это же значение. GetCollisionOffset () вернет нам нужное 
				// смещение, основываясь на нормали, радиусе и дистанции центра сферы 
				// от плоскости:
				Offset = GetCollisionOffset(normal, m_radius, distance);
				// Теперь, получив смещение, нужно прибавить его к позиции и вектору взгляда
				mv_position = mv_position + Offset;
				mv_view = mv_view + Offset;
			}
		}
	}
}
void Camera::Rotate_view(float angle, float x, float y, float z) {
	VECTOR new_view;
	VECTOR v_view; // наш вектор взгляда
	v_view.x = mv_view.x - mv_position.x;
	v_view.y = mv_view.x - mv_position.y;
	v_view.z = mv_view.x - mv_position.z;
	float cos_theta = cos(angle);
	float sin_theta = sin(angle);
	// Найдем новую позицию X для вращаемой точки
	new_view.x = (cos_theta + (1 - cos_theta) * x * x) * v_view.x;
	new_view.x += ((1 - cos_theta) * x * y - z * sin_theta) * v_view.y;
	new_view.x += ((1 - cos_theta) * x * z + y * sin_theta) * v_view.z;
	// Найдем позицию Y
	new_view.y = ((1 - cos_theta) * x * y + z * sin_theta) * v_view.x;
	new_view.y += (cos_theta + (1 - cos_theta) * y * y) * v_view.y;
	new_view.y += ((1 - cos_theta) * y * z - x * sin_theta) * v_view.z;
	// И позицию Z
	new_view.z = ((1 - cos_theta) * x * z - y * sin_theta) * v_view.x;
	new_view.z += ((1 - cos_theta) * y * z + x * sin_theta) * v_view.y;
	new_view.z += (cos_theta + (1 - cos_theta) * z * z) * v_view.z;
	// установить новый взгляд камеры.
	mv_view.x = mv_position.x + new_view.x;
	mv_view.y = mv_position.y + new_view.y;
	mv_view.z = mv_position.z + new_view.z;
}
// управление мышью
void Camera::SetViewByMouse() {
	POINT mousePos;
	RECT rect;
	GetWindowRect(hWnd, &rect);
	int middleX = rect.left + camera_width / 2;
	int middleY = rect.top + camera_height / 2;
	float angleY = 0.0f;		// Направление взгляда вверх/вниз
	float angleZ = 0.0f;    // Значение, необходимое для вращения влево-вправо (по оси Y)
	static float currentRotX = 0.0f;
	// Получаем текущие коорд. мыши 
	GetCursorPos(&mousePos);
	// Если курсор остался в том же положении, мы не вращаем камеру 
	if ((mousePos.x == middleX) && (mousePos.y == middleY)) { return; }
	// Теперь, получив координаты курсора, возвращаем его обратно в середину. 
	SetCursorPos(middleX, middleY);
	// Теперь нам нужно направление (или вектор), куда сдвинулся курсор.
	angleY = (float)((middleX - mousePos.x)) / 1500.0f;
	angleZ = (float)((middleY - mousePos.y)) / 1500.0f;
	static float lastRotX = 0.0f; // Сохраняем последний угол вращения 
	lastRotX = currentRotX;      // и используем заново currentRotX
	// Если текущее вращение больше 1 градуса, обрежем его, чтобы не вращать слишком быстро
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
			// Опять же вычисляем ось 
			VECTOR vAxis = Cross(mv_view - mv_position, mv_up_vector);
			vAxis = Normaliz(vAxis); // Вращаем 
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
// взгляд от 3 лица
void Camera::RotateAroundPoint(VECTOR v_Center, float angle, float x, float y, float z) {
	VECTOR new_position;
	VECTOR v_pos = mv_position - v_Center;
	float cosTheta = cos(angle);
	float sinTheta = sin(angle);
	// Найдем значение X точки вращения
	new_position.x = (cosTheta + (1 - cosTheta) * x * x) * v_pos.x;
	new_position.x += ((1 - cosTheta) * x * y - z * sinTheta) * v_pos.y;
	new_position.x += ((1 - cosTheta) * x * z + y * sinTheta) * v_pos.z;
	// И значение Y
	new_position.y = ((1 - cosTheta) * x * y + z * sinTheta) * v_pos.x;
	new_position.y += (cosTheta + (1 - cosTheta) * y * y) * v_pos.y;
	new_position.y += ((1 - cosTheta) * y * z - x * sinTheta) * v_pos.z;
	// И Z...
	new_position.z = ((1 - cosTheta) * x * z - y * sinTheta) * v_pos.x;
	new_position.y += ((1 - cosTheta) * y * z + x * sinTheta) * v_pos.y;
	new_position.y += (cosTheta + (1 - cosTheta) * z * z) * v_pos.z;
	// Теперь просто прибавим новый вектор к нашей позиции, 
	// чтобы установить новую позицию камеры.
	mv_position = v_Center + new_position;
}
// стрейф камера
void Camera::StrafeCamera(float speed) {
	// добавим вектор стрейфа к позиции 
	mv_position.x += mv_strafe.x * speed;
	mv_position.z += mv_strafe.z * speed;
	// Добавим теперь к взгляду 
	mv_view.x += mv_strafe.x * speed;
	mv_view.z += mv_strafe.z * speed;
}
void Camera::CheckForMovement(float speed) {
	// Теперь, имея интервал времени, прошедший с последнего кадра, в начале функции 
	// мы получаем необходимую скорость умножением скорости на интервал времени:
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
// Вычисляет время с последнего кадра
//void GetFrameTime() {
//	static float frameTime = 0.0; // Время последнего кадра
//	float currentTime = timeGetTime() * 0.001f;	// Интервал времени, прошедшего с прошлого кадра
//	g_FrameInterval = currentTime - frameTime;
//	frameTime = currentTime;
//}
void Camera::Update(float speed) {
	// Иниц. переменную для результата cross
	VECTOR v_Cross = Cross(mv_view - mv_position, mv_up_vector);
	//Нормализуем вектор стрейфа
	mv_strafe = Normaliz(v_Cross);
	// Посмотрим, двигалась ли мыша 
	//SetViewByMouse();
	// Проверим нажатия 
	CheckForMovement(speed);
	//GetFrameTime();
}
void Camera::Look() {
	// Дадим OpenGL позицию, взгляд и верт. вектор камеры
	gluLookAt(mv_position.x, mv_position.y, mv_position.z, mv_view.x,
		mv_view.y, mv_view.z, mv_up_vector.x, mv_up_vector.y, mv_up_vector.z);
}