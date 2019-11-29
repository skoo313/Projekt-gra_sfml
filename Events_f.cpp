#include "objects.h"
#include <fstream>
#include <string>

void start(sf::RenderWindow &oknoStart)
{

    sf::Texture t1;
    t1.loadFromFile("x/start/start1.png");
    sf::Sprite s1;
    s1.setTexture(t1);
    s1.setPosition(140,50);

    sf::RectangleShape rec1( sf::Vector2f( 30,40 ) ); // tworzymy prostok¹t

    rec1.setPosition( 150,400); // i ustawiamy mu pozycjê


    rec1.setFillColor(sf::Color(255,255,255));
    oknoStart.draw(rec1);
    oknoStart.display();
    Sleep(5000);
        oknoStart.clear();


    string a="South Park Digital Studio presents", b;
    sf::Font f;
    f.loadFromFile("x/font.ttf");
    sf::Text napis;
    napis.setColor(sf::Color::White);
    napis.setFont(f);
    napis.setPosition(150,400);
    napis.setCharacterSize(30);

    float x;
        sf::SoundBuffer sb;
    sf::Sound sound;

    sb.loadFromFile("x/start/typewrite.wav");
    sound.setBuffer(sb);


    for(int i=0; i<a.size(); i++)
    {
        if(i%2==0)
            sound.play();
        b+=a[i];
        napis.setString(b);

        x=napis.getLocalBounds().width;
        rec1.setPosition(x+160, 400);

        oknoStart.draw(s1);
        oknoStart.draw(napis);
        oknoStart.draw(rec1);

        oknoStart.display();
        oknoStart.clear();

        Sleep(75);
    }
    for(int i=0; i<5; i++)
    {
        if(i%2==0)
            rec1.setFillColor(sf::Color::Black);
        else
            rec1.setFillColor(sf::Color::White);
        oknoStart.draw(s1);
        oknoStart.draw(napis);
        oknoStart.draw(rec1);
        oknoStart.display();
         oknoStart.clear();
        Sleep(400);
    }
    for(int i=a.size()-1; i>=0; i--)
    {
        if(i%2==0)
            sound.play();
        a.erase(a.size() - 1, 1);
        napis.setString(a);
        oknoStart.draw(napis);
        oknoStart.draw(s1);
        oknoStart.display();
        oknoStart.clear();

        Sleep(40);
    }
    b="";
    a="Cartman: I hate gingers game";



    for(int i=0; i<a.size(); i++)
    {
        if(i%2==0)
            sound.play();
        b+=a[i];
        napis.setString(b);
        x=napis.getLocalBounds().width;
        rec1.setPosition(x+160, 400);

        oknoStart.draw(s1);
        oknoStart.draw(napis);
        oknoStart.draw(rec1);

        oknoStart.display();
        oknoStart.clear();

        Sleep(75);
    }

    for(int i=0; i<10; i++)
    {
        if(i%2==0)
            rec1.setFillColor(sf::Color::Black);
        else
            rec1.setFillColor(sf::Color::White);

        s1.setColor( sf::Color( 255, 255, 255, 255- 30*i ) );
        oknoStart.draw(s1);
        oknoStart.draw(napis);
        oknoStart.draw(rec1);
        oknoStart.display();
         oknoStart.clear();
        Sleep(200);
    }

        oknoStart.clear();
}

void game_over(sf::RenderWindow &oknoOver, options &o)
{
    sf::SoundBuffer sb;
    sf::Sound sound;
    sb.loadFromFile("x/cartman/game_over.wav");
    sound.setBuffer(sb);

    sf::Texture t1;
    sf::Sprite dead_cartman;
    t1.loadFromFile("x/cartman/dead_cartman.png");
    dead_cartman.setTexture(t1);
    dead_cartman.setScale(.75f,.75f);
    dead_cartman.setPosition(150,200);

    sf::Font f;
    f.loadFromFile("x/font.ttf");
    sf::Text napis;
    napis.setString("GAME OVER!");
    napis.setColor(sf::Color::White);
    napis.setFont(f);
    napis.setPosition(170,50);
    napis.setCharacterSize(100);


    sound.play();
    oknoOver.clear(sf::Color::Black);
    oknoOver.draw(napis);
    oknoOver.draw(dead_cartman);
    oknoOver.display();
    Sleep(3000);
    ranking(oknoOver, 2, o);
    exit(0);
}



void menu(options &op, sf::RenderWindow &oknoMenu)
{
    start(oknoMenu);

    sf::Texture tMenu;
    sf::Sprite sMenu;
    tMenu.loadFromFile("x/start/menu1.jpg");
    sMenu.setTexture(tMenu);

    sf::Font f;
    f.loadFromFile("x/font.ttf");
    sf::Text napis[5];
    for(int i=0; i<5; i++)
    {
        napis[i].setColor(sf::Color::Black);
        napis[i].setFont(f);
    }

    string opcje_tekstu[5]={"Menu","1. Graj", "2. Ranking","3. Pomoc","4. Wyjscie z gry"};
    int x_tekstu=580, y_tekstu=20;

    for(int i=0; i<5; i++)
    {
        y_tekstu+=50;
        napis[i].setString(opcje_tekstu[i]);
        napis[i].setPosition(x_tekstu,y_tekstu);
    }
    int wybor_menu=0;
    while( true )
    {
         oknoMenu.draw(sMenu);
        sf::Event event2;

        while(oknoMenu.pollEvent(event2))
        {


                sf::Vector2f k(sf::Mouse::getPosition(oknoMenu).x, sf::Mouse::getPosition().y-115);
               // cout<<k.x<<"  "<<k.y<<std::endl;
                for(int i=1; i<5; i++)
                    if(napis[i].getGlobalBounds().contains(k))
                    {
                        napis[i].setStyle( sf::Text::Style::Underlined );

                        if(event2.type==sf::Event::MouseButtonPressed)
                        {
                            wybor_menu=i;
                            op.option_num=wybor_menu;
                        }
                    }
                    else
                        napis[i].setStyle(sf::Text::Style::Regular);
        }

        for(int i=0; i<5; i++)
            oknoMenu.draw(napis[i]);

        if(wybor_menu==1)
        {
            oknoMenu.clear();
            break;
        }
        else if(wybor_menu==2)
        {
            wybor_menu=0;
            ranking(oknoMenu, 1, op);
        }
        else if(wybor_menu==3)
        {
            help(oknoMenu);
            break;
        }
        else if(wybor_menu==4)
            exit(0);

        oknoMenu.display();
        oknoMenu.clear();

        }
}

void level(options &op, sf::RenderWindow &oknoLevel,vector <Enemy> &en, Gracz &g)
{
    g.HP=g.HP_MAX;
    g.p_hp=313;
    op.lvl++;

    ostringstream ss;
    ss << op.lvl;
    string text_str = "Level " + ss.str();

    sf::Font f;
    f.loadFromFile("x/font.ttf");

    sf::Text text, text2;
    text.setFont(f);
    text.setString(text_str);
    text.setCharacterSize(100);

    text2=text;
    text2.setString("Trwa przygotowywanie poziomu");
    text2.setCharacterSize(20);
    text2.setPosition(300,500);
    text.setPosition(100,200);


    oknoLevel.clear();
    oknoLevel.draw(text);
    oknoLevel.draw(text2);
    oknoLevel.display();
    Sleep(3000);




    op.number_of_enemy=op.lvl;
    op.range_damage[0]=op.lvl;
    op.range_damage[1]=op.lvl*3;
    op.range_speed[0]=10;
    op.range_speed[1]=20;
    op.range_hp[0]=op.lvl*10;
    op.range_hp[1]=op.lvl*20;


    for(int y=0; y<op.number_of_enemy; y++)
    {
        cout<<"Tworzenie obiektu...";
        Enemy **obiekt = new Enemy*[0];

        obiekt[0]= new Enemy(
                             rand()% (op.range_hp[1]-op.range_hp[0])+op.range_hp[0]+1,
                             rand()% (op.range_damage[1]-op.range_damage[0])+op.range_damage[0]+1,
                             rand()% (op.range_speed[1]-op.range_speed[0])+op.range_speed[0]+1);

        en.push_back(*obiekt[0]);
        Sleep(10);
        delete obiekt;
        cout<<".. OK!"<<endl;
    }

     for (int i=0; i<en.size()-1; i++)
        for (int j=0; j<en.size()-1; j++)
            if (en[j].y>en[j+1].y)
                swap(en[j], en[j+1]);

    oknoLevel.clear();

    for(int i=0; i<g.ammo_num; i++)
            {
                g.ammo_shotgun[i].fired=0;
                g.ammo_shotgun[i].ammo.setTextureRect(sf::IntRect(174,0, 15, 40 ));
            }

}

void ranking(sf::RenderWindow &window, int op, options &o)
{
    window.clear();
    fstream plik;
    sf::Texture t;
    sf::Sprite background;
    t.loadFromFile("x/start/menu1.jpg");
    background.setTexture(t);
    sf::Font f;
    f.loadFromFile("x/font.ttf");

    if(op==1)
    {
        sf::Text text[5];
        sf::Text tmp_text[4];
        sf::Texture n_pt;
        n_pt.loadFromFile("x/start/n_p.png");
        sf::Sprite next, prev;
        next.setTexture(n_pt);
        next.setScale(.05f,.05f);
        next.setPosition(830,150);
        prev.setTexture(n_pt);
        prev.setScale(.05f,.05f);

        prev.setPosition(585,200);
        prev.rotate(180);
        text[0].setFont(f);
        text[0].setCharacterSize(20);
        text[0].setColor(sf::Color::Black);
        tmp_text[0]=tmp_text[1]=tmp_text[2]=tmp_text[3]=text[0];
        text[0].setCharacterSize(30);
        text[4]=text[3]=text[2]=text[1]=text[0];

        plik.open("x/ranking.txt", std::ios::in);

        if( !plik.good() )
        {
            text[0].setString("Brak danych!");
            text[0].setPosition(600,150);
            text[1].setString("[esc] wroc do menu");
            text[1].setCharacterSize(15);
            text[1].setPosition(620,190);

            while(true)
            {
                sf::Event event;

                while(window.pollEvent(event))
                {
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        return;
                }
                window.draw(background);

                for(int i=0; i<4; i++)
                    window.draw(text[i]);
                window.display();
                window.clear();
            }

        }
        else
        {
            struct dane
            {
                string d[4];
            };

            vector < dane > player;
            while(!plik.eof())
            {
                dane x;
                for(int i=0; i<4; i++)
                    getline( plik, x.d[i] );

                if(x.d[0]!="")
                    player.push_back(x);

            }
        {//zawartosc tmp_txt i polozenie testów
            tmp_text[0].setString("-------------nick-------------");
            tmp_text[0].setPosition(580,90);
            tmp_text[1].setString("------------poziom------------");
            tmp_text[1].setPosition(580,160);
            tmp_text[2].setString("-------------czas--------------");
            tmp_text[2].setPosition(580,230);
            tmp_text[3].setString("------zabici wrogowie------");
            tmp_text[3].setPosition(580,300);

            text[0].setPosition(600,35);
            text[0].setCharacterSize(40);
            text[1].setPosition(590,110);
            text[2].setPosition(590,180);
            text[3].setPosition(590,250);
            text[4].setPosition(590,320);
        }

            window.clear();

            int act_player=0;
            while(true)
            {
                sf::Event event;

                while(window.pollEvent(event))
                {
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        return;

                    sf::Vector2f k(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition().y-115);
               // cout<<k.x<<"  "<<k.y<<std::endl;

                    if(event.type==sf::Event::MouseButtonPressed)
                    {
                        if(prev.getGlobalBounds().contains(k))
                        {
                            cout<<player.size();
                            if(act_player==0)
                                act_player=player.size()-1;
                            else
                                act_player--;
                        }
                        else if(next.getGlobalBounds().contains(k))
                        {
                            if(act_player==player.size()-1)
                                act_player=0;
                            else
                                act_player++;
                        }
                    }
                }
                ostringstream ss;
                ss<<act_player+1;
                text[0].setString("MIEJSCE " + ss.str());
                ss.str("");
                text[1].setString(player[act_player].d[0]);
                text[2].setString(player[act_player].d[1]);
                text[3].setString(player[act_player].d[2]);
                text[4].setString(player[act_player].d[3]);

                window.draw(background);
                window.draw(next);
                window.draw(prev);
                int j=0;
                for(int i=0; i<5; i++)
                {
                    window.draw(tmp_text[j]);
                    window.draw(text[i]);
                    j++;
                }
                window.display();
                window.clear();
            }

        }

        plik.close();
    }
    else
    {
        t.loadFromFile("x/start/menu2.jpg");
        background.setTexture(t);
        window.clear();

        sf::Text nickt;
        sf::String nick;
        sf::Text tmp_text[4], text[4];
        nickt.setFont(f);
        nickt.setCharacterSize(20);
        nickt.setColor(sf::Color::Black);
        nickt.setPosition(590,110);

        tmp_text[3]=tmp_text[2]=tmp_text[1]=tmp_text[0]=nickt;
        nickt.setCharacterSize(30);
        text[0]=text[1]=text[2]=text[3]=nickt;

            tmp_text[0].setString("------wpisz swoj nick------");
            tmp_text[0].setPosition(580,90);
            tmp_text[1].setString("------------poziom------------");
            tmp_text[1].setPosition(580,160);
            tmp_text[2].setString("-------------czas--------------");
            tmp_text[2].setPosition(580,230);
            tmp_text[3].setString("------zabici wrogowie------");
            tmp_text[3].setPosition(580,300);


            text[0].setPosition(700,185);
            text[1].setPosition(700,250);
            text[2].setPosition(700,320);
            text[3].setCharacterSize(40);
            text[3].setPosition(600,35);

            ostringstream ss;
            ss<<o.lvl;
            text[0].setString(ss.str());
            ss.str("");

            int time = o.time_All.getElapsedTime().asSeconds();
            ss<< time/60;
            string a=ss.str();
            ss.str("");
            time= (int)time%60;
            ss<< time;
            a+=":"+ss.str();
            text[1].setString(a);
            ss.str("");

            ss<<o.dead_enemy;
            text[2].setString(ss.str());
            ss.str("");

        plik.open("x/ranking.txt", std::ios::in);
        int miejsce=-1, l, licznik=0;

        struct dane
        {
            string d[4];
        };

        vector < dane > player;

        if( plik.good() )
        {
            while(!plik.eof())
            {
                dane x;
                for(int i=0; i<4; i++)
                    getline( plik, x.d[i] );

                l= atoi(x.d[1].c_str());
                cout<<"L= "<<l<<endl;
                if(o.lvl>=l && miejsce==-1)
                    miejsce=licznik;
                licznik++;

                if(x.d[0]!="")
                    player.push_back(x);
            }
        }
        plik.close();

         ss<<miejsce+1;
        text[3].setString("Miejsce "+ss.str()+"!");
        ss.str();

        while(true)
        {

            sf::Event event;


            while(window.pollEvent(event))
            {
                switch(event.type)
                {
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Escape)
                        return;
                    break;
                case sf::Event::TextEntered:
                    if(event.text.unicode >= 32 && event.text.unicode && nick.getSize()<13)
                        nick += (char)event.text.unicode;
                    else if(event.text.unicode == 8 && nick.getSize() >0)
                        nick.erase(nick.getSize()-1, nick.getSize());
                    nickt.setString(nick);
                    if(event.text.unicode == 13)
                    {
                        ofstream z("x/ranking.txt");
                        bool zapisany=false;
                        cout<<miejsce<<endl;
                        for(int i=0; i<player.size(); i++)
                        {
                            if(i==miejsce && miejsce!=-1 && !zapisany)
                            {
                               zapisany=true;

                               z<<(string)nick<<endl;
                               z<<o.lvl<<endl;
                               z<<a<<endl;
                               z<<o.dead_enemy<<endl;
                               i--;
                            }
                            else
                                for(int j=0; j<4; j++)
                                {
                                    z<<player[i].d[j]<<endl;
                                }
                        }
                        if(miejsce==-1 && !zapisany)
                        {
                            z<<(string)nick<<endl;
                            z<<o.lvl<<endl;
                            z<<a<<endl;
                            z<<o.dead_enemy<<endl;
                        }
                        z.close();
                    }
                    break;
                }
            }
            window.draw(background);

            for(int i=0; i<4; i++)
                window.draw(tmp_text[i]);
            for(int i=0; i<4; i++)
                window.draw(text[i]);

            window.draw(nickt);
            window.display();
            window.clear();
        }
    }
    plik.close();
}


