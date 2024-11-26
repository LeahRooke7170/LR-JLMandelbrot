#include"ComplexPlane.h"


int main()
{
	cout << "when the project compiles :D" << endl;
	cout << ">:)" << endl;

	VideoMode video;
	int screenH = video.getDesktopMode().height;
	int screenW = video.getDesktopMode().width;

	RenderWindow window(VideoMode(screenW, screenH), "opened");
	CircleShape cir(100.f);
	cir.setFillColor(sf::Color::Blue);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) { window.close(); }

			if (Keyboard::isKeyPressed(Keyboard::Escape)) { window.close(); }
		}


		window.clear();
		window.draw(cir);
		window.display();


	}
	return 0;
}
