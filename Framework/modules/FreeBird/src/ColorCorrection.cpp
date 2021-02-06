#include "ColorCorrection.h"

namespace freebird
{
    
    void ColorCorrection::Init(unsigned width, unsigned height)
    {
        int index = int(_buffers.size());
        _buffers.push_back(new Framebuffer());
        _buffers[index]->AddColorTarget(GL_RGBA8);
        _buffers[index]->AddDepthTarget();
        _buffers[index]->Init(width, height);

        //Set up shaders
        index = int(_shaders.size());
        _shaders.push_back(Shader::Create());
        _shaders[index]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
        _shaders[index]->LoadShaderPartFromFile("shaders/Post/color_correction_frag.glsl", GL_FRAGMENT_SHADER);
        _shaders[index]->Link();

        //Loads the LUT
        colorEffectCube.loadFromFile(cubeName);

        PostEffect::Init(width, height);
    }
   
    void ColorCorrection::ApplyEffect(PostEffect* buffer)
    {
        BindShader(0);

        //Bind previous framebuffer to the texutre as a color
        buffer->BindColorAsTexture(0, 0, 0);
        colorEffectCube.bind(30);
        
        //Render buffer as full screen quad
        _buffers[0]->RenderToFSQ();

        colorEffectCube.unbind(30);

        buffer->UnbindTexture(0);

        UnbindShader();
    }

    //Getters
    std::string ColorCorrection::GetCubeName()
    {
        return cubeName;
    }

    //Setters
    void ColorCorrection::SetCubeName(std::string name)
    {
        cubeName = name;
    }
}