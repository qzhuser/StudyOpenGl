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

float deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
float lastFrame = 0.0f; // ��һ֡��ʱ��
float pitch, yaw;
float fov = 45.0f;
Camera mycamera(glm::vec3(0.0f,0.0f,3.0f));

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    //�����ӿ� ǰ�����������ô������½ǵ�λ�� �������ǿ�Ⱥ͸߶ȣ����أ�
    glViewport(0, 0, width, height);
}
//����
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
    
    glfwInit();//��ʼ��
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //GLFW����glfwCreateWindow��width,height,title��������һ�����ڶ���
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", NULL, NULL);
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
    


    //��������
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
   

    //����VBO�����㻺����󣩣�VAO������������󣩣�EBO�������������
    unsigned int VBO,VAO,EBO,texture1,texture2;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenTextures(1,&texture1);
    
    //��VAO
    glBindVertexArray(VAO);

    //�󶨻���Ŀ��
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //�Ѷ������ݸ��Ƶ�����Ŀ����ڴ���
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    //������������(Ҫ���õĶ������Ե�λ��ֵ����ɫ����������0������ǰ�������ԵĴ�С��vec3��3��float�����������ͣ��Ƿ�ϣ��normalize������ֵ���ƶ�����vec3��λ�ú���ɫ����ƫ������λ������ǰ����ɫҪ����ƫ��λ�����Եĳ��ȣ�Ҳ����3*sizeof(float)��)
    //λ������
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    //���ö�������  ������λ��ֵ
    glEnableVertexAttribArray(0);

    //��ɫ����
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);
    //��������1
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    //��������2
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(3);

    glBindTexture(GL_TEXTURE_2D, texture1);

    //�������ST�����û��Ʒ�ʽ
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //ָ���Ŵ����С�Ĺ��˷�ʽ
    //GL_LINEAR_MIPMAP_LINEAR:�༶��Զ����������ƥ�����ش�С�Ķ༶����֮����в�ֵ��
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    //GL_LINEAR:��ͨ�����Թ��ˣ������������긽�������ؼ���һ����ֵ��GL_NEAREST:�ٽ����ˣ�ֱ��ѡȡ���������
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    //���ز���������
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        //ͼƬ�����������
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        //���ɶ༶��Զ����
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    //�ͷ�ͼ���ڴ�
    stbi_image_free(data);
    //�ڶ�������
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    //�������ST�����û��Ʒ�ʽ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //ָ���Ŵ����С�Ĺ��˷�ʽ
    //GL_LINEAR_MIPMAP_LINEAR:�༶��Զ����������ƥ�����ش�С�Ķ༶����֮����в�ֵ��
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //GL_LINEAR:��ͨ�����Թ��ˣ������������긽�������ؼ���һ����ֵ��GL_NEAREST:�ٽ����ˣ�ֱ��ѡȡ���������
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //���ز���������
    data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
    if (data) {
        //ͼƬ�����������
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        //���ɶ༶��Զ����
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    //�ͷ�ͼ���ڴ�
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
    //������Ȳ���
    glEnable(GL_DEPTH_TEST);
    //���ع��
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //��Ⱦѭ��
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window,scroll_callback);
        //glfwSetKeyCallback(window,key_callback);
        processInput(window);

        //�����Ļʹ�õ���ɫ
        glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
        //�����Ļ����ɫ���壬��Ȼ���
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
        //��ͼ��Ҫ��ʲô�����������㣩
        //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        //����Ƿ��д����¼�
        glfwSwapBuffers(window);
        //������ɫ���壨Doubule Buffer��
        glfwPollEvents();
    }
    //�ͷ���Դ

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
    if (firstMouse) // ���bool������ʼʱ���趨Ϊtrue��
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
