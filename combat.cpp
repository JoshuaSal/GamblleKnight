#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "combat.h"
#include "enemy.h"
#include "player.h"
#include "skills.h"

using namespace std;
int battle(PLAYER* p, ENEMY* e, int lvl, SKILLCLASS::SKILLS* s[3]) {
	int outcome = 1, round = 1;
	BatStat* pbs = new BatStat;
	BatStat* ebs = new BatStat;

	pbs->hp = p->HP;
	pbs->atk = p->ATK;
	pbs->def = p->DEF;
	pbs->mana = p->MANA;


	ebs->hp = e->HP;
	ebs->atk = e->ATK;
	ebs->def = e->DEF;
	ebs->mana = e->MANA;

	while (pbs->hp > 0 && ebs->hp > 0) {
		rounddetails(p, pbs, ebs, round, lvl);
		playerturn(p, e, pbs, ebs, s, round, lvl);
		cin.ignore();
		cin.ignore();
		rounddetails(p, pbs, ebs, round, lvl);
		enemyturn(p, e, pbs, ebs);
		cin.ignore();
		rounddetails(p, pbs, ebs, round, lvl);
		pbs->mana++;
		if (pbs->mana > p->MANA) {
			pbs->mana = p->MANA;
		}
		ebs->mana++;
		if (ebs->mana > e->MANA) {
			ebs->mana = e->MANA;
		}
		//decrease passive
		pbs->pass--;
		if (pbs->pass < 0) {
			pbs->pass = 0;
		}
		round++;
	}
	if (ebs->hp > 0) {
		outcome = 0;
	}
	system("cls");
	cout << "\n\nEnd of level\n\n";
	return outcome;
}

void rounddetails(PLAYER* p, BatStat* pbs, BatStat* ebs, int round, int lvl) {
	system("cls");
	cout << "\t\t\tlevel " << lvl;
	cout << "\n___________________________________________________________________________________";
	cout << "\n\n\t\t\tRound: " << round << "\n\n";
	cout << p->name << "\n";
	cout << setprecision(3);
	cout << "HP: " << pbs->hp << "\t\t\t\t\t\t\tEnemy HP: " << ebs->hp << "\n";
	cout << "ATK: " << pbs->atk << "\t\t\t\t\t\t\tEnemy ATK:" << ebs->atk << "\n";
	cout << "DEF: " << pbs->def << "\t\t\t\t\t\t\tEnemy DEF:" << ebs->def << "\n";
	cout << "MANA: " << pbs->mana << "\t\t\t\t\t\tEnemy MANA:" << ebs->mana << "\n\n";
	cout << "___________________________________________________________________________________\n";

}

float hitCalc() {
	float randnum = rand() % (10) + 1;
	return randnum;
}

//player's turn
void playerturn(PLAYER* p, ENEMY* e, BatStat *pbs, BatStat * ebs, SKILLCLASS::SKILLS* s[3], int round, int lvl) {
	int choice = 0;
	pbs->def = p->DEF;
	float dmg = 0;
	//Passive skills check
	if (pbs->pass != -1 && pbs->pass> 0) {
		if (pbs->psactivecode == 0) {
			cout << "Passive left: " << pbs->pass << "\n";
			ebs->def = 0;
		}
	}
	else if (pbs->pass == 0) {
		ebs->atk = e->ATK;
		ebs->def = e->DEF;
	}
	if (e->level < 6) {
		cout <<"\t\t"<< p->name << "'s turn\n\n";
		cout << "\t\t"<<"What does " << p->name << " do?\n";
		cout << "\t\t"<<"(1) Attack\t(2) Guard\n\t\t\t>";
		cin >> choice;

		if (choice == 1) {
			cout << p->name << " attacks!\n";
			if (hitCalc() + pbs->atk > ebs->def) {
				dmg = ((p->ATK / 10) + 1);
				cout << "Attack hits! Deals " << dmg << " damage!\n";
				ebs->hp -= dmg;
			}
			else {
				cout << "Attack missed!";
			}
		}
		else if (choice == 2) {
			cout << p->name << " Guards!";
			pbs->def += p->DEF / 2;
		}
	}
	else
	{
		cout << "\t\t" << p->name << "'s turn\n\n";
		cout << "\t\t" << "What does " << p->name << " do?\n";
		cout << "\t\t" << "(1) Attack\t(2) Guard\n\t\t(3) Skills\n\t\t\t>";
		cin >> choice;

		if (choice == 1) {
			cout << p->name << " attacks!\n";
			if (hitCalc() + pbs->atk > ebs->def) {
				dmg = ((p->ATK / 10) + 1);
				cout << "Attack hits! Deals " << dmg << " damage!\n";
				ebs->hp -= dmg;
			}
			else {
				cout << "Attack missed!";
			}
		}
		else if (choice == 2) {
			cout << p->name << " Guards!";
			pbs->def += p->DEF / 2;
		}
		else if (choice == 3) {
			if (skillsmenu(p, e, pbs, ebs, s) == false) {
				rounddetails(p, pbs, ebs, round, lvl);
				playerturn(p, e, pbs, ebs, s, round, lvl);
			}
		}
	}
}



//enemy's turn
void enemyturn(PLAYER* p, ENEMY* e, BatStat* pbs, BatStat* ebs) {
	int echoice = rand() % (3) + 1;
	ebs->def = e->DEF;
	float dmg;
	cout << "\n\nEnemy's turn\n";


	if (echoice == 1) {
		cout << "Enemy attacks!\n";
		if ( hitCalc() + ebs->atk > pbs->def) {
			dmg = ((e->ATK / 10) + 1);
			cout << "Attack hits! Deals " << dmg << " damage!\n";
			pbs->hp -= dmg;
		}
		else {
			cout << "Attack missed!";
		}
	}
	else if (echoice == 2) {
		cout << "Enemy Guards!";
		ebs->def += e->DEF / 2;
	}
	else if (echoice == 3) {

	}
}

bool skillsmenu(PLAYER* p, ENEMY* e, BatStat* pbs, BatStat* ebs, SKILLCLASS::SKILLS* s[3]) {
	SKILLCLASS skill;
	int choice = 0;
	int skillchoice = -1;
	if (e->level > 15) {
		cout << "(1) ";
		skill.skilldisplay(s[0]);
		cout << "\n";
		cout << "(2) ";
		skill.skilldisplay(s[1]);
		cout << "\n";
		cout << "(3) ";
		skill.skilldisplay(s[2]);
	}
	else if (e->level > 10) {
		cout << "(1) ";
		skill.skilldisplay(s[0]);
		cout << "\n";
		cout << "(2) ";
		skill.skilldisplay(s[1]);
		cout << "\n";
	} else if (e->level >= 6) {
		cout << "(1) ";
		skill.skilldisplay(s[0]);
	}
	cout << "\n(4) Go back";
	cout << "\n\nWhich skill would you like to use?\n>";
	cin >> choice;
	if (choice == 1) {
		skillchoice = 0;
	}
	else if (choice == 2) {
		skillchoice = 1;
	}
	else if (choice == 3) {
		skillchoice = 2;

	}
	else if (choice == 4) {
		system("cls");
		return false;
	}
	
	return skillexecute(p, e, pbs, ebs, s[skillchoice]);
}



bool skillexecute(PLAYER* p, ENEMY* e, BatStat* pbs, BatStat* ebs, SKILLCLASS::SKILLS* s) {
	if (s->effect2 <= pbs->mana) {
		if (s->skillcode == 0) {
			cout << "Dealt " << s->effect1 << " damage";
			ebs->hp -= s->effect1;
		}
		else if (s->skillcode == 1) {
			cout << "Healed " << s->effect1 << " hp";
			pbs->hp += s->effect1;
			if (pbs->hp > p->HP) {
				pbs->hp = p->HP;
			}
		}
		else if (s->skillcode == 2) {
			cout << "Strengthened armor by " << s->effect1;
			pbs->def += s->effect1;
		}
		else if (s->skillcode == 3) {
			cout << "The enemy's defenses have been elminated for the next 5 rounds";
			pbs->pass += s->effect1;
			pbs->psactivecode = 0;
		}
		pbs->mana -= s->effect2;
		return true;
	}
	else if (s->effect2 > pbs->mana) {
		cout << "\nNot enough mana!\n";
		cin.ignore();
		cin.ignore();
		return false;
	}
	

}

