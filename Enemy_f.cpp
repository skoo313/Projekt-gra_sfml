#include "objects.h"

using namespace std;

sf::Texture texture[7];

void load_textures()
{
    cout<<"Ladowanie tekstur"<<endl;
    string char_names[]={"stan", "kyle", "kenny", "rudy1","rudy2", "rudy3","rudy_maly"};

    for(int i=0; i<7; i++)
        texture[i].loadFromFile("x/enemy/"+char_names[i]+".png");
}

Enemy::Enemy(int hp, int d, int s)
{
        y=rand()%155+281;
        HP=hp;
        HP_MAX=hp;
        speed=s;
        damage=d;
        player.setTexture(texture[rand()%7]);
        player.setPosition(800, y);
}
void Enemy::ruch(sf::RenderWindow &window)
    {

        t_x++;

        if(t_y==0)
        {
            if(t_x*75 >=225)
                t_x=1;
        }
        if(player.getPosition().x<200)
        {
            speed=0;
            if(!attack)
                 c_hit.restart();
            attack=true;
            if(!t_y==1)
                t_y=2;
        }
        player.move(-speed,0);

        rysuj(window);
    }

void Enemy::rysuj(sf::RenderWindow &window)
{
    if(t_y==0)
        player.setTextureRect(sf::IntRect(t_x * 75, t_y*100, 75,100 ));
    else
    {
        player.setTextureRect(sf::IntRect(pixele_p[dead_f], t_y*100, pixele_s[dead_f],100 ));
        dead_f++;

        if(dead_f==5)
        {
            if(t_y==1)
            {
                player.setPosition(-100,-100);
                dead=true;
            }
            dead_f=0;
        }
    }
    window.draw(player);
}

void Enemy::hit(Gracz &g, sf::RenderWindow &window)
 {
        if(attack && t_y!=1 && g.HP>0 && !g.immortal_b)
        {
            if(c_hit.getElapsedTime().asSeconds()>=1)
            {
                c_hit.restart();
                g.HP-=damage;

                float pr=(100-(g.HP*100/g.HP_MAX))/100;
                g.p_hp=(313-(pr*313));
                cout<<g.HP<<"  "<<pr<<"   " <<g.p_hp<<endl;

            }
        }
        else if(g.immortal_c.getElapsedTime().asSeconds()<5 && g.immortal_b)
        {
            ostringstream ss;
            g.immortal_l-=g.immortal_c2.getElapsedTime().asMilliseconds();
            g.immortal_c2.restart();
            ss << g.immortal_l;
            g.immortal_t.setString(ss.str());
            ss.str("");
            window.draw(g.immortal_t);
        }
        else if(g.immortal_c.getElapsedTime().asSeconds()>=5)
        {
            g.immortal_b=false;
        }
 }
