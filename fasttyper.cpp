#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>

unsigned int gameState = 1;
unsigned int level = 15;

void Game(sf::RenderWindow &window, sf::Font &calibri) {
	std::vector<sf::Text> texts;
	sf::String wordlist[] = {"abessives","abet","abetment","abetments","abets","abettal","abettals","abetted","abetter","abetters","abetting","abettor","abettors","abeyance","abeyances","abeyancies","abeyancy","abeyant","abfarad","abfarads","abhenries","abhenry","abhenrys","abhominable","abhor","abhorred","abhorrence","abhorrences","abhorrencies","abhorrency","abhorrent","abhorrently","abhorrer","abhorrers","abhorring","abhorrings","abhors","abid","abidance","abidances","abidden","abide","abided","abider","abiders","abides","abiding","abidingly","abidings","abies","abietic","abigail","abigails","abilities","ability","abiogeneses","abiogenesis","abiogenetic","abiogenetically","abiogenic","abiogenically","abiogenist","abiogenists","abiological","abioses","abiosis","abiotic","abiotically","abiotrophic","abiotrophies","abiotrophy","abirritant","abirritants","abirritate","abirritated","abirritates","abirritating","abitur","abiturient","abiturients","abiturs","abject","abjected","abjecting","abjection","abjections","abjectly","abjectness","abjectnesses","abjects","abjoint","abjointed","abjointing","abjoints","abjunction","abjunctions","abjuration","abjurations","abjure","abjured"};
	int count = sizeof(wordlist)/sizeof(wordlist[0]);
	texts.reserve(count);

	for (int i = 0; i < count; i++) {
		texts.emplace_back(sf::Text(wordlist[i], calibri, 30u));
		texts[i].setPosition(rand() % count*20 - count*20, rand() % 680 - 10);
	}

	sf::Text currentWordT("", calibri, 30);
	currentWordT.setFillColor(sf::Color::Black);

	sf::String currentWord = "";
	while (window.isOpen()) {
		if (!count) {
			gameState = 1;
			return;
		}

		sf::Event evt;

		while (window.pollEvent(evt)) {
			switch (evt.type) {
			case sf::Event::Closed:
				window.close();
				gameState = 0;
				break;

			case sf::Event::TextEntered:
				if (evt.text.unicode != 32){
					if (evt.text.unicode == 8){
						if(currentWord.getSize()) currentWord.erase(currentWord.getSize() - 1, 1);
					}else
						currentWord += evt.text.unicode;
				}else
					currentWord.clear();
				break;
			}
		}
		window.clear(sf::Color::Green);
		for (auto text = texts.begin(); text != texts.end(); ) {
			auto word = text->getString();
			if (word == currentWord) {
				text = texts.erase(text);
				currentWord = "";
				count--;
			}
			else {
				text->move(level / static_cast<float>(word.getSize()), 0);
				window.draw(*text);

				if (text->getPosition().x >= 850) {
					gameState = 3;
					return;
				}
				text++;
			}
		}
		currentWordT.setString(currentWord);
		window.draw(currentWordT);
		window.display();
	}
}

void Menu(sf::RenderWindow &window, sf::Font &font) {
	sf::Text title("zorluk seciniz", font, 50);
	sf::Text l1("ez", font, 30);
	sf::Text l2("norm", font, 30);
	sf::Text l3("hard", font, 30);
	title.setPosition(180, 300);
	l1.setPosition(140, 360);
	l2.setPosition(190, 360);
	l3.setPosition(310, 360);

	window.clear(sf::Color::Black);
	window.draw(title);
	window.draw(l1); window.draw(l3); window.draw(l2);
	window.display();
	while (window.isOpen()) {
		sf::Event evt;
		while (window.pollEvent(evt)) {
			switch (evt.type) {
			case sf::Event::Closed:
				window.close();
				gameState = 0;
				break;
			case sf::Event::MouseButtonPressed:
				if (l1.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
					level = 5;
					gameState = 2;
					return;
				}else if (l2.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
					level = 10;
					gameState = 2;
					return;
				}else if (l3.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
					level = 14;
					gameState = 2;
					return;
				}
				break;
			}
		}
	}
}

void Fail(sf::RenderWindow &window, sf::Font &font){
	sf::Text title("yenildin yavas", font, 50);
	sf::Text back("<- menu", font, 30);
	title.setPosition(180, 300);
	back.setPosition(140, 360);

	window.clear(sf::Color::Red);
	window.draw(title);
	window.draw(back);
	window.display();
	while (window.isOpen()) {
		sf::Event evt;
		while (window.pollEvent(evt)) {
			switch (evt.type) {
				case sf::Event::Closed:
					window.close();
					gameState = 0;
					break;
				case sf::Event::MouseButtonPressed:
					if (back.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
						gameState = 1;
						return;
					}
					break;
			}
		}
	}
}

int main() {
	srand((unsigned)time(0));
	sf::RenderWindow window(sf::VideoMode(900, 700), "fasttyper", sf::Style::Resize | sf::Style::Close);
	window.setFramerateLimit(30);
	
	sf::Font calibri;
	calibri.loadFromFile("calibri.ttf");

	while (gameState) {
		switch (gameState) {
		case 1:
			Menu(window, calibri);
			break;

		case 2:
			Game(window, calibri);
			break;
		case 3:
			Fail(window, calibri);
			break;
		}
	}
	
}