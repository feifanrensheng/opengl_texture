#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <opencv2/opencv.hpp>

using namespace cv;

Mat I = imread("../desk.jpg");

int width = I.cols;
int height = I.rows;

GLuint load_texture()
{
	GLuint m_backgroundTextureId;
    glGenTextures(1, &m_backgroundTextureId);
    glBindTexture(GL_TEXTURE_2D, m_backgroundTextureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int w = I.cols;
    int h = I.rows;

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, m_backgroundTextureId);

    if (I.channels() == 3)
    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, I.data);
    else if(I.channels() == 4)
    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, I.data);
    else if (I.channels()==1)
    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, I.data); 
    return m_backgroundTextureId;
}

void display()
{
    // 清除屏幕
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //获取纹理对象
    GLuint image = load_texture();

    //重新设置OpenGL窗口：原点位置为左上角，x轴从左到右，y轴从上到下，坐标值与像素坐标值相同
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, height, 0);

    //显示纹理
    glEnable(GL_TEXTURE_2D);    //允许使用纹理
    glBindTexture(GL_TEXTURE_2D, image);    //选择纹理对象

                                            //原始完全填充四边形
    glBegin(GL_POLYGON);    //设置为多边形纹理贴图方式并开始贴图
    glTexCoord2f(0.0f, 0.0f); glVertex2f(0, 0);    //纹理左上角对应窗口左上角
    glTexCoord2f(0.0f, 1.0f); glVertex2f(0, height);    //纹理左下角对应窗口左下角
    glTexCoord2f(1.0f, 1.0f); glVertex2f(width, height);    //纹理右下角对应窗口右下角
    glTexCoord2f(1.0f, 0.0f); glVertex2f(width, 0);    //纹理右上角对应窗口右上角
    glEnd();    //结束贴图
    

                /*//三角形
                glBegin(GL_POLYGON);
                glTexCoord2f(0.0f, 0.0f); glVertex2f(0, 0);
                glTexCoord2f(0.0f, 1.0f); glVertex2f(0, height);
                glTexCoord2f(1.0f, 1.0f); glVertex2f(width, height);
                glEnd();*/

            /*    //多边形
                glBegin(GL_POLYGON);
                glTexCoord2f(0, 0); glVertex2f(0, 0);
                glTexCoord2f(0, 1); glVertex2f(0, height/3);
                glTexCoord2f(1, 1); glVertex2f(width/4, height/3);
                glTexCoord2f(1, 0); glVertex2f(width/4, 0);
                glTexCoord2f(0.0f, 0.5f); glVertex2f(0, height/2);
                glEnd();*/

                /*//任意变换
                glBegin(GL_POLYGON);
                glTexCoord2f(0.0f, 0.0f); glVertex2f(width/4, height/4);
                glTexCoord2f(0.0f, 1.0f); glVertex2f(0, height);
                glTexCoord2f(1.0f, 1.0f); glVertex2f(width, height*2/3);
                glTexCoord2f(1.0f, 0.0f); glVertex2f(width*4/5, 50);
                glEnd();*/

                //边缘贴图效果
                /*glBegin(GL_POLYGON);
                glTexCoord2f(0.0f, 0.0f); glVertex2f(0, 0);
                glTexCoord2f(0.0f, 2.0f); glVertex2f(0, height);
                glTexCoord2f(2.0f, 2.0f); glVertex2f(width, height);
                glTexCoord2f(2.0f, 0.0f); glVertex2f(width, 0);
                glEnd();
                */

    glDisable(GL_TEXTURE_2D);    //禁止使用纹理

                                //双缓存交换缓存以显示图像
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    //初始化GL
    glutInit(&argc, argv);
    //设置显示参数(双缓存，RGB格式)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    //设置窗口尺寸：width*height
    glutInitWindowSize(width, height);
    //设置窗口位置：在屏幕左上角像素值(100,100)处
    glutInitWindowPosition(100, 100);
    //设置窗口名称
    glutCreateWindow("OpenGL");
    //显示函数，display事件需要自行编写
    glutDisplayFunc(display);

    //重复循环GLUT事件
    glutMainLoop();

    return 0;
}