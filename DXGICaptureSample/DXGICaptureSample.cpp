// DXGICaptureSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DXGIManager.h"
#include <windows.h>

DXGIManager g_DXGIManager;

int _tmain(int argc, _TCHAR* argv[])
{
	CoInitialize(NULL);

	g_DXGIManager.SetCaptureSource(CSMonitor1);

	RECT rcDim;
	g_DXGIManager.GetOutputRect(rcDim);
	DWORD dwWidth = rcDim.right - rcDim.left;
	DWORD dwHeight = rcDim.bottom - rcDim.top;
	DWORD dwBufSize = dwWidth*dwHeight*4;

	BYTE* pBuf = new BYTE[dwBufSize];
	HRESULT hr;
	
	int i=0;
	do
	{
		hr = g_DXGIManager.GetOutputBits(pBuf, rcDim);
		i++;
	}
	while (hr == DXGI_ERROR_WAIT_TIMEOUT || i < 2);

	if( FAILED(hr) )
	{
		printf("GetOutputBits failed with hr=0x%08x\n", hr);
		return hr;
	}
	UINT offset;
	for (int a = 1; a < 364; a = a + 4) {
		offset = a * 4;
			printf("\#%02x%02x%02x\n", pBuf[offset + 2], pBuf[offset + 1], pBuf[offset]);
	}
	
	delete[] pBuf;

	return 0;
}