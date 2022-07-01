#include <GL/glut.h>
#include <GL/freeglut.h>
#include"GL/glext.h"
#include<windows.h>
#include "ObjParser.h"
#include "bmpfuncs.h"
#include "foods.h"
#include<mmsystem.h>
#pragma comment(lib,"winmm")
#define M_PI 3.1415926535897
using std::cos;
using std::sin;
using std::sqrt;

// global variable for counting fps
volatile int frame = 0, time, timebase = 0;
volatile float fps;

/* texture mapping set variable */
GLuint textureMonkey;
bool antialiase_on = true;
double radius = 20;
double theta = 45, phi = 45;
double cam[3];
double center[3] = { 0, 0, 0 };
double up[3] = { 0, 1, 0 };
int cur_width, cur_height;

//open-close var
bool left_open = false;
float door_open_limit = 0;
bool right_open = false;
bool homebar_open = false;
bool inside_open = false;
bool all_open = false;
float trans = 0;
float trans_bar = 0;
bool ref_light = false;
bool howto = true;
// object var
ObjParser* monkey;
ObjParser* monkey1;
ObjParser* monkey2;
ObjParser* monkey3;
ObjParser* monkey4;
ObjParser* monkey5;
ObjParser* monkey6;
ObjParser* monkey7;
ObjParser* monkey8;
int ref_tex = 1;
// user-defined function
GLuint g_nCubeTex;
float g_nSkySize = 50;

void init(void);
void light_default();
void add_menu();
void get_resource(const char* str);

void mouse(int, int, int, int);
void mouseWheel(int, int, int, int);
void motion(int, int);
void passiveMotion(int, int);
void keyboard(unsigned char, int, int);
void special_keyboard(int, int, int);
void draw(void);
void resize(int, int);
void idle();
//...

/* Main method */
int main(int argc, char** argv)
{
	// glut initialize
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(400, 300);
	glutCreateWindow("GLUT Test");	// 위의 순서 무조건 고정

	// 사용자 초기화 함수
	init();

	// pop-up 메뉴 등록 함수
	add_menu();

	// 리소스 로드 함수
	get_resource("obj/ref_left.obj");
	monkey1= new ObjParser("obj/ref_right.obj");
	monkey2 = new ObjParser("obj/ref_body.obj");
	monkey3 = new ObjParser("obj/ref_homebar.obj");
	monkey4 = new ObjParser("obj/ref_leftbar.obj");
	monkey5 = new ObjParser("obj/ref_rightbar.obj");
	monkey6 = new ObjParser("obj/ref_left_door_bar.obj");
	monkey7 = new ObjParser("obj/ref_right_door_bar.obj");
	monkey8 = new ObjParser("obj/ref_homebar_inside.obj");

	/* Create a single window with a keyboard and display callback */
	glutMouseFunc(&mouse);
	glutMouseWheelFunc(&mouseWheel);
	glutMotionFunc(&motion);
	glutPassiveMotionFunc(&passiveMotion);
	glutKeyboardFunc(&keyboard);
	glutSpecialFunc(&special_keyboard);
	glutDisplayFunc(&draw);
	glutReshapeFunc(&resize);
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricDrawStyle(qobj2, GLU_FILL);
	gluQuadricNormals(qobj2, GLU_SMOOTH);
	glutIdleFunc(&idle);
	
	/* Run the GLUT event loop */
	glutMainLoop();

	return EXIT_SUCCESS;
}

void light_default() {
	glClearColor(0.f, 0.f, 0.f, 1.0f);

	/* Light0 조명 관련 설정 */
	GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat diffuseLight[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat specularLight[] = { 0.5f, 0.5f, 0.9f, 1.0f };
	GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	/********* light point position setting **********/
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	/* Light1 조명 관련 설정 */
	GLfloat ambientLight1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat diffuseLight1[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat specularLight1[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat light_position1[] = { 0.0, 0.0, 0.0, 1.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight1);

	/********* light point position setting **********/
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

	/************* spot position setting *************/
	/*GLfloat spot_direction[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);*/

	GLfloat specularMaterial[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat diffuseMaterial[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat ambientMaterial[] = { 0.2f, 0.2f, 0.2f, 1.0f };

	/************* Material  setting *************/
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMaterial);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, 30);


	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glDisable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	/* DEPTH TEST ENABLE */
	glFrontFace(GL_CW);	// CW CCW바꿔보면서 front face 변경해보기!
}

void setTextureMapping() {
	int imgWidth, imgHeight, channels;
	uchar* img=0;
	if (ref_tex == 1){
		img = readImageData("img/grey.bmp", &imgWidth, &imgHeight, &channels);
	}
	else if (ref_tex == 2) {
		img = readImageData("img/rainbow.bmp", &imgWidth, &imgHeight, &channels);
	}
	else if (ref_tex == 3) {
		img = readImageData("img/louis.bmp", &imgWidth, &imgHeight, &channels);
	}
	int texNum = 1;
	glGenTextures(texNum, &textureMonkey);
	glBindTexture(GL_TEXTURE_2D, textureMonkey);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//GL_REPEAT 둘중 하나 선택
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, imgWidth, imgHeight, GL_RGB, GL_UNSIGNED_BYTE, img);
}
void cubeTexture() {
	glGenTextures(1, &g_nCubeTex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, g_nCubeTex);
	int swidth, sheight, channels;
	uchar* img0 = readImageData("img/TexImage5.bmp", &swidth, &sheight, &channels);
	uchar* img1 = readImageData("img/left.bmp", &swidth, &sheight, &channels);
	uchar* img2 = readImageData("img/bottom.bmp", &swidth, &sheight, &channels);
	uchar* img3 = readImageData("img/top.bmp", &swidth, &sheight, &channels);
	uchar* img4 = readImageData("img/front.bmp", &swidth, &sheight, &channels);
	uchar* img5 = readImageData("img/back.bmp", &swidth, &sheight, &channels);

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, swidth,
		sheight, 0, GL_RGB, GL_UNSIGNED_BYTE, img0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, swidth,
		sheight, 0, GL_RGB, GL_UNSIGNED_BYTE, img1);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, swidth,
		sheight, 0, GL_RGB, GL_UNSIGNED_BYTE, img2);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, swidth,
		sheight, 0, GL_RGB, GL_UNSIGNED_BYTE, img3);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, swidth,
		sheight, 0, GL_RGB, GL_UNSIGNED_BYTE, img4);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, swidth,
		sheight, 0, GL_RGB, GL_UNSIGNED_BYTE, img5);

	glBindTexture(GL_TEXTURE_CUBE_MAP, g_nCubeTex);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
}

void init()
{
	//printf("init func called\n");
	// clear background color
	glClearColor(0.f, 0.f, 0.f, 1.f);

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluOrtho2D(0, 500, 500, 0);

	// set blend
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// set antialiasing
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	light_default();

	textureMapping_cube();
	textureMapping_cylinder();
	textureMapping_cider();
	textureMapping_sphere();
	gluQuadricTexture(qobj, GL_TRUE);
	gluQuadricTexture(qobj2, GL_TRUE);
	/* TEXTURE MAPPING SET */
	cubeTexture();
	glEnable(GL_TEXTURE_2D);
	setTextureMapping();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); //GL_REPLACE : polygon의 원래 색상은 무시하고 texture로 덮음
	
}

void special_keyboard(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		phi -= 5;
		if (phi < 0)phi += 360;
		break;
	case GLUT_KEY_RIGHT:
		phi += 5;
		if (phi > 360)phi -= 360;
		break;
	case GLUT_KEY_UP:
		theta -= 5;
		if (theta < 0)theta += 360;
		break;
	case GLUT_KEY_DOWN:
		theta += 5;
		if (theta > 360)theta -= 360;
		break;
	default:break;
	}

	//std::cout << "theta : " << theta << ", phi : " << phi << "\n";
	glutPostRedisplay();
}

/* Keyboard callback function */
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		/* Exit on escape key press */
	case '\x1B':
	{
		exit(EXIT_SUCCESS);
		break;
	}
	case 'a':
	{
		ref_light = !ref_light;
		if (ref_light == true) printf("light on\n");
		else printf("light off\n");
		break;
	}
	case 'z':
	{
		howto = !howto;
		if (howto == false) printf("How to play off(다시 켜려면 z를 누르세요)\n");
		break;
	}
	case '1': {
		left_open = !left_open;
		if (left_open == true) printf("left door open\n");
		else printf("left door close\n");
		break;
	}
	case '2': {
		right_open = !right_open;
		if (right_open == true) printf("right door open\n");
		else printf("right door close\n");
		break;
	}
	case '3': {
		homebar_open = !homebar_open;
		if (homebar_open == true) printf("homebar open\n");
		else printf("homebar close\n");
		break;
	}
	case 'q': {
		left_open = !left_open;
		right_open = !right_open;
		homebar_open = !homebar_open;
		inside_open = !inside_open;
		all_open = !all_open;
		if (all_open == true) printf("all open\n");
		else printf("all close\n");
		break;
	}
	}
	glutPostRedisplay();
}

void draw_obj(ObjParser* objParser)
{
	glBegin(GL_TRIANGLES);
	for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) {
		glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x,
			objParser->normal[objParser->normalIdx[n] - 1].y,
			objParser->normal[objParser->normalIdx[n] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x,
			objParser->vertices[objParser->vertexIdx[n] - 1].y,
			objParser->vertices[objParser->vertexIdx[n] - 1].z);

		glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
			objParser->normal[objParser->normalIdx[n + 1] - 1].y,
			objParser->normal[objParser->normalIdx[n + 1] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);

		glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
			objParser->normal[objParser->normalIdx[n + 2] - 1].y,
			objParser->normal[objParser->normalIdx[n + 2] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
	}
	glEnd();
}

void draw_obj_with_texture(ObjParser* objParser)
{
	glDisable(GL_BLEND);
	// glEnable(GL_TEXTURE_2D);	// texture 색 보존을 위한 enable
	glBindTexture(GL_TEXTURE_2D, textureMonkey);
	glBegin(GL_TRIANGLES);
	for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) {
		glTexCoord2f(objParser->textures[objParser->textureIdx[n] - 1].x,
			objParser->textures[objParser->textureIdx[n] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x,
			objParser->normal[objParser->normalIdx[n] - 1].y,
			objParser->normal[objParser->normalIdx[n] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x,
			objParser->vertices[objParser->vertexIdx[n] - 1].y,
			objParser->vertices[objParser->vertexIdx[n] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 1] - 1].x,
			objParser->textures[objParser->textureIdx[n + 1] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
			objParser->normal[objParser->normalIdx[n + 1] - 1].y,
			objParser->normal[objParser->normalIdx[n + 1] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 2] - 1].x,
			objParser->textures[objParser->textureIdx[n + 2] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
			objParser->normal[objParser->normalIdx[n + 2] - 1].y,
			objParser->normal[objParser->normalIdx[n + 2] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
	}
	glEnd();
	glEnable(GL_BLEND);
}

void draw_cube_textures()
{
	int size = 2;
	glBindTexture(GL_TEXTURE_2D, textureMonkey);
	glBegin(GL_QUADS);
	//Quad 1
	glNormal3f(1.0f, 0.0f, 0.0f);   //N1
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size / 2, size / 2, size / 2);   //V2
	glTexCoord2f(0.0f, 0.0f); glVertex3f(size / 2, -size / 2, size / 2);   //V1
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size / 2, -size / 2, -size / 2);   //V3
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size / 2, size / 2, -size / 2);   //V4
  //Quad 2
	glNormal3f(0.0f, 0.0f, -1.0f);  //N2
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size / 2, size / 2, -size / 2);   //V4
	glTexCoord2f(0.0f, 0.0f); glVertex3f(size / 2, -size / 2, -size / 2);   //V3
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size / 2, -size / 2, -size / 2);   //V5
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size / 2, size / 2, -size / 2);   //V6
  //Quad 3
	glNormal3f(-1.0f, 0.0f, 0.0f);  //N3
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size / 2, size / 2, -size / 2);   //V6
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size / 2, -size / 2, -size / 2);   //V5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size / 2, -size / 2, size / 2);   //V7
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size / 2, size / 2, size / 2);   //V8
  //Quad 4
	glNormal3f(0.0f, 0.0f, 1.0f);   //N4
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size / 2, size / 2, size / 2);   //V8
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size / 2, -size / 2, size / 2);   //V7
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size / 2, -size / 2, size / 2);   //V1
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size / 2, size / 2, size / 2);   //V2
  //Quad 5
	glNormal3f(0.0f, 1.0f, 0.0f);   //N5
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size / 2, size / 2, -size / 2);   //V6
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size / 2, size / 2, size / 2);   //V8
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size / 2, size / 2, size / 2);   //V2
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size / 2, size / 2, -size / 2);   //V4
  //Quad 6
	glNormal3f(1.0f, -1.0f, 0.0f);  //N6
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size / 2, -size / 2, size / 2);   //V7
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size / 2, -size / 2, -size / 2);   //V5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size / 2, -size / 2, -size / 2);   //V3
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size / 2, -size / 2, size / 2);   //V1
	glEnd();
}

void draw_textureCube() {
	glColor3f(1.0, 1.0, 1.0);	// white로 color를 set해주어야 texture색상이 제대로 적용 됨!
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			// polygon의 원래 색상은 무시하고 texture로 덮음
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// polygon의 원래 색상과 texture 색상을 곱하여 덮음, texture가 입혀진 표면에 광원 효과 설정 가능
//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		// texture의 색상으로 덮어 씌운다

	glBindTexture(GL_TEXTURE_2D, textureMonkey);
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0, 0);	// -x axis
	glTexCoord2f(0, 0); glVertex3f(-1.0, 1.0, -1.0);
	glTexCoord2f(1, 0); glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(1, 1); glVertex3f(-1.0, -1.0, 1.0);
	glTexCoord2f(0, 1); glVertex3f(-1.0, 1.0, 1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureMonkey);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0, 0);	//x axis
	glTexCoord2f(0, 0); glVertex3f(1.0, 1.0, 1.0);
	glTexCoord2f(1, 0); glVertex3f(1.0, -1.0, 1.0);
	glTexCoord2f(1, 1); glVertex3f(1.0, -1.0, -1.0);
	glTexCoord2f(0, 1); glVertex3f(1.0, 1.0, -1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureMonkey);
	glBegin(GL_QUADS);
	glNormal3f(0, -1.0, 0);	// -y axis
	glTexCoord2f(0, 0); glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(1, 0); glVertex3f(1.0, -1.0, -1.0);
	glTexCoord2f(1, 1); glVertex3f(1.0, -1.0, 1.0);
	glTexCoord2f(0, 1); glVertex3f(-1.0, -1.0, 1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureMonkey);
	glBegin(GL_QUADS);
	glNormal3f(0, 1.0, 0);	// y axis
	glTexCoord2f(0, 0); glVertex3f(-1.0, 1.0, 1.0);
	glTexCoord2f(1, 0); glVertex3f(1.0, 1.0, 1.0);
	glTexCoord2f(1, 1); glVertex3f(1.0, 1.0, -1.0);
	glTexCoord2f(0, 1); glVertex3f(-1.0, 1.0, -1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureMonkey);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1.0);	//z axis
	glTexCoord2f(0, 0); glVertex3f(1.0, 1.0, 1.0);
	glTexCoord2f(1, 0); glVertex3f(-1.0, 1.0, 1.0);
	glTexCoord2f(1, 1); glVertex3f(-1.0, -1.0, 1.0);
	glTexCoord2f(0, 1); glVertex3f(1.0, -1.0, 1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureMonkey);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1.0);	//-z축
	glTexCoord2f(0, 0); glVertex3f(1.0, 1.0, -1.0);
	glTexCoord2f(1, 0); glVertex3f(-1.0, 1.0, -1.0);
	glTexCoord2f(1, 1); glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(0, 1); glVertex3f(1.0, -1.0, -1.0);
	glEnd();

	draw_axis();
}
void draw_string(void* font, const char* str, float x_position,
	float y_position, float red, float green, float blue) {
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(red, green, blue);
	glRasterPos3f(x_position, y_position, 0);
	unsigned int i;
	for (i = 0; i < strlen(str); i++) {
		glutBitmapCharacter(font, str[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
}
void draw_text() {

	draw_string(GLUT_BITMAP_HELVETICA_18, "How to play (on/off: keyboard z)", -9.5, 9, 1, 1, 0);
	draw_string(GLUT_BITMAP_HELVETICA_18, "keyboard 1, 2: Left, Right Door open / close", -9.5, 7, 1, 1, 0);
	draw_string(GLUT_BITMAP_HELVETICA_18, "keyboard 3: Homebar open / close", -9.5, 6, 1, 1, 0);
	draw_string(GLUT_BITMAP_HELVETICA_18, "keyboard q: All open / close", -9.5, 5, 1, 1, 0);
	draw_string(GLUT_BITMAP_HELVETICA_18, "keyboard a: Inside Light on / off", -9.5, 4, 1, 1, 0);
	draw_string(GLUT_BITMAP_HELVETICA_18, "menu : Change Style, Store/Pick food ", -9.5, 3, 1, 1, 0);
	draw_string(GLUT_BITMAP_HELVETICA_18, "mouse wheel : zoom in/out ", -9.5, 2, 1, 1, 0);

}
void draw_smallview_coke() {
	gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);
	glViewport(cur_width / 2,0, cur_width/2, cur_height/2);
	glRotatef(60, 1, 0, 0);
	draw_cylinder();
	glFlush();
}
void draw_smallview_cider() {
	gluLookAt(0.7, 0.7, 0.7, 0, 0, 0, 0, 1, 0);
	glViewport(cur_width / 2, 0, cur_width / 2, cur_height / 2);
	glRotatef(60, 1, 0, 0);
	draw_cider();
	glFlush();
}
/* Display callback function */
void draw()
{
	glViewport(0, 0, cur_width, cur_height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(howto==true)	draw_text();
	glEnable(GL_DEPTH_TEST);
	glColor3f(1.f, 1.f, 1.f);
	cam[0] = radius * sin(theta * M_PI / 180) * sin(phi * M_PI / 180);
	cam[1] = radius * cos(theta * M_PI / 180);
	cam[2] = radius * sin(theta * M_PI / 180) * cos(phi * M_PI / 180);

	if (theta <= 180)
		gluLookAt(cam[0], cam[1], cam[2], 0, 3, 0, 0, 1, 0);
	else
		gluLookAt(cam[0], cam[1], cam[2], 0, 3, 0, 0, -1, 0);
	
	glDisable(GL_LIGHT1);
	GLfloat light_position[] = { cam[0],cam[1],cam[2],1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	
	//draw_axis();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glColor3f(1.f, 1.f, 1.f);
	
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	if (all_open == true) {
		glTranslatef(0, 0, trans-5);
	}
	if(ref_light==true)
		glEnable(GL_LIGHT1);
	draw_obj_with_texture(monkey2);//body
	glPopMatrix();
	if (left_open == true) {
		glRotatef(-90, 0, 1, 0);
		glTranslatef(0, 0, 1);
		glTranslatef(3.3, 0, 0);
	}
	draw_obj_with_texture(monkey);//left door
	draw_obj_with_texture(monkey6);//left door-bar
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(-1.7, 0, -1.7);
	if(coke_location==11)draw_cylinder();//콜라 왼쪽바 2
	glTranslatef(0, 0, -6.3);
	if(coke_location==10)draw_cylinder();//콜라 왼쪽바 1
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(-0.6, 0, -1);
	if(cider_location==11)draw_cider();//사이다 왼쪽바2
	glTranslatef(0, 0, -6.3);
	if (cider_location == 10)draw_cider();//사이다 왼쪽바1
	glPopMatrix();

	glPopMatrix();
	if (right_open == true) {
		glRotatef(90, 0, 1, 0);
		glTranslatef(0, 0, 2.2);
		glTranslatef(-4.2, 0, 0);
	}
	draw_obj_with_texture(monkey1);//right door
	draw_obj_with_texture(monkey7);//right door-bar
	draw_obj_with_texture(monkey8);//right door-bar
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(1.7, 0, -1.7);
	if (coke_location == 13)draw_cylinder();//콜라 오른쪽바 2
	glTranslatef(0, 0, -6.3);
	if (coke_location == 12)draw_cylinder();//콜라 오른쪽바 1
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.6, 0, -1);
	if (cider_location == 13)draw_cider();//사이다 오른쪽바2
	glTranslatef(0, 0, -6.3);
	if (cider_location == 12)draw_cider();//사이다 오른쪽바1
	glPopMatrix();
	if (homebar_open == true) {
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, 0, -3.8);
		glTranslatef(0, -1.5, 0);
	}
	draw_obj_with_texture(monkey3);//right_homebar
	glPopMatrix();
	if (all_open == true) {
		glTranslatef(0, 0, trans_bar);
	}
	glPushMatrix();
	glPushMatrix();
	draw_obj(monkey4);//left bar
	glRotatef(90, 1, 0, 0);
	glTranslatef(-1, -1, -7.7);
	if (coke_location == 1)	draw_cylinder(); //콜라 냉동1
	
	glTranslatef(0, 0, 3);
	if (coke_location == 2) {
		draw_cylinder(); //콜라 냉동2
	}
	glTranslatef(0, 0, 3);
	if (coke_location == 3) {
		draw_cylinder(); //콜라 냉동3
	}
	glTranslatef(0, 0, 3);
	if (coke_location == 4) {
		draw_cylinder(); //콜라 냉동4
	}
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(-0.5, 0, -7);
	if(cider_location==1) draw_cider();//사이다 냉동1
	glTranslatef(0, 0, 3);
	if (cider_location == 2) draw_cider();//사이다 냉동2
	glTranslatef(0, 0, 3);
	if (cider_location == 3) draw_cider();//사이다 냉동3
	glTranslatef(0, 0, 3);
	if (cider_location == 4) draw_cider();//사이다 냉동4
	glPopMatrix();

	draw_obj(monkey5);//right bar
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(1, -1, -7.7);
	if (coke_location == 5) {
		draw_cylinder(); //콜라 냉장1
	}
	glTranslatef(0, 0, 3);
	if (coke_location == 6) {
		draw_cylinder(); //콜라 냉장2
	}
	glTranslatef(0, 0, 3);
	if (coke_location == 7) {
		draw_cylinder(); //콜라 냉장3
	}
	glTranslatef(0, 0, 3);
	if (coke_location == 8) {
		draw_cylinder(); //콜라 냉장4
	}
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.5, 0, -7);
	if (cider_location == 5) draw_cider();//사이다 냉장1
	glTranslatef(0, 0, 3);
	if (cider_location == 6) draw_cider();//사이다 냉장2
	glTranslatef(0, 0, 3);
	if (cider_location == 7) draw_cider();//사이다 냉장3
	glTranslatef(0, 0, 3);
	if (cider_location == 8) draw_cider();//사이다 냉장4
	glPopMatrix();
	glPopMatrix();
	

	//draw_obj(monkey);
	//draw_cube_textures();
	//draw_textureCube();
	
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(coke_location==9)draw_smallview_coke();//coke pickup
	if (cider_location == 9)draw_smallview_cider();//cider pickup

	glutSwapBuffers();
	glFlush();
}

void mouse(int button, int state, int x, int y)
{
	if (state==1&&(x>490&&x<650&&y<540&&y>420)&&coke_location==9) {
		 printf("Big Coke를 다시 보관합니다.(Default: 냉동 1)\n");
		 coke_location = 1;
	}
	else if (state == 1 && (x > 490 && x < 650 && y < 540 && y>420) && cider_location == 9) {
		printf("Cider를 다시 보관합니다.(Default: 냉동 1)\n");
		cider_location = 1;
	}
	//else {
		// printf("button(%d), state(%d), x(%d), y(%d)\n", button, state, x, y);
	//}
	glutPostRedisplay();
}

void mouseWheel(int button, int dir, int x, int y)
{
	if (dir > 0) {
		// printf("button(%d), dir(%d), x(%d), y(%d)\n", button, dir, x, y);
		if (radius > 1) radius -= 0.5;
	}
	else {
		// printf("button(%d), dir(%d), x(%d), y(%d)\n", button, dir, x, y);
		if (radius < 100) radius += 0.5;
	}
	glutPostRedisplay();
}

void passiveMotion(int x, int y)
{
	//printf("Mouse movement x, y = (%d, %d)\n", x, y);
	glutPostRedisplay();
}

void motion(int x, int y)
{
	//printf("Mouse movement x, y = (%d, %d)\n", x, y);
	glutPostRedisplay();
}

void main_menu(int option)
{
	if (option == 99) exit(0);
	else if (option == 1) {
		radius = 20;
		theta = 45; phi = 45;
	}
	glutPostRedisplay();
}

void sub_menu(int option)
{
	if (option == 2)
		ref_tex = 1;
	else if (option == 3)
		ref_tex = 2;
	else if (option == 4)
		ref_tex = 3;
	setTextureMapping();
}

void add_menu()
{
	int submenu1;
	submenu1 = glutCreateMenu(sub_menu);
	glutAddMenuEntry("Grey", 2);
	glutAddMenuEntry("Rainbow", 3);
	glutAddMenuEntry("LV", 4);

	int sub_submenu1;
	sub_submenu1 = glutCreateMenu(sub_menu_food);
	glutAddMenuEntry("Freeze-1", 11);
	glutAddMenuEntry("Freeze-2", 12);
	glutAddMenuEntry("Freeze-3", 13);
	glutAddMenuEntry("Freeze-4", 14);
	glutAddMenuEntry("Refrigeration-1", 15);
	glutAddMenuEntry("Refrigeration-2", 16);
	glutAddMenuEntry("Refrigeration-3", 17);
	glutAddMenuEntry("Refrigeration-4", 18);
	glutAddMenuEntry("Left bar-1", 40);
	glutAddMenuEntry("Left bar-2", 41);
	glutAddMenuEntry("Right bar-1", 42);
	glutAddMenuEntry("Right bar-2", 43);
	glutAddMenuEntry("Pick up", 30);
	int sub_submenu2;
	sub_submenu2 = glutCreateMenu(sub_menu_food);
	glutAddMenuEntry("Freeze-1", 19);
	glutAddMenuEntry("Freeze-2", 20);
	glutAddMenuEntry("Freeze-3", 21);
	glutAddMenuEntry("Freeze-4", 22);
	glutAddMenuEntry("Refrigeration-1", 23);
	glutAddMenuEntry("Refrigeration-2", 24);
	glutAddMenuEntry("Refrigeration-3", 25);
	glutAddMenuEntry("Refrigeration-4", 26);
	glutAddMenuEntry("Left bar-1", 44);
	glutAddMenuEntry("Left bar-2", 45);
	glutAddMenuEntry("Right bar-1", 46);
	glutAddMenuEntry("Right bar-2", 47);
	glutAddMenuEntry("Pick up", 31);
	int submenu2= glutCreateMenu(sub_menu_food);
	glutAddSubMenu("Big Coke", sub_submenu1);
	glutAddSubMenu("Cider", sub_submenu2);

	int mainmenu1 = glutCreateMenu(&main_menu);
	glutAddMenuEntry("Init View", 1);
	glutAddSubMenu("Style", submenu1);
	glutAddSubMenu("Store Food", submenu2);
	glutAddMenuEntry("Quit", 99);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void idle()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME); // unit : ms

	if (time - timebase > 1000)
	{
		fps = frame * 1000.f / (time - timebase);
		timebase = time;
		frame = 0;
		//printf("fps : %.0f\n", fps);
	}
	
	else if (all_open == true) {
		trans -= 0.01;
		trans_bar -= 0.015;
	}
	else {
		trans = 0;
		trans_bar = 0;
	}
	if (trans < -2)trans = -2;
	if (trans_bar < -2)trans_bar = -2;
	if (left_open || right_open || homebar_open) {
		door_open_limit += 0.1;
		if (door_open_limit > 400) {
			PlaySound(TEXT("./sound_button_wrong.wav"), NULL, SND_ASYNC);
			printf("냉장고의 문을 닫아주세요!\n");
			Sleep(1000);
		}
	}
	else door_open_limit = 0;
	glutPostRedisplay();
}

void resize(int width, int height)
{
	printf("resize func called\n");
	glViewport(0, 0, width, height);
	cur_width = width;
	cur_height = height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0, 500, 0, 500);
	gluPerspective(60, (double)width / (double)height, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

void get_resource(const char* str)
{
	monkey = new ObjParser(str);
}
