#include "objects.h"

void rysuj_ekran(sf::RenderWindow &window, sf::Sprite &freeman, sf::Sprite &tlo, int op, int xs, int ys)
{
    sf::Texture sT, sS, cT;
    sT.loadFromFile("x/help/strzalka.png");
    sS.loadFromFile("x/help/kursor.png");
    cT.loadFromFile("x/cartman/cartman_ok.png");
    sf::Sprite cartman;
    sf::Sprite strz;
    sf::Sprite kursor;
    cartman.setTexture(cT);
    cartman.setTextureRect(sf::IntRect(0, 0, 425, 280 ));
    kursor.setTexture(sS);
    strz.setTexture(sT);
    cartman.setScale(.25f,.25f);
    cartman.setPosition(230,250);
    strz.setScale(.5f,.5f);
    kursor.setScale(.1f,.1f);
    strz.rotate(140);


    if(op==0)
    {
        window.draw(tlo);

    }
    else if(op!=0)
    {
        sf::Texture t;

        if(op==6)
            t.loadFromFile("x/help/okno2.jpg");
        else
            t.loadFromFile("x/help/okno.jpg");
        sf::Sprite s;
        s.setTexture(t);
        s.setPosition(166,45);
        window.draw(tlo);
        window.draw(s);

        if(op==3 || op==6)
        {
            static bool migniecie=true;

            if(migniecie)
            {
                strz.setColor(sf::Color(0,0,0,0));
                migniecie=false;
            }
            else
            {
                strz.setTexture(sT);
                migniecie=true;
            }
            strz.setPosition(xs,ys);
            window.draw(strz);
        }
        else if(op==4)
        {
            static int click=0;

            if(click%4==0)
            {
                 cartman.setTextureRect(sf::IntRect(425, 0, 425, 280 ));
                kursor.setTextureRect(sf::IntRect(295, 0, 392, 468));

                click=0;
            }
            else
            {
                  cartman.setTextureRect(sf::IntRect(0, 0, 425, 280 ));
                kursor.setTextureRect(sf::IntRect(0, 0, 295, 468));

            }
            click++;
            kursor.setPosition(xs,ys);
            window.draw(kursor);
        }
        else if(op==8)
        {
            static int x=xs, l=1;


            kursor.setTextureRect(sf::IntRect(295, 0, 392, 468));
            cartman.setTextureRect(sf::IntRect(425*l, 560, 425, 280 ));
            x+=2;
            l++;
            if(l>=3)
                l=1;


            kursor.setPosition(x,ys);
            window.draw(kursor);
        }
        else if(op==5)
        {
            static int l=0;

            cartman.setTextureRect(sf::IntRect(425*l, 280, 425, 280 ));
            l++;
            if(l>=5)
                l=0;
        }
        else if(op==7)
            cartman.setTextureRect(sf::IntRect(0, 280*3, 425, 280 ));

    }

    if(op!=0 && op!=6)
        window.draw(cartman);
    window.draw(freeman);

}

bool napis(string str, sf::RenderWindow &window, sf::Sprite &freeman)
{
    static int fx=0, l_fx=0;


    freeman.setTextureRect(sf::IntRect(300*fx, 550, 300, 550));

    if(l_fx==2)
     {
         l_fx=0;
         fx++;
     }
    l_fx++;

    if(fx>=7)
        fx=0;

    sf::Font f;
    sf::Text napis;
    sf::Texture p_tex;
    sf::Sprite pasek;

    p_tex.loadFromFile("x/help/pasek.jpg");
    pasek.setTexture(p_tex);
    pasek.setPosition(0,450);

    f.loadFromFile("x/font.ttf");
    napis.setColor(sf::Color::White);
    napis.setFont(f);
    napis.setString(str);

    napis.setCharacterSize(35);
    static int x, y=453;
    static bool pobierz_wartosc=true;

    if(pobierz_wartosc)
    {
        pobierz_wartosc=false;
        x=napis.getLocalBounds().width-100;
    }
    x-=20;
    napis.setPosition(x,y);
    window.draw(pasek);
    window.draw(napis);

    if(x<=-napis.getLocalBounds().width)
    {
        pobierz_wartosc=true;
        return false;
    }
    else
        return true;

}

bool podejdz(int x, sf::Sprite &freeman)
{
    static int l_tex=0;

    if(freeman.getPosition().x!=x)
    {
        freeman.setTextureRect(sf::IntRect(300*l_tex, 0, 300, 550));

        if(freeman.getPosition().x>x)
            freeman.move(-20,0);
        else
            freeman.move(20,0);
        std::cout<<freeman.getPosition().x<<std::endl;
        cout<<x<<endl;
        l_tex++;
        if(l_tex>=5)
            l_tex=0;
        return true;
    }
    else
    {
        freeman.setTextureRect(sf::IntRect(0, 0, 300, 550));
        freeman.move(0,0);
        return false;
    }
}


void help(sf::RenderWindow &window)
{
    static int licznik=0;
    sf::Texture tlo;
    tlo.loadFromFile("x/help/bg.png");
    sf::Sprite t;
    t.setTexture(tlo);

    sf::Texture mf;
    mf.loadFromFile("x/help/freeman_ok.png");
    sf::Sprite freeman;
    int x=960,y=-10, l_tex=0;
    freeman.setPosition(x,y);
    freeman.setTexture(mf);

    sf::Clock clock;

    const float timeStep = 1 / 10.f;

    while( window.isOpen() )
    {

        while(clock.getElapsedTime().asSeconds() < timeStep)
            sf::sleep(sf::milliseconds(20));
        clock.restart();

        sf::Event event;

        while(window.pollEvent(event))
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
               return;
        }
        if(licznik<3)
            rysuj_ekran(window,freeman,t,0);
        else if(licznik>=3)
            rysuj_ekran(window, freeman,t,1);

        switch(licznik)
        {
        case 0:
            if(!podejdz(600, freeman))
                licznik++;
            break;
        case 1:
            if(!napis("Witaj! Nazywam sie Morgan Freeman i wprowadze Cie do gry!", window, freeman))
                licznik++;
            break;
        case 2:
            if(!podejdz(-60, freeman))
                licznik++;
            break;
        case 3:
            if(!napis("To jest ekran rozgrywki", window, freeman))
                licznik++;
            break;
        case 4:
            rysuj_ekran(window, freeman, t, 3, 400 ,250);
            if(!napis("Tu znajduje sie twoja postac.. ", window, freeman))
                licznik++;
            break;
        case 5:
            rysuj_ekran(window, freeman, t, 4, 400 ,280);
            if(!napis("Zeby strzelic kliknij w ekran.. ", window, freeman))
                licznik++;
                break;
        case 6:
            rysuj_ekran(window, freeman, t, 3, 400 ,50);
            if(!napis("Tutaj pokazany jest stan twojego magazynka.", window, freeman))
                licznik++;
            break;
        case 7:
            rysuj_ekran(window, freeman, t, 5, 400 ,50);
            if(!napis("Po 2 sekundach bezczynnosci rozpocznie sie przeladowanie", window, freeman))
                licznik++;
            break;


        case 8:
            rysuj_ekran(window, freeman, t, 3, 500 ,25);
            if(!napis("To jest twoj pasek zdrowia.. ", window, freeman))
                licznik++;
            break;

        case 9:
            rysuj_ekran(window, freeman, t, 3, 380 ,90);
            if(!napis("W tym miejscu znajduje sie liczba posiadanych przez ciebie monet.. ", window, freeman))
                licznik++;
            break;
        case 10:
            if(!podejdz(700, freeman))
                licznik++;
            break;
        case 11:
            rysuj_ekran(window, freeman, t, 6, -1000 ,-1000);
            if(!napis("To jest menu ulepszen pokazujace sie po kazdym poziomie", window, freeman))
                licznik++;
            break;
        case 12:
            rysuj_ekran(window, freeman, t, 6, 400 ,60);
            if(!napis("Tu sa posiadane przez ciebie monety", window, freeman))
                licznik++;
            break;
         case 13:
            rysuj_ekran(window, freeman, t, 6, 630 ,60);
            if(!napis("Mozesz kupic: karabin (i amunicje)", window, freeman))
                licznik++;
            break;
        case 14:
            rysuj_ekran(window, freeman, t, 6, 750 ,80);
            if(!napis("Shotgun update (wiecej ammo)", window, freeman))
                licznik++;
            break;
        case 15:
            rysuj_ekran(window, freeman, t, 6, 550 ,230);
            if(!napis("Mr Towelie Special (chwilowa niesmiertelnosc)", window, freeman))
                licznik++;
            break;
        case 16:
            rysuj_ekran(window, freeman, t, 6, 750 ,200);
            if(!napis("Cheesy Poofs (+50% hp)", window, freeman))
                licznik++;
            break;
        case 17:
            rysuj_ekran(window, freeman, t, 1, -1000, -1000);
            if(!napis("Po odblokowaniu przedmioty te pojawia sie na ekranie gry", window, freeman))
                licznik++;
            break;
        case 18:
            rysuj_ekran(window, freeman, t, 7, -1000, -1000);
            if(!napis("Uzywac karabinu mozesz wciskajac '2'", window, freeman))
                licznik++;
            break;
        case 19:
            rysuj_ekran(window, freeman, t, 8, 400 ,280);
            if(!napis("Karabinem strzelasz klikajac i przeciagajac myszka po ekranie", window, freeman))
                licznik++;
            break;
        case 20:
             rysuj_ekran(window, freeman, t, 0);
             if(!podejdz(320, freeman))
                licznik++;
            break;
        case 21:
            rysuj_ekran(window, freeman, t, 0);
            if(!napis("To wszystko.. Zostaje mi tylko zyczyc ci powodzenia..", window, freeman))
                licznik++;
            break;
        case 22:
            rysuj_ekran(window, freeman, t, 0);
            if(!napis("...cieszyc sie kolejnym piegiem", window, freeman))
                licznik++;
            break;
        case 23:
                static int l=0;
                freeman.setTextureRect(sf::IntRect(l*300, 1100, 300, 550 ));
                rysuj_ekran(window,freeman,t,0);
                l++;
                if(l>=7)
                {
                    window.clear(sf::Color::Black);
                    return;
                }
        }




        window.display();
        window.clear();
    }



}
