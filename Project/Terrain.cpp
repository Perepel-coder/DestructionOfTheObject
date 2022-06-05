#include "pch.h"
#include "Main.h"
using namespace std;
#pragma warning(disable : 4996)
extern bool g_bDetail; // Включение/выключение глобальных текстур
// Текущее значение тайлинга детальной текстуры 
extern int g_DetailScale;
// устанавливает текстурные координаты поверхности на основе X и Z
void SetTextureCoord(float x, float z) {
	//// Нам нужно рассчитать текстурные координаты для текущей вершины. Чтобы 
	//// сделать это, просто берём текущие X & Y, и делми их на MAP_SIZE нашей поверхности. 
	//// Конечно, это подразумевает, что карта высот имеет такие же размеры, что и текстура.
	//glTexCoord2f(x / MAP_SIZE, -z / MAP_SIZE);
	float u = x / (float)MAP_SIZE;
	float v = -z / (float)MAP_SIZE;
	// Вместо обычного наложения текстур мы будем использовать 
	// glMultiTexCoord2fARB (). Это позволит нам выбрать u/v координаты 
	// для каждой текстурной карты, так как мы используем мультитекстурирование. 
	// Посколько мы будем использовать текстурные матрицы для тайлинга 
	// детальной текстуры, просто применим те же u/v координаты 
	// для обоих текстур.
	// Передадим координаты текстуры поверхности
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB, u, v);
	// Передадим координаты детальной текстуры 
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB, u, v);
}
// Ф-я используется для индексации нашей карты высот.
// При работе с массивами всегда нужно убеждатся, что мы не выходим
// за пределы массива, так что убедимся, что этого не случилось. 
// Таким образом X и Y будут в пределах (MAX_SIZE — 1).
int Height_for_camera(BYTE* pHeightMap, int X, int Y) {
	int x = X % MAP_SIZE;   // Проверка для X 
	int y = Y % MAP_SIZE;   // Проверка для Y
	if (!pHeightMap) { return 0; }	// Убедимся, что работаем с правильными даннымиu
	int size = MAP_SIZE * MAP_SIZE;
	if ((x + (y * MAP_SIZE)) >= size || (x + (y * MAP_SIZE)) < 0) {
		return -1;
	}
	else {
		return pHeightMap[x + (y * MAP_SIZE)];  // вернём высоту данного индекса
	}
}
int Height(BYTE* pHeightMap, int X, int Y) {
	int x = X % MAP_SIZE;   // Проверка для X 
	int y = Y % MAP_SIZE;   // Проверка для Y
	if (!pHeightMap) { return 0; }	// Убедимся, что работаем с правильными даннымиu
	// Ниже нам нужно вернуть единичный — 2д-массив. 
	// Мы можем использовать формулу: index = (x + (y * arrayWidth) ). 
	// Это значит, что мы используем 2д-массив[x][y], 
	// иначе он будет противоположным. Теперь, имея верный индекс, 
	// вернём высоту для этого индекса.
	return pHeightMap[x + (y * MAP_SIZE)];  // вернём высоту данного индекса
}
// Устанавливает цветовое значение вершины, в зависимости от высоты и ширины	(устаревшая)
void SetVertexColor(BYTE* pHeightMap, int x, int y) {
	if (!pHeightMap) return;     // Убедимся, что данные верны
	// Здесь мы устанавливаем цвет вершины, основываясь на индексе её высоты.
	// значение от 0 до 1.0 получаем делением высоту на 256.0f.
	float fColor = -0.15f + (Height(pHeightMap, x, y) / 256.0f);
	// Применим нужный оттенок зеленого на текущую вершину 
	glColor3f(0, fColor, 0);
}
// рисуем карту высот, как множество квадратов
// Теперь нам нужно скомбинировать текстуру поверхности с детальной 
// текстурой. Чтобы красиво их обьединить, нам нужны некоторые дефайны 
// ARB-расширений. Первое, GL_COMBINE_ARB, позволяет нам комбинировать 
// параметры текстуры, второе, GL_RGB_SCALE_ARB, позволяет нам 
// увеличивать гамму второй текстуры, чтобы она не затемняла первую. 
// Это прекрасно работает для карт освещения и детальных текстур. 
// GL_RGB_SCALE_ARB может принимать значения только 1, 2 или 4. 2 работает
// просто прекрасно, 4 уже слишком ярко. 
// Чтобы сделать тайлинг детальной текстуры, задействуем текстурную
// матрицу. Когда мы входим в режим текстурных матриц, мы можем 
// воздействовать на координаты выбранной текстуры.
void RenderHeightMap(BYTE pHeightMap[]) {
	int X = 0, Y = 0;       // Переменные для прохда по массиву
	int x, y, z;            // Переменные для чтения
	bool Z = false; int i = 0;
	bool bSwitchSides = false;
	if (!pHeightMap) return;     // Убедимся, что данные верны
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Terrain[0]);
	// Если включена детальная текстура, накладываем поверх вторую:
	if (g_bDetail) {
		// Активируем детальную текстуру
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glEnable(GL_TEXTURE_2D);
		// Включаем режим смешивания и увеличиваем гамму (значение «2»).
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
		glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 2);
		// Биндим детальную текстуру 
		glBindTexture(GL_TEXTURE_2D, Detail[0]);
		// Теперь входим в текстурную матрицу. Это позволит нам изменять 
		// тайлинг детальной текстуры.
		glMatrixMode(GL_TEXTURE);
		// Сбрасываем матрицу и применяем текущее значение scale
		glLoadIdentity();
		glScalef((float)g_DetailScale, (float)g_DetailScale, 1);
		// Выходим из текстурной матрицы 
		glMatrixMode(GL_MODELVIEW);
	}
	glBegin(GL_TRIANGLE_STRIP);
	for (X = 0; X < MAP_SIZE; X += STEP_SIZE) {
		// Проверяем, нужно ли рендерить в противоположную сторону 
		if (bSwitchSides) {
			// Рендерим линию поверхности для текущего X. 
			// Начинаем с MAP_SIZE и идём до 0.
			for (Y = MAP_SIZE; Y > 0; Y -= STEP_SIZE) {
				// Получаем (X, Y, Z) значения для нижней левой вершины 
				x = X;
				y = Height(pHeightMap, X, Y);
				z = Y;
				// Устанавливаем коорд-ты тумана этой вершины
				SetFogCoord(g_FogDepth, (float)y);
				// Текстурные координаты для вершины 
				SetTextureCoord((float)x, (float)z);
				glVertex3i(x, y, z);
				// Получаем (X, Y, Z) для нижней правой вершины 
				x = X + STEP_SIZE;
				y = Height(pHeightMap, X + STEP_SIZE, Y);
				z = Y;
				// Устанавливаем коорд-ты тумана этой вершины
				SetFogCoord(g_FogDepth, (float)y);
				// Устанавливаем текстурные координаты и рендерим вершину 
				SetTextureCoord((float)x, (float)z);
				glVertex3i(x, y, z);
			}
		}
		else {
			// Рендерим линию поверхности для текущего X. 
			// Начинаем с 0 и идём до MAP_SIZE.
			for (Y = 0; Y < MAP_SIZE; Y += STEP_SIZE) {
				// Получаем (X, Y, Z) для нижней правой вершины
				x = X + STEP_SIZE;
				y = Height(pHeightMap, X + STEP_SIZE, Y);
				z = Y;
				// Устанавливаем коорд-ты тумана этой вершины
				SetFogCoord(g_FogDepth, (float)y);
				// Устанавливаем текстурные координаты и рендерим вершину 
				SetTextureCoord((float)x, (float)z);
				glVertex3i(x, y, z);
				// Получаем (X, Y, Z) значения для нижней левой вершины 
				x = X;
				y = Height(pHeightMap, X, Y);
				z = Y;
				// Устанавливаем коорд-ты тумана этой вершины
				SetFogCoord(g_FogDepth, (float)y);
				// Устанавливаем текстурные координаты и рендерим вершину 
				SetTextureCoord((float)x, (float)z);
				glVertex3i(x, y, z);
			}
		}
		bSwitchSides = !bSwitchSides;
	}
	glEnd();
	//glBegin(GL_QUADS);
	//for (X = 0; X < MAP_SIZE; X += STEP_SIZE) {
	//	for (Y = 0; Y < MAP_SIZE; Y += STEP_SIZE) {
	//		// Получаем X,Y,Z для нижней левой вершины 
	//		x = X; y = Height(pHeightMap, X, Y ); z = Y;
	//		SetFogCoord(g_FogDepth, y);
	//		SetTextureCoord(x, z);
	//		glVertex3i(x, y, z);    // Посылаем эту вершину для рендера в OpenGL
	//		// Получаем (X, Y, Z) для верхней левой вершины 
	//		x = X; y = Height(pHeightMap, X, Y + STEP_SIZE ); z = Y + STEP_SIZE ;
	//		SetFogCoord(g_FogDepth, y);
	//		SetTextureCoord(x, z);
	//		glVertex3i(x, y, z);    // Рисуем
	//		x = X + STEP_SIZE; y = Height(pHeightMap, X + STEP_SIZE, Y + STEP_SIZE); z = Y + STEP_SIZE;
	//		SetFogCoord(g_FogDepth, y);
	//		SetTextureCoord(x, z);
	//		glVertex3i(x, y, z);    // Рисуем
	//		x = X + STEP_SIZE; y = Height(pHeightMap, X + STEP_SIZE, Y); z = Y;
	//		SetFogCoord(g_FogDepth, y);
	//		SetTextureCoord(x, z);
	//		glVertex3i(x, y, z);    // Отрисовываем
	//	}
	//}
	//glEnd();
	glActiveTextureARB(GL_TEXTURE1_ARB); glDisable(GL_TEXTURE_2D);
	glActiveTextureARB(GL_TEXTURE0_ARB); glDisable(GL_TEXTURE_2D);
}
//   Загружает .raw файл в массив байт. Каждое значение — значение высоты.
void LoadRawFile(LPSTR strName, int nSize, BYTE* pHeightMap) {
	FILE* pFile = NULL;
	// Откроем файл для бинарного чтения 
	pFile = fopen(strName, "rb");
	// Проверяем, корректно ли открылся файл 
	if (pFile == NULL) { // Выводим ошибку и останавливаем функцию 
		MessageBox(NULL, L"Файл не открылся!", L"Error", MB_OK);
		return;
	}
	fread(pHeightMap, 1, nSize, pFile);
	int result = ferror(pFile);
	if (result) {
		MessageBox(NULL, L"Невозможно считать данные!", L"Error", MB_OK);
	}
	fclose(pFile);
}
// Пройдем по шагам всё, что мы сделали: 
// 1) Сначала читаем карту высот из файла .raw. Это просто, так как в .raw файлах нет никаких заголовков, просто биты изображения. 
// 2) После прочтения карты высот, нам нужно вывести её на экран.
// Это тоже не слишком сложно, мы просто рендерим квадраты с установленным размером (STEP_SIZE).
// Основываясь на карте высот, рисуем эти квадраты в цикле. 
// Вместо задания освещения окрашиваем вершины в разные оттенки зеленого цвета.
//////////////////////////////////
// Устанавливает обьемный туман для текущей вершины с указанной глубиной
void SetFogCoord(float depth, float height) {
	// Функция принимает глубину тумана и высоту текущей вершины. Если высота 
	// больше глубины, дым для этой вершины не установлен (0), но если высота 
	// ниже глубины, рассчитываем значение тумана. Посколько более высокое 
	// число, передаваемое в glFogCoordfEXT (), выведет больше тумана, нам нужно 
	// вычести глубину из высоты, затем сделать это значение отрицательным. 
	// Иначе будет больше тумана сверху, чем снизу.
	float fogY = 0;
	// Проверим, не больше ли высота вершины, чем значение глубины
	if (height > depth) fogY = 0; // Иначе вычисляем глубину тумана для текущей вершины 
	else fogY = -(height - depth);
	// Применяем координаты тумана для этой вершины, используя указатель на функцию-расширение 
	glFogCoordfEXT(fogY);
}
