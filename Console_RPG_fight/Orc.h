#pragma once
#include "Character.h"
class Orc :virtual public Character
{
private:
	string race;//раса орка
	int buff;//доп.урон в зависимости от расы
public:
	Orc(string cl, int hp, int dam, int x, int y, string f, char a,string w,
		string r="Grey orc", int b=20) :Character(cl, hp, dam, x, y, f, a,w), race(r), buff(b) { }
	virtual ~Orc() {}
	void Attack(Character& o)override;//виртуальная функция атаки(здесь происходит логика отнимания HP при ударе),т.к. добавляется доп.урон в зависимости от расы орка(физ.сила)
	bool isOnSight(Character& o)override;//вирутальная функция позволяющая обнаружить врага в поле зрения(каждый класс имеет свою дальность)
	void Character_info(Character& obj)override;//виртуальная функция, выводит информацию об атаке:кто кого атаковал,тип атаки(вблизи), сколько HP снесла атака и сколько HP осталось у противника
	friend ostream& operator<<(ostream& os, const Orc& o);//вывести информацию о параметрах класса
};
