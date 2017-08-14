// Link statically with GLEW ==============> If use the static GLEW, there will be an error: 
// error LNK2005: _glewInit@0 already defined in glew32.lib(glew32.dll)

// #define GLEW_STATIC 

// Headers
#include <GL\glew.h>
#include <SDL2\SDL.h>
#include <SDL2\SDL_opengl.h>


// Shader sources. Version OpenGl is 4.4 ===> version of GLSL is 440
const GLchar* vertexSource = R"glsl(
    #version 440 core			
    in vec2 position;
	in vec3 color;
	out vec3 Color;
	void main()
	{
		Color = color;
		gl_Position = vec4(position.x, position.y, 0.0, 1.0);
	}
)glsl";
const GLchar* fragmentSource = R"glsl(
    #version 440 core
    in vec3 Color;
    out vec4 outColor;
    void main()
    {
		outColor = vec4(Color, 1.0);
    }
)glsl";


int main(int argc, char *argv[])
{

	//=========================================================================================================
	// Init SDL 
	SDL_Init(SDL_INIT_VIDEO);

	// Create a rendering window with OpenGL 3.2 context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_Window* window = SDL_CreateWindow("20170808_DrawingTriangle", 200, 200, 800, 600, SDL_WINDOW_OPENGL);

	// Create the OpenGL context
	SDL_GLContext context = SDL_GL_CreateContext(window);


	//=========================================================================================================
	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();


	//=========================================================================================================
	// Create Vertex Array Object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint vbo;
	glGenBuffers(1, &vbo);

	GLfloat vertices[] = {
		0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Create and compile the vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Create and compile the fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// Link the vertex and fragment shader into a shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));


	//=========================================================================================================
	// The event loop.
	SDL_Event windowEvent;
	while (true)
	{
		// Check if there are any new events that have to be handled.
		if (SDL_PollEvent(&windowEvent))
		{
			// If there is any event (now is only event that user click on the X button to close window).
			if (windowEvent.type == SDL_QUIT) break;
		}

		// Clear the screen to white
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw a triangle from the 3 vertices
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Take care os swapping the front and back buffer after new things have been drawn by your application.
		SDL_GL_SwapWindow(window);
	}


	//=========================================================================================================
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	glDeleteBuffers(1, &vbo);

	glDeleteVertexArrays(1, &vao);

	// Delete the OpenGL context. Context should be destroyed right before calling SDL_Quit() to clean up the resource.
	SDL_GL_DeleteContext(context);

	// SDL Quit
	SDL_Quit();

	return 0;
}