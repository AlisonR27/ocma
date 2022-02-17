#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "potengi_structs.h"

#define MAX_STR 50

int getDistance(Ship ship, Pixel pixel) {
  int numberOfRounds = abs((ship.x - pixel.x)) + abs((ship.y - pixel.y));
  return (numberOfRounds);
}
void updateTarget(int x, int y, Ship *ship, int v) {
  if (v == 0 && v == 1 && v == 11 && v == 21 && v == 31) {
    return;
  }
  if(ship->state == 2) {
    return;
  }
  if (v != 0 && v != 1 && v != 11 && v != 21 && v != 31) {
    if (ship->hasTarget == 0) {
      Pixel target;
      target.x = x;
      target.y = y;
      target.value = v;
      ship->target = target;
      ship->hasTarget = 1;
      ship->distanceToTarget = getDistance((*ship), target);
    } else {
      if (ship->target.x == x && ship->target.y == y) {
        ship->target.value = v;
      }
      Pixel currentPixel;
      currentPixel.x = x;
      currentPixel.y = y;
      currentPixel.value = v;
      int distanceToCurrent = getDistance((*ship), currentPixel);
      if (ship->distanceToTarget > distanceToCurrent){
        ship->target = currentPixel;
        ship->distanceToTarget = distanceToCurrent;
      }
    }
  }
}
void updateCloserHarbor(Ship * ship, Pixel harbor) {
  if (ship->hasHarbor == 0) {
    ship->distanceToHarbor = getDistance((*ship), harbor);
    ship->closerHarbor = harbor;
    ship->hasHarbor = 1;
  } else {
    if (getDistance((*ship), harbor) < ship->distanceToHarbor) {
      ship->distanceToHarbor = getDistance((*ship), harbor);
      ship->closerHarbor = harbor;
      ship->hasHarbor = 1;
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
      if (ship->isSet == 1){
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
     ship->notFirstRound = true;
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
    if (strcmp(id,ship->id) == 0) {
      ship->x = x;
      ship->y = y;
      ship->isSet = 1;
      // fprintf(stderr, "(%i,%i)",ship->x, ship->y);
      if (ship->hasHarbor == 0) {
        ship->closerHarbor.x = x;
        ship->closerHarbor.y = y;
      }
    } else {
      Pixel boat;
      boat.x = x;
      boat.y = y;
      (*otherBoats).list[otherAux] = boat;
      otherAux++;
    }
  }
}
// in the start of the game, detect how much harbors there are (including the player spawn)