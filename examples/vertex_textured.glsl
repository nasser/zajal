attribute vec4 position;
attribute vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

varying vec2 texCoordVar;

void main()
{
	vec4 p = viewMatrix * modelMatrix  * position;
    texCoordVar = texCoord;
	gl_Position = projectionMatrix * p;
}