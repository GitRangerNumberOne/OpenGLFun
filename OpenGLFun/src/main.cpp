#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

void ReadFileToString(std::string& outString, const std::string& fileName)
{
	std::ifstream VertexFS(fileName);
	std::string ReadLine;
	while (std::getline(VertexFS, ReadLine))
	{
		outString += ReadLine;
		outString += '\n';
	}
	VertexFS.close();
}

void CheckShaderCompilation(int shaderHandle)
{
	int sucess = 0;
	char infolog[512];
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &sucess);
	if (!sucess)
	{
		glGetShaderInfoLog(shaderHandle, 512, nullptr, infolog);
		std::cout << "Shader Compilation Error: " << infolog << std::endl;
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//this creates a window
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL_Fun", nullptr,nullptr);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));

	std::vector<float> Vertices{
		-0.5,-0.5, 0,
		 0.5,-0.5, 0,
		 0,    0.5,  0
	};

	//shader src
	std::string VertexShaderSrc;
	ReadFileToString(VertexShaderSrc, "Resources/BasicVertexShader.shader");
	std::string FragShaderSrc;
	ReadFileToString(FragShaderSrc, "Resources/BasicFragShader.shader");

	//vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexShaderSource = VertexShaderSrc.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	CheckShaderCompilation(vertexShader);
	//frag shader
	unsigned int FragShader;
	FragShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* FragmentShaderSrc = FragShaderSrc.c_str();
	glShaderSource(FragShader, 1, &FragmentShaderSrc, NULL);
	glCompileShader(FragShader);
	CheckShaderCompilation(FragShader);
	
	//shader program
	unsigned int ShaderProgram;
	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, vertexShader);
	glAttachShader(ShaderProgram, FragShader);
	glLinkProgram(ShaderProgram);
	glUseProgram(ShaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(FragShader);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//assign data, describe it, and enable it
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*Vertices.size(), Vertices.data() ,GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.3f, 0.3f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(ShaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0; 
}

