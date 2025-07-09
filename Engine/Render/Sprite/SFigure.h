#ifndef _SFigure_h_
#define _SFigure_h_

#include "BaseSprite.h"
#include <vector>

// 图形类型枚举
enum class FigureType {
    LINE,       // 直线
    RECTANGLE,  // 矩形
    ELLIPSE,    // 椭圆
    POLYGON,    // 多边形
    POLYLINE    // 多段线
};

// 图形样式
struct FigureStyle {
    D2D1_COLOR_F fillColor;    // 填充色
    D2D1_COLOR_F strokeColor;  // 边框色
    float strokeWidth;         // 边框粗细
};

class SFigure : public Sprite {
private:
    FigureType type;                    // 图形类型
    FigureStyle style;                  // 绘制样式
    std::vector<D2D1_POINT_2F> points;  // 图形顶点
    float angle;                        // 旋转角度

public:
    // 构造函数
    SFigure();

    // 析构函数
    virtual ~SFigure();

    // 实现基类虚函数
    virtual void Update() override;
    virtual void Draw() override;
    virtual void SetRect(D2D1_RECT_F _rect) override;
    virtual void SetRotate(float _angle) override;
    virtual ID2D1Bitmap* GetImage() override { return nullptr; }

    // 新增功能方法
    void SetFigureType(FigureType newType);
    void SetStyle(const FigureStyle& newStyle);
    void SetPoints(const std::vector<D2D1_POINT_2F>& newPoints);
    void AddPoint(const D2D1_POINT_2F& point);
    void ClearPoints();
};

#endif //!_SFigure_h_