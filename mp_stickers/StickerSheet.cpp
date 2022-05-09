#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image& picture, unsigned max) {
	image_ = new Image(picture);
	max_ = max;
	stickers_ = new Image*[max_];
	x_array_ = new unsigned[max_];
	y_array_ = new unsigned[max_];
	for (unsigned i = 0; i < max_; i++) {
		stickers_[i] = NULL;
		x_array_[i] = 0;
		y_array_[i] = 0;
	}
}

StickerSheet::~StickerSheet() {
	clear();
}

StickerSheet::StickerSheet(const StickerSheet& other) {
	copy_(other);
}

int StickerSheet::addSticker(Image& sticker, unsigned x, unsigned y) {
	for (unsigned i = 0; i < max_; i++) {
		if (stickers_[i] == NULL) {
			stickers_[i] = new Image(sticker);
			x_array_[i] = x;
			y_array_[i] = y;
			return i;
		}
	}

	return -1;
}

void StickerSheet::changeMaxStickers(unsigned max) {
	
	if (max == max_) {
		return;
	}
	
	Image** new_stickers_ = new Image*[max];
	unsigned * new_x = new unsigned[max];
	unsigned * new_y = new unsigned[max];

	if (max < max_) {
		for (unsigned i = 0; i < max_; i++) {
			if (i >= max) {
				delete stickers_[i];
				stickers_[i] = NULL;
				x_array_[i] = 0;
				y_array_[i] = 0;
				continue;
			}
			new_stickers_[i] = stickers_[i];
			new_x[i] = x_array_[i];
			new_y[i] = y_array_[i];
		}
	}
	else if (max > max_) {
		for (unsigned i = 0; i < max; i++) {
			if (i >= max_) {
				new_stickers_[i] = NULL;
				new_x[i] = 0;
				new_y[i] = 0;
			}
			else {
				new_stickers_[i] = stickers_[i];
				new_x[i] = x_array_[i];
				new_y[i] = y_array_[i];
			}
		}
	}

	delete[] stickers_;
	delete[] x_array_;
	delete[] y_array_;

	x_array_ = new_x;
	y_array_ = new_y;

	max_ = max;
	stickers_ = new_stickers_;

}

Image* StickerSheet::getSticker(unsigned index) {
	if (stickers_[index] == NULL) {
		return NULL;
	}
	return stickers_[index];
}

const StickerSheet& StickerSheet::operator=(const StickerSheet& other) {
	clear();
	copy_(other);
	return *this;
}

void StickerSheet::removeSticker(unsigned index) {
	delete stickers_[index];
	stickers_[index] = NULL;
	x_array_[index] = 0;
	y_array_[index] = 0;
	for (unsigned i = index; i < max_ - 1; i++) {
		stickers_[i] = stickers_[i + 1];
		x_array_[i] = x_array_[i + 1];
		y_array_[i] = y_array_[i + 1];
		stickers_[i + 1] = NULL;
		x_array_[i + 1] = 0;
		y_array_[i + 1] = 0;
	}
}

Image StickerSheet::render() const {

	unsigned int final_width = image_->width();
	unsigned int final_height = image_->height();
	for (unsigned i = 0; i < max_; i++) {
		if (stickers_[i] == NULL) {
			continue;
		}
		if (x_array_[i] + stickers_[i]->width() > final_width) {
			final_width = x_array_[i] + stickers_[i]->width();
		}
		if (y_array_[i] + stickers_[i]->height() > final_height) {
			final_height = y_array_[i] + stickers_[i]->height();
		}
	}

	Image final_image(*image_);
	final_image.resize(final_width, final_height);

	/*
	for (unsigned x = 0; x < image_->width(); x++) {
		for (unsigned y = 0; y < image_->height(); y++) {
			HSLAPixel& pixel = image_->getPixel(x, y);
			HSLAPixel& pixel2 = final_image.getPixel(x, y);
			pixel2 = pixel;
		}
	}
	*/

	for (unsigned i = 0; i < max_; i++) {
		if (stickers_[i] == NULL) {
			continue;
		}
		for (unsigned x = 0; x < stickers_[i]->width(); x++) {
			for (unsigned y = 0; y < stickers_[i]->height(); y++) {
				HSLAPixel& pixel = stickers_[i]->getPixel(x, y);
				if (pixel.a == 0) {
					continue;
				}
				HSLAPixel& pixel2 = final_image.getPixel(x + x_array_[i], y + y_array_[i]);
				pixel2 = pixel;
			}
		}
	}

	return final_image;

}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
	if (stickers_[index] == NULL || index >= max_) {
		return false;
	}
	x_array_[index] = x;
	y_array_[index] = y;
	return true;
}

void StickerSheet::copy_(const StickerSheet& other) {
	image_ = new Image(*other.image_);
	max_ = other.max_;
	stickers_ = new Image * [max_];
	x_array_ = new unsigned [max_];
	y_array_ = new unsigned [max_];
	for (unsigned i = 0; i < max_; i++) {
		if (other.stickers_[i] == NULL) {
			stickers_[i] = NULL;
			continue;
		}
		stickers_[i] = new Image(*other.stickers_[i]);
		x_array_[i] = other.x_array_[i];
		y_array_[i] = other.y_array_[i];
	}
}

void StickerSheet::clear() {
	delete image_;
	for (unsigned i = 0; i < max_; i++) {
		delete stickers_[i];
		stickers_[i] = NULL;
		x_array_[i] = 0;
		y_array_[i] = 0;
	}
	delete[] stickers_;
	delete[] x_array_;
	delete[] y_array_;
}