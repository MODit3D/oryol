#pragma once
//------------------------------------------------------------------------------
/**
    @class Oryol::_priv::debugTextRenderer
    @ingroup _priv
    @brief minimalistic 7-bit-ASCII text renderer
*/
#include "Core/Types.h"
#include "Resource/Id.h"
#include "Resource/ResourceLabel.h"
#include "Core/String/StringBuilder.h"
#include "Core/Threading/RWLock.h"
#include "Gfx/Core/VertexLayout.h"
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"
#include <cstdarg>

namespace Oryol {
namespace _priv {

class debugTextRenderer {
public:
    /// constructor
    debugTextRenderer();
    /// destructor
    ~debugTextRenderer();

    /// discard the text renderer
    void discard();
    /// return true if the object has been setup
    bool isValid() const;
    
    /// set global text scale
    void setTextScale(const glm::vec2& s);
    /// get global text scale
    const glm::vec2& getTextScale() const;
    
    /// draw text (only adds to internal buffer)
    void print(const char* text);
    /// draw text (only adds to internal buffer)
    void printf(const char* text, std::va_list args);
    /// reposition the cursor
    void cursorPos(uint8 x, uint8 y);
    /// change text color
    void textColor(const glm::vec4& color);
    /// draw the accumulated text
    void drawTextBuffer();
    
private:
    /// setup the text renderer (will be called as needed)
    void setup();

    /// setup the font texture
    void setupFontTexture();
    /// setup the text dynamic mesh
    void setupTextMesh();
    /// setup the text draw state
    void  setupTextDrawState();
    /// convert the provides string object into vertices, and return number of vertices
    int32 convertStringToVertices(const String& str);
    /// write one glyph vertex, returns next vertex index
    int32 writeVertex(int32 vertexIndex, uint8 x, uint8 y, uint8 u, uint8 v, uint32 rgba);
    
    static const int32 MaxNumColumns = 120;
    static const int32 MaxNumLines = 80;
    static const int32 MaxNumChars = MaxNumColumns * MaxNumLines;
    static const int32 MaxNumVertices = MaxNumChars * 6;
    
    glm::vec2 textScale;
    VertexLayout vertexLayout;
    RWLock rwLock;
    Id textShader;
    Id fontTextureBundle;
    Id textMesh;
    Id textDrawState;
    StringBuilder stringBuilder;
    bool valid;
    ResourceLabel resourceLabel;
    
    struct Vertex {
        float x, y, u, v;
        uint32 color;
    };
    struct Vertex vertexData[MaxNumVertices];
};

} // namespace _priv
} // namespace Oryol
