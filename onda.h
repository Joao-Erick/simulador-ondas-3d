#ifndef ONDA_H
#define ONDA_H

typedef struct
{
    float amplitude;
    float frequencia;
    float velocidade;

    int pausado;

} Onda;

void inicializarOnda(Onda *onda);

void aumentarAmplitude(Onda *onda);
void diminuirAmplitude(Onda *onda);

void aumentarFrequencia(Onda *onda);
void diminuirFrequencia(Onda *onda);

void aumentarVelocidade(Onda *onda);
void diminuirVelocidade(Onda *onda);

void reiniciarOnda(Onda *onda);

float calcularAltura(
    Onda *onda,
    float x,
    float z,
    float tempo
);

void calcularNormal(
    Onda *onda,
    float x,
    float z,
    float tempo,
    float *nx,
    float *ny,
    float *nz
);

void desenharOnda(
    Onda *onda,
    float tempo
);

#endif