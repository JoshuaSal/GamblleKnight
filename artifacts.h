#pragma once
#include "player.h"
#ifndef ARTIFACT_H
struct ARTI {
	char artiname[50];
	char buff1[5], buff2[5];
	float buffef1, buffef2;
	int level = 1;

};
ARTI* artifactset(int lvl);
void artifactdisplay(ARTI* a);
void artifactselect(PLAYER* p, ARTI* a1, ARTI* a2);
void buffupdate(PLAYER* p, ARTI* a);
void namegen(ARTI *a);
void buffs(ARTI* a, int lvl);
#endif // !ARTIFACT_H
