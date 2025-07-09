#ifndef _SFigure_h_
#define _SFigure_h_

#include "BaseSprite.h"
#include <vector>

// ͼ������ö��
enum class FigureType {
    LINE,       // ֱ��
    RECTANGLE,  // ����
    ELLIPSE,    // ��Բ
    POLYGON,    // �����
    POLYLINE    // �����
};

// ͼ����ʽ
struct FigureStyle {
    D2D1_COLOR_F fillColor;    // ���ɫ
    D2D1_COLOR_F strokeColor;  // �߿�ɫ
    float strokeWidth;         // �߿��ϸ
};

class SFigure : public Sprite {
private:
    FigureType type;                    // ͼ������
    FigureStyle style;                  // ������ʽ
    std::vector<D2D1_POINT_2F> points;  // ͼ�ζ���
    float angle;                        // ��ת�Ƕ�

public:
    // ���캯��
    SFigure();

    // ��������
    virtual ~SFigure();

    // ʵ�ֻ����麯��
    virtual void Update() override;
    virtual void Draw() override;
    virtual void SetRect(D2D1_RECT_F _rect) override;
    virtual void SetRotate(float _angle) override;
    virtual ID2D1Bitmap* GetImage() override { return nullptr; }

    // �������ܷ���
    void SetFigureType(FigureType newType);
    void SetStyle(const FigureStyle& newStyle);
    void SetPoints(const std::vector<D2D1_POINT_2F>& newPoints);
    void AddPoint(const D2D1_POINT_2F& point);
    void ClearPoints();
};

#endif //!_SFigure_h_