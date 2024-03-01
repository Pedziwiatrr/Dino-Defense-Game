#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>
#include <math.h>
#include<vector>
#include<string>
#include <SFML/Audio.hpp>

#include<iostream>

using namespace sf;

bool keyHold = false;

Texture arrowTex;

class Arrow
{
private:
    Vector2f velocity;
    int speed;

public:
    Sprite arrow;

    Arrow(Texture &arrowTex) : velocity(0.f, 0.f), speed(50)
    {
        if (!arrowTex.loadFromFile("..\\Tekstury\\strza³a1.png"))
            std::cout << "Error:Tekstura strza³y :(";
        this->arrow.setTexture(arrowTex);
        this->arrow.setScale(0.5f, 0.5f);

    };

    Vector2f getVelocity()
    {
        return velocity;
    }

    int getSpeed()
    {
        return speed;
    }

    void setVelocity(Vector2f newVelocity)
    {
        velocity = newVelocity;
    }

    void setSpeed(int newSpeed)
    {
        speed = newSpeed;
    }

    void update()
    {
        arrow.move(velocity);
    }

};
std::vector<Arrow> arrows;

Texture cavemanTex;
Texture balistaTex;
Texture bonesTex;
Texture dmgTex;
Texture reloadTex;

class Player
{
    int maxHp;
    int hp;
    int dmg;
    int attackSpeed;
    float income;
    int bones;
    
public:
    Sprite caveman;
    Sprite balista;
    RectangleShape hpBar;

    Sprite bonesSprite;
    Sprite dmgSprite;
    Sprite reloadSprite;

    // Konstruktor
    Player(RenderWindow& window, Texture& cavemanTex, Texture& balistaTex) : hp(100), dmg(5), attackSpeed(180), income(3), maxHp(100), bones(0)
    {
        if (!cavemanTex.loadFromFile("..\\Tekstury\\Jaskiniowiec3.png"))
            std::cout << "Error: Tekstura jaskiniowca :( \n";
        this->caveman.setTexture(cavemanTex);
        this->caveman.setScale(0.3f, 0.3f);
        this->caveman.setPosition(window.getSize().x * 0, window.getSize().y * 0.68f);

        if (!balistaTex.loadFromFile("..\\Tekstury\\Balista1.png"))
            std::cout << "Error: Tekstura balisty :( \n";
        this->balista.setTexture(balistaTex);
        this->balista.setScale(0.5f, 0.5f);
        this->balista.setPosition(window.getSize().x * 0.07f, window.getSize().y * 0.5f);

        if (!bonesTex.loadFromFile("..\\Tekstury\\kosc1.png"))
            std::cout << "Error: Tekstura koœci :( \n";
        this->bonesSprite.setTexture(bonesTex);
        this->bonesSprite.setScale(0.3f, 0.3f);
        this->bonesSprite.setPosition(0, window.getSize().y * 1/6);

        if (!bonesTex.loadFromFile("..\\Tekstury\\kosc1.png"))
            std::cout << "Error: Tekstura koœci :( \n";
        this->bonesSprite.setTexture(bonesTex);
        this->bonesSprite.setScale(0.3f, 0.3f);
        this->bonesSprite.setPosition(0, window.getSize().y * 1 / 6);

        if (!dmgTex.loadFromFile("..\\Tekstury\\sword1.png"))
            std::cout << "Error: Tekstura luku :( \n";
        this->dmgSprite.setTexture(dmgTex);
        this->dmgSprite.setScale(0.3f, 0.3f);
        this->dmgSprite.setPosition(0, window.getSize().y * 1 / 6 + bonesSprite.getGlobalBounds().height * 1.f);
        this->dmgSprite.setScale(0.06f, 0.06f);

        if (!reloadTex.loadFromFile("..\\Tekstury\\reload1.png"))
            std::cout << "Error: Tekstura reload :( \n";
        this->reloadSprite.setTexture(reloadTex);
        this->reloadSprite.setScale(0.3f, 0.3f);
        this->reloadSprite.setPosition(20, window.getSize().y * 1 / 6 + bonesSprite.getGlobalBounds().height * 1.f + dmgSprite.getGlobalBounds().height);
        this->reloadSprite.setScale(0.06f, 0.06f);

    }
    void labelUpdate(RenderWindow &window, Font& font)
    {
        Text bonesText;
        bonesText.setFont(font);
        bonesText.setString(std::to_string(bones));
        bonesText.setOutlineColor(Color::Black);
        bonesText.setOutlineThickness(2.f);
        bonesText.setPosition(bonesSprite.getPosition().x + 100, bonesSprite.getPosition().y);

        Text dmgText;
        dmgText.setFont(font);
        dmgText.setString(std::to_string(dmg));
        dmgText.setOutlineColor(Color::Black);
        dmgText.setOutlineThickness(2.f);
        dmgText.setPosition(bonesSprite.getPosition().x + 100, dmgSprite.getPosition().y + dmgSprite.getGlobalBounds().height / 3);

        Text reloadText;
        reloadText.setFont(font);
        float attacksPerSec = getAttackSpeed() / 60;
        reloadText.setString(std::to_string(getAttackSpeed()));
        reloadText.setOutlineColor(Color::Black);
        reloadText.setOutlineThickness(2.f);
        reloadText.setPosition(reloadSprite.getPosition().x + 80, reloadSprite.getPosition().y + reloadSprite.getGlobalBounds().height / 3);

        window.draw(bonesText);
        window.draw(dmgText);
        window.draw(reloadText);

        
    }

    void hpBarUpdate(RenderWindow&window, Font &font)
    {
        hpBar.setFillColor(Color::Red);
        hpBar.setSize(Vector2f(float(hp * 2), 30.f));
        hpBar.setPosition(150, window.getSize().y - 40);
        hpBar.setOutlineThickness(5.f);
        hpBar.setOutlineColor(Color::Black);

        Text hpText;
        hpText.setFillColor(Color::Red);
        hpText.setOutlineThickness(4);
        hpText.setFont(font);
        hpText.setPosition(hpBar.getPosition().x + hpBar.getGlobalBounds().width, hpBar.getPosition().y - 10);
        hpText.setString(std::to_string(hp));

        window.draw(hpText);
    }
    
    int getMaxHp()
    {
        return maxHp;
    }

    void setMaxHp(int newMaxHp)
    {
        maxHp = newMaxHp;
    }

    float getIncome()
    {
        return income;
    }

    void setIncome(float newIncome)
    {
        income = newIncome;
    }

    int getBones()
    {
        return bones;
    }

    void setBones(int newBones)
    {
        bones = newBones;
    }

    int getAttackSpeed()
    {
        return attackSpeed;
    }

    void setAttackSpeed(int newAttackSpeed)
    {
        attackSpeed = newAttackSpeed;
    }

    void upgradeAttackSpeed(int bonusAttackSpeed)
    {
        attackSpeed -= bonusAttackSpeed;
    }

    void upgradeIncome(int bonusIncome)
    {
        income += bonusIncome;
    }
    

    int getHp()
    {
        return hp;
    }

    void setHp(int newHp)
    {
        hp = newHp;
    }

    void upgradeHp(int bonusHp)
    {
        maxHp += bonusHp;
    }

    int getDmg()
    {
        return dmg;
    }

    void setDmg(int newDmg)
    {
        dmg = newDmg;
    }

    void upgradeDmg(int bonusDmg)
    {
        dmg += bonusDmg;
    }
};

Texture dinoTexRap;
Texture dinoTexPter;
Texture dinoTexRex;
Texture dinoTexIndominus;

class Dino;
std::vector<Dino> dinos;

class Dino
{
    int hp;
    int dmg;
    float speed;
    int bounty;
    String species;
    
public:
    Sprite dino;
    RectangleShape hpBar;

    Dino(RenderWindow& window, String species, float hpMult, float dmgMult) :  species(species)
    {
        if (species == "raptor")
        {
            if (!dinoTexRap.loadFromFile("..\\Tekstury\\raptor1.png"))
                std::cout << "Error: Tekstura raptora :( \n";
            setHp(15*hpMult);
            setSpeed(2);
            setDmg(15*dmgMult);
            this->dino.setTexture(dinoTexRap);
            this->dino.setScale(0.7f, 0.7f);
            dino.setPosition(window.getSize().x, window.getSize().y - dino.getGlobalBounds().height);
        }

        if (species == "pterodaktyl")
        {
            if (!dinoTexPter.loadFromFile("..\\Tekstury\\pterodaktyl1.png"))
                std::cout << "Error: Tekstura pterodaktyla :( \n";
            setHp(5*hpMult);
            setSpeed(4);
            setDmg(10*dmgMult);
            this->dino.setTexture(dinoTexPter);
            dino.setPosition(window.getSize().x, window.getSize().y / 4 );
            dino.setScale(0.3f, 0.3f);
        }
        if (species == "trex")
        {
            if (!dinoTexRex.loadFromFile("..\\Tekstury\\trex1.png"))
                std::cout << "Error: Tekstura trexa :( \n";
            setHp(50*hpMult);
            setSpeed(0.5f);
            setDmg(50*dmgMult);
            this->dino.setTexture(dinoTexRex);
            dino.setScale(1.5f, 1.5f);
            dino.setPosition(window.getSize().x, window.getSize().y - dino.getGlobalBounds().height);
        }
        if (species == "indominus")
        {
            if (!dinoTexIndominus.loadFromFile("..\\Tekstury\\indominusRex.png"))
                std::cout << "Error: Tekstura indominusa :( \n";
            setHp(300 * hpMult);
            setSpeed(0.2f);
            setDmg(999 * dmgMult);
            this->dino.setTexture(dinoTexIndominus);
            dino.setScale(1.5f, 1.5f);
            dino.setPosition(window.getSize().x, window.getSize().y - dino.getGlobalBounds().height);
        }


       
    }

    void hpBarUpdate(RenderWindow& window, Font& font)
    {
        hpBar.setFillColor(Color::Magenta);
        if (hp < 150)
        {
            hpBar.setSize(Vector2f(float(hp * 5), 20.f));
        }
        else
            hpBar.setSize(Vector2f(float(150 * 5), 20.f));
        hpBar.setPosition(dino.getPosition().x, dino.getPosition().y - 50.f);
        hpBar.setOutlineThickness(2.f);
        hpBar.setOutlineColor(Color::Black);

        Text hpText;
        hpText.setFillColor(Color::Magenta);
        hpText.setOutlineThickness(4);
        hpText.setFont(font);
        hpText.setPosition(hpBar.getPosition().x + hpBar.getGlobalBounds().width, hpBar.getPosition().y - 10);
        hpText.setString(std::to_string(hp));

        window.draw(hpText);
    }

    int getHp()
    {
        return hp;
    }
    
    void setHp(int newHp)
    {
        hp = newHp;
    }
    
    int getDmg()
    {
        return dmg;
    }
    
    void setDmg(int newDmg)
    {
        dmg = newDmg;
    }

    float getSpeed()
    {
        return speed;
    }

    void setSpeed(float newSpeed)
    {
        speed = newSpeed;
    }

    String getSpecies()
    {
        return species;
    }

};

class Background
{
public:
    Sprite background;
    Texture backgroundTex;
    
    Background()
    {
        if (!backgroundTex.loadFromFile("..\\Tekstury\\tlo2.png"))
            std::cout << "Error:Tekstura tla :(";
        this->background.setTexture(backgroundTex);
        this->background.setScale(0.9f, 0.9f);
    }
};

Texture boardTex;
class Board;
std::vector<Board> boards;

String dmgBoardText = "tekst dmg";
String reloadSpeedBoardText = "tekst reload";
String hpBoardText = "tekst hp";
String incomeBoardText = "tekst income";

class Board
{
    String text;
    Text boardText;
    String stat;
    int level = 1;
    int cost = 30;
    Keyboard::Key bind;
    Vector2f position;

public:
    Sprite board;

    Board(RenderWindow& window, Font&font, Player&player, Vector2f position, int size, String text, Keyboard::Key bind, String stat)
        : bind(bind), stat(stat), text(text), cost(30)
    {
        if (!boardTex.loadFromFile("..\\Tekstury\\pustaTabliczka2.png"))
            std::cout << "Error: Tekstura tabliczki :(" << std:: endl;

        this->board.setTexture(boardTex);
        this->board.setScale(0.6f, 0.6f);
        this->board.setPosition(position);

        boardText.setFont(font);
        boardText.setString(text);
        boardText.setCharacterSize(size);
        boardText.setFillColor(Color::White);
        boardText.setPosition(board.getPosition().x + 50.f, board.getPosition().y + 50.f);
        boardText.setOutlineThickness(2.f);
        boardText.setOutlineColor(Color::Black);

    }

    void checkBoardInput(Player &player)
    {   

        cost = (30*level);

        if (Keyboard::isKeyPressed(bind))
        {
            keyHold = true;
            std::cout << "Klikniêto tabliczke: " << text.toAnsiString() << std::endl;
            if (player.getBones() >= getCost())
            {
                if (stat == "dmg")
                {
                    player.upgradeDmg(2 + level);
                    level++;
                }
                if (stat == "attackSpeed")
                {
                    player.upgradeAttackSpeed(60/(level));
                    level++;
                    std::cout << player.getAttackSpeed() << std::endl;
                }
                if (stat == "hp")
                {
                    player.upgradeHp(20 + 10 * level);
                    level++;
                }
                if (stat == "bones")
                {
                    player.upgradeIncome(level - (level - 1) * 0.5);
                    level++;
                }
                int newBones = player.getBones() - getCost();
                player.setBones(newBones);
            }
        }
    }

    String getStat()
    {
        return stat;
    }

    void setStat(String newStat)
    {
        stat = newStat;
    }

    Text getText()
    {
        return boardText;
    }

    void setText(String& newText, Font font, float size)
    {
        boardText.setString(newText);
        boardText.setFont(font);
        boardText.setCharacterSize(size);
        boardText.setFillColor(Color::White);
        boardText.setPosition(board.getPosition().x + 50.f, board.getPosition().y + 50.f);
        boardText.setOutlineThickness(3.f);
        boardText.setOutlineColor(Color::Black);
    }

    int getLevel()
    {
        return level;
    }

    void setLevel(int newLevel)
    {
        level = newLevel;
    }

    void upLevel()
    {
        level++;
    }

    int getCost()
    {
        return cost;
    }
    void setCost(int newCost)
    {
        cost = newCost;
    }
    
    Vector2f getPos()
    {
        return position;
    }
};

class Info
{
public:
    int cost;
    int upgradeAmount;
    Text info;
    int level;

    Info(Board& board, Font& font)
    {
        cost = board.getCost();
        level = board.getLevel();

        info.setFont(font);

        String costText = std::to_string(cost);
        if (board.getStat() == "dmg")
            upgradeAmount = 2 + board.getLevel();
        if (board.getStat() == "hp")
            upgradeAmount = 20 + 10 * board.getLevel();
        if (board.getStat() == "attackSpeed")
            upgradeAmount = 30 / board.getLevel();
        if (board.getStat() == "bones")
            upgradeAmount = board.getLevel() - (board.getLevel()  - 1) * 0.5;

        String upgradeAmountText = std::to_string(upgradeAmount);

        String infoText = "Koszt: " + costText + " (+" + upgradeAmountText + ")";

        if (board.getStat() != "pauza")
        {
            info.setString(infoText);
            info.setPosition(board.board.getPosition().x, board.board.getPosition().y + 150);
            info.setOutlineColor(Color::Black);
            info.setOutlineThickness(4.f);
        }

    }
    
    void updateBoards(Board&board)
    {
        cost = board.getCost();
        level = board.getLevel();
    }
};

Vector2f divideVectorByScalar(Vector2f& vector, float scalar)
{
    return Vector2f(vector.x / scalar, vector.y / scalar);
}

// Czas
int reloadFrames = 0;
bool readyToShoot = false;

bool reloaded(RectangleShape& reloadBar, Player& player)
{
    reloadBar.setPosition(player.balista.getPosition().x, player.balista.getPosition().y - 50);
    float reloadPercentage = 0;

    if (reloadFrames < player.getAttackSpeed() && !readyToShoot)
    {
        reloadFrames++;
        reloadBar.setFillColor(Color::Yellow);
        reloadBar.setOutlineColor(Color::Black);
        reloadBar.setOutlineThickness(5);
        reloadPercentage = static_cast<float>(reloadFrames) / player.getAttackSpeed();

    }
    else
    {
        readyToShoot = true;
        reloadFrames = 0;
        reloadBar.setFillColor(Color::Green);
        reloadPercentage = 1.f;
    }
    reloadBar.setSize(Vector2f(reloadPercentage*200.f, 20.f));

    return readyToShoot;
}

void IncomeTick(Player& player)
{
    int bones = player.getBones();
    player.setBones(bones + player.getIncome());
}

void hpRegenTick(Player& player)
{   
    float maxHpPercentage = player.getMaxHp() / 100;

    if (player.getHp() < player.getMaxHp() - maxHpPercentage)
    {
        player.setHp(player.getHp() + maxHpPercentage);
    }
    else if (player.getHp() < player.getMaxHp())
    {
        player.setHp(player.getMaxHp());
    }

}

int frameCounter = 0;
int s = 0;


int timer(Player &player)
{   
    if (frameCounter < 60)
        frameCounter++;
    else
    {
        frameCounter = 0;
        s++;
        IncomeTick(player);
        hpRegenTick(player);

     
    }
    return s;


}



// Move dino
void moveDinos()
{
    for (size_t i = 0; i < dinos.size(); i++)
    {
        dinos[i].dino.move(-dinos[i].getSpeed(), 0);
    }
}

int dinoTimer = 5;
float hpMultiplier = 1;
float dmgMultiplier = 1;

void spawnDinos(RenderWindow &window, int frameCounter)
{
    if (frameCounter == 60)
    {
        dinoTimer++;
        
        if (dinoTimer % 8 == 0 && dinoTimer != 0)
            hpMultiplier += 0.06;
            dmgMultiplier += 0.01;
        if (dinoTimer % 10 == 0 && dinoTimer != 0)
        {
            Dino raptor(window, "raptor", hpMultiplier, dmgMultiplier);
            dinos.push_back(raptor);
        }
        if (dinoTimer % 14 == 0 && dinoTimer != 0)
        {
            Dino ptero(window, "pterodaktyl", hpMultiplier, dmgMultiplier);
            dinos.push_back(ptero);
        }
        if (dinoTimer % 50 == 0 && dinoTimer != 0)
        {   
            std::cout << "trex" << std::endl;
            Dino trex(window, "trex", hpMultiplier, dmgMultiplier);
            dinos.push_back(trex);
        }
        if (dinoTimer % 190 == 0 && dinoTimer != 0)
        {
            std::cout << "indominus" << std::endl;
            Dino indominus(window, "indominus", hpMultiplier, dmgMultiplier);
            dinos.push_back(indominus);

        }
    }
    
}

int count = 0;


int main()
{
    RenderWindow window(VideoMode(1600, 900), "Dino Defense!");
    window.setFramerateLimit(60);
    
    Vector2f mousePos;
    Vector2f aimDir;
    Vector2f aimDirNorm;

    Music music;
    if (!music.openFromFile("..\\Tekstury\\ageOfWar.mp3"))
        std::cout << "Error: muzyka age of war :(";

    Font font;
    if(!font.loadFromFile("..\\Tekstury\\StoneAge-OV4AO.ttf"))
    {
        std::cout << "Error: Czcionka :((";
    }

    Background background;
    Player player(window, cavemanTex, balistaTex);
    RectangleShape reloadBar;

    String dmgBoardText = "Ulepsz \n Obrazenia [ D ]";
    String reloadSpeedBoardText = "Ulepsz \n Szybkostrzelnosc [ F ]";
    String hpBoardText = "Ulepsz \n Zdrowie [ H ]";
    String incomeBoardText = "Ulepsz \n Dochod [ G ]";

    Vector2f boardPos1(0.f, 0.f);
    Board pauseBoard(window, font, player, boardPos1, 30.f, "Pauza [ESC]", Keyboard::Escape, "pauza");
    boards.push_back(pauseBoard);

    Vector2f boardPos2(300.f, 0.f);
    Board upgradeDmgBoard(window, font, player, boardPos2, 20.f, dmgBoardText, Keyboard::D, "dmg");
    boards.push_back(upgradeDmgBoard);

    Vector2f boardPos3(600.f, 0.f);
    Board upgradeReloadSpeed(window, font, player, boardPos3, 15.f, reloadSpeedBoardText, Keyboard::F, "attackSpeed");
    boards.push_back(upgradeReloadSpeed);

    Vector2f boardPos4(900.f, 0.f);
    Board upgradeHp(window, font, player, boardPos4, 20.f, hpBoardText, Keyboard::H, "hp");
    boards.push_back(upgradeHp);

    Vector2f boardPos5(1200.f, 0.f);
    Board upgradeIncome(window, font, player, boardPos5, 20.f, incomeBoardText, Keyboard::G, "bones");
    boards.push_back(upgradeIncome);

    music.play();

    bool paused = false;

    while (window.isOpen() && player.getHp() > 0)
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                paused = !paused;
            if (event.type == sf::Event::KeyReleased)
                keyHold = false;
        }

        // Aktualizacja
        if (!paused)
        {
            int time = timer(player);


            dmgBoardText = "Ulepsz \n Obrazenia [ D ] \nKoszt: " + std::to_string(upgradeDmgBoard.getCost());
            reloadSpeedBoardText = "Ulepsz \n Szybkostrzelnosc [ F ] \nKoszt: " + std::to_string(upgradeReloadSpeed.getCost());
            hpBoardText = "Ulepsz \n Zdrowie [ H ] \nKoszt: " + std::to_string(upgradeHp.getCost());
            incomeBoardText = "Ulepsz \n Dochod [ G ] \nKoszt: " + std::to_string(upgradeIncome.getCost());

            upgradeDmgBoard.setText(dmgBoardText, font, 20.f);
            upgradeReloadSpeed.setText(reloadSpeedBoardText, font, 15.f);
            upgradeHp.setText(hpBoardText, font, 20.f);
            upgradeIncome.setText(incomeBoardText, font, 20.f);

     

            mousePos = Vector2f(Mouse::getPosition(window));
            aimDir = mousePos - player.balista.getPosition();
            aimDirNorm = divideVectorByScalar(aimDir, sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));


            // Strzelanie
            if (!readyToShoot)
                readyToShoot = reloaded(reloadBar, player);

            if (Mouse::isButtonPressed(Mouse::Left) and readyToShoot)
            {
                readyToShoot = false;

                Arrow arrow1(arrowTex);
                arrow1.arrow.setPosition(window.getSize().x * 0.2f, window.getSize().y * 0.55f);
                int arrowSpeed = arrow1.getSpeed();
                arrow1.setVelocity(aimDirNorm * float(arrowSpeed));

                // Ustawienie pozycji strza³y na pozycji myszy

                arrows.push_back(arrow1);
            }

            // Dinozaury
            spawnDinos(window, frameCounter);
            moveDinos();

            // Wyœwietlanie
            window.clear();

            window.draw(background.background);

            window.draw(player.balista);
            window.draw(player.caveman);

            for (size_t i = 0; i < dinos.size(); i++)
            {
                window.draw(dinos[i].dino);
                dinos[i].hpBarUpdate(window, font);
                window.draw(dinos[i].hpBar);

                if (player.caveman.getGlobalBounds().intersects(dinos[i].dino.getGlobalBounds()) || dinos[i].dino.getPosition().x < 0)
                {
                    int playerHp = player.getHp();
                    int newPlayerHp = player.getHp() - dinos[i].getDmg();
                    player.setHp(newPlayerHp);
                    std::cout << "HP: " << player.getHp() << std::endl;
                    dinos.erase(dinos.begin() + i);
                }
            }

            for (size_t i = 0; i < arrows.size(); i++)
            {
                arrows[i].update();
                window.draw(arrows[i].arrow);

                for (size_t j = 0; j < dinos.size(); j++)
                {
                    if (arrows[i].arrow.getGlobalBounds().intersects(dinos[j].dino.getGlobalBounds()))
                    {
                        int dinoHp = dinos[j].getHp();
                        int newHp = dinoHp - player.getDmg();
                        dinos[j].setHp(newHp);

                        if (dinos[j].getHp() <= 0)
                        {
                            dinos.erase(dinos.begin() + j);
                        }
                        arrows.erase(arrows.begin() + i);
                        i--;
                    }
                }
            }


            for (size_t i = 0; i < boards.size(); i++)
            {
                window.draw(boards[i].board);
                window.draw(boards[i].getText());
                if(!keyHold)
                boards[i].checkBoardInput(player);
                Info info(boards[i], font);
                info.updateBoards(boards[i]);
                window.draw(info.info);
            }

            if (count < 60)
                count++;
            else
            {
                count = 0;
                std::cout << std::endl << "Czas gry: " << s << "s\n";
                std::cout << "Strza³y w akcji: " << arrows.size() << std::endl;
                std::cout << "Dinosy w akcji: " << dinos.size() << std::endl;
            }


            window.draw(reloadBar);
            player.hpBarUpdate(window, font);
            window.draw(player.hpBar);
            window.draw(player.bonesSprite);
            window.draw(player.dmgSprite);
            window.draw(player.reloadSprite);

            player.labelUpdate(window, font);

            window.display();
        }
        else
        {
            Text pauseText;
            pauseText.setFont(font);
            pauseText.setFillColor(Color::White);
            pauseText.setPosition(window.getSize().x/2 - 300, window.getSize().y / 2 - pauseText.getGlobalBounds().height / 2);
            pauseText.setOutlineColor(Color::Black);
            pauseText.setOutlineThickness(10);
            pauseText.setCharacterSize(150);
            pauseText.setString("PAUZA II");
                

            window.draw(pauseText);
            window.display();
            }
    }

    return 0;
}
