#version 430 core

layout(location = 0) in vec3 a_Position;

out vec3 vs_FragColor;

void main() {
	gl_Position = vec4(a_Position.x - 0.5, a_Position.y - 0.5, a_Position.z, 1.0);
	vs_FragColor = vec3(a_Position.xy, -a_Position.z);
}