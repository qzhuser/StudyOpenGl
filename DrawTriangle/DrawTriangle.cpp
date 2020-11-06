#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <stdio.h> 
#include <iostream>

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

const char* vertexShaderSource = "#version 330 core\n"
        "layout (location =0) in vec3 aPos;\n"
        "layout(location=1) in vec3 aColor;\n"
        "out vec3 ourColor;"
        "void main()"
        " {\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "   ourColor=aColor;\n"//��Ҫ���ݸ�Ƭ����ɫ����ourcolor����Ϊ�Ӷ���������õ���������ɫ
        "}\0";
const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 ourColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor=vec4(ourColor,1.0);\n"
        "}\n\0";



int main() {
    
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
    //ÿ�����ڵ�����Сʱ �Զ�������������������µ����ӿ�
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //��ʼ��GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    ////����һ��������ɫ��
    //int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    ////����ɫ��Դ����ӵ���ɫ���ϣ�Ȼ����루�Ǹ�1��Դ���ַ���������
    //glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    //glCompileShader(vertexShader);
    ////���glCompileShader�Ƿ����ɹ�
    //int success;
    //char infoLog[512];
    //glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    ////�������ʧ�� ��ӡ������Ϣ
    //if (!success) {
    //    glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
    //    std::cout << "ERROR:SHADER VERTEX COMPILATION_FAILED\n" << infoLog << std::endl;
    //}
    ////����һ��ƬԪ��ɫ��
    //int fragmentShader;
    //fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    //glCompileShader(fragmentShader);

    ////�������ʧ�� ��ӡ������Ϣ
    //glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    //if (!success) {
    //    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    //    std::cout << "ERROR:SHADER FRAGMENT COMPILATION_FAILED\n" << infoLog << std::endl;
    //}
    ////������ɫ������
    //int shaderProgram;
    //shaderProgram = glCreateProgram();
    ////����ɫ�����ӵ������� Ȼ����glLinkProgram����
    //glAttachShader(shaderProgram,vertexShader);
    //glAttachShader(shaderProgram, fragmentShader);
    //glLinkProgram(shaderProgram);
    ////�������
    //glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    //if (!success) {
    //    glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
    //    std::cout << "ERROR SHADER PROGRAM LINKING_FAILD\n" << infoLog << std::endl;
    //}
    ////�Ѿ����ӵ����� ����ɾ��shader������
    //glDeleteShader(vertexShader);
    //glDeleteShader(fragmentShader);

    Shader myShader("shader.vs","shader.fs");

    //��������
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

    //����VBO�����㻺����󣩣�VAO������������󣩣�EBO�������������
    unsigned int VBO,VAO,EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1,&EBO);
    //��VAO
    glBindVertexArray(VAO);

    //�󶨻���Ŀ��
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    //�Ѷ������ݸ��Ƶ�����Ŀ����ڴ���
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    //������������(Ҫ���õĶ������Ե�λ��ֵ����ɫ����������0������ǰ�������ԵĴ�С��vec3��3��float�����������ͣ��Ƿ�ϣ��normalize������ֵ���ƶ�����vec3��λ�ú���ɫ����ƫ������λ������ǰ����ɫҪ����ƫ��λ�����Եĳ��ȣ�Ҳ����3*sizeof(float)��)
    //λ������
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    //���ö�������  ������λ��ֵ
    glEnableVertexAttribArray(0);

    //��ɫ����
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);


    //��Ⱦѭ��
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        //�����Ļʹ�õ���ɫ
        glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
        //�����Ļ����ɫ����
        glClear(GL_COLOR_BUFFER_BIT);

        myShader.use();
        float timeValue = glfwGetTime();
        float t = sin(timeValue)/2;
        myShader.SetFloat("offset", t);
        //glUseProgram(shaderProgram);
        //����ɫ������֮�⶯̬�ı���ɫ������
        /*float timeValue = glfwGetTime();
        float t = sin(timeValue) / 2 + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram,"ourColor");
        glUniform4f(vertexColorLocation,t,1.0f,1.0f,1.0f);*/

        glBindVertexArray(VAO);
        //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        //��ͼ��Ҫ��ʲô�����������㣩
        glDrawArrays(GL_TRIANGLES,0,6);
        //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        //glBindVertexArray(0);

        //����Ƿ��д����¼�
        glfwSwapBuffers(window);
        //������ɫ���壨Doubule Buffer��
        glfwPollEvents();
    }
    //�ͷ���Դ

    glfwTerminate();

    return 0;
}
