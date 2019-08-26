#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;

out vec2 tex_out;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;

void main() {
	gl_Position = proj * view * vec4(pos.xyz, 1.0);
	tex_out = tex.xy;
}
