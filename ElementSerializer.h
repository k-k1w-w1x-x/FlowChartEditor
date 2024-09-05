#ifndef ELEMENTSERIALIZER_H
#define ELEMENTSERIALIZER_H

#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QPen>
#include <QBrush>
#include <QDataStream>

class ElementSerializer {
public:
    // 序列化 QPainterPath
    static void serializePainterPath(const QPainterPath& path, QDataStream& out);
    static QPainterPath deserializePainterPath(QDataStream& in);

    // 序列化 QGraphicsPathItem
    static void serializePathItem(QGraphicsPathItem* item, QDataStream& out);
    static QGraphicsPathItem* deserializePathItem(QDataStream& in);

    // 序列化 QPen
    static void serializePen(const QPen& pen, QDataStream& out);
    static QPen deserializePen(QDataStream& in);

    // 序列化 QBrush
    static void serializeBrush(const QBrush& brush, QDataStream& out);
    static QBrush deserializeBrush(QDataStream& in);

    static void serializeRect(const QRectF& rect, QDataStream& out);
    static QRectF deserializeRect(QDataStream& in);
    // 序列化 QGraphicsRectItem
    static void serializeGraphicsRectItem(const QGraphicsRectItem* item, QDataStream& out);
    // 反序列化 QGraphicsRectItem
    static QGraphicsRectItem* deserializeGraphicsRectItem(QDataStream& in);
    static void serializeColor(const QColor &color, QDataStream &out);
    static QColor deserializeColor(QDataStream &in);
};

#endif // ELEMENTSERIALIZER_H
