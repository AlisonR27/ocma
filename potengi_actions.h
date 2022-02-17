#ifndef bot_actions_h
#define bot_actions_h

#define MAX_STR 50

void resetTarget(Ship *ship);

void sell(Ship *ship);

void fish(Ship *ship);

void move(Ship *ship);

void think(Ship *ship, Enemies *otherBoats);

#endif