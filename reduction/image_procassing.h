/*
 * image_procassing.h
 *
 *  Created on: 2 нояб. 2020 г.
 *      Author: lrikozavr
 */

#ifndef IMAGE_PROCASSING_H_
#define IMAGE_PROCASSING_H_


#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cmath>

typedef
struct pixel {
	unsigned int value;
	bool close;
} pixel;

struct obj_s{
	int x,y;
	int lum;
	int border[4];
};

class IMAGE {
private:
	obj_s * s;
	pixel ** pix;
	IMAGE * mf1;
	IMAGE * mf2;
public:
	int count;
	int size;
	IMAGE()
	{
		s=NULL;
		pix=NULL;
		count=0;
		size=0;
	}
	void set_image(int n)
	{
		size=n;
		pix = new pixel *[size];
		for (int i=0; i<size; i++)
		{pix[i] = new pixel [size];}
		for (int i=0; i<size; i++){for (int j=0; j<size; j++){pix[i][j].close=false;}}
	}

	void set_obj(int n)
	{
		count=n;
		s = new obj_s [count];
	}

	void read_fits(FILE * f);
	void write_fits(FILE * f, IMAGE * data, int n);

	void Median(int resolution);
	void Medver(int **a, int center, int k, int flag);
	int obj_rec_sep(pixel ** mass, obj_s * massive, int x, int y, int count, int i);
	obj_s Center(obj_s * mass, int count);

	~IMAGE()
	{
		delete [] s;
		for (int i=0; i<size; i++)
		{delete [] pix[i];}
		delete [] pix;
	}
};
int power_number(int origin[],int power);
int comp1(const void * a, const void * b);
void Medver(IMAGE * data, int **a, int center, int k, int flag);

//
#endif /* IMAGE_PROCASSING_H_ */
