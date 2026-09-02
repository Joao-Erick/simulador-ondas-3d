#include <math.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <GLFW/glfw3.h>

#include "render.h"

#define PI 3.14159265358979323846

#define LARGURA_PAINEL 280

static GLuint fonteBase = 0;

// =========================================================
// PROJEÇÃO PERSPECTIVA
// =========================================================

static void configurarPerspectiva(
    float fov,
    float aspecto,
    float perto,
    float longe
)
{
    float topo =
        perto *
        tanf(
            fov *
            PI /
            360.0f
        );

    float direita =
        topo *
        aspecto;

    glFrustum(
        -direita,
        direita,
        -topo,
        topo,
        perto,
        longe
    );
}

// =========================================================
// FONTE
// =========================================================

static void criarFonte()
{
    HDC hdc =
        wglGetCurrentDC();

    HFONT fonte =
        CreateFont(
            -16,
            0,
            0,
            0,
            FW_NORMAL,
            FALSE,
            FALSE,
            FALSE,
            ANSI_CHARSET,
            OUT_TT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            ANTIALIASED_QUALITY,
            FF_DONTCARE |
            DEFAULT_PITCH,
            "Arial"
        );

    HGDIOBJ fonteAnterior =
        SelectObject(
            hdc,
            fonte
        );

    fonteBase =
        glGenLists(96);

    wglUseFontBitmaps(
        hdc,
        32,
        96,
        fonteBase
    );

    SelectObject(
        hdc,
        fonteAnterior
    );

    DeleteObject(
        fonte
    );
}

// =========================================================
// TEXTO
// =========================================================

static void desenharTexto(
    float x,
    float y,
    const char *texto
)
{
    glRasterPos2f(
        x,
        y
    );

    glPushAttrib(
        GL_LIST_BIT
    );

    glListBase(
        fonteBase - 32
    );

    glCallLists(
        strlen(texto),
        GL_UNSIGNED_BYTE,
        texto
    );

    glPopAttrib();
}

// =========================================================
// MODO 2D
// =========================================================

static void iniciarModo2D(
    int largura,
    int altura
)
{
    /*
        Salvamos a matriz de projeção 3D.
    */

    glMatrixMode(
        GL_PROJECTION
    );

    glPushMatrix();

    glLoadIdentity();

    /*
        Criamos uma projeção ortográfica.

        Isso permite trabalhar usando
        coordenadas diretamente da tela.
    */

    glOrtho(
        0,
        largura,
        altura,
        0,
        -1,
        1
    );

    /*
        Salvamos também a ModelView.
    */

    glMatrixMode(
        GL_MODELVIEW
    );

    glPushMatrix();

    glLoadIdentity();

    /*
        O painel não precisa de iluminação
        nem teste de profundidade.
    */

    glDisable(
        GL_DEPTH_TEST
    );

    glDisable(
        GL_LIGHTING
    );
}

// =========================================================
// RETORNO AO MODO 3D
// =========================================================

static void finalizarModo2D()
{
    glEnable(
        GL_LIGHTING
    );

    glEnable(
        GL_DEPTH_TEST
    );

    glMatrixMode(
        GL_MODELVIEW
    );

    glPopMatrix();

    glMatrixMode(
        GL_PROJECTION
    );

    glPopMatrix();

    glMatrixMode(
        GL_MODELVIEW
    );
}

// =========================================================
// MATERIAL DA ÁGUA
// =========================================================

static void configurarMaterialAgua()
{
    /*
        Componente especular.

        É responsável pelo brilho
        concentrado observado na água.
    */

    GLfloat materialEspecular[] =
    {
        0.9f,
        0.95f,
        1.0f,
        1.0f
    };

    glMaterialfv(
        GL_FRONT_AND_BACK,
        GL_SPECULAR,
        materialEspecular
    );

    /*
        Controla a concentração
        do brilho especular.
    */

    glMaterialf(
        GL_FRONT_AND_BACK,
        GL_SHININESS,
        80.0f
    );
}

// =========================================================
// INICIALIZAÇÃO DO OPENGL
// =========================================================

void inicializarRenderizacao()
{
    // -----------------------------------------------------
    // TESTE DE PROFUNDIDADE
    // -----------------------------------------------------

    /*
        Ativa o Z-buffer.

        Ele permite determinar quais
        superfícies estão na frente
        e quais estão atrás.
    */

    glEnable(
        GL_DEPTH_TEST
    );

    // -----------------------------------------------------
    // ILUMINAÇÃO
    // -----------------------------------------------------

    glEnable(
        GL_LIGHTING
    );

    glEnable(
        GL_LIGHT0
    );

    // -----------------------------------------------------
    // MATERIAL E COR
    // -----------------------------------------------------

    glEnable(
        GL_COLOR_MATERIAL
    );

    glColorMaterial(
        GL_FRONT_AND_BACK,
        GL_AMBIENT_AND_DIFFUSE
    );

    // -----------------------------------------------------
    // NORMAIS
    // -----------------------------------------------------

    glEnable(
        GL_NORMALIZE
    );

    // -----------------------------------------------------
    // REFLEXÃO ESPECULAR
    // -----------------------------------------------------

    glLightModeli(
        GL_LIGHT_MODEL_LOCAL_VIEWER,
        GL_TRUE
    );

    // -----------------------------------------------------
    // CONFIGURAÇÃO DA LUZ
    // -----------------------------------------------------

    GLfloat luzAmbiente[] =
    {
        0.15f,
        0.15f,
        0.20f,
        1.0f
    };

    GLfloat luzDifusa[] =
    {
        0.85f,
        0.90f,
        1.0f,
        1.0f
    };

    GLfloat luzEspecular[] =
    {
        1.0f,
        1.0f,
        1.0f,
        1.0f
    };

    glLightfv(
        GL_LIGHT0,
        GL_AMBIENT,
        luzAmbiente
    );

    glLightfv(
        GL_LIGHT0,
        GL_DIFFUSE,
        luzDifusa
    );

    glLightfv(
        GL_LIGHT0,
        GL_SPECULAR,
        luzEspecular
    );

    // -----------------------------------------------------
    // COR DE FUNDO
    // -----------------------------------------------------

    glClearColor(
        0.025f,
        0.06f,
        0.11f,
        1.0f
    );

    // -----------------------------------------------------
    // FONTE DO PAINEL
    // -----------------------------------------------------

    criarFonte();
}

// =========================================================
// INÍCIO DE UM NOVO FRAME
// =========================================================

void iniciarFrame()
{
    /*
        Limpamos:

        1. Buffer de cor
        2. Buffer de profundidade
    */

    glClear(
        GL_COLOR_BUFFER_BIT |
        GL_DEPTH_BUFFER_BIT
    );
}

// =========================================================
// CENA 3D
// =========================================================

void desenharCena3D(
    int largura,
    int altura,
    Camera *camera,
    Onda *onda,
    float tempoSimulacao,
    int modoVisualizacao
)
{
    int larguraCena =
        largura -
        LARGURA_PAINEL;

    if (larguraCena < 1)
    {
        larguraCena = 1;
    }

    // =====================================================
    // VIEWPORT
    // =====================================================

    glViewport(
        0,
        0,
        larguraCena,
        altura
    );

    float aspecto =
        (float)larguraCena /
        (float)altura;

    // =====================================================
    // PROJEÇÃO
    // =====================================================

    glMatrixMode(
        GL_PROJECTION
    );

    glLoadIdentity();

    configurarPerspectiva(
        60.0f,
        aspecto,
        0.1f,
        100.0f
    );

    // =====================================================
    // MODELVIEW
    // =====================================================

    glMatrixMode(
        GL_MODELVIEW
    );

    glLoadIdentity();

    /*
        Aplicamos as transformações
        da câmera.
    */

    aplicarCamera(
        camera
    );

    // =====================================================
    // POSIÇÃO DA LUZ
    // =====================================================

    GLfloat posicaoLuz[] =
    {
        2.0f,
        4.0f,
        2.0f,
        1.0f
    };

    glLightfv(
        GL_LIGHT0,
        GL_POSITION,
        posicaoLuz
    );

    // =====================================================
    // MATERIAL
    // =====================================================

    configurarMaterialAgua();

    // =====================================================
    // MODO DE REPRESENTAÇÃO
    // =====================================================

    if (
        modoVisualizacao == 0
    )
    {
        /*
            Superfície preenchida.
        */

        glPolygonMode(
            GL_FRONT_AND_BACK,
            GL_FILL
        );
    }
    else if (
        modoVisualizacao == 1
    )
    {
        /*
            Wireframe.

            Exibe as arestas da malha.
        */

        glPolygonMode(
            GL_FRONT_AND_BACK,
            GL_LINE
        );
    }
    else
    {
        /*
            Apenas os vértices.
        */

        glPolygonMode(
            GL_FRONT_AND_BACK,
            GL_POINT
        );

        glPointSize(
            3.0f
        );
    }

    // =====================================================
    // SUPERFÍCIE DE ONDAS
    // =====================================================

    desenharOnda(
        onda,
        tempoSimulacao
    );

    /*
        Restauramos o modo preenchido
        antes de desenhar a interface.
    */

    glPolygonMode(
        GL_FRONT_AND_BACK,
        GL_FILL
    );
}

// =========================================================
// PAINEL
// =========================================================

void desenharPainel(
    int largura,
    int altura,
    Onda *onda,
    int modoVisualizacao
)
{
    float painelX =
        largura -
        LARGURA_PAINEL;

    /*
        Utilizamos toda a janela para
        desenhar a interface 2D.
    */

    glViewport(
        0,
        0,
        largura,
        altura
    );

    iniciarModo2D(
        largura,
        altura
    );

    // =====================================================
    // FUNDO DO PAINEL
    // =====================================================

    glColor3f(
        0.08f,
        0.08f,
        0.12f
    );

    glBegin(
        GL_QUADS
    );

    glVertex2f(
        painelX,
        0
    );

    glVertex2f(
        largura,
        0
    );

    glVertex2f(
        largura,
        altura
    );

    glVertex2f(
        painelX,
        altura
    );

    glEnd();

    // =====================================================
    // LINHA DIVISÓRIA
    // =====================================================

    glColor3f(
        0.2f,
        0.6f,
        0.9f
    );

    glBegin(
        GL_LINES
    );

    glVertex2f(
        painelX,
        0
    );

    glVertex2f(
        painelX,
        altura
    );

    glEnd();

    // =====================================================
    // TÍTULO
    // =====================================================

    glColor3f(
        1.0f,
        1.0f,
        1.0f
    );

    desenharTexto(
        painelX + 20,
        35,
        "SIMULADOR DE ONDAS 3D"
    );

    // =====================================================
    // CÂMERA
    // =====================================================

    glColor3f(
        0.4f,
        0.8f,
        1.0f
    );

    desenharTexto(
        painelX + 20,
        80,
        "CAMERA"
    );

    glColor3f(
        1.0f,
        1.0f,
        1.0f
    );

    desenharTexto(
        painelX + 20,
        105,
        "W / S  Aproximar / Afastar"
    );

    desenharTexto(
        painelX + 20,
        130,
        "A / D  Movimento lateral"
    );

    desenharTexto(
        painelX + 20,
        155,
        "Setas  Rotacionar camera"
    );

    // =====================================================
    // ONDA
    // =====================================================

    glColor3f(
        0.4f,
        0.8f,
        1.0f
    );

    desenharTexto(
        painelX + 20,
        200,
        "ONDA"
    );

    glColor3f(
        1.0f,
        1.0f,
        1.0f
    );

    desenharTexto(
        painelX + 20,
        225,
        "1 / 2  Amplitude"
    );

    desenharTexto(
        painelX + 20,
        250,
        "3 / 4  Frequencia"
    );

    desenharTexto(
        painelX + 20,
        275,
        "5 / 6  Velocidade"
    );

    desenharTexto(
        painelX + 20,
        300,
        "ESPACO Pausar / Continuar"
    );

    desenharTexto(
        painelX + 20,
        325,
        "R      Reiniciar"
    );

    // =====================================================
    // VISUALIZAÇÃO
    // =====================================================

    glColor3f(
        0.4f,
        0.8f,
        1.0f
    );

    desenharTexto(
        painelX + 20,
        370,
        "VISUALIZACAO"
    );

    glColor3f(
        1.0f,
        1.0f,
        1.0f
    );

    desenharTexto(
        painelX + 20,
        395,
        "F1  Preenchido"
    );

    desenharTexto(
        painelX + 20,
        420,
        "F2  Wireframe"
    );

    desenharTexto(
        painelX + 20,
        445,
        "F3  Pontos"
    );

    // =====================================================
    // PARÂMETROS
    // =====================================================

    glColor3f(
        0.4f,
        0.8f,
        1.0f
    );

    desenharTexto(
        painelX + 20,
        490,
        "PARAMETROS"
    );

    char texto[128];

    glColor3f(
        1.0f,
        1.0f,
        1.0f
    );

    snprintf(
        texto,
        sizeof(texto),
        "Amplitude: %.2f",
        onda->amplitude
    );

    desenharTexto(
        painelX + 20,
        520,
        texto
    );

    snprintf(
        texto,
        sizeof(texto),
        "Frequencia: %.2f",
        onda->frequencia
    );

    desenharTexto(
        painelX + 20,
        545,
        texto
    );

    snprintf(
        texto,
        sizeof(texto),
        "Velocidade: %.2f",
        onda->velocidade
    );

    desenharTexto(
        painelX + 20,
        570,
        texto
    );

    const char *modo;

    if (
        modoVisualizacao == 0
    )
    {
        modo =
            "Preenchido";
    }
    else if (
        modoVisualizacao == 1
    )
    {
        modo =
            "Wireframe";
    }
    else
    {
        modo =
            "Pontos";
    }

    snprintf(
        texto,
        sizeof(texto),
        "Modo: %s",
        modo
    );

    desenharTexto(
        painelX + 20,
        595,
        texto
    );

    snprintf(
        texto,
        sizeof(texto),
        "Estado: %s",
        onda->pausado
            ? "PAUSADO"
            : "RODANDO"
    );

    desenharTexto(
        painelX + 20,
        620,
        texto
    );

    desenharTexto(
        painelX + 20,
        675,
        "ESC  Sair"
    );

    finalizarModo2D();
}

// =========================================================
// FINALIZAÇÃO
// =========================================================

void finalizarRenderizacao()
{
    if (fonteBase != 0)
    {
        glDeleteLists(
            fonteBase,
            96
        );

        fonteBase = 0;
    }
}