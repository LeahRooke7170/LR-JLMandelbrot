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
	ComplexPlane cPlane(screenW, screenH);


	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) { window.close(); }

			if (Keyboard::isKeyPressed(Keyboard::Escape)) { window.close(); }

			if (event.mouseButton.button == Mouse::Left)
			{
				cout << "LEFT CLICK" << endl;
			}
			if (event.mouseButton.button == Mouse::Right)
			{
				cout << "!(LEFT CLICK)" << endl;
			}
			if (event.MouseMoved)
			{
				cout << "moved" << endl;
			}
		}

		///YUPDATE

		cPlane.updateRender();
		//jeremy.loadText (WHEN DONE)

		///DRAWER
		window.clear();
		//cPlane.draw(window);
		//window.draw(TEXTS);
		window.display();


	}
	return 0;
}
