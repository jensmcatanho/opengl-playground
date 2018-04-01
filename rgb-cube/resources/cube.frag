#version 430 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
    float shininess;
};

in vec3 vs_FragColor;
in vec2 vs_TexCoord;

layout(location = 6) uniform Material u_Material;

out vec4 FragColor;

void main() {
	FragColor = vec4(vs_FragColor, 1.0);
	FragColor += texture(u_Material.diffuse, vs_TexCoord);
}