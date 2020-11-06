#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h> 
#include <iostream>

void PrintVersion()
{
    const GLubyte* name = glGetString(GL_VENDOR);            //返回负责当前OpenGL实现厂商的名字
    const GLubyte* biaoshifu = glGetString(GL_RENDERER);    //返回一个渲染器标识符，通常是个硬件平台
    const GLubyte* OpenGLVersion = glGetString(GL_VERSION);    //返回当前OpenGL实现的版本号
    const GLubyte* glsl = glGetString(GL_SHADING_LANGUAGE_VERSION);//返回着色预压编译器版本号
    //const GLubyte* gluVersion = gluGetString(GLU_VERSION);    //返回当前GLU工具库版本
    printf("OpenGL实现厂商的名字：%s\n", name);
    printf("渲染器标识符：%s\n", biaoshifu);
    printf("OpenGL实现的版本号：%s\n", OpenGLVersion);
    printf("OpenGL着色语言版本：%s\n", glsl);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    //设置视口 前两个参数设置窗口左下角的位置 后两个是宽度和高度（像素）
    glViewport(0, 0, width, height);
}
//输入
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
int main() {
    //PrintVersion();
	glfwInit();//初始化
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //GLFW函数glfwCreateWindow（width,height,title）；返回一个窗口对象
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //每当窗口调整大小时 自动调用这个函数用来重新调整视口
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //渲染循环
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        //清空屏幕使用的颜色
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        //清空屏幕的颜色缓冲
        glClear(GL_COLOR_BUFFER_BIT);

        //检查是否有触发事件
        glfwSwapBuffers(window);
        //交换颜色缓冲（Doubule Buffer）
        glfwPollEvents();
    }
    //释放资源

    glfwTerminate();

	return 0;
}
