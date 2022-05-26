#version 400
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;

varying vec2 textcoord;
varying vec3 normal;

void main() {
	textcoord = gl_MultiTexCoord0.xy;
	
	normal = vertexNormal;
	
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vec4(vertexPosition, 1);
}