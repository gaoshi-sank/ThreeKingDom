#include "SFigure.h"
#include "../RenderFactory.h"

// 构造函数
SFigure::SFigure() {
    type = FigureType::RECTANGLE;
    style.fillColor = D2D1::ColorF(D2D1::ColorF::White);
    style.strokeColor = D2D1::ColorF(D2D1::ColorF::Black);
    style.strokeWidth = 1.0f;
    angle = 0.0f;
}

// 析构函数
SFigure::~SFigure() {
    // 无需要释放的资源
}

// 更新方法
void SFigure::Update() {
    // 可用于动画或变形
}

// 绘制方法
void SFigure::Draw() {
    if (!visiable) return;

    auto render = RenderFactory::GetInstance()->GetRender();
    if (!render) return;

    // 计算旋转中心点
    D2D1_POINT_2F center = {
        (draw_rect.left + draw_rect.right) / 2,
        (draw_rect.top + draw_rect.bottom) / 2
    };

    // 根据不同类型绘制
    switch (type) {
    case FigureType::LINE:      // 画直线
        if (points.size() >= 2) {
            render->RenderLine(points[0], points[1], style.strokeColor, style.strokeWidth, angle, center);
        }
        break;

    case FigureType::RECTANGLE: // 画矩形
        render->RenderRectangle(draw_rect, style.fillColor, style.strokeColor, style.strokeWidth, angle, center);
        break;

    case FigureType::ELLIPSE:   // 画椭圆
        render->RenderEllipse(draw_rect, style.fillColor, style.strokeColor, style.strokeWidth, angle, center);
        break;

    case FigureType::POLYGON:   // 画多边形
        if (points.size() >= 3) {
            render->RenderPolygon(points, style.fillColor, style.strokeColor, style.strokeWidth, angle, center);
        }
        break;

    case FigureType::POLYLINE: // 画多段线
        if (points.size() >= 2) {
            render->RenderPolyline(points, style.strokeColor, style.strokeWidth, angle, center);
        }
        break;
    }
}

// 设置绘制区域
void SFigure::SetRect(D2D1_RECT_F _rect) {
    this->draw_rect = _rect;
}

// 设置旋转角度
void SFigure::SetRotate(float _angle) {
    this->angle = _angle;
}

// 设置图形类型
void SFigure::SetFigureType(FigureType newType) {
    type = newType;
}

// 设置图形样式
void SFigure::SetStyle(const FigureStyle& newStyle) {
    style = newStyle;
}

// 设置顶点
void SFigure::SetPoints(const std::vector<D2D1_POINT_2F>& newPoints) {
    points = newPoints;
}

// 添加顶点
void SFigure::AddPoint(const D2D1_POINT_2F& point) {
    points.push_back(point);
}

// 清空顶点
void SFigure::ClearPoints() {
    points.clear();
}
