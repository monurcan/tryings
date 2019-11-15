#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include <functional>

constexpr float PI = 3.14159;
#define PERIOD 1000
sf::Vector2f img[PERIOD];

class Button {
private:
	sf::Text circleSwitch, circleOff;
	sf::RectangleShape circleOffBg;
	bool showCirclesChanged;
public:
	static int numberOfButtons;
	// type | 0=switch, 1=button
	Button(const sf::Font &calibri, const bool type, const char* text):
		circleSwitch(text, calibri, 15),
		circleOff("x", calibri, 15),
		circleOffBg({ 15, 15 })
	{
		circleSwitch.setPosition(710, 11 + numberOfButtons * 22);
		if (type == 0) {
			circleOff.setPosition(690, 10 + numberOfButtons * 22);
			circleOff.setStyle(sf::Text::Bold);

			circleOffBg.setPosition(686, 14 + numberOfButtons * 22);
			circleOffBg.setFillColor(sf::Color::Transparent);
			circleOffBg.setOutlineColor(sf::Color::White);
			circleOffBg.setOutlineThickness(1);
		}
		else {
			circleOff.setPosition(-99, -99);
			circleOffBg.setPosition(-99, -99);
		}
		showCirclesChanged = 0;
		numberOfButtons++;
	}

	void draw(sf::RenderWindow &window, sf::Event event, std::function<void()> onClick, bool isOn = true) {
		if (event.type == sf::Event::MouseButtonReleased)
			showCirclesChanged = 0;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !showCirclesChanged) {
			sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			if (circleSwitch.getGlobalBounds().contains(mouse) || circleOffBg.getGlobalBounds().contains(mouse)) {
				onClick();
				showCirclesChanged = 1;
			}
		}

		if (isOn) window.draw(circleOff);
		window.draw(circleSwitch);
		window.draw(circleOffBg);
	}
};

int Button::numberOfButtons = 0;

sf::Vector2f convertCoord2Window(sf::Vector2f coord) {
	return { (coord.x + 2) * 200, (2-coord.y)*200};
}

sf::Vector2f convertWindow2Coord(sf::Vector2f coord) {
	return { coord.x / 200 - 2, -coord.y / 200 + 2 };
}

sf::Vector2f polar2Cartesian(sf::Vector2f polar) {
	return {polar.x * cos(polar.y), polar.x * sin(polar.y) };
}
sf::Vector2f cartesian2Polar(sf::Vector2f polar) {
	float phase = atanf(polar.y / polar.x);

	if(polar.x / fabs(polar.x) < 0)
		if (polar.y / fabs(polar.y) < 0)
			phase -= PI; 
		else
			phase += PI;

	return { sqrt(polar.x * polar.x + polar.y * polar.y), phase};
}

void drawYourShape() {
	sf::RenderWindow window(sf::VideoMode(800, 800), "fourier | draw your shape", sf::Style::Resize | sf::Style::Close);
	std::list<sf::CircleShape> pastPoints;

	sf::Font calibri;
	calibri.loadFromFile("calibri.ttf");

	sf::Text m0("-2", calibri, 15);
	m0.setPosition(0, 400);
	sf::Text m1("-1", calibri, 15);
	m1.setPosition(200, 400);
	sf::Text m2("0", calibri, 15);
	m2.setPosition(400, 400);
	sf::Text m3("1", calibri, 15);
	m3.setPosition(600, 400);
	sf::Text m4("2", calibri, 15);
	m4.setPosition(790, 400);
	sf::Text m5("2", calibri, 15);
	m5.setPosition(400, 0);
	sf::Text m6("1", calibri, 15);
	m6.setPosition(400, 200);
	sf::Text m7("-1", calibri, 15);
	m7.setPosition(400, 600);
	sf::Text m8("-2", calibri, 15);
	m8.setPosition(400, 780);

	float t = 0, dt = 0.1f;
	int img_t = 0;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(0, 0, 0));
		for (int i = 0; i < 80; i++)
		{
			sf::Vertex linex[] =
			{
				sf::Vertex(sf::Vector2f(i * 10, 0), sf::Color(73, 73, 73)),
				sf::Vertex(sf::Vector2f(i * 10, 800), sf::Color(73, 73, 73))
			}, liney[] =
			{
				sf::Vertex(sf::Vector2f(0, i * 10), sf::Color(73, 73, 73)),
				sf::Vertex(sf::Vector2f(800, i * 10), sf::Color(73, 73, 73))
			};

			if (i == 40) {
				linex[0].color = sf::Color(123, 123, 123);
				liney[0].color = sf::Color(123, 123, 123);
			}

			window.draw(linex, 2, sf::Lines);
			window.draw(liney, 2, sf::Lines);
		}

		sf::CircleShape point(1.2);
		point.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		constexpr int sampling_slowness = 5;
		if (t >= (dt * sampling_slowness)) {
			t = 0;
			pastPoints.emplace_back(point);
			img[img_t++] = convertWindow2Coord(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
			if (img_t == PERIOD) return;
		}

		for (auto &point_ : pastPoints)
			window.draw(point_);
		
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) t += dt;

		window.draw(m0); window.draw(m1); window.draw(m2); window.draw(m3); window.draw(m4); window.draw(m5); window.draw(m6); window.draw(m7); window.draw(m8);
		window.display();
	}
}

void drawCircle(sf::RenderWindow &window, sf::Vector2f origin, float magnitude) {
	sf::CircleShape shape(magnitude);
	shape.setOrigin(magnitude, magnitude);
	shape.setOutlineColor(sf::Color(150, 150, 150));
	shape.setFillColor(sf::Color::Transparent);
	shape.setPosition(origin);
	shape.setOutlineThickness(1);
	window.draw(shape);
}

// get input in polar form for vec, but returns in cartesian form
sf::Vector2f drawVector(sf::RenderWindow &window, const sf::Vector2f origin, const sf::Vector2f vec, bool showCircles) {
	sf::Vertex vect[] =
	{
		sf::Vertex(convertCoord2Window(origin), sf::Color(255, 255, 0)),
		sf::Vertex(convertCoord2Window(origin+polar2Cartesian(vec)), sf::Color(255, 255, 0))
	};

	if(showCircles) drawCircle(window, convertCoord2Window(origin), vec.x * 200);
	window.draw(vect, 2, sf::Lines);
	return polar2Cartesian(vec);
}

// returns magnitude and phase of a_k's
std::vector<sf::Vector2f> fourierCoeff(const int T, const int numberofCoeffs) {
	//#define PERIOD 100
	//sf::Vector2f img[PERIOD];
	//for (int i = 0; i < PERIOD; i++)
	//	img[i] = { i * 2.f / PERIOD, i * 2.f / PERIOD };
	//
	std::vector<sf::Vector2f> res;
	res.reserve(numberofCoeffs);
	for (int k = 0; k < numberofCoeffs; k++){
		int realk = k - numberofCoeffs / 2;
		sf::Vector2f sum(0, 0);
		for (int t = 0; t < T; t++)
			sum += sf::Vector2f(
				cos(realk * 2 * PI / T * t)*img[t*PERIOD/T].x + sin(realk * 2 * PI / T * t)*img[t*PERIOD/T].y,
				-sin(realk * 2 * PI / T * t)*img[t*PERIOD/T].x + cos(realk * 2 * PI / T * t)*img[t*PERIOD/T].y
			);
		
		res.emplace_back(cartesian2Polar(sf::Vector2f( sum.x / T, sum.y / T )));
	}

	return res;
}

int main() {
	drawYourShape();

	sf::RenderWindow window(sf::VideoMode(800, 800), "fourier", sf::Style::Resize | sf::Style::Close);
	std::list<sf::CircleShape> pastPoints;
	
	sf::Font calibri;
	calibri.loadFromFile("calibri.ttf");

	sf::Text m0("-2", calibri, 15);
	m0.setPosition(0, 400);
	sf::Text m1("-1", calibri, 15);
	m1.setPosition(200, 400);
	sf::Text m2("0", calibri, 15);
	m2.setPosition(400, 400);
	sf::Text m3("1", calibri, 15);
	m3.setPosition(600, 400);
	sf::Text m4("2", calibri, 15);
	m4.setPosition(790, 400);
	sf::Text m5("2", calibri, 15);
	m5.setPosition(400, 0);
	sf::Text m6("1", calibri, 15);
	m6.setPosition(400, 200);
	sf::Text m7("-1", calibri, 15);
	m7.setPosition(400, 600);
	sf::Text m8("-2", calibri, 15);
	m8.setPosition(400, 780);

	bool showCircles = 0;

	Button showCircleButton(calibri, 0, "Show Circles"),
		speedUp(calibri, 1, "Faster!"),
		slowDown(calibri, 1, "Slower!"),
		drawShape(calibri, 1, "Draw A Shape");

	float t = 0,
		dt = 0.1f,
		T = PERIOD;
	int trace = 400;

	int numberofCoeffs = 11; // odd
	std::vector<sf::Vector2f> a_k = fourierCoeff(T, numberofCoeffs);

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(0, 0, 0));
		for (int i = 0; i < 80; i++)
		{
			sf::Vertex linex[] =
			{
				sf::Vertex(sf::Vector2f(i * 10, 0), sf::Color(73, 73, 73)),
				sf::Vertex(sf::Vector2f(i * 10, 800), sf::Color(73, 73, 73))
			}, liney[] =
			{
				sf::Vertex(sf::Vector2f(0, i * 10), sf::Color(73, 73, 73)),
				sf::Vertex(sf::Vector2f(800, i * 10), sf::Color(73, 73, 73))
			};

			if (i == 40) {
				linex[0].color = sf::Color(123, 123, 123);
				liney[0].color = sf::Color(123, 123, 123);
			}

			window.draw(linex, 2, sf::Lines);
			window.draw(liney, 2, sf::Lines);
		}

		t += dt;

		sf::Vector2f origin = { 0,0 };

		for(int k = 0; k < numberofCoeffs; k++)
			origin += drawVector(window, origin, { a_k[k].x, a_k[k].y + (k-numberofCoeffs/2) * 2 * PI / T * t }, showCircles);
		
		sf::CircleShape point(1.2);
		point.setPosition(convertCoord2Window(origin));
		pastPoints.emplace_back(point);

		if (t > trace * dt) {
			auto it = pastPoints.begin();
			if (trace > 200) {
				for (int i = 0; i < 50; i++) {
					it->setFillColor(sf::Color(100, 100, 100));
					std::advance(it, 1);
				}
				for (int i = 0; i < 100; i++) {
					it->setFillColor(sf::Color(170, 170, 170));
					std::advance(it, 1);
				}
			}
			pastPoints.pop_front(); 
		}

		for (auto &point_ : pastPoints)
			window.draw(point_);

		window.draw(m0); window.draw(m1); window.draw(m2); window.draw(m3); window.draw(m4); window.draw(m5); window.draw(m6); window.draw(m7); window.draw(m8); 

		showCircleButton.draw(window, event, [&showCircles]() {showCircles = !showCircles; }, showCircles);

		speedUp.draw(window, event, [&dt]() { dt *= 2; });
		slowDown.draw(window, event, [&dt]() { dt /= 2; });
		drawShape.draw(window, event, [&a_k, T, numberofCoeffs]() {drawYourShape(); a_k = fourierCoeff(T, numberofCoeffs); });

		window.display();
	}

	return 0;
}
