#ifndef RENDER_H
#define RENDER_H

#include "camera.h"
#include "onda.h"

void inicializarRenderizacao();

void iniciarFrame();

void desenharCena3D(
    int largura,
    int altura,
    Camera *camera,
    Onda *onda,
    float tempoSimulacao,
    int modoVisualizacao
);

void desenharPainel(
    int largura,
    int altura,
    Onda *onda,
    int modoVisualizacao
);

void finalizarRenderizacao();

#endif