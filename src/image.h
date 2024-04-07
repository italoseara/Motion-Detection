#ifndef __image_h__
#define __image_h__

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
 * @brief Represents a pixel in an image.
 */
class Pixel
{
public:
  int r, g, b;

  /**
   * @brief Default constructor for the Pixel class.
   */
  Pixel();

  /**
   * @brief Constructs a Pixel object with the specified RGB values.
   *
   * @param r The red component of the pixel (0-255).
   * @param g The green component of the pixel (0-255).
   * @param b The blue component of the pixel (0-255).
   */
  Pixel(int r, int g, int b);

  /**
   * @brief Adds the RGB values of two pixels.
   *
   * @param other The pixel to add to this pixel.
   */
  Pixel operator+(Pixel &other);

  /**
   * @brief Subtracts the RGB values of two pixels.
   *
   * @param other The pixel to subtract from this pixel.
   */
  Pixel operator-(Pixel &other);

  /**
   * @brief Returns a string representation of the pixel.
   */
  string tostring();
};

/**
 * @brief Represents a .PPM image.
 */
class PPMImage
{
private:
  int width, height;
  int maxColor;

  Pixel **pixels;

public:
  /**
   * @brief Constructs a PPMImage object with the specified width, height, maximum color value, and pixel data.
   *
   * @param width The width of the image.
   * @param height The height of the image.
   * @param maxColor The maximum color value of the image.
   * @param pixels A 2D array of Pixel objects representing the pixel data of the image.
   */
  PPMImage(int width, int height, int maxColor, Pixel **pixels);

  /**
   * @brief Constructs a PPMImage object with the specified width, height, and maximum color value.
   *
   * @param width The width of the image.
   * @param height The height of the image.
   * @param maxColor The maximum color value of the image.
   */
  PPMImage(int width, int height, int maxColor);

  /**
   * @brief Constructs a PPMImage object from a PPM file.
   *
   * @param path The path to the PPM file.
   */
  PPMImage(string path);

  /**
   * @brief Destroys the PPMImage object.
   */
  ~PPMImage();

  /**
   * @brief Subtracts the pixel data of two images.
   *
   * Both images must have the same dimensions.
   *
   * @param other The image to subtract from this image.
   */
  PPMImage operator-(PPMImage &other);

  /**
   * @brief Normalizes the image to avoid overflow or underflow.
   */
  void normalize();

  /**
   * @brief Returns the width of the image.
   */
  int getWidth();

  /**
   * @brief Returns the height of the image.
   */
  int getHeight();

  /**
   * @brief Returns the maximum color value of the image.
   */
  int getMaxColor();

  /**
   * @brief Returns the pixel at the specified coordinates.
   *
   * @param x The x-coordinate of the pixel.
   * @param y The y-coordinate of the pixel.
   */
  Pixel getPixel(int x, int y);

  /**
   * @brief Sets the pixel at the specified coordinates.
   *
   * @param x The x-coordinate of the pixel.
   * @param y The y-coordinate of the pixel.
   * @param pixel The pixel to set.
   */
  void setPixel(int x, int y, Pixel pixel);

  /**
   * @brief Returns the pixel data of the image.
   */
  Pixel **getPixels();

  /**
   * @brief Saves the image to a PPM file.
   *
   * @param path The path to save the image to.
   */
  void save(string path);

  /**
   * @brief Returns a string representation of the image.
   */
  string tostring();
};

#endif // __image_h__