#include "Magician.h"

void Magician::Attack(Character& o)
{
	int hp = o.getHP();
	hp -= damage;
	if (hp < 0)hp = 0;
	o.setHP(hp);
}

void Magician::Magic_Attack(Character& o)
{
	int hp = o.getHP();
	hp -= power_damage;
	if (hp < 0)hp = 0;
	o.setHP(hp);
}

bool Magician::isAllowedMagicAttack(Character& o)
{
	int x_enemy = o.getPosX();
	int y_enemy = o.getPosY();
	int x_me = posX;
	int y_me = posY;
	double distance = sqrt(pow(x_me - x_enemy, 2) + pow(y_me - y_enemy, 2));
	return distance > 1.5 && distance <= 4;
}

bool Magician::isOnSight(Character& obj)
{
	int x_enemy = obj.getPosX();
	int y_enemy = obj.getPosY();
	int x_me = posX;
	int y_me = posY;
	double distance = sqrt(pow(x_me - x_enemy, 2) + pow(y_me - y_enemy, 2));
	return distance <= 15.0;
}


void Magician::Character_info(Character& obj)
{
	cout << "CLOSE COMBAT" << endl;
	cout << name << "(" << appearance << ") hit " << obj.getName() << "(" << obj.getAppearance() << ")" << endl;
	cout << "Damage by " << name << "(" << appearance << "): " << damage << " HP" << endl;
	cout << "Current " << obj.getName() << " HP:" << obj.getHP() << endl << endl;
}

void Magician::Character_info_remote(Character& obj) const
{
	cout << "REMOTE ATTACK BY REAL MAGIC" << endl;
	cout << name << "(" << appearance << ") hit " << obj.getName() << "(" << obj.getAppearance() << ")" << endl;
	cout << "Damage by " << name << "(" << appearance << "): " << power_damage << " HP" << endl;
	cout << "Current " << obj.getName() << " HP:" << obj.getHP() << endl << endl;
}

ostream& operator<<(ostream& os, Magician& o)
{
	os << "Power of:                            " << o.power << endl;
	os << "Magic attack(DMG):                   " << o.power_damage << endl;
	return os;
}
