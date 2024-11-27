#include"ComplexPlane.h"


int main()
{
	cout << "when the project compiles :D" << endl;
	cout << ">:)" << endl;

	VideoMode video(1920,1080);
	int screenH = video.getDesktopMode().height;
	int screenW = video.getDesktopMode().width;

	RenderWindow window(video, "Mandelbrot set");
	ComplexPlane cPlane(1920,1080);
	RenderStates state;

	Font font;
	font.loadFromFile("ComicSansMS.ttf");
	Text text;
	text.setFont(font);
	text.setColor(Color::White);
	text.setCharacterSize(25);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) { window.close(); }

			if (Keyboard::isKeyPressed(Keyboard::Escape)) { window.close(); }

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					cout << "left click" << endl;
					cPlane.setCenter({ event.mouseButton.x, event.mouseButton.y });
					cPlane.zoomIn();
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					cout << "right click" << endl;
					cPlane.setCenter({ event.mouseButton.x, event.mouseButton.y });
					cPlane.zoomOut();
				}
			}
			if (event.MouseMoved)
			{
				cPlane.setMouseLocation(Vector2i(event.mouseButton.x, event.mouseButton.y));
			}
		}

		///YUPDATE

		thread t1(&ComplexPlane::updateRender, &cPlane);
		//cPlane.updateRender();
		t1.join();
		cPlane.loadText(text);

		///DRAWER
		window.clear();
		cPlane.draw(window, state);
		window.draw(text);
		window.display();


	}
	return 0;
}
