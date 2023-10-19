#pragma once

#include <raylib.h>

namespace LAYOUT
{
	constexpr Vector2 SCREEN_SIZE = Vector2( 1470.f, 870.f );

	// Topbar
	namespace TOPBAR
	{
		constexpr Vector2 IMPORT_SIZE  = { 50.f, 50.f };
		constexpr Vector2 IMPORT_POS   = { 20.f, 20.f };
		constexpr Vector2 EXPORT_SIZE  = { 50.f, 50.f };
		constexpr Vector2 EXPORT_POS   = { 90.f, 20.f };
		constexpr Vector2 SEARCH_SIZE  = { 1070.f, 50.f };
		constexpr Vector2 SEARCH_POS   = { 160.f, 20.f };
		constexpr Vector2 PACKAGE_SIZE = { 200.f, 50.f };
		constexpr Vector2 PACKAGE_POS  = { 1250.f, 20.f };
	}

	// Assetgrid
	constexpr Vector2 ASSETGRID_SIZE = { 1210.f, 760.f };
	constexpr Vector2 ASSETGRID_POS  = { 20.f, 90.f };

	// Assetdetail
	namespace ASSETDETAIL
	{
		constexpr Vector2 SIZE                 = { 200.f, 760.f };
		constexpr Vector2 POS                  = { 1250.f, 90.f };
		constexpr Vector2 ASSET_ICON_SIZE      = { 110.f, 165.f };
		constexpr Vector2 ASSET_ICON_POS       = { 1295.f, 110.f };
		constexpr Vector2 ASSET_NAME_SIZE      = { 160.f, 0.f };
		constexpr Vector2 ASSET_NAME_POS       = { 1270.f, 295.f };
	}
}
