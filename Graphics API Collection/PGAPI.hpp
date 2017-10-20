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



typedef unsigned int IUINT32;//32位二进制数   RGBA颜色单元也就是四位十六进制颜色表示

//=====================================================================
// 数学库：此部分应该不用详解，熟悉 D3D 矩阵变换即可
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
//重写要求：重写向量类  采用c++11泛型编程
//完成：
//1.插值计算
//2.求模
//3.加减、点乘叉乘、矢量插值
//4.归一






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
// 坐标变换
//=====================================================================
typedef struct {
	matrix_t world;         // 世界坐标变换
	matrix_t view;          // 摄影机坐标变换
	matrix_t projection;    // 投影变换
	matrix_t transform;     // transform = world * view * projection
	float w, h;             // 屏幕大小
}	transform_t;

void transform_update(transform_t *ts);

void transform_init(transform_t *ts, int width, int height);

void transform_apply(const transform_t *ts, vector_t *y, const vector_t *x);

int transform_check_cvv(const vector_t *v);

void transform_homogenize(const transform_t *ts, vector_t *y, const vector_t *x);



////矩阵类重写要求：c++11泛型编程
//1.重载运算符：矩阵加减乘
//2.平移，缩放，旋转，设置摄像机
//3.透视矩阵
//4.矩阵更新计算 transform = world * view * projection
//5.初始化设置屏幕
//6.矢量投影
//7.检查其次坐标 CVV
//8.归一化




//=====================================================================
// 几何计算：顶点、扫描线、边缘、矩形、步长计算
//=====================================================================
typedef struct { float r, g, b; } color_t;
typedef struct { float u, v; } texcoord_t;
typedef struct { point_t pos; texcoord_t tc; color_t color; float rhw; } vertex_t;

typedef struct { vertex_t v, v1, v2; } edge_t;
typedef struct { float top, bottom; edge_t left, right; } trapezoid_t;
typedef struct { vertex_t v, step; int x, y, w; } scanline_t;

//重定义工作



void vertex_rhw_init(vertex_t *v);


void vertex_interp(vertex_t *y, const vertex_t *x1, const vertex_t *x2, float t);


void vertex_division(vertex_t *y, const vertex_t *x1, const vertex_t *x2, float w);


void vertex_add(vertex_t *y, const vertex_t *x);

int trapezoid_init_triangle(trapezoid_t *trap, const vertex_t *p1,
	                     const vertex_t *p2, const vertex_t *p3);

void trapezoid_init_scan_line(const trapezoid_t *trap, scanline_t *scanline, int y);

void trapezoid_edge_interp(trapezoid_t *trap, float y);

//顶点类方法重写































//=====================================================================
// 渲染设备
//=====================================================================
//typedef struct {
//	transform_t transform;      // 坐标变换器
//	int width;                  // 窗口宽度
//	int height;                 // 窗口高度
//	IUINT32 **framebuffer;      // 像素缓存：framebuffer[y] 代表第 y行 //二级指针
//	float **zbuffer;            // 深度缓存：zbuffer[y] 为第 y行指针
//	IUINT32 **texture;          // 纹理：同样是每行索引
//	int tex_width;              // 纹理宽度
//	int tex_height;             // 纹理高度
//	float max_u;                // 纹理最大宽度：tex_width - 1
//	float max_v;                // 纹理最大高度：tex_height - 1
//	int render_state;           // 渲染状态
//	IUINT32 background;         // 背景颜色
//	IUINT32 foreground;         // 线框颜色
//}	device_t;
//
//
//#define RENDER_STATE_WIREFRAME      1		// 渲染线框
//#define RENDER_STATE_TEXTURE        2		// 渲染纹理
//#define RENDER_STATE_COLOR          4		// 渲染颜色
//
//
//
//



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//设备

// 设备初始化，fb为外部帧缓存，非 NULL 将引用外部帧缓存（每行 4字节对齐）
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
// 渲染实现
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
// Win32 窗口及图形绘制：为 device 提供一个 DibSection 的 FB
//=====================================================================


//
//int screen_w, screen_h, screen_exit = 0;
//int screen_mx = 0, screen_my = 0, screen_mb = 0;
//int screen_keys[512];	// 当前键盘按下状态
//static HWND screen_handle = NULL;		// 主窗口 HWND
//static HDC screen_dc = NULL;			// 配套的 HDC
//static HBITMAP screen_hb = NULL;		// DIB
//static HBITMAP screen_ob = NULL;		// 老的 BITMAP
//unsigned char *screen_fb = NULL;		// frame buffer
//long screen_pitch = 0;
//
//
////设备函数
//int screen_init(int w, int h, const TCHAR *title);	// 屏幕初始化
//int screen_close(void);								// 关闭屏幕
//void screen_dispatch(void);							// 处理消息
//void screen_update(void);							// 显示 FrameBuffer
//
//													// win32 event handler
//static LRESULT screen_events(HWND, UINT, WPARAM, LPARAM);
//
//
////GDI标准
//
////初始化窗口
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
