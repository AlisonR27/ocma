/********************************************************************
  Bot-exemplo
  
  Após receber as informações iniciais do jogo, a cada rodada esse
  bot irá se movimentar para esquerda.
  Cabe a você agora aprimorar sua estratégia!!!
 ********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR 50

typedef struct {
  int x;
  int y;
} Harbor;

typedef struct {
  int * w;
  int * h;
} Map;

typedef struct {
  int x;
  int y;
  char id[MAX_STR];
  int maxWeight;
  int currentWeight;

  Harbor closerHarbor;
} Ship;

typedef struct {
  int numberOfBots;
  int numberOfHarbors;
  Harbor * harbors;
} State;

typedef struct {
  char **  position;
} Map;

void detectWalls(int h, int w, Ship ship) {
  int chunk = 3;
  // padrão, xNextToWall: 0 longe da parede, 1 perto da parede da esquerda, 2 perto da parede da direita
  int xNextToWall;
  // padrão, yNextToWall: 0 longe da parede, 1 perto da parede de cima, 2 perto da parede de baixo
  int yNextToWall;
  // Verifica se está perto da parede
  if (ship.x < chunk) {
    xNextToWall = 1;
  } else if (ship.x > w - chunk) {
    xNextToWall = 2;
  } else { 
    xNextToWall = 0;
  }
  if (ship.y < chunk) {
    yNextToWall = 1;
  } else if (ship.y > h - chunk){
    yNextToWall = 2;
  } else {
    yNextToWall = 0;
  }
  
  // O array guidance dará 4 coordenadas, que será o chunk de varredura ao redor do barco
}

// Primeiro checar em cruz, depois checar os outros 4 pontos
detectFish(int h, int w, Ship ship, Map * map) {
  //if ()
}

/* ADAPTAR EM FUNÇÃO DE COMO OS DADOS SERÃO ARMAZENADOS NO SEU BOT */
void readData(int h, int w, Ship ship, Map * map) {
  if (!map) {
    map = malloc(sizeof(char) * h * w);
  }
  char id[MAX_STR];
  int v, n, x, y;
  // lê os dados da área de pesca
  for (int i = 0; i < h; i++) {   
    for (int j = 0; j < w; j++) {
      scanf("%i", &v);
    }
  }
  // lê os dados dos bots
  scanf(" BOTS %i", &n);
  
  // Seta o ponteiro de bots para a quantidade 
  // o " " antes de BOTS é necessário para ler o '\n' da linha anterior
  for (int i = 0; i < n; i++) {
    scanf("%s %i %i", id, &x, &y);
    if (strcmp(id,ship.id)) {
      ship.x = x;
      ship.y = y;
      if (x != 0 && (ship.closerHarbor.x == 0) || y != 0 && (ship.closerHarbor.y == 0)) {
        ship.closerHarbor.x = x;
        ship.closerHarbor.y = y;
      }
    }
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
  ship.currentWeight = 0;
  State state;
  Map map; 
  scanf("AREA %i %i", &h, &w);  // lê a dimensão da área de pesca: altura (h) x largura (w)
  scanf(" ID %s", &ship.id);        // ...e o id do bot
  // obs: o " " antes de ID é necessário para ler o '\n' da linha anterior
  // Para "debugar", é possível enviar dados para a saída de erro padrão (stderr).
  // Esse dado não será enviado para o simulador, apenas para o terminal.
  // A linha seguinte é um exemplo. Pode removê-la se desejar.
  fprintf(stderr, "Meu id = %s\n", myId);

  // === PARTIDA === 
  // O bot entra num laço infinito, mas não se preocupe porque o simulador irá matar
  // o processo quando o jogo terminar.
  while (1) {

    // LÊ OS DADOS DO JOGO E ATUALIZA OS DADOS DO BOT
    readData(h, w, &ship, &map);

    // switch (state) {
    //   case GOING_TO_FISHING_POINT:
    //     kdjhgjksdfhjks;
    //     if(????) {
    //       state = FISHING;
    //     }
    //     strcpy(action, "LEFT");
    //     break;

    //   case FISHING:
    //     sdjghsf;
    //     if (???) {
    //       state = 
    //     }
    //     strcpy(action, "FISH");
    //     break;
    // }
    // printf("%s\n", action);

    // INSIRA UMA LÓGICA PARA ESCOLHER UMA AÇÃO A SER EXECUTADA

    // envia a ação escolhida (nesse exemplo, ir para esquerda)
    printf("LEFT\n");

    // lê qual foi o resultado da ação (e eventualmente atualiza os dados do bot).
    scanf("%s", line);
  }

  return 0;
}