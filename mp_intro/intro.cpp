#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>

using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
	PNG image; 
	image.readFromFile(inputFile);
	PNG newImage(image.width(), image.height());
	for (unsigned int x = 0; x < image.width(); x++) {
		for (unsigned int y = 0; y < image.height(); y++) {
			newImage.getPixel(x, y) = image.getPixel(image.width() - 1 - x, image.height() - 1 - y);
		}
	}
	newImage.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  for (unsigned int x = 0; x < width; x++) {
	  for (unsigned int y = 0; y < height; y++) {
		  HSLAPixel& pixel = png.getPixel(x, y);
		  if (x % 4 == 0 || y % 4 == 0) {
			  HSLAPixel* newPixel = new HSLAPixel(242, 1, 0.52, 1);
			  pixel = *newPixel;
		  }
		  else if (x % 4 == 1 || y % 4 == 1) {
			  HSLAPixel* newPixel = new HSLAPixel(136, 1, 0.4, 1);
			  pixel = *newPixel;
		  }
		  else if (x % 4 == 2 || y % 4 == 2) {
			  HSLAPixel* newPixel = new HSLAPixel(305, 1, 0.4, 1);
			  pixel = *newPixel;
		  } else {
			  HSLAPixel* newPixel = new HSLAPixel(30, 1, 0.4, 1);
			  pixel = *newPixel;
		  }
	  }
  }

  return png;
}
