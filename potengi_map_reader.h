#ifndef potengi_map_reader_h
#define potengi_map_reader_h

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


int getDistance(Ship ship, Pixel pixel);

void updateTarget(int x, int y, Ship *ship, int v);

void updateCloserHarbor(Ship * ship, Pixel harbor);

void readData(int h, int w, Ship *ship, Enemies *otherBoats);

#endif