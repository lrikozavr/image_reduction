#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cmath>
#include "image_procassing.h"
using namespace std;


int main()
{
	//int l;
	int b[3]={3,2,1};
	qsort(b,2,sizeof(int),comp1);
	printf("%d\n",b[0]);
	int n=3056; // количество элементов в квадратном массиве
	IMAGE * data = new IMAGE();
	//data.set_image(3056);
	//int data[3056][3056];
	//int sym1,sym2;
	//char s[100];

    //char pack_header[2880*4];
    //char pack_data[3056*2];
    FILE * f;
    f=fopen("A01-1-001-001.fts","rb");
    FILE * g;
    g=fopen("test.txt","w");
    data->set_image(n);
	char pack_header[2880*4];
	fread(&pack_header,1,2880*4,f);
	//printf("hi");
	data->read_fits(f);
	//IMAGE garlic;
	//garlic=data.Median(&data,3);
	data->Median(3);
	//fprintf(stderr,"%d\n",1);
    /*
    for (int j=0; j<3056 ; j++)
    	fread(&pack_data,3056*2,1,f);
    */

	/*
////////////////////////////////////////////////////////////////////////
     // количество элементов в квадратном массиве
    int resolution; //3 размер ядра
    int center = resolution / 2; //1 центр ядра
    int k = pow(resolution,2);
    int b[k];
    int a[n][n];
    int ind;
   // Median(,3056,3);
//////////////////////////////////////////////////////////////////////////////////
    //sym1=(int)(pack_header[2882*4-1]);
    //sym2=(int)(pack_header[2882*4-3]);
   // fprintf(g,"%s\n%s",pack_header,s); //<< endl << sizeof(double);
*/
    return 0;
}
