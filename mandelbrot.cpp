#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

struct complex {
	double a, b;
};

complex cMult(complex num1, complex num2) {
	complex res = { num1.a * num2.a - num1.b * num2.b, num1.a * num2.b + num1.b * num2.a };
	return res;
}

complex cAdd(complex num1, complex num2) {
	complex res = { num1.a + num2.a, num1.b + num2.b };
	return res;
}

double cSize(complex num) {
	return sqrt(num.a*num.a + num.b*num.b);
}

bool tryNumber( complex num) {
	complex res = {0,0};
	for (int i = 0; i < 100; i++) {
		res = cAdd(cMult(res, res), num);
		if (cSize(res) > 2) return false;
	}
	return true;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(900, 700), "mandelbrot", sf::Style::Resize | sf::Style::Close);
	std::vector<sf::CircleShape> coordinates;
	coordinates.reserve(6141);

	std::cout << tryNumber({ 1, 0 });
	
	sf::Font calibri;
	calibri.loadFromFile("calibri.ttf");

	sf::Text m0("-2", calibri, 20);
	m0.setPosition(0, 350);
	sf::Text m1("-1", calibri, 20);
	m1.setPosition(300, 350);
	sf::Text m2("0", calibri, 20);
	m2.setPosition(600, 350);
	sf::Text m3("1", calibri, 20);
	m3.setPosition(890, 350);
	
	for (int y = 0; y < 70; y++)
	{
		for (int x = 0; x < 90; x++)
		{
			sf::CircleShape shape(3.f);
			shape.setPosition(x * 10+1.5, y * 10+1.5);

			complex coord = { x / 30.0f - 2.f , -y / 35.f  + 1};
			
			std::cout << coord.a << " + " << coord.b << "j \n";

			if(tryNumber(coord)) shape.setFillColor(sf::Color(100, 250, 50));
			else shape.setFillColor(sf::Color(0, 0, 0));
			coordinates.emplace_back(shape);
		}
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(0,0,0));
		for (int i = 0; i<90; i++)
		{
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(i*10, 0)),
				sf::Vertex(sf::Vector2f(i*10, 700))
			};
			
			if (i == 60) line[0].color = sf::Color(255, 0, 0);

			window.draw(line, 2, sf::Lines);
		}


		for (int i = 0; i < 70; i++)
		{
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(0, i * 10)),
				sf::Vertex(sf::Vector2f(900, i * 10))
			};

			line[0].color = sf::Color(255, 255, 0);
			if (i == 35) line[0].color = sf::Color(255, 0, 0);

			window.draw(line, 2, sf::Lines);
		}
		for (auto &coord : coordinates)
			window.draw(coord);
		window.draw(m0); window.draw(m1); window.draw(m2); window.draw(m3);
		window.display();
	}

	return 0;
}