#include <glad/glad.h>
#include <algorithm>

class Texture
{

private:
	GLuint obj_ = 0;

	void Release() {
		glDeleteTextures(1, &obj_);
		obj_ = 0;
	}
public: 
	~Texture() { Release(); }

	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	Texture(Texture&& other) : obj_(other.obj_) {
		other.obj_ = 0;
	}

	Texture& operator=(Texture&& other) {
		if (this != &other) {
			Release();
			std::swap(obj_, other.obj_);
		}
	}
};

