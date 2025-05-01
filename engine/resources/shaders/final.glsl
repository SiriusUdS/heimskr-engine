#version 330 core
layout (location = 0) in vec4 in_quad;
out vec2 uvs;

void main() {
	uvs = vec2(in_quad.z, in_quad.w);
	gl_Position = vec4(in_quad.x, in_quad.y, 0.0, 1.0);
}

++VERTEX++

#version 330 core
out vec4 out_fragment;
in vec2 uvs;

uniform sampler2D u_map;

void main() {
	out_fragment = texture(u_map, uvs);
}

++FRAGMENT++