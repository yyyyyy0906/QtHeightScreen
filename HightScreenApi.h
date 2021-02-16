#ifndef HIGHTSCREENAPI_H
#define HIGHTSCREENAPI_H

#include <QObject>
#include <QtMath>

#ifdef Q_OS_WIN
#include <qt_windows.h>
#ifdef _MSC_VER
#pragma comment(lib, "user32.lib")
#endif
#endif

extern float dpiScaleRatio;

const float DEFAULT_DPI_SCALED = 96.0;
const float DEFAULT_MAX_DPI    = 0.9f;

class ScreenDPIUtils final {
public:
    ScreenDPIUtils() = delete;
    ScreenDPIUtils(const ScreenDPIUtils&) = delete;
    ~ScreenDPIUtils() = delete;

    /// \brief setScaleRatio
    /// \param value
    /// 设置缩放比例
    static void setScaleRatio(const float& value) {
        dpiScaleRatio = value;
    }
    /// \brief getScaleRatio
    /// \return
    /// 获取缩放比例
    static float getScaleRatio(void) {
        if (dpiScaleRatio > 0) return dpiScaleRatio;
        dpiScaleRatio = sqrtf(getCurrentWinDpi());
        float screenWidth  = getCurrentScreenWidth();
        float screenHeight = getCurrentScreenHeight();
        if (screenWidth  < DEF_SCREEN_WIDTH   ||
            screenHeight < DEF_SCREEN_HEIGHT) {
            float scaleWidth  = (float)(dpiScaleRatio * screenWidth  / DEF_SCREEN_WIDTH );
            float scaleHeight = (float)(dpiScaleRatio * screenHeight / DEF_SCREEN_HEIGHT);
            dpiScaleRatio = qMin(scaleWidth, scaleHeight);
        }
        return dpiScaleRatio;
    }
    /// \brief getScaleRatio
    /// \param value
    /// \return
    /// 获取缩放后的大小
    static int getScaleRatio(const int& value) {
        return dpiScaleRatio * value;
    }
    /// \brief getCurrentWinDpi
    /// \return
    /// 获取当前缩放比例
    static float getCurrentWinDpi() {
#ifdef Q_OS_WIN
        HDC screen = GetDC(NULL);
        FLOAT dpi = static_cast<FLOAT>(GetDeviceCaps(screen, LOGPIXELSX));
        ReleaseDC(0, screen);
        float scale = dpi / DEFAULT_DPI_SCALED;
        return scale;
#endif
        return DEFAULT_DPI_SCALED;
    }
    /// \brief getCurrentScreenWidth
    /// \return
    /// 获取当前屏幕宽度
    static float getCurrentScreenWidth() {
#ifdef Q_OS_WIN
        RECT rect;
        SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
        FLOAT screenWidth = static_cast<FLOAT>(rect.right - rect.left);
        return screenWidth;
#endif
        return 0.0;
    }
    /// \brief getCurrentScreenHeight
    /// \return
    /// 获取当前屏幕高度
    static float getCurrentScreenHeight() {
#ifdef Q_OS_WIN
        RECT rect;
        SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
        FLOAT screenHeight = static_cast<FLOAT>(rect.bottom - rect.top);
        return screenHeight;
#endif
        return 0.0;
    }

private:
    enum {
        DEF_SCREEN_WIDTH  = 1920,
        DEF_SCREEN_HEIGHT = 1080
    };
};

#endif // HIGHTSCREENAPI_H
