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
	VideoMode vIdeo;
	int x = vIdeo.getDesktopMode().width;
	int y = vIdeo.getDesktopMode().height;
	int interationCount = 0;
	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;

	if (m_state == CALCULATING)
	{
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; i < x; j++)
			{
				m_vArray[j + i * x].position = { float(j), float(i) };
				interationCount += countIterations(mapPixelToCoords(Vector2i(i,j)));
				iterationsToRGB(interationCount, r, g, b);
				m_vArray[j + i * x].color = { r,g,b };
			}

		}
		m_state = DISPLAYING;
	}
}

///private functions
int ComplexPlane::countIterations(Vector2f coord)
{
	complex<double> c = complex<double>(coord.x, coord.y);
	complex<double> z = c;
	int iterations = 0;
	while (abs(z) < 2.0 && iterations < MAX_ITER)
	{
		z = z * z + c;
		iterations++;
	}
	return iterations;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	if (count == MAX_ITER)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	else
	{
		//this is just to test if the pattern is being correctly colored. nothgin fancy yet.
		r = 255;
		g = 255;
		b = 255;
	}
}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	VideoMode videO;
	double h = videO.getDesktopMode().height;
	double w = videO.getDesktopMode().width;

	//[0, width] -> [m_plane_center.x - m_plane_size.x / 2.0, m_plane_size.x]
	float rx = ((mousePixel.x) / (w)) * (m_plane_size.x - (m_plane_center.x - (m_plane_size.x / 2.0))) + (m_plane_center.x - (m_plane_size.x / 2.0));
	//[0, height] -> [m_plane_center.y - m_plane_size.y / 2.0, m_plane_size.y]
	float ry = ((mousePixel.y) / (h)) * (m_plane_size.y - (m_plane_center.y - (m_plane_size.y / 2.0))) + (m_plane_center.y - (m_plane_size.y / 2.0));

	return { rx,ry };
}