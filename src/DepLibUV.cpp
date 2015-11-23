#define MS_CLASS "DepLibUV"

#include "DepLibUV.h"
#include "Logger.h"

/* Static variables. */

__thread uv_loop_t* DepLibUV::loop = nullptr;

/* Static methods. */

void DepLibUV::ClassInit()
{
	MS_TRACE();

	// Print libuv version.
	MS_DEBUG("loaded libuv version: %s", uv_version_string());
}

void DepLibUV::ThreadInit()
{
	MS_TRACE();

	int err;

	// This should never happen.
	if (DepLibUV::loop)
		MS_ABORT("DepLibUV::loop alread allocated in this thread");

	DepLibUV::loop = new uv_loop_t;
	err = uv_loop_init(DepLibUV::loop);
	if (err)
		MS_ABORT("uv_loop_init() failed: %s", uv_strerror(err));
}

void DepLibUV::ThreadDestroy()
{
	MS_TRACE();

	// This should never happen.
	if (!DepLibUV::loop)
		MS_ABORT("DepLibUV::loop was not allocated in this thread");

	uv_loop_close(DepLibUV::loop);
	delete DepLibUV::loop;
}

void DepLibUV::RunLoop()
{
	MS_TRACE();

	// This should never happen.
	if (!DepLibUV::loop)
		MS_ABORT("DepLibUV::loop was not allocated in this thread");

	uv_run(DepLibUV::loop, UV_RUN_DEFAULT);
}
