#include <GLFW/glfw3.h>

#include "input.h"

// =========================================================
// INICIALIZAÇÃO
// =========================================================

void inicializarEntrada(
    EstadoEntrada *entrada
)
{
    entrada->teclaEspacoAnterior =
        GLFW_RELEASE;
}

// =========================================================
// PROCESSAMENTO DO TECLADO
// =========================================================

void processarEntrada(
    GLFWwindow *janela,
    Camera *camera,
    Onda *onda,
    EstadoEntrada *entrada,
    int *modoVisualizacao,
    float *tempoSimulacao,
    float deltaTime
)
{
    float velocidadeCamera =
        2.0f * deltaTime;

    float velocidadeRotacao =
        60.0f * deltaTime;

    // =====================================================
    // CÂMERA
    // =====================================================

    if (
        glfwGetKey(
            janela,
            GLFW_KEY_W
        ) == GLFW_PRESS
    )
    {
        camera->z +=
            velocidadeCamera;
    }

    if (
        glfwGetKey(
            janela,
            GLFW_KEY_S
        ) == GLFW_PRESS
    )
    {
        camera->z -=
            velocidadeCamera;
    }

    if (
        glfwGetKey(
            janela,
            GLFW_KEY_A
        ) == GLFW_PRESS
    )
    {
        camera->x +=
            velocidadeCamera;
    }

    if (
        glfwGetKey(
            janela,
            GLFW_KEY_D
        ) == GLFW_PRESS
    )
    {
        camera->x -=
            velocidadeCamera;
    }

    if (
        glfwGetKey(
            janela,
            GLFW_KEY_UP
        ) == GLFW_PRESS
    )
    {
        camera->rotacaoX +=
            velocidadeRotacao;
    }

    if (
        glfwGetKey(
            janela,
            GLFW_KEY_DOWN
        ) == GLFW_PRESS
    )
    {
        camera->rotacaoX -=
            velocidadeRotacao;
    }

    if (
        glfwGetKey(
            janela,
            GLFW_KEY_LEFT
        ) == GLFW_PRESS
    )
    {
        camera->rotacaoY -=
            velocidadeRotacao;
    }

    if (
        glfwGetKey(
            janela,
            GLFW_KEY_RIGHT
        ) == GLFW_PRESS
    )
    {
        camera->rotacaoY +=
            velocidadeRotacao;
    }

    // =====================================================
    // AMPLITUDE
    // =====================================================

    if (
        glfwGetKey(
            janela,
            GLFW_KEY_1
        ) == GLFW_PRESS
    )
    {
        aumentarAmplitude(
            onda
        );
    }

    if (
        glfwGetKey(
            janela,
            GLFW_KEY_2
        ) == GLFW_PRESS
    )
    {
        diminuirAmplitude(
            onda
        );
    }

    // =====================================================
    // FREQUÊNCIA
    // =====================================================

    if (
        glfwGetKey(
            janela,
            GLFW_KEY_3
        ) == GLFW_PRESS
    )
    {
        aumentarFrequencia(
            onda
        );
    }

    if (
        glfwGetKey(
            janela,
            GLFW_KEY_4
        ) == GLFW_PRESS
    )
    {
        diminuirFrequencia(
            onda
        );
    }

    // =====================================================
    // VELOCIDADE DA ONDA
    // =====================================================

    if (
        glfwGetKey(
            janela,
            GLFW_KEY_5
        ) == GLFW_PRESS
    )
    {
        aumentarVelocidade(
            onda
        );
    }

    if (
        glfwGetKey(
            janela,
            GLFW_KEY_6
        ) == GLFW_PRESS
    )
    {
        diminuirVelocidade(
            onda
        );
    }

    // =====================================================
    // PAUSA
    // =====================================================

    int teclaEspacoAtual =
        glfwGetKey(
            janela,
            GLFW_KEY_SPACE
        );

    /*
        Detectamos somente o momento
        em que a tecla é pressionada.

        Isso evita pausar e continuar
        centenas de vezes enquanto
        a tecla permanece pressionada.
    */

    if (
        teclaEspacoAtual ==
            GLFW_PRESS &&
        entrada->teclaEspacoAnterior ==
            GLFW_RELEASE
    )
    {
        onda->pausado =
            !onda->pausado;
    }

    entrada->teclaEspacoAnterior =
        teclaEspacoAtual;

    // =====================================================
    // RESET
    // =====================================================

    if (
        glfwGetKey(
            janela,
            GLFW_KEY_R
        ) == GLFW_PRESS
    )
    {
        reiniciarOnda(
            onda
        );

        *tempoSimulacao =
            0.0f;
    }

    // =====================================================
    // MODOS DE VISUALIZAÇÃO
    // =====================================================

    if (
        glfwGetKey(
            janela,
            GLFW_KEY_F1
        ) == GLFW_PRESS
    )
    {
        *modoVisualizacao =
            0;
    }

    if (
        glfwGetKey(
            janela,
            GLFW_KEY_F2
        ) == GLFW_PRESS
    )
    {
        *modoVisualizacao =
            1;
    }

    if (
        glfwGetKey(
            janela,
            GLFW_KEY_F3
        ) == GLFW_PRESS
    )
    {
        *modoVisualizacao =
            2;
    }

    // =====================================================
    // FECHAR PROGRAMA
    // =====================================================

    if (
        glfwGetKey(
            janela,
            GLFW_KEY_ESCAPE
        ) == GLFW_PRESS
    )
    {
        glfwSetWindowShouldClose(
            janela,
            GLFW_TRUE
        );
    }
}