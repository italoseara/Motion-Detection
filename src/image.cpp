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
  bool underflow = false;
  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; j++)
    {
      // Subtract pixels
      Pixel pixel = pixels[i][j] - other.pixels[i][j];
      newPixels[i][j] = pixel;

      // Check for underflow
      underflow = underflow || pixel.r < 0 || pixel.g < 0 || pixel.b < 0;
    }
  }

  PPMImage newImage(width, height, maxColor, newPixels);

  // Normalize if there is underflow
  if (underflow)
    newImage.normalize();

  return newImage;
}

void PPMImage::normalize()
{
  // Get the min and max values for each channel
  int minR = __INT_MAX__, minG = __INT_MAX__, minB = __INT_MAX__;
  int maxR = 0, maxG = 0, maxB = 0;

  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; j++)
    {
      Pixel pixel = pixels[i][j];

      // Update min and max values
      minR = pixel.r < minR ? pixel.r : minR;
      minG = pixel.g < minG ? pixel.g : minG;
      minB = pixel.b < minB ? pixel.b : minB;

      maxR = pixel.r > maxR ? pixel.r : maxR;
      maxG = pixel.g > maxG ? pixel.g : maxG;
      maxB = pixel.b > maxB ? pixel.b : maxB;
    }
  }

  // Applies the normalization
  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; j++)
    {
      Pixel pixel = pixels[i][j];

      pixel.r = (pixel.r - minR) * maxColor / (maxR - minR);
      pixel.g = (pixel.g - minG) * maxColor / (maxG - minG);
      pixel.b = (pixel.b - minB) * maxColor / (maxB - minB);

      pixels[i][j] = pixel;
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
  return pixels[y][x];
}

void PPMImage::setPixel(int x, int y, Pixel pixel)
{
  pixels[y][x] = pixel;
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