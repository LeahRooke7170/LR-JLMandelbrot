#include"ComplexPlane.h"

///public functions
ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	//Leah
	m_pixel_size = { pixelWidth, pixelHeight };
	m_aspectRatio = float(pixelHeight) / float(pixelWidth);
	m_plane_center = { 0,0 };
	m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
	m_zoomCount = 0;
	m_state = State::CALCULATING;
	m_vArray.setPrimitiveType(Points);
	m_vArray.resize(pixelWidth * pixelHeight);
}

void ComplexPlane::draw(RenderTarget& target, RenderStates& states) const
{
	//Leah
	target.draw(m_vArray);
}

void ComplexPlane::zoomIn()
{
	//Leah
	m_zoomCount++;
	double x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	double y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = { x,y };
	m_state = CALCULATING;
}

void ComplexPlane::zoomOut()
{
	//Leah
	m_zoomCount--;
	double x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	double y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = { x,y };
	m_state = CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel)
{
	//Leah
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
	//Leah
}

void ComplexPlane::loadText(Text& text)
{
	//Leah
}

void ComplexPlane::updateRender()
{
	//Jeremy
}

///private functions
int ComplexPlane::countIterations(Vector2f coord)
{
	//Jeremy
	return 0;
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