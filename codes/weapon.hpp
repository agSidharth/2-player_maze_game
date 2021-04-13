#pragma once
#include<iostream>

class Weapon
{
public:
	weapon();
	~weapon();

	void switch(int t) {type = t;}

	int hastype() {return type;}

private:
	int type; //1 for melee, 2 for mine, 3 for assault rifle, 4 for sniper, 5 for frag
	int ammo = 0;
}