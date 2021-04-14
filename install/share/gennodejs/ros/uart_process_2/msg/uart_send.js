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

class uart_send {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.xdata = null;
      this.ydata = null;
      this.zdata = null;
      this.tdata = null;
      this.Cmdata = null;
    }
    else {
      if (initObj.hasOwnProperty('xdata')) {
        this.xdata = initObj.xdata
      }
      else {
        this.xdata = 0.0;
      }
      if (initObj.hasOwnProperty('ydata')) {
        this.ydata = initObj.ydata
      }
      else {
        this.ydata = 0.0;
      }
      if (initObj.hasOwnProperty('zdata')) {
        this.zdata = initObj.zdata
      }
      else {
        this.zdata = 0.0;
      }
      if (initObj.hasOwnProperty('tdata')) {
        this.tdata = initObj.tdata
      }
      else {
        this.tdata = 0.0;
      }
      if (initObj.hasOwnProperty('Cmdata')) {
        this.Cmdata = initObj.Cmdata
      }
      else {
        this.Cmdata = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type uart_send
    // Serialize message field [xdata]
    bufferOffset = _serializer.float32(obj.xdata, buffer, bufferOffset);
    // Serialize message field [ydata]
    bufferOffset = _serializer.float32(obj.ydata, buffer, bufferOffset);
    // Serialize message field [zdata]
    bufferOffset = _serializer.float32(obj.zdata, buffer, bufferOffset);
    // Serialize message field [tdata]
    bufferOffset = _serializer.float32(obj.tdata, buffer, bufferOffset);
    // Serialize message field [Cmdata]
    bufferOffset = _serializer.uint8(obj.Cmdata, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type uart_send
    let len;
    let data = new uart_send(null);
    // Deserialize message field [xdata]
    data.xdata = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [ydata]
    data.ydata = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [zdata]
    data.zdata = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [tdata]
    data.tdata = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [Cmdata]
    data.Cmdata = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 17;
  }

  static datatype() {
    // Returns string type for a message object
    return 'uart_process_2/uart_send';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '128b179fa20ccd12168b588fea92e3a7';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 xdata
    float32 ydata
    float32 zdata
    float32 tdata
    uint8 Cmdata
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new uart_send(null);
    if (msg.xdata !== undefined) {
      resolved.xdata = msg.xdata;
    }
    else {
      resolved.xdata = 0.0
    }

    if (msg.ydata !== undefined) {
      resolved.ydata = msg.ydata;
    }
    else {
      resolved.ydata = 0.0
    }

    if (msg.zdata !== undefined) {
      resolved.zdata = msg.zdata;
    }
    else {
      resolved.zdata = 0.0
    }

    if (msg.tdata !== undefined) {
      resolved.tdata = msg.tdata;
    }
    else {
      resolved.tdata = 0.0
    }

    if (msg.Cmdata !== undefined) {
      resolved.Cmdata = msg.Cmdata;
    }
    else {
      resolved.Cmdata = 0
    }

    return resolved;
    }
};

module.exports = uart_send;
