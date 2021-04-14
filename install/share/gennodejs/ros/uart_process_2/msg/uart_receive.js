// Auto-generated. Do not edit!

// (in-package uart_process_2.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class uart_receive {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.yaw = null;
      this.pitch = null;
      this.mod = null;
      this.red_blue = null;
      this.shoot_speed_mod = null;
    }
    else {
      if (initObj.hasOwnProperty('yaw')) {
        this.yaw = initObj.yaw
      }
      else {
        this.yaw = 0.0;
      }
      if (initObj.hasOwnProperty('pitch')) {
        this.pitch = initObj.pitch
      }
      else {
        this.pitch = 0.0;
      }
      if (initObj.hasOwnProperty('mod')) {
        this.mod = initObj.mod
      }
      else {
        this.mod = 0;
      }
      if (initObj.hasOwnProperty('red_blue')) {
        this.red_blue = initObj.red_blue
      }
      else {
        this.red_blue = 0;
      }
      if (initObj.hasOwnProperty('shoot_speed_mod')) {
        this.shoot_speed_mod = initObj.shoot_speed_mod
      }
      else {
        this.shoot_speed_mod = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type uart_receive
    // Serialize message field [yaw]
    bufferOffset = _serializer.float32(obj.yaw, buffer, bufferOffset);
    // Serialize message field [pitch]
    bufferOffset = _serializer.float32(obj.pitch, buffer, bufferOffset);
    // Serialize message field [mod]
    bufferOffset = _serializer.uint8(obj.mod, buffer, bufferOffset);
    // Serialize message field [red_blue]
    bufferOffset = _serializer.uint8(obj.red_blue, buffer, bufferOffset);
    // Serialize message field [shoot_speed_mod]
    bufferOffset = _serializer.uint8(obj.shoot_speed_mod, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type uart_receive
    let len;
    let data = new uart_receive(null);
    // Deserialize message field [yaw]
    data.yaw = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [pitch]
    data.pitch = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [mod]
    data.mod = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [red_blue]
    data.red_blue = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [shoot_speed_mod]
    data.shoot_speed_mod = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 11;
  }

  static datatype() {
    // Returns string type for a message object
    return 'uart_process_2/uart_receive';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9eb1c17f9d76fdce5a06ed519a258d0d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 yaw
    float32 pitch
    uint8 mod
    uint8 red_blue
    uint8 shoot_speed_mod
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new uart_receive(null);
    if (msg.yaw !== undefined) {
      resolved.yaw = msg.yaw;
    }
    else {
      resolved.yaw = 0.0
    }

    if (msg.pitch !== undefined) {
      resolved.pitch = msg.pitch;
    }
    else {
      resolved.pitch = 0.0
    }

    if (msg.mod !== undefined) {
      resolved.mod = msg.mod;
    }
    else {
      resolved.mod = 0
    }

    if (msg.red_blue !== undefined) {
      resolved.red_blue = msg.red_blue;
    }
    else {
      resolved.red_blue = 0
    }

    if (msg.shoot_speed_mod !== undefined) {
      resolved.shoot_speed_mod = msg.shoot_speed_mod;
    }
    else {
      resolved.shoot_speed_mod = 0
    }

    return resolved;
    }
};

module.exports = uart_receive;
