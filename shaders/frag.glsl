// ====================================================
#version 330 core

// Our light sources
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float ambientIntensity;
// Used for our specular highlights
uniform mat4 view;
// Used for fog effect
uniform vec3 skyColor;

// ======================= IN =========================
in vec3 v_normal; 
in vec3 v_color;
in vec3 FragPos;
in float visibility;

// ======================= out ========================
out vec4 FragColor;

// ======================= Globals ====================
float specularStrength = 0.1f;


void main()
{
    // (1) Compute ambient light
    vec3 ambient = ambientIntensity * lightColor;

    // (2) Compute diffuse light
    
    vec3 lightDir = normalize(lightPos - FragPos);
    float diffImpact = max(dot(v_normal, lightDir), 0.0);
    vec3 diffuseLight = diffImpact * lightColor;

    // (3) Compute Specular lighting
    vec3 viewPos = (inverse(view)*vec4(0.0,0.0,0.0,1.0)).xyz;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, v_normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 Lighting = diffuseLight + ambient + specular;

    // Final color + "how dark or light to make fragment"
    FragColor = vec4(v_color * Lighting,1.0);
    FragColor = mix(vec4(skyColor, 1.0), FragColor, visibility);
}
// ==================================================================
