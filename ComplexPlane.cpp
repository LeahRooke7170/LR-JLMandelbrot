#include"ComplexPlane.h"

///public functions
ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_pixel_size = { pixelWidth, pixelHeight };
	m_aspectRatio = double(pixelHeight) / double(pixelWidth);
	m_plane_center = { 0,0 };
	m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
	m_zoomCount = 0;
	m_state = State::CALCULATING;
	m_vArray.setPrimitiveType(Points);
	m_vArray.resize(pixelWidth * pixelHeight);
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	float x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	float y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = { x,y };
	m_state = CALCULATING;
}

void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	float x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	float y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = { x,y };
	m_state = CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel)
{
	m_state = CALCULATING;
	m_plane_center = mapPixelToCoords(mousePixel);
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
	m_mouseLocation = mapPixelToCoords(mousePixel);
}

void ComplexPlane::loadText(Text& text)
{
	stringstream os; 
	os << "Mandelbrot Set!!!!\n"
		<< "Center: (" << m_plane_center.x << ", " << m_plane_center.y << ")\n"
		<< "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")\n"
		<< "Left-click to zoom in\n"
		<< "Right click to zoom out";
	Font font;
	font.loadFromFile("ComicSansMS.ttf");
	text.setString(os.str());
	text.setFont(font);
	text.setFillColor(Color::Green);
}

void ComplexPlane::updateRender()
{
	/*VideoMode video;
	int x = video.getDesktopMode().width;
	int y = video.getDesktopMode().height;
	int iterationCount = 0;
	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;

	if (m_state == CALCULATING)
	{
		for (int i = 0; i < m_pixel_size.y; i++)
		{
			for (int j = 0; j < m_pixel_size.x; j++)
			{
				m_vArray[j + i * m_pixel_size.x].position = { (float)j, (float)i };
				iterationCount = countIterations(mapPixelToCoords(Vector2i(i,j)));
				iterationsToRGB(iterationCount, r, g, b);
				m_vArray[j + i * m_pixel_size.x].color = { r,g,b };
			}
		}
	}
	m_state = DISPLAYING;*/

	int pixelHeight = m_pixel_size.y;
	int pixelWidth = m_pixel_size.x;
	int iterCount = 0;
	Vector2f coord;

	if (m_state == CALCULATING)
	{
		for (int i = 0; i < pixelHeight; i++)
		{
			for (int j = 0; j < pixelWidth; j++)
			{
				m_vArray[j + i * pixelWidth].position = { float(j), float(i) };
				coord = mapPixelToCoords({ j,i });
				iterCount = countIterations(coord);
				Uint8 r, g, b;
				iterationsToRGB(iterCount, r, g, b);
				m_vArray[j + i * pixelWidth].color = { r,g,b };
				cout << m_vArray[j + i * pixelWidth].position.x << " " << m_vArray[j + i * pixelWidth].position.y << endl;
			}
			m_state = DISPLAYING;
		}
	}
}

///private functions
int ComplexPlane::countIterations(Vector2f coord)
{
	/*complex<double> c = complex<double>(coord.x, coord.y);
	cout << c.real() << " " << c.imag() << endl;
	complex<double> z = c;
	int iterations = 0;
	while (abs(z) < 2.0 && iterations < MAX_ITER)
	{
		z = z * z + c;
		iterations++;
	}
	cout << iterations << endl;
	return iterations;*/
	complex<float> c = complex<float>(coord.x, coord.y);
	int iterations = 0;
	for (complex<float> z; abs(z) <= 2 && iterations < MAX_ITER; ++iterations)
		z = z * z + c;
	return iterations;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	cout << count << endl;
	if (count == MAX_ITER)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	else if (count < 16)
	{
		//this is just to test if the pattern is being correctly colored. nothgin fancy yet.
		r = MAX_ITER;
		g = MAX_ITER;
		b = MAX_ITER;
	}
	else if (count < 32)
	{
		r = MAX_ITER * 2;
		g = MAX_ITER * 2;
		b = MAX_ITER * 2;
	}
	else if (count < 48)
	{
		r = MAX_ITER * 3;
		g = MAX_ITER * 3;
		b = MAX_ITER * 3;
	}
	else
	{
		r = 200;
		g = 0;
		b = MAX_ITER;
	}
	if (count == 0 || count == 1)
	{
		r = 255;
		g = 0;
		b = 0;
	}
}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	VideoMode videO;
	float h = videO.getDesktopMode().height;
	float w = videO.getDesktopMode().width;

	//[a, b] for the x [0, 1920]
	//[a, b] for the y [0, 1080]

	Vector2f a = { 0, 0 }; 
	Vector2f b = { w, h };
	//Vector2f c = { (m_plane_center.x - (m_plane_size.x / 2.0)),(m_plane_center.y - (m_plane_size.y / 2.0)) };
	//Vector2f d = { (m_plane_center.x + (m_plane_size.x / 2.0)),(m_plane_center.y + (m_plane_size.y / 2.0)) };
	//[0, width] -> [m_plane_center.x - m_plane_size.x / 2.0, m_plane_size.x]
	float rx = ((mousePixel.x) / (m_pixel_size.x)) * (m_plane_size.x - (m_plane_center.x - (m_plane_size.x / 2.0))) + (m_plane_center.x - (m_plane_size.x / 2.0));
	//[0, height] -> [m_plane_center.y - m_plane_size.y / 2.0, m_plane_size.y]
	float ry = ((mousePixel.y - a.y) / (b.y - a.y)) * ((m_plane_center.y + (m_plane_size.y / 2.0)) - (m_plane_center.y - (m_plane_size.y / 2.0)) + (m_plane_center.y - (m_plane_size.y / 2.0)));
	
	//comment

	return { rx,ry };
}