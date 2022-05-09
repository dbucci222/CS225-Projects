/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"

class StickerSheet {
private:
	Image * image_;
	unsigned max_;
	Image ** stickers_;
	unsigned* x_array_;
	unsigned* y_array_;

public:
	StickerSheet(const Image & picture, unsigned max);
	~StickerSheet();
	StickerSheet(const StickerSheet& other);

	int addSticker(Image& sticker, unsigned x, unsigned y);
	void changeMaxStickers(unsigned max);
	Image* getSticker(unsigned index);
	const StickerSheet& operator=(const StickerSheet& other);
	void removeSticker(unsigned index);
	Image render() const;
	bool translate(unsigned index, unsigned x, unsigned y);

	void copy_(const StickerSheet& other);
	void clear();
 };