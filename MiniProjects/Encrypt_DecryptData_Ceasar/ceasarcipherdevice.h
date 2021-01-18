#ifndef CEASARCIPHERDEVICE_H
#define CEASARCIPHERDEVICE_H
#include <QIODevice>
#include <QString>
#include <QByteArray>
class CeasarCipherDevice : public QIODevice
{
private:
    int m_key;
    QIODevice* m_rootDevice;
public:
    explicit CeasarCipherDevice(QIODevice *parent = nullptr);
    // root device getter - setter
    void setRootDevice(QIODevice* rootDevice);
    QIODevice* rootDevice() const;

    // key getter - setter
    void setKey(int newKey);
    int key() const;

    virtual bool open(OpenMode mode) override;
    virtual qint64 writeData(const char *data, qint64 len) override;
    virtual qint64 readData(char *data, qint64 maxlen) override;
};

#endif // CEASARCIPHERDEVICE_H
