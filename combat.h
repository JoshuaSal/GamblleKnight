#pragma once
#include "player.h"
#include "enemy.h"
#include "skills.h"
#ifndef COMBAT_H

using namespace std;
struct BatStat{
	float hp,
		atk,
		def,
		mana;
	int pass = 0;
	int psactivecode = -1;
};

int battle(PLAYER* p, ENEMY* e, int lvl, SKILLCLASS::SKILLS* s[3]);
void playerturn(PLAYER* p, ENEMY* e, BatStat* pbs, BatStat* ebs, SKILLCLASS::SKILLS* s[3], int round, int lvl);
void enemyturn(PLAYER* p, ENEMY* e, BatStat* pbs, BatStat* ebs); 
float hitCalc();
bool skillsmenu(PLAYER* p, ENEMY* e, BatStat* pbs, BatStat* ebs, SKILLCLASS::SKILLS* s[3]);
bool skillexecute(PLAYER* p, ENEMY* e, BatStat* pbs, BatStat* ebs, SKILLCLASS::SKILLS* s);
void rounddetails(PLAYER* p, BatStat* pbs, BatStat* ebs, int round, int lvl);
#endif // !COMBAT_H

