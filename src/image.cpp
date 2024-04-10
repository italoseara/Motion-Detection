#include "image.h"

Pixel::Pixel() : r(0), g(0), b(0) {}

Pixel::Pixel(int r, int g, int b) : r(r), g(g), b(b) {}

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

PPMImage::PPMImage(int width, int height, int maxColor)
    : width(width), height(height), maxColor(maxColor)
{
  // Allocate memory
  pixels = new Pixel *[height];
  for (int i = 0; i < height; i++)
    pixels[i] = new Pixel[width];
}

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

PPMImage PPMImage::operator-(PPMImage &other)
{
  if (width != other.width || height != other.height)
    throw invalid_argument("Error: Can't subtract images of different dimentions");

  // Allocate memory for the new pixels
  Pixel **newPixels = new Pixel *[height];
  for (int i = 0; i < height; i++)
    newPixels[i] = new Pixel[width];

  // Operates in each pixel
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      // Subtract pixels
      Pixel pixel = pixels[i][j] - other.pixels[i][j];
      newPixels[i][j] = pixel;
    }
  }

  PPMImage newImage(width, height, maxColor, newPixels);
  return newImage;
}

void PPMImage::normalize()
{
  // Applies the normalization
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      Pixel pixel = pixels[i][j];

      pixel.r += 255;
      pixel.r /= 2;

      pixel.g += 255;
      pixel.g /= 2;

      pixel.b += 255;
      pixel.b /= 2;

      pixels[i][j] = pixel;
    }
  }
}

void PPMImage::segment(int tolerance)
{
  // Get the average pixel
  Pixel avgPixel;
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      avgPixel = avgPixel + pixels[i][j];
  avgPixel.r /= width * height;
  avgPixel.g /= width * height;
  avgPixel.b /= width * height;

  // Segment the image
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      Pixel pixel = pixels[i][j];

      // Calculate the distance between the pixel and the average pixel
      int distance = abs(pixel.r - avgPixel.r) + abs(pixel.g - avgPixel.g) + abs(pixel.b - avgPixel.b);

      // If the distance is less than the tolerance, set the pixel to black
      if (distance < tolerance)
        pixels[i][j] = Pixel(0, 0, 0);
      else
        pixels[i][j] = Pixel(255, 255, 255);
    }
  }
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
  return pixels[x][y];
}

void PPMImage::setPixel(int x, int y, Pixel pixel)
{
  pixels[x][y] = pixel;
}

Pixel **PPMImage::getPixels()
{
  return pixels;
}

void PPMImage::save(string path)
{
  ofstream file(path);
  file << tostring();
  file.close();
}

PPMImage PPMImage::clone()
{
  // Allocate memory for the new pixels
  Pixel **newPixels = new Pixel *[height];
  for (int i = 0; i < height; i++)
    newPixels[i] = new Pixel[width];

  // Copy the pixels
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      newPixels[i][j] = pixels[i][j];

  PPMImage newImage(width, height, maxColor, newPixels);
  return newImage;
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