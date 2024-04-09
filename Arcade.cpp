#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>
#include <ctime>
#include <vector>

using namespace sf;
using namespace std;

int checker(float x, float y, int type)
{
    if (type == 1)
    {
        if (x < 0 || x + 50 > 600 || y - 70 < 0 || y + 5 > 900)
        {
            return 0;
        }
    }
    if (type == 2)
    {
        if (x < 0 || x + 60 > 600 || y - 78 < 0 || y + 40 > 900)
        {
            return 0;
        }
    }
    return 1;
}
class Bang
{
public:
    Bang()
    {

    }
};
class Plane_lvl2
{
public:

    int type = 2;
    float shootCooldown = 0.2f;
    float damage = 1.5f;

    Plane_lvl2()
    {
        wing.setPointCount(3);
        wing.setPoint(0, Vector2f(0.f, 0.f));
        wing.setPoint(1, Vector2f(60.f, 0.f));
        wing.setPoint(2, Vector2f(30.f, -80.f));

        wing.setFillColor(Color::Blue);
        wing.setPosition(275.f, 800.f);

        wing_helper.setPointCount(3);
        wing_helper.setPoint(0, Vector2f(0.f, 0.f));
        wing_helper.setPoint(1, Vector2f(60.f, 0.f));
        wing_helper.setPoint(2, Vector2f(30.f, 40.f));


        wing_helper.setFillColor(Color::Blue);
        wing_helper.setPosition(275.f, 800.f);

        small_wing.setPointCount(3);
        small_wing.setPoint(0, Vector2f(0.f, 0.f));
        small_wing.setPoint(1, Vector2f(30.f, 0.f));
        small_wing.setPoint(2, Vector2f(15.f, -40.f));
        

        small_wing.setFillColor(Color::Green);
        small_wing.setPosition(290.f, 807.5f);

        small_wing_helper.setPointCount(3);
        small_wing_helper.setPoint(0, Vector2f(0.f, 0.f));
        small_wing_helper.setPoint(1, Vector2f(30.f, 0.f));
        small_wing_helper.setPoint(2, Vector2f(15.f, 20.f));


        small_wing_helper.setFillColor(Color::Green);
        small_wing_helper.setPosition(290.f, 807.5f);
    }

    Vector2f getPosition() const
    {
        return wing.getPosition();
    }

    void draw(RenderWindow& window)
    {
        window.draw(wing);
        window.draw(wing_helper);
        window.draw(small_wing);
        window.draw(small_wing_helper);
    }

    void move(float offsetX, float offsetY)
    {
        wing.move(offsetX, offsetY);
        wing_helper.move(offsetX, offsetY);
        small_wing.move(offsetX, offsetY);
        small_wing_helper.move(offsetX, offsetY);
    }

    Vector2f getGunPosition() const
    {
        return wing.getPosition() + Vector2f(25.0f, -77.f);
    }

private:
    ConvexShape wing, wing_helper;
    ConvexShape small_wing, small_wing_helper;
};
class Plane_lvl1 
{
public:

    int type = 1;
    float shootCooldown = 0.25f;
    float damage = 1.0f;

    Plane_lvl1()
    {
        wing.setPointCount(3);
        wing.setPoint(0, Vector2f(0.f, 0.f));
        wing.setPoint(1, Vector2f(50.f, 0.f));
        wing.setPoint(2, Vector2f(25.f, -70.f));
        wing.setFillColor(Color::Blue);
        wing.setPosition(275.f, 800.f);

        small_wing.setPointCount(3);
        small_wing.setPoint(0, Vector2f(0.f, 0.f));
        small_wing.setPoint(1, Vector2f(25.f, 0.f));
        small_wing.setPoint(2, Vector2f(12.5f, -35.5f));
        small_wing.setFillColor(Color::Green);
        small_wing.setPosition(287.5f, 805.f);
    }

    Vector2f getPosition() const
    {
        return wing.getPosition();
    }

    void draw(RenderWindow& window)
    {
        window.draw(wing);
        window.draw(small_wing);
    }

    void move(float offsetX, float offsetY)
    {
        wing.move(offsetX, offsetY);
        small_wing.move(offsetX, offsetY);
    }

    Vector2f getGunPosition() const 
    {
        return wing.getPosition() + Vector2f(20.5f, -70.f);
    }

private:
    ConvexShape wing;
    ConvexShape small_wing;
};
class Astro
{
public:
    Vector2f speed;
    ConvexShape astro;

    float health = 5.0f;
    float cooldown = 0.1;

    Astro(Vector2f position, Vector2f speed) : speed(speed)
    {
        astro.setPointCount(8);

        astro.setPoint(0, Vector2f(20.f, 0.f));
        astro.setPoint(1, Vector2f(14.14f, 14.14f));
        astro.setPoint(2, Vector2f(0.f, 20.f));
        astro.setPoint(3, Vector2f(-14.14f, 14.14f));
        astro.setPoint(4, Vector2f(-20.f, 0.f));
        astro.setPoint(5, Vector2f(-14.14f, -14.14f));
        astro.setPoint(6, Vector2f(0.f, -20.f));
        astro.setPoint(7, Vector2f(14.14f, -14.14f));

        astro.setFillColor(Color::White);
        astro.setPosition(position);
    }

    Vector2f getPos() const
    {
        return astro.getPosition();
    }

    void update()
    {
        astro.move(speed);
    }
};
class Projectile 
{
public:
    CircleShape shape;
    Vector2f velocity;

    float damage = 2.5f;

    Projectile(Vector2f position, Vector2f velocity) : velocity(velocity) 
    {
        shape.setPosition(position);
        shape.setRadius(5.f);
        shape.setFillColor(Color::Red);
    }

    Vector2f getPos() const
    {
        return shape.getPosition();
    }

    void update() 
    {
        shape.move(velocity);
    }
};

int main()
{
    RenderWindow window(VideoMode(600, 900), "Arcade", Style::Default);
    
    Font font;
    font.loadFromFile("tested.ttf");

    Text inst;
    inst.setFont(font);
    inst.setFillColor(Color::Red);
    inst.setCharacterSize(40);
    inst.setStyle(Text::Bold);

    inst.setString("\t\t\t\t\tHello everyone!"
                   "\n\tThis is my simple Arcade game!"
                   "\n\tIf you want to start - click \"G\"!"
                   "\n\tIf you want to end - click \"Q\"!"
                   "\n\t\t\t\t\tGood luck :)");
    inst.setPosition(100.f, 275.f);

    RectangleShape menu(Vector2f(400.f, 230.f));
    menu.setFillColor(Color::White);
    menu.setPosition(100.f, 275.f);
    menu.setOutlineThickness(2);
    menu.setOutlineColor(Color::Red);

    RectangleShape scoreboard(Vector2f(600.f, 100.f));
    scoreboard.setFillColor(Color::White);
    scoreboard.setPosition(0.f, 0.f);
    scoreboard.setOutlineThickness(2);
    scoreboard.setOutlineColor(Color::Green);

    int help = 0;

    SoundBuffer buff, shoot;
    buff.loadFromFile("boom.wav");
    shoot.loadFromFile("dupko.wav");
    Sound sound, sound1;
    sound.setBuffer(buff);
    sound1.setBuffer(shoot);

    Plane_lvl1 plane;
    Clock shootClock, for_astro, expoClock;

    vector<Projectile> projectiles;
    vector<Astro> astro;
    
    Texture expo;
    Texture heart;
    Texture hrest;

    expo.loadFromFile("pop1.psd");
    heart.loadFromFile("heart.png");
    hrest.loadFromFile("hrest.png");

    vector<Sprite> hearts;
    for (int i = 0; i < 5; ++i)
    {
        Sprite heartSprite;
        heartSprite.setTexture(heart);
        heartSprite.setPosition(300.f + i * 50.f, 20.f);
        heartSprite.setOrigin(10.0f, 10.0f);
        heartSprite.setScale(50.0f / heartSprite.getGlobalBounds().width, 50.0f / heartSprite.getGlobalBounds().height);
        hearts.push_back(heartSprite);
    }

    vector<Sprite> crosses;
    for (int i = 0; i < 5; ++i)
    {
        Sprite crossSprite;
        crossSprite.setTexture(hrest);
        crossSprite.setPosition(300.f + i * 50.f, 20.f);
        crossSprite.setOrigin(10.0f, 10.0f);
        crossSprite.setScale(50.0f / crossSprite.getGlobalBounds().width, 50.0f / crossSprite.getGlobalBounds().height);
        crosses.push_back(crossSprite);
    }

    

    vector<pair<Sprite, Clock>> explosions;

    float spdX = 0.05;
    float spdY = 0.05;

    float astro_spdX = 0.025;
    float astro_spdY = 0.025;

    int pointer = 0;
    int visible = 0;

    int kills = 0;
    float koef = 1.5f;
    float suma = 0;

    int health = 3;

    Text message;
    message.setFont(font);
    message.setFillColor(Color::Red);
    message.setCharacterSize(35);

    srand(time(0));

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Q))
            {
                window.close();
            }
        }

        while (!help)
        {
            if (Keyboard::isKeyPressed(Keyboard::G))
            {
                help = 1;
            }
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Q))
            {
                window.close();
            }
            window.clear();

            window.draw(menu);
            window.draw(inst);

            window.display();
        }

        float popochka = rand() % (550 - 50 + 1) + 50;

        Projectile newProjectile(plane.getGunPosition(), Vector2f(0, -0.1f));
        Astro newAstro(Vector2f(popochka, 100), Vector2f(0, 0.03f));

        if (Keyboard::isKeyPressed(Keyboard::Space)) 
        {
            sound1.play();
            if (shootClock.getElapsedTime().asSeconds() >= plane.shootCooldown)
            {
                projectiles.push_back(newProjectile);
                shootClock.restart();
            }
        }

        if (for_astro.getElapsedTime().asSeconds() >= 1.0f)
        {
            astro.push_back(newAstro);
            for_astro.restart();
        }

        FloatRect cord1 = newAstro.astro.getGlobalBounds();
        FloatRect cord2 = newProjectile.shape.getGlobalBounds();


        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                if (checker(plane.getPosition().x - spdX, plane.getPosition().y - spdY, plane.type))
                {
                    plane.move(-spdX, -spdY);
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::D))
            {
                if (checker(plane.getPosition().x + spdX, plane.getPosition().y - spdY, plane.type))
                {
                    plane.move(spdX, -spdY);
                }
            }
            else
            {
                if (checker(plane.getPosition().x, plane.getPosition().y - spdY - 0.05, plane.type))
                {
                    plane.move(0, -spdY - 0.05);
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            if (Keyboard::isKeyPressed(Keyboard::W))
            {
                if (checker(plane.getPosition().x - spdX, plane.getPosition().y - spdY, plane.type))
                {
                    plane.move(-spdX, -spdY);
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::S))
            {
                if (checker(plane.getPosition().x - spdX, plane.getPosition().y + spdY, plane.type))
                {
                    plane.move(-spdX, spdY);
                }
            }
            else
            {
                if (checker(plane.getPosition().x - spdX - 0.05, plane.getPosition().y, plane.type))
                {
                    plane.move(-spdX - 0.05, 0);
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                if (checker(plane.getPosition().x - spdX, plane.getPosition().y + spdY, plane.type))
                {
                    plane.move(-spdX, spdY);
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::D))
            {
                if (checker(plane.getPosition().x + spdX, plane.getPosition().y + spdY, plane.type))
                {
                    plane.move(spdX, spdY);
                }
            }
            else
            {
                if (checker(plane.getPosition().x, plane.getPosition().y + spdY + 0.05, plane.type))
                {
                    plane.move(0, spdY + 0.05);
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            if (Keyboard::isKeyPressed(Keyboard::S))
            {
                if (checker(plane.getPosition().x + spdX, plane.getPosition().y + spdY, plane.type))
                {
                    plane.move(spdX, spdY);
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::W))
            {
                if (checker(plane.getPosition().x + spdX, plane.getPosition().y - spdY, plane.type))
                {
                    plane.move(spdX, -spdY);
                }
            }
            else
            {
                if (checker(plane.getPosition().x + spdX + 0.05, plane.getPosition().y, plane.type))
                {
                    plane.move(spdX + 0.05, 0);
                }
            }
        }

        

        window.clear();

        window.draw(scoreboard);
        plane.draw(window);

        for (auto it = projectiles.begin(); it != projectiles.end();) 
        {
            bool projectileRemoved = false; 
            for (auto astroIt = astro.begin(); astroIt != astro.end(); ++astroIt) 
            {
                if (it->shape.getGlobalBounds().intersects(astroIt->astro.getGlobalBounds())) 
                {
                    
                    astroIt->health -= it->damage;
                    
                    it = projectiles.erase(it);
                    projectileRemoved = true;
                    
                    if (astroIt->health <= 0) 
                    {
                        kills++;
                        suma = kills * koef;

                        Sprite exp1;
                        exp1.setTexture(expo);
                        exp1.setPosition(astroIt->astro.getPosition().x - 17, astroIt->astro.getPosition().y - 20);
                        exp1.setOrigin(10.0f, 10.0f);
                        exp1.setScale(50.0f / exp1.getLocalBounds().width, 50.0f / exp1.getGlobalBounds().height);
                        explosions.push_back(make_pair(exp1, Clock()));
                        astroIt = astro.erase(astroIt);
                        
                        sound.play();
                    }
                    break; 
                }
            }
            if (!projectileRemoved) 
            {
                it++; 
            }
        }

        message.setString("Kills: " + to_string(kills) + "\n" + "Score: " + to_string(suma));
        message.setPosition(50.f, 10.f);

        window.draw(message);

        for (auto& projectile : projectiles)
        {
            if (projectile.shape.getPosition().y > 100)
            {
                projectile.update();
                window.draw(projectile.shape);
            }
        }
        float angle = 15.0f;

        for (auto& astro : astro)
        {
            astro.update();
           
            astro.astro.setRotation(angle);
            angle = angle + 15.0f;
            window.draw(astro.astro);
        }

        for (auto& astro : astro)
        {
            if (astro.getPos().y >= 890)
            {
                if (health > 0)
                {
                    health--;
                }

                for (int i = 0; i < 5; i++)
                {
                    if (i < health)
                    {
                        hearts[i].setPosition(300.f + i * 50.f, 20.f);
                    }
                    else
                    {
                        crosses[i].setPosition(300.f + i * 50.f, 20.f);
                    }
                }
            }
        }

        for (int i = 0; i < 5; i++)
        {
            if (i < health)
            {
                window.draw(hearts[i]);
            }
            else
            {
                window.draw(crosses[i]);
            }
        }

        for (auto& explosion : explosions)
        {
            if (explosion.second.getElapsedTime().asSeconds() < 0.5f) 
            {
                window.draw(explosion.first);
            }
        }

        explosions.erase(remove_if(explosions.begin(), explosions.end(), [](const pair<Sprite, Clock>& explosion) 
        {
            return explosion.second.getElapsedTime().asSeconds() >= 0.5f;
        }), explosions.end());

        window.display();
    }

    return 0;
}
