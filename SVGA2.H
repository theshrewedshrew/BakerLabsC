/*
	(C)Copyright of program produced by Wang Xuancong (HCJC/02S33).
*/
/*		!!!Warning!!!
	Do NOT include GRAPHICS.H if you have included this header file.
	Graphic functions for different graphic systems are not compatible.
	Users: In order to optimise the speed,these functions do not have
		error-check features,please use them carefully.
		Moreover,all pixel functions assume that the BIOS
		setpage	function does not change the value of CX. If so,
		XXXpixel(...) cannot draw correctly,and please contact me.
	Once initgraph() is successful,putpixel,getpixel and line functions
		will become universal and can be used for any graphic mode.
	Warning:No matter whether initgraph() has been successful or not,you
		must use closegraph() before exit,otherwise it will cause
		crash.
*/
#include <dos.h>
#include <conio.h>
#include <alloc.h>
#define VGA_320_200_256		0x13
#define SVGA_400_300_256	0x122
#define SVGA_640_400_256 	0x100
#define SVGA_640_480_256 	0x101
#define SVGA_800_600_256	0x103
#define SVGA_1024_768_256 	0x105
#define SVGA_1024_768_15B	0x116
#define SVGA_1024_768_16B	0x117
#define SVGA_1024_768_24B	0x118
#define SVGA_1280_1024_256	0x107
#define SVGA_1280_1024_15B 	0x119
#define SVGA_1280_1024_16B 	0x11a
#define SVGA_1280_1024_24B	0x11b
#define SVGA_1600_1200_256	0x11c
#define SVGA_1600_1200_15B 	0x11d
#define SVGA_1600_1200_16B  0x11e
#define SVGA_800_600_15B 	0x113
#define SVGA_800_600_16B 	0x114
#define SVGA_640_400_16B	0x108
#define SVGA_320_200_15B 	0x10d
#define SVGA_320_200_16B 	0x10e
#define SVGA_320_240_256	0x120
#define SVGA_320_240_16B	0x121
#define SVGA_640_480_15B 	0x110
#define SVGA_640_480_16B 	0x111
#define SVGA_400_300_16B	0x123
#define SVGA_640_480_24B	0x112
#define SVGA_800_600_24B	0x115
#define SVGA_640_400_24B	0x10c

#define M256	1
#define M16B	2
#define M24B	3
#define M32B	4
#define MS1K	11
#define MS2K	12
#define MS4K	14

struct _SVGA{
	unsigned mode_attr;
	unsigned char winA_attr,winB_attr;
	unsigned wingranularity;
	unsigned winsize;
	unsigned winA_seg;
	unsigned winB_seg;
	void far (*func)();
	unsigned bytesperscanline;
	unsigned Xresolution;
	unsigned Yresolution;
	unsigned char Xcharsize,Ycharsize;
	unsigned char numofplanes;
	unsigned char bitsperpixel;
	unsigned char numberofbanks;
	unsigned char memorymodel;
	unsigned char banksize;
	unsigned char numberofimagepages;
	unsigned char reserved1;
	unsigned char redmasksize;
	unsigned char redfieldposition;
	unsigned char greenmasksize;
	unsigned char greenfieldposition;
	unsigned char bluemasksize;
	unsigned char bluefieldposition;
	unsigned char rsvdmasksize;
	unsigned char directcolormodeinfo;
	unsigned char reserved2;
}*_SVGA1;

/*Useful globals.*/
unsigned g_Xresolution;
unsigned g_Yresolution;
unsigned g_Xcenter;
unsigned g_Ycenter;
unsigned g_bytesperline;
unsigned char g_bitsperpixel;

struct _SVGA_detail{
	char a[4];
	unsigned ver;
	char far *inc;
	long ability;
	unsigned far *table;
	unsigned mem;
	}*_SVGA2;
unsigned char far *_vbuff=(unsigned char far*)0xa0000000;
unsigned char RGB_BLACK[3]={0,0,0};
unsigned char RGB_WHITE[3]={0xff,0xff,0xff};
unsigned far *_vbuffi=(unsigned far*)0xa0000000;
unsigned page_num=0,_scr_width,no_of_pages=0,color_mode=0;
void far _NULL(){}
void far (*_bios_setpage_func)()=_NULL;
void (*putpixel)(unsigned,unsigned,unsigned char*)=(void(*)(unsigned,unsigned,unsigned char*))_NULL;
void (*getpixel)(unsigned,unsigned,unsigned char*)=(void(*)(unsigned,unsigned,unsigned char*))_NULL;
void closegraph()
{
 _AX=3;
 geninterrupt(0x10);
 putpixel=(void(*)(unsigned,unsigned,unsigned char*))_NULL;
 getpixel=(void(*)(unsigned,unsigned,unsigned char*))_NULL;
 _bios_setpage_func=_NULL;
 color_mode=0;
}
int getsvgamode()
{
 _AX=0x4f03;
 geninterrupt(0x10);
 return _BX;
}

/*Very useful,it sets video buffer A000:0000 towards different positions on the screen.*/
void setpage(unsigned int page)
{
 asm {
	mov dx,page
	cmp dx,page_num
	jz end
	xor bx,bx
	call dword ptr [_bios_setpage_func]
 }
 page_num=page;
 end:
}

/*Notice:for all drawing functions,_x is the number of line,_y is the number of column.*/

/*For 1024*768*256 mode only, very fast!
It can draw 5,000,000 pixels in order within 1 second on PC300.
*/
void putpixel105h(unsigned _x,unsigned _y,unsigned char *_color)
{
 _DX=_x;
 _CX=_DX;
 _DX>>=6;
 if(_DX!=page_num){
		_BX^=_BX;
		page_num=_DX;
		_bios_setpage_func();
		}
 _CX&=63;
 _CX<<=10;
 _CX+=_y;
 _vbuff[_CX]=_color[0];
 /*setpage(_x>>6);
 _vbuff[((_x&63)<<10)+_y]=_color;
 A bit slower,but more like C++ source code.
 */
}
void getpixel105h(unsigned _x,unsigned _y,unsigned char*_color)
{
 _DX=_x;
 _CX=_DX;
 _DX>>=6;
 if(_DX!=page_num){
		_BX^=_BX;
		page_num=_DX;
		_bios_setpage_func();
		}
 _CX&=63;
 _CX<<=10;
 _CX+=_y;
 _color[0]=_vbuff[_CX];
 /*setpage(_x>>6);
 return (_vbuff[((_x&63)<<10)+_y]);
 A bit slower,but more like C++ source code.
 */
}

/*For 1024*768*16-Bit_color graphic mode only,very fast!
It can draw about 4,500,000 pixels in order within 1 second on PC300.
*/
void putpixel116h(unsigned _x,unsigned _y,unsigned*_color)
{
 _DX=_x;
 _CX=_DX;
 _DX>>=5;
 if(_DX!=page_num){
		_BX^=_BX;
		page_num=_DX;
		_bios_setpage_func();
		}
 _CX&=31;
 _CX<<=10;
 _CX+=_y;
 _vbuffi[_CX]=_color[0];
}
void getpixel116h(unsigned _x,unsigned _y,unsigned*_color)
{
 _DX=_x;
 _CX=_DX;
 _DX>>=5;
 if(_DX!=page_num){
		_BX^=_BX;
		page_num=_DX;
		_bios_setpage_func();
		}
 _CX&=31;
 _CX<<=10;
 _CX+=_y;
 _color[0]=_vbuffi[_CX];
}
/*For 1024*768*32-Bit color graphic mode only,very fast!
It can draw about 4,000,000 pixels in order within 1 second on PC300.
*/
void putpixel118h32(unsigned _x,unsigned _y,unsigned char*_color)
{
 _DX=_x;
 _CX=_DX;
 _DX>>=4;
 if(_DX!=page_num){
		_BX^=_BX;
		page_num=_DX;
		_bios_setpage_func();
		}

 _CX&=15;
 _DX=_y;

 _CX<<=12;
 _DX<<=2;

 _CX+=_DX;
 asm{
	mov dx,0a000h
	mov bx,cx
	mov es,dx
	mov ax,word ptr _color[0]
	mov es:[bx],ax
	mov ax,word ptr _color[2]
	mov es:[bx+2],ax
	}
}
void getpixel118h32(unsigned _x,unsigned _y,unsigned char*_color)
{
 _DX=_x;
 _CX=_DX;
 _DX>>=4;
 if(_DX!=page_num){
		_BX^=_BX;
		page_num=_DX;
		_bios_setpage_func();
		}

 _CX&=15;
 _DX=_y;

 _CX<<=12;
 _DX<<=2;

 _CX+=_DX;
 asm{
	mov dx,0a000h
	mov bx,cx
	mov es,dx
	mov ax,es:[bx]
	mov word ptr _color[0],ax
	mov ax,es:[bx+2]
	mov word ptr _color[2],ax
	}
}

/*For any 32-Bit-color graphic mode,fast!
It can draw 1,500,000 pixels in order within 1 second on PC300.
*/
void putpixel32b(unsigned _x,unsigned _y,unsigned char*_color)
{
 _x*=_scr_width;
 _BX=_y;
 _BX<<=2;

 _AX+=_BX;
 _CX=_AX;
 asm jnc norm1
 _DX++;
 norm1:
 if(_DX!=page_num){
	_BX^=_BX;
	page_num=_DX;
	_bios_setpage_func();
	}
 _vbuff[_CX]=_color[0];
 _vbuff[_CX+1]=_color[1];
 _vbuff[_CX+2]=_color[2];
}
void getpixel32b(unsigned _x,unsigned _y,unsigned char *_color)
{
 _x*=_scr_width;
 _BX=_y;
 _BX<<=2;

 _AX+=_BX;
 _CX=_AX;
 asm jnc norm1
 _DX++;
 norm1:
 if(_DX!=page_num){
	_BX^=_BX;
	page_num=_DX;
	_bios_setpage_func();
	}
 _color[0]=_vbuff[_CX];
 _color[1]=_vbuff[_CX+1];
 _color[2]=_vbuff[_CX+2];
}

/*For any 24-Bit-color graphic mode,a bit slow!
It can draw 1,000,000 pixels in order within 1 second on PC300.
*/
void putpixel24b(unsigned _x,unsigned _y,unsigned char*_color)
{
 _x*_scr_width;// was * then *=
 _BX=_y;
 _BX<<=1;
 _BX+=_y;
 _AX+=_BX;
 _CX=_AX;
 asm jnc norm1
 _DX++;
 norm1:
 if(_DX!=page_num)
 {
	_BX^=_BX;
	page_num=_DX;
	_bios_setpage_func();
	}
 _vbuff[_CX]=_color[2];

 _CX++;
 asm jnz norm2
 page_num++;
 _DX=page_num;
	_BX^=_BX;
	_bios_setpage_func();
 norm2:
 _vbuff[_CX]=_color[1];

 _CX++;
 asm jnz norm3
 page_num++;
 _DX=page_num;
	_BX^=_BX;
	_bios_setpage_func();
 norm3:
 _vbuff[_CX]=_color[0];
}
void getpixel24b(unsigned _x,unsigned _y,unsigned char*_color)
{
 _x*=_scr_width;
 _BX=_y;
 _BX<<=1;
 _BX+=_y;
 _AX+=_BX;
 _CX=_AX;
 asm jnc norm1
 _DX++;
 norm1:
 if(_DX!=page_num){
	_BX^=_BX;
	page_num=_DX;
	_bios_setpage_func();
	}
 _color[2]=_vbuff[_CX];

 _CX++;
 asm jnz norm2
 page_num++;
 _DX=page_num;
	_BX^=_BX;
	_bios_setpage_func();
 norm2:
 _color[1]=_vbuff[_CX];

 _CX++;
 asm jnz norm3
 page_num++;
 _DX=page_num;
	_BX^=_BX;
	_bios_setpage_func();
 norm3:
 _color[0]=_vbuff[_CX];
}

/*For any 16-Bit-color graphic mode,fast!
It can draw 3,500,000 pixels in order within 1 second on PC300.
*/
void putpixel16b(unsigned _x,unsigned _y,unsigned *_color)
{
 _x*=_scr_width;
 _y<<=1;
 _AX+=_y;
 asm jnc norm
 _DX++;
 norm:
 _CX=_AX;
 if(_DX!=page_num){
		_BX^=_BX;
		page_num=_DX;
		_bios_setpage_func();
		}
 _AX=_color[0];
 asm{
	mov bx,0a000h
	mov es,bx
	mov bx,cx
	mov es:[bx],ax
	}
}
void getpixel16b(unsigned _x,unsigned _y,unsigned*_color)
{
 _x*=_scr_width;
 _y<<=1;
 _AX+=_y;
 asm jnc norm
 _DX++;
 norm:
 _CX=_AX;
 if(_DX!=page_num){
		_BX^=_BX;
		page_num=_DX;
		_bios_setpage_func();
		}
 asm{
	mov dx,0a000h
	mov bx,cx
	mov es,dx
	mov ax,es:[bx]
	}
 _color[0]=_AX;
}

/*For any 256-color graphic mode, very fast!
It can draw 4,000,000 pixels in order within 1 second on PC300.
*/
void putpixel256(unsigned _x,unsigned _y,unsigned char *_color)
{
 _x*=_scr_width+_y;
 asm jnc norm
 _DX++;
 norm:
 _CX=_AX;
 if(_DX!=page_num){
		_BX^=_BX;
		page_num=_DX;
		_bios_setpage_func();
		}
 _vbuff[_CX]=_color[0];
}
void getpixel256(unsigned _x,unsigned _y,unsigned char*_color)
{
 _x*=_scr_width+_y;
 asm jnc norm
 _DX++;
 norm:
 _CX=_AX;
 if(_DX!=page_num){
		_BX^=_BX;
		page_num=_DX;
		_bios_setpage_func();
		}
 _color[0]=_vbuff[_CX];
}

char _signiture1[4]="VESA";
char _signiture2[4]="VBE2";
/* Initialize SVGA graphic system
Return value:
	0: successful;
	1: video card does not support VESA SVGA graphic system;
	2: video card does not support the required graphic mode;
	3: unknown graphic mode,putpixel and getpixel functions are not enabled;
	4: not enough memory.
*/
int initgraph(int _vmode)
{
 int x,_retv;
 char *_info_buffer;
 _info_buffer=(char*)malloc(512);
 if(_info_buffer==NULL)return 4;

 if(_vmode&0x0100){
	_ES=FP_SEG(_info_buffer);
	_DI=FP_OFF(_info_buffer);
	_AX=0x4f00;
	geninterrupt(0x10);
	for(x=0;x<4;x++){
		if(_signiture1[x]!=_info_buffer[x]){
			for(x=0;x<4;x++)if(_signiture2[x]!=_info_buffer[x])
				{_retv=1;goto end;}
			}
		}

	_SVGA2=(struct _SVGA_detail*)_info_buffer;
	for(x=0;_SVGA2->table[x]!=0xffff;x++)
		if(_SVGA2->table[x]==_vmode)goto found;
	_retv=2;
	goto end;

	found:
	_AX=0x4f02;
	_BX=_vmode;
	geninterrupt(0x10);	/* Disable this line for debugging */
	}
 else {
	_AX=_vmode;
	_AH^=_AH;
	geninterrupt(0x10);
	if(_vmode==0x13){
		_scr_width=320;
		no_of_pages=1;
		x=M256;
		goto skip;
		}
	_retv=0;
	goto end;
	}
 _ES=FP_SEG(_info_buffer);
 _DI=FP_OFF(_info_buffer);
 _AX=0x4f01;
 _CX=_vmode;
 geninterrupt(0x10);
 _SVGA1=(struct _SVGA*)_info_buffer;
 _bios_setpage_func=_SVGA1->func;
 page_num=0;

 _scr_width=_SVGA1->bytesperscanline;
 _scr_width*=(_SVGA1->Yresolution);
 if(_AX)_DX++;
 no_of_pages=_DX;

 switch(_SVGA1->bitsperpixel){
	case 8:	color_mode=x=M256;break;
	case 15:
	case 16:color_mode=x=M16B;break;
	case 24:color_mode=x=M24B;goto skip;
	case 32:color_mode=x=M32B;break;
	default:_retv=3;goto end;
	}
 if(_SVGA1->Xresolution==1024)x+=10;

 skip:
 g_Xresolution=_SVGA1->Xresolution;
 g_Yresolution=_SVGA1->Yresolution;
 g_bitsperpixel=_SVGA1->bitsperpixel;
 g_bytesperline=_SVGA1->bytesperscanline;
 g_Xcenter=g_Xresolution>>1;
 g_Ycenter=g_Yresolution>>1;

 switch(x){
	case M256:putpixel=putpixel256;
		  getpixel=getpixel256;
		  break;
	case M16B:putpixel=(void(*)(unsigned,unsigned,unsigned char*))putpixel16b;
		  getpixel=(void(*)(unsigned,unsigned,unsigned char*))getpixel16b;
		  break;
	case M24B:putpixel=putpixel24b;
		  getpixel=getpixel24b;
		  break;
	case M32B:putpixel=putpixel32b;
		  getpixel=getpixel32b;
		  break;
	case MS1K:putpixel=putpixel105h;
		  getpixel=getpixel105h;
		  break;
	case MS2K:putpixel=(void(*)(unsigned,unsigned,unsigned char*))putpixel116h;
		  getpixel=(void(*)(unsigned,unsigned,unsigned char*))getpixel116h;
		  break;
	case MS4K:putpixel=putpixel118h32;
		  getpixel=getpixel118h32;
		  break;
	default	 :_retv=3;goto end;
	}
 _retv=0;
 end:
 free(_info_buffer);
 return _retv;
}
/*Set the current 64K buffer A000:0000 to all zero.*/
void clr_vbuffer()
{
 asm{
	cld
	mov ax,0a000h
	mov es,ax
	xor di,di
	xor ax,ax
	mov cx,0ffffh
	repnz stosw
	}
}
void clr_screen()
{
 unsigned _temp=0;
 for(_BX^=_BX;_temp<no_of_pages;_temp++){
	_DX=_temp;
	_bios_setpage_func();
	clr_vbuffer();
	}
 page_num=no_of_pages-1;
}
/*	DAC table	For 256-color graphic modes only!
	Color index		RED	GREEN	BLUE
		 0                  #0	#1	#2
		 1                  #3      #4	#5
		 2                  #6      #7      #8
	     :                  :	:	:
		 :                  :	:	:
	     255                #2FD    #2FE    #2FF
	(#N means Nth byte)
Note:only the first 6 bits counting from the right of each byte writen into
	the DAC are effective,because DAC color only support 2^18 colors.
Therefore,the length of the DAC table is 3*256=768 bytes in length.*/
void writeDAC(unsigned char far *DACtable)
{
 _SI=FP_OFF(DACtable);
 _AX=FP_SEG(DACtable);
 asm{
	push ds
	cld
	mov ds,ax
	mov dx,3c8h
	xor al,al
	out dx,al
	inc dx
	mov cx,0x300
//	repnz outsb	/*80286 instruction*/
	pop ds
    }
}
void readDAC(unsigned char far *DACtable)
{
 _DI=FP_OFF(DACtable);
 _ES=FP_SEG(DACtable);
 asm{
	cld
	mov dx,3c7h
	xor al,al
	out dx,al
	add dx,2
	mov cx,0x300
//	repnz insb	/*80286 instruction*/
	}
}
void setDACcolor(unsigned char color_index,unsigned char _red,
			unsigned char _green,unsigned char _blue)
{
 asm{
	cld
	mov dx,3c8h
	mov al,color_index
	out dx,al
	inc dx
	mov al,_red
	out dx,al
	mov al,_green
	out dx,al
	mov al,_blue
	out dx,al
	}
}

void getDACcolor(unsigned char color_index,unsigned char *_red,
			unsigned char *_green,unsigned char *_blue)
{
 asm{
	cld
	mov dx,3c7h
	mov al,color_index
	out dx,al
	add dx,2
	in al,dx
	}
 *_red=_AL;
 _AL=inportb(_DX);
 *_green=_AL;
 _AL=inportb(_DX);
 *_blue=_AL;
}

/* Solid line function*/
void line(int x1,int y1,int x2,int y2,unsigned char *_color)
{
 unsigned x_diff=abs(x1-x2),y_diff=abs(y1-y2),_cont;
 int _x,_y;

 if(y1>y2){/*Swap the 2 points*/
	_x=x2;
	_y=y2;
	x2=x1;
	y2=y1;
	x1=_x;
	y1=_x;
	goto ins;
	}
	_x=x1;
	_y=y1;
 ins:
	if(x_diff<y_diff){
		_cont=y_diff/2;
		if(x1>x2){
			for(;_y<=y2;_y++,_cont+=x_diff){
				if(_cont>=y_diff){_x--;_cont-=y_diff;}
				putpixel(_x,_y,_color);
				}
			}
		else{
			for(;_y<=y2;_y++,_cont+=x_diff){
				if(_cont>=y_diff){_x++;_cont-=y_diff;}
				putpixel(_x,_y,_color);
				}
			}
		}
	else{
		_cont=x_diff/2;
		if(x1>x2){
			for(;_x>=x2;_x--,_cont+=y_diff){
				if(_cont>=x_diff){_y++;_cont-=x_diff;}
				putpixel(_x,_y,_color);
				}
			}
		else{
			for(;_x<=x2;_x++,_cont+=y_diff){
				if(_cont>=x_diff){_y++;_cont-=x_diff;}
				putpixel(_x,_y,_color);
				}
			}
		}
}

/* Dotted line function */
void dotline(int x1,int y1,int x2,int y2,unsigned no_of_dots,
			unsigned char *_color)
{
 unsigned x_diff=abs(x1-x2),y_diff=abs(y1-y2),_cont=0,_cont2=0;
 int _x,_y;

 if(y1>y2){/*Swap the 2 points*/
	_x=x2;
	_y=y2;
	x2=x1;
	y2=y1;
	x1=_x;
	y1=_x;
	goto ins;
	}
	_x=x1;
	_y=y1;
 ins:
	putpixel(_x,_y,_color);
	if(x_diff<=y_diff){
		if(no_of_dots>y_diff)no_of_dots=y_diff;
		if(x1>x2){
			for(;_y<=y2;_y++,_cont+=x_diff){
				if(_cont>=y_diff){_x--;_cont-=y_diff;}
				_cont2+=no_of_dots;
				if(_cont2>=y_diff){
					_cont2-=y_diff;
					putpixel(_x,_y,_color);
					}
				}
			}
		else{
			for(;_y<=y2;_y++,_cont+=x_diff){
				if(_cont>=y_diff){_x++;_cont-=y_diff;}
				_cont2+=no_of_dots;
				if(_cont2>=y_diff){
					_cont2-=y_diff;
					putpixel(_x,_y,_color);
					}
				}
			}
		}
	else{
		if(no_of_dots>x_diff)no_of_dots=x_diff;
		if(x1>x2){
			for(;_x>=x2;_x--,_cont+=y_diff){
				if(_cont>=x_diff){_y++;_cont-=x_diff;}
				_cont2+=no_of_dots;
				if(_cont2>=x_diff){
					_cont2-=x_diff;
					putpixel(_x,_y,_color);
					}
				}
			}
		else{
			for(;_x<=x2;_x++,_cont+=y_diff){
				if(_cont>=x_diff){_y++;_cont-=x_diff;}
				_cont2+=no_of_dots;
				if(_cont2>=x_diff){
					_cont2-=x_diff;
					putpixel(_x,_y,_color);
					}
				}
			}
		}
}
