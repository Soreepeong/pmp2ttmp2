#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <cmath>
#include <iostream>
#include <ranges>

#include <Windows.h>
#include <PathCch.h>

#include <zlib.h>
#include <minizip/zip.h>
#include <minizip/unzip.h>
#include <minizip/iowin32.h>

#include <nlohmann/json.hpp>

#include "xivres/installation.h"
#include "xivres/packed_stream.model.h"
#include "xivres/packed_stream.standard.h"
#include "xivres/packed_stream.texture.h"
#include "xivres/textools.h"
#include "xivres/texture.h"
#include "xivres/unpacked_stream.h"
#include "xivres/util.pixel_formats.h"
#include "xivres/util.on_dtor.h"
#include "xivres/util.unicode.h"

extern HINSTANCE g_hInstance;
