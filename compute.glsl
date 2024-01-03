#version 430 core
layout (local_size_x = 32, local_size_y = 32, local_size_z = 1) in;

layout(rgba32f, binding = 0) uniform image2D imgOutput;

void main() {
    ivec2 tID = ivec2(gl_GlobalInvocationID.xy);
    vec3 res;

    if ((gl_WorkGroupID.x % 2 == 0 && gl_WorkGroupID.y % 2 != 0) || (gl_WorkGroupID.x % 2 != 0 && gl_WorkGroupID.y % 2 == 0))
    {
        res = res + vec3(0.0);
    } else
    {
        res = res + vec3(1.0);
    }
    
    if (distance(vec2(tID), vec2(1280 / 2, 768 / 2)) < 200.0)
    {
        vec3 currentValue = vec3(imageLoad(imgOutput, tID));
        currentValue += vec3(0.001);
        res = clamp(res + currentValue, 0.0, 1.0);
    }


    imageStore(imgOutput, tID, vec4(res,1.0));
}