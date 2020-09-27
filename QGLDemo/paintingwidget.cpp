#include "paintingwidget.h"

static const char* VERTEX_SHADER_CODE=
        "#version 330 \n"
        /*将位于0的向量设为posVertex*/
        "layout(location=0) in vec3 posVertex; \n"
        "void main(){ \n"
        "gl_Position=vec4(posVertex,1.0f); \n"
        "} \n";
static const char* FRAGMENT_SHADER_CODE=
        "#version 330 \n"
        "out vec4 fragColor; \n"
        "void main(){ \n"
        "fragColor=vec4(1.0f,0.0f,0.0f,1.0f); \n"
        "} \n";

PaintingWidget::PaintingWidget(QWidget *parent) :
    QOpenGLWidget(parent),m_vbo(nullptr),m_vao(nullptr),m_shader(nullptr)
{

}
PaintingWidget::~PaintingWidget(){

}

void PaintingWidget::initializeGL(){

    //函数封装集
    QOpenGLFunctions *f=this->context()->functions();

    m_shader=new QOpenGLShaderProgram();
    //将上述的顶点和片段程序代码写入m_shader中
    m_shader->addShaderFromSourceCode(QOpenGLShader::Vertex,VERTEX_SHADER_CODE);
    m_shader->addShaderFromSourceCode(QOpenGLShader::Fragment,FRAGMENT_SHADER_CODE);
    if(m_shader->link()){
        qDebug("shader link sucess");
    }
    else{
        qDebug("shader link failed");
    }
    //-------
    m_vao=new QOpenGLVertexArrayObject();
    m_vbo=new QOpenGLBuffer();
    m_vao->create();
    m_vao->bind();//绑定
    m_vbo->create();
    m_vbo->bind();

    static const GLfloat VERTEX_DATA[]={
        -0.5f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        -0.5f,0.5f,0.0f
    };
    //传入顶点信息，还需要传入总的字节大小
    m_vbo->allocate(VERTEX_DATA,3*3*sizeof (GLfloat));

    f->glEnableVertexAttribArray(0);//开启使用

    //定义顶点属性数据
    //1.指定某顶点，在之前的定义中我们的点的位置为0
    //2.此参数是顶点向量的长度，也就为3（三维，写4也行）
    //3.向量的数值类型
    //4.是否需要标准化
    //5.点与点之间在内存上的间隔，
    //6.位置偏移量
    f->glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),0);

    m_vbo->release();
    m_vao->release();
}
void PaintingWidget::paintGL(){
    QOpenGLFunctions *f=this->context()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    m_vao->bind();
    m_shader->bind();
    f->glDrawArrays(GL_TRIANGLES,0,3);
    m_shader->release();
    m_vao->release();
}
