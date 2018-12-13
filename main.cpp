#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

#define FPS 60
#define WIDTH 800
#define HEIGHT 600
#define TITLE "ESCAPE FROM JSEC CHALLENGE: THE CHALLENGE"
#define TIMESTEP 1.0f / FPS
#define GRAVITY 500.0f
#define JUMP_LIMIT 300
#define GROUND_LIMIT 450

#define UP sf::Keyboard::W
#define DOWN sf::Keyboard::S
#define LEFT sf::Keyboard::A
#define RIGHT sf::Keyboard::D
#define SELECT sf::Keyboard::Return
#define CANCEL sf::Keyboard::BackSpace

using namespace std;

struct Player{
    float x = 20;
    float y = 450;
    sf::RectangleShape boundingBox;
    sf::Texture texture;
    sf::IntRect sourceSprite;
    sf::Sprite sprite;
    int state; // 0 - walking   1 - jumping    2 - falling    3 - sliding
    sf::Clock clock;

    Player(){
        texture.loadFromFile("images/matt.png");
        sourceSprite = sf::IntRect(400, 450, 400, 450);
        sprite = sf::Sprite(texture, sourceSprite);
        sourceSprite.left = 400;
        sourceSprite.top = 450;
        sprite.setTextureRect(sourceSprite);
        sprite.setScale(sf::Vector2f(0.25,0.27));
        sprite.setPosition(sf::Vector2f(x, y));
        state = 0;

        boundingBox = sf::RectangleShape(sf::Vector2f(80,120));
        boundingBox.setFillColor(sf::Color::Red);
        boundingBox.setPosition(sf::Vector2f(20, 450));
    }

    void update(){
        if(state == 0){
            if(clock.getElapsedTime().asSeconds() > 0.5f){  
                walk();
                clock.restart();
            }
        } else if(state == 1){
            y -= 420 * TIMESTEP;
            if(y <= JUMP_LIMIT){
                y = JUMP_LIMIT;
                state = 2;
            }
        } else if (state == 2){
            y += GRAVITY * TIMESTEP;
            if(y >= GROUND_LIMIT){
                y = GROUND_LIMIT;
                state = 0;
            }
        }
        cout << state << endl;
        updatePosition(x, y);
    }

    void walk(){
        if (sourceSprite.left == 800)
            sourceSprite.left = 0;
        else
            sourceSprite.left += 400;
        sprite.setTextureRect(sourceSprite);
    }

    void jump(){
        if(state == 0){
            state = 1;
        }
    }

    void updatePosition(float x, float y){
        sprite.setPosition(sf::Vector2f(x,y));
    }

    sf::Sprite getSprite(){
        return sprite;
    }
}; 

struct BGImage{
    float x, y, scrollSpeed;
    sf::Vector2u size;
    sf::Texture texture;
    sf::Sprite sprite, sprite2;
    sf::Image image;

    BGImage(string filename, float speed){
        this->x = 0;
        this->y = 0;

        assert(this->texture.loadFromFile(filename));

        this->size = texture.getSize();

        this->sprite.setTexture(this->texture);

        this->sprite2.setTexture(this->texture);
        this->sprite2.setPosition(this->size.x, 0);
        
        this->scrollSpeed = speed;
    }

    void update(){
        x -= TIMESTEP * scrollSpeed;

        if(abs(x) >= size.x){
            x = 0;
        }

        sprite.setPosition(x, y);
        sprite2.setPosition(x + size.x, 0);
    }
};

bool keyPressed(sf::Keyboard::Key key){
    return sf::Keyboard::isKeyPressed(key);
}

void handleInput(){
    if(keyPressed(UP)){
        cout << "UP PRESSED" << endl;
    }

    if(keyPressed(DOWN)){
        cout << "DOWN PRESSED" << endl;
    }

    if(keyPressed(RIGHT)){
        cout << "RIGHT PRESSED" << endl;
    }

    if(keyPressed(LEFT)){
        cout << "LEFT PRESSED" << endl;
    }

    if(keyPressed(SELECT)){
        cout << "SELECT PRESSED" << endl;
    }

    if(keyPressed(CANCEL)){
        cout << "CANCEL PRESSED" << endl;
    }

}

int main( void )
{
    srand( time( NULL ) );

    sf::RenderWindow window( sf::VideoMode( WIDTH, HEIGHT ), TITLE);
	window.setFramerateLimit( FPS );

    vector<BGImage> backgrounds;
    BGImage bg = BGImage("images/test_bg.png", 150);
    BGImage bg2 = BGImage("images/test_bg2.png", 250);
    for(int i=0; i<2; i++){
        // backgrounds.push_back()
    }
    backgrounds.push_back(bg);
    backgrounds.push_back(bg2);

    Player player;
    

    while( window.isOpen() )
    {

        sf::Event event;
        while( window.pollEvent( event ) )
        {
            switch( event.type )
			{
			case sf::Event::Closed:
                window.close();
				break;
			case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::Escape){
                    window.close();
                }
				break;
            case sf::Event::KeyReleased:
                break;
            }
        }
		
        window.clear();

        
        if(keyPressed(UP)){
            player.jump();
        }

        //draw backgrounds
        for(int i=0; i<backgrounds.size(); i++){
            window.draw(backgrounds[i].sprite);
            window.draw(backgrounds[i].sprite2);
        }

        player.update();

        // player.updatePosition();
        window.draw(player.getSprite());

        //move backgrounds
        for(int i=0; i<backgrounds.size(); i++){
            backgrounds[i].update();
        }

        window.display();

    }

    return 0;
}