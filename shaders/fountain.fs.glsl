#version 330 core

in FragmentData {
	vec3 position;
	vec3 normal;
	vec2 texCoords;
} fragment;

uniform sampler2D uTexture;
uniform float radius;

uniform vec3 uLightDirection;
uniform vec3 uLightColor;
uniform float uLightIntensity;
uniform float uSpecularPower;
uniform vec3 uCameraPosition;

layout(location = 0) out vec4 Color;
layout(location = 1) out vec4 Normal;

vec3 directionalLight(vec3 n, vec3 v, vec3 diffuseColor, vec3 specularColor, float specularPower){
	vec3 l = normalize(-uLightDirection);
	float ndotl =  max(dot(n, l), 0.0);
	vec3 h = normalize(l+v);
	float ndoth = max(dot(n, h), 0.0);
	return  uLightColor * uLightIntensity * (diffuseColor * (ndotl+0.2f) + specularColor * pow(ndoth, specularPower));
}

void main() {
	vec3 n = normalize(fragment.normal);
	vec3 v = normalize(uCameraPosition-fragment.position);
	vec3 diffuseColor = texture(uTexture, fragment.texCoords).rgb;
	vec3 specularColor = texture(uTexture, fragment.texCoords).rrr;

	Color = vec4(directionalLight(n, v, diffuseColor, specularColor, uSpecularPower),1.f); 
//	Normal = vec4(vec3(fragment.normal),SpecularPower);
	Normal = vec4(vec3(fragment.normal),1.f);
};