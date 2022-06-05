#include "pch.h"
#include "Main.h"
GLuint texture[1];
GLuint Top[1];  // верх
GLuint Back[1]; // назад
GLuint Bottom[1];   // низ
GLuint Right[1];    // право
GLuint Front[1];    // перед
GLuint Left[1];     // лево
GLuint Terrain[1];    // поверхность
GLuint Detail[1];   // детальная текстура
GLuint Particle[1];
GLuint Marble[1];   
GLuint Oak[1];
GLuint Iron[1];
GLuint Roger[1];
GLvoid LoadGLTextures() {
    // Сетка
    AUX_RGBImageRec* texture1;
    texture1 = auxDIBImageLoadA("img1.bmp");
    // Создание текстуры
    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
    free(texture1->data);
    free(texture1);
    // SkyBox
    AUX_RGBImageRec* Top_t;
    Top_t = auxDIBImageLoadA("Top.bmp");
    glGenTextures(1, &Top[0]);
    glBindTexture(GL_TEXTURE_2D, Top[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, Top_t->sizeX, Top_t->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, Top_t->data);
    free(Top_t->data);
    free(Top_t);
    AUX_RGBImageRec* Bottom_t;
    Bottom_t = auxDIBImageLoadA("Bottom.bmp");
    glGenTextures(1, &Bottom[0]);
    glBindTexture(GL_TEXTURE_2D, Bottom[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, Bottom_t->sizeX, Bottom_t->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, Bottom_t->data);
    free(Bottom_t->data);
    free(Bottom_t);
    AUX_RGBImageRec* Front_t;
    Front_t = auxDIBImageLoadA("Front.bmp");
    glGenTextures(1, &Front[0]);
    glBindTexture(GL_TEXTURE_2D, Front[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, Front_t->sizeX, Front_t->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, Front_t->data);
    free(Front_t->data);
    free(Front_t);
    AUX_RGBImageRec* Back_t;
    Back_t = auxDIBImageLoadA("Back.bmp");
    glGenTextures(1, &Back[0]);
    glBindTexture(GL_TEXTURE_2D, Back[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, Back_t->sizeX, Back_t->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, Back_t->data);
    free(Back_t->data);
    free(Back_t);
    AUX_RGBImageRec* Right_t;
    Right_t = auxDIBImageLoadA("Right.bmp");
    glGenTextures(1, &Right[0]);
    glBindTexture(GL_TEXTURE_2D, Right[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, Right_t->sizeX, Right_t->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, Right_t->data);
    free(Right_t->data);
    free(Right_t);
    AUX_RGBImageRec* Left_t;
    Left_t = auxDIBImageLoadA("Left.bmp");
    glGenTextures(1, &Left[0]);
    glBindTexture(GL_TEXTURE_2D, Left[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, Left_t->sizeX, Left_t->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, Left_t->data);
    free(Left_t->data);
    free(Left_t);
    // поверхность
    AUX_RGBImageRec* Terrain_t;
    Terrain_t = auxDIBImageLoadA("Terrain.bmp");
    glGenTextures(1, &Terrain[0]);
    glBindTexture(GL_TEXTURE_2D, Terrain[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, Terrain_t->sizeX, Terrain_t->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, Terrain_t->data);
    free(Terrain_t->data);
    free(Terrain_t);
    AUX_RGBImageRec* Detail_t;
    Detail_t = auxDIBImageLoadA("Detail.bmp");
    glGenTextures(1, &Detail[0]);
    glBindTexture(GL_TEXTURE_2D, Detail[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, Detail_t->sizeX, Detail_t->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, Detail_t->data);
    free(Detail_t->data);
    free(Detail_t);
    // частица
    AUX_RGBImageRec* Particle_t;
    Particle_t = auxDIBImageLoadA("particle.bmp");
    glGenTextures(1, &Particle[0]);
    glBindTexture(GL_TEXTURE_2D, Particle[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, Particle_t->sizeX, Particle_t->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, Particle_t->data);
    free(Particle_t->data);
    free(Particle_t);
    // мрамор
    AUX_RGBImageRec* Marble_t;
    Marble_t = auxDIBImageLoadA("marble.bmp");
    glGenTextures(1, &Marble[0]);
    glBindTexture(GL_TEXTURE_2D, Marble[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, Marble_t->sizeX, Marble_t->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, Marble_t->data);
    free(Marble_t->data);
    free(Marble_t);
    // дуб
    AUX_RGBImageRec* Oak_t;
    Oak_t = auxDIBImageLoadA("oak.bmp");
    glGenTextures(1, &Oak[0]);
    glBindTexture(GL_TEXTURE_2D, Oak[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, Oak_t->sizeX, Oak_t->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, Oak_t->data);
    free(Oak_t->data);
    free(Oak_t);
    // железо
    AUX_RGBImageRec* Iron_t;
    Iron_t = auxDIBImageLoadA("iron.bmp");
    glGenTextures(1, &Iron[0]);
    glBindTexture(GL_TEXTURE_2D, Iron[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, Iron_t->sizeX, Iron_t->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, Iron_t->data);
    free(Iron_t->data);
    free(Iron_t);
    // РОДЖЕР
    AUX_RGBImageRec* Roger_t;
    Roger_t = auxDIBImageLoadA("Roger.bmp");
    glGenTextures(1, &Roger[0]);
    glBindTexture(GL_TEXTURE_2D, Roger[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, Roger_t->sizeX, Roger_t->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, Roger_t->data);
    free(Roger_t->data);
    free(Roger_t);
}
int Texture = -1;