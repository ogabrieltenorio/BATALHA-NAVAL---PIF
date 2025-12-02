# 🚢 Batalha Naval (C)

![Language](https://img.shields.io/badge/language-C-blue)
![Course](https://img.shields.io/badge/course-PIFSI%202025.2-orange)
![Status](https://img.shields.io/badge/status-completed-brightgreen)

> Projeto da disciplina **Programação de Inovação e Fundamentos de Sistemas de Informação** (PIFSI 2025.2) da **CESAR School**, pelo **incrível** professor **João Victor Tinoco**.

## 📋 Sobre o Projeto

Este projeto consiste na implementação do clássico jogo **Batalha Naval** (Battleship) via interface de linha de comando (CLI).

O objetivo pedagógico foi consolidar os fundamentos da programação estruturada em C, atendendo aos seguintes requisitos obrigatórios:
* **Alocação Dinâmica de Memória** (`malloc` e `free` para criação dos tabuleiros e frotas).
* **Estruturas de Dados** (`structs` para Jogador, Navio e Tabuleiro).
* **Ponteiros** (passagem por referência para manipulação dos dados).
* **Modularização** (separação em arquivos `.c` e `.h`).
* **Validação de Entrada** (blindagem contra inputs inválidos).

---

## 👥 Equipe

| Aluno | Email | Responsabilidades |
| :--- | :--- | :--- |
| **Gabriel Tenório** | gtlt@cesar.school | • **Revisão de Código e Correção de Bugs**<br>• Interface (IO) e Menus<br>• Sistema de Aleatoriedade (RND)<br>• Documentação |
| **Vinícius Cardoso** | vca4@cesar.school | • Lógica do Jogo (Game Loop)<br>• Gerenciamento de Memória (Board/Fleet)<br>• Estruturação do Main |

---

## 🛠️ Tecnologias

* **Linguagem:** C (Standard C99)
* **Compilador:** GCC (MinGW-w64)
* **IDE Recomendada:** VS Code
* **Bibliotecas:** Apenas padrão (`stdio.h`, `stdlib.h`, `string.h`, `time.h`, `ctype.h`).

---

## 🚀 Instalação e Execução

Como o projeto não utiliza ferramentas externas de build complexas, a compilação é feita diretamente via **GCC**. Siga os passos abaixo no seu terminal (VS Code, PowerShell ou CMD).

### 1. Preparar o Ambiente

Certifique-se de estar na pasta raiz do projeto. Em seguida, entre no diretório do código-fonte:

    cd src

### 2. Compilar

Utilize o GCC para compilar todos os arquivos `.c` e gerar o executável (`jogo.exe`):

    gcc *.c -o jogo.exe

### 3. Executar

Após compilar sem erros, inicie o jogo com o comando:

    .\jogo.exe

> **Nota:** Se precisar reiniciar o jogo do zero ou limpar o terminal, use `Ctrl + C` para parar, digite `cls` para limpar a tela e rode o executável novamente.

---

## 🎮 Como Jogar

1.  **Configuração Inicial:**
    * Ao iniciar, insira os **apelidos** (nicknames) dos dois jogadores.
    * O jogo gerencia automaticamente a criação dos tabuleiros 10x10.

2.  **Posicionamento da Frota:**
    * Cada jogador escolhe como posicionar seus navios:
    * **(M)anual:** Você digita a coordenada (ex: `A0`) e orientação (`H` ou `V`).
    * **(A)utomático:** O computador distribui os navios aleatoriamente (recomendado para testes rápidos).

3.  **O Combate:**
    * Os turnos são alternados.
    * O jogador vê o **Mapa de Tiros** (tabuleiro inimigo sem os navios) e sua própria **Frota**.
    * Digite a coordenada do ataque (ex: `B5`, `A9`).
    * O jogo informa se foi **ÁGUA**, **ACERTOU** ou se um navio foi **AFUNDADO**.

4.  **Vitória:**
    * O jogo termina imediatamente quando um jogador afunda todos os navios do oponente.

### ⚓ A Frota

Cada jogador comanda a seguinte frota (baseada nas regras clássicas):

| Qtd | Navio | Tamanho |
| :---: | :--- | :---: |
| 1 | **Porta-aviões** | 5 células |
| 1 | **Encouraçado** | 4 células |
| 2 | **Cruzadores** | 3 células |
| 2 | **Destroyers** | 2 células |

---

## 🏗️ Estrutura do Código

O projeto foi dividido em módulos para facilitar a manutenção e leitura:

```text
📁 pif-naval-c-main
│
├── 📄 README.md        # Este arquivo
│
└── 📁 src              # Código Fonte
    ├── main.c          # Loop principal e setup inicial
    ├── game.c/h        # Regras de negócio (vitória, validação de tiro)
    ├── board.c/h       # Alocação da matriz e manipulação de células
    ├── fleet.c/h       # Definição dos navios e controle de dano
    ├── io.c/h          # Interface com usuário (printf/scanf e displays)
    └── rnd.c/h         # Wrapper para geração de números aleatórios

Professor, se o senhor leu até aqui, saiba que nós amamos ter o senhor como professor. Você é um excelente profissional, mas acima de tudo, uma excelente pessoa. Eu amei fazer parte disso com você. Obrigado por todo o apoio, obrigado por ter me feito(realmente) gostar mais de C. Espero crescer mais ao seu lado no futuro!!!!! - Gtenório
