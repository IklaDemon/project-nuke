/*
 *  glad API to access OpenGL function pointers
 */
#include <glad/gl.h>
/*
 *  GLFW API to handle windows and user input
 */
#include <GLFW/glfw3.h>
/*
 *  standard input/ouput c library
 */
//#include <linmath.h>
#include <stdio.h>

// callback prototype to handle window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// function to handle user input (ESC type)
void processInput(GLFWwindow* window);
 
int main(void)
{
	// VBO = vertex buffer object
	unsigned int VBO;
	unsigned int VAO;
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;

	int success;
	char infoLog[512];

	float vertices_1[] = {
		-0.5f, -0.5f, 0.0f,//a
		0.5f, -0.5f, 0.0f, //b
		-0.5f, 0.5f, 0.0f  //c
	};
	float vertices_2[] = {
		0.5f, -0.5f, 0.0f,//a
		0.5f, 0.5f, 0.0f, //b
		-0.5f, 0.5f, 0.0f //c
	};

	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

    	// glfw: initialize and configure
    	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    	// glfw window creation
    	// --------------------
	GLFWwindow* window = glfwCreateWindow(800, 600, "FirstGLWin", NULL, NULL);
	if (window == NULL)
	{
		printf("Error while creating window.");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    	// glad: load all OpenGL function pointers
    	// ---------------------------------------
	if (!gladLoadGL(glfwGetProcAddress))
	{
		printf("Error while initializing GLAD.");
		return -1;
	}

    	// build and compile our shader program
	// ------------------------------------
    	// vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s", infoLog);
	}
	// fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s", infoLog);
	}
	// link shader
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("ERROR::SHADER::LINK::COMPILATION_FAILED\n%s", infoLog);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//glViewport(0, 0, 800, 600);

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
    	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	// 0. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_2), vertices_2, GL_STATIC_DRAW);
	// ;
	// 1. then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

    	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

	//glUseProgram(shaderProgram);
	//glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	while(!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// end of program
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, 1);
	}
}
