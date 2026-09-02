#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

#include "camera.h"
#include "onda.h"

typedef struct
{
    int teclaEspacoAnterior;

} EstadoEntrada;

void inicializarEntrada(
    EstadoEntrada *entrada
);

void processarEntrada(
    GLFWwindow *janela,
    Camera *camera,
    Onda *onda,
    EstadoEntrada *entrada,
    int *modoVisualizacao,
    float *tempoSimulacao,
    float deltaTime
);

#endif