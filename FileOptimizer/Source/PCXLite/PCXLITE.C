///////////////////////////////////////////////
// Copyright
///////////////////////////////////////////////
//
// pcxlite - lossless pcx compressor
// Copyright (c) 1998-2002 Jari Komppa
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

//#include <dos.h>
//#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
//#include <i86.h>
//#include <mem.h>
#include <math.h>
//#include "/watcom/solib/solib.h"
#include "pcxload.h"


typedef struct pcxheaderstruct {
  unsigned char manufacturer;
  unsigned char version;
  unsigned char encoding;
  unsigned char bits_per_pixel;
  short int xmin;
  short int ymin;
  short int xmax;
  short int ymax;
  short int horizontal_res;
  short int vertical_res;
  unsigned char palette_for_16c_modes[48];
  unsigned char reserved;
  unsigned char colour_planes;
  short int bytes_per_line;
  short int palette_type;
  short int hscreensize;
  short int vscreensize;
  unsigned char filler[54];
} PCXHEADER;

static unsigned char * encode_pcx_line(unsigned char * ptr,unsigned char * src, int bytes) {
int len;
  while (bytes>0) {
    if ((bytes>1) && (*(src)==*(src+1))) { // rle
      len=0;
      while ((*src==*(src+len)) && (len<63) && (len<bytes))
        len++; // find RLE len
      *ptr=0xc0+len;
      ptr++;
      *ptr=*src;
      ptr++;
      src+=len;
      bytes-=len;
    } else { // single unsigned char
      if ((*src&0xc0)==0xc0) { // 2 high bits on
        *ptr=0xc1; // rle with 1 byte thanks..
        ptr++;
        *ptr=*src;
        ptr++;
        src++;
        bytes--;
      } else {  // normal raw byte
        *ptr=*src;
        ptr++;
        src++;
        bytes--;
      }
    }
  }
  return ptr;
}

static unsigned char * encode_pcx8(unsigned char * picbuf, unsigned char * palbuf, int xwid, int ywid, int * datalen) {
unsigned char * data, * ptr;
PCXHEADER * hdr;
int a;
  data=malloc(sizeof(PCXHEADER)+768+1+(xwid*ywid*2));
  hdr=(PCXHEADER*)data;
  ptr=data+sizeof(PCXHEADER);

  hdr->manufacturer=10;
  hdr->version=5;
  hdr->encoding=1;
  hdr->bits_per_pixel=8;
  hdr->xmin=0;
  hdr->ymin=0;
  hdr->xmax=xwid-1;
  hdr->ymax=ywid-1;
  hdr->horizontal_res=xwid/10;
  hdr->vertical_res=ywid/10;
  hdr->reserved=0;
  hdr->colour_planes=1;
  hdr->bytes_per_line=xwid;
  hdr->palette_type=0;
  hdr->hscreensize=xwid;
  hdr->vscreensize=ywid;
  for (a=0;a<ywid;a++)
    ptr=encode_pcx_line(ptr,picbuf+a*xwid,xwid);
  *(ptr)=12;
  ptr++;
  memcpy(ptr,palbuf,768);
  ptr+=768;
  *datalen=ptr-data;
  return data;
}

static void savepcx8(unsigned char * picbuf,unsigned char * palbuf,int xwid,int ywid,unsigned char * fname) {
FILE * f;
int a,b=0;
int fs;
unsigned char * buf;
  for (a=0;a<768;a++)
    if (b<*(palbuf+a)) b=*(palbuf+a);
  if (b<64)
    for (a=0;a<768;a++)
      *(palbuf+a)*=4;
  buf=encode_pcx8(picbuf,palbuf,xwid,ywid,&fs);
  f=fopen(fname,"wb");
  fwrite(buf,fs,1,f);
  fclose(f);
  free(buf);
  if (b<64)
    for (a=0;a<768;a++)
      *(palbuf+a)/=4;
}

int freq[256], idx[256];

int sort_int(const void * a, const void * b) {
  if (freq[*(int*)b]>freq[*(int*)b]) return 1;
  if (freq[*(int*)b]<freq[*(int*)b]) return -1;
  return 0;
}

void main(int paramc, unsigned char ** params) {
unsigned char * pcxpic, * pcxpal, *newpal;
int xwid,ywid,breaker=1,i,a,b;
  printf("\nPCXLITE v1.1 (c)1998 Jari Komppa\nModified by Javier Gutierrez Chamorro (Guti)\n\nLossless or optionally lossy optimization of PCX pictures\n");
  if (paramc<3) {
    printf("Usage: pcxlite infile.pcx outfile.pcx [palette breaker value 1-256, default 1]\n"
           "\n"
           "PCXLITE does two optimizations:\n"
           " 1. Removal of duplicate colors (same palette, two colors)\n"
           " 2. Analysation of which colors do least damage over 192 color edge\n"
           "and optionally removes colors that are very close to each other\n"
           "before the 1st step using the breaker value. Generally speaking\n"
           "breaker value of 4 reduces palette width to 64:64:64, 8 to 32:32:32\n"
           "etc.\n"
           "Reorganizing colors to start of palette is generally good idea\n"
           "due to the fact that saving single pixels of color index over 192\n"
           "in PCX format takes more space than it saves.\n"
           "Color 0 is not moved due to its special use in many places. (Border etc).\n");
    return;
  }
  if (paramc>3) breaker=strtol(params[3],0,10);
  if (breaker==0) {
    printf("invalid breaker value\n");
    return;
  }
  getpcxinfo(params[1],&xwid,&ywid);
  if (xwid==0) {
    printf("Invalid input file\n");
    return;
  }
  printf("Input:\n  x_size :%d\n  y_size :%d\n  breaker:%d\n",xwid,ywid,breaker);
  pcxpic=loadpcx(params[1]);
  pcxpal=loadpcxpal(params[1]);
  for (i=0;i<768;i++)
    *(pcxpal+i)=(*(pcxpal+i)/breaker)*breaker;
  for (i=0;i<256;i++)
    idx[i]=-1;
  printf("Finding unused colors..\n");
  for (a=0;a<xwid*ywid;a++)
    idx[*(pcxpic+a)]=*(pcxpic+a);
  printf("Finding duplicate colors in used colors..\n");
  i=0;
  for (a=0;a<256;a++)
    if (idx[a]==a)
      for (b=0;b<256;b++)
        if (a!=b)
          if (idx[b]==b) {
            if ((*(pcxpal+a*3+0)==*(pcxpal+b*3+0)) &&
                (*(pcxpal+a*3+1)==*(pcxpal+b*3+1)) &&
                (*(pcxpal+a*3+2)==*(pcxpal+b*3+2))) {
              idx[b]=a;
              i++;
            }
          }
  printf("%d duplicate%c found\n",i,(i==1)?0:'s');
  if (i) {
    printf("Remapping duplicate colors..\n");
    for (a=0;a<xwid*ywid;a++)
      *(pcxpic+a)=idx[*(pcxpic+a)];
  }
  printf("Getting single pixel frequencies..\n");
  for (a=0;a<256;a++) {
    freq[a]=0;
    idx[a]=a;
  }
  i=0; b=-1;
  for (a=0;a<xwid*ywid;a++) {
    if ((*(pcxpic+a)!=b) || ((a%320)==0) || (i==63)) {
      if (i==1)
        freq[b]++;
      if (i>2)
        freq[b]-=i-2;
      b=*(pcxpic+a);
      i=0;
    }
    i++;
  }
//  for (a=0;a<256;a++) printf("%3d:%d\n",a,freq[a]);
  printf("Sorting..\n");
  qsort(&idx[1],255,sizeof(int),&sort_int);
  printf("Remapping..\n");
  for (a=0;a<xwid*ywid;a++)
    *(pcxpic+a)=idx[*(pcxpic+a)];
  newpal=malloc(768);
  printf("Remapping palette..\n");
  for (a=0;a<256;a++) {
      *(newpal+idx[a]*3+0)=*(pcxpal+a*3+0);
      *(newpal+idx[a]*3+1)=*(pcxpal+a*3+1);
      *(newpal+idx[a]*3+2)=*(pcxpal+a*3+2);
    }
  printf("Saving %s..\n",params[2]);
  savepcx8(pcxpic,newpal,xwid,ywid,params[2]);
  printf("Done.\n");
}
