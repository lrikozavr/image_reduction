/*
 * image_procassing.cpp
 *
 *  Created on: 2 нояб. 2020 г.
 *      Author: lrikozavr
 */

#include <stdio.h>
#include <cstdlib> //qsort
#include <iostream>
#include <string.h>
#include <cmath>
#include "image_procassing.h"

#define cconst 0.5*(pow(r2,2)-pow(r1,2)+pow(dx1,2)-pow(dx2,2)+pow(dy1,2)-pow(dy2,2))
#define dx dx1-dx2
#define dy dy1-dy2
#define kkk dx/dy
#define bbb dx1+(pow(kkk,2)/dx)*cconst-kkk*dy1
#define DDD pow(r1,2)*(1+pow(kkk,2))-pow(dy1+dx1*kkk-(kkk/dx)*cconst,2)

int comp1(const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int power_number(int origin[],int power)
{	int result=0;
	int dif=power/2;
	//fprintf(stderr,"%d\n",sizeof(origin));
	for (int i=1, j=0; i>=0; i--, j++)
	{origin[i]+=dif; result+=origin[i]*pow(power,j);}
	return result;
}

void IMAGE::read_fits(FILE * f)
{
	int n=size;
	int m[2];
	char pack_data[n*2];

    for (int j=0; j<n ; j++)
    {	//fprintf(stderr,"%d\n",j);
    	fread(&pack_data,1,n*2,f);
    	for (int i=0; i<n*2 ; i+=2)
    	{m[0]=(int)pack_data[i]; m[1]=(int)pack_data[i+1];
    	//printf("%d\t%d\t",m[0],m[1]);
    	pix[j][i/2].value=power_number(m,256);
    	//printf("%d\t%d\t\t%d\t%d\t%d\t%c,%c\n",j,i/2,pix[j][i/2].value,m[0],m[1],pack_data[i],pack_data[i+1]);
    	}
    }

}
/*
void IMAGE::write_fits(FILE * f, IMAGE * data, int n)
{
	mf=data;
	int m[2];
	char pack_data[n*2];
    for (int j=0; j<n ; j++)
    {	//fprintf(stderr,"%d\n",j);
    	fwrite(&pack_data[j],n*2,1,f);
    	for (int i=0; i<n*2 ; i+=2)
    	{m[0]=(int)pack_data[i]; m[1]=(int)pack_data[i+1];
    	mf->pix[j][i/2].value=power_number(m,256);
    	//fprintf(g,"%d\t%d\t%d\t%c,%c\n",power_number(m,256),m[0],m[1],pack_data[i],pack_data[i+1]);
    	}
    }
}
*/

void IMAGE::Medver(int **a, int center, int k, int flag)
{
	int n=size;
	int b[k];
	int ind;
	int jl,il,m;
    if (flag<2){
		for (int i=0; i<n ; i++)
		{
			if (flag==0)
			{jl=0;m=center;}
			else {jl=n-center; m=n;}
			for (int j=jl;j<m;j++)
			{
				ind=0;
				for (int i1=i-center; i1<=i+center; i1++)
					{
						for (int j1=j; j1<=j+center; j1++)
						{	if(i1<n && i1>=0 && j1<n && j1>=0)
							{b[ind]=pix[i1][j1].value;}}
						ind++;
					}
				qsort(b,ind,sizeof(int),comp1);
				a[i][j]=b[ind/2]; //?
			}

		}}
    else{
        for (int j=center; j<n-center ; j++)
        {
        	if (flag==2)
        	{il=0;m=center;}
        	else{il=n-center;m=n;}
        	for (int i=il ;i<m;i++)
        	{
            	ind=0;
				for (int i1=i; i1<=i+center; i1++)
					{
						for (int j1=j-center; j1<=j+center; j1++)
						{b[ind]=pix[i1][j1].value;}
						ind++;
					}
	    		qsort(b,k,sizeof(int),comp1);
	    		a[i][j]=b[k/2]; //?
			}

        }
    }
}
/*
IMAGE IMAGE::Median(IMAGE * data, int resolution) // количество элементов в квадратном массиве, 3 размер ядра
{
	mf1=data;
	int n=data->size;
	//printf("%d\n",size);
    int center = resolution / 2; //1 центр ядра
    int k = pow(resolution,2);
    //printf("%d",k);
    int b[k];
    IMAGE a;
    a.set_image(n);
    mf2=&a;
    //int ** aa; for (int i=0; i<n ; i++){for (int j=0; j<n ; j++){aa[i][j]=a[i][j];}}

    //printf("%d\t%d\t%d\n",center,k,n);
    int ind;
    for (int i=center; i < n-center; i++)
    {
    	for (int j=center; j < n-center; j++)
    		{
    			ind=0;
    			for (int i1=i-center; i1<=i+center; i1++)
    				{
    					for (int j1=j-center; j1<=j+center; j1++)
    					{b[ind]=mf1->pix[i1][j1].value;
    					ind++;}
    				}
    			//printf("%d\n",b[1]);
    			qsort(b,ind,sizeof(int),comp1);
    			//printf("%d",ind);
    			mf2->pix[i][j].value=b[k/2];
    		}
    }
    //mf1->pix[1][2].value=a[1][2];
    /*
    k-=resolution*center;
    Medver(aa,center,k,0);
    Medver(aa,center,k,1);
    Medver(aa,center,k,2);
    Medver(aa,center,k,3);
    *

    for (int i=0; i<n ; i++ )
    {
    	for (int j=0; j<n ; j++)
    	{
    		mf2->pix[i][j].value=mf1->pix[i][j].value;
    	}
    }

}
*/
void IMAGE::Median(int resolution) // количество элементов в квадратном массиве, 3 размер ядра
{
	int n=size;
	//printf("%d\n",size);
    int center = resolution / 2; //1 центр ядра
    int k = pow(resolution,2);
    //printf("%d",k);
    int b[k];
    int ** a;
    a = new int *[n];
    for (int i=0; i<n;i++)
    { a[i]= new int [n];}
    //int ** aa; for (int i=0; i<n ; i++){for (int j=0; j<n ; j++){aa[i][j]=a[i][j];}}

    //printf("%d\t%d\t%d\n",center,k,n);
    int ind;
    for (int i=center; i < n-center; i++)
    {
    	for (int j=center; j < n-center; j++)
    		{
    			ind=0;
    			for (int i1=i-center; i1<=i+center; i1++)
    				{
    					for (int j1=j-center; j1<=j+center; j1++)
    					{b[ind]=pix[i1][j1].value;
    					ind++;}
    				}
    			//printf("%d\n",b[1]);
    			qsort(b,ind,sizeof(int),comp1);
    			//printf("%d",ind);
    			a[i][j]=b[k/2];
    		}
    }
    //mf1->pix[1][2].value=a[1][2];
    /*
    k-=resolution*center;
    Medver(aa,center,k,0);
    Medver(aa,center,k,1);
    Medver(aa,center,k,2);
    Medver(aa,center,k,3);
    */

    for (int i=0; i<n ; i++ )
    {
    	for (int j=0; j<n ; j++)
    	{
    		pix[i][j].value=a[i][j];
    	}
    }
    for (int i=0;i<n;i++)
    {delete [] a[i];}
    delete [] a;

}


int IMAGE::obj_rec_sep(pixel ** mass, obj_s * massive, int x, int y, int count, int i)
{
	if (mass[x][y].close==true){return i;}
	mass[x][y].close=true;
	massive[i].lum=mass[x][y].value;
	massive[i].x=x; massive[i].y=y;
	i++;
	if ( x+1 < count && mass[x+1][y].value>0) {i=obj_rec_sep(mass,massive,x+1,y,count,i);}
	if ( y+1 < count && mass[x][y+1].value>0) {i=obj_rec_sep(mass,massive,x,y+1,count,i);}
	if (   x > 0 	 && mass[x-1][y].value>0) {i=obj_rec_sep(mass,massive,x-1,y,count,i);}
	if (   y > 0	 && mass[x][y-1].value>0) {i=obj_rec_sep(mass,massive,x,y-1,count,i);}
	return i;
}

obj_s IMAGE::Center(obj_s * mass, int count)
{
	obj_s obj;
	float su,s1,s2,s3=0;
	float r1,r2,r3=0;
	for (int i=0; i<count ; i++)
	{
		s1+=mass[i].lum*hypot(mass[i].x,mass[i].y);
		s2+=mass[i].lum*hypot(mass[i].x-mass[0].x,mass[i].y-mass[0].y);
		s3+=mass[i].lum*hypot(mass[i].x-mass[1].x,mass[i].y-mass[1].y);
		su+=mass[i].lum;
	}
	r1=s1/su; r2=s2/su; r3=s2/su;
	int dx1,dx2,dy1,dy2;
	float x1,x2,y1,y2;
		dx1=0; dy1=0;
		dx2=mass[0].x; dy2=mass[0].y;
		x1=(-(bbb) + pow(DDD,0.5))/(1+pow(kkk,2));
		x2=(-(bbb) - pow(DDD,0.5))/(1+pow(kkk,2));
		y1=-x1*kkk-(kkk/dx)*cconst;
		y2=-x2*kkk-(kkk/dx)*cconst;
	float x3,x4,y3,y4;
		r1=r2; r2=r3;
		dx1=mass[0].x; dy1=mass[0].y;
		dx2=mass[1].x; dy2=mass[1].y;
		x3=(-(bbb) + pow(DDD,0.5))/(1+pow(kkk,2));
		x4=(-(bbb) - pow(DDD,0.5))/(1+pow(kkk,2));
		y3=-x3*kkk-(kkk/dx)*cconst;
		y4=-x4*kkk-(kkk/dx)*cconst;

	if(abs(y3-y1) < abs(y4-y2) && abs(x3-x1) < abs(x4-x2))
	{
		obj.y=round((y3+y1)/2);
		obj.x=round((x3+x1)/2);
	}
	else {
		obj.y=round((y4+y2)/2);
		obj.x=round((x4+x2)/2);
	}
	return obj;
}

