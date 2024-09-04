#include <QPainterPath>
#include <QPen>
#include <QBrush>
#include <QGraphicsPathItem>
#include "elementserializer.h"



void ElementSerializer::serializePainterPath(const QPainterPath& path, QDataStream& out) {
    int elementCount = path.elementCount();
    qDebug() << "serializePainterPath" << elementCount;
    out << elementCount;

    // 保存每个元素
    for (int i = 0; i < elementCount; ++i) {
        QPainterPath::Element element = path.elementAt(i);
        out << static_cast<int>(element.type) << element.x << element.y;  // 序列化类型为整数

        qDebug() << element.type << element.x << element.y;

        // 如果是曲线终点 (CurveToElement)，序列化后续的两个控制点
        if (element.type == QPainterPath::CurveToElement) {
            QPainterPath::Element ctrl1 = path.elementAt(i + 1);  // 第一个控制点
            QPainterPath::Element ctrl2 = path.elementAt(i + 2);  // 第二个控制点
            out << ctrl1.x << ctrl1.y << ctrl2.x << ctrl2.y;

            qDebug() << "CurveTo control points:" << ctrl1.x << ctrl1.y << ctrl2.x << ctrl2.y;

            // 跳过控制点，`i` 需要增加 2，因为它们已经被处理
            i += 2;
        }
    }
}

QPainterPath ElementSerializer::deserializePainterPath(QDataStream& in) {
    QPainterPath path;
    int elementCount;
    in >> elementCount;
    qDebug() << "deserializePainterPath" << elementCount;

    // 读取每个元素
    for (int i = 0; i < elementCount; ++i) {
        int typeInt;
        qreal x, y;
        in >> typeInt >> x >> y;

        QPainterPath::ElementType type = static_cast<QPainterPath::ElementType>(typeInt);
        qDebug() << type << x << y;

        // 检查类型是否合法
        if (type != QPainterPath::MoveToElement && type != QPainterPath::LineToElement && type != QPainterPath::CurveToElement) {
            qWarning() << "Invalid QPainterPath::ElementType" << type;
            continue;  // 如果类型无效，跳过该元素
        }

        // 根据元素类型构造路径
        if (type == QPainterPath::MoveToElement) {
            path.moveTo(x, y);
        } else if (type == QPainterPath::LineToElement) {
            path.lineTo(x, y);
        } else if (type == QPainterPath::CurveToElement) {
            qreal ctrl1X, ctrl1Y, ctrl2X, ctrl2Y;
            in >> ctrl1X >> ctrl1Y >> ctrl2X >> ctrl2Y;
            path.cubicTo(QPointF(ctrl1X, ctrl1Y), QPointF(ctrl2X, ctrl2Y), QPointF(x, y));  // 构造曲线
            qDebug() << "CurveTo control points:" << ctrl1X << ctrl1Y << ctrl2X << ctrl2Y;
        }
    }

    return path;
}



// 序列化 QGraphicsPathItem
void ElementSerializer::serializePathItem(QGraphicsPathItem* item, QDataStream& out) {
    QPainterPath path = item->path(); // 获取 QPainterPath
    serializePainterPath(path, out); // 序列化路径
}

// 反序列化 QGraphicsPathItem
QGraphicsPathItem* ElementSerializer::deserializePathItem(QDataStream& in) {
    QPainterPath path = deserializePainterPath(in); // 反序列化路径
    return new QGraphicsPathItem(path); // 使用路径创建 QGraphicsPathItem
}

// 序列化 QPen
void ElementSerializer::serializePen(const QPen& pen, QDataStream& out) {
    out << pen.color() << pen.widthF() << pen.style();
}

// 反序列化 QPen
QPen ElementSerializer::deserializePen(QDataStream& in) {
    QColor color;
    qreal width;
    Qt::PenStyle style;
    in >> color >> width >> style;
    return QPen(color, width, style);
}

// 序列化 QBrush
void ElementSerializer::serializeBrush(const QBrush& brush, QDataStream& out) {
    out << brush.color() << brush.style();
}

// 反序列化 QBrush
QBrush ElementSerializer::deserializeBrush(QDataStream& in) {
    QColor color;
    Qt::BrushStyle style;
    in >> color >> style;
    return QBrush(color, style);
}
// 序列化 QRectF
void ElementSerializer::serializeRect(const QRectF& rect, QDataStream& out) {
    out << rect.x() << rect.y() << rect.width() << rect.height();
    qDebug() << "serializeRect" << rect;
}

// 反序列化 QRectF
QRectF ElementSerializer::deserializeRect(QDataStream& in) {
    qreal x, y, width, height;
    in >> x >> y >> width >> height;
    QRectF rect(x, y, width, height);
    qDebug() << "deserializeRect" << rect;
    return rect;
}

// 序列化 QGraphicsRectItem
void ElementSerializer::serializeGraphicsRectItem(const QGraphicsRectItem* item, QDataStream& out) {
    // 序列化基本几何信息
    serializeRect(item->rect(), out);

    // 序列化位置、旋转、缩放
    out << item->pos() << item->rotation() << item->scale();

    // 序列化 pen 和 brush 的颜色
    out << item->pen().color() << item->brush().color();

    qDebug() << "serializeGraphicsRectItem"
             << "Rect:" << item->rect()
             << "Pos:" << item->pos()
             << "Rotation:" << item->rotation()
             << "Scale:" << item->scale();
}

// 反序列化 QGraphicsRectItem
QGraphicsRectItem* ElementSerializer::deserializeGraphicsRectItem(QDataStream& in) {
    // 反序列化基本几何信息
    QRectF rect = deserializeRect(in);

    // 创建 QGraphicsRectItem
    QGraphicsRectItem* item = new QGraphicsRectItem(rect);

    // 反序列化位置、旋转、缩放
    QPointF pos;
    qreal rotation, scale;
    in >> pos >> rotation >> scale;
    item->setPos(pos);
    item->setRotation(rotation);
    item->setScale(scale);

    // 反序列化 pen 和 brush 的颜色
    QColor penColor, brushColor;
    in >> penColor >> brushColor;
    item->setPen(QPen(penColor));
    item->setBrush(QBrush(brushColor));

    qDebug() << "deserializeGraphicsRectItem"
             << "Rect:" << item->rect()
             << "Pos:" << item->pos()
             << "Rotation:" << item->rotation()
             << "Scale:" << item->scale();

    return item;
}
