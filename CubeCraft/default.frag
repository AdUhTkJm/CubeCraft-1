#version 330 core

in vec2 tex_out;
out vec4 frag;

uniform sampler2D textu;

void main(){
	frag = texture(textu, tex_out);
}
