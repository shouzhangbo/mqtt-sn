//
// Copyright 2016 (C). Alex Robenko. All rights reserved.
//

// This file is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "CommonTestClient.h"

#include <cassert>
#include <iostream>

namespace
{

ClientLibFuncs createDefaultLibFuncs()
{
    ClientLibFuncs funcs;
    funcs.m_newFunc = &mqttsn_client_new;
    funcs.m_freeFunc = &mqttsn_client_free;
    funcs.m_nextTickProgramCallbackSetFunc = &mqttsn_client_set_next_tick_program_callback;
    funcs.m_cancelNextTickCallbackSetFunc = &mqttsn_client_set_cancel_next_tick_wait_callback;
    funcs.m_sentOutDataCallbackSetFunc = &mqttsn_client_set_send_output_data_callback;
    funcs.m_gwStatusReportCallbackSetFunc = &mqttsn_client_set_gw_status_report_callback;
    funcs.m_connectionStatusReportCallbackSetFunc = &mqttsn_client_set_connection_status_report_callback;
    funcs.m_msgReportCallbackSetFunc = &mqttsn_client_set_message_report_callback;
    funcs.m_startFunc = &mqttsn_client_start;
    funcs.m_processDataFunc = &mqttsn_client_process_data;
    funcs.m_tickFunc = &mqttsn_client_tick;
    funcs.m_setGwAdvertisePeriodFunc = &mqttsn_client_set_gw_advertise_period;
    funcs.m_setRetryPeriodFunc = &mqttsn_client_set_retry_period;
    funcs.m_setRetryCountFunc = &mqttsn_client_set_retry_count;
    funcs.m_setBroadcastRadius = &mqttsn_client_set_broadcast_radius;
    funcs.m_setSearchgwEnabledFunc = &mqttsn_client_set_searchgw_enabled;
    funcs.m_cancelFunc = &mqttsn_client_cancel;
    funcs.m_connectFunc = &mqttsn_client_connect;
    funcs.m_disconnectFunc = &mqttsn_client_disconnect;
    funcs.m_publishIdFunc = &mqttsn_client_publish_id;
    funcs.m_publishFunc = &mqttsn_client_publish;
    funcs.m_subscribeIdFunc = &mqttsn_client_subscribe_id;
    funcs.m_subscribeFunc = &mqttsn_client_subscribe;
    funcs.m_unsubscribeIdFunc = &mqttsn_client_unsubscribe_id;
    funcs.m_unsubscribeFunc = &mqttsn_client_unsubscribe;
    funcs.m_willUpdateFunc = &mqttsn_client_will_update;
    funcs.m_willTopicUpdateFunc = &mqttsn_client_will_topic_update;
    funcs.m_willMsgUpdateFunc = &mqttsn_client_will_msg_update;
    funcs.m_sleepFunc = &mqttsn_client_sleep;
    funcs.m_checkMessagesFunc = &mqttsn_client_check_messages;
    return funcs;
}

}  // namespace

const ClientLibFuncs CommonTestClient::DefaultFuncs = createDefaultLibFuncs();

CommonTestClient::~CommonTestClient()
{
    assert(m_libFuncs.m_freeFunc != nullptr);
    m_libFuncs.m_freeFunc(m_client);
}

CommonTestClient::ProgramNextTickCallback CommonTestClient::setProgramNextTickCallback(
    ProgramNextTickCallback&& func)
{
    ProgramNextTickCallback old(std::move(m_programNextTickCallback));
    m_programNextTickCallback = std::move(func);
    return old;
}

CommonTestClient::CancelNextTickCallback CommonTestClient::setCancelNextTickCallback(
    CancelNextTickCallback&& func)
{
    CancelNextTickCallback old(std::move(m_cancelNextTickCallback));
    m_cancelNextTickCallback = std::move(func);
    return old;
}

CommonTestClient::SendDataCallback CommonTestClient::setSendDataCallback(
    SendDataCallback&& func)
{
    SendDataCallback old(std::move(m_sendDataCallback));
    m_sendDataCallback = std::move(func);
    return old;
}

CommonTestClient::GwStatusReportCallback CommonTestClient::setGwStatusReportCallback(
    GwStatusReportCallback&& func)
{
    GwStatusReportCallback old(std::move(m_gwStatusReportCallback));
    m_gwStatusReportCallback = std::move(func);
    return old;
}

CommonTestClient::ConnectionStatusReportCallback CommonTestClient::setConnectionStatusReportCallback(
    ConnectionStatusReportCallback&& func)
{
    ConnectionStatusReportCallback old(std::move(m_connectionStatusReportCallback));
    m_connectionStatusReportCallback = std::move(func);
    return old;
}

CommonTestClient::MessageReportCallback CommonTestClient::setMessageReportCallback(
    MessageReportCallback&& func)
{
    MessageReportCallback old(std::move(m_msgReportCallback));
    m_msgReportCallback = std::move(func);
    return old;
}

CommonTestClient::PublishCompleteCallback CommonTestClient::setPublishCompleteCallback(
    PublishCompleteCallback&& func)
{
    PublishCompleteCallback old(std::move(m_publishCompleteCallback));
    m_publishCompleteCallback = std::move(func);
    return old;
}

CommonTestClient::SubscribeCompleteCallback CommonTestClient::setSubsribeCompleteCallback(
    SubscribeCompleteCallback&& func)
{
    SubscribeCompleteCallback old(std::move(m_subscribeCompleteCallback));
    m_subscribeCompleteCallback = std::move(func);
    return old;
}

CommonTestClient::UnsubscribeCompleteCallback CommonTestClient::setUnsubsribeCompleteCallback(
    UnsubscribeCompleteCallback&& func)
{
    UnsubscribeCompleteCallback old(std::move(m_unsubscribeCompleteCallback));
    m_unsubscribeCompleteCallback = std::move(func);
    return old;
}

CommonTestClient::WillUpdateCompleteCallback CommonTestClient::setWillUpdateCompleteCallback(
    WillUpdateCompleteCallback&& func)
{
    WillUpdateCompleteCallback old(std::move(m_willUpdateCompleteCallback));
    m_willUpdateCompleteCallback = std::move(func);
    return old;
}

CommonTestClient::WillTopicUpdateCompleteCallback CommonTestClient::setWillTopicUpdateCompleteCallback(
    WillTopicUpdateCompleteCallback&& func)
{
    WillTopicUpdateCompleteCallback old(std::move(m_willTopicUpdateCompleteCallback));
    m_willTopicUpdateCompleteCallback = std::move(func);
    return old;
}

CommonTestClient::WillMsgUpdateCompleteCallback CommonTestClient::setWillMsgUpdateCompleteCallback(
    WillMsgUpdateCompleteCallback&& func)
{
    WillMsgUpdateCompleteCallback old(std::move(m_willMsgUpdateCompleteCallback));
    m_willMsgUpdateCompleteCallback = std::move(func);
    return old;
}

CommonTestClient::SleepCompleteCallback CommonTestClient::setSleepCompleteCallback(
    SleepCompleteCallback&& func)
{
    SleepCompleteCallback old(std::move(m_sleepCompleteCallback));
    m_sleepCompleteCallback = std::move(func);
    return old;
}

CommonTestClient::CheckMessagesCompleteCallback CommonTestClient::setCheckMessagesCompleteCallback(
    CheckMessagesCompleteCallback&& func)
{
    CheckMessagesCompleteCallback old(std::move(m_checkMessagesCompleteCallback));
    m_checkMessagesCompleteCallback = std::move(func);
    return old;
}

CommonTestClient::Ptr CommonTestClient::alloc(const ClientLibFuncs& libFuncs)
{
    return Ptr(new CommonTestClient(libFuncs));
}

bool CommonTestClient::start()
{
    assert(m_libFuncs.m_startFunc != nullptr);
    return (m_libFuncs.m_startFunc)(m_client);
}

void CommonTestClient::inputData(const std::uint8_t* buf, std::size_t bufLen)
{
    assert(m_inData.empty());
    m_inData.insert(m_inData.end(), buf, buf + bufLen);
    assert(m_libFuncs.m_processDataFunc != nullptr);
    assert(!m_inData.empty());
    unsigned count = (m_libFuncs.m_processDataFunc)(m_client, &m_inData[0], m_inData.size());
    if (m_inData.size() < count) {
        std::cout << "Processed " << count << " bytes, while having only " << m_inData.size() << std::endl;
    }
    assert(count <= m_inData.size());
    m_inData.erase(m_inData.begin(), m_inData.begin() + count);
}

void CommonTestClient::tick(unsigned ms)
{
    assert(m_libFuncs.m_tickFunc != nullptr);
    (m_libFuncs.m_tickFunc)(m_client, ms);
}

void CommonTestClient::setGwAdvertisePeriod(unsigned ms)
{
    assert(m_libFuncs.m_setGwAdvertisePeriodFunc != nullptr);
    (m_libFuncs.m_setGwAdvertisePeriodFunc)(m_client, ms);
}

void CommonTestClient::setRetryPeriod(unsigned ms)
{
    assert(m_libFuncs.m_setRetryPeriodFunc != nullptr);
    (m_libFuncs.m_setRetryPeriodFunc)(m_client, ms);
}

void CommonTestClient::setRetryCount(unsigned value)
{
    assert(m_libFuncs.m_setRetryCountFunc != nullptr);
    (m_libFuncs.m_setRetryCountFunc)(m_client, value);
}

void CommonTestClient::setBroadcastRadius(unsigned char val)
{
    assert(m_libFuncs.m_setBroadcastRadius != nullptr);
    (m_libFuncs.m_setBroadcastRadius)(m_client, val);
}

void CommonTestClient::setSearchgwEnabled(bool value)
{
    assert(m_libFuncs.m_setSearchgwEnabledFunc != nullptr);
    (m_libFuncs.m_setSearchgwEnabledFunc)(m_client, value);
}

MqttsnErrorCode CommonTestClient::connect(
    const char* clientId,
    unsigned short keepAliveSeconds,
    bool cleanSession,
    const MqttsnWillInfo* willInfo)
{
    assert(m_libFuncs.m_connectFunc != nullptr);

    return
        (m_libFuncs.m_connectFunc)(
            m_client,
            clientId,
            keepAliveSeconds,
            cleanSession,
            willInfo);
}

bool CommonTestClient::cancel()
{
    assert(m_libFuncs.m_cancelFunc != nullptr);
    return (m_libFuncs.m_cancelFunc)(m_client);
}

MqttsnErrorCode CommonTestClient::disconnect()
{
    assert(m_libFuncs.m_disconnectFunc != nullptr);
    return (m_libFuncs.m_disconnectFunc)(m_client);
}

MqttsnErrorCode CommonTestClient::publishId(
    MqttsnTopicId topicId,
    const std::uint8_t* msg,
    std::size_t msgLen,
    MqttsnQoS qos,
    bool retain)
{
    assert(m_libFuncs.m_publishIdFunc != nullptr);
    return (m_libFuncs.m_publishIdFunc)(
        m_client,
        topicId,
        msg,
        msgLen,
        qos,
        retain,
        &CommonTestClient::publishCompleteCallback,
        this);
}

MqttsnErrorCode CommonTestClient::publish(
    const std::string& topic,
    const std::uint8_t* msg,
    std::size_t msgLen,
    MqttsnQoS qos,
    bool retain)
{
    assert(m_libFuncs.m_publishFunc != nullptr);
    return (m_libFuncs.m_publishFunc)(
        m_client,
        topic.c_str(),
        msg,
        msgLen,
        qos,
        retain,
        &CommonTestClient::publishCompleteCallback,
        this);
}

MqttsnErrorCode CommonTestClient::subscribe(
    const std::string& topic,
    MqttsnQoS qos)
{
    assert(m_libFuncs.m_subscribeFunc != nullptr);
    return (m_libFuncs.m_subscribeFunc)(
        m_client,
        topic.c_str(),
        qos,
        &CommonTestClient::subsribeCompleteCallback,
        this);
}

MqttsnErrorCode CommonTestClient::subscribe(
    MqttsnTopicId topicId,
    MqttsnQoS qos)
{
    assert(m_libFuncs.m_subscribeIdFunc != nullptr);
    return (m_libFuncs.m_subscribeIdFunc)(
        m_client,
        topicId,
        qos,
        &CommonTestClient::subsribeCompleteCallback,
        this);
}

MqttsnErrorCode CommonTestClient::unsubscribe(const std::string& topic)
{
    assert(m_libFuncs.m_unsubscribeFunc != nullptr);
    return (m_libFuncs.m_unsubscribeFunc)(
        m_client,
        topic.c_str(),
        &CommonTestClient::unsubsribeCompleteCallback,
        this);
}

MqttsnErrorCode CommonTestClient::unsubscribe(MqttsnTopicId topicId)
{
    assert(m_libFuncs.m_unsubscribeIdFunc != nullptr);
    return (m_libFuncs.m_unsubscribeIdFunc)(
        m_client,
        topicId,
        &CommonTestClient::unsubsribeCompleteCallback,
        this);
}

MqttsnErrorCode CommonTestClient::willUpdate(
    const MqttsnWillInfo* willInfo)
{
    assert(m_libFuncs.m_willUpdateFunc != nullptr);
    return (m_libFuncs.m_willUpdateFunc)(
        m_client,
        willInfo,
        &CommonTestClient::willUpdateCompleteCallback,
        this);
}

MqttsnErrorCode CommonTestClient::willTopicUpdate(
    const std::string& topic,
    MqttsnQoS qos,
    bool retain)
{
    assert(m_libFuncs.m_willTopicUpdateFunc != nullptr);
    return (m_libFuncs.m_willTopicUpdateFunc)(
        m_client,
        topic.c_str(),
        qos,
        retain,
        &CommonTestClient::willTopicUpdateCompleteCallback,
        this);
}

MqttsnErrorCode CommonTestClient::willMsgUpdate(
    const std::uint8_t* msg,
    std::size_t msgLen)
{
    assert(m_libFuncs.m_willMsgUpdateFunc != nullptr);
    return (m_libFuncs.m_willMsgUpdateFunc)(
        m_client,
        msg,
        msgLen,
        &CommonTestClient::willMsgUpdateCompleteCallback,
        this);
}

MqttsnErrorCode CommonTestClient::sleep(std::uint16_t duration)
{
    assert(m_libFuncs.m_sleepFunc != nullptr);
    return (m_libFuncs.m_sleepFunc)(
        m_client,
        duration,
        &CommonTestClient::sleepCompleteCallback,
        this);
}

MqttsnErrorCode CommonTestClient::checkMessages()
{
    assert(m_libFuncs.m_checkMessagesFunc != nullptr);
    return (m_libFuncs.m_checkMessagesFunc)(
        m_client,
        &CommonTestClient::checkMessagesCompleteCallback,
        this);
}

MqttsnQoS CommonTestClient::transformQos(mqttsn::protocol::field::QosType val)
{
    static_assert(
        (int)mqttsn::protocol::field::QosType::AtMostOnceDelivery == MqttsnQoS_AtMostOnceDelivery,
        "Invalid mapping");

    static_assert(
        (int)mqttsn::protocol::field::QosType::AtLeastOnceDelivery == MqttsnQoS_AtLeastOnceDelivery,
        "Invalid mapping");

    static_assert(
        (int)mqttsn::protocol::field::QosType::ExactlyOnceDelivery == MqttsnQoS_ExactlyOnceDelivery,
        "Invalid mapping");

    if (val == mqttsn::protocol::field::QosType::NoGwPublish) {
        return MqttsnQoS_NoGwPublish;
    }

    return static_cast<MqttsnQoS>(val);
}

mqttsn::protocol::field::QosType CommonTestClient::transformQos(MqttsnQoS val)
{

    if (val == MqttsnQoS_NoGwPublish) {
        return mqttsn::protocol::field::QosType::NoGwPublish;
    }

    return static_cast<mqttsn::protocol::field::QosType>(val);
}

CommonTestClient::CommonTestClient(const ClientLibFuncs& libFuncs)
  : m_libFuncs(libFuncs),
    m_client((libFuncs.m_newFunc)())
{
    assert(m_libFuncs.m_nextTickProgramCallbackSetFunc != nullptr);
    assert(m_libFuncs.m_cancelNextTickCallbackSetFunc != nullptr);
    assert(m_libFuncs.m_sentOutDataCallbackSetFunc != nullptr);
    assert(m_libFuncs.m_gwStatusReportCallbackSetFunc != nullptr);
    assert(m_libFuncs.m_connectionStatusReportCallbackSetFunc != nullptr);
    assert(m_libFuncs.m_msgReportCallbackSetFunc != nullptr);

    (m_libFuncs.m_nextTickProgramCallbackSetFunc)(m_client, &CommonTestClient::nextTickProgramCallback, this);
    (m_libFuncs.m_cancelNextTickCallbackSetFunc)(m_client, &CommonTestClient::cancelNextTickCallback, this);
    (m_libFuncs.m_sentOutDataCallbackSetFunc)(m_client, &CommonTestClient::sendOutputDataCallback, this);
    (m_libFuncs.m_gwStatusReportCallbackSetFunc)(m_client, &CommonTestClient::gwStatusReportCallback, this);
    (m_libFuncs.m_connectionStatusReportCallbackSetFunc)(m_client, &CommonTestClient::connectionStatusReportCallback, this);
    (m_libFuncs.m_msgReportCallbackSetFunc)(m_client, &CommonTestClient::msgReportCallback, this);
    // TODO: callbacks
}

void CommonTestClient::programNextTick(unsigned duration)
{
    if (m_programNextTickCallback) {
        ProgramNextTickCallback tmp(m_programNextTickCallback);
        tmp(duration);
    }
}

unsigned CommonTestClient::cancelNextTick()
{
    if (m_cancelNextTickCallback) {
        CancelNextTickCallback tmp(m_cancelNextTickCallback);
        return tmp();
    }

    assert(!"Should not happen");
    return 0;
}

void CommonTestClient::sendOutputData(const unsigned char* buf, unsigned bufLen, bool broadcast)
{
    if (m_sendDataCallback) {
        SendDataCallback tmp(m_sendDataCallback);
        tmp(buf, bufLen, broadcast);
    }
}

void CommonTestClient::reportGwStatus(unsigned short gwId, MqttsnGwStatus status)
{
    if (m_gwStatusReportCallback) {
        GwStatusReportCallback tmp(m_gwStatusReportCallback);
        tmp(gwId, status);
    }
}

void CommonTestClient::reportConnectionStatus(MqttsnConnectionStatus status)
{
    if (m_connectionStatusReportCallback) {
        ConnectionStatusReportCallback tmp(m_connectionStatusReportCallback);
        tmp(status);
    }
}

void CommonTestClient::reportMessage(const MqttsnMessageInfo* msgInfo)
{
    if (m_msgReportCallback) {
        assert(msgInfo != nullptr);
        MessageReportCallback tmp(m_msgReportCallback);
        tmp(*msgInfo);
    }
}

void CommonTestClient::reportPublishComplete(MqttsnAsyncOpStatus status)
{
    if (m_publishCompleteCallback) {
        PublishCompleteCallback tmp(m_publishCompleteCallback);
        tmp(status);
    }
}

void CommonTestClient::reportSubsribeComplete(MqttsnAsyncOpStatus status, MqttsnQoS qos)
{
    if (m_subscribeCompleteCallback) {
        SubscribeCompleteCallback tmp(m_subscribeCompleteCallback);
        tmp(status, qos);
    }
}

void CommonTestClient::reportUnsubsribeComplete(MqttsnAsyncOpStatus status)
{
    if (m_unsubscribeCompleteCallback) {
        UnsubscribeCompleteCallback tmp(m_unsubscribeCompleteCallback);
        tmp(status);
    }
}

void CommonTestClient::reportWillUpdateComplete(MqttsnAsyncOpStatus status)
{
    if (m_willUpdateCompleteCallback) {
        WillUpdateCompleteCallback tmp(m_willUpdateCompleteCallback);
        tmp(status);
    }
}

void CommonTestClient::reportWillTopicUpdateComplete(MqttsnAsyncOpStatus status)
{
    if (m_willTopicUpdateCompleteCallback) {
        WillTopicUpdateCompleteCallback tmp(m_willTopicUpdateCompleteCallback);
        tmp(status);
    }
}

void CommonTestClient::reportWillMsgUpdateComplete(MqttsnAsyncOpStatus status)
{
    if (m_willMsgUpdateCompleteCallback) {
        WillMsgUpdateCompleteCallback tmp(m_willMsgUpdateCompleteCallback);
        tmp(status);
    }
}

void CommonTestClient::reportSleepComplete(MqttsnAsyncOpStatus status)
{
    if (m_sleepCompleteCallback) {
        SleepCompleteCallback tmp(m_sleepCompleteCallback);
        tmp(status);
    }
}

void CommonTestClient::reportCheckMessagesComplete(MqttsnAsyncOpStatus status)
{
    if (m_checkMessagesCompleteCallback) {
        CheckMessagesCompleteCallback tmp(m_checkMessagesCompleteCallback);
        tmp(status);
    }
}

void CommonTestClient::nextTickProgramCallback(void* data, unsigned duration)
{
    assert(data != nullptr);
    reinterpret_cast<CommonTestClient*>(data)->programNextTick(duration);
}

unsigned CommonTestClient::cancelNextTickCallback(void* data)
{
    assert(data != nullptr);
    return reinterpret_cast<CommonTestClient*>(data)->cancelNextTick();
}

void CommonTestClient::sendOutputDataCallback(
    void* data,
    const unsigned char* buf,
    unsigned bufLen,
    bool broadcast)
{
    assert(data != nullptr);
    reinterpret_cast<CommonTestClient*>(data)->sendOutputData(buf, bufLen, broadcast);
}

void CommonTestClient::gwStatusReportCallback(
    void* data,
    unsigned short gwId,
    MqttsnGwStatus status)
{
    assert(data != nullptr);
    reinterpret_cast<CommonTestClient*>(data)->reportGwStatus(gwId, status);
}

void CommonTestClient::connectionStatusReportCallback(void* data, MqttsnConnectionStatus status)
{
    assert(data != nullptr);
    reinterpret_cast<CommonTestClient*>(data)->reportConnectionStatus(status);
}

void CommonTestClient::msgReportCallback(void* data, const MqttsnMessageInfo* msgInfo)
{
    assert(data != nullptr);
    reinterpret_cast<CommonTestClient*>(data)->reportMessage(msgInfo);
}

void CommonTestClient::publishCompleteCallback(void* data, MqttsnAsyncOpStatus status)
{
    assert(data != nullptr);
    reinterpret_cast<CommonTestClient*>(data)->reportPublishComplete(status);
}

void CommonTestClient::subsribeCompleteCallback(void* data, MqttsnAsyncOpStatus status, MqttsnQoS qos)
{
    assert(data != nullptr);
    reinterpret_cast<CommonTestClient*>(data)->reportSubsribeComplete(status, qos);
}

void CommonTestClient::unsubsribeCompleteCallback(void* data, MqttsnAsyncOpStatus status)
{
    assert(data != nullptr);
    reinterpret_cast<CommonTestClient*>(data)->reportUnsubsribeComplete(status);
}

void CommonTestClient::willUpdateCompleteCallback(void* data, MqttsnAsyncOpStatus status)
{
    assert(data != nullptr);
    reinterpret_cast<CommonTestClient*>(data)->reportWillUpdateComplete(status);
}

void CommonTestClient::willTopicUpdateCompleteCallback(void* data, MqttsnAsyncOpStatus status)
{
    assert(data != nullptr);
    reinterpret_cast<CommonTestClient*>(data)->reportWillTopicUpdateComplete(status);
}

void CommonTestClient::willMsgUpdateCompleteCallback(void* data, MqttsnAsyncOpStatus status)
{
    assert(data != nullptr);
    reinterpret_cast<CommonTestClient*>(data)->reportWillMsgUpdateComplete(status);
}

void CommonTestClient::sleepCompleteCallback(void* data, MqttsnAsyncOpStatus status)
{
    assert(data != nullptr);
    reinterpret_cast<CommonTestClient*>(data)->reportSleepComplete(status);
}

void CommonTestClient::checkMessagesCompleteCallback(void* data, MqttsnAsyncOpStatus status)
{
    assert(data != nullptr);
    reinterpret_cast<CommonTestClient*>(data)->reportCheckMessagesComplete(status);
}
