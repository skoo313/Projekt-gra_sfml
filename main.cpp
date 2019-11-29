#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#define _WIN32_WINNT 0x0500
#include<windows.h>
#include<vector>
#include "objects.h"

int main()
{
    HWND hwnd=GetConsoleWindow();

    sf::RenderWindow oknoAplikacji( sf::VideoMode( 960, 540, 32 ), "x" ,sf::Style::None);

    ShowWindow(hwnd, SW_MINIMIZE);
    srand(time(NULL));

    vector < Enemy > enemy_a;
    options op;

    menu(op, oknoAplikacji);

    Gracz gracz(100,6);
    level(op, oknoAplikacji,enemy_a, gracz);

    Tlo t("tlo1");

    sf::Clock clock;

    const float timeStep = 1 / 10.f;
    load_textures();
    op.time_All.restart();
    while( oknoAplikacji.isOpen() )
    {
        while(clock.getElapsedTime().asSeconds() < timeStep)
            sf::sleep(sf::milliseconds(20));
        clock.restart();


        sf::Event event;
        bool action=false;


        while(oknoAplikacji.pollEvent(event))
        {

            if(event.type==sf::Event::KeyPressed)
            {

                gracz.stading.restart();
                gracz.reload=false;

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    oknoAplikacji.close();
                      ShowWindow(hwnd, SW_RESTORE);
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
                {
                    cout<<"Shotgun activated"<<endl;
                    gracz.active_gun=gracz.shotgun;
                    gracz.gracz.setTextureRect(sf::IntRect(0, 0, 425, 280 ));

                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && gracz.item[2].lock==false)
                {
                    gracz.active_gun=gracz.rifle;
                    gracz.gracz.setTextureRect(sf::IntRect(0, 560, 425, 280 ));
                    cout<<"Rifle activated"<<endl;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && gracz.item[1].num>0)
                {
                    gracz.immortal_b=true;
                    gracz.immortal_l=5000;
                    gracz.immortal_c.restart();
                    gracz.immortal_c2.restart();
                    gracz.item[1].num--;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && gracz.item[0].num>0)
                {
                    if(gracz.HP>=gracz.HP_MAX/2)
                        gracz.HP=gracz.HP_MAX;
                    else
                        gracz.HP+=gracz.HP_MAX/2;
                    gracz.item[0].num--;
                }



            }
            if(event.type==sf::Event::MouseButtonPressed && gracz.active_gun==gracz.shotgun )
            {
                gracz.stading.restart();
                gracz.s_action=true;
                gracz.reload=false;
            }
            else if( sf::Mouse::isButtonPressed( sf::Mouse::Button::Left ) && gracz.active_gun==gracz.rifle)
            {
                gracz.stading.restart();
                gracz.s_action=true;
                gracz.reload=false;
            }
            else if(event.type==sf::Event::MouseButtonReleased)
                gracz.stading.restart();
        }
        t.rysuj(oknoAplikacji);

        if(gracz.stading.getElapsedTime().asSeconds() > 2)
            gracz.reload=true;

        if(enemy_a.empty())
        {
            enemy_a.clear();
            gracz.update_menu(oknoAplikacji);
            level(op, oknoAplikacji,enemy_a, gracz);
        }
        else
            for(int i=0; i<enemy_a.size(); i++)
            {
                enemy_a[i].ruch(oknoAplikacji);
                enemy_a[i].hit(gracz, oknoAplikacji);

                if(gracz.HP<=0)
                    game_over(oknoAplikacji, op);

                if(enemy_a[i].dead)
                {
                    gracz.cash.coin_num+=enemy_a[i].value;
                    op.dead_enemy++;
                    enemy_a.erase(enemy_a.begin()+i);
                }
            }

        if(gracz.s_action)
        {
             gracz.shotf(oknoAplikacji, event);
             gracz.hit(enemy_a, oknoAplikacji);
        }
        else if(gracz.reload && gracz.active_gun==gracz.shotgun && gracz.ammo_shotgun[gracz.ammo_num-1].fired==1 ||
                                gracz.active_gun==gracz.rifle && gracz.ammo_rifle[29].fired==1)
            gracz.reloadf(oknoAplikacji);
        else
            gracz.draw(oknoAplikacji);

        oknoAplikacji.display();
        oknoAplikacji.clear();
    }
    return 0;
}

