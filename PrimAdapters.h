#pragma once

#include <pxr/pxr.h>
#include <pxr/usdImaging/usdImaging/gprimAdapter.h>
#include <pxr/imaging/hd/rprim.h>
#include <pxr/imaging/hd/field.h>
#include <pxr/base/tf/debug.h>


PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PRIVATE_TOKENS(
	_tokens,
	(MyCustomToken)
);

class MyCustomAdapter : public UsdImagingGprimAdapter
{
public:
	typedef UsdImagingGprimAdapter BaseAdapter;

	MyCustomAdapter() : UsdImagingGprimAdapter()
	{
	}

	SdfPath Populate(const UsdPrim& prim, UsdImagingIndexProxy* index, UsdImagingInstancerContext const* instancerContext = nullptr) override;

	bool IsSupported(UsdImagingIndexProxy const* index) const override;

	TfTokenVector GetImagingSubprims(UsdPrim const& prim) override;

	TfToken GetImagingSubprimType(UsdPrim const& prim, TfToken const& subprim) override;
};

class UsdMyCustomPrim : public HdRprim
{
public:

	UsdMyCustomPrim(SdfPath const& sprimId) : HdRprim(sprimId) {};

	HdDirtyBits GetInitialDirtyBitsMask() const override;

	void Sync(HdSceneDelegate* delegate, HdRenderParam* renderParam, HdDirtyBits* dirtyBits, TfToken const& reprToken) override;

	void Finalize(HdRenderParam* renderParam) override;

	TfTokenVector const& GetBuiltinPrimvarNames() const override;

	HdDirtyBits _PropagateDirtyBits(HdDirtyBits bits) const override;

	void _InitRepr(TfToken const& reprToken, HdDirtyBits* dirtyBits) override;
};


PXR_NAMESPACE_CLOSE_SCOPE