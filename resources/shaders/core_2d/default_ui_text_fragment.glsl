// Abstract Shader Engine - Jed Fakhfekh - https://github.com/ougi-washi
// inspired by https://www.shadertoy.com/view/stVBRR

#version 450

#include "as_ui_text_layout.glsl"
#include "as_2d_sdf_shapes.glsl"

uint decode_char(uint encoded_chars, int char_index_in_u32) {
    return (encoded_chars >> (char_index_in_u32 * 8)) & 0xFF; // Extract the corresponding byte
}
uint[4] decode_chars(uint encoded_chars) 
{
    uint c1 = (encoded_chars >> 24) & 0xFF; 
    uint c2 = (encoded_chars >> 16) & 0xFF; 
    uint c3 = (encoded_chars >> 8) & 0xFF;  
    uint c4 = encoded_chars & 0xFF;    
    return uint[4](c1, c2, c3, c4);
}

float get_char(vec2 position, uint c) 
{
    vec2 new_uv = uv;
    vec2 uv_char_offset = vec2(mod(c, FONT_TEXTURE_SUB_X), floor(c / FONT_TEXTURE_SUB_X));
    vec2 uv_char_text_coord = (uv_char_offset + .5) * FONT_TEXTURE_CHAR_SIZE;
    float char_mask = step(distance(uv, position ), FONT_TEXTURE_CHAR_SIZE.x/ 2.); //+ 
    return (smoothstep(.5, .55, 1. - texture(tex_sampler, uv - (position - uv_char_text_coord)).a)) * char_mask;
}

void main()
{
    vec2 position = get_2d_position(); 
    float text_opacity = 0.0;

     for (int i = 0; i < get_text_length(); i += 4) 
    {
        int character_index = (i / 4) + AS_SCREEN_OBJECT_DATA_OFFSET;
        uint encoded_value = ubo.custom_data[character_index];
        uint[4] decoded_chars = decode_chars(encoded_value);
        
        for (int j = 0; j < 4; j++)
        {
            text_opacity += get_char(position, decoded_chars[j]);
            position.x += FONT_CHAR_SPACING; 
        }
    }

    out_color = vec4(0.5, 0.3, 1.0, text_opacity);
    if (get_text_font_size() > 0)
    {
        out_color = vec4(1., 0.3, 1.0, text_opacity * 5.);
    }
}