#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "potengi_structs.h"

#define MAX_STR 50

void resetTarget(Ship *ship) {
  ship->hasTarget = 0;
  ship->target.x = 0;
  ship->target.y = 0;
  ship->target.value = 0;
}

void sell(Ship *ship) {
  fprintf(stderr, "Vendendo em (%i,%i)",ship->x,ship->y);
  resetTarget(ship);
  ship->currentWeight = 0;
  printf("SELL\n");
}
void fish(Ship *ship) {
  if(ship->target.value == 11 || ship->target.value == 21 || ship->target.value == 31) {
    resetTarget(ship);
    printf("RIGHT\n");
    return;
  }
  ship->currentWeight++;
  ship->state = 1;
  fprintf(stderr, "Pescando (%i)",ship->target.value);
  printf("FISH\n");
}

void move(Ship *ship) { 
  // Se estiver a direita do x do alvo, volte;
  if (ship->x > ship->target.x) {
    printf("LEFT\n");
  } else if (ship->x < ship->target.x) {
    printf("RIGHT\n");
  } else if (ship->y > ship->target.y){
    printf("UP\n");
  } else if (ship->y < ship->target.y){
    printf("DOWN\n");
  }
}

void think(Ship *ship, Enemies *otherBoats) {
  // Se o navio estiver cheio, volte para o porto
  if (ship->currentWeight > 9 || (ship->state == 1 && (ship->target.value == 12) || (ship->target.value == 22) || (ship->target.value == 32) )) {
    Pixel target;
    target.x = ship->closerHarbor.x;
    target.y = ship->closerHarbor.y;
    target.value = 1;
    ship->target = target;
    ship->hasTarget = 1; 
    ship->state = 2;
    move(ship);
  }
  // Já está no target
  else if (ship->target.x == ship->x && ship->target.y == ship->y) {
    if (ship->target.value == 1) {
      sell(ship);
    }
    else if (ship->target.value != 12 && ship->target.value != 22 && ship->target.value != 32) {
      fish(ship);
    } else {
      resetTarget(ship);
      move(ship);
    }
  } else {
    move(ship);
  }
}
