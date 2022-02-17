#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "potengi_structs.h"

#define MAX_STR 50

void resetTarget(Ship *ship) {
  ship->hasTarget = 0;
  ship->distanceToTarget = 0;
  ship->target.x = 0;
  ship->target.y = 0;
  ship->target.value = 0;
}
void setHarborAsTarget(Ship *ship) {
  fprintf(stderr, "(%i, %i)",ship->closerHarbor.x,ship->closerHarbor.y);
  ship->target.x = ship->closerHarbor.x;
  ship->target.y = ship->closerHarbor.y;
  ship->target.value = 1;
  ship->hasTarget = 1; 
  ship->state = 2;
}
void sell(Ship *ship) {
  //fprintf(stderr, "Vendendo em (%i,%i)",ship->x,ship->y);
  printf("SELL\n");
  ship->currentWeight = 0;
  ship->state = 0;
  resetTarget(ship);
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
  } else {
    if (ship->currentWeight > 9) {
      setHarborAsTarget(ship);
    }
  }
}

void fish(Ship *ship) {
  if(ship->target.value == 11 || ship->target.value == 21 || ship->target.value == 31) {
    resetTarget(ship);
    move(ship);
  } else {
    ship->currentWeight++;
    ship->state = 1;
    ship->target.value--;
    fprintf(stderr, "Pescando (%i)",ship->target.value);
    printf("FISH\n");
  }
}

void think(Ship *ship, Enemies *otherBoats) {
  if (ship->currentWeight > 9) {
    setHarborAsTarget(ship);
    move(ship);
  }
  if (ship->target.x == ship->x && ship->target.y == ship->y) {
    if (ship->target.value == 1) {
      if (ship->currentWeight == 0) {
        resetTarget(ship);
        move(ship);
      } else {
        sell(ship);
        ship->state = 0;
      }
    } else if (ship->currentWeight > 5) {
      setHarborAsTarget(ship);
      move(ship);
    } else if ((ship->target.value > 11 && ship->target.value < 20) || (ship->target.value > 21 && ship->target.value < 30) || (ship->target.value > 31 && ship->target.value < 40)) {
      fish(ship);
    } else {
      resetTarget(ship);
      move(ship);
    }
  } else {
    move(ship);
  }
}
