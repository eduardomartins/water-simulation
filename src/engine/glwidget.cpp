#include "glwidget.h"


GLWidget::GLWidget(QWidget *parent):
    //QOpenGLWidget(parent)
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
  , mat_specular { 1.0, 1.0, 1.0, 1.0 }
  , mat_shininess { 50.0 }
  , light_position { 1.0, 1.0, 1.0, 0.0 }
{
    //connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    xRot = 0;
    yRot = 0;
    zRot = 0;

    bowling = new Room(this);
}

GLWidget::~GLWidget()
{

}


void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5,0,0,0,0,1,0);
}

void GLWidget::initializeGL()
{


    qDebug() << "Incializando...";


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
}

void GLWidget::paintGL()
{

    qDebug() << "Paint";
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glClearColor(0.6, 0.7, 0.8, 1.0);
    //glShadeModel (GL_SMOOTH);

    glTranslatef(0.0f, 0.0f, -0.0f);
    glRotatef(xRot / 1.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 1.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 1.0, 0.0, 0.0, 1.0);

    GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    bowling->draw();
    //bowling->drawTextures();
}


void GLWidget::setXRotation(int angle)
{
    angle = angle % 360;
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setYRotation(int angle)
{
    angle = angle % 360;
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setZRotation(int angle)
{
    angle = angle % 360;
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPosition = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPosition.x();
    int dy = event->y() - lastPosition.y();

    int x = (int) ((dy - yRot) * 0.2);
    int y = (int) ((dx - xRot) * 0.5);

    if (event->buttons() & Qt::LeftButton) {

        //setXRotation(x);
        setYRotation(y);

        lastPosition = event->pos();
    }

}
