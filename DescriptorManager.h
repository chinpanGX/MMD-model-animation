/*-----------------------------------------------------------
	
	[DescriptorHandle.h]  [DescriptorManager.h]
	Author : èoçá„ƒëæ

-------------------------------------------------------------*/
#pragma once
#include<wrl.h>
#include<list>
#include"d3dx12.h"

class DescriptorHandle
{
private:
	D3D12_CPU_DESCRIPTOR_HANDLE m_CPU_handle;
	D3D12_GPU_DESCRIPTOR_HANDLE m_GPU_handle;
public:
	DescriptorHandle() : m_CPU_handle(), m_GPU_handle() {}
	DescriptorHandle(D3D12_CPU_DESCRIPTOR_HANDLE hCPU, D3D12_GPU_DESCRIPTOR_HANDLE hGPU) : m_CPU_handle(hCPU),m_GPU_handle(hGPU) {}
	~DescriptorHandle() {}
	operator D3D12_CPU_DESCRIPTOR_HANDLE() const { return m_CPU_handle; }
	operator D3D12_GPU_DESCRIPTOR_HANDLE() const { return m_GPU_handle; }
};

class DescriptorManager
{
private:
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
	ComPtr<ID3D12DescriptorHeap> m_Heap;
	CD3DX12_CPU_DESCRIPTOR_HANDLE m_CPU_handle;
	CD3DX12_GPU_DESCRIPTOR_HANDLE m_GPU_handle;
	UINT m_Index;
	UINT m_IncrementSize;
	std::list<DescriptorHandle> m_FreeList;

public:
	DescriptorManager(ComPtr<ID3D12Device> device, const D3D12_DESCRIPTOR_HEAP_DESC& desc);
	DescriptorHandle Alloc();
	void Free(const DescriptorHandle& handle);
	ComPtr<ID3D12DescriptorHeap> GetHeap() const { return m_Heap; }
};

