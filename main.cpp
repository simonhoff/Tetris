#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <new>
#include "Tetris.h"
#include "shape.h"


int main(){
	srand(time(NULL));
	int rows = 20;
	int cols = 10;
	static const int WIDTH = 40*rows + 4*40 + 10*40;
	static const int HEIGHT = 40*cols + 3*40;

	sf::RenderWindow window(sf::Videomode(WIDTH,HEIGHT), "Tetris", sf::Style::close);

	//set up colors
	const sf::Color boardColor = sf::Color{0xCC,0xCC,0xCC};

	const sf::Color colormap[] = {
		sf::Color::Red,
		sf::Color::Blue,
		sf::Color(0x00,0xAA,0xCC),
		sf::Color(0xCC,0xDD,0x00),
		sf::Color::Green,
		sf::Color(0xBB,0x00,0xCC),
		sf::Color(0xBB,0xEE,0x00),
		boardColor
	};


	//allocate and set up game
	Tetris* game = new Tetris;

while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch(event.type){
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch(event.key.code) {
                case sf::Keyboard::Left:
                	game->move(LEFT);
                	break;
                case sf::Keyboard::Right:
                	game->move(RIGHT);
                	break;
                case sf::Keyboard::Down:
                	game->move(DOWN);
                	break;
                case sf::Keyboard::Up:
                	game->rotate();
                	break;
                case sf::Keyboard::Shift:
                    //add hold functionality
                    break;
                case sf::Keyboard::Space:
                	//hardDrop
                    game->hardDrop();
                    break;
                }
                break;
            
            }
        }

        game->update();
        window.clear();

        /*
        for(int row = 0; row < height; ++row) {
            for(int col = 0; col < width; ++col) {
                const int tile_x = col * tile_size, tile_y = row * tile_size;

                sf::RectangleShape tile;
                tile.setSize(sf::Vector2f(tile_size - border_size, tile_size - border_size));
                tile.setFillColor(game->isTileOpen(row, col) ? open_fill_color : closed_fill_color);
                tile.setPosition(tile_x + border_size / 2.0, tile_y + border_size / 2.0);

                window.draw(tile);

                if (game->isTileOpen(row, col) || (game->isGameOver() && game->isTileMine(row, col))) {
                    sf::Text text;
                    text.setStyle(sf::Text::Bold);
                    text.setCharacterSize(tile_size / 2.0);

                    if (game->isTileMine(row, col)) {
                        text.setString("X");
                        text.setColor(mine_color);
                    }
                    else {
                        int num_adjacent_mines = game->numAdjacentMines(row, col);
                        if(num_adjacent_mines == 0) continue; // Ikke tegn nuller
                        text.setString(to_string(num_adjacent_mines));
                        text.setColor(number_colors[num_adjacent_mines]);
                    }

                    text.setFont(font);

                    sf::FloatRect text_rect = text.getLocalBounds();
                    text.setOrigin(text_rect.left + text_rect.width  / 2.0,
                                   text_rect.top  + text_rect.height / 2.0);
                    text.setPosition(tile_x + tile_size / 2.0, tile_y + tile_size / 2.0);

                    window.draw(text);
                }
            }
        }
        */

        window.display();
    }

    delete game;