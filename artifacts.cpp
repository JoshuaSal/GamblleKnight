#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstdlib>
#include "artifacts.h"
#include "player.h"


using namespace std;

ARTI* artifactset(int lvl) {
	ARTI* artifact = new ARTI; 
	namegen(artifact);
	buffs(artifact, lvl);
	artifactdisplay(artifact);
	return artifact;
}

void artifactdisplay( ARTI* a) {
	cout << a->artiname << "\n" << a->buff1 << " +" << a->buffef1 << "\n" << a->buff2 << " +" << a->buffef2 << "\n\n";
}

void artifactselect(PLAYER *p, ARTI* a1, ARTI* a2) {
	int choice;
	cout << "Which artifact do you wish to select? (1) or (2)?";
	cin >> choice;

	if (choice == 1) {
		buffupdate(p, a1);
	}
	else if (choice == 2) {
		buffupdate(p, a2);
	}
}

void buffupdate(PLAYER *p, ARTI * a ) {
	if (strcmp(a->buff1, "HP") == 0) {
		p->HP += a->buffef1;
	}
	else if (strcmp(a->buff1, "ATK") == 0) {
		p->ATK += a->buffef1;
	}
	else if (strcmp(a->buff1, "DEF") == 0) {
		p->DEF += a->buffef1;
	}
	else if (strcmp(a->buff1, "MANA") == 0) {
		p->MANA += a->buffef1;
	}

	if (strcmp(a->buff2, "HP") == 0) {
		p->HP += a->buffef2;
	}
	else if (strcmp(a->buff2, "ATK") == 0) {
		p->ATK += a->buffef2;
	}
	else if (strcmp(a->buff2, "DEF") == 0) {
		p->DEF += a->buffef2;
	}
	else if (strcmp(a->buff2, "MANA") == 0) {
		p->MANA += a->buffef2;
	}
}


void namegen(ARTI*a) {
	string name, bridge;
	string firstname[10]
		= {"Book", "Shard", "Statue", "Grimoire", "Runes",
	"Amulet", "Canopic Jar", "Ring", "Gem", "Feather"};
	string secondname[10]
		= { "", "", "", "'s", "'s", "'s", "of", "of", "of", "of" };
	string lastname[10]
		= {"Justice", "Hell", "Misfortune", "Corruption", "Rebirth",
	"Destiny", "Resistance", "Mending", "Warding", "Charm"};


	bridge = secondname[rand() % 10];
	if (bridge == "of") {
		name = firstname[rand() % 10] + " " + bridge + " " + lastname[rand() % 10];
	}
	else {
		name = lastname[rand() % 10] + " " + firstname[rand() % 10];
	}
	const char* c = name.c_str();

	strcpy(a->artiname, c);
}

void buffs(ARTI* a, int lvl) {
	int statselect1 = rand() % (4) + 1,
		statselect2 = rand() % (4) + 1;
	float effect1 = rand() % (10) + 1,
		effect2 = rand() % (10) + 1;
	if (lvl > 10) {
		effect1 = rand() % (11) + 10;
		effect2 = rand() % (11) + 10;
	}


	if (statselect1 == 1) {
		strcpy(a->buff1, "HP");
	}
	else if (statselect1 == 2) {
		strcpy(a->buff1, "ATK");
	}
	else if (statselect1 == 3) {
		strcpy(a->buff1, "DEF");
	} 
	else if (statselect1 == 4) {
		strcpy(a->buff1, "MANA");
	}
	a->buffef1 = effect1;


	if (statselect2 == 1) {
		strcpy(a->buff2, "HP");
	}
	else if (statselect2 == 2) {
		strcpy(a->buff2, "ATK");
	}
	else if (statselect2 == 3) {
		strcpy(a->buff2, "DEF");
	}
	else if (statselect2 == 4) {
		strcpy(a->buff2, "MANA");
	}
	a->buffef2 = effect2;


}