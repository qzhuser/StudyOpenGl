#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <stdio.h> 
#include <iostream>

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

const char* vertexShaderSource = "#version 330 core\n"
        "layout (location =0) in vec3 aPos;\n"
        "layout(location=1) in vec3 aColor;\n"
        "out vec3 ourColor;"
        "void main()"
        " {\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "   ourColor=aColor;\n"//将要传递给片段着色器的ourcolor设置为从顶点数据里得到的输入颜色
        "}\0";
const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 ourColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor=vec4(ourColor,1.0);\n"
        "}\n\0";



int main() {
    
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
    //每当窗口调整大小时 自动调用这个函数用来重新调整视口
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    ////创建一个顶点着色器
    //int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    ////把着色器源码添加到着色器上，然后编译（那个1是源码字符串数量）
    //glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    //glCompileShader(vertexShader);
    ////检测glCompileShader是否编译成功
    //int success;
    //char infoLog[512];
    //glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    ////如果编译失败 打印错误信息
    //if (!success) {
    //    glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
    //    std::cout << "ERROR:SHADER VERTEX COMPILATION_FAILED\n" << infoLog << std::endl;
    //}
    ////创建一个片元着色器
    //int fragmentShader;
    //fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    //glCompileShader(fragmentShader);

    ////如果编译失败 打印错误信息
    //glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    //if (!success) {
    //    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    //    std::cout << "ERROR:SHADER FRAGMENT COMPILATION_FAILED\n" << infoLog << std::endl;
    //}
    ////创建着色器程序
    //int shaderProgram;
    //shaderProgram = glCreateProgram();
    ////把着色器附加到程序中 然后用glLinkProgram链接
    //glAttachShader(shaderProgram,vertexShader);
    //glAttachShader(shaderProgram, fragmentShader);
    //glLinkProgram(shaderProgram);
    ////检查链接
    //glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    //if (!success) {
    //    glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
    //    std::cout << "ERROR SHADER PROGRAM LINKING_FAILD\n" << infoLog << std::endl;
    //}
    ////已经链接到程序 可以删除shader对象了
    //glDeleteShader(vertexShader);
    //glDeleteShader(fragmentShader);

    Shader myShader("shader.vs","shader.fs");

    //顶点输入
    float vertices[] = {
        -1.0f, 0.0f, 0.0f,1.0f,0.0f,0.0f,  
         0.0f, 0.0f, 0.0f, 0.0f,1.0f,0.0f,
        -0.5f, 1.0f, 0.0f,0.0f,0.0f,1.0f,
         1.0f, 0.0f, 0.0f, 0.0f,0.0f,1.0f,
         0.0f, 0.0f, 0.0f, 0.0f,1.0f,0.0f,
         0.5f, 1.0f, 0.0f, 1.0f,0.0f,0.0f,
    };
    unsigned int indices[] = {
        0,1,3,
        1,2,3
    };

    //生成VBO（顶点缓冲对象），VAO（顶点数组对象），EBO（索引缓冲对象）
    unsigned int VBO,VAO,EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1,&EBO);
    //绑定VAO
    glBindVertexArray(VAO);

    //绑定缓冲目标
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    //把顶点数据复制到缓冲目标的内存中
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    //解析顶点数据(要配置的顶点属性的位置值（着色器中设置了0），当前顶点属性的大小（vec3是3个float），数据类型，是否希望normalize，步长值（移动两个vec3，位置和颜色），偏移量（位置在最前，颜色要往后偏移位置属性的长度，也就是3*sizeof(float)）)
    //位置属性
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    //启用顶点属性  参数是位置值
    glEnableVertexAttribArray(0);

    //颜色属性
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);


    //渲染循环
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        //清空屏幕使用的颜色
        glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
        //清空屏幕的颜色缓冲
        glClear(GL_COLOR_BUFFER_BIT);

        myShader.use();
        float timeValue = glfwGetTime();
        float t = sin(timeValue)/2;
        myShader.SetFloat("offset", t);
        //glUseProgram(shaderProgram);
        //在着色器程序之外动态改变着色器变量
        /*float timeValue = glfwGetTime();
        float t = sin(timeValue) / 2 + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram,"ourColor");
        glUniform4f(vertexColorLocation,t,1.0f,1.0f,1.0f);*/

        glBindVertexArray(VAO);
        //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        //画图（要画什么，，几个顶点）
        glDrawArrays(GL_TRIANGLES,0,6);
        //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        //glBindVertexArray(0);

        //检查是否有触发事件
        glfwSwapBuffers(window);
        //交换颜色缓冲（Doubule Buffer）
        glfwPollEvents();
    }
    //释放资源

    glfwTerminate();

    return 0;
}
