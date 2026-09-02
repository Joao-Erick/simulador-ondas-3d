#include <stdio.h>
#include <GLFW/glfw3.h>

#include "onda.h"
#include "camera.h"
#include "input.h"
#include "render.h"

int main(void)
{
    // =====================================================
    // INICIALIZAÇÃO DA GLFW
    // =====================================================

    if (!glfwInit())
    {
        printf("Erro ao inicializar a GLFW.\n");
        return -1;
    }

    // =====================================================
    // CRIAÇÃO DA JANELA
    // =====================================================

    GLFWwindow *janela =
        glfwCreateWindow(
            1200,
            720,
            "Simulador de Ondas 3D",
            NULL,
            NULL
        );

    if (janela == NULL)
    {
        printf("Erro ao criar a janela.\n");

        glfwTerminate();

        return -1;
    }

    glfwMakeContextCurrent(janela);

    /*
        Ativa sincronização vertical.
    */
    glfwSwapInterval(1);

    // =====================================================
    // OPENGL
    // =====================================================

    inicializarRenderizacao();

    // =====================================================
    // OBJETOS DO PROGRAMA
    // =====================================================

    Camera camera;
    Onda onda;
    EstadoEntrada entrada;

    inicializarCamera(&camera);
    inicializarOnda(&onda);
    inicializarEntrada(&entrada);

    // =====================================================
    // CONTROLE DA SIMULAÇÃO
    // =====================================================

    int modoVisualizacao = 0;

    float tempoSimulacao = 0.0f;

    double tempoAnterior =
        glfwGetTime();

    // =====================================================
    // LOOP PRINCIPAL
    // =====================================================

    while (!glfwWindowShouldClose(janela))
    {
        // -------------------------------------------------
        // TEMPO
        // -------------------------------------------------

        double tempoAtual =
            glfwGetTime();

        float deltaTime =
            (float)(
                tempoAtual -
                tempoAnterior
            );

        tempoAnterior =
            tempoAtual;

        /*
            Evita um salto muito grande caso
            o programa fique travado por alguns instantes.
        */
        if (deltaTime > 0.1f)
        {
            deltaTime = 0.1f;
        }

        /*
            Só avançamos o tempo da onda
            quando a simulação não está pausada.
        */
        if (!onda.pausado)
        {
            tempoSimulacao += deltaTime;
        }

        // -------------------------------------------------
        // ENTRADA DO USUÁRIO
        // -------------------------------------------------

        processarEntrada(
            janela,
            &camera,
            &onda,
            &entrada,
            &modoVisualizacao,
            &tempoSimulacao,
            deltaTime
        );

        // -------------------------------------------------
        // TAMANHO DA JANELA
        // -------------------------------------------------

        int largura;
        int altura;

        glfwGetFramebufferSize(
            janela,
            &largura,
            &altura
        );

        if (altura == 0)
        {
            altura = 1;
        }

        // -------------------------------------------------
        // RENDERIZAÇÃO
        // -------------------------------------------------

        iniciarFrame();

        desenharCena3D(
            largura,
            altura,
            &camera,
            &onda,
            tempoSimulacao,
            modoVisualizacao
        );

        desenharPainel(
            largura,
            altura,
            &onda,
            modoVisualizacao
        );

        // -------------------------------------------------
        // EXIBIÇÃO
        // -------------------------------------------------

        glfwSwapBuffers(janela);

        glfwPollEvents();
    }

    // =====================================================
    // FINALIZAÇÃO
    // =====================================================

    finalizarRenderizacao();

    glfwDestroyWindow(janela);

    glfwTerminate();

    return 0;
}