// GLAD must be included before GLFW
#include "Shader.h"
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "stb_image.h"
#include "Texture.h"
#include <vector>

const float SCR_WIDTH{ 800.0f };
const float SCR_HEIGHT{ 600.0f };

class Engine
{
public:
	GLFWwindow* window;
	Camera camera;
	Shader shader;
	Shader light_shader;
	bool firstMouse;
	float lastX;
	float lastY;
	float lastFrame;
	float deltaTime;
	std::vector<unsigned int> textures;
	unsigned int n_vertices;
	unsigned int VBO, VAO, lightVAO;

	Engine();
	~Engine();
	int InitWindow();
	void SetShaders(const char* vertexPath, const char* fragmentPath);
	void SetLightShaders(const char* vertexPath, const char* fragmentPath);
	void LoadTextureFromImage(const char* imagePath, bool isPng = false);
	void SetBuffers(const float* verts, unsigned int length, bool texture_coordinates);
	void SetLightBuffers();
	void EnableTextures();
	void BindVertexArray();
	void BindLightVertexArray();
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

