# Blackjack-ED

Este projeto implementa um jogo de **Blackjack (21)** em linguagem **C**.

## Estrutura do Projeto

* `main.c`: Contém o ponto de entrada principal da aplicação e fluxo principal do jogo, recebe como argumento o numero de jogadores de 1-10.
* `game.c` / `game.h`: Implementa toda as funções de jogo do Blackjack, pontuação e regras.
* `deck.c` / `deck.h`: Responsável por gerar e manipular o baralho de cartas.
* `LICENSE`: Licença do projeto.

## Compilação

Para compilar o projeto, é necessário ter um compilador C instalado, como o **gcc**.

### Exemplo de compilação no Linux / Mac / Windows (usando terminal com gcc):

```bash
gcc -o blackjack main.c game.c deck.c
```

Este comando gera um executável chamado `blackjack`.

## Execução

Depois de compilado, execute o programa com:

```bash
./blackjack
```

No Windows:

```bash
blackjack.exe
```

## Funcionalidades

* Simula o jogo de Blackjack com as seguintes regras:

* O jogador pode pedir carta ou parar.
* Verifica condições de vitória automaticamente(quem fizer 21 ou o mais próximo possível).
* Baralho embaralhado a cada jogo.
* Cálculo dinâmico da pontuação(O Ás vale 11, as cartas com caras{valete, reis, e rainha} valem 10).
*Caso alguém passe de 21, a pessoa estoura(perde o jogo).
*Após cada partida a potuação pode ser salva(opção do usuário) em um arquivo scored, as pontuações anteriores podem ser vistas após o termino da partida.

## Requisitos

* Compilador C (gcc, clang, etc)
* Sistema operacional compatível com linha de comando

---

