#ifndef PAINTINGWIDGET_H
#define PAINTINGWIDGET_H

#include <QOpenGLWidget>
#include<QOpenGLContext>
#include<QOpenGLBuffer>
#include<QOpenGLFunctions>
#include<QOpenGLShaderProgram>
#include<QOpenGLVertexArrayObject>
#include <QWidget>

class PaintingWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    PaintingWidget(QWidget *parent);
    ~PaintingWidget();
protected:
    void initializeGL();
    //绘图
    void paintGL();
    //处理窗口变化
    void resizeGL(int w,int h);
private:
    //顶点缓冲
    QOpenGLBuffer *m_vbo;
    //存储多个顶点缓冲
    QOpenGLVertexArrayObject *m_vao;
    //渲染器
    QOpenGLShaderProgram *m_shader;
};

#endif // PAINTINGWIDGET_H
