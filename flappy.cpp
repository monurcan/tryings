#include <SFML\Graphics.hpp>
int gameState = 1;
unsigned int score_ = 0;
sf::Font font;
sf::Text score;
void Menu(sf::RenderWindow & window) {
	score.setPosition(270, 370);
	score.setCharacterSize(120);
	score.setFillColor(sf::Color::White);
	sf::CircleShape bird(80);
	bird.setFillColor(sf::Color::Green);
	bird.setPosition(220, 370);
	while (window.isOpen()){
		sf::Event evet;
		while (window.pollEvent(evet))
			if (evet.type == sf::Event::Closed) {
				window.close();
				gameState = 0;
				return;
			}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bird.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))) {
			gameState = 2;
			return;
		}
		window.clear(sf::Color(150, 140, 155));
		window.draw(bird);
		window.draw(score);
		window.display();
	}
}
void Game(sf::RenderWindow & window) {
	score.setPosition(20, 12);
	sf::CircleShape bird(30);
	bird.setFillColor(sf::Color::Black);
	bird.setPosition(260, 410);
	float velocity = 0;
	bool canJump = true, isIncreased = false;
	score_ = 0;
	score.setString(sf::String(std::to_string(score_)));
	score.setFillColor(sf::Color::Black);
	score.setCharacterSize(40);
	std::vector<sf::RectangleShape> platform;
	platform.reserve(6);
	for (int i = 0; i < 3; i++) {
		float size = 100 + rand() % 600;
		platform.emplace_back(sf::RectangleShape(sf::Vector2f(80, size)));
		platform[2 * i].setPosition(480 + i * 320, 0);
		platform[2 * i].setFillColor(sf::Color(static_cast<int>(size) % 256, static_cast<int>(size) % 50, static_cast<int>(size) % 100));
		platform.emplace_back(sf::RectangleShape(sf::Vector2f(80, 700 - size)));
		platform[2 * i + 1].setPosition(480 + i * 320, size + 200);
		platform[2 * i + 1].setFillColor(sf::Color(static_cast<int>(size) % 256, static_cast<int>(size) % 50, static_cast<int>(size) % 100));
	}
	platform[0].setFillColor(sf::Color::White);
	platform[1].setFillColor(sf::Color::White);
	sf::Clock cl;
	while (window.isOpen()){
		float dTime = cl.restart().asSeconds();
		sf::Event evet;
		while (window.pollEvent(evet))
			if (evet.type == sf::Event::Closed) {
				window.close();
				gameState = 0;
				return;
			}
		if (!canJump && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) canJump = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump) {
			velocity = -500.0f;
			canJump = false;
		}
		if (isIncreased && platform[2].getPosition().x < 240) isIncreased = false;
		if (240 < platform[2].getPosition().x && platform[2].getPosition().x < 260 && !isIncreased) {
			score_++;
			score.setString(sf::String(std::to_string(score_)));
			isIncreased = true;
		}
		if (platform[0].getPosition().x < -160) {
			platform.erase(platform.begin(), platform.begin() + 2);
			float size = 100 + rand() % 600;
			platform.emplace_back(sf::RectangleShape(sf::Vector2f(80, size)));
			platform[4].setPosition(880, 0);
			platform[4].setFillColor(sf::Color(static_cast<int>(size) % 256, static_cast<int>(size) % 50, static_cast<int>(size) % 100));
			platform.emplace_back(sf::RectangleShape(sf::Vector2f(80, 700 - size)));
			platform[5].setPosition(880, size + 200);
			platform[5].setFillColor(sf::Color(static_cast<int>(size) % 256, static_cast<int>(size) % 50, static_cast<int>(size) % 100));
		}
		for (sf::RectangleShape& p : platform) p.move(sf::Vector2f(-211.0f * dTime, 0));
		if (platform[2].getGlobalBounds().intersects(bird.getGlobalBounds()) || platform[3].getGlobalBounds().intersects(bird.getGlobalBounds()) || bird.getPosition().y < 0 || bird.getPosition().y > 860) {
			gameState = 1;
			return;
		}
		velocity += 1281.0f * dTime;
		bird.move(sf::Vector2f(0, dTime * velocity));
		window.clear(sf::Color::White);
		for (sf::RectangleShape& p : platform) window.draw(p);
		window.draw(bird);
		window.draw(score);
		window.display();
	}
}
int main() {
	sf::RenderWindow window(sf::VideoMode(600, 900), "Efe Eren KAYA", sf::Style::Close);
	window.setFramerateLimit(360);
	font.loadFromFile("calibri.ttf");
	score.setFont(font);
	score.setString(sf::String(std::to_string(score_)));
	while (gameState)
		if (gameState == 2) Game(window);
		else Menu(window);
}