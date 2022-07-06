
#pragma once

#include <stdint.h>
#include <atomic>
#include <vector>
#include "DeckLinkAPI_h.h"

class StereoVideoFrame : public IDeckLinkVideoFrame, public IDeckLinkVideoFrame3DExtensions
{
private:
	long							m_width;
	long							m_height;
	BMDFrameFlags					m_flags;
	std::vector<uint8_t>			m_pixelBuffer;
	com_ptr<IDeckLinkVideoFrame>	m_rightEyeFrame;
	std::atomic<ULONG>				m_refCount;

public:
	StereoVideoFrame(long width, long height, BMDFrameFlags flags);
	virtual ~StereoVideoFrame() {};

	// IDeckLinkVideoFrame interface
	virtual long			STDMETHODCALLTYPE	GetWidth(void) { return m_width; };
	virtual long			STDMETHODCALLTYPE	GetHeight(void) { return m_height; };
	virtual long			STDMETHODCALLTYPE	GetRowBytes(void) { return m_width * 2; };
	virtual HRESULT			STDMETHODCALLTYPE	GetBytes(void** buffer);
	virtual BMDFrameFlags	STDMETHODCALLTYPE	GetFlags(void) { return m_flags; };
	virtual BMDPixelFormat	STDMETHODCALLTYPE	GetPixelFormat(void) { return bmdFormat10BitYUV; };

	// IDeckLinkVideoFrame3DExtensions interface
	virtual BMDVideo3DPackingFormat STDMETHODCALLTYPE Get3DPackingFormat(void) { return bmdVideo3DPackingLeftOnly; };
	virtual HRESULT STDMETHODCALLTYPE GetFrameForRightEye(IDeckLinkVideoFrame** rightEyeFrame) { rightEyeFrame = (IDeckLinkVideoFrame**)&m_rightEyeFrame; return S_OK; };
	virtual HRESULT STDMETHODCALLTYPE SetFrameForRightEye(const com_ptr<IDeckLinkVideoFrame> &rightEyeFrame) { m_rightEyeFrame = rightEyeFrame; return S_OK; };

	// Dummy implementations of remaining methods in IDeckLinkVideoFrame
	virtual HRESULT			STDMETHODCALLTYPE	GetAncillaryData(IDeckLinkVideoFrameAncillary** ancillary) { return E_NOTIMPL; };
	virtual HRESULT			STDMETHODCALLTYPE	GetTimecode(BMDTimecodeFormat format, IDeckLinkTimecode** timecode) { return E_NOTIMPL; };

	// IUnknown interface
	virtual HRESULT			STDMETHODCALLTYPE	QueryInterface(REFIID iid, LPVOID* ppv);
	virtual ULONG			STDMETHODCALLTYPE	AddRef();
	virtual ULONG			STDMETHODCALLTYPE	Release();
};

#pragma once
