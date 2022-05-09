#include "Image.h"

void Image::lighten() {
	for (unsigned i = 0; i < width(); i++) {
		for (unsigned j = 0; j < height(); j++) {
			HSLAPixel& pixel = getPixel(i, j);
			if (pixel.l + 0.1 >= 1.0) {
				pixel.l = 1.0;
			}
			else {
				pixel.l += 0.1;
			}
		}
	}
}

void Image::lighten(double amount) {
	for (unsigned i = 0; i < width(); i++) {
		for (unsigned j = 0; j < height(); j++) {
			HSLAPixel& pixel = getPixel(i, j);
			if (pixel.l + amount >= 1.0) {
				pixel.l = 1.0;
			}
			else {
				pixel.l += amount;
			}
		}
	}
}

void Image::darken() {
	for (unsigned i = 0; i < width(); i++) {
		for (unsigned j = 0; j < height(); j++) {
			HSLAPixel& pixel = getPixel(i, j);
			if (pixel.l - 0.1 <= 0) {
				pixel.l = 0;
			}
			else {
				pixel.l -= 0.1;
			}
		}
	}
}

void Image::darken(double amount) {
	for (unsigned i = 0; i < width(); i++) {
		for (unsigned j = 0; j < height(); j++) {
			HSLAPixel& pixel = getPixel(i, j);
			if (pixel.l - amount <= 0) {
				pixel.l = 0;
			}
			else {
				pixel.l -= amount;
			}
		}
	}
}

void Image::saturate() {
	for (unsigned i = 0; i < width(); i++) {
		for (unsigned j = 0; j < height(); j++) {
			HSLAPixel& pixel = getPixel(i, j);
			if (pixel.s + 0.1 >= 1.0) {
				pixel.l = 1.0;
			}
			else {
				pixel.s += 0.1;
			}
		}
	}
}

void Image::saturate(double amount) {
	for (unsigned i = 0; i < width(); i++) {
		for (unsigned j = 0; j < height(); j++) {
			HSLAPixel& pixel = getPixel(i, j);
			if (pixel.s + amount >= 1.0) {
				pixel.s = 1.0;
			}
			else {
				pixel.s += amount;
			}
		}
	}
}

void Image::desaturate() {
	for (unsigned i = 0; i < width(); i++) {
		for (unsigned j = 0; j < height(); j++) {
			HSLAPixel& pixel = getPixel(i, j);
			if (pixel.s - 0.1 <= 0) {
				pixel.s = 0;
			}
			else {
				pixel.s -= 0.1;
			}
		}
	}
}

void Image::desaturate(double amount) {
	for (unsigned i = 0; i < width(); i++) {
		for (unsigned j = 0; j < height(); j++) {
			HSLAPixel& pixel = getPixel(i, j);
			if (pixel.s - amount <= 0) {
				pixel.s = 0;
			}
			else {
				pixel.s -= amount;
			}
		}
	}
}

void Image::grayscale() {
	for (unsigned x = 0; x < width(); x++) {
		for (unsigned y = 0; y < height(); y++) {
			HSLAPixel& pixel = getPixel(x, y);
			pixel.s = 0;
		}
	}
}

void Image::rotateColor(double degrees) {
	double full_rotate = 360.0;
	for (unsigned i = 0; i < width(); i++) {
		for (unsigned j = 0; j < height(); j++) {
			HSLAPixel& pixel = getPixel(i, j);
			double sum = pixel.h + degrees;
			if (sum < 0) {
				while (sum < 0) {
					sum += full_rotate;
				}
			} else if (sum > full_rotate) {
				while (sum > full_rotate) {
					sum -= full_rotate;
				}
			}
			pixel.h = sum;
		}
	}
}

void Image::illinify() {

	double illiniOrange = 11.0;
	double illiniBlue = 216.0;
	double average = 113.5;

	for (unsigned x = 0; x < width(); x++) {
		for (unsigned y = 0; y < height(); y++) {
			HSLAPixel& pixel = getPixel(x, y);
			if (pixel.h <= average || pixel.h >= average + illiniBlue) {
				pixel.h = illiniOrange;
			}
			else {
				pixel.h = illiniBlue;
			}
		}
	}
}

void Image::scale(double factor) {
	if (factor <= 0 || factor == 1) {
		return;
	}
	PNG image(*this);
	resize(width() * factor, height() * factor);
	for (unsigned x = 0; x < width(); x++) {
		for (unsigned y = 0; y < height(); y++) {
			HSLAPixel& pixel = image.getPixel(x / factor, y / factor);
			getPixel(x, y) = pixel;
		}
	}
}

void Image::scale(unsigned w, unsigned h) {
	double w_factor = (w * 1.0) / width();
	double h_factor = (h * 1.0) / height();
	if (w_factor < h_factor) {
		scale(w_factor);
	}
	else {
		scale(h_factor);
	}
}