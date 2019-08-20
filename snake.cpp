#include <SFML\Graphics.hpp>
char gameState = 1, number;
sf::Font font;
sf::Text score;
struct coord {
	char x, y;
	bool operator==(struct coord& other) {
		return (other.x == this->x) && (other.y == this->y);
	}
};
void Menu(sf::RenderWindow &window) {
	score.setPosition(180, 175);
	score.setCharacterSize(70);
	sf::CircleShape button(80);
	button.setFillColor(sf::Color::Black);
	button.setPosition(141, 141);
	while (window.isOpen()) {
		sf::Event evet;
		while (window.pollEvent(evet))
			if (evet.type == sf::Event::Closed) {
				window.close();
				gameState = 0;
				return;
			}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || (sf::Mouse::isButtonPressed(sf::Mouse::Left) && button.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))) {
			gameState = 2;
			return;
		}
		window.clear(sf::Color(150, 140, 155));
		window.draw(button);
		window.draw(score);
		window.display();
	}
}
void Game(sf::RenderWindow &window) {
	number = 2;
	score.setPosition(10, 10);
	score.setCharacterSize(20);
	score.setString(sf::String(std::to_string(number*10)));
	std::vector<coord> table;
	coord bait = {rand() % 20, rand() % 20};
	sf::RectangleShape tmp(sf::Vector2f(20.0f, 20.0f));
	char direction = 0;
	table.push_back({ 12, 3 });
	table.push_back({ 12, 4 });
	while (window.isOpen()) {
		sf::Event evt;
		while (window.pollEvent(evt))
			if (evt.type == sf::Event::Closed) {
				gameState = 0;
				return;
			}else if (evt.type == sf::Event::KeyPressed)
				switch (evt.key.code) {
					case sf::Keyboard::W:
						if(table[0].y <= table[1].y)
							direction = 0;
						break;
					case sf::Keyboard::S:
						if (table[0].y >= table[1].y)
							direction = 1;
						break;
					case sf::Keyboard::A:
						if (table[0].x <= table[1].x)
							direction = 2;
						break;
					case sf::Keyboard::D:
						if (table[0].x >= table[1].x)
							direction = 3;
						break;
				}
		switch (direction){
			case 0:
				for (int i = number - 1; i > 0; i--) table[i] = table[i - 1];
				table[0].y = table[0].y ? (table[0].y-1) : 19;
				break;
			case 1:
				for (int i = number - 1; i > 0; i--) table[i] = table[i - 1];
				table[0].y = (table[0].y != 19) ? (table[0].y + 1) : 0;
				break;
			case 2:
				for (int i = number - 1; i > 0; i--) table[i] = table[i - 1];
				table[0].x = table[0].x ? (table[0].x - 1) : 19;
				break;
			case 3:
				for (int i = number - 1; i > 0; i--) table[i] = table[i - 1];
				table[0].x = (table[0].x != 19) ? (table[0].x + 1) : 0;
				break;
		}
		if (bait == table[0]) {
			table.push_back(table[number++ - 1]);
			score.setString(sf::String(std::to_string(number * 10)));
			bait = { rand() % 20, rand() % 20 };
		}
		window.clear(sf::Color::Black);
		for (int i = 0; i < number; i++) {
			if (i && table[i] == table[0]) {
				gameState = 1;
				return;
			}
			tmp.setPosition(22 * table[i].x + 2, 22 * table[i].y + 2);
			tmp.setFillColor(sf::Color::White);
			window.draw(tmp);
		}
		tmp.setPosition(22 * bait.x + 2, 22 * bait.y + 2);
		tmp.setFillColor(sf::Color::Red);
		window.draw(tmp);
		window.draw(score);
		window.display();
	}
}
int main() {
	sf::RenderWindow window(sf::VideoMode(442, 442), "Yilan Serdar", sf::Style::Close);
	window.setFramerateLimit(10);
	font.loadFromFile("calibri.ttf");
	score.setFont(font);
	score.setString(sf::String("yilan ol"));
	while (gameState)
		if (gameState == 2) Game(window);
		else Menu(window);
}