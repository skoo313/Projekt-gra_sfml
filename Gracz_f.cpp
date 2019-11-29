#include "objects.h"

using namespace std;

void Gracz::shotf(sf::RenderWindow &window, sf::Event &event)
{
    static int x= 0, y;   //pozycja x i y w teksturze

    if(active_gun==shotgun)
    {
        y=0;

        if(ammo_shotgun[0].fired==0)
           x++;
        else if(ammo_shotgun[0].fired==1)
        {
            x=0;
            s_action=false;
        }
        else
            x=0;

        if(x>=3)
        {
            x=0;
            s_action=false;
        }

        if(event.type==sf::Event::MouseButtonPressed)
        {
            if(ammo_shotgun[0].fired==0)
            {
                  x++;
                shotgun_shot.play();

                //rysuje i pisze info o pozycji strzalu
                sf::Vector2i shoot_pos(sf::Mouse::getPosition(window));
                strzal.setPosition(shoot_pos.x - shoot_pos.x/20, shoot_pos.y- shoot_pos.y/20);
                window.draw(strzal);
                cout<<"X:"<<shoot_pos.x<<" Y:"<<shoot_pos.y<<endl;

                Sleep(50);
                shotgun_reload.play();

                for(int i=ammo_num-1; i>=0; i--) //sprawdza ammo, jak znajdzie pełny to nim ,,strzela''
                    if(ammo_shotgun[i].fired==0)
                    {
                        ammo_shotgun[i].fired=1;
                        ammo_shotgun[i].ammo.setTextureRect(sf::IntRect(156,0, 15, 40 ));
                        break;
                    }

            }
        }
    }
    else if(active_gun==rifle)
    {
        y=560;
        if(ammo_rifle[0].fired==0)
        {
            rifle_shot.play();

            sf::Vector2i shoot_pos(sf::Mouse::getPosition(window));
            shot_rifle.setPosition(shoot_pos.x, shoot_pos.y);
            window.draw(shot_rifle);
            cout<<"X:"<<shoot_pos.x<<" Y:"<<shoot_pos.y<<endl;
            mag_num--;
            Sleep(50);

            for(int i=29; i>=0; i--)
                if(ammo_rifle[i].fired==0)
                {
                    ammo_rifle[i].fired=1;
                    ammo_rifle[i].ammo.setTextureRect(sf::IntRect(29,0, 9, 37 ));
                    break;
                }

            x++;
            if(x>=3)
            {
                x=0;
                s_action=false;

            }
        }
    }

    gracz.setTextureRect(sf::IntRect(x*425, y, 425, 280 ));
    draw(window);
}
void Gracz::reloadf(sf::RenderWindow &window)
{
    cout<<"elo w reload"<<endl;
    static int x= 0,y;      // pozycja x i y w teksturze
    static sf::Clock clock2;

    if(active_gun==shotgun)
    {
        y=280;
        if(clock2.getElapsedTime().asMilliseconds()>=500)
        {
            shotgun_reload.play();
            for(int i=0; i<ammo_num; i++)
            {
                if(ammo_shotgun[i].fired==1)
                {
                    ammo_shotgun[i].fired=0;
                    ammo_shotgun[i].ammo.setTextureRect(sf::IntRect(174,0, 15, 40 ));
                    break;
                }
            }
            clock2.restart();
        }

        x++;

        if(x>=5 || ammo_shotgun[ammo_num-1].fired==0)
        {

            x=0;
            reload=false;
            s_action=false;
            shotgun_reload.pause();

        }
    }
    else if(active_gun==rifle)
    {
        if(x==0 && ammo_rifle[29].fired==1 && mag_num>=30)
            rifle_reload.play();
        y=840;



        if(clock2.getElapsedTime().asMilliseconds()>=250)               //działanie dzewieku strzlu
        {
            x++;
            clock2.restart();
        }

        if(mag_num<30)
        {
            reload=false;
            s_action=false;
            x=0;
        }
        else if(x>=7 || ammo_rifle[29].fired==0)
        {

            reload=false;
            s_action=false;
            x=0;

            int end_m;
            if(mag_num>=30)
                end_m=30;
            else
                end_m=mag_num;

            for(int i=0; i<end_m; i++)
            {
                ammo_rifle[i].fired=0;
                ammo_rifle[i].ammo.setTextureRect(sf::IntRect(40, 0, 9, 37));
            }

        }



    }
    if(active_gun==shotgun && ammo_shotgun[ammo_num-1].fired==0 || active_gun==rifle && ammo_rifle[29].fired==0 || mag_num==0)
        stading.restart();

    gracz.setTextureRect(sf::IntRect(426*x, y, 425, 280 ));
    draw(window);
}

void Gracz::hit(vector <Enemy> &enemyx, sf::RenderWindow &window)
{
    for(int i=0; i<enemyx.size(); i++)
        if(strzal.getGlobalBounds().intersects(enemyx[i].player.getGlobalBounds()) || shot_rifle.getGlobalBounds().intersects(enemyx[i].player.getGlobalBounds()))
        {
            enemyx[i].HP-=damage;

            if(enemyx[i].HP<=0)
            {

                enemyx[i].speed=0;
                enemyx[i].t_y=1;
            }
            cout<<"Trafiony!"<<enemyx[i].HP<<endl;

            //-------Tworzy pasek zdrowia przy trafieniu we wroga-----------//
            float p_hp= enemyx[i].HP*100/enemyx[i].HP_MAX; //oblicza ile % hp zostało przeciwnikowi
            sf::RectangleShape rec1( sf::Vector2f( p_hp, 10 ) ); // tworzymy prostok¹t
            rec1.setPosition( enemyx[i].player.getPosition().x, enemyx[i].player.getPosition().y-10); // i ustawiamy mu pozycjê
            rec1.setFillColor(sf::Color(255,0,58));
            window.draw(rec1);
        }

    strzal.setPosition(-200,-200);
    shot_rifle.setPosition(-200,-200);
}
void Gracz::draw(sf::RenderWindow &window)
{
ostringstream ss;
    if(active_gun==shotgun)
    {
        for(int i=0; i<ammo_num; i++)
            window.draw(ammo_shotgun[i].ammo);
    }
    else if(active_gun==rifle)
    {
        for(int i=0; i<30; i++)
            window.draw(ammo_rifle[i].ammo);
        ss << mag_num;
        item[2].t1.setString("x"+ss.str());
        ss.str("");
        item[2].t1.setPosition(320,60);
        window.draw(item[2].t1);
    }



    item[0].item.setPosition(850,20);
    item[0].t1.setPosition(790,40);
    item[1].item.setPosition(700,15);
    item[1].t1.setPosition(630,40);
    for(int i=0; i<2; i++)
    {
        window.draw(item[i].item);
        window.draw(item[i].t1);
        ss << item[i].num;
        item[i].t1.setString(ss.str()+"x");
        ss.str("");
    }

    hp_view.setTextureRect(sf::IntRect(0,0, p_hp, 22 ));
    hp_view.setPosition(0,20);
    window.draw(hp_view);
    window.draw(cash.coin);


    ss << cash.coin_num;
    string text_cn = "x" + ss.str();
    cash.coin_numT.setString(text_cn);
    window.draw(cash.coin_numT);
    window.draw(gracz);

}
void Gracz::update_menu(sf::RenderWindow &window)
{
    ostringstream ss;
    sf::Texture t;
    t.loadFromFile("x/cartman/update/menu.jpg");
    sf::Sprite menu;

    menu.setTexture(t);

    ss << item[0].price;
    item[0].t1.setString("-"+ss.str());
    item[0].t1.setPosition(750,350);
    ss.str("");

    ss << item[1].price;
    item[1].t1.setString("-"+ss.str());
    item[1].t1.setPosition(400,350);
    ss.str("");

    ss << item[2].price;
    item[2].t1.setString("-"+ss.str());
    item[2].t1.setPosition(400,90);
    item[2].t1.setCharacterSize(50);
    ss.str("");

    ss << item[3].price;
    item[3].t1.setString("-"+ss.str());
    item[3].t1.setPosition(750,90);
    ss.str("");

    cash.coin_numT.setPosition(100,60);
    while(true)
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            //zmienia wartości które są uzywane w innym miejscu na poczatkowe. konczy funkcje
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                item[2].t1.setCharacterSize(30);
                cash.coin_numT.setPosition(10,130);
                item[0].item.setPosition(850, 20);
                ss << item[0].num;
                item[0].t1.setString(ss.str()+"x");
                ss.str("");
                item[0].t1.setPosition(item[0].item.getPosition().x-item[0].t1.getLocalBounds().width , 40);
                item[1].item.setPosition(650,20);
                ss << item[1].num;
                item[1].t1.setString(ss.str()+"x");
                ss.str("");
                item[1].t1.setPosition(item[1].item.getPosition().x-item[1].t1.getLocalBounds().width , 40);

                for(int i=0; i<4; i++)
                    item[i].t1.setStyle( sf::Text::Style::Regular );
                return;
            }

            sf::Vector2f k(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition().y-115);
               //cout<<k.x<<"  "<<k.y<<std::endl;
                for(int i=0; i<4; i++)
                    if(item[i].t1.getGlobalBounds().contains(k))
                    {
                        item[i].t1.setStyle( sf::Text::Style::Underlined );

                        if(event.type==sf::Event::MouseButtonPressed)
                        {
                            if(cash.coin_num >= item[i].price)
                            {
                                cash.coin_num -= item[i].price;
                                ss << cash.coin_num;
                                cash.coin_numT.setString("x"+ss.str());
                                ss.str("");

                                if(i==0 || i==1)
                                    item[i].num+=1;
                                else if(i==2)
                                {
                                    if(item[i].lock)
                                    {
                                        item[i].price=100;
                                        ss << item[i].price;
                                        item[i].t1.setString("-"+ss.str());
                                        ss.str("");
                                        item[i].lock=false;
                                    }
                                    else
                                        mag_num+=30;
                                }
                                else if(i==3)
                                {
                                    ammo_num+=1;
                                    ammo_state el;
                                    el.fired=0;
                                    x_sammo+=20;
                                    el.ammo.setTexture(sTexture);
                                    el.ammo.setPosition(x_sammo, 60);
                                    el.ammo.setTextureRect(sf::IntRect(174,0, 15, 40 ));

                                    ammo_shotgun.push_back(el);

                                }
                            }

                        }
                    }
                    else
                       item[i].t1.setStyle(sf::Text::Style::Regular);


        }
        window.draw(menu);

        for(int i=0; i<4; i++)
            window.draw(item[i].t1);
        window.draw(cash.coin_numT);
        window.display();
        window.clear();
    }

}

