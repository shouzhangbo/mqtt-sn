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


#pragma once

#include "comms/comms.h"
#include "mqttsn/protocol/MsgTypeId.h"
#include "mqttsn/protocol/field.h"

namespace mqttsn
{

namespace protocol
{

namespace message
{

template <typename TFieldBase>
using PubrecFields =
    std::tuple<
        field::MsgId<TFieldBase>
    >;

template <typename TMsgBase, template<class> class TActual>
using PubrecBase =
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgTypeId_PUBREC>,
        comms::option::FieldsImpl<PubrecFields<typename TMsgBase::Field> >,
        comms::option::MsgType<TActual<TMsgBase> >
    >;

template <typename TMsgBase>
class Pubrec : public PubrecBase<TMsgBase, Pubrec>
{
    typedef PubrecBase<TMsgBase, mqttsn::protocol::message::Pubrec> Base;

public:
    COMMS_MSG_FIELDS_ACCESS(Base, msgId);
};

}  // namespace message

}  // namespace protocol

}  // namespace mqttsn


