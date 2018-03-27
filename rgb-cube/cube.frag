#version 430 core

in vec3 vs_FragColor;

out vec4 FragColor;

void main() {
	FragColor = vec4(vs_FragColor, 1.0);
}