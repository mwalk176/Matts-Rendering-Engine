#ifndef IMAGE_H
#define IMAGE_H

#include <fstream>

#include "../Utils/Vec3.h"

class Image {
public:
	Image();
	Image(int x, int y);
	Image(std::string fileName);
	~Image();

	int getWidth();
	int getHeight();
	void setWidth(int x);
	void setHeight(int y);

	Vec3 get(int x, int y);
	void set(int x, int y, Vec3 v);

	void writeToPPMFile();

	//Vec3 operator() (int i, int j) const { return image[i][j]; } //get
	//Vec3& operator() (int i, int j) { return image[i][j];} //set
	

private:
	int width;
	int height;
	Vec3** image;

	void initImage();
	double readNumber(std::ifstream& stream);
};

#endif