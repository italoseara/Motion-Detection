#include <iostream>
#include <string>
#include "image.h"

using namespace std;

int main(int argc, char const *argv[])
{
  PPMImage image("img/lena.ppm");
  cout << image.tostring() << endl;
  return 0;
}
