#include <SFML/Graphics.hpp>

int main(){
	int rows = 20;
	int cols = 10;
	const int WIDTH = 40*rows + 4*40 + 10*40;
	const int HEIGHT = 40*cols + 3*40;

	sf::RenderWindow window(sf::Videomode(WIDTH,HEIGHT), "Tetris");
