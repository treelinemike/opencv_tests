#include "platform.h"
#include "StereoVideoFrame.h"

/* StereoVideoFrame class */

// Constructor generates empty pixel buffer
StereoVideoFrame::StereoVideoFrame(long width, long height, BMDFrameFlags flags) :
	m_width(width), m_height(height), m_flags(flags), m_refCount(1)
{
	// Allocate pixel buffer
	m_pixelBuffer.resize(m_width * m_height * 2);
}

HRESULT StereoVideoFrame::GetBytes(void** buffer)
{
	*buffer = (void*)m_pixelBuffer.data();
	return S_OK;
}

HRESULT	STDMETHODCALLTYPE StereoVideoFrame::QueryInterface(REFIID iid, LPVOID* ppv)
{
	HRESULT result = E_NOINTERFACE;

	if (ppv == NULL)
		return E_INVALIDARG;

	// Initialise the return result
	*ppv = NULL;

	// Obtain the IUnknown interface and compare it the provided REFIID
	if (iid == IID_IUnknown)
	{
		*ppv = this;
		AddRef();
		result = S_OK;
	}

	else if (iid == IID_IDeckLinkVideoFrame)
	{
		*ppv = (IDeckLinkVideoFrame*)this;
		AddRef();
		result = S_OK;
	}
	else if (iid == IID_IDeckLinkVideoFrame3DExtensions) {
		*ppv = (IDeckLinkVideoFrame3DExtensions*)this;
		AddRef();
		result = S_OK;
	}

	return result;
}

ULONG STDMETHODCALLTYPE StereoVideoFrame::AddRef(void)
{
	return ++m_refCount;
}

ULONG STDMETHODCALLTYPE StereoVideoFrame::Release(void)
{

	ULONG newRefValue = --m_refCount;
	if (newRefValue == 0)
		delete this;

	return newRefValue;
}
