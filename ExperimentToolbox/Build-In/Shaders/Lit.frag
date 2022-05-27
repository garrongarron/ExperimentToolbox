#version 400
varying vec2 textcoord;
varying vec3 normal;

void main() {
	gl_FragColor = vec4(normal, 1);
}
