#include "image.h"

Pixel::Pixel() : r(0), g(0), b(0) {}

Pixel::Pixel(int r, int g, int b) : r(r), g(g), b(b)
{
  if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    throw invalid_argument("Error: Invalid RGB values");
}

Pixel Pixel::operator+(Pixel &other)
{
  return Pixel(r + other.r, g + other.g, b + other.b);
}

Pixel Pixel::operator-(Pixel &other)
{
  return Pixel(r - other.r, g - other.g, b - other.b);
}

string Pixel::tostring()
{
  return to_string(r) + " " + to_string(g) + " " + to_string(b);
}

PPMImage::PPMImage(int width, int height, int maxColor, Pixel **pixels)
    : width(width), height(height), maxColor(maxColor), pixels(pixels) {}

PPMImage::PPMImage(string path)
{
  // Open file
  ifstream file(path);
  if (!file.is_open())
    throw invalid_argument("Error: Could not open file " + path);

  // Read header
  string format;
  file >> format;
  if (format != "P3")
    throw invalid_argument("Error: Invalid file format");

  file >> width >> height >> maxColor;

  // Allocate memory
  pixels = new Pixel *[height];
  for (int i = 0; i < height; i++)
    pixels[i] = new Pixel[width];

  // Read pixels
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      file >> pixels[i][j].r >> pixels[i][j].g >> pixels[i][j].b;

  // Close file
  file.close();
}

PPMImage::~PPMImage()
{
  for (int i = 0; i < height; i++)
    delete[] pixels[i];
  delete[] pixels;
}

int PPMImage::getWidth()
{
  return width;
}

int PPMImage::getHeight()
{
  return height;
}

int PPMImage::getMaxColor()
{
  return maxColor;
}

Pixel PPMImage::getPixel(int x, int y)
{
  return pixels[y][x];
}

void PPMImage::save(string path)
{
  ofstream file(path);
  file << tostring();
  file.close();
}

string PPMImage::tostring()
{
  string str = "P3\n";
  str += to_string(width) + " " + to_string(height) + "\n";
  str += to_string(maxColor) + "\n";

  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      str += pixels[i][j].tostring() + " ";

  return str;
}