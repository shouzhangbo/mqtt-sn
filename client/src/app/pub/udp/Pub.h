//
// Copyright 2016 - 2020 (C). Alex Robenko. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include <memory>
#include <type_traits>
#include <string>
#include <list>

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>

#include "client.h"

namespace mqttsn
{

namespace client
{

namespace app
{

namespace sub
{

namespace udp
{

class Pub : public QObject
{
    Q_OBJECT
public:
    Pub();

    void setGwAddr(const QString& value)
    {
        m_gwAddr = value;
    }

    void setGwPort(unsigned short value)
    {
        m_gwPort = value;
    }

    void setGwId(int value)
    {
        m_gwId = value;
    }

    void setLocalPort(unsigned short value)
    {
        m_localPort = value;
    }

    void setClientId(const std::string& value)
    {
        m_clientId = value;
    }

    void setKeepAlive(unsigned short value)
    {
        m_keepAlive = value;
    }

    void setCleanSession(bool value)
    {
        m_cleanSession = value;
    }

    void setTopic(const std::string& topic)
    {
        m_topic = topic;
    }

    void setTopicId(std::uint16_t topicId)
    {
        m_topicId = topicId;
    }

    void setQos(MqttsnQoS value)
    {
        m_qos = value;
    }

    void setRetain(bool value)
    {
        m_retain = value;
    }

    typedef std::vector<std::uint8_t> DataBuf;
    void setMessage(const DataBuf& value)
    {
        m_msg = value;
    }

    void setDebug(bool value)
    {
        m_debug = value;
    }

    bool start();

private slots:
    void tick();
    void readFromSocket();
    void socketErrorOccurred(QAbstractSocket::SocketError err);

private:
    struct ClientDeleter
    {
        void operator()(MqttsnClientHandle client)
        {
            mqttsn_client_free(client);
        }
    };

    typedef std::unique_ptr<
        typename std::remove_pointer<MqttsnClientHandle>::type,
        ClientDeleter
    > ClientPtr;

    void nextTickProgram(unsigned ms);
    static void nextTickProgramCb(void* obj, unsigned ms);

    unsigned cancelTick();
    static unsigned caneclTickCb(void* obj);

    void sendData(const unsigned char* buf, unsigned bufLen, bool broadcast);
    static void sendDataCb(void* obj, const unsigned char* buf, unsigned bufLen, bool broadcast);

    void gwStatusReport(unsigned short gwId, MqttsnGwStatus status);
    static void gwStatusReportCb(void* obj, unsigned char gwId, MqttsnGwStatus status);

    void gwDisconnectReport();
    static void gwDisconnectReportCb(void* obj);

    static void messageReportCb(void* obj, const MqttsnMessageInfo* msgInfo);

    void doConnect(bool reconnecting = false);
    void doPublish();
    void connectComplete(MqttsnAsyncOpStatus status);
    static void connectCompleteCb(void* obj, MqttsnAsyncOpStatus status);
    void disconnectComplete(MqttsnAsyncOpStatus status);
    static void disconnectCompleteCb(void* obj, MqttsnAsyncOpStatus status);
    void publishComplete(MqttsnAsyncOpStatus status);
    static void publishCompleteCb(void* obj, MqttsnAsyncOpStatus status);
    bool bindLocalPort();
    bool openSocket();
    bool connectToGw();
    void broadcastData(const unsigned char* buf, unsigned bufLen);
    void sendDataConnected(const unsigned char* buf, unsigned bufLen);
    static void quitApp();

    ClientPtr m_client;
    QTimer m_timer;
    unsigned m_reqTimeout = 0;
    QString m_gwAddr;
    unsigned short m_gwPort = 0;
    int m_gwId = -1;
    unsigned short m_localPort = 0;
    QUdpSocket m_socket;
    QHostAddress m_lastSenderAddress;
    quint16 m_lastSenderPort;
    std::string m_clientId;
    unsigned short m_keepAlive = 0;
    bool m_cleanSession = true;
    bool m_retain = false;
    std::string m_topic;
    std::uint16_t m_topicId;
    MqttsnQoS m_qos = MqttsnQoS_AtMostOnceDelivery;
    DataBuf m_msg;
    bool m_debug = false;
    bool m_disconnecting = false;
};

}  // namespace udp

}  // namespace sub

}  // namespace app

}  // namespace client

}  // namespace mqttsn


