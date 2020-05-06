#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <math.h>
#include <numeric>


class Warrior {
private:
    std::string name;
    int health;
    int power;
    int block;
public:
    std::string GetName() {return name;}
    void SetName(std::string name) {this->name = name;}
    int GetHealth(){return health;}
    void SetHealth(int health) {this->health = health;}
    int GetPower(){return power;}
    void SetPower(int power){this->power = power;}
    int GetBlock(){return block;}
    void SetBlock(int block) {this->block = block;}
    
    int Attack() {
        return std::rand() % this->power;
    }
    int Block() {
        return std::rand() % this->block;
    }
    Warrior(std::string, int, int, int);
    Warrior();
    ~Warrior();
    void ToString(); 
};

Warrior::Warrior(std::string name, int health, int power, int block) {
    this->block = block;
    this->health = health;
    this->name = name;
    this->power = power;
}

Warrior::Warrior() {
    this->block = 0;
    this->health = 0;
    this->name = "";
    this->power = 0;
}

Warrior::~Warrior() {
    std::cout << "Warrior " << this->name << " destroyed\n";
}

class Battle {
public:
    static void StartFight(Warrior& player1, Warrior& player2) {
        while(true) {
            if(Battle::GetAttackResult(player1, player2).compare("Game Over") == 0) {
                std::cout << "Game Over\n";
                break;
            }
            if(Battle::GetAttackResult(player2, player1).compare("Game Over") == 0) {
                std::cout << "Game Over\n";
                break;
            }
        }
    }
    static std::string GetAttackResult(Warrior& player1, Warrior& player2) {
        int player1Attack = player1.Attack();
        int player2Block = player2.Block();
        int damage2Player2 = ceil(player1Attack - player2Block);
        damage2Player2 = (damage2Player2 <= 0) ? 0 : damage2Player2;
        player2.SetHealth(player2.GetHealth() - damage2Player2);

        printf("%s attacks %s and deals %d damage\n", player1.GetName().c_str(), player2.GetName().c_str(), damage2Player2);
        printf("%s is down to %d health\n", player2.GetName().c_str(), player2.GetHealth());

        if(player2.GetHealth() <= 0) {
            printf("%s has died and %s is Victorious\n", player2.GetName().c_str(), player1.GetName().c_str());
            return "Game Over";
        } else {
            return "Fight Again";
        }
    }
};

int main() { 
    srand(time(NULL));
    Warrior thor("Thor", 100, 30, 15); //health, power, block ability
    Warrior hulk("Hulk", 135, 25, 10);
    Battle::StartFight(thor, hulk);
    return 0;
}