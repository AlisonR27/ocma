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

#define MAX_STR 50

typedef struct {
  int x;
  int y;
  int value;
} Pixel;

typedef struct {
  Pixel * list;
} Enemies;

typedef struct {
  int x;
  int y;
  char id[MAX_STR];
  int maxWeight;
  int currentWeight;
  
  bool notFirstRound;
  bool enemyAtLeft;
  bool enemyAtTop;
  bool enemyAtBottom;
  bool enemyAtRight;


  int hasHarbor;
  int hasTarget;
  int isSet;

  int distanceToHarbor;
  int distanceToTarget;

  Pixel closerHarbor;
  Pixel target;
  /*
    Estados:
    0 - Indo até alvo
    1 - Pescando
    2 - Indo vender
  */
  int state;
} Ship;

int getDistance(Ship ship, Pixel pixel) {
  int numberOfRounds = abs((ship.x - pixel.x)) + abs((ship.y - pixel.y));
  return (numberOfRounds);
}
void updateTarget(int x, int y, Ship *ship, int v) {
  if (v == 0 && v == 1 && v == 11 && v == 21 && v == 31) {
    return;
  }
  if((*ship).state == 2) {
    return;
  }
  if (v != 0 && v != 1 && v != 11 && v != 21 && v != 31) {
    if ((*ship).hasTarget == 0) {
      Pixel target;
      target.x = x;
      target.y = y;
      target.value = v;
      (*ship).target = target;
      (*ship).hasTarget = 1;
      (*ship).distanceToTarget = getDistance((*ship), target);
    } else {
      if ((*ship).target.x == x && (*ship).target.y == y) {
        (*ship).target.value = v;
      }
      Pixel currentPixel;
      currentPixel.x = x;
      currentPixel.y = y;
      currentPixel.value = v;
      int distanceToCurrent = getDistance((*ship), currentPixel);
      if ((*ship).distanceToTarget > distanceToCurrent){
        (*ship).target = currentPixel;
        (*ship).distanceToTarget = distanceToCurrent;
      }
    }
  }
}
void updateCloserHarbor(Ship * ship, Pixel harbor) {
  if ((*ship).hasHarbor == 0) {
    (*ship).distanceToHarbor = getDistance((*ship), harbor);
    (*ship).closerHarbor = harbor;
    (*ship).hasHarbor = 1;
  } else {
    if (getDistance((*ship), harbor) < (*ship).distanceToHarbor) {
      (*ship).distanceToHarbor = getDistance((*ship), harbor);
      (*ship).closerHarbor = harbor;
      (*ship).hasHarbor = 1;
    }
  }
}
/* ADAPTAR EM FUNÇÃO DE COMO OS DADOS SERÃO ARMAZENADOS NO SEU BOT */
void readData(int h, int w, Ship *ship, Enemies *otherBoats) {
  char id[MAX_STR];
  int v, n, x, y;
  // lê os dados da área de pesca
  for (int i = 0; i < h; i++) {   
    for (int j = 0; j < w; j++) {
      scanf("%i", &v);
      if ((*ship).isSet == 1){
        switch(v){
          case 0: 
            break;
          case 1:
          { 
            Pixel harbor;
            harbor.x = j, harbor.y = i;
            updateCloserHarbor(ship, harbor);
            break;
          }
          default:
            updateTarget(j,i,ship,v);
            break;
        }
      }
    }
    if (i == w-1) {
     (*ship).notFirstRound = true;
    }
  }
  // lê os dados dos bots
  scanf(" BOTS %i", &n);
  (*otherBoats).list = malloc((n-1) * sizeof(Pixel));
  // Seta o ponteiro de bots para a quantidade 
  // o " " antes de BOTS é necessário para ler o '\n' da linha anterior
  int otherAux = 0;
  for (int i = 0; i < n; i++) {
    scanf("%s %i %i", id, &y, &x);
    if (strcmp(id,(*ship).id) == 0) {
      (*ship).x = x;
      (*ship).y = y;
      (*ship).isSet = 1;
      // fprintf(stderr, "(%i,%i)",(*ship).x, (*ship).y);
      if ((*ship).hasHarbor == 0) {
        (*ship).closerHarbor.x = x;
        (*ship).closerHarbor.y = y;
      }
    } else {
      Pixel boat;
      boat.x = x;
      boat.y = y;
      if ((*ship).x-1 == x) {
        (*ship).enemyAtLeft = true;
      }
      if ((*ship).x+1 == x) {
        (*ship).enemyAtRight = true;
      }
      if ((*ship).y-1 == y) {
        (*ship).enemyAtTop = true;
      }
      if ((*ship).y+1 == y) {
        (*ship).enemyAtBottom = true;
      }
      (*otherBoats).list[otherAux] = boat;
      otherAux++;
    }
  }
}
/* Vida do BOT */

void resetTarget(Ship *ship) {
  (*ship).hasTarget = 0;
  (*ship).target.x = 0;
  (*ship).target.y = 0;
  (*ship).target.value = 0;
}

void sell(Ship *ship) {
  fprintf(stderr, "Vendendo em (%i,%i)",(*ship).x,(*ship).y);
  resetTarget(ship);
  (*ship).currentWeight = 0;
  printf("SELL\n");
}
void fish(Ship *ship) {
  (*ship).currentWeight++;
  (*ship).state = 1;
  fprintf(stderr, "Pescando (%i,%i)",(*ship).x,(*ship).y);
  printf("FISH\n");
}

void move(Ship *ship) { 
  // Se estiver a direita do x do alvo, volte;
  if ((*ship).x > (*ship).target.x) {
    printf("LEFT\n");
  } else if ((*ship).x < (*ship).target.x) {
    printf("RIGHT\n");
  } else if ((*ship).y > (*ship).target.y){
    printf("UP\n");
  } else if ((*ship).y < (*ship).target.y){
    printf("DOWN\n");
  }
}

void think(Ship *ship, Enemies *otherBoats) {
  // Se o navio estiver cheio, volte para o porto
  if ((*ship).currentWeight > 9 || ((*ship).state == 1 && ((*ship).target.value == 12) || ((*ship).target.value == 22) || ((*ship).target.value == 32) )) {
    Pixel target;
    target.x = (*ship).closerHarbor.x;
    target.y = (*ship).closerHarbor.y;
    target.value = 1;
    (*ship).target = target;
    (*ship).hasTarget = 1; 
    (*ship).state = 2;
    move(ship);
  }
  // Já está no target
  else if ((*ship).target.x == (*ship).x && (*ship).target.y == (*ship).y) {
    if ((*ship).target.value == 1) {
      sell(ship);
    }
    else if ((*ship).target.value != 12 && (*ship).target.value != 22 && (*ship).target.value != 32) {
      fish(ship);
    } else {
      resetTarget(ship);
      move(ship);
    }
  } else {
    move(ship);
  }
}

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
    if (strcmp(line, "BUSY\n") == 0) {
    printf("RIGHT\n");
    }
  }

  return 0;
}