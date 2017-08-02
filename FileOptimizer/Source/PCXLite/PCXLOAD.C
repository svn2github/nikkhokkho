///////////////////////////////////////////////
// Copyright
///////////////////////////////////////////////
//
// pcx loader
// Copyright (c) 2002 Jari Komppa
//
//
///////////////////////////////////////////////
// License
///////////////////////////////////////////////
// 
//     This software is provided 'as-is', without any express or implied
//     warranty.  In no event will the authors be held liable for any damages
//     arising from the use of this software.
// 
//     Permission is granted to anyone to use this software for any purpose,
//     including commercial applications, and to alter it and redistribute it
//     freely, subject to the following restrictions:
// 
//     1. The origin of this software must not be misrepresented; you must not
//        claim that you wrote the original software. If you use this software
//        in a product, an acknowledgment in the product documentation would be
//        appreciated but is not required.
//     2. Altered source versions must be plainly marked as such, and must not be
//        misrepresented as being the original software.
//     3. This notice may not be removed or altered from any source distribution.
// 
// (eg. same as ZLIB license)

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

/***************
  * Structures *
  ***************/

typedef struct {
 char manufacturer; /* 10 for paintbrush */
 char version; /* If 5 or more, 768 byte palette is found at the eof. */
 char encoding; /* 1 for .pcx */
 char bits_per_pixel; /* 1,4,8,24 */
 short int xmin; /* why min?! */
 short int ymin;
 short int xmax;
 short int ymax;
 short int horizontal_res; /* in dpi.. forget it */
 short int vertical_res;
 char palette_for_16c_modes[48]; /* 0=black, 255=white. in rgb triplets. */
 char reserved; /* should be 0 */
 char colour_planes;
 short int bytes_per_line;
 short int palette_type; /* to be ignored */
 short int hscreensize;
 short int vscreensize; /* These two are only found in some PCXes but should
                           be filled for compatibility's sake. */
 char filler[54];
} PCXHEADER;

/***************
  * Real stuff *
  ***************/

static void decode_pcx_line(int yoffs, int bytesperline, int realwidth, char * picdata, FILE * picfile) {
int depack,packto,counter;
char data;
    counter=0;
    while (counter<(bytesperline)) {
      data=fgetc(picfile);
      if ((data&192)==192) {
        packto=data&63;
        data=fgetc(picfile);
        for(depack=0;depack<packto;depack++) {
           if (counter<realwidth)
            *(picdata+yoffs+counter)=data;
           counter++;
        }
      }
      else {
       if (counter<realwidth)
        *(picdata+yoffs+counter)=data;
       counter++;
      }
    }
}

void getpcxinfo(char * filename, int * xsize, int * ysize) {
FILE * picfile;
PCXHEADER hdr;
  picfile=fopen(filename,"rb");
  fread(&hdr,sizeof(PCXHEADER),1,picfile);
  if (hdr.manufacturer==10 && hdr.encoding==1 && hdr.bits_per_pixel==8)
  {
    *xsize=hdr.xmax-hdr.xmin+1;
    *ysize=hdr.ymax-hdr.ymin+1;
  }
  else
  {
    *xsize=*ysize=0;
  }
  fclose(picfile);
}

char * loadpcx(char * filename) {
FILE * picfile;
int picsize,ycount;
char * buf=NULL;
int xsize, ysize;
PCXHEADER hdr;
    picfile=fopen(filename,"rb");
    fread(&hdr,sizeof(PCXHEADER),1,picfile);
    xsize=hdr.xmax-hdr.xmin+1;
    ysize=hdr.ymax-hdr.ymin+1;
    fseek(picfile,-769,SEEK_END);
    if((hdr.version>4)&&(hdr.encoding==1)&&(hdr.bits_per_pixel==8)&&
       (hdr.colour_planes==1)&&(fgetc(picfile)==12)) {

/* We can only handle v5+, PCX, 8b, one plane PCXes with 256c palette.
   (for the time being) */

        picsize=xsize*ysize;
        buf=malloc(picsize);
        fseek(picfile,sizeof(PCXHEADER),SEEK_SET);
        for (ycount=0;ycount<ysize;ycount++)
         decode_pcx_line(ycount*(xsize),hdr.bytes_per_line,xsize,buf,picfile);
    }

    fclose(picfile);
    return(buf);
}


char * loadpcxpal(char * filename) {
FILE * picfile;
char * buf=NULL;
PCXHEADER hdr;
    picfile=fopen(filename,"rb");
    fread(&hdr,sizeof(PCXHEADER),1,picfile);
    fseek(picfile,-769,SEEK_END);
    if((hdr.version>4)&&(hdr.encoding==1)&&(hdr.bits_per_pixel==8)&&
       (hdr.colour_planes==1)&&(fgetc(picfile)==12)) {

/* We can only handle v5+, PCX, 8b, one plane PCXes with 256c palette.
   (for the time being) */

        buf=malloc(768);
        fread(buf,768,1,picfile);

    }

    fclose(picfile);
    return(buf);
}
