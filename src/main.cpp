#include <iostream>
#include <string>
#include <random>

#include "image.h"

using namespace std;

int main(int argc, char const *argv[])
{
  PPMImage background("img/background.ppm");
  PPMImage movement("img/movement.ppm");

  PPMImage result = movement - background;

  PPMImage segmented = result.clone();
  segmented.segment(50);

  PPMImage normalized = result.clone();
  normalized.normalize();

  segmented.save("img/segmented.ppm");
  normalized.save("img/normalized.ppm");

  return 0;
}
