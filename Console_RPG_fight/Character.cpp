Character::Character(string C, int h, int d, int x, int y, string f, char ch,string w)
    : name(C), HP(h), damage(d), posX(x), posY(y), feature(f), appearance(ch),weapon(w) {
}

void Character::move(int dx, int dy,Character& o)  {
    if (isOccupied(posY + dy, posX + dx, o))
    {
        int ddx = -dx;
        int ddy = -dy;
        int newX = posX + ddx;
        int newY = posY + ddy;
        if (MAP[newY][newX] != '#')
        {
            posX = newX; posY = newY;
        }
        else
        {
            posX += 0;
            posY += 0;
        }
    }
    else
    {
        posX += dx; posY += dy;
    }
}

bool Character::inBorders(int d) const { 
    int newX = posX;
    int newY = posY;

    switch (d) {
    case UP:    newY--; break;
    case DOWN:  newY++; break;
    case LEFT:  newX--; break;
    case RIGHT: newX++; break;
    default: return false;
    }

    // Проверка выхода за границы карты
    if (newX < 1 || newX >= WIDTH-1 || newY < 1 || newY >= HEIGHT-1)
        return false;

    // Проверка стены 
    if (MAP[newY][newX] == '#') return false;

    return true;
}

bool Character::isOccupied(int y, int x,Character& o) const
{

    return o.getPosY() == y&&o.getPosX()==x;
}
void Character::toRun(Character& o, bool isUnderAttack)
{
    if (!isUnderAttack) return;          // убегаем только после получения удара

    int x_enemy = o.getPosX();
    int y_enemy = o.getPosY();
    int x_me = posX;
    int y_me = posY;

    // Направление ОТ врага
    int dx = 0, dy = 0;
    if (x_me < x_enemy) dx = -1;         // враг справа - бежим влево
    else if (x_me > x_enemy) dx = 1;     // враг слева – бежим вправо

    if (dx == 0)
    {
        if (y_me < y_enemy) dy = -1;         // враг снизу – бежим вверх
        else if (y_me > y_enemy) dy = 1;     // враг сверху – бежим вниз
    }
    int newX = x_me + dx;
    int newY = y_me + dy;

    // Функция проверки проходимости (стены + границы)
    auto isWalkable = [](int x, int y) -> bool {
        return (x >= 1 && x < WIDTH - 1 && y >= 1 && y < HEIGHT - 1 && MAP[y][x] != '#');
        };

    if (isWalkable(newX, newY)) {
        move(dx, dy, o);
        return;
    }
}

void Character::toPursue(Character& o)
{
    int x_enemy = o.getPosX();
    int y_enemy = o.getPosY();
    int x_me = posX;
    int y_me = posY;

    int dist = sqrt(pow(x_enemy - x_me, 2) + pow(y_enemy - y_me, 2));
    if (dist <= 1) return;              // уже рядом – атакуем в основном цикле

    // Направление к врагу
    int dx = 0, dy = 0;
    if (x_me < x_enemy) dx = 1;
    else if (x_me > x_enemy) dx = -1;

    if (dx == 0)
    {
        if (y_me < y_enemy) dy = 1;
        else if (y_me > y_enemy) dy = -1;
    }

    int newX = x_me + dx;
    int newY = y_me + dy;

    // Проверка на стены
    bool walkable = (newX >= 1 && newX < WIDTH - 1 && newY >= 1 && newY < HEIGHT - 1 && MAP[newY][newX] != '#');
    // Запрещаем занимать клетку врага
    if (walkable && (newX != x_enemy || newY != y_enemy))
        move(dx, dy, o);
}

void Character::showCloseAttack(Character& o) const
{
    system("cls");
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == posY && j == posX)
            {
                cout << getAppearance();
            }
            else if (i == o.getPosY() && j == o.getPosX())
            {
                cout << 'X';
            }
            else cout << MAP[i][j];
        }
        cout << endl;
    }
}

void Character::animateRemoteAttack(Character& o, char symb)
{
    system("cls");
    int x_target = o.getPosX();
    int y_target = o.getPosY();
    int dx = (x_target > posX) ? 1 : (x_target < posX) ? -1 : 0;
    int dy = (y_target > posY) ? 1 : (y_target < posY) ? -1 : 0;
    double realDistance = sqrt(dx * dx + dy * dy);
    int steps = int(realDistance);
    for (int i = 0; i <= steps; i++)
    {
        int cx = posX + dx * i, cy = posY + dy * i;
        showRemoteAttack(o, cx, cy, symb);
        Sleep(100);
        system("cls");
    }
    showCloseAttack(o);
    Sleep(100);
}

void Character::showRemoteAttack(Character& o, int x, int y, char& symb)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == posY && j == posX)
            {
                cout << getAppearance();
            }
            else if (i == o.getPosY() && j == o.getPosX())
            {
                cout << o.getAppearance();
            }
            else if (i == y && j == x)cout << symb;
            else cout << MAP[i][j];
        }
        cout << endl;
    }
}

ostream& operator<<(ostream& os, Character& o)
{
    os << "Name of fighter:                     " <<right<< o.getName() << endl;
    os << "Feature:                             " << right<< o.getFeature() << endl;
    os << "Display:                             " << right<< o.getAppearance() << endl;
    os << "HP:                                  " << right << o.getHP() << endl;
    os << "Weapon:                              " << right<< o.getWeapon() << endl;
    os << "Damage(DMG):                         " << right<< o.getDamage() << endl;
    cout << "Curent position on the arean(x,y):  (" << right << o.getPosX() << "," << o.getPosY() << ")" << endl;
    return os;
}
bool Character::isAllowedToAttack(Character& o)const
{
    int x_enemy = o.getPosX();
    int y_enemy = o.getPosY();
    int x_me = posX;
    int y_me = posY;
    double distance = sqrt(pow(x_me - x_enemy, 2) + pow(y_me - y_enemy, 2));
    return distance <= 1.5;
}
