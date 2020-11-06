#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h> 
#include <iostream>

void PrintVersion()
{
    const GLubyte* name = glGetString(GL_VENDOR);            //���ظ���ǰOpenGLʵ�ֳ��̵�����
    const GLubyte* biaoshifu = glGetString(GL_RENDERER);    //����һ����Ⱦ����ʶ����ͨ���Ǹ�Ӳ��ƽ̨
    const GLubyte* OpenGLVersion = glGetString(GL_VERSION);    //���ص�ǰOpenGLʵ�ֵİ汾��
    const GLubyte* glsl = glGetString(GL_SHADING_LANGUAGE_VERSION);//������ɫԤѹ�������汾��
    //const GLubyte* gluVersion = gluGetString(GLU_VERSION);    //���ص�ǰGLU���߿�汾
    printf("OpenGLʵ�ֳ��̵����֣�%s\n", name);
    printf("��Ⱦ����ʶ����%s\n", biaoshifu);
    printf("OpenGLʵ�ֵİ汾�ţ�%s\n", OpenGLVersion);
    printf("OpenGL��ɫ���԰汾��%s\n", glsl);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    //�����ӿ� ǰ�����������ô������½ǵ�λ�� �������ǿ�Ⱥ͸߶ȣ����أ�
    glViewport(0, 0, width, height);
}
//����
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
int main() {
    //PrintVersion();
	glfwInit();//��ʼ��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //GLFW����glfwCreateWindow��width,height,title��������һ�����ڶ���
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //��ʼ��GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //ÿ�����ڵ�����Сʱ �Զ�������������������µ����ӿ�
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //��Ⱦѭ��
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        //�����Ļʹ�õ���ɫ
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        //�����Ļ����ɫ����
        glClear(GL_COLOR_BUFFER_BIT);

        //����Ƿ��д����¼�
        glfwSwapBuffers(window);
        //������ɫ���壨Doubule Buffer��
        glfwPollEvents();
    }
    //�ͷ���Դ

    glfwTerminate();

	return 0;
}
