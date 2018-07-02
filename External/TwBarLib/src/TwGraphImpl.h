//  ---------------------------------------------------------------------------
//
//  @file       TwDirect3D11.h
//  @brief      Direct3D11 graphic functions
//  @author     Philippe Decaudin
//  @license    This file is part of the AntTweakBar library.
//              For conditions of distribution and use, see License.txt
//
//  note:       Private header
//
//  ---------------------------------------------------------------------------


#if !defined ANT_TW_DIRECT3D11_INCLUDED
#define ANT_TW_DIRECT3D11_INCLUDED

#include "TwGraph.h"
#include "RefCntAutoPtr.h"
#include "DebugUtilities.h"

#include "RenderDevice.h"
#include "DeviceContext.h"

//  ---------------------------------------------------------------------------

class CTwGraphImpl : public ITwGraph
{
public:
    virtual int                 Init(int BackBufferFormat, int DepthStencilFormat);
    virtual int                 Shut();
    virtual void                BeginDraw(int _WndWidth, int _WndHeight);
    virtual void                EndDraw();
    virtual bool                IsDrawing();
    virtual void                Restore();
    virtual void                DrawLine(int _X0, int _Y0, int _X1, int _Y1, color32 _Color0, color32 _Color1, bool _AntiAliased=false);
    virtual void                DrawLine(int _X0, int _Y0, int _X1, int _Y1, color32 _Color, bool _AntiAliased=false) { DrawLine(_X0, _Y0, _X1, _Y1, _Color, _Color, _AntiAliased); }
    virtual void                DrawRect(int _X0, int _Y0, int _X1, int _Y1, color32 _Color00, color32 _Color10, color32 _Color01, color32 _Color11);
    virtual void                DrawRect(int _X0, int _Y0, int _X1, int _Y1, color32 _Color) { DrawRect(_X0, _Y0, _X1, _Y1, _Color, _Color, _Color, _Color); }
    virtual void                DrawTriangles(int _NumTriangles, int *_Vertices, color32 *_Colors, Cull _CullMode);

    virtual void *              NewTextObj();
    virtual void                DeleteTextObj(void *_TextObj);
    virtual void                BuildText(void *_TextObj, const std::string *_TextLines, color32 *_LineColors, color32 *_LineBgColors, int _NbLines, const CTexFont *_Font, int _Sep, int _BgWidth);
    virtual void                DrawText(void *_TextObj, int X, int Y, color32 _Color, color32 _BgColor);

    virtual void                ChangeViewport(int _X0, int _Y0, int _Width, int _Height, int _OffsetX, int _OffsetY);
    virtual void                RestoreViewport();
    virtual void                SetScissor(int _X0, int _Y0, int _Width, int _Height);

protected:
    Diligent::RefCntAutoPtr<Diligent::IRenderDevice> m_pDev;
    bool m_bIsGLDevice;
    Diligent::IDeviceContext* m_pDevImmContext;

    bool                        m_Drawing;
    const CTexFont *            m_FontTex;
    Diligent::RefCntAutoPtr<Diligent::ITexture>    m_pFontGPUTex;
    int                         m_WndWidth;
    int                         m_WndHeight;
    int                         m_OffsetX;
    int                         m_OffsetY;
    Diligent::Viewport                   m_ViewportInit;
    Diligent::Rect                       m_ViewportAndScissorRects[2];
    Diligent::Rect                       m_FullRect;

    struct CLineRectVtx
    {
        float                   m_Pos[3];
        color32                 m_Color;
    };
    struct CTextVtx
    {
        float                   m_Pos[3];
        color32                 m_Color;
        float                   m_UV[2];
    };
    struct CConstants
    {
        float                   m_Offset[4];
        float                   m_CstColor[4];
    };

    struct CTextObj
    {
        Diligent::RefCntAutoPtr<Diligent::IBuffer> m_pTextVertexBuffer;
        Diligent::RefCntAutoPtr<Diligent::IBuffer> m_pBgVertexBuffer;
        int                     m_NbTextVerts;
        int                     m_NbBgVerts;
        int                     m_TextVertexBufferSize;
        int                     m_BgVertexBufferSize;
        bool                    m_LineColors;
        bool                    m_LineBgColors;
    };

    enum class PSO_ID
    {
        Text = 0,
        TextCstColor,
        Line,
        LineAA,
        Triangle_CullNone,
        Triangle_CullCW,
        Triangle_CullCCW,
        Triangle_Multisample,
        Triangle_CstColor,
        NumIDs
    };
    Diligent::RefCntAutoPtr<Diligent::IPipelineState>  m_pPSO[static_cast<int>(PSO_ID::NumIDs)];
    Diligent::RefCntAutoPtr<Diligent::IShaderResourceBinding>  m_pTextSRB, m_pTextCstColorSRB;

    Diligent::RefCntAutoPtr<Diligent::IShader>     m_pLineRectVS;
    Diligent::RefCntAutoPtr<Diligent::IShader>     m_pLineRectCstColorVS;
    Diligent::RefCntAutoPtr<Diligent::IShader>     m_pLineRectPS;
    Diligent::RefCntAutoPtr<Diligent::IShader>     m_pTextVS;
    Diligent::RefCntAutoPtr<Diligent::IShader>     m_pTextCstColorVS;
    Diligent::RefCntAutoPtr<Diligent::IShader>     m_pTextPS;

    Diligent::RefCntAutoPtr<Diligent::IBuffer>     m_pLineVertexBuffer;
    Diligent::RefCntAutoPtr<Diligent::IBuffer>     m_pRectVertexBuffer;
    Diligent::RefCntAutoPtr<Diligent::IBuffer>     m_pTrianglesVertexBuffer;
    int                         m_TrianglesVertexBufferCount;
    Diligent::RefCntAutoPtr<Diligent::IBuffer>     m_pConstantBuffer;
    Diligent::RefCntAutoPtr<Diligent::IResourceMapping> m_pResourceMapping;
    Diligent::RefCntAutoPtr<Diligent::ISampler>    m_pSamplerState;

    std::vector<CLineRectVtx> m_mappedVertices;
    std::vector<CTextVtx> m_textVtxBuffer;
};

//  ---------------------------------------------------------------------------


#endif // !defined ANT_TW_DIRECT3D11_INCLUDED
