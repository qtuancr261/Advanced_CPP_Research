#include "ceasarcipherdevice.h"

CeasarCipherDevice::CeasarCipherDevice(QIODevice *parent)
    :QIODevice{parent}, m_key{0}, m_rootDevice{nullptr}
{
    // Default constructor
}

void CeasarCipherDevice::setRootDevice(QIODevice *rootDevice)
{
    m_rootDevice = rootDevice;
}

QIODevice *CeasarCipherDevice::rootDevice() const
{
    return m_rootDevice;
}

void CeasarCipherDevice::setKey(int newKey)
{
    m_key = newKey;
}

int CeasarCipherDevice::key() const
{
    return m_key;
}

bool CeasarCipherDevice::open(OpenMode mode)
{
    if (m_rootDevice == nullptr)
        return false;
    // invalid device
    if (m_rootDevice->openMode() != mode)
        return false;
    // check if the device was opened in the same mode before calling QIODevice::open(mode)
    return QIODevice::open(mode);
    // the QIODEvice::open(OpenMode) should be called from any reimplementations of open() or
    // other functions that open the device
}

qint64 CeasarCipherDevice::writeData(const char *data, qint64 len)
{
    // copy data into a local byte array
    QByteArray bytes(data, len);
    // perform the encryption - ceasar
    for (int i=0; i < len; i++)
        bytes.data()[i] += m_key;
    // write the byte array to the underlying device
    int written = m_rootDevice->write(bytes);
    // emit a signal that carries the informa
    emit bytesWritten(written);
    return written;
}

qint64 CeasarCipherDevice::readData(char *data, qint64 maxlen)
{
    // Read from the device and store the data in a byte array
    QByteArray baseData = m_rootDevice->read(maxlen);
    const int size = baseData.size();
    // Perform the decryption - ceasar
    for (int i = 0; i < size; i++)
        data[i] = baseData.at(i) - m_key;
    // return the amount of data that was reallt read.
    return size;
}

