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

void ComplexPlane::draw(RenderTarget& target, RenderStates& states) const
{
	target.draw(m_vArray);
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	double x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	double y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = { x,y };
	m_state = CALCULATING;
}

void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	double x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	double y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = { x,y };
	m_state = CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel)
{
	//Jeremy
	//this one corresponds with mapPixelToCoords
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
	//Jeremy
	//this one also corresponds with mapPixelToCoords
}

void ComplexPlane::loadText(Text& text)
{
	//Leah
	stringstream os; 
}

void ComplexPlane::updateRender()
{
	//Jeremy
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
	//Leah
}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	//Jeremy
	return { 0,0 };
}