#ifndef IMAGELOADER_H
#define IMAGELOADER_H

class ImageLoader
{
public:
    ImageLoader();

    inline QPixmap *loadImage(QByteArray &data){imageData->loadFromData(data);}
    QPixmap *loadImage(QString data);
};

#endif // IMAGELOADER_H
