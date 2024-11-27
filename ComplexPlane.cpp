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
	m_plane_center = ComplexPlane::mapPixelToCoords(mousePixel);
	m_state = CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
	m_mouseLocation = ComplexPlane::mapPixelToCoords(mousePixel);
}

void ComplexPlane::loadText(Text& text)
{
	stringstream ss; 
	ss << "Mandelbrot Set!!!!\n"
		<< "Center: (" << m_plane_center.x << ", " << m_plane_center.y << ")\n"
		<< "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")\n"
		<< "Left-click to zoom in\n"
		<< "Right click to zoom out";
	text.setString(ss.str());
}

void ComplexPlane::updateRender()
{
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
				coord = ComplexPlane::mapPixelToCoords({ j,i });
				iterCount = ComplexPlane::countIterations(coord);
				Uint8 r, g, b;
				ComplexPlane::iterationsToRGB(iterCount, r, g, b);
				m_vArray[j + i * pixelWidth].color = Color(r,g,b);
			}
			m_state = DISPLAYING;
		}
	}
}

///private functions
int ComplexPlane::countIterations(Vector2f coord)
{
	complex<float> c = complex<float>(coord.x, coord.y);
	int iterations = 0;
	for (complex<float> z; abs(z) <= 2 && iterations < MAX_ITER; ++iterations)
		z = z * z + c;
	return iterations;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	float delim = MAX_ITER / 6;
	if (count == MAX_ITER)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	if (count < delim * 6 - 1)
	{
		//red
		r = 255;
		g = 0;
		b = 0;
	}
	if (count < delim * 5)
	{
		//orange
		r = 255;
		g = 128;
		b = 0;
	}
	if (count < delim * 4)
	{
		//yellow
		r = 255;
		g = 255;
		b = 0;
	}
	if (count < delim * 3)
	{
		//green
		r = 0;
		g = 255;
		b = 0;
	}
	if (count < delim * 2)
	{
		//blue
		r = 0;
		g = 0;
		b = 255;
	}
	if (count < delim)
	{
		//purple (magenta but whatevs)
		r = 255;
		g = 0;
		b = 255;
	}
}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	float h = m_pixel_size.y;
	float w = m_pixel_size.x;
	Vector2f a = { 0, 0}; 
	Vector2f b = { w, h };
	float c1 = m_plane_center.x - m_plane_size.x / 2.0;
	float d1 = m_plane_center.x + m_plane_size.x / 2.0;
	float c2 = m_plane_center.y - m_plane_size.y / 2.0;
	float d2 = m_plane_center.y + m_plane_size.y / 2.0;
	//[0, width] -> [m_plane_center.x - m_plane_size.x / 2.0, m_plane_size.x]
	float rx = ((mousePixel.x - a.x) / (w - a.x)) * (d1 - c1) + c1;
	//[0, height] -> [m_plane_center.y - m_plane_size.y / 2.0, m_plane_size.y]
	float ry = ((mousePixel.y - h) / (a.y - h)) * (d2 - c2) + c2;

	return {rx,ry};
}