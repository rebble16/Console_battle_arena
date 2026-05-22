#pragma once
#include"Character.h"
class Magician :public Character
{
private:
	string power;
	int power_damage;
public:
	Magician(string cl, int hp, int dam, int x, int y, string f, char a,string w,
		string p = "Fire", int pd = 25) :Character(cl, hp, dam, x, y, f, a,w),power(p),power_damage(pd){}
	virtual ~Magician() {}
	void Attack(Character& o)override;//ближняя атака стальным шестом
	void Magic_Attack(Character& o);//атака магией на расстоянии
	bool isAllowedMagicAttack(Character& o);//проверка достаточно ли расстояния для того чтобы атаковать магией, если слишком близко или далеко - не атаковать
	bool isOnSight(Character& obj)override;//видно ли врага, если расстояние до врага меньше или равно 15.0, то true, иначе false
	void Character_info(Character& obj)override;//вывести информацию об атаке:кто кого атаковал,тип атаки(вблизи), сколько HP снесла атака и сколько HP осталось у противника
	void Character_info_remote(Character& obj)const;//вывести информацию об атаке:кто кого атаковал,тип атаки(на расстоянии), сколько HP снесла атака и сколько HP осталось у противника
	friend ostream& operator<<(ostream& os, Magician& o);//вывести информацию о параметрах класса
};
