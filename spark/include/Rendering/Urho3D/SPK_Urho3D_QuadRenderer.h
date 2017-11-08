#ifndef H_SPK_URHO3D_QUADRENDERER
#define H_SPK_URHO3D_QUADRENDERER

#include "Rendering/Urho3D/SPK_Urho3D_Renderer.h"
#include "Extensions/Renderers/SPK_QuadRenderBehavior.h"
#include "Extensions/Renderers/SPK_Oriented3DRenderBehavior.h"

#include <Urho3D/Core/Context.h>

namespace SPK {
namespace URHO {

class SPK_URHO_PREFIX IUrho3DQuadRenderer :
        public IUrho3DRenderer,
        public QuadRenderBehavior,
        public Oriented3DRenderBehavior
{
    SPK_IMPLEMENT_OBJECT(IUrho3DQuadRenderer)

    SPK_START_DESCRIPTION
    SPK_PARENT_ATTRIBUTES(Renderer)
    SPK_ATTRIBUTE("material",ATTRIBUTE_TYPE_STRING)
    SPK_ATTRIBUTE("texture",ATTRIBUTE_TYPE_STRING)
    SPK_ATTRIBUTE("scale",ATTRIBUTE_TYPE_FLOATS)
    SPK_END_DESCRIPTION

public:

    static Ref<IUrho3DQuadRenderer> create(Urho3D::Context* context, float scaleX = 1.0f,float scaleY = 1.0f);


protected:
    virtual void innerImport(const IO::Descriptor& descriptor);
    virtual void innerExport(IO::Descriptor& descriptor) const;

private:

    static const size_t NB_INDICES_PER_PARTICLE = 6;
    static const size_t NB_VERTICES_PER_PARTICLE = 4;
    mutable float _u0, _u1, _v0, _v1;
    PODVector<VertexElement> _elements;

    IUrho3DQuadRenderer(Urho3D::Context* context = nullptr, float scaleX = 1.0f,float scaleY = 1.0f);
    IUrho3DQuadRenderer(const IUrho3DQuadRenderer& renderer);

    virtual RenderBuffer* attachRenderBuffer(const Group& group) const override;
    virtual void render(const Group& group,const DataSet* dataSet,RenderBuffer* renderBuffer) const override;
    virtual void computeAABB(Vector3D& AABBMin,Vector3D& AABBMax,const Group& group,const DataSet* dataSet) const override;

    mutable void (IUrho3DQuadRenderer::*renderParticle)(const Particle&, IUrho3DBuffer& renderBuffer) const;	// pointer to the right render method

    void renderBasic(const Particle& particle,IUrho3DBuffer& renderBuffer) const;		// Rendering for particles with texture or no texture
    void renderRot(const Particle& particle,IUrho3DBuffer& renderBuffer) const;         // Rendering for particles with texture or no texture and rotation
    void renderAtlas(const Particle& particle,IUrho3DBuffer& renderBuffer) const;		// Rendering for particles with texture atlas
    void renderAtlasRot(const Particle& particle,IUrho3DBuffer& renderBuffer) const;	// Rendering for particles with texture atlas and rotation
};


inline Ref<IUrho3DQuadRenderer> IUrho3DQuadRenderer::create(Urho3D::Context* context, float scaleX, float scaleY)
{
    return SPK_NEW(IUrho3DQuadRenderer, context, scaleX, scaleY);
}


}}

#endif
