// https://github.com/amaork/libi2c

#ifndef _I2C_H_
#define _I2C_H_

#include <QObject>
#include <QString>
#include <qqml.h>
#include <QQuickItem>
#include <QTimer>
#include <linux/types.h>

#include <sys/types.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>


// I2c device
typedef struct i2c_device {
    int bus;			        /* I2C Bus fd, return from i2c_open */
    unsigned short addr;		/* I2C device(slave) address */
    unsigned char tenbit;		/* I2C is 10 bit device address */
    unsigned char delay;		/* I2C internal operation delay, unit millisecond */
    unsigned short flags;		/* I2C i2c_ioctl_read/write flags */
    unsigned int page_bytes;    /* I2C max number of bytes per page, 1K/2K 8, 4K/8K/16K 16, 32K/64K 32 etc */
    unsigned int iaddr_bytes;   /* I2C device internal(word) address bytes, such as: 24C04 1 byte, 24C64 2 bytes */
} I2CDevice;



class I2C : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString buss READ readBuss WRITE setBuss)
    Q_PROPERTY(int address READ readAddress WRITE setAddress)
    Q_PROPERTY(int sensor READ readSensor WRITE setSensor NOTIFY sensorChanged)
    QML_ELEMENT

public:
    explicit I2C(QObject *parent = nullptr);


    void setBuss(QString buss);
    int readBuss();

    void setAddress(int address);
    int readAddress();

    void setSensor(int sensor);

    /* Close i2c bus */
    void i2c_close(int bus);

    /* Open i2c bus, return i2c bus fd */
    int i2c_open(const char *bus_name);

    /* Initialize I2CDevice with default value */
    void i2c_init_device(I2CDevice *device);

    /* Get i2c device description */
    char *i2c_get_device_desc(const I2CDevice *device, char *buf, size_t size);

    /* Select i2c device on i2c bus */
    int i2c_select(int bus, unsigned long dev_addr, unsigned long tenbit);

    /* I2C internal(word) address convert */
    void i2c_iaddr_convert(unsigned int int_addr, unsigned int iaddr_bytes, unsigned char *addr);

    void i2c_delay(unsigned char delay);

    /* I2C file I/O read, write */
    ssize_t i2c_read(const I2CDevice *device, unsigned int iaddr, __u8 *buf, size_t len);
    ssize_t i2c_write(const I2CDevice *device, unsigned int iaddr, const unsigned char *buf, size_t len);

signals:
    void sensorChanged(int val);

public slots:
    int readSensor();

private:
    /* I2c ioctl read, write can set i2c flags */
    ssize_t i2c_ioctl_read(const I2CDevice *device, unsigned int iaddr, __u8 *buf, size_t len);
    ssize_t i2c_ioctl_write(const I2CDevice *device, unsigned int iaddr, const unsigned char *buf, size_t len);

    /* I2C read / write handle function */
    typedef ssize_t (*I2C_READ_HANDLE)(const I2CDevice *dev, unsigned int iaddr, void *buf, size_t len);
    typedef ssize_t (*I2C_WRITE_HANDLE)(const I2CDevice *dev, unsigned int iaddr, const void *buf, size_t len);


//    int addr;
//    QString buss;


};

#endif
