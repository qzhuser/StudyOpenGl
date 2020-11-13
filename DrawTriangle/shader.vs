#version 330 core
layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aColor;
layout(location=2) in vec2 aTexCoord1;
layout(location=3) in vec2 aTexCoord2;
uniform float offset;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 ourColor;
out vec3 ourPos;
out vec2 TexCoord1;
out vec2 TexCoord2;

void main(){
	gl_Position=projection*view*model*vec4(aPos.x,aPos.y+offset,aPos.z,1.0);
	ourPos=aPos;
	ourColor=aColor;
	TexCoord1=aTexCoord1;
	TexCoord2=aTexCoord2;
}