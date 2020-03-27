/*-----------------------------------------------------------

	[DescriptorManager.h]
	Author : èoçá„ƒëæ

-------------------------------------------------------------*/
#include "DescriptorManager.h"

DescriptorManager::DescriptorManager(ComPtr<ID3D12Device> device, const D3D12_DESCRIPTOR_HEAP_DESC & desc) : m_Index(0),m_IncrementSize(0)
{
	HRESULT result = device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_Heap));
	m_CPU_handle = m_Heap->GetCPUDescriptorHandleForHeapStart();
	m_GPU_handle = m_Heap->GetGPUDescriptorHandleForHeapStart();
	m_IncrementSize = device->GetDescriptorHandleIncrementSize(desc.Type);
}

DescriptorHandle DescriptorManager::Alloc()
{
	if (!m_FreeList.empty())
	{
		auto ret = m_FreeList.front();
		m_FreeList;
	}
	
}

void DescriptorManager::Free(const DescriptorHandle & handle)
{
}
