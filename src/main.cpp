#include <iostream>
#include <string>
#include <random>
#include "image.h"

using namespace std;

PPMImage randomImage(int width, int height, int maxColor);

int main(int argc, char const *argv[])
{

  PPMImage image("img/lena.ppm");
  PPMImage noise = randomImage(image.getWidth(), image.getHeight(), image.getMaxColor());

  PPMImage result = image - noise;
  result.save("img/result.ppm");

  return 0;
}

PPMImage randomImage(int width, int height, int maxColor)
{
  PPMImage image(width, height, maxColor);

  for (int i = 0; i < image.getHeight(); i++)
  {
    for (int j = 0; j < image.getWidth(); j++)
    {
      Pixel pixel = image.getPixel(i, j);
      pixel.r = rand() % 256;
      pixel.g = rand() % 256;
      pixel.b = rand() % 256;
      image.setPixel(i, j, pixel);
    }
  }

  image.save("img/random.ppm");
  return image;
}