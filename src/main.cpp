#include <iostream>
#include <string>
#include <random>

#include "image.h"

using namespace std;

/**
 * Usage:
 * ./main <image1.ppm> <image2.ppm> <threshold>
 */
int main(int argc, char const *argv[])
{
  if (argc != 4)
  {
    cout << endl;
    cout << "Usage: " << (char *)argv[0] << " <image1.ppm> <image2.ppm> <threshold>" << endl;
    cout << endl;
    return 1;
  }

  string image1_path = argv[1];
  string image2_path = argv[2];
  int threshold = stoi(argv[3]);

  PPMImage image1(image1_path);
  PPMImage image2(image2_path);
  PPMImage result = image1 - image2;

  PPMImage normalized = result.clone();
  normalized.normalize(threshold);
  normalized.save("img/normalized.ppm");

  PPMImage segmented = result.clone();
  segmented.segment(threshold);
  segmented.save("img/segmented.ppm");
  return 0;
}
