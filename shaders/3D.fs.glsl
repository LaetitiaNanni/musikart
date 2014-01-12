#version 330
 
uniform sampler2D uTexture;

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

uniform vec4 uDiffuse;
uniform vec4 uAmbient;
uniform vec4 uSpecular;
uniform vec4 uEmissive;
uniform float uShininess;
uniform int uTexCount;

out vec4 fFragColor;

vec4 blinnPhong() {
	vec3 wi = normalize(vec3(0.0,0.0,10.0));
	vec3 N = normalize(vNormal_vs);
	vec3 wo = normalize(-vPosition_vs);

	vec3 halfVector = 0.5f * (wi + wo);

	return 2 * (uDiffuse * dot(wi, N) + uSpecular * pow(dot(halfVector, N), uShininess));
}
 
void main()
{
    vec4 color;
    vec4 amb;
    float intensity;
    vec3 lightDir;
    vec3 n;
 
    lightDir = normalize(vec3(0.0,1.0,1.0));
    n = normalize(vNormal_vs);
    intensity = max(dot(lightDir,n),0.5);
 
    if (uTexCount == 0) {
        color = uDiffuse;
        amb = uAmbient;
    } else {
        color = texture(uTexture, vTexCoords);
        amb = color * 0.33;
    }
    
    fFragColor = (color * intensity) + amb;
    //fFragColor = blinnPhong();
}