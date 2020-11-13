#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Camera.h"
#include <stb_image.h>
#include <stdio.h> 
#include <iostream>

float amount = 0.2f;
unsigned int screenWidth=800, screenHeight=600;

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间
float pitch, yaw;
float fov = 45.0f;
Camera mycamera(glm::vec3(0.0f,0.0f,3.0f));

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    //设置视口 前两个参数设置窗口左下角的位置 后两个是宽度和高度（像素）
    glViewport(0, 0, width, height);
}
//输入
void key_callback(GLFWwindow* window,int key,int scancode,int action,int mods) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        if (amount < 1) {
            amount += 0.1f;
        }
    }
    else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        if (amount >= 0.1f) {
            amount -= 0.1f;
        }
    }
}
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
int main() {
    
    glfwInit();//初始化
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //GLFW函数glfwCreateWindow（width,height,title）；返回一个窗口对象
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", NULL, NULL);
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
    


    //顶点输入
    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    unsigned int indices[] = {
        0,1,3,
        1,2,3
    };
   

    //生成VBO（顶点缓冲对象），VAO（顶点数组对象），EBO（索引缓冲对象）
    unsigned int VBO,VAO,EBO,texture1,texture2;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenTextures(1,&texture1);
    
    //绑定VAO
    glBindVertexArray(VAO);

    //绑定缓冲目标
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //把顶点数据复制到缓冲目标的内存中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    //解析顶点数据(要配置的顶点属性的位置值（着色器中设置了0），当前顶点属性的大小（vec3是3个float），数据类型，是否希望normalize，步长值（移动两个vec3，位置和颜色），偏移量（位置在最前，颜色要往后偏移位置属性的长度，也就是3*sizeof(float)）)
    //位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    //启用顶点属性  参数是位置值
    glEnableVertexAttribArray(0);

    //颜色属性
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);
    //纹理属性1
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    //纹理属性2
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(3);

    glBindTexture(GL_TEXTURE_2D, texture1);

    //对纹理的ST轴设置环绕方式
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //指定放大和缩小的过滤方式
    //GL_LINEAR_MIPMAP_LINEAR:多级渐远纹理（两个最匹配像素大小的多级纹理之间进行插值）
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    //GL_LINEAR:普通的线性过滤，基于纹理坐标附近的像素计算一个插值，GL_NEAREST:临近过滤，直接选取最近的像素
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    //加载并生成纹理
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        //图片数据填充纹理
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        //生成多级渐远纹理
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    //释放图像内存
    stbi_image_free(data);
    //第二张纹理
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    //对纹理的ST轴设置环绕方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //指定放大和缩小的过滤方式
    //GL_LINEAR_MIPMAP_LINEAR:多级渐远纹理（两个最匹配像素大小的多级纹理之间进行插值）
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //GL_LINEAR:普通的线性过滤，基于纹理坐标附近的像素计算一个插值，GL_NEAREST:临近过滤，直接选取最近的像素
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //加载并生成纹理
    data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
    if (data) {
        //图片数据填充纹理
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        //生成多级渐远纹理
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    //释放图像内存
    stbi_image_free(data);

    glm::vec3 cubePositions[] = {
      glm::vec3(0.0f,  0.0f,  0.0f),
      glm::vec3(2.0f,  5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f,  3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),
      glm::vec3(1.5f,  2.0f, -2.5f),
      glm::vec3(1.5f,  0.2f, -1.5f),
      glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    Shader myShader("shader.vs", "shader.fs");

    myShader.use();

    myShader.SetInt("texture1", 0);
    myShader.SetInt("texture2", 1);
    //启用深度测试
    glEnable(GL_DEPTH_TEST);
    //隐藏光标
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //渲染循环
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window,scroll_callback);
        //glfwSetKeyCallback(window,key_callback);
        processInput(window);

        //清空屏幕使用的颜色
        glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
        //清空屏幕的颜色缓冲，深度缓冲
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        myShader.use();
        myShader.SetMat4("view", mycamera.GetViewMatrix());


        glm::mat4 projection;
        projection = glm::perspective(glm::radians(fov),(float)screenWidth/(float)screenHeight,0.1f,100.0f);
        myShader.SetMat4("projection", projection);
        /*float timeValue = glfwGetTime();
        float t = sin(timeValue)/2;
        myShader.SetFloat("offset", t);*/
        //myShader.SetFloat("amount",amount);
       
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            float angle;
            if (i % 3 == 0) {
                angle = 20.0f * i + 3 * glfwGetTime();
            }
            else {
                angle = 20.0f * i;
            }
            model = glm::rotate(model,glm::radians(angle),glm::vec3(1.0,0.3f,0.5f));
            myShader.SetMat4("model",model);

            glDrawArrays(GL_TRIANGLES,0,36);
        }
        //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        //画图（要画什么，，几个顶点）
        //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        //检查是否有触发事件
        glfwSwapBuffers(window);
        //交换颜色缓冲（Doubule Buffer）
        glfwPollEvents();
    }
    //释放资源

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    glfwTerminate();

    return 0;
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    mycamera.ProcessMouseScroll(yoffset);
}
float lastX = 400, lastY = 300;
bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) // 这个bool变量初始时是设定为true的
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY-ypos;
    lastX = xpos;
    lastY = ypos;
    mycamera.ProcessMouseMovement(xoffset,yoffset);

}
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    
    float cameraSpeed = 10.0f*deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        mycamera.ProcessKeyboard(Forward,deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        mycamera.ProcessKeyboard(Backward, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        mycamera.ProcessKeyboard(Left, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        mycamera.ProcessKeyboard(Right, deltaTime);
}
