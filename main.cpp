#include"ComplexPlane.h"


int main()
{
	cout << "when the project compiles :D" << endl;
	cout << ">:)" << endl;

	VideoMode video(1920, 1080);
	int screenH = video.getDesktopMode().height;
	int screenW = video.getDesktopMode().width;

	RenderWindow window(video, "Mandelbrot set");
	CircleShape cir(100.f);
	cir.setFillColor(sf::Color::Blue);
	ComplexPlane cPlane(screenW, screenH);
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
				cPlane.zoomIn();
			}
			if (event.mouseButton.button == Mouse::Right)
			{
				cout << "!(LEFT CLICK)" << endl;
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
