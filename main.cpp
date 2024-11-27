#include"ComplexPlane.h"


int main()
{
	cout << "when the project compiles :D" << endl;
	cout << ">:)" << endl;

	VideoMode video(500, 400);
	int screenH = video.getDesktopMode().height;
	int screenW = video.getDesktopMode().width;

	RenderWindow window(video, "Mandelbrot set");
	CircleShape cir(100.f);
	cir.setFillColor(sf::Color::Blue);
	ComplexPlane cPlane(500, 400);
	RenderStates state;


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
				cPlane.setCenter({event.mouseButton.x, event.mouseButton.y });
				cPlane.zoomIn();
			}
			if (event.mouseButton.button == Mouse::Right)
			{
				cout << "!(LEFT CLICK)" << endl;
				cPlane.setCenter({event.mouseButton.x, event.mouseButton.y});
				cPlane.zoomOut();
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
		cPlane.draw(window, state);
		//window.draw(TEXTS);
		window.display();


	}
	return 0;
}
