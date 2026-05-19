#include "Warrior.h"
#include "Orc.h"
#include "Magician.h"
#include<fstream>
enum{orcVSwarrior=1,orcVSmagician,warriorVSmagician,QUIT};
void showMap(Character* ch1, Character* ch2);
void move_ch(int& d, Character& o, Character& check);
void move_ch_opposite(int& d, Character& o, Character& check);
void gotoxy(int x, int y);
void SaveVictory(string winner);
int OrcVSWarrior(int& whoHitsFirst, Warrior& witcher, Orc& azog, int& dir1, int& dir2, bool& isHit1, bool& isOver);
int OrcVSMagician(int& whoHitsFirst, Orc& azog, Magician& vilgefortz, int& dir1, int& dir2, bool& isHit1, bool& isOver);
int WarriorVSMagician(int& whoHitsFirst, Warrior& witcher, Magician& vilgefortz, int& dir1, int& dir2, bool& isHit1, bool& isOver);
int BattlePick();
void menu(Warrior& o1, Orc& o2, Magician& o3);
void Logo();
void GameOver();




int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "RU");
    gotoxy(0, 0); // курсор в начало консоли
    Warrior witcher("Geralt of Rivia", 100, 20, 2, 3, "Magic signs", 'W', "Sword");
    Orc azog("Azog the Defiler", 150, 20, 10, 5, "Superhuman strength", 'O',"Mace");
    Magician vilgefortz("Vilgefortz of Roggeveen", 100, 10, 4, 11, "Master of Magic", 'M',"Steel pole");
    //cout << witcher;
    bool isOver = false;
    bool isHit1 = false;
    int dir1 = 0;
    int dir2 = 0;
    int whoHits = 0;//кто бьет?Если 0-воин,если 1-орк
    menu(witcher,azog,vilgefortz);
    int pick = BattlePick();
    system("cls");
    while (!isOver)
    {
        switch (pick)
        {
        case orcVSwarrior:
            OrcVSWarrior(whoHits, witcher, azog, dir1, dir2, isHit1, isOver);
            //добавить войну отображение выстрела с арбалета
            break;
        case orcVSmagician:
            //орк против маги
            OrcVSMagician(whoHits, azog, vilgefortz, dir1, dir2, isHit1, isOver);
            //добавить магу отображение магической атаки на карте
            break;
        case warriorVSmagician:
            //воин против маги
            WarriorVSMagician(whoHits, witcher, vilgefortz, dir1, dir2, isHit1, isOver);
            break;
        case QUIT:
            isOver = true;
            break;
        default:
            break;
        }
    }
    return 0;
}






void showMap(Character* ch1, Character* ch2)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == ch1->getPosY() && j == ch1->getPosX())
            {
                cout << ch1->getAppearance();
            }
            else if (i == ch2->getPosY() && j == ch2->getPosX())
            {
                cout << ch2->getAppearance();
            }
            else cout << MAP[i][j];
        }
        cout << endl;
    }
}
void move_ch(int& d, Character& o, Character& check)
{
    if (d == UP)o.move(0, -1, check);
    else if (d == DOWN)o.move(0, 1, check);
    else if (d == LEFT)o.move(-1, 0, check);
    else if (d == RIGHT)o.move(1, 0, check);
    else cout << "Error!" << endl;
}
void move_ch_opposite(int& d, Character& o, Character& check)
{
    if (d == UP)o.move(0, 1, check);
    else if (d == DOWN)o.move(0, -1, check);
    else if (d == LEFT)o.move(1, 0, check);
    else if (d == RIGHT)o.move(-1, 0, check);
    else cout << "Error!" << endl;
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void SaveVictory(string winner)
{
    //считаем количество строк в файле
    ifstream file("winners.txt");
    if (!file.is_open())
    {
        cout << "Error 303!Couldn't open file!" << endl;
    }
    int counter = 0;
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            if (!line.empty()) counter++;
        }
        file.close();
    }
    //добавляем строку в файл
    ofstream outFile("winners.txt", ios::app);
    if (outFile.is_open()) {
        outFile << counter + 1 << ". " << winner << " won the battle!" << endl;
        outFile.close();
    }
}


int OrcVSWarrior(int& whoHitsFirst, Warrior& witcher, Orc& azog, int& dir1, int& dir2, bool& isHit1, bool& isOver)
{
    whoHitsFirst = rand() % 2;
    showMap(&witcher, &azog);
    if (azog.isOnSight(witcher))azog.toPursue(witcher);
    else {
        dir2 = rand() % 4;
        if (azog.inBorders(dir2))
            move_ch(dir2, azog, witcher);
        else
            move_ch_opposite(dir2, azog, witcher);
    }
    isHit1 = false;
    if (witcher.isAllowedRemoteAttack(azog))
    {
        witcher.Remote_Attack(azog);
        witcher.animateRemoteAttack(azog, '.');
        witcher.Character_info_remote(azog);
        if (azog.getHP() <= 0)
        {
            isOver = true;
            Sleep(1000);
            system("cls");
            cout << "Witcher won the battle!Last attack was remote." << endl;
            GameOver();
            SaveVictory("Witcher");
            return 0;
        }
    }
    if (witcher.isAllowedToAttack(azog) && whoHitsFirst == 0)
    {
        witcher.Attack(azog);
        witcher.showCloseAttack(azog);
        witcher.Character_info(azog);
        if (azog.getHP() <= 0)
        {
            isOver = true;
            Sleep(1000);
            system("cls");
            cout << "Witcher won the battle!" << endl;
            GameOver();
            SaveVictory("Witcher");
            return 0;
        }
    }
    else if (witcher.isAllowedToAttack(azog))cout << azog.getName() << "(" << azog.getAppearance() << ") defended against the attack" << endl << endl;
    if (azog.isAllowedToAttack(witcher) && whoHitsFirst == 1)
    {
        azog.Attack(witcher);
        azog.showCloseAttack(witcher);
        azog.Character_info(witcher);
        isHit1 = true;
        if (witcher.getHP() <= 0)
        {
            isOver = true;
            Sleep(1000);
            system("cls");
            cout << "Azog won the battle!" << endl;
            GameOver();
            SaveVictory("Azog");
            return 0;
        }
    }
    else if (azog.isAllowedToAttack(witcher))cout << witcher.getName() << "(" << witcher.getAppearance() << ") escaped the attack" << endl << endl;
    if (isHit1 == true)witcher.toRun(azog, isHit1);
    else
    {
        dir1 = rand() % 4;
        if (witcher.inBorders(dir1))move_ch(dir1, witcher, azog);
        else move_ch_opposite(dir1, witcher, azog);
    }
    Sleep(1000);
    system("cls");
    showMap(&witcher, &azog);
    Sleep(250);
    system("cls");
    return 0;
}


int OrcVSMagician(int& whoHitsFirst, Orc& azog, Magician& vilgefortz, int& dir1, int& dir2, bool& isHit1, bool& isOver)
{
    whoHitsFirst = rand() % 2;
    showMap(&vilgefortz, &azog);
    if (azog.isOnSight(vilgefortz))azog.toPursue(vilgefortz);
    else {
        dir2 = rand() % 4;
        if (azog.inBorders(dir2))
            move_ch(dir2, azog, vilgefortz);
        else
            move_ch_opposite(dir2, azog, vilgefortz);
    }
    isHit1 = false;
    if (vilgefortz.isAllowedMagicAttack(azog))
    {
        vilgefortz.Magic_Attack(azog);
        vilgefortz.animateRemoteAttack(azog, '*');
        vilgefortz.Character_info_remote(azog);
        if (azog.getHP() <= 0)
        {
            isOver = true;
            Sleep(1000);
            system("cls");
            cout << "Vilgefortz won the battle!Last attack was remote." << endl;
            GameOver();
            SaveVictory("Vilgefortz");
            return 0;
        }
    }
    if (vilgefortz.isAllowedToAttack(azog) && whoHitsFirst == 0)
    {
        vilgefortz.Attack(azog);
        vilgefortz.showCloseAttack(azog);
        vilgefortz.Character_info(azog);
        if (azog.getHP() <= 0)
        {
            isOver = true;
            Sleep(1000);
            system("cls");
            cout << "Vilgefortz won the battle!" << endl;
            GameOver();
            SaveVictory("Vilgefortz");
            return 0;
        }
    }
    else if (vilgefortz.isAllowedToAttack(azog))cout << azog.getName() << "(" << azog.getAppearance() << ") defended against the attack" << endl << endl;
    if (azog.isAllowedToAttack(vilgefortz) && whoHitsFirst == 1)
    {
        azog.Attack(vilgefortz);
        azog.showCloseAttack(vilgefortz);
        azog.Character_info(vilgefortz);
        isHit1 = true;
        if (vilgefortz.getHP() <= 0)
        {
            isOver = true;
            Sleep(1000);
            system("cls");
            cout << "Azog won the battle!" << endl;
            GameOver();
            SaveVictory("Azog");
            return 0;
        }
    }
    else if (azog.isAllowedToAttack(vilgefortz))cout << vilgefortz.getName() << "(" << vilgefortz.getAppearance() << ") escaped the attack" << endl << endl;
    if (isHit1 == true)vilgefortz.toRun(azog, isHit1);
    else
    {
        dir1 = rand() % 4;
        if (vilgefortz.inBorders(dir1))move_ch(dir1, vilgefortz, azog);
        else move_ch_opposite(dir1, vilgefortz, azog);
    }
    Sleep(1000);
    system("cls");
    showMap(&vilgefortz, &azog);
    Sleep(250);
    system("cls");
    return 0;
}


int WarriorVSMagician(int& whoHitsFirst, Warrior& witcher, Magician& vilgefortz, int& dir1, int& dir2, bool& isHit1, bool& isOver)
{
    whoHitsFirst = rand() % 2;
    showMap(&vilgefortz, &witcher);
    if (witcher.isOnSight(vilgefortz))witcher.toPursue(vilgefortz);
    else {
        dir2 = rand() % 4;
        if (witcher.inBorders(dir2))
            move_ch(dir2, witcher, vilgefortz);
        else
            move_ch_opposite(dir2, witcher, vilgefortz);
    }
    isHit1 = false;
    if (vilgefortz.isAllowedMagicAttack(witcher))
    {
        vilgefortz.Magic_Attack(witcher);
        vilgefortz.animateRemoteAttack(witcher, '*');
        vilgefortz.Character_info_remote(witcher);
        if (witcher.getHP() <= 0)
        {
            isOver = true;
            Sleep(1000);
            system("cls");
            cout << "Vilgefortz won the battle!Last attack was remote." << endl;
            GameOver();
            SaveVictory("Vilgefortz");
            return 0;
        }
    }
    if (vilgefortz.isAllowedToAttack(witcher) && whoHitsFirst == 0)
    {
        vilgefortz.Attack(witcher);
        vilgefortz.showCloseAttack(witcher);
        vilgefortz.Character_info(witcher);
        if (witcher.getHP() <= 0)
        {
            isOver = true;
            Sleep(1000);
            system("cls");
            cout << "Vilgefortz won the battle!" << endl;
            GameOver();
            SaveVictory("Vilgefortz");
            return 0;
        }
    }
    else if (vilgefortz.isAllowedToAttack(witcher))cout << witcher.getName() << "(" << witcher.getAppearance() << ") defended against the attack" << endl << endl;
    if (witcher.isAllowedRemoteAttack(vilgefortz))
    {
        witcher.Remote_Attack(vilgefortz);
        witcher.animateRemoteAttack(vilgefortz, '.');
        witcher.Character_info_remote(vilgefortz);
        if (vilgefortz.getHP() <= 0)
        {
            isOver = true;
            Sleep(1000);
            system("cls");
            cout << "Witcher won the battle!Last attack was remote." << endl;
            GameOver();
            SaveVictory("Witcher");
            return 0;
        }
    }
    if (witcher.isAllowedToAttack(vilgefortz) && whoHitsFirst == 1)
    {
        witcher.Attack(vilgefortz);
        witcher.showCloseAttack(vilgefortz);
        witcher.Character_info(vilgefortz);
        isHit1 = true;
        if (vilgefortz.getHP() <= 0)
        {
            isOver = true;
            Sleep(1000);
            system("cls");
            cout << "Witcher won the battle!" << endl;
            GameOver();
            SaveVictory("Witcher");
            return 0;
        }
    }
    else if (witcher.isAllowedToAttack(vilgefortz))cout << vilgefortz.getName() << "(" << vilgefortz.getAppearance() << ") escaped the attack" << endl << endl;
    if (isHit1 == true)vilgefortz.toRun(witcher, isHit1);
    else
    {
        dir1 = rand() % 4;
        if (vilgefortz.inBorders(dir1))move_ch(dir1, vilgefortz, witcher);
        else move_ch_opposite(dir1, vilgefortz, witcher);
    }
    Sleep(1000);
    system("cls");
    showMap(&vilgefortz, &witcher);
    Sleep(250);
    system("cls");
    return 0;
}
int BattlePick()
{
    int input = 0;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CHOOSE BATTLE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "======================================       1.Orc versus Warrior           ============================================" << endl;
    cout << "======================================       2.Orc versus Magician          ============================================" << endl;
    cout << "======================================       3.Warrior versus Magician      ============================================" << endl;
    cout << "======================================       4.To QUIT                      ============================================" << endl;
    do
    {
        cin >> input;
    } while (input < 1 || input>4);
    return input;
}
void menu(Warrior& o1, Orc& o2, Magician& o3)
{
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~WELCOME TO CONSOLE BATTLE ARENA!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << '\a' << endl;
    cout << endl;
    Logo();
    Sleep(1000);
    system("cls");
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~HERE'S OUR HEROES:~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "1. Warrior - true professional when it comes to kill somebody." << '\n' << "He has a sharp lightweight sword that allows him to move so fast that it seems impossible for a common man." << '\n' << "He also can use his crossbow when it comes to long - range combat. " << endl << endl;
    cout << static_cast<Character&> (o1);
    cout << o1 << endl << endl;
    cout << "2.Orc - this beast was caught in mountains,it killed 5 our men and wounded 3." << '\n' << "That creature has furious anger and superhuman strenght,so it's better not to get close to this thing..." << endl << endl;
    cout << static_cast<Character&> (o2);
    cout << o2 << endl << endl;
    cout << "3.Magician - arrogance and selfishness was never man's virtue,it always leads people on a wrong path," << '\n' << "so we don't really know what led this man on the arena,maybe he wants to become famous or maybe he just likes to kill..." << '\n' << "It doesn't matter as long as he does his job..." << endl << endl;
    cout << static_cast<Character&> (o3);
    cout << o3 << endl << endl;
}
void Logo()
{
    ifstream read("Logo.txt");
    string out;
    if (!read.is_open())
    {
        cout << "Error!Couldn't open Logo.txt!" << endl;
    }
    while (getline(read, out))
    {
        cout <<"                                            " << out << endl;
    }
    read.close();
}
void GameOver()
{
    ifstream read("GameOver.txt");
    string out;
    if (!read.is_open())
    {
        cout << "Error!Couldn't open GameOver.txt!" << endl;
    }
    while (getline(read, out)) 
        {
            cout <<'\t'<< out << endl;
        }
        read.close();
}
