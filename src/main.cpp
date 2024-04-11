#include <iostream>
#include <string>
#include <random>

#include "image.h"

using namespace std;

/**
 * Usage:
 * ./main <image1.ppm> <image2.ppm> <tolerance>
 */
int main(int argc, char const *argv[])
{
  if (argc != 4)
  {
    cout << endl;
    cout << "Usage: " << (char *)argv[0] << " <image1.ppm> <image2.ppm> <tolerance>" << endl;
    cout << endl;
    return 1;
  }

  string image1_path = argv[1];
  string image2_path = argv[2];
  int tolerance = stoi(argv[3]);

  PPMImage image1(image1_path);
  PPMImage image2(image2_path);
  PPMImage result = image1 - image2;

  PPMImage segmented = result.clone();
  segmented.segment(tolerance);

  PPMImage normalized = result.clone();
  normalized.normalize(tolerance);

  segmented.save("img/segmented.ppm");
  normalized.save("img/normalized.ppm");

  return 0;
}
