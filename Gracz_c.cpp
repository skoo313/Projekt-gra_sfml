#include "objects.h"

using namespace std;

Gracz::Gracz(int hp, int ammo_numb)
{   ostringstream ss;
    f.loadFromFile("x/font.ttf");

    item[0].t1.setFont(f);
    item[0].t1.setCharacterSize(50);
    item[0].t1.setColor(sf::Color::White);
    item[0].textura.loadFromFile("x/cartman/update/cp.png");
    item[0].item.setTexture(item[0].textura);
    item[0].item.setScale(.3f,.3f);
    item[0].price=50;

    item[1].price=75;
    item[1].textura.loadFromFile("x/cartman/update/te.png");
    item[1].item.setTexture(item[1].textura);
    item[1].item.setScale(.25f,.25f);

    item[2].price=300;
    item[3].price=100;
    //ustawienia tekstu dla wszystkich elementów
    item[3].t1=item[2].t1=item[1].t1=immortal_t=item[0].t1;
    immortal_t.setPosition(600,120);

    pTexture.loadFromFile("x/cartman/cartman_ok.png");
    gracz.setTexture(pTexture);
    gracz.setPosition(20,400);
    gracz.setScale(.35f,.35f);
    gracz.setTextureRect(sf::IntRect(0, 0, 425, 280 ));

    hpTexture.loadFromFile("x/cartman/hp.png");
    hp_view.setTexture(hpTexture);
    hp_view.setPosition(0,0);

    cash.tCoin.loadFromFile("x/cartman/coin.png");
    cash.coin.setTexture(cash.tCoin);
    cash.coin.setScale(.12f,.12f);
    cash.font.loadFromFile("x/font.ttf");
    cash.coin_numT.setColor(sf::Color::White);
    cash.coin_numT.setFont(cash.font);
    cash.coin_numT.setPosition(10,130);
    cash.coin_numT.setCharacterSize(30);


    ss << cash.coin_num;
    string text_cn = "x" + ss.str();
    cash.coin_numT.setString(text_cn);

    cash.coin.setPosition(cash.coin_numT.getLocalBounds().width+20,130);

    sTexture.loadFromFile("x/cartman/shoot.png");
    strzal.setTexture(sTexture);
    strzal.setTextureRect(sf::IntRect(0, 0, 155, 120 ));
    strzal.setScale(.5f,.5f);

    sb1[0].loadFromFile("x/cartman/shotgun_shot.wav");
    shotgun_shot.setBuffer(sb1[0]);
    sb1[1].loadFromFile("x/cartman/shotgun_reload.wav");
    shotgun_reload.setBuffer(sb1[1]);

    rifle_ammoTexture.loadFromFile("x/cartman/shoot2.png");
    shot_rifle.setTexture(rifle_ammoTexture);
    shot_rifle.setTextureRect(sf::IntRect(0, 0, 29, 37));
    shot_rifle.setScale(.5f,.5f);

    sb2[0].loadFromFile("x/cartman/rifle_shot.wav");
    rifle_shot.setBuffer(sb2[0]);
    sb2[1].loadFromFile("x/cartman/rifle_reload.wav");
    rifle_reload.setBuffer(sb2[1]);

    ammo_num=ammo_numb;
    HP=hp;
    HP_MAX=hp;
    x_sammo=-10;
    x_rammo=-10;

    for(int i=0; i<ammo_numb; i++)
    {
        ammo_state el;
        el.fired=0;
        x_sammo+=20;
        el.ammo.setTexture(sTexture);
        el.ammo.setPosition(x_sammo,60);
        el.ammo.setTextureRect(sf::IntRect(174,0, 15, 40 ));

        ammo_shotgun.push_back(el);
    }

    for(int i=0; i<30; i++)
    {
        ammo_state el;
        el.fired=0;
        x_rammo+=10;
        el.ammo.setTexture(rifle_ammoTexture);
        el.ammo.setPosition(x_rammo, 60);
        el.ammo.setTextureRect(sf::IntRect(40,0, 9, 37 ));
        ammo_rifle.push_back(el);
    }
    item[2].t1.setPosition(320,60);
    item[2].t1.setCharacterSize(30);
}

