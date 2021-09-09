#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoords;


out vec4 v_Color;
out vec3 v_Pos;
out vec2 v_TexCoords;

//uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

void main()
{
	//gl_Position = u_ProjectionMatrix * vec4(aPos, 1.0);
	gl_Position = u_ProjectionMatrix * u_ViewMatrix * vec4(aPos, 1.0);
	//gl_Position = vec4(aPos, 1.0);
    v_Pos = aPos;
    v_Color = aColor;
    v_TexCoords = aTexCoords;
}

#shader fragment
#version 330 core

out vec4 Color;
in vec4 v_Color;
in vec3 v_Pos;
in vec2 v_TexCoords;
uniform vec4 u_Color;
uniform vec2 u_Quantity;

uniform sampler2D u_Texture;

void main()
{
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    //Color = v_Color;
   // Color = texture(u_Texture, v_TexCoords * 10.0f);
    Color = texture(u_Texture, vec2(v_TexCoords.x * u_Quantity.x, v_TexCoords.y * u_Quantity.y)) * v_Color;
   // Color = vec4(v_TexCoords,0.0f,1.0f);

} 