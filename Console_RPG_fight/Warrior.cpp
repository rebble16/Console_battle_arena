#include "Warrior.h"
ostream& operator<<(ostream& os, const Warrior& o) {
    os << "Armor named:                         " << o.ArmorName << endl;
    os << "Armor protection(+HP):               " << o.defense << endl;
    os << "Sword sharpness(+DMG):               " << o.SwordSharpness << endl;
    os << "Remote damage by crossbow:           " << o.remote_damage << endl;
    return os;
}

void Warrior::Attack(Character& o)
{
    int hp = o.getHP();
    hp -= damage+SwordSharpness;
    if (hp < 0)hp = 0;
    o.setHP(hp);
}

void Warrior::Remote_Attack(Character& o)
{
    int hp = o.getHP();
    hp -= remote_damage;
    if (hp < 0)hp = 0;
    o.setHP(hp);
}

bool Warrior::isAllowedRemoteAttack(Character& o)
{
    int x_enemy = o.getPosX();
    int y_enemy = o.getPosY();
    int x_me = posX;
    int y_me = posY;
    double distance = sqrt(pow(x_me - x_enemy, 2) + pow(y_me - y_enemy, 2));
    return distance>1.5&&distance<=3.0;
}

bool Warrior::isOnSight(Character& obj)
{
    int x_enemy = obj.getPosX();
    int y_enemy = obj.getPosY();
    int x_me = posX;
    int y_me = posY;
    double distance = sqrt(pow(x_me - x_enemy, 2) + pow(y_me - y_enemy, 2));
    return distance <= 20.0;
}

void Warrior::Character_info(Character& obj)
{
    cout << "CLOSE COMBAT" << endl;
    cout << name << "(" << appearance << ") hit " << obj.getName() << "(" << obj.getAppearance() << ")" << endl;
    cout << "Damage by " << name << "(" << appearance << "): " << damage+SwordSharpness << " HP" << endl;
    cout << "Current " << obj.getName() << " HP:" << obj.getHP() << endl<<endl;
}

void Warrior::Character_info_remote(Character& obj)
{
    cout << "REMOTE ATTACK BY CROSSBOW" << endl;
    cout << name << "(" << appearance << ") hit " << obj.getName() << "(" << obj.getAppearance() << ")" << endl;
    cout << "Damage by " << name << "(" << appearance << "): " << remote_damage << " HP" << endl;
    cout << "Current " << obj.getName() << " HP:" << obj.getHP() << endl << endl;
}

