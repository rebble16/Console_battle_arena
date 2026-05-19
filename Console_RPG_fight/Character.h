#pragma once
#include<iostream>
#include<string>
#include<cmath>
#include<windows.h>
using namespace std;
enum { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };
const int HEIGHT = 14;
const int WIDTH = 14;
extern char MAP[HEIGHT][WIDTH];
class Character {
protected:
    string name;//имя персонажа
    string feature;//его особенность(преимущество)
    char appearance;//оторажение на экране
    int HP;//уровень здоровья
    int damage;//сколько HP снимает ближняя атака
    string weapon;//название оружия
    int posX, posY;//позиция на арене
public:
    Character(string C = "Unknown", int h = 100, int d = 10, int x = 5, int y = 5, string f = "close combat", char ch = 'W',string w="sword");
    virtual ~Character() {}
    //геттеры 
    string getName() const { return name; }
    int getHP() const { return HP; }
    int getDamage() const { return damage; }
    char getAppearance() const { return appearance; }
    string getFeature() const { return feature; }
    string getWeapon()const { return weapon; }
    int getPosX()const { return posX; };
    int getPosY()const { return posY; };
    //сеттеры
    int setHP(int hp=0) { return HP=hp; };
    //функционал
    void move(int dx, int dy, Character& o);//передвижение по арене
    bool inBorders(int d)const;//проверка на достижение границы
    bool isOccupied(int y, int x, Character& o)const;//проверка на занятость клетки на арене,чтобы избежать столкновение двух бойцов
    void toRun(Character& o, bool isUnderAttack);//отбежать, если враг имеет преимущество в ближнем бою
    void toPursue(Character& o);//преследовать врага, если он слаб в ближнем бою
    bool isAllowedToAttack(Character& o)const;//проверка достаточно ли близко подошел для ближней атаки
    void showCloseAttack(Character& o)const;//отобразить ближнюю атаку на экране
    void animateRemoteAttack(Character& o, char symb);//отобразить атаку на расстоянии
    void showRemoteAttack(Character& o, int x, int y, char& symb);//отобразить позицию стрелы(пламенного шара) на данный момент
    virtual void Attack(Character& obj) = 0;
    virtual bool isOnSight(Character& obj) = 0;
    virtual void Character_info(Character& obj) = 0;
    friend ostream& operator<<(ostream& os, Character& o);//вывести основную информацию о персонаже
};