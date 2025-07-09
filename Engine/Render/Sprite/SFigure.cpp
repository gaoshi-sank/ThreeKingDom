#include "SFigure.h"
#include "../RenderFactory.h"

// ���캯��
SFigure::SFigure() {
    type = FigureType::RECTANGLE;
    style.fillColor = D2D1::ColorF(D2D1::ColorF::White);
    style.strokeColor = D2D1::ColorF(D2D1::ColorF::Black);
    style.strokeWidth = 1.0f;
    angle = 0.0f;
}

// ��������
SFigure::~SFigure() {
    // ����Ҫ�ͷŵ���Դ
}

// ���·���
void SFigure::Update() {
    // �����ڶ��������
}

// ���Ʒ���
void SFigure::Draw() {
    if (!visiable) return;

    auto render = RenderFactory::GetInstance()->GetRender();
    if (!render) return;

    // ������ת���ĵ�
    D2D1_POINT_2F center = {
        (draw_rect.left + draw_rect.right) / 2,
        (draw_rect.top + draw_rect.bottom) / 2
    };

    // ���ݲ�ͬ���ͻ���
    switch (type) {
    case FigureType::LINE:      // ��ֱ��
        if (points.size() >= 2) {
            render->RenderLine(points[0], points[1], style.strokeColor, style.strokeWidth, angle, center);
        }
        break;

    case FigureType::RECTANGLE: // ������
        render->RenderRectangle(draw_rect, style.fillColor, style.strokeColor, style.strokeWidth, angle, center);
        break;

    case FigureType::ELLIPSE:   // ����Բ
        render->RenderEllipse(draw_rect, style.fillColor, style.strokeColor, style.strokeWidth, angle, center);
        break;

    case FigureType::POLYGON:   // �������
        if (points.size() >= 3) {
            render->RenderPolygon(points, style.fillColor, style.strokeColor, style.strokeWidth, angle, center);
        }
        break;

    case FigureType::POLYLINE: // �������
        if (points.size() >= 2) {
            render->RenderPolyline(points, style.strokeColor, style.strokeWidth, angle, center);
        }
        break;
    }
}

// ���û�������
void SFigure::SetRect(D2D1_RECT_F _rect) {
    this->draw_rect = _rect;
}

// ������ת�Ƕ�
void SFigure::SetRotate(float _angle) {
    this->angle = _angle;
}

// ����ͼ������
void SFigure::SetFigureType(FigureType newType) {
    type = newType;
}

// ����ͼ����ʽ
void SFigure::SetStyle(const FigureStyle& newStyle) {
    style = newStyle;
}

// ���ö���
void SFigure::SetPoints(const std::vector<D2D1_POINT_2F>& newPoints) {
    points = newPoints;
}

// ��Ӷ���
void SFigure::AddPoint(const D2D1_POINT_2F& point) {
    points.push_back(point);
}

// ��ն���
void SFigure::ClearPoints() {
    points.clear();
}
