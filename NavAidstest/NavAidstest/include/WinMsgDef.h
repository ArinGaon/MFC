#pragma once

#include <WinUser.h>
#include "DataTypeDef.h"

namespace NS_SALUS_MS_APP
{
	static const UINT g_unWM_REQUEST_RENDER_PRIMARY = static_cast<UINT>(WM_USER) + 3000U;
	static const UINT g_unWM_REQUEST_RENDER_SECONDARY = static_cast<UINT>(WM_USER) + 3001U;
	static const UINT g_unWM_CHANGE_SCOPE_CENTER = static_cast<UINT>(WM_USER) + 3002U;
	static const UINT g_unWM_CHANGE_SCOPE_RANGE = static_cast<UINT>(WM_USER) + 3003U;
	static const UINT g_unWM_CHANGE_SCOPE_RING_VIEW = static_cast<UINT>(WM_USER) + 3004U;
	static const UINT g_unWM_UPDATE_TRACK_DATA = static_cast<UINT>(WM_USER) + 3020U;
	static const UINT g_unWM_UPDATE_VIRTUAL_TRACK = static_cast<UINT>(WM_USER) + 3021U;
	static const UINT g_unWM_UPDATE_GUARD_ZONE = static_cast<UINT>(WM_USER) + 3022U;
	static const UINT g_unWM_UPDATE_USER_MAP = static_cast<UINT>(WM_USER) + 3023U;
	static const UINT g_unWM_UPDATE_AREA_MASK = static_cast<UINT>(WM_USER) + 3024U;
	static const UINT g_unWM_UPDATE_EBL_LINE = static_cast<UINT>(WM_USER) + 3025U;

	static const UINT g_unWM_CHANGE_COLOR_CONFIG = static_cast<UINT>(WM_USER) + 3100U;
	static const UINT g_unWM_CHANGE_DISPLAY_CONFIG = static_cast<UINT>(WM_USER) + 3101U;
	static const UINT g_unWM_CHANGE_SCOPE_VIEW_PARAM = static_cast<UINT>(WM_USER) + 3102U;
	static const UINT g_unWM_UPDATE_DATA_CONFIG = static_cast<UINT>(WM_USER) + 3103U;
	static const UINT g_unWM_UPDATE_DATA_SAVE = static_cast<UINT>(WM_USER) + 3104U;

	static const UINT g_unWM_START_OVERLAY_EDIT_ON_SCREEN = static_cast<UINT>(WM_USER) + 4000U;
	static const UINT g_unWM_CHANGED_EDITING_OVERLAY = static_cast<UINT>(WM_USER) + 4001U;
	static const UINT g_unWM_START_VIRTUAL_TRACK_ON_SCREEN = static_cast<UINT>(WM_USER) + 4002U;
	static const UINT g_unWM_UPDAE_GUARDZONE_POS = static_cast<UINT>(WM_USER) + 4003U;
	static const UINT g_unWM_UPDAE_USERMAP_POS = static_cast<UINT>(WM_USER) + 4004U;

	// report window message ID
	static const UINT g_unWM_CHANGED_ENV_CONFIG = static_cast<UINT>(WM_USER) + 5000U;
	static const UINT g_unWM_NOTIFY_ALARM = static_cast<UINT>(WM_USER) + 5010U;

	static const UINT g_unWM_SHOW_TRACK_REPORT_WND = static_cast<UINT>(WM_USER) + 5020U;

	// update info
	static const UINT g_unWM_UPDATE_DIALOG_INFO = static_cast<UINT>(WM_USER) + 6000U;
	static const UINT g_unWM_UPDATE_VTPOS_INFO = static_cast<UINT>(WM_USER) + 6001U;

	// update info AIS/GPS Com
	static const UINT g_unWM_NOTIFY_AIS_UPDATE_COM = static_cast<UINT>(WM_USER) + 7000U;
	static const UINT g_unWM_NOTIFY_GPS_UPDATE_COM = static_cast<UINT>(WM_USER) + 7100U;

	//Update Alarm CPA/TCPA Value
	static const UINT g_unWM_NOTIFY_ALARM_UPDATE_CPATCPA = static_cast<UINT>(WM_USER) + 7200U;
	static const UINT g_unWM_NOTIFY_CPACONTROL_UPDATE_CPATCPA = static_cast<UINT>(WM_USER) + 7300U;
	static const UINT g_unWM_NOTIFY_CPACONTROL_UPDATE_CPATCPA_END = static_cast<UINT>(WM_USER) + 7400U;
	static const UINT g_unWM_NOTIFY_UNIT_CHANGE_UPDATE = static_cast<UINT>(WM_USER) + 7500U;

	static const UINT g_unWM_NOTIFY_SUB_SCOPE_SELECT = static_cast<UINT>(WM_USER) + 7501U;
	static const UINT g_unWM_NOTIFY_SUB_SCOPE_UNSELECT = static_cast<UINT>(WM_USER) + 7502U;

	//SIMRAD IMAGE PARAMETER UPDATE
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SCANPWR = static_cast<UINT>(WM_USER) +             8000U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_TRANSMIT = static_cast<UINT>(WM_USER) +            8001U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_USEMODE = static_cast<UINT>(WM_USER) +             8002U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_RPM = static_cast<UINT>(WM_USER) +                 8003U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_FASTSCAN = static_cast<UINT>(WM_USER) +            8004U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_BEAMSHARP = static_cast<UINT>(WM_USER) +           8005U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_IRLEVEL = static_cast<UINT>(WM_USER) +             8006U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_LOCALIR = static_cast<UINT>(WM_USER) +             8007U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_TARGETBOOST = static_cast<UINT>(WM_USER) +         8008U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_TARGETSTRETCH = static_cast<UINT>(WM_USER) +       8009U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_TARGETLEGACY = static_cast<UINT>(WM_USER) +        8010U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_CURVETYPE = static_cast<UINT>(WM_USER) +           8011U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_GAIN = static_cast<UINT>(WM_USER) +		         8012U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_RAIN = static_cast<UINT>(WM_USER) +		         8013U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_NOISEREJECT = static_cast<UINT>(WM_USER) +         8014U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_FTC = static_cast<UINT>(WM_USER) +		         8015U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_GAINMODE = static_cast<UINT>(WM_USER) +	         8016U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SEALEGACY = static_cast<UINT>(WM_USER) +           8017U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SEALEGACYMODE = static_cast<UINT>(WM_USER) +       8018U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SEA = static_cast<UINT>(WM_USER) +		         8019U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SEAMODE = static_cast<UINT>(WM_USER) +	         8020U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SEAAUTOOFFSET = static_cast<UINT>(WM_USER) +       8021U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SEACOMBINED = static_cast<UINT>(WM_USER) +         8022U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SIDELOBE = static_cast<UINT>(WM_USER) +	         8023U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SIDELOBEMODE = static_cast<UINT>(WM_USER) +        8024U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_TRANSMITPERIOD = static_cast<UINT>(WM_USER) +      8025U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_STANDBYPERIOD = static_cast<UINT>(WM_USER) +       8026U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_TIMETRANSMITENABLED = static_cast<UINT>(WM_USER) + 8027U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_VIDEOAPERTURE = static_cast<UINT>(WM_USER) +       8028U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_USERMINSNR = static_cast<UINT>(WM_USER) +          8029U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_BANGSUPPRESSION = static_cast<UINT>(WM_USER) +     8030U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_STCRANGETRIM = static_cast<UINT>(WM_USER) +        8031U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_STCRANGERATE = static_cast<UINT>(WM_USER) +        8032U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_STCSEATRIM = static_cast<UINT>(WM_USER) +          8033U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_STCSEARATE1 = static_cast<UINT>(WM_USER) +         8034U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_STCSEARATE2 = static_cast<UINT>(WM_USER) +         8035U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_STCRAINTRIM = static_cast<UINT>(WM_USER) +         8036U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_STCRAINRATE = static_cast<UINT>(WM_USER) +         8037U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SETALLVALUE = static_cast<UINT>(WM_USER) +         8038U;

	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SECTOR0ENABLED = static_cast<UINT>(WM_USER) + 8114U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SECTOR1ENABLED = static_cast<UINT>(WM_USER) + 8115U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SECTOR2ENABLED = static_cast<UINT>(WM_USER) + 8116U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SECTOR3ENABLED = static_cast<UINT>(WM_USER) + 8117U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SECTOR4ENABLED = static_cast<UINT>(WM_USER) + 8118U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SECTOR5ENABLED = static_cast<UINT>(WM_USER) + 8119U;

	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SECTOR0START = static_cast<UINT>(WM_USER) + 8220U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SECTOR1START = static_cast<UINT>(WM_USER) + 8221U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SECTOR2START = static_cast<UINT>(WM_USER) + 8222U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SECTOR3START = static_cast<UINT>(WM_USER) + 8223U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SECTOR4START = static_cast<UINT>(WM_USER) + 8224U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SECTOR5START = static_cast<UINT>(WM_USER) + 8225U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SECTOR0END = static_cast<UINT>(WM_USER) +   8226U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SECTOR1END = static_cast<UINT>(WM_USER) +   8227U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SECTOR2END = static_cast<UINT>(WM_USER) +   8228U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SECTOR3END = static_cast<UINT>(WM_USER) +   8229U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SECTOR4END = static_cast<UINT>(WM_USER) +   8230U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_SECTOR5END = static_cast<UINT>(WM_USER) +   8231U;

	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_PARKPOS = static_cast<UINT>(WM_USER) +           8332U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_ANTHEIGHT = static_cast<UINT>(WM_USER) +         8333U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_ANTXOFFSET = static_cast<UINT>(WM_USER) +        8334U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_ANTYOFFSET = static_cast<UINT>(WM_USER) +        8335U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_ZERORANGEOFFSET = static_cast<UINT>(WM_USER) +   8336U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_ZEROBEARINGOFFSET = static_cast<UINT>(WM_USER) + 8337U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_RESETTOFACTORY = static_cast<UINT>(WM_USER) +    8338U;
	static const UINT g_unWM_NOTIFY_SIMRAD_UPDATE_ANTTYPE = static_cast<UINT>(WM_USER) +           8339U;
}	// namespace NS_SALUS_MS_APP