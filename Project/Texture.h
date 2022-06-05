#pragma once
// материал фигур
#define	MARBLE  0
#define IRON	1
#define OAK		2
// Дефайны для мультитекстурирования
#define GL_TEXTURE0_ARB                     0x84C0
#define GL_TEXTURE1_ARB                     0x84C1
#define GL_COMBINE_ARB          0x8570
#define GL_RGB_SCALE_ARB        0x8573
// Добавляем константы для передачи в glFogi () (это для дыма)
#define GL_FOG_COORDINATE_SOURCE_EXT        0x8450
#define GL_FOG_COORDINATE_EXT           0x8451
#pragma once
extern float g_FogDepth; // Глубина тумана
//extern PFNGLFOGCOORDFEXTPROC glFogCoordfEXT;	// Указатель на функцию-расширение для установки глубины вершины
extern GLuint texture[1];
extern GLuint Top[1];
extern GLuint Back[1];
extern GLuint Bottom[1];
extern GLuint Right[1];
extern GLuint Front[1];
extern GLuint Left[1];
extern GLuint Terrain[1];
extern GLuint Detail[1];
extern GLuint Particle[1];
extern GLuint Marble[1];
extern GLuint Oak[1];
extern GLuint Iron[1];
extern GLuint Roger[1];
extern int Texture;
// загрузка текстур
GLvoid LoadGLTextures();
// Прототипы функций мультитекстурирования
typedef void (APIENTRY* PFNGLMULTITEXCOORD2FARBPROC) (GLenum target, GLfloat s, GLfloat t);
typedef void (APIENTRY* PFNGLACTIVETEXTUREARBPROC) (GLenum target);
// Обьявляем внешние указатели на функции мультитекстурирования
extern PFNGLMULTITEXCOORD2FARBPROC      glMultiTexCoord2fARB;
extern PFNGLACTIVETEXTUREARBPROC        glActiveTextureARB;
