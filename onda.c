#include <math.h>
#include <GLFW/glfw3.h>

#include "onda.h"

// =========================================================
// INICIALIZAÇÃO
// =========================================================

void inicializarOnda(Onda *onda)
{
    onda->amplitude = 0.35f;
    onda->frequencia = 3.0f;
    onda->velocidade = 2.0f;

    onda->pausado = 0;
}

// =========================================================
// CONTROLE DA AMPLITUDE
// =========================================================

void aumentarAmplitude(Onda *onda)
{
    onda->amplitude += 0.002f;
}

void diminuirAmplitude(Onda *onda)
{
    onda->amplitude -= 0.002f;

    if (onda->amplitude < 0.0f)
    {
        onda->amplitude = 0.0f;
    }
}

// =========================================================
// CONTROLE DA FREQUÊNCIA
// =========================================================

void aumentarFrequencia(Onda *onda)
{
    onda->frequencia += 0.02f;
}

void diminuirFrequencia(Onda *onda)
{
    onda->frequencia -= 0.02f;

    if (onda->frequencia < 0.1f)
    {
        onda->frequencia = 0.1f;
    }
}

// =========================================================
// CONTROLE DA VELOCIDADE
// =========================================================

void aumentarVelocidade(Onda *onda)
{
    onda->velocidade += 0.02f;
}

void diminuirVelocidade(Onda *onda)
{
    onda->velocidade -= 0.02f;

    if (onda->velocidade < 0.0f)
    {
        onda->velocidade = 0.0f;
    }
}

// =========================================================
// RESET
// =========================================================

void reiniciarOnda(Onda *onda)
{
    onda->amplitude = 0.35f;
    onda->frequencia = 3.0f;
    onda->velocidade = 2.0f;
}

// =========================================================
// CÁLCULO MATEMÁTICO DA SUPERFÍCIE
// =========================================================

float calcularAltura(
    Onda *onda,
    float x,
    float z,
    float tempo
)
{
    /*
        Primeira onda:
        propagação no eixo X.
    */

    float ondaX =
        onda->amplitude *
        sinf(
            onda->frequencia * x -
            onda->velocidade * tempo
        );

    /*
        Segunda onda:
        propagação no eixo Z.
    */

    float ondaZ =
        onda->amplitude *
        sinf(
            onda->frequencia * z -
            onda->velocidade * tempo
        );

    /*
        Superposição das duas ondas.
    */

    return ondaX + ondaZ;
}

// =========================================================
// CÁLCULO DA NORMAL
// =========================================================

void calcularNormal(
    Onda *onda,
    float x,
    float z,
    float tempo,
    float *nx,
    float *ny,
    float *nz
)
{
    float passo = 0.01f;

    /*
        Calculamos a altura de pontos
        próximos ao vértice atual.
    */

    float alturaEsquerda =
        calcularAltura(
            onda,
            x - passo,
            z,
            tempo
        );

    float alturaDireita =
        calcularAltura(
            onda,
            x + passo,
            z,
            tempo
        );

    float alturaTras =
        calcularAltura(
            onda,
            x,
            z - passo,
            tempo
        );

    float alturaFrente =
        calcularAltura(
            onda,
            x,
            z + passo,
            tempo
        );

    /*
        Diferença de altura nos eixos.
    */

    float dx =
        alturaDireita -
        alturaEsquerda;

    float dz =
        alturaFrente -
        alturaTras;

    /*
        Construção aproximada
        da normal da superfície.
    */

    *nx = -dx;
    *ny = 2.0f * passo;
    *nz = -dz;

    /*
        Normalização do vetor.
    */

    float tamanho =
        sqrtf(
            (*nx) * (*nx) +
            (*ny) * (*ny) +
            (*nz) * (*nz)
        );

    if (tamanho != 0.0f)
    {
        *nx /= tamanho;
        *ny /= tamanho;
        *nz /= tamanho;
    }
}

// =========================================================
// DESENHO DA SUPERFÍCIE
// =========================================================

void desenharOnda(
    Onda *onda,
    float tempo
)
{
    /*
        Quanto menor o passo,
        maior a quantidade de vértices
        e mais suave a superfície.
    */

    float passo = 0.08f;

    /*
        Cor base da água.
    */

    glColor3f(
        0.05f,
        0.45f,
        0.8f
    );

    /*
        Percorre a superfície no eixo Z.
    */

    for (
        float z = -2.0f;
        z < 2.0f;
        z += passo
    )
    {
        /*
            Triangle Strip permite criar
            vários triângulos usando
            uma sequência de vértices.
        */

        glBegin(
            GL_TRIANGLE_STRIP
        );

        /*
            Percorre o eixo X.
        */

        for (
            float x = -2.0f;
            x <= 2.0f;
            x += passo
        )
        {
            float nx;
            float ny;
            float nz;

            // ---------------------------------------------
            // Primeiro vértice
            // ---------------------------------------------

            float y1 =
                calcularAltura(
                    onda,
                    x,
                    z,
                    tempo
                );

            calcularNormal(
                onda,
                x,
                z,
                tempo,
                &nx,
                &ny,
                &nz
            );

            glNormal3f(
                nx,
                ny,
                nz
            );

            glVertex3f(
                x,
                y1,
                z
            );

            // ---------------------------------------------
            // Segundo vértice da faixa
            // ---------------------------------------------

            float proximoZ =
                z + passo;

            float y2 =
                calcularAltura(
                    onda,
                    x,
                    proximoZ,
                    tempo
                );

            calcularNormal(
                onda,
                x,
                proximoZ,
                tempo,
                &nx,
                &ny,
                &nz
            );

            glNormal3f(
                nx,
                ny,
                nz
            );

            glVertex3f(
                x,
                y2,
                proximoZ
            );
        }

        glEnd();
    }
}