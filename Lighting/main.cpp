#include "Engine.h"


int main() {
	Engine engine{};

	engine.InitWindow();

	engine.SetShaders("vertex.glsl", "fragment.glsl");
	engine.SetLightShaders("vertex.glsl", "light_fragment.glsl");

    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

	engine.SetBuffersWithNormal(vertices, 36*6);
	// we are reusing the VBO so the call should be after the vbo init.
	engine.SetLightBuffers();

    glm::vec3 lightPos{ 1.2f, 1.0f, 2.0f };

    while (!engine.ShouldClose()) {
        engine.Tick();
        engine.ProcessInput();
        engine.Clear(0.1f, 0.1f, 0.1f, 1.0f);

        engine.shader.use();
        engine.shader.setVec3("objectColor", glm::vec3{ 1.0f, 0.5f, 0.31f });
        engine.shader.setVec3("lightColor", glm::vec3{1.0f, 1.0f, 1.0f});
        engine.shader.setVec3("lightPos", lightPos);

		glm::mat4 view = engine.camera.GetViewMatrix();

		glm::mat4 projection = glm::perspective(glm::radians(engine.camera.Zoom), SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);

		glm::mat4 model{1.0f};

		engine.shader.setMat4("model", model);
		engine.shader.setMat4("view", view);
		engine.shader.setMat4("projection", projection);

		engine.BindVertexArray();
		engine.Draw();


		engine.light_shader.use();

        
		model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3{ 0.2f });
		engine.light_shader.setMat4("model", model);
		engine.light_shader.setMat4("view", view);
		engine.light_shader.setMat4("projection", projection);
        engine.light_shader.setVec3("lightPos", lightPos);
		engine.BindLightVertexArray();
		engine.Draw();

		engine.Swap();
		engine.PollEvents();
	}
}