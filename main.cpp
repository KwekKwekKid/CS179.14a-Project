#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#define FPS 60
#define WIDTH 800
#define HEIGHT 600
#define TITLE "ESCAPE FROM JSEC CHALLENGE: THE CHALLENGE"
#define TIMESTEP 1.0f / FPS
#define GRAVITY 9.8f

#define UP sf::Keyboard::W
#define DOWN sf::Keyboard::S
#define LEFT sf::Keyboard::A
#define RIGHT sf::Keyboard::D
#define SELECT sf::Keyboard::Return
#define CANCEL sf::Keyboard::BackSpace

using namespace std;

struct Player{
    float x, y;
    sf::RectangleShape boundingBox;
}; 

bool keyPressed(sf::Keyboard::Key key){
    return sf::Keyboard::isKeyPressed(key);
}

int main( void )
{
    srand( time( NULL ) );

    sf::RenderWindow window( sf::VideoMode( WIDTH, HEIGHT ), TITLE);
	window.setFramerateLimit( FPS );
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


        window.display();

    }

    return 0;
}