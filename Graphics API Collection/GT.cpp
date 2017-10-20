#include "GT.hpp"

void displaypicture(void)
{
	//glClear(GL_COLOR_BUFFER_BIT);
	//绘制像素
	glDrawPixels(imagewidth, imageheight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixeldata);
	//---------------------------------
	glFlush();
	glutSwapBuffers();
}


void read_bmp_file(int argc, char *argv[])
{
	//打开文件
	FILE* pfile = fopen("1.bmp", "rb");
	if (pfile == 0) exit(0);
	//读取图像大小
	fseek(pfile, 0x0012, SEEK_SET);
	fread(&imagewidth, sizeof(imagewidth), 1, pfile);
	fread(&imageheight, sizeof(imageheight), 1, pfile);


	//计算像素数据长度
	pixellength = imagewidth * 3;
	while (pixellength % 4 != 0)pixellength++;
	pixellength *= imageheight;


	//读取像素数据
	pixeldata = (GLubyte*)malloc(pixellength);
	if (pixeldata == 0) exit(0);
	fseek(pfile, 54, SEEK_SET);
	fread(pixeldata, pixellength, 1, pfile);

	//关闭文件
	fclose(pfile);
	//初始化glut运行
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(imagewidth, imageheight);
	glutCreateWindow(FileName);
	glutDisplayFunc(&displaypicture);
	glutMainLoop();
	//-------------------------------------
	free(pixeldata);

}

//Demo 茶壶

double angle;
void initialize()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	//设置光照  
	const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

	const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat high_shininess[] = { 100.0f };

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

}

static void resize(int width, int height)
{
	//指定视口  
	glViewport(0, 0, width, height);

	//投影变换---平截头体  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLdouble)width / (GLdouble)height, 0.1, 10000.0);
}

static void displaychahu(void)
{
	//视图变换，指定相机  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();//用一个4×4的单位矩阵来替换当前矩阵
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//模型变换  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0);//指定颜色

	glPushMatrix();//矩阵入栈
	glRotatef(angle, 0.0, 1.0, 0.0);//四元数
	angle++;
	glutSolidTeapot(1.0);//茶壶
	
	glPopMatrix();//矩阵出栈

	glutSwapBuffers();//双缓冲 交换两个缓冲区的指针
	/*两个缓冲区： 
		前台缓冲和后台缓冲。前台缓冲即我们看到的屏幕，
		后台缓冲则在内存当中，对我们来说是不可见的。每次的所有绘图操作都在后台缓冲中进行， 
		当绘制完成时， 把绘制的最终结果复制到屏幕上， 
		这样， 我们看到所有GDI元素同时出现在屏幕上，从而解决了频繁刷新导致的画面闪烁问题。
    */
	glutPostRedisplay();//重新绘制buffer 在GL中每帧每个循环执行一次，也可设置为相应操作再执行
}


static void key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		exit(0);
		break;

	case '+':
		angle++;
		break;

	case '-':
		angle--;
		break;
	}

	glutPostRedisplay();
}
void Chahu(int argc, char *argv[])
{

	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(10, 10);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("GLUT Shapes");

	initialize();

	glutReshapeFunc(resize);
	glutDisplayFunc(displaychahu);
	glutKeyboardFunc(key);

	glutMainLoop();




}