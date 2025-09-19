#pragma once

#include <atlimage.h>
#include <afxbutton.h>

#include "SmsBaseDef.h"
#include "SmsImage.h"

#include "SystemTypeDef.h"

namespace NS_SALUS_MS_APP
{
	enum class E_IMAGE_SIZE : INT
	{
		eLARGE_SIZE = 0,
		eSMALL_SIZE,
	};

	class AFX_EXT_CLASS CSmsBaseImage
	{
	public:
		CSmsBaseImage() noexcept;
		~CSmsBaseImage();

	public:
		static CSmsBaseImage* GetInstance();
		static void DeleteInstance();

		void LoadBaseImage(const CString strHomeDirectory);

		CSmsImage* GetCheckImage(const E_COLOR_SET eColorSet, const INT nIndex);
		CSmsImage* GetRadioImage(const E_COLOR_SET eColorSet, const INT nIndex);

		CSmsImage* GetOverlayLargeImage(const E_COLOR_SET eColorSet, const E_OVERLAY_FORMAT eOverlayFormat);
		CSmsImage* GetOverlayMidiumImage(const E_COLOR_SET eColorSet, const E_OVERLAY_FORMAT eOverlayFormat);

		CSmsImage* GetScreenLargeImage(const E_COLOR_SET eColorSet);
		CSmsImage* GetScreenSmallImage(const E_COLOR_SET eColorSet);

		CSmsImage* GetStatusGreenImage(const INT nIndex);
		CSmsImage* GetStatusRedImage(const INT nIndex);

		CSmsImage* GetAlarmImage(const INT nIndex);
		CSmsImage* GetAlarmListImage(const E_COLOR_SET eColorSet);
		CSmsImage* GetSoundOnImage(const E_COLOR_SET eColorSet);
		CSmsImage* GetSoundOffImage(const E_COLOR_SET eColorSet);
		CSmsImage* GetVolumeUpImage(const E_COLOR_SET eColorSet);
		CSmsImage* GetVolumeDownImage(const E_COLOR_SET eColorSet);
		CSmsImage* GetVolumeImage(const E_COLOR_SET eColorSet, const INT nIndex);

	private:
		void LoadBaseImage();
		static UINT LoadBaseImageThread(LPVOID const lpParam);

		void LoadCheckButtonImages();
		void LoadRadioButtonImages();
		void LoadStatusImages();
		void LoadZoneLargeImages();
		void LoadZoneMidiumImages();
		void LoadScreenLargeImages();
		void LoadScreenSmallImages();
		void LoadAlarmImages();

		void DeleteCheckButtonImages();
		void DeleteRadioButtonImages();
		void DeleteStatusImages();
		void DeleteZoneLargeImages();
		void DeleteZoneMidiumImages();
		void DeleteScreenLargeImages();
		void DeleteScreenSmallImages();
		void DeleteAlarmImages();

		void LoadImageFromFile(CSmsImage** ppLoadImage, CString strFileName);
		void DeleteImage(CSmsImage** pDelImage);

	private:
		static CSmsBaseImage* m_pInstance;

		static const INT m_nMaxButtonImageNum = 6;
		static const INT m_nMaxZoneImageNum = 7;
		static const INT m_nMaxStatusImageNum = 16;
		static const INT m_nMaxVolumeNum = 6;

		CString m_strHomeDirectory;

		CSmsImage* m_pimgCheckDay[m_nMaxButtonImageNum];		// Check Button Day Image
		CSmsImage* m_pimgCheckNight[m_nMaxButtonImageNum];		// Check Button Night Image
		CSmsImage* m_pimgRadioDay[m_nMaxButtonImageNum];		// Radio Button Day Image
		CSmsImage* m_pimgRadioNight[m_nMaxButtonImageNum];		// Radio Button Night Image

		CSmsImage* m_pimgZoneDayLarge[m_nMaxZoneImageNum];		// Guard Zone and User Map Day Large Image
		CSmsImage* m_pimgZoneNightLarge[m_nMaxZoneImageNum];	// Guard Zone and User Map Night Large Image

		CSmsImage* m_pimgZoneDayMidium[m_nMaxZoneImageNum];		// Guard Zone and User Map Day Midium Image
		CSmsImage* m_pimgZoneNightMidium[m_nMaxZoneImageNum];	// Guard Zone and User Map Night Midium Image

		CSmsImage* m_pimgScreenDayLarge;						// Screen Button Day Large Image
		CSmsImage* m_pImgScreenNightLarge;						// Screen Button Night Large Image
		CSmsImage* m_pimgScreenDaySmall;						// Screen Button Day Small Image
		CSmsImage* m_pimgScreenNightSmall;						// Screen Button Night Small Image

		CSmsImage* m_pimgStatusGreen[m_nMaxStatusImageNum];
		CSmsImage* m_pimgStatusRed[m_nMaxStatusImageNum];

		CSmsImage* m_pimgAlarm[6];

		CSmsImage* m_pimgAlarmListDay;
		CSmsImage* m_pimgAlarmListNight;
		CSmsImage* m_pimgSoundOnDay;
		CSmsImage* m_pimgSoundOnNight;
		CSmsImage* m_pimgSoundOffDay;
		CSmsImage* m_pimgSoundOffNight;
		CSmsImage* m_pimgVolumeUpDay;
		CSmsImage* m_pimgVolumeUpNight;
		CSmsImage* m_pimgVolumeDnDay;
		CSmsImage* m_pimgVolumeDnNight;
		CSmsImage* m_pimgVolumeDay[m_nMaxVolumeNum];
		CSmsImage* m_pimgVolumeNight[m_nMaxVolumeNum];
	};
}	// NS_SALUS_MS_APP