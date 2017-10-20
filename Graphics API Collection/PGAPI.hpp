#pragma once
#ifndef PGAPI_HPP
#define PGAPI_HPP
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")


#include "PGAPI.hpp"
#include "GT.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
//
////
//#include <windows.h>
#include <tchar.h>



typedef unsigned int IUINT32;//32λ��������   RGBA��ɫ��ԪҲ������λʮ��������ɫ��ʾ

//=====================================================================
// ��ѧ�⣺�˲���Ӧ�ò�����⣬��Ϥ D3D ����任����
//=====================================================================
typedef struct { float m[4][4]; } matrix_t;
typedef struct { float x, y, z, w; } vector_t;
typedef vector_t point_t;

int CMID(int x, int min, int max);

float interp(float x1, float x2, float t);

void vector_add(vector_t *z, const vector_t *x, const vector_t *y);

void vector_sub(vector_t *z, const vector_t *x, const vector_t *y);

float vector_dotproduct(const vector_t *x, const vector_t *y);

void vector_crossproduct(vector_t *z, const vector_t *x, const vector_t *y);

void vector_interp(vector_t *z, const vector_t *x1, const vector_t *x2, float t);

void vector_normalize(vector_t *v);

//
//��дҪ����д������  ����c++11���ͱ��
//��ɣ�
//1.��ֵ����
//2.��ģ
//3.�Ӽ�����˲�ˡ�ʸ����ֵ
//4.��һ






void matrix_add(matrix_t *c, const matrix_t *a, const matrix_t *b);

void matrix_sub(matrix_t *c, const matrix_t *a, const matrix_t *b);

void matrix_mul(matrix_t *c, const matrix_t *a, const matrix_t *b);

void matrix_scale(matrix_t *c, const matrix_t *a, float f);

void matrix_apply(vector_t *y, const vector_t *x, const matrix_t *m);

void matrix_set_identity(matrix_t *m);

void matrix_set_zero(matrix_t *m);

void matrix_set_translate(matrix_t *m, float x, float y, float z);

void matrix_set_scale(matrix_t *m, float x, float y, float z);

void matrix_set_rotate(matrix_t *m, float x, float y, float z, float theta);

void matrix_set_lookat(matrix_t *m, const vector_t *eye, const vector_t *at, const vector_t *up);

void matrix_set_perspective(matrix_t *m, float fovy, float aspect, float zn, float zf);


//=====================================================================
// ����任
//=====================================================================
typedef struct {
	matrix_t world;         // ��������任
	matrix_t view;          // ��Ӱ������任
	matrix_t projection;    // ͶӰ�任
	matrix_t transform;     // transform = world * view * projection
	float w, h;             // ��Ļ��С
}	transform_t;

void transform_update(transform_t *ts);

void transform_init(transform_t *ts, int width, int height);

void transform_apply(const transform_t *ts, vector_t *y, const vector_t *x);

int transform_check_cvv(const vector_t *v);

void transform_homogenize(const transform_t *ts, vector_t *y, const vector_t *x);



////��������дҪ��c++11���ͱ��
//1.���������������Ӽ���
//2.ƽ�ƣ����ţ���ת�����������
//3.͸�Ӿ���
//4.������¼��� transform = world * view * projection
//5.��ʼ��������Ļ
//6.ʸ��ͶӰ
//7.���������� CVV
//8.��һ��




//=====================================================================
// ���μ��㣺���㡢ɨ���ߡ���Ե�����Ρ���������
//=====================================================================
typedef struct { float r, g, b; } color_t;
typedef struct { float u, v; } texcoord_t;
typedef struct { point_t pos; texcoord_t tc; color_t color; float rhw; } vertex_t;

typedef struct { vertex_t v, v1, v2; } edge_t;
typedef struct { float top, bottom; edge_t left, right; } trapezoid_t;
typedef struct { vertex_t v, step; int x, y, w; } scanline_t;

//�ض��幤��



void vertex_rhw_init(vertex_t *v);


void vertex_interp(vertex_t *y, const vertex_t *x1, const vertex_t *x2, float t);


void vertex_division(vertex_t *y, const vertex_t *x1, const vertex_t *x2, float w);


void vertex_add(vertex_t *y, const vertex_t *x);

int trapezoid_init_triangle(trapezoid_t *trap, const vertex_t *p1,
	                     const vertex_t *p2, const vertex_t *p3);

void trapezoid_init_scan_line(const trapezoid_t *trap, scanline_t *scanline, int y);

void trapezoid_edge_interp(trapezoid_t *trap, float y);

//�����෽����д































//=====================================================================
// ��Ⱦ�豸
//=====================================================================
//typedef struct {
//	transform_t transform;      // ����任��
//	int width;                  // ���ڿ��
//	int height;                 // ���ڸ߶�
//	IUINT32 **framebuffer;      // ���ػ��棺framebuffer[y] ����� y�� //����ָ��
//	float **zbuffer;            // ��Ȼ��棺zbuffer[y] Ϊ�� y��ָ��
//	IUINT32 **texture;          // ����ͬ����ÿ������
//	int tex_width;              // ������
//	int tex_height;             // ����߶�
//	float max_u;                // ��������ȣ�tex_width - 1
//	float max_v;                // �������߶ȣ�tex_height - 1
//	int render_state;           // ��Ⱦ״̬
//	IUINT32 background;         // ������ɫ
//	IUINT32 foreground;         // �߿���ɫ
//}	device_t;
//
//
//#define RENDER_STATE_WIREFRAME      1		// ��Ⱦ�߿�
//#define RENDER_STATE_TEXTURE        2		// ��Ⱦ����
//#define RENDER_STATE_COLOR          4		// ��Ⱦ��ɫ
//
//
//
//



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//�豸

// �豸��ʼ����fbΪ�ⲿ֡���棬�� NULL �������ⲿ֡���棨ÿ�� 4�ֽڶ��룩
//void device_init(device_t *device, int width, int height, void *fb);
//
//void device_destroy(device_t *device);
//
//void device_set_texture(device_t *device, void *bits, long pitch, int w, int h);
//
//void device_clear(device_t *device, int mode);
//
//void device_pixel(device_t *device, int x, int y, IUINT32 color);
//
//void device_draw_line(device_t *device, int x1, int y1, int x2, int y2, IUINT32 c);
//
//IUINT32 device_texture_read(const device_t *device, float u, float v);

//=====================================================================
// ��Ⱦʵ��
//=====================================================================

//void device_draw_scanline(device_t *device, scanline_t *scanline);
//
//
//void device_render_trap(device_t *device, trapezoid_t *trap);
//
//
//void device_draw_primitive(device_t *device, const vertex_t *v1,
//	const vertex_t *v2, const vertex_t *v3);
//
//
//


//=====================================================================
// Win32 ���ڼ�ͼ�λ��ƣ�Ϊ device �ṩһ�� DibSection �� FB
//=====================================================================


//
//int screen_w, screen_h, screen_exit = 0;
//int screen_mx = 0, screen_my = 0, screen_mb = 0;
//int screen_keys[512];	// ��ǰ���̰���״̬
//static HWND screen_handle = NULL;		// ������ HWND
//static HDC screen_dc = NULL;			// ���׵� HDC
//static HBITMAP screen_hb = NULL;		// DIB
//static HBITMAP screen_ob = NULL;		// �ϵ� BITMAP
//unsigned char *screen_fb = NULL;		// frame buffer
//long screen_pitch = 0;
//
//
////�豸����
//int screen_init(int w, int h, const TCHAR *title);	// ��Ļ��ʼ��
//int screen_close(void);								// �ر���Ļ
//void screen_dispatch(void);							// ������Ϣ
//void screen_update(void);							// ��ʾ FrameBuffer
//
//													// win32 event handler
//static LRESULT screen_events(HWND, UINT, WPARAM, LPARAM);
//
//
////GDI��׼
//
////��ʼ������
////
////
//int screen_init(int w, int h, const TCHAR *title);
//
//
//int screen_close(void);
//
//
//static LRESULT screen_events(HWND hWnd, UINT msg,
//	WPARAM wParam, LPARAM lParam);
//
//
//void screen_dispatch(void);
//
//
//void screen_update(void);
//
//vertex_t mesh[8] = {
//	{ { 1, -1,  1, 1 },{ 0, 0 },{ 1.0f, 0.2f, 0.2f }, 1 },
//	{ { -1, -1,  1, 1 },{ 0, 1 },{ 0.2f, 1.0f, 0.2f }, 1 },
//	{ { -1,  1,  1, 1 },{ 1, 1 },{ 0.2f, 0.2f, 1.0f }, 1 },
//	{ { 1,  1,  1, 1 },{ 1, 0 },{ 1.0f, 0.2f, 1.0f }, 1 },
//	{ { 1, -1, -1, 1 },{ 0, 0 },{ 1.0f, 1.0f, 0.2f }, 1 },
//	{ { -1, -1, -1, 1 },{ 0, 1 },{ 0.2f, 1.0f, 1.0f }, 1 },
//	{ { -1,  1, -1, 1 },{ 1, 1 },{ 1.0f, 0.3f, 0.3f }, 1 },
//	{ { 1,  1, -1, 1 },{ 1, 0 },{ 0.2f, 1.0f, 0.3f }, 1 },
//};//Mesh define


//int mainLoop(void);







#endif // !PGAPI_HPP
