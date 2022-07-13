#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <shader_s.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
   
    glEnable(GL_DEPTH_TEST);

    Shader ourShader("src/camera.vs", "src/camera.fs");

    float vertices[] = {
        //first house
        //1
            -1, -1,  1, 0.25, 0.34,
            -1, -1, -1, 0.25, 0.66,
            -1,  1,  1, 0.00, 0.34,
            -1,  1,  1, 0.00, 0.34,
            -1,  1, -1, 0.00, 0.66,
            -1, -1, -1, 0.25, 0.66,


        //2
            -1, -1, -1, 0.25, 0.66,
            -1, -1,  1, 0.25, 0.34,
             1, -1,  1, 0.50, 0.34,
             1, -1,  1, 0.50, 0.34,
             1, -1, -1, 0.50, 0.66,
            -1, -1, -1, 0.25, 0.66,

       //3
            -1,  1, -1, 0.25, 1.00,
            -1, -1, -1, 0.25, 0.66,
             1, -1, -1, 0.50, 0.66,
             1, -1, -1, 0.50, 0.66,
             1,  1, -1, 0.50, 1.00,
            -1,  1, -1, 0.25, 1.00,

        //4
            -1,  1,  1, 0.25, 0.00,
            -1, -1,  1, 0.25, 0.34,
             1, -1,  1, 0.50, 0.34,
             1, -1,  1, 0.50, 0.34,
             1,  1,  1, 0.50, 0.00,
            -1,  1,  1, 0.25, 0.00,

       //5
              1, -1,  1, 0.50, 0.34,
              1, -1, -1, 0.50, 0.66,
              1,  1,  1, 0.75, 0.34,
              1,  1,  1, 0.75, 0.34,
              1,  1, -1, 0.75, 0.66,
              1, -1, -1, 0.50, 0.66,

        //6
             -1,  1, -1, 1.00, 0.66,
             -1,  1,  1, 1.00, 0.34,
              1,  1,  1, 0.75, 0.34,
              1,  1,  1, 0.75, 0.34,
              1,  1, -1, 0.75, 0.66,
             -1,  1, -1, 1.00, 0.66,

        

              -1.0f, 1.0f,  -1.0f,  0.0f, 0.0f,
               1.0f, 1.0f,  -1.0f,  1.0f, 0.0f,
               0.0f, 2.0f,   0.0f,  1.0f, 1.0f,

              -1.0f, 1.0f,   1.0f,  1.0f, 1.0f,
               1.0f, 1.0f,   1.0f,  0.0f, 1.0f,
               0.0f, 2.0f,   0.0f,  0.0f, 0.0f,

              -1.0f,  1.0f, -1.0f,  0.0f, 0.0f,
              -1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
               0.0f,  2.0f,  0.0f,  0.0f, 0.0f,

               1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
               1.0f,  1.0f,  1.0f,  0.0f, 1.0f,
               0.0f,  2.0f,  0.0f,  0.0f, 0.0f,

          //second house
          
          //1
                 -5,  1,  1, 0.25, 0.34,
                 -5, -1,  1, 0.25, 0.66,
                 -3, -1,  1, 0.00, 0.34,
                 -3, -1,  1, 0.00, 0.34,
                 -3,  1,  1, 0.00, 0.66,
                 -5,  1,  1, 0.25, 0.66,

           //2
                 -5, 1, -1, 0.25, 0.66,
                 -5, -1, -1, 0.25, 0.34,
                 -3, -1, -1, 0.50, 0.34,
                 -3, -1, -1, 0.50, 0.34,
                 -3,  1, -1, 0.50, 0.66,
                 -5,  1, -1, 0.25, 0.66,

          //3
                -5,  1,  1, 0.25, 1.00,
                -5,  1, -1, 0.25, 0.66,
                -5, -1,  1, 0.50, 0.66,
                -5, -1,  1, 0.50, 0.66,
                -5, -1, -1, 0.50, 1.00,
                -5,  1, -1, 0.25, 1.00,

         //4
                -3,  1,  1, 0.25, 0.00,
                -3,  1, -1, 0.25, 0.34,
                -3, -1,  1, 0.50, 0.34,
                -3, -1,  1, 0.50, 0.34,
                -3, -1, -1, 0.50, 0.00,
                -3,  1, -1, 0.25, 0.00,

         //5
               -3, -1, -1, 0.50, 0.34,
               -3, -1,  1, 0.50, 0.66,
               -5, -1, -1, 0.75, 0.34,
               -5, -1, -1, 0.75, 0.34,
               -5, -1,  1, 0.75, 0.66,
               -3, -1,  1, 0.50, 0.66,

        //6
               -3,  1, -1, 1.00, 0.66,
               -3,  1,  1, 1.00, 0.34,
               -5,  1, -1, 0.75, 0.34,
               -5,  1, -1, 0.75, 0.34,
               -5,  1,  1, 0.75, 0.66,
               -3,  1,  1, 1.00, 0.66,

        

               -5.0f, 1.0f,   1.0f,  0.0f, 0.0f,
               -3.0f, 1.0f,   1.0f,  1.0f, 0.0f,
               -4.0f, 2.0f,   0.0f,  1.0f, 1.0f,

               -5.0f, 1.0f,  -1.0f,  1.0f, 1.0f,
               -3.0f, 1.0f,  -1.0f,  0.0f, 1.0f,
               -4.0f, 2.0f,   0.0f,  0.0f, 0.0f,

               -5.0f,  1.0f, -1.0f,  0.0f, 0.0f,
               -5.0f,  1.0f,  1.0f,  1.0f, 0.0f,
               -4.0f,  2.0f,  0.0f,  0.0f, 0.0f,

               -3.0f,  1.0f, -1.0f,  1.0f, 1.0f,
               -3.0f,  1.0f,  1.0f,  0.0f, 1.0f,
               -4.0f,  2.0f,  0.0f,  0.0f, 0.0f,


               -12.0f, -1.0f, -12.0f, 0.0f, 0.0f,
               -12.0f, -1.0f,  12.0f, 1.0f, 0.0f,
                12.0f, -1.0f,  12.0f, 1.0f, 1.0f,

                12.0f, -1.0f,  12.0f, 1.0f, 1.0f,
                12.0f, -1.0f, -12.0f, 0.0f, 1.0f,
               -12.0f, -1.0f, -12.0f, 0.0f, 0.0f,


      

               0.0f, -1.0f, -3.0f, 0.0f, 0.0f,
               4.0f, -1.0f, -3.0f, 1.0f, 0.0f,
               2.0f,  3.0f, -4.0f, 1.0f, 1.0f,

               0.0f, -1.0f, -5.0f, 1.0f, 1.0f,
               4.0f, -1.0f, -5.0f, 0.0f, 1.0f,
               2.0f,  3.0f, -4.0f, 0.0f, 0.0f,

              0.0f, -1.0f, -5.0f, 0.0f, 0.0f,
              0.0f, -1.0f, -3.0f, 0.0f, 1.0f,
              2.0f,  3.0f, -4.0f, 0.0f, 0.0f,

              4.0f, -1.0f, -5.0f, 1.0f, 1.0f,
              4.0f, -1.0f, -3.0f, 0.0f, 1.0f,
              2.0f,  3.0f, -4.0f, 0.0f, 0.0f,

        

              0.0f, -1.0f, -3.0f, 0.0f, 0.0f,
             -4.0f, -1.0f, -3.0f, 1.0f, 0.0f,
             -2.0f,  3.0f, -4.0f, 1.0f, 1.0f,

              0.0f, -1.0f, -5.0f, 1.0f, 1.0f,
             -4.0f, -1.0f, -5.0f, 0.0f, 1.0f,
             -2.0f,  3.0f, -4.0f, 0.0f, 0.0f,

              0.0f, -1.0f, -5.0f, 0.0f, 0.0f,
              0.0f, -1.0f, -3.0f, 0.0f, 1.0f,
             -2.0f,  3.0f, -4.0f, 0.0f, 0.0f,

              -4.0f, -1.0f, -5.0f, 1.0f, 1.0f,
              -4.0f, -1.0f, -3.0f, 0.0f, 1.0f,
              -2.0f,  3.0f, -4.0f, 0.0f, 0.0f,

       

              2.5f,  0.0f,  0.0f, 0.0f, 0.0f,
              4.5f,  0.0f,  0.0f, 1.0f, 0.0f,
              3.5f,  3.0f,  0.0f, 1.0f, 1.0f,

              3.5f,  0.0f,  1.0f, 1.0f, 1.0f,
              3.5f,  0.0f, -1.0f, 0.0f, 1.0f,
              3.5f,  3.0f,  0.0f, 0.0f, 0.0f,

        
          //1
           

              3.0f,  0.0f,  0.0f, 0.25, 0.34,
              3.0f, -1.0f,  0.0f, 0.25, 0.66,
              4.0f, -1.0f,  0.0f, 0.00, 0.34,
              4.0f, -1.0f,  0.0f, 0.00, 0.34,
              4.0f,  0.0f,  0.0f, 0.00, 0.66,
              3.0f,  0.0f,  0.0f, 0.25, 0.66,

         //2
              3.5f,  0.0f,  0.5f, 0.25, 0.66,
              3.5f,  0.0f, -0.5f, 0.25, 0.34,
              3.5f, -1.0f,  0.5f, 0.50, 0.34,
              3.5f, -1.0f,  0.5f, 0.50, 0.34,
              3.5f, -1.0f, -0.5f, 0.50, 0.66,
              3.5f,  0.0f, -0.5f, 0.25, 0.66,

    };

    
    glm::vec3 cubePositions[] = {
       glm::vec3(0.0f,  0.0f,  0.0f)
   
    };


    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
   
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    unsigned int texture1, texture2;
    // texture 1
    
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
   

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); 
    unsigned char* data = stbi_load("src/iceland.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // texture 2
   
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    data = stbi_load("src/scar.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);


    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    ourShader.setMat4("projection", projection);

    while (!glfwWindowShouldClose(window))
    {
        
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        
        ourShader.use();

        glm::mat4 view = glm::mat4(1.0f);
        float radius = 13.0f;
        float camX = static_cast<float>(sin(glfwGetTime()) * radius);
        float camZ = static_cast<float>(cos(glfwGetTime()) * radius);
        view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        ourShader.setMat4("view", view);

        glBindVertexArray(VAO);
        
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[0]);
            float angle = 0;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0,144);
       

        glfwSwapBuffers(window);
        
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}