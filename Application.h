/*----------------------------------------------------------

	[Application.h]
	Author : 出合翔太

-----------------------------------------------------------*/
#pragma once
#include<Windows.h>
#include<tchar.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<DirectXMath.h>
#include<vector>
#include<map>
#include<d3dcompiler.h>
#include<DirectXTex.h>
#include"d3dx12.h"
#include<wrl.h>
#include<memory>

class DX12Wrapper;
class PMDRenderer;
class PMDActor;
class Application
{
private:
	//ウィンドウ周り
	WNDCLASSEX m_WindowClass;
	HWND m_hWnd;
	std::shared_ptr<DX12Wrapper> _dx12;
	std::shared_ptr<PMDRenderer> _pmdRenderer;
	std::shared_ptr<PMDActor> _pmdActor;
public:
	~Application() {};
	static Application& Instance(); // Applicationのシングルトンインスタンスを得る
	bool Init();
	void Run();
	void Uninit();

	// Getter
	SIZE GetWindowSize()const;
private:
	// シングルトンのためにコンストラクタをprivateにしてコピーと代入を禁止に
	Application() {} 
	Application(const Application&) = delete;
	void operator=(const Application&) = delete;
	
	void CreateGameWindow(HWND &hwnd, WNDCLASSEX &windowClass); //ゲーム用ウィンドウの生成
};

