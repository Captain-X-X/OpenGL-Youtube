#ifndef SHADER_H
#define SHADER_H
#include <glm/glm.hpp>
namespace DLEngine
{
	class Shader
	{
	private:
		unsigned int vertexShader; 
		unsigned int FragmentShader;
		const char* fragFile;
		const char* vertFile;
	public:
		Shader(){}
		Shader(const char* shaderVert, const char* shaderFrag);
		unsigned int shaderProgram_id = 0;
		bool LoadShaders(unsigned int & shaderPrograme, const char* shaderVert, const char* shaderFrag);
		void Use_program(unsigned int & shaderPrograme, int reset = 1);
		void use(int value);

		// Shader Options
		void set1i(const char* name, int value);
		void set1f(float value, const char* name);
		void setVec2f(glm::fvec2 value, const char* name);
		void setVec3f(glm::fvec3 value, const char* name);
		void setVec4f(glm::fvec4 value, const char* name);
		void setMat3fv(glm::mat3 value, const char* name, unsigned char transpose);
		void setMat4fv(glm::mat4 value, const char* name, unsigned char transpose);
		void Set_VertexAttribPoint(int index, int size, const void* pointer);
	};
}
#endif // SHADER_H