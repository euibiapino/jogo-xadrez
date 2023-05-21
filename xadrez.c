#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

int xequemate = 0;
int permissao, vez = 0;
int cordapeca = 0;
int peao1 = 0;
int peao2 = 0;
int ultimaLinha, ultimaColuna;

char xadrez[8][8] = {
  
    {'T', 'C', 'B', 'Q', 'K', 'B', 'C', 'T'},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {'t', 'c', 'b', 'q', 'k', 'b', 'c', 't'}};

int pintura()
{
  system("CLS");
  int lin, col, t, i, aux = -1;
  printf("              CHESS TITANS");
  printf("\n  0    1    2    3    4    5    6    7\n-----------------------------------------\n");

  for (lin = 0; lin < 8; lin++)
  {
    aux++;
    for (t = 0; t < 3; t++)
    {
      for (col = 0; col < 8; col++)
      {
        char peca = xadrez[lin][col];
        char letra = ((lin + col) % 2 == 0) ? '\xB2' : ' ';
        letra = (t == 1 && peca != ' ') ? peca : letra;
        if ((lin + col) % 2 == 0)
        {
          printf("\xB2\xB2%c\xB2\xB2", letra);
        }
        else
        {
          printf("  %c  ", letra);
        }
        if ((col == 7) && t != 1)
        {
          printf(" |");
        }
        if ((col == 7) && t == 1)
        {
          printf(" | %d", aux);
        }
      }
      printf("\n");
    }
  }
}

int movimento(int linhaO, int colunaO, int linhaD, int colunaD)
{
  int promopeao1 = 0, promopeao2 = 0;
  int p1 = 0;
  int p2 = 0;
  int dv, dh, acao = 0;
  char peca;
  peca = xadrez[linhaO][colunaO];

  dv = abs(linhaD - linhaO);

  dh = abs(colunaD - colunaO);

  if ((peca == 'T') && (dv == 0 || dh == 0))
  {
    acao = 1;
  }
  if ((peca == 'B') && (dv == dh))
  {
    acao = 1;
  }
  if ((peca == 'C') && ((dv == 1 && dh == 2) || (dv == 2 && dh == 1)))
  {
    acao = 1;
  }
  if ((peca == 'Q') && ((dv == dh) || (dv == 0) || (dh == 0)))
  {
    acao = 1;
  }
  if ((peca == 'K') && ((dv >= 0 && dv <= 1) && (dh >= 0 && dh <= 1)))
  {
    acao = 1;
  }
  if ((peca == 'P') && (peao1 == 0) && (((linhaD - linhaO) == 2) && (dh == 0)) || (((linhaD - linhaO) == 1)) || (((linhaD - linhaO) == 1) && ((dv == dh))))
  {
    acao = 1;
    peao1 = 1;
  }
  if (peca == 'P' && linhaO == 4 && linhaD == 5 && dh == 1 && linhaD == ultimaLinha && colunaD == ultimaColuna)
  {
    acao = 1;
    xadrez[linhaD - 1][colunaD] = ' ';
  }
  if ((peca == 'P') && (peao1 == 1) && (((linhaD - linhaO) == 1) && (dh == 0)) || (((linhaD - linhaO) == 1) && ((dv == dh))))
  {
    acao = 1;
  }
  if ((peca == 't') && (dv == 0 || dh == 0))
  {
    acao = 1;
  }
  if ((peca == 'b') && (dv == dh))
  {
    acao = 1;
  }
  if ((peca == 'c') && ((dv == 1 && dh == 2) || (dv == 2 && dh == 1)))
  {
    acao = 1;
  }
  if ((peca == 'q') && ((dv == dh) || (dv == 0) || (dh == 0)))
  {
    acao = 1;
  }
  if ((peca == 'k') && ((dv >= 0 && dv <= 1) && (dh >= 0 && dh <= 1)))
  {
    acao = 1;
  }
  if ((peca == 'p') && (peao2 == 0) && (((linhaD - linhaO) == -2) && (dh == 0)) || (((linhaD - linhaO) == -1) && (dh == 0)) || (((linhaD - linhaO) == -1) && ((dh == dv))))
  {
    acao = 1;
    peao2 = 1;
  }
  if (peca == 'p' && linhaO == 3 && linhaD == 2 && dh == 1 && linhaD == ultimaLinha && colunaD == ultimaColuna)
  {
    acao = 1;
    // Captura en passant do peão branco
    xadrez[linhaD + 1][colunaD] = ' ';
  }
  if ((peca == 'p') && (peao2 == 1) && (((linhaD - linhaO) == -1) && (dh == 0)) || (((linhaD - linhaO) == -1) && ((dv == dh))))
  {
    acao = 1;
  }

  vez = islower(peca);

  // Verifica a condição de xeque-mate //
  if ((xadrez[linhaD][colunaD] == 'K') || (xadrez[linhaD][colunaD] == 'k'))
  {
    xequemate = 1;
  }
  // Verifica se o movimento for válido //
  if ((acao == 1) && (dv + dh > 0))
  {
    // Verifica se o jogador das pretas tentou mover uma peça branca //
    if (vez == 0 && permissao != 0)
    {
      printf("\nVoce nao pode mover uma peca preta.");
      getch();
    }
    // Verifica se o jogador das brancas tentou mover uma peça preta //
    else if (vez != 0 && permissao != 2)
    {
      printf("\nVoce nao pode mover uma peca branca.");
      getch();
    }
    else
    {
      // Executa o movimento //
      cordapeca++;
      xadrez[linhaD][colunaD] = xadrez[linhaO][colunaO];
      xadrez[linhaO][colunaO] = ' ';

      ultimaLinha = linhaD;
      ultimaColuna = colunaD;

      // Promoção dos peões pretos caso eles cheguem ao final do seu respectivo lado do tabuleiro //
      if ((peca == 'P') && (peao1 == 1) && (p1 == 0) && (((linhaD - linhaO) == 1) && (dh == 0)) && (xadrez[linhaD][colunaD] == xadrez[7][colunaD]) || (((linhaD - linhaO) == 1) && ((dv == dh))) && (xadrez[linhaD][colunaD] == xadrez[7][colunaD]))
      {
        printf("Bravo peao, voce merece uma promocao!\nEscolha para qual peca voce quer se promover e aperte Enter:\n 1-Rainha\n 2-Torre\n 3-Cavalo\n 4-Bispo\n");
        scanf("%d", &promopeao1);
      }
      switch (promopeao1)
      {
      case 1:
        xadrez[linhaO][colunaO] = ' ';
        xadrez[linhaD][colunaD] = 'Q';
        p1++;
        break;
      case 2:
        xadrez[linhaD][colunaD] = ' ';
        xadrez[linhaD][colunaD] = 'T';
        p1++;
        break;
      case 3:
        xadrez[linhaD][colunaD] = ' ';
        xadrez[linhaD][colunaD] = 'C';
        p1++;
        break;
      case 4:
        xadrez[linhaD][colunaD] = ' ';
        xadrez[linhaD][colunaD] = 'B';
        p1++;
        break;
      }
      // Promoção dos peões brancos caso eles cheguem ao final do seu respectivo lado do tabuleiro //
      if ((peca == 'p') && (peao2 == 1) && (p2 == 0) && (((linhaD - linhaO) == -1) && (dh == 0)) && (xadrez[linhaD][colunaD] == xadrez[0][colunaD]) || (((linhaD - linhaO) == -1) && ((dv == dh))) && (xadrez[linhaD][colunaD] == xadrez[0][colunaD]))
      {
        printf("Bravo peao, voce merece uma promocao!\nEscolha para qual peca voce quer se promover e aperte Enter:\n 1-Rainha\n 2-Torre\n 3-Cavalo\n 4-Bispo\n");
        scanf("%d", &promopeao2);
      }
      switch (promopeao2)
      {
      case 1:
        xadrez[linhaO][colunaO] = ' ';
        xadrez[linhaD][colunaD] = 'q';
        p2++;
        break;
      case 2:
        xadrez[linhaD][colunaD] = ' ';
        xadrez[linhaD][colunaD] = 't';
        p2++;
        break;
      case 3:
        xadrez[linhaD][colunaD] = ' ';
        xadrez[linhaD][colunaD] = 'c';
        p2++;
        break;
      case 4:
        xadrez[linhaD][colunaD] = ' ';
        xadrez[linhaD][colunaD] = 'b';
        p2++;
        break;
      }
    }
  }
  else
  {
    printf("\nO movimento da peca foi invalido, aperte qualquer tecla para tentar novamente...");
    getch();
  }
}

int main()
{
  int linhaO, linhaD, colunaO, colunaD;
  while (1)
  {
    if (xequemate == 0)
    {
      pintura();
      if (cordapeca % 2 == 0)
      {
        printf("Jogam as brancas! (minusculas)");
        permissao = 2;
      }
      else
      {
        printf("Jogam as pretas! (maiusculas)");
        permissao = 0;
      }
      printf("\nInforme a linha e coluna de origem:  ");
      scanf("%d %d", &linhaO, &colunaO);
      printf("Informe a linha e coluna de destino: ");
      scanf("%d %d", &linhaD, &colunaD);

      if ((linhaO >= 0 && linhaO < 8 && colunaO >= 0 && colunaO < 8) && (linhaD >= 0 && linhaD < 8 && colunaD >= 0 && colunaD < 8))
      {
        movimento(linhaO, colunaO, linhaD, colunaD);
      }
      else
      {
        printf("\nLinha e/ou coluna invalida, aperte qualquer tecla para tentar novamente...\n");
        getch();
      }
    }
    else
    {
      printf("Rei inimigo capturado, fim de jogo!");
      return 0;
    }
  }
  getch();
  return 0;
}