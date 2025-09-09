#pragma once

#include <string>
#include <iostream>
#include <map>

namespace IMGL {

	// Shader.h
	// This file contains the Shader class, which is used to load and compile shaders for OpenGL rendering.
	// It provides methods to set uniforms and use the shader program.

	class Shader
	{

	public:
		unsigned int id;
		// Constructor reads and builds the shader
		Shader() = default;
		~Shader();
		Shader(const char* vertexPath, const char* fragmentPath);
		Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath);
		
		// Use/activate the shader
		void use();
		// Utility uniform functions
		void setBool(const std::string& name, bool value);
		void setUint(const std::string& name, unsigned int value);
		void setInt(const std::string& name, int value);
		void setFloat(const std::string& name, float value);
		void setUVec2(const std::string& name, unsigned int x, unsigned int y);
		void setVec2(const std::string& name, float x, float y);
		void setVec3(const std::string& name, float x, float y, float z);
		void setVec4(const std::string& name, float x, float y, float z, float w);
		void setMat4(const std::string& name, const float* mat);
	};

	class ShaderManager {
	public:
		ShaderManager();
		~ShaderManager();

		static ShaderManager* get();
		static void addShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
		static void addShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath);
		static Shader* getShader(const std::string& name);

		std::map<std::string, Shader> shaders;
	};

}