#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include "enemy.h"

using namespace std;

ENEMY* enemystat(int lvl) {
	ENEMY* enemy = new ENEMY;
	enemy->level = lvl;
	
	
	enemy->HP += statMod(enemy->level);
	enemy->ATK += statMod(enemy->level);
	enemy->DEF += statMod(enemy->level);
	enemy->MANA += statMod(enemy->level);

	statDisp(enemy);
	return enemy;
}


float statMod(int lvl) {
	float statmod = 0;
	if (lvl < 5) {
		statmod += ((rand() % (lvl + 5) + lvl) / 2) * lvl;
	}
	else if (lvl < 10 && lvl >= 5) {
		statmod += (((rand() % lvl + (lvl-3)) / 2) * lvl)*0.75;
	}
	else if (lvl >= 10 && lvl < 20) {
		statmod += (((rand() % (lvl)+ (lvl - 5)) / 2) * lvl)*0.75;
	}
	else if (lvl >=20){
		statmod += (((rand() % (lvl)+(lvl - 7)) / 2) * lvl) * 0.50;
	}
	return statmod;
}

void statDisp(ENEMY* e) {
	cout << "\n\nEnemy stats:\n";
	cout << "\nLevel: " << e->level << "\nHP: " << e->HP
		<< "\nATK: " << e->ATK << "\nDEF: " << e->DEF
		<< "\nMANA: " << e->MANA << "\n";
}