//*********************************************************
// www.Ultimategameprogramming.com
// Dot3 Specular Bump Mapping shader demo.
// Created by the Programming Ace.
//
// Uniform Variables:
//   worldViewProj   - Holds the model view projection matrix.
//   worldView       - Holds the model view matrix.
//   lightPos        - Holds object space light position.
//   decal           - Holds the texture.
//   bump            - Holds bump map texture.
//
//*********************************************************


// Uniform parameters.
float4x4 worldViewProj  : WorldViewProjection;
float4x4 worldView      : WorldView;

float3 lightPos;

texture decal;
texture bump;

// This sampler struct is used to specifiy texture options.
sampler DecalSampler = sampler_state
{
    Texture   = (decal);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

sampler BumpSampler = sampler_state
{
    Texture   = (bump);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};


// Vertex shader input.
struct VS_Input
{
   float3 vertexPos  : POSITION;
   float3 normal     : NORMAL;
   float2 texture0   : TEXCOORD0;
   float3 sTangent   : TANGENT;
   float3 binormal   : BINORMAL;
};


// Vertex shader output.
struct Vs_Output
{
   float4 vertexPos  : POSITION;
   float2 texture0   : TEXCOORD0;
   float3 lightDirection : TEXCOORD1;
};


// Pixel shader output.
struct Ps_Output
{
	float4 color      : COLOR;
};


// The vertex shader...
Vs_Output VertexShaderEffect(VS_Input IN)
{
   Vs_Output vs_out;

   // Set output vertex pos, and texture coords.
   vs_out.vertexPos = mul(worldViewProj, float4(IN.vertexPos, 1));
   vs_out.texture0 = IN.texture0;
   
   // Set the object space light direction.
   vs_out.lightDirection = lightPos - IN.vertexPos;
   
   // Build TBN matrix.
   float3x3 tbnMatrix;
   tbnMatrix[0] = mul(IN.sTangent, worldView);
   tbnMatrix[1] = mul(IN.binormal, worldView);
   tbnMatrix[2] = mul(IN.normal, worldView);
   
   // Convert light direction to texture space.
   vs_out.lightDirection = mul(tbnMatrix, vs_out.lightDirection);
   
   return vs_out;
}


// The pixel shader...
Ps_Output PixelShaderEffect(Vs_Output IN)
{
   Ps_Output ps_out;
   
   float4 decalCol = tex2D(DecalSampler, IN.texture0);
   float4 bumpCol = tex2D(BumpSampler, IN.texture0);
   
   // Expand normal.
   bumpCol = (bumpCol - 0.5f) * 2;
   
   // Normalize the light direction on a per pixel level.
   float3 lightDirection = normalize(IN.lightDirection);
   
   // Calculate the half angle using a hardcoded camera position.
   float3 cameraPos = float3(0, 0, -2.5);
   cameraPos = normalize(cameraPos);
   float3 halfAngle = lightDirection + cameraPos;
   halfAngle = normalize(halfAngle);

   // Calculate the bump value as n dot l.  Light direction in texture
   // space will have a z value above 0 if the light source is not behind
   // this surface.  This allows us to take into account geometric self shadowing.
   // Do the same with the specular value.
   float diffuse = lightDirection.z > 0 ? saturate(dot(bumpCol, lightDirection)) : 0;
   float specular = diffuse > 0 && lightDirection.z > 0 ?
                    saturate(pow(dot(bumpCol, halfAngle), 128)) : 0;
   
   // To make things simple I hardcoded material values but we could have passed
   // these as uniform parameters.
   float3 diffuseMat = float3(0.8f, 0.8f, 0.8f);
   float3 specularMat = float3(0.6f, 0.6f, 0.6f);
   float ambient = 0.4f;
   
   // Combine the decal with the bump value.
   ps_out.color = decalCol * float4((diffuseMat * (ambient + diffuse) +
                              specularMat * specular), 1);

   return ps_out;
}


// Effect...
technique SpecularBumpMapping
{
   pass Pass0
   {
      // Here we will compile and set the vertex and pixel shader.
      VertexShader = compile vs_2_0 VertexShaderEffect();
      PixelShader  = compile ps_2_0 PixelShaderEffect();
   }
}