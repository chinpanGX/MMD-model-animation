/*-------------------------------------------------------

	[DX12Wrapper.h]
	Author : 出合翔太

--------------------------------------------------------*/
#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<map>
#include<unordered_map>
#include<DirectXTex.h>
#include<wrl.h>
#include<string>
#include<functional>

class DX12Wrapper
{
private:
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
	SIZE m_Winsize;
	//DXGIまわり
	ComPtr < IDXGIFactory4> _dxgiFactory = nullptr;//DXGIインターフェイス
	ComPtr < IDXGISwapChain4> _swapchain = nullptr;//スワップチェイン
	//DirectX12まわり
	ComPtr< ID3D12Device> _dev = nullptr;//デバイス
	ComPtr < ID3D12CommandAllocator> _cmdAllocator = nullptr;//コマンドアロケータ
	ComPtr < ID3D12GraphicsCommandList> _cmdList = nullptr;//コマンドリスト
	ComPtr < ID3D12CommandQueue> _cmdQueue = nullptr;//コマンドキュー
	//表示に関わるバッファ周り
	ComPtr<ID3D12Resource> _depthBuffer = nullptr;//深度バッファ
	std::vector<ID3D12Resource*> _backBuffers;//バックバッファ(2つ以上…スワップチェインが確保)
	ComPtr<ID3D12DescriptorHeap> _rtvHeaps = nullptr;//レンダーターゲット用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> _dsvHeap = nullptr;//深度バッファビュー用デスクリプタヒープ
	std::unique_ptr<D3D12_VIEWPORT> _viewport;//ビューポート
	std::unique_ptr<D3D12_RECT> _scissorrect;//シザー矩形
	//シーンを構成するバッファまわり
	ComPtr<ID3D12Resource> _sceneConstBuff = nullptr;

	struct SceneData 
	{
		DirectX::XMMATRIX view;//ビュー行列
		DirectX::XMMATRIX proj;//プロジェクション行列
		DirectX::XMFLOAT3 eye;//視点座標
	};
	SceneData* _mappedSceneData;
	ComPtr<ID3D12DescriptorHeap> _sceneDescHeap = nullptr;

	//フェンス
	ComPtr<ID3D12Fence> _fence = nullptr;
	UINT64 _fenceVal = 0;

	//ロード用テーブル
	using LoadLambda_t = std::function<HRESULT(const std::wstring& path, DirectX::TexMetadata*, DirectX::ScratchImage&)>;
	std::map < std::string, LoadLambda_t> _loadLambdaTable;
	//テクスチャテーブル
	std::unordered_map<std::string, ComPtr<ID3D12Resource>> _textureTable;

public:
	DX12Wrapper(HWND hwnd);
	~DX12Wrapper() {}
	void Update() {}
	void BeginDraw();
	void EndDraw();
	// Getter/Setter
	///@param texpath テクスチャファイルパス
	ComPtr<ID3D12Resource> GetTextureByPath(const char* texpath); // テクスチャパスから必要なテクスチャバッファへのポインタを返す
	ComPtr< ID3D12Device> GetDevice() { return _dev; }						// デバイス
	ComPtr < ID3D12GraphicsCommandList> GetCommandList() { return _cmdList; }	// コマンドリスト
	ComPtr < IDXGISwapChain4> GetSwapchain(){ return _swapchain; } // スワップチェイン
	void SetScene();
private:
	HRESULT	CreateFinalRenderTargets();			// 最終的なレンダーターゲットの生成
	HRESULT CreateDepthStencilView();			// デプスステンシルビューの生成
	HRESULT CreateSwapChain(const HWND& hwnd);	// スワップチェインの生成
	HRESULT InitDXGIDevice();					// DXGIまわり初期化
	HRESULT InitCommand();						// コマンドまわり初期化
	HRESULT CreateSceneView();					// ビュープロジェクション用ビューの生成
	void CreateTextureLoaderTable();			// テクスチャローダテーブルの作成
	ID3D12Resource* CreateTextureFromFile(const char* texpath); //テクスチャ名からテクスチャバッファ作成、中身をコピー
};

