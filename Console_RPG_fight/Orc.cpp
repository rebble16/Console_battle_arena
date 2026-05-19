#include "Orc.h"

void Orc::Attack(Character& o)
{
	int hp = o.getHP();
	hp -= damage + buff;
	if (hp < 0)hp = 0;
	o.setHP(hp);
}

bool Orc::isOnSight(Character& o)
{
	int x_enemy = o.getPosX();
	int y_enemy = o.getPosY();
	int x_me = posX;
	int y_me = posY;
	double distance = sqrt(pow(x_me - x_enemy, 2) + pow(y_me - y_enemy, 2));
	return distance <= 20.0;
}

void Orc::Character_info(Character& obj)
{
	cout << "CLOSE COMBAT" << endl;
	cout << name << "(" << appearance << ") hit " << obj.getName() << "(" << obj.getAppearance() << ")" << endl;
	cout << "Damage by " << name << "(" << appearance << "): " << damage+buff << " HP" << endl;
	cout << "Current " << obj.getName() << " HP:" << obj.getHP() << endl << endl;
}


ostream& operator<<(ostream& os, const Orc& o)
{
	os << "Race:                                "<< right << o.race << endl;
	os << "Strength buff(+DMG):                 "<<right << o.buff << endl;
	return os;
}
