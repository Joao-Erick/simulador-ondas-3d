#include <GLFW/glfw3.h>

#include "camera.h"

void inicializarCamera(
    Camera *camera
)
{
    camera->x = 0.0f;
    camera->y = -0.5f;
    camera->z = -5.0f;

    camera->rotacaoX = 35.0f;
    camera->rotacaoY = -25.0f;
}

void aplicarCamera(
    Camera *camera
)
{
    glTranslatef(
        camera->x,
        camera->y,
        camera->z
    );

    glRotatef(
        camera->rotacaoX,
        1.0f,
        0.0f,
        0.0f
    );

    glRotatef(
        camera->rotacaoY,
        0.0f,
        1.0f,
        0.0f
    );
}