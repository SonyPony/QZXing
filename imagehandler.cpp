#include "imagehandler.h"
#include <QImage>
#include <QDebug>
#include <QQuickItem>
#include <QQuickWindow>
#include <QQuickItemGrabResult>

ImageHandler::ImageHandler(QObject *parent) :
    QObject(parent)
{
}

void ImageHandler::extractQImage(QObject *imageObj,
                                   const double offsetX, const double offsetY,
                                   const double width, const double height)
{
    QQuickItem* item = qobject_cast<QQuickItem*>(imageObj);

    disconnect(result.data(), SIGNAL(ready()), this, SLOT(emitConversionResult()));
    result = item->grabToImage(QSize(item->width(), item->height()));
    connect(result.data(), SIGNAL(ready()), this, SLOT(emitConversionResult()));
}

void ImageHandler::emitConversionResult()
{
    emit conversionDone(result.data()->image());
}
