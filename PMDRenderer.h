/*-------------------------------------------------------
	
	[PMDRenderer.h]
	Author : 出合翔太

--------------------------------------------------------*/
#pragma once
#include<d3d12.h>
#include<vector>
#include<wrl.h>
#include<memory>

class DX12Wrapper;
class PMDActor;
class PMDRenderer
{
	friend PMDActor;
private:
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	DX12Wrapper& _dx12;
	ComPtr< ID3D12PipelineState> _pipeline = nullptr;//PMD用パイプライン
	ComPtr< ID3D12RootSignature> _rootSignature = nullptr;//PMD用ルートシグネチャ

	//PMD用共通テクスチャ(白、黒、グレイスケールグラデーション)
	ComPtr<ID3D12Resource> _whiteTex = nullptr;
	ComPtr<ID3D12Resource> _blackTex = nullptr;
	ComPtr<ID3D12Resource> _gradTex = nullptr;

public:
	PMDRenderer(DX12Wrapper& dx12);
	~PMDRenderer() {}
	void Update() {}
	void Draw() {}
	ID3D12PipelineState* GetPipelineState() const { return _pipeline.Get(); }
	ID3D12RootSignature* GetRootSignature() const { return _rootSignature.Get(); };
private:
	ID3D12Resource* CreateDefaultTexture(size_t width, size_t height);
	ID3D12Resource* CreateWhiteTexture();//白テクスチャの生成
	ID3D12Resource*	CreateBlackTexture();//黒テクスチャの生成
	ID3D12Resource*	CreateGrayGradationTexture();//グレーテクスチャの生成

	//パイプライン初期化
	HRESULT CreateGraphicsPipelineForPMD();
	//ルートシグネチャ初期化
	HRESULT CreateRootSignature();

	bool CheckShaderCompileResult(HRESULT result, ID3DBlob* error = nullptr);
};

