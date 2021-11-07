#include "Image.h"


Image::Image() {
	width = 256;
	height = 256;
	initImage();
}

Image::Image(int x, int y) {
	width = x;
	height = y;
	initImage();
}

Image::Image(std::string fileName) {
	std::cout << "Trying to read " << fileName << "...\n";
	std::ifstream stream;
	stream.open(fileName, std::ios::in | std::ios::binary);
	if (!stream.is_open()) {
		width = 1;
		height = 1;
		initImage();
		std::cout << "Couldn't Read " << fileName << "!!\n";
	}
	std::cout << "Successfully Opened " << fileName << "!\n";
	std::string ppmHeader;
	stream >> ppmHeader;
	stream.ignore();
	std::cout << ppmHeader << std::endl;
	width = readNumber(stream);
	height = readNumber(stream);
	int maxColor = readNumber(stream);
	initImage();
	for (int i = height - 1; i >= 0; i--) {
		for (int j = 0; j < width; j++) {
			double val;
			val = readNumber(stream);
			image[i][j].x = val / maxColor;
			val = readNumber(stream);
			image[i][j].y = val / maxColor;
			val = readNumber(stream);
			image[i][j].z = val / maxColor;
		}
	}
	stream.close();
	writeToPPMFile();


}

void Image::initImage() {
	image = new Vec3 * [height];
	for (int i = 0; i < height; i++) {
		image[i] = new Vec3[width];
		for (int j = 0; j < width; j++) {
			image[i][j] = Vec3();
		}
	}
}

double Image::readNumber(std::ifstream& stream) {
	char s;
	while (!stream.eof()) {
		stream >> s;
		stream.ignore();
		std::cout << static_cast<int>(s) << std::endl;
		//if (isdigit(s.at(0))) return atof(s.c_str());
	}
	return 0.0;
}

Image::~Image() {
	//for (int i = 0; i < height; i++) {
	//	delete[] image[i];
	//}
	//delete[] image;
}

int Image::getWidth() {
	return width;
}

int Image::getHeight() {
	return height;
}

void Image::setWidth(int x) {
	width = x;
}

void Image::setHeight(int y) {
	height = y;
}

Vec3 Image::get(int x, int y) {
	return image[y][x];
}

void Image::set(int x, int y, Vec3 v) {
	image[y][x] = v;
}

void Image::writeToPPMFile() {
	//Start creating the file
	std::ostringstream oss;
	//char s[10];
	//sprintf_s(s, "%04d", frameNum);

	//oss << "./output/image." << s << ".ppm";

	oss << "./Output/image" << ".ppm";
	std::string outputLocation = oss.str();
	std::ofstream file(outputLocation, std::ios::binary);

	file << "P6\n";
	file << width << " " << height << "\n";
	file << 255 << "\n";



	//for each pixel in the image
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			//each pixel has 3 values, R, G, and B
			//we have to convert the ints into chars because
			//otherwise the image isn't correct

			file <<
				(unsigned char)(image[i][j].x * 255) <<
				(unsigned char)(image[i][j].y * 255) <<
				(unsigned char)(image[i][j].z * 255);

		}
	}

	std::cout << "wrote output file to " << outputLocation << std::endl;




	file.close();
}
