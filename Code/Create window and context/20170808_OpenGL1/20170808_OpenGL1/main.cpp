#include <stdio.h>
#include <GL\glew.h>
#include <SDL2\SDL.h>
#include <SDL2\SDL_opengl.h>

int main(int argc, char *argv[])
{

	// Init SDL 
	SDL_Init(SDL_INIT_VIDEO);

	// Create a rendering window with OpenGL 3.2 context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_Window* window = SDL_CreateWindow("20170808_OpenGL", 200, 200, 800, 600, SDL_WINDOW_OPENGL);

	// Create the OpenGL context
	SDL_GLContext context = SDL_GL_CreateContext(window);


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
		// Take care os swapping the front and back buffer after new things have been drawn by your application.
		SDL_GL_SwapWindow(window);
	}

	
	// Delete the OpenGL context. Context should be destroyed right before calling SDL_Quit() to clean up the resource.
	SDL_GL_DeleteContext(context);

	// SDL Quit
	SDL_Quit();
	
	return 0;
}