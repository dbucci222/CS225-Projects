#include "Image.h"
#include "StickerSheet.h"

int main() {
	
	Image alma_mater;
	alma_mater.readFromFile("alma.png");

	Image i;
	i.readFromFile("i.png");

	StickerSheet * sheet = new StickerSheet(alma_mater, 3);
	sheet->addSticker(i, alma_mater.width() / 4, alma_mater.height() / 4);
	sheet->addSticker(i, alma_mater.width() / 3, alma_mater.height() / 3);
	sheet->addSticker(i, alma_mater.width() / 2, alma_mater.height() / 2);

	Image creation = sheet->render();
	creation.writeToFile("myImage.png");

	return 0;
}
