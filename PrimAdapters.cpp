#include "PrimAdapters.h"

#include "pxr/usdImaging/usdImaging/indexProxy.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
	TF_DEBUG(USDIMAGING_PLUGINS).Msg("MyCustomAdapter::Register \n");

	typedef MyCustomAdapter Adapter;
	TfType t = TfType::Define<Adapter, TfType::Bases<Adapter::BaseAdapter> >();
	t.SetFactory< UsdImagingPrimAdapterFactory<Adapter> >();
}

SdfPath MyCustomAdapter::Populate(const UsdPrim& prim, UsdImagingIndexProxy* index, UsdImagingInstancerContext const* instancerContext)
{
	TF_DEBUG(USDIMAGING_PLUGINS).Msg("MyCustomAdapter::Populate \n");

	return _AddRprim(_tokens->MyCustomToken, prim, index, GetMaterialUsdPath(prim), instancerContext);
}

bool MyCustomAdapter::IsSupported(UsdImagingIndexProxy const* index) const
{
	TF_DEBUG(USDIMAGING_PLUGINS).Msg("MyCustomAdapter::IsSupported \n");

	if (index->IsRprimTypeSupported(_tokens->MyCustomToken))
		return true;

	return UsdImagingGprimAdapter::IsSupported(index);
}

TfTokenVector MyCustomAdapter::GetImagingSubprims(UsdPrim const& prim)
{
	TF_DEBUG(USDIMAGING_PLUGINS).Msg("MyCustomAdapter::GetImagingSubprims \n");

	return { TfToken() };
}

TfToken MyCustomAdapter::GetImagingSubprimType(UsdPrim const& prim, TfToken const& subprim)
{
	TF_DEBUG(USDIMAGING_PLUGINS).Msg("MyCustomAdapter::GetImagingSubprimType \n");

	if (subprim.IsEmpty()) {
		return _tokens->MyCustomToken;
	}

	return TfToken();
}



HdDirtyBits UsdMyCustomPrim::GetInitialDirtyBitsMask() const
{
	return HdField::AllDirty;
}

void UsdMyCustomPrim::Sync(HdSceneDelegate* delegate, HdRenderParam* renderParam, HdDirtyBits* dirtyBits, TfToken const& reprToken)
{
}

void UsdMyCustomPrim::Finalize(HdRenderParam* renderParam)
{
}

TfTokenVector const& UsdMyCustomPrim::GetBuiltinPrimvarNames() const
{
	static const TfTokenVector tempVector;
	return tempVector;
}

HdDirtyBits UsdMyCustomPrim::_PropagateDirtyBits(HdDirtyBits bits) const
{
	return bits;
}

void UsdMyCustomPrim::_InitRepr(TfToken const& reprToken, HdDirtyBits* dirtyBits)
{
	TF_UNUSED(dirtyBits);
	TF_UNUSED(reprToken);
}









PXR_NAMESPACE_CLOSE_SCOPE