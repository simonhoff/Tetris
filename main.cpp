#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <new>
#include "Tetris.h"
#include "shape.h"

//set up colors
const sf::Color boardColor = sf::Color{0x33,0x33,0x33};

const sf::Color colormap[8] = {
	sf::Color::Red,
	sf::Color::Blue,
	sf::Color(0x00,0xAA,0xCC), //Cyan
	sf::Color(0xCC,0xDD,0x00), //Yellow
	sf::Color::Green,
	sf::Color(0xBB,0x00,0xCC), //Purple
	sf::Color(0xFF,0xBB,0x00), //Orange
	boardColor
};

const sf::Time updateTime = sf::milliseconds(250);
const sf::Time keyTime = sf::milliseconds(100);
const sf::Time frame = sf::milliseconds(10);

int main(){
	srand(time(NULL));

	int rows = 20;
	int cols = 10;

	static const int field_size = 40;
	static const int border_size = 4;
	static const int WIDTH = field_size*rows + (rows - 1)* border_size + 4*field_size + 10*field_size;
	static const int HEIGHT = field_size*cols + (cols - 1)*border_size + 3*field_size;

	sf::RenderWindow window(sf::VideoMode(HEIGHT,WIDTH), "Tetris", sf::Style::Close);
	//allocate and set up game
	Tetris game;
	game.startGame();

	game.checkBoard();

	sf::Clock playTimer;
	sf::Clock inputTimer;
	sf::Clock frameTimer;

	while (window.isOpen()) {
		sf::Time elapsedPlay = playTimer.getElapsedTime();
		sf::Time elapsedInput = inputTimer.getElapsedTime();
		sf::Time elapsedFrame = frameTimer.getElapsedTime();

    	if(elapsedInput > keyTime){
    		inputTimer.restart();

        	sf::Event event;
        	while (window.pollEvent(event)) {
            	switch(event.type){
            	case sf::Event::Closed:
                	window.close();
                	break;
            	case sf::Event::KeyPressed:
                switch(event.key.code) {
        	        case sf::Keyboard::Left:
    	            	game.move(LEFT);
        	        	break;
	                case sf::Keyboard::Right:
                		game.move(RIGHT);
            	    	break;
        	        case sf::Keyboard::Down:
    	            	game.move(DOWN);
                		break;
                	case sf::Keyboard::Up:
                		game.rotate();
                		break;
                	case sf::Keyboard::LShift:
                    	//add hold functionality
                    	break;
                	case sf::Keyboard::Space:
                		//hardDrop
                	    game.hardDrop();
                    	break;
                	}
            	    break;
        	    
    	        }
    	    }
    	}

    	if (elapsedPlay > updateTime){
	        playTimer.restart();

	        game.update();
        	window.clear();
        }

        if (elapsedFrame > frame){
        	frameTimer.restart();
    		for(int row = 0; row < rows; row++) {
	        	for(int col = 0; col < cols; col++) {
    	        	const int tile_x = col * field_size, tile_y = (rows - row - 1) * field_size;

    	    	    sf::RectangleShape field;
	        	    field.setSize(sf::Vector2f(field_size - border_size, field_size - border_size));
        	    	//get tile at current position, and copy color to output field
	        	    Field_t* cur = game.get(col,row);
    	        	field.setFillColor(colormap[(int) cur->clr]);
    	    	    //set window position of current field
        		    field.setPosition(tile_x + border_size / 2.0, tile_y + border_size / 2.0);
        		    window.draw(field);
            	}
            }
	    }

	    window.display();
	    if (game.isGameLost())
	    	break;
	}

    return 0;
}