#include "GT.hpp"

void displaypicture(void)
{
	//glClear(GL_COLOR_BUFFER_BIT);
	//��������
	glDrawPixels(imagewidth, imageheight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixeldata);
	//---------------------------------
	glFlush();
	glutSwapBuffers();
}


void read_bmp_file(int argc, char *argv[])
{
	//���ļ�
	FILE* pfile = fopen("1.bmp", "rb");
	if (pfile == 0) exit(0);
	//��ȡͼ���С
	fseek(pfile, 0x0012, SEEK_SET);
	fread(&imagewidth, sizeof(imagewidth), 1, pfile);
	fread(&imageheight, sizeof(imageheight), 1, pfile);


	//�����������ݳ���
	pixellength = imagewidth * 3;
	while (pixellength % 4 != 0)pixellength++;
	pixellength *= imageheight;


	//��ȡ��������
	pixeldata = (GLubyte*)malloc(pixellength);
	if (pixeldata == 0) exit(0);
	fseek(pfile, 54, SEEK_SET);
	fread(pixeldata, pixellength, 1, pfile);

	//�ر��ļ�
	fclose(pfile);
	//��ʼ��glut����
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

//Demo ���

double angle;
void initialize()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	//���ù���  
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
	//ָ���ӿ�  
	glViewport(0, 0, width, height);

	//ͶӰ�任---ƽ��ͷ��  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLdouble)width / (GLdouble)height, 0.1, 10000.0);
}

static void displaychahu(void)
{
	//��ͼ�任��ָ�����  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();//��һ��4��4�ĵ�λ�������滻��ǰ����
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//ģ�ͱ任  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0);//ָ����ɫ

	glPushMatrix();//������ջ
	glRotatef(angle, 0.0, 1.0, 0.0);//��Ԫ��
	angle++;
	glutSolidTeapot(1.0);//���
	
	glPopMatrix();//�����ջ

	glutSwapBuffers();//˫���� ����������������ָ��
	/*������������ 
		ǰ̨����ͺ�̨���塣ǰ̨���弴���ǿ�������Ļ��
		��̨���������ڴ浱�У���������˵�ǲ��ɼ��ġ�ÿ�ε����л�ͼ�������ں�̨�����н��У� 
		���������ʱ�� �ѻ��Ƶ����ս�����Ƶ���Ļ�ϣ� 
		������ ���ǿ�������GDIԪ��ͬʱ��������Ļ�ϣ��Ӷ������Ƶ��ˢ�µ��µĻ�����˸���⡣
    */
	glutPostRedisplay();//���»���buffer ��GL��ÿ֡ÿ��ѭ��ִ��һ�Σ�Ҳ������Ϊ��Ӧ������ִ��
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