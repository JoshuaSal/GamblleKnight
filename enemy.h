#pragma once
#ifndef ENEMY_H
using namespace std;

struct ENEMY {
	int level;
	float
		HP = 10,
		ATK = 5,
		DEF = 5,
		MANA = 10;
};

ENEMY* enemystat(int lvl);
void statDisp(ENEMY* e);
float statMod(int lvl);

#endif // !ENEMY_H
