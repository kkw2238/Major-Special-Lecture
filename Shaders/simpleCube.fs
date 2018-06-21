#version 330

uniform vec3 u_LightPos;
uniform vec3 u_CameraPos;

const float c_Ambient  = 1.0f;
const float c_Diffuse  = 0.7f; 
const float c_Specular = 0.5f;
	
in vec4 v_Color;
in vec3 v_Normal;
in vec3 v_Pos;

out vec4 FragColor;

float angle(vec3 L, vec3 N) {
	float oneMinusDot = 1.0 - dot(L, N);
	float F = pow(oneMinusDot, 5.0);
	return F;
};

void main() 
{
	vec3 lightDir			= vec3(0.0f, -1.0f, 0.0f);
	vec3 toLight			= normalize(v_Pos - u_LightPos);
	vec3 cameraDirection	= normalize(u_CameraPos - v_Pos);
	vec3 reflectDir			= normalize(reflect(-toLight, v_Normal));

	float ambient  = 0.25f;
	float diffuse  = 0.0f;
	float specular = 0.0f;

	//float ang = angle(vec3(1.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f));
	
	diffuse = max(dot(v_Normal, -toLight), 0.0f);

	float ang = acos(diffuse) * 180.0f / 3.141592; 

		FragColor.rgb = ( 
		c_Ambient * ambient +
		c_Diffuse * diffuse +
		c_Specular * specular
		) * v_Color.rgb;


	//if(ang < 45.0f) {
	//	FragColor.rgb = ( 
	//	c_Ambient * ambient + 
	//	c_Diffuse * diffuse + 
	//	c_Specular * specular
	//	) * v_Color.rgb;
	//}
	//else if(ang < 60.0f) {
	//	FragColor.rgb = ( 
	//	c_Ambient * ambient + 
	//	c_Diffuse * diffuse + 
	//	c_Specular * specular
	//	) * v_Color.rgb * 0.5f;
	//}
	//else {
	//	FragColor.rgb = vec3(0.0f, 0.0f, 0.0f);
	//}
	FragColor.a = v_Color.a;
}