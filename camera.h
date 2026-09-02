#ifndef CAMERA_H
#define CAMERA_H

typedef struct
{
    float x;
    float y;
    float z;

    float rotacaoX;
    float rotacaoY;

} Camera;

void inicializarCamera(
    Camera *camera
);

void aplicarCamera(
    Camera *camera
);

#endif