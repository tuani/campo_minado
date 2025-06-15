# 💣 Campo Minado em C

Este projeto é uma versão simplificada do clássico jogo **Campo Minado**, desenvolvida em linguagem C. O jogo roda no terminal, com níveis de dificuldade, sistema de pontuação e menu de pausa.

## 🎮 Como Jogar

- O objetivo é revelar todas as células **seguras** sem clicar em uma **bomba**.
- O jogo exibe o campo com células escondidas (`.`).
- O jogador digita as coordenadas da **linha** e **coluna** para revelar uma célula.
- Se revelar uma bomba (`X`), perde o jogo.
- Se revelar todas as células seguras, vence a partida.

## 📋 Funcionalidades

- **3 níveis de dificuldade:**
  - Fácil: 4x4 com 2 bombas
  - Médio: 5x5 com 3 bombas
  - Difícil: 6x6 com 4 bombas
- **Menu principal** com opção de jogar ou sair.
- **Menu de pausa** durante o jogo.
- **Pontuação acumulada** para cada vitória.
- Exibição de bombas (apenas para testes).
- Validações para jogadas inválidas ou repetidas.

## 🧠 Estrutura do Código

- `Celula`: struct que representa cada espaço no campo (`valor`, `revelado`)
- `criar_campo`: gera o campo com bombas em posições aleatórias
- `exibir_campo`: mostra o estado atual do campo para o jogador
- `mostrar_bombas`: mostra a localização de todas as bombas (modo debug)
- `jogar_partida`: lógica principal da partida
- `menu_principal`, `menu_niveis` e `menu_pausa`: controlam navegação entre menus

## 📷 Exemplo de Saída

```bash
===== CAMPO MINADO =====
1 - Jogar
2 - Sair
Escolha: 1

Escolha o nível de dificuldade:
1 - Fácil (4x4, 2 bombas)
2 - Médio (5x5, 3 bombas)
3 - Difícil (6x6, 4 bombas)
Escolha: 2

💣 Mapa das Bombas (apenas para testes):
 .  .  .  X  .
 X  .  .  .  .
 .  .  .  .  .
 .  X  .  .  .
 .  .  .  .  .

Jogo iniciado! (-1 para pausar)

    0  1  2  3  4
 0  .  .  .  .  .
 1  .  .  .  .  .
 2  .  .  .  .  .
 3  .  .  .  .  .
 4  .  .  .  .  .

Linha (-1 pausa): 0
Coluna: 1
✅ Seguro!

...

🎉 Parabéns, você venceu!
Pontuação: 1

