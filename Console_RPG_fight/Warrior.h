#pragma once
#include "Character.h"
class Warrior : virtual public Character { 
    string ArmorName;//название брони
    int remote_damage;//урон от дальней атаки
    int defense;//добавляет хп в зависимости от брони
    int SwordSharpness;//добавляет урон в зависимости от остроты клинка
public:
    Warrior(string cl, int hp, int dam, int x, int y, string f, char a,string w,
        string A = "Wolf school armor", int def = 25, int SS = 10, int rd = 10)
        : Character(cl, hp, dam, x, y, f, a,w), ArmorName(A), defense(def), SwordSharpness(SS),remote_damage(rd) {
        HP += defense;
    }
    virtual ~Warrior() {}
    //геттеры
    string getArmorName()const { return ArmorName; }
    int getRemote_Damage()const { return remote_damage; }
    int get_defense()const { return defense; }
    int getSwordSharpness()const { return SwordSharpness; }
    //функционал
    void Attack(Character& o)override;//виртуальная функция атаки(здесь происходит логика отнимания HP при ударе),т.к. добавляется доп.урон в зависимости от остроты клинка
    void Remote_Attack(Character& o);//атака на расстоянии с помощью арбалета
    bool isAllowedRemoteAttack(Character& o);//проверка достаточно ли расстояния для того чтобы атаковать из арбалета, если слишком близко или далеко - не атаковать
    bool isOnSight(Character& obj)override;//вирутальная функция позволяющая обнаружить врага в поле зрения
    void Character_info(Character& obj)override;//виртуальная функция, выводит информацию об атаке:кто кого атаковал,тип атаки(вблизи), сколько HP снесла атака и сколько HP осталось у противника
    void Character_info_remote(Character& obj);//вывести информацию об атаке:кто кого атаковал,тип атаки(на расстоянии), сколько HP снесла атака и сколько HP осталось у противника
    friend ostream& operator<<(ostream& os, const Warrior& o); //вывести информацию о параметрах класса
};
