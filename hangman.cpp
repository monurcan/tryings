#include <SFML\Graphics.hpp>
char gameState = 1;
sf::Font font;

std::string picknewWord() {
	srand(time(NULL));
	std::string wlist[26] = {
		"absolutely",
		"absorb",
		"abuse",
		"abuse",
		"academic",
		"accent",
		"late",
		"later",
		"latest",
		"latter",
		"minimum",
		"minister",
		"ministry",
		"minor",
		"minority",
		"neat",
		"neck",
		"bear",
		"hack",
		"quora",
		"face",
		"daft",
		"what",
		"onur",
		"ceza",
		"sago"
	};
	return wlist[rand() % 25];
}

void Menu(sf::RenderWindow &window) {
	sf::Text score;
	score.setFont(font);
	score.setString(sf::String("ok"));
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

void Win(sf::RenderWindow &window) {
	sf::Text score;
	score.setFont(font);
	score.setString(sf::String("hll"));
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
		window.clear(sf::Color::Green);
		window.draw(button);
		window.draw(score);
		window.display();
	}
}

void Game(sf::RenderWindow &window) {
	std::string word = picknewWord(), nword=word;
	int len = word.length(), falsetry = 0, truetry = 0;
	char falsetries[7];
	std::vector<sf::RectangleShape> lines(len, sf::RectangleShape(sf::Vector2f(330/len, 4)));
	for (int i = 0; i < len; i++) lines[i].setPosition(400 / len * i + 30, 470);
	std::vector<sf::Text> letters(len, sf::Text("", font, 70));
	for (int i = 0; i < len; i++) {
		letters[i].setFillColor(sf::Color::Black);
		letters[i].setPosition(400 / len * i + 50, 370);
		letters[i].setString(sf::String(word[i]));
	}
	sf::RectangleShape man[7] = {
		sf::RectangleShape(sf::Vector2f(60, 60)),
		sf::RectangleShape(sf::Vector2f(5, 200)),
		sf::RectangleShape(sf::Vector2f(5, 100)),
		sf::RectangleShape(sf::Vector2f(5, 100)),
		sf::RectangleShape(sf::Vector2f(5, 120)),
		sf::RectangleShape(sf::Vector2f(5, 120)),
		sf::RectangleShape(sf::Vector2f(5, 20))
	};
	man[0].setPosition(190, 10);
	man[1].setPosition(220, 70);
	man[2].setPosition(220, 80);
	man[2].setRotation(45);
	man[3].setPosition(220, 80);
	man[3].setRotation(-45);
	man[4].setPosition(220, 265);
	man[4].setRotation(45);
	man[5].setPosition(220, 265);
	man[5].setRotation(-45);
	man[6].setPosition(220, 265);
	man[6].setFillColor(sf::Color::Red);
	while (window.isOpen()) {
		sf::Event evt;
		while (window.pollEvent(evt))
			if (evt.type == sf::Event::Closed) {
				gameState = 0;
				return;
			}
			else if (evt.type == sf::Event::TextEntered) {
				int pos = nword.find(evt.key.code);
				if (pos != std::string::npos) {
					if (letters[pos].getFillColor() != sf::Color::Red) {
						truetry++;
						letters[pos].setFillColor(sf::Color::Red);
						nword[pos] = ' ';
					}
				}else if (word.find(evt.key.code) == std::string::npos){
					bool isTried = 0;
					for (int i = 0; i < falsetry; i++) if (falsetries[i] == evt.key.code) isTried = 1;
					if(!isTried) falsetries[falsetry++] = evt.key.code;
				}
			}
		window.clear(sf::Color::Black);
		for (auto l : lines) window.draw(l);
		for (auto l : letters) window.draw(l);
		if (falsetry == 7) {
			gameState = 1;
			return;
		}else if(truetry == len) {
			gameState = 3;
			return;
		}
		for (int i = 0; i < falsetry; i++) window.draw(man[i]);
		window.display();
	}
}

int main() {
	sf::RenderWindow window(sf::VideoMode(442, 492), "tatli busra", sf::Style::Close);
	window.setFramerateLimit(10);
	font.loadFromFile("calibri.ttf");
	while (gameState)
		if (gameState == 2) Game(window);
		else if (gameState == 3) Win(window);
		else Menu(window);
}