#version 330

#define MAX_LIGHTS_PER_WORLD 12
#define NEAR_PLANE 0.05
#define FAR_PLANE 100.0

struct light
{
	vec3 location;
	float intensity;
	float attenuation;
	vec3 color;
	sampler2D shadow_map;
};

// Input vertex attributes (from vertex shader)
in vec3 fragPosition;
in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragNormal;
in vec4 fragPosLightSpace[MAX_LIGHTS_PER_WORLD];

// Output fragment color
out vec4 finalColor;

uniform int lights_count;
uniform light lights[MAX_LIGHTS_PER_WORLD];

float get_light_attenuation(const light in_light);
vec3 calculate_light(const light in_light);
float get_band_mask(const vec3 light_location, const float offset, const float range);
float get_raw_depth();
float get_linear_depth();
float calculate_shadows(const sampler2D shadow_map, const vec4 frag_pos_light_space);

void main()
{
	// ambient color
	vec3 final_color = vec3(.03f);

	// first ambient pass for lights
	for(int i = 0 ; i < lights_count ; i++)
	{
        float shadow = calculate_shadows(lights[i].shadow_map, fragPosLightSpace[i]);
        vec3 point_light_color = calculate_light(lights[i]);
//		point_light_color *= (1.0 - shadow);
		final_color += point_light_color;

        // Apply lighting calculations with the shadow value
        // Ambient lighting
//	    vec3 light_dir = normalize(lights[i].location - fragPosition);
//        vec3 normal_dir = normalize(fragNormal);
//        vec3 ambient = lights[i].intensity * lights[i].color;
//		float distance_to_light = length(lights[i].location - fragPosition);
//		float attenuation = get_light_attenuation(lights[i]);
//		final_color += (dot(normalize(fragNormal), normalize(lights[i].location)) * lights[i].intensity * lights[i].color * attenuation * (1.0 - shadow));
	}

	// rim light
	for(int i = 0 ; i < lights_count ; i++)
	{
		float attenuation = get_light_attenuation(lights[i]);
		float band_mask = get_band_mask(lights[i].location, 0.99f - attenuation, 0.01f);
		final_color = mix(final_color, lights[i].color, band_mask);	
	}

	//fog
//	final_color += mix(vec3(.01f, .02f, 0.1f), vec3(0.f), gl_FragCoord.a);

	// output
	finalColor = vec4(final_color,1.f);
};

float get_light_attenuation(const light in_light)
{
	float distance_to_light = distance(in_light.location, fragPosition);
	float attenuation_sphere = clamp(1.f - distance_to_light/in_light.attenuation, .0f, 1.f);
	// 0.5f and 0.001f define the softness of the light, expose later
	return (1.f / (1.f + .5f * distance_to_light + .01f * distance_to_light * distance_to_light)) * attenuation_sphere;
};

vec3 calculate_light(const light in_light)
{
    vec3 lightDir = normalize(in_light.location - fragPosition);
    vec3 viewDir = normalize(-fragPosition); // Assuming the camera/viewer is at the origin

    // Diffuse lighting
    float diff = max(dot(fragNormal, lightDir), 0.0);
    vec3 diffuse = diff * in_light.intensity * in_light.color;

    // Specular lighting
    float specularStrength = 0.5; // Adjust as needed
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(fragNormal, halfwayDir), 0.0), 32.0); // Shininess factor of 32, adjust as needed
    vec3 specular = specularStrength * spec * in_light.intensity * in_light.color;

    // Attenuation
    float distance = distance(in_light.location, fragPosition);
    float attenuation = 1.0 / (1.0 + in_light.attenuation * pow(distance, 2.0));

    return (diffuse + specular) * attenuation;
}

float get_band_mask(const vec3 light_location, const float offset, const float range)
{
	return smoothstep(offset, offset + range, dot(normalize(fragNormal), normalize(light_location)));
};

float get_raw_depth()
{
	return gl_FragColor.a;
}

float get_linear_depth()
{
    float z = get_raw_depth() * 2.f - 1.f; // back to NDC 
    return (2.f * NEAR_PLANE * FAR_PLANE) / (FAR_PLANE + NEAR_PLANE - z * (FAR_PLANE - NEAR_PLANE));
}

float calculate_shadows(const sampler2D shadow_map, const vec4 frag_pos_light_space)
{
    vec3 proj_coords = frag_pos_light_space.xyz / frag_pos_light_space.w;
    proj_coords = proj_coords * 0.5 + 0.5;
    float depth = texture(shadow_map, proj_coords.xy).r;
    float linear_depth = get_linear_depth();
    float shadow = proj_coords.z > depth + 0.0025 * linear_depth ? 1.0 : 0.0; // Add bias to account for shadow acne
    return shadow;
}