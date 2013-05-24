#ifndef IMAGELOADER_H
#define IMAGELOADER_H
class QPixmap;
class QString;
class ImageLoader
{
public:
    ImageLoader();

    //inline QPixmap *loadImage(QByteArray &data){imageData->loadFromData(data);}
    QPixmap *loadImage(QString path);
};

#endif // IMAGELOADER_H
