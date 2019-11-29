#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <windows.h>
#include <ctime>
#include <vector>
#include <sstream>

using namespace std;

class Gracz;
class Enemy;

struct options
{
    int option_num;
    int lvl=0;
    int number_of_enemy;
    int dead_enemy=0;
    sf::Clock time_All;
    int range_hp[2];
    int range_damage[2];
    int range_speed[2];

};

class Enemy
{
public:
    sf::Sprite player;
    int speed;
    int HP, HP_MAX;
    bool attack=false, dead=false;
    int damage;
    sf::Clock c_hit;
    int y;
    int value=10;

    //zmienne do sterowania grafik¹
    int pixele_p[5]={0,74,153,250,350}, pixele_s[5]={74,79,97,100,116};
    int dead_f=0;
    int t_x=0, t_y=0;
    //---------------------------

    Enemy(int hp=0, int d=0, int s=0);
    void ruch(sf::RenderWindow &window);
    void rysuj(sf::RenderWindow &window);
    void hit(Gracz &g, sf::RenderWindow &window);
};

class Gracz
{
public:
    struct ammo_state
    {
        bool fired;     // 1-wystrzelony
        sf::Sprite ammo;
    };
    struct money
    {
        sf::Texture tCoin;
        sf::Sprite coin;
        sf::Font font;
        sf::Text coin_numT;
        int coin_num=500;
    };
    struct items
    {
        bool lock=1;
        sf::Texture textura;
        sf::Sprite item;
        sf::Text t1;
        int num=0, price;
        sf::Vector2i xy_gra, xy_menu;
    };
    int x_sammo, x_rammo; //położenie sprita pocisków(stanu)

    items item[4];
    sf::Font f;
    money cash;
    enum Guns {shotgun, rifle};
    Guns active_gun=shotgun;

    sf::Clock stading, immortal_c, immortal_c2;
    bool immortal_b=false;
    int immortal_l;
    sf::Text immortal_t;

    vector <ammo_state> ammo_shotgun;
    vector <ammo_state> ammo_rifle;
    int ammo_num, mag_num=30;

    bool s_action=false, reload=false;



    sf::Texture pTexture, sTexture, rTexture, rifle_ammoTexture, hpTexture;
    sf::Sprite gracz, strzal, shot_rifle, hp_view;
    sf::SoundBuffer sb1[2], sb2[2];
    sf::Sound shotgun_shot, shotgun_reload, rifle_shot, rifle_reload;
    int damage=5;

    int p_hp=313, HP; //szerokość paska HP
    float HP_MAX;


    Gracz(int hp, int ammo_numb);

    void hit(vector <Enemy> &enemy, sf::RenderWindow &window);
    void shotf(sf::RenderWindow &window, sf::Event &event);
    void reloadf(sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);
    void update_menu(sf::RenderWindow &window);


};

class Tlo
{
    sf::Sprite background;
    sf::Texture texture2;
public:


    Tlo(string a)
    {
        texture2 .loadFromFile("x/background/"+a+".jpg");
        background.setTexture(texture2);
    }

    void rysuj(sf::RenderWindow &window)
    {
        window.draw(background);
    }

};

void load_textures();
void menu(options &op,sf::RenderWindow &oknoMenu);
void level(options &op, sf::RenderWindow &oknoLevel, vector <Enemy> &en, Gracz &g);
void game_over(sf::RenderWindow &oknoOver, options &o);
void rysuj_ekran(sf::RenderWindow &window, sf::Sprite &freeman, sf::Sprite &tlo, int op, int xs=0, int ys=0);
bool napis(string str, sf::RenderWindow &window, sf::Sprite &freeman);
bool podejdz(int x, sf::Sprite &freeman);
void help(sf::RenderWindow &window);
void ranking(sf::RenderWindow &window, int op, options &o);

