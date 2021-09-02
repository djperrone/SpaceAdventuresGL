#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;


out vec4 coords;
void main()
{
	gl_Position = vec4(aPos, 1.0);
}

#shader fragment
#version 330 core

out vec4 FragColor;
uniform vec4 u_Color;

void main()
{
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    FragColor = u_Color;
} 