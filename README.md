# Simulador de Ondas 3D

Simulador interativo de uma superfície de ondas em três dimensões, desenvolvido em **C**, **OpenGL** e **GLFW** como projeto acadêmico de Computação Gráfica.

## Sobre o projeto

A superfície é construída com faixas de triângulos (`GL_TRIANGLE_STRIP`). Sua altura varia com o tempo pela superposição de duas ondas senoidais, uma no eixo X e outra no eixo Z:

```text
y(x, z, t) = A · sen(f · x − v · t) + A · sen(f · z − v · t)
```

O simulador calcula normais aproximadas para a iluminação, utiliza projeção em perspectiva e teste de profundidade (*Z-buffer*) e apresenta um painel com os parâmetros atuais.

## Funcionalidades

- Ajuste em tempo real de amplitude, frequência e velocidade.
- Pausa, retomada e reinício da simulação.
- Movimentação e rotação da câmera.
- Três modos de visualização: preenchido, wireframe e pontos.
- Painel lateral com controles, parâmetros e estado da simulação.

## Tecnologias

- **C**
- **OpenGL** (pipeline de funções fixas)
- **GLFW 3** para janela e entrada de teclado
- **Win32/GDI** para desenhar textos no painel (implementação específica do Windows)

## Controles

| Tecla | Ação |
| --- | --- |
| W / S | Aproximar / afastar a câmera |
| A / D | Movimentar a câmera lateralmente |
| Setas | Rotacionar a câmera |
| 1 / 2 | Aumentar / diminuir amplitude |
| 3 / 4 | Aumentar / diminuir frequência |
| 5 / 6 | Aumentar / diminuir velocidade |
| Espaço | Pausar / continuar |
| R | Reiniciar parâmetros e tempo |
| F1 | Superfície preenchida |
| F2 | Wireframe |
| F3 | Pontos |
| Esc | Fechar o programa |

## Estrutura do código

| Arquivos | Responsabilidade |
| --- | --- |
| `main.c` | Inicialização da GLFW e laço principal |
| `camera.c` / `camera.h` | Transformações da câmera |
| `input.c` / `input.h` | Processamento de teclas e comandos |
| `onda.c` / `onda.h` | Modelo matemático e geometria da onda |
| `render.c` / `render.h` | Cena 3D, iluminação e painel 2D |

O repositório também contém diretórios de configuração e dependências locais, como `include/GLFW` e `lib`.

## Compilação no Windows

Use um compilador C compatível com as bibliotecas GLFW presentes em `include/` e `lib/`, por exemplo, uma instalação compatível do MinGW/TDM-GCC.

Na raiz do projeto:

```bash
gcc main.c camera.c input.c onda.c render.c -Iinclude -Llib -lglfw3 -lopengl32 -lgdi32 -lm -o simulador.exe
```

Dependendo da versão do compilador e da distribuição da GLFW, podem ser necessários ajustes na vinculação de bibliotecas. A compilação **não foi validada novamente** nesta atualização da documentação.

> O arquivo `render.c` utiliza APIs do Windows. A aplicação não é diretamente portável para Linux ou macOS sem adaptações.

## Demonstração

Uma captura de tela ou GIF do programa em execução será acrescentado futuramente para mostrar os modos preenchido e wireframe.

## Conceitos aplicados

Modelagem matemática de ondas, malhas triangulares, cálculo de normais, iluminação, projeção em perspectiva, Z-buffer, organização modular em C e processamento de entrada do usuário.
