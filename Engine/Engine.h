// GLAD must be included before GLFW
#include "Shader.h"
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "stb_image.h"
#include "Texture.h"
#include <vector>

const unsigned int SCR_WIDTH{ 800 };
const unsigned int SCR_HEIGHT{ 600 };

class Engine
{
public:
	GLFWwindow* window;
	Camera camera;
	Shader shader;
	bool firstMouse;
	float lastX;
	float lastY;
	float lastFrame;
	float deltaTime;
	std::vector<unsigned int> textures;
	unsigned int n_vertices;
	unsigned int VBO, VAO;

	Engine();
	~Engine();
	int InitWindow();
	void SetShaders(const char* vertexPath, const char* fragmentPath);
	void LoadTextureFromImage(const char* imagePath, bool isPng = false);
	void SetBuffers(const float* verts, int length);
	void EnableTextures();
	void BindVertexArray();
	void Draw();
	void ProcessInput();
	bool ShouldClose();
	void Tick();
	void Clear(float r, float g, float b, float a);
	void Swap();
	void PollEvents();
	void Release();
private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
};

