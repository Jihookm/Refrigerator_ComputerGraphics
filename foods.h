#pragma once
#include<GL/freeglut.h>
#include "bmpfuncs.h"
#include <gl/glut.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
GLuint texName[6];
GLuint texName2[3];
GLuint* texName3 = new GLuint();
GLuint texName4[3];
GLuint tmp;
GLUquadricObj* qobj = gluNewQuadric();
GLUquadricObj* qobj2 = gluNewQuadric();
GLUquadricObj* qobj3 = gluNewQuadric();
int coke_location = 0; //�ݶ��� ��ġ ����
int cider_location = 0;

void draw_axis(void)
{
	glLineWidth(1.5f);
	glBegin(GL_LINES);

	glColor4f(1.f, 0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(4.f, 0.f, 0.f);

	glColor4f(0.f, 1.f, 0.f, 1.f);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 4.f, 0.f);

	glColor4f(0.f, 0.f, 1.f, 1.f);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 0.f, 4.f);

	glEnd();
	glLineWidth(1);
}
void textureMapping_cube() {
	glGenTextures(6, texName);
	int imgwidth, imgheight, channels;
	for (int i = 0; i < 6; i++) {
		glBindTexture(GL_TEXTURE_2D, texName[i]);
		char buf[100];
		sprintf(buf, "img/TexImage%d.bmp", i);
		buf[strlen(buf)] = 0;
		uchar* img = readImageData(buf, &imgwidth, &imgheight, &channels);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, imgwidth, imgheight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
}
void draw_cube() {
	glColor3f(1.0, 1.0, 1.0);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, texName[0]);//-x
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0, 0);
	glTexCoord2f(0, 0); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(3, 0);  glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(3, 3);  glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0, 3);  glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texName[1]);//x
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0, 0);
	glTexCoord2f(0, 0);  glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1, 0);  glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1, 1);  glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0, 1);  glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texName[2]);//-y
	glBegin(GL_QUADS);
	glNormal3f(0, -1.0, 0);
	glTexCoord2f(0, 0);  glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1, 0);  glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1, 1);  glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0, 1);  glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texName[3]);//y
	glBegin(GL_QUADS);
	glNormal3f(0, 1.0, 0);
	glTexCoord2f(0, 0);  glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1, 0);  glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1, 1);  glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0, 1);  glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texName[4]);//z
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1.0);
	glTexCoord2f(0, 0);  glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1, 0);  glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1, 1);  glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0, 1);  glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texName[5]);//-z
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1.0);
	glTexCoord2f(0, 0);  glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1, 0);  glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1, 1);  glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0, 1);  glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	draw_axis();
}

void textureMapping_cylinder() {
	glGenTextures(3, texName2);
	int width, height, channels;
	glBindTexture(GL_TEXTURE_2D, texName2[0]);
	uchar* img = readImageData("img/CIDER_T.bmp", &width, &height, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texName2[1]);
	img = readImageData("img/coke.bmp", &width, &height, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texName2[2]);
	img = readImageData("img/CIDER_B.bmp", &width, &height, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}
void textureMapping_cider() {
	glGenTextures(3, texName4);
	int width, height, channels;
	glBindTexture(GL_TEXTURE_2D, texName4[0]);
	uchar* img = readImageData("img/CIDER_T.bmp", &width, &height, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texName4[1]);
	img = readImageData("img/CIDER_S.bmp", &width, &height, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texName4[2]);
	img = readImageData("img/CIDER_B.bmp", &width, &height, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}
void draw_cylinder() {
	glColor3f(1.0, 1.0, 1.0);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texName2[0]);
	gluDisk(qobj, 0, 0.5, 10, 10);

	glBindTexture(GL_TEXTURE_2D, texName2[1]);//quadric obj ��� : �ݶ��� ����
	gluCylinder(qobj, 0.5, 0.5, 1.5, 10, 10);

	glBindTexture(GL_TEXTURE_2D, texName2[2]);
	glTranslatef(0, 0, 1.5);
	gluDisk(qobj, 0, 0.5, 10, 10);

	//draw_axis();

}
void draw_cider() {
	glColor3f(1.0, 1.0, 1.0);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texName4[0]);
	gluDisk(qobj2, 0, 0.2, 10, 10);

	glBindTexture(GL_TEXTURE_2D, texName4[1]);//quadric obj ��� : �ݶ��� ����
	gluCylinder(qobj2, 0.2, 0.2, 0.8, 10, 10);

	glBindTexture(GL_TEXTURE_2D, texName4[2]);
	glTranslatef(0, 0, 0.8);
	gluDisk(qobj2, 0, 0.2, 10, 10);

	//draw_axis();

}
void textureMapping_sphere() {
	glGenTextures(1, texName3);
	int swidth, sheight, channels;
	glBindTexture(GL_TEXTURE_2D, *texName3);
	uchar* imgc = readImageData("img/EARTH.bmp", &swidth, &sheight, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, swidth, sheight, 0, GL_RGB, GL_UNSIGNED_BYTE, imgc);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

}
void draw_sphere() {
	glColor3f(1.0, 1.0, 1.0);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, *texName3);
	gluSphere(qobj3, 0.6, 10, 10);//���ڹٲٱ�
	//draw_axis();
}
void sub_menu_food(int option)
{
	switch (option) {
	case 11:
		coke_location = 1; //1~4: �õ�ĭ
		printf("Big Coke�� '�õ��� ù��° ĭ'�� �����մϴ�.\n");
		break;
	case 12:
		coke_location = 2;
		printf("Big Coke�� '�õ��� �ι�° ĭ'�� �����մϴ�.\n");
		break;
	case 13:
		coke_location = 3;
		printf("Big Coke�� '�õ��� ����° ĭ'�� �����մϴ�.\n");
		break;
	case 14:
		coke_location = 4;
		printf("Big Coke�� '�õ��� �׹�° ĭ'�� �����մϴ�.\n");
		break;
	case 15:
		coke_location = 5; //5~8: ����ĭ
		printf("Big Coke�� '����� ù��° ĭ'�� �����մϴ�.\n");
		break;
	case 16:
		coke_location = 6;
		printf("Big Coke�� '����� �ι�° ĭ'�� �����մϴ�.\n");
		break;
	case 17:
		coke_location = 7;
		printf("Big Coke�� '����� ����° ĭ'�� �����մϴ�.\n");
		break;
	case 18:
		coke_location = 8;
		printf("Big Coke�� '����� �׹�° ĭ'�� �����մϴ�.\n");
		break;
	case 19:
		cider_location = 1;
		printf("Cider�� '�õ��� ù��° ĭ'�� �����մϴ�.\n");
		break;
	case 20:
		cider_location = 2;
		printf("Cider�� '�õ��� �ι�° ĭ'�� �����մϴ�.\n");
		break;
	case 21:
		cider_location = 3;
		printf("Cider�� '�õ��� ����° ĭ'�� �����մϴ�.\n");
		break;
	case 22:
		cider_location = 4;
		printf("Cider�� '�õ��� �׹�° ĭ'�� �����մϴ�.\n");
		break;
	case 23:
		cider_location = 5;
		printf("Cider�� '����� ù��° ĭ'�� �����մϴ�.\n");
		break;
	case 24:
		cider_location = 6;
		printf("Cider�� '����� �ι�° ĭ'�� �����մϴ�.\n");
		break;
	case 25:
		cider_location = 7;
		printf("Cider�� '����� ����° ĭ'�� �����մϴ�.\n");
		break;
	case 26:
		cider_location = 8;
		printf("Cider�� '����� �׹�° ĭ'�� �����մϴ�.\n");
		break;
	case 30://�ݶ� �տ� ���
		if (cider_location == 9) {
			printf("���� ���̴ٸ� �տ��� ���ƾ� �մϴ�!!\n");
		}
		else {
			coke_location = 9;
			printf("Big Coke�� ������� �����ϴ�.\n");
		}
		break;
	case 31:
		if (coke_location == 9) {
			printf("���� �ݶ� �տ��� ���ƾ� �մϴ�!!\n");
		}
		else {
			cider_location = 9;
			printf("Cider�� ������� �����ϴ�.\n");
		}
		break;
	case 40: //�ݶ� ���� �� 1
		coke_location = 10;
		printf("Big Coke�� '�õ��� ù��° ��'�� �����մϴ�.\n");
		break;
	case 41: //�ݶ� ���� �� 2
		coke_location = 11;
		printf("Big Coke�� '�õ��� �ι�° ��'�� �����մϴ�.\n");
		break;
	case 42: //�ݶ� ������ �� 1
		coke_location = 12;
		printf("Big Coke�� '����� ù��° ��'�� �����մϴ�.\n");
		break;
	case 43: //�ݶ� ������ �� 2
		coke_location = 13;
		printf("Big Coke�� '����� �ι�° ��'�� �����մϴ�.\n");
		break;
	case 44: //���̴� ���� �� 1
		cider_location = 10;
		printf("Cider�� '�õ��� ù��° ��'�� �����մϴ�.\n");
		break;
	case 45: //���̴� ���� �� 2
		cider_location = 11;
		printf("Cider�� '�õ��� �ι�° ��'�� �����մϴ�.\n");
		break;
	case 46: //���̴� ������ �� 1
		cider_location = 12;
		printf("Cider�� '����� ù��° ��'�� �����մϴ�.\n");
		break;
	case 47: //���̴� ������ �� 2
		cider_location = 13;
		printf("Cider�� '����� �ι�° ��'�� �����մϴ�.\n");
		break;
	}
	glutPostRedisplay();
}