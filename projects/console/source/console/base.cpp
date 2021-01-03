#include "headers/base.h"
#include <iostream>

namespace console
{
    void lib_test()
    {
        std::cout << "Library test - console\n";
    }

    int window_test()
    {
        GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -3;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK)
        return -2;



    float pos[] =
    {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f,
    };

    abstract::vertex_array vao;

    abstract::vertex_buffer vbo(GL_ARRAY_BUFFER);
    vbo.buffer_data(sizeof(pos), pos, GL_STATIC_DRAW);

    vbo.bind();
    vao.vertex_attrib_pointer(0, 2, GL_FLOAT, GL_FALSE, 
                   sizeof(float)*2, nullptr);
    vao.bind();

    glClearColor(0.4f, 0.4f, 0.9f, 1.0f);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
    }
}