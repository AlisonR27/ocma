/********************************************************************
  Bot-exemplo
  
  Após receber as informações iniciais do jogo, a cada rodada esse
  bot irá se movimentar para esquerda.
  Cabe a você agora aprimorar sua estratégia!!!
 ********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "potengi_map_reader.h"
#include "potengi_actions.h"

#define MAX_STR 50

int main() {
  char line[MAX_STR];   // dados temporários
  char myId[MAX_STR];   // identificador do bot em questão

  setbuf(stdin, NULL);   // stdin, stdout e stderr não terão buffers
  setbuf(stdout, NULL);  // assim, nada é "guardado temporariamente"
  setbuf(stderr, NULL);

  // === INÍCIO DA PARTIDA ===
  int h, w;
  Ship ship;
  ship.hasTarget = 0;
  ship.distanceToHarbor = 0;
  ship.distanceToTarget = 0 ;
  ship.hasHarbor = 0;
  ship.isSet = 0;
  ship.target.x = 0, ship.target.y = 0;
  ship.currentWeight = 0;
  Enemies otherBoats;
  scanf("AREA %i %i", &h, &w);  // lê a dimensão da área de pesca: altura (h) x largura (w)
  scanf(" ID %s", &ship.id);        // ...e o id do bot
  // obs: o " " antes de ID é necessário para ler o '\n' da linha anterior
  // Para "debugar", é possível enviar dados para a saída de erro padrão (stderr).
  // Esse dado não será enviado para o simulador, apenas para o terminal.
  // A linha seguinte é um exemplo. Pode removê-la se desejar.
  fprintf(stderr, "Meu id = %s\n", &ship.id);

  // === PARTIDA === 
  // O bot entra num laço infinito, mas não se preocupe porque o simulador irá matar
  // o processo quando o jogo terminar.
  while (1) {
    // LÊ OS DADOS DO JOGO E ATUALIZA OS DADOS DO BOT
    readData(h, w, &ship, &otherBoats);
    think(&ship, &otherBoats);
    // lê qual foi o resultado da ação (e eventualmente atualiza os dados do bot).
    scanf("%s", line);
    if (strcmp(line, "IMPACT\n") == 0) {
      fprintf(stderr,"IMPACTO MIZERA");
    }
  }

  return 0;
}