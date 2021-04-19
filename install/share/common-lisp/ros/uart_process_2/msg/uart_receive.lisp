; Auto-generated. Do not edit!


(cl:in-package uart_process_2-msg)


;//! \htmlinclude uart_receive.msg.html

(cl:defclass <uart_receive> (roslisp-msg-protocol:ros-message)
  ((yaw
    :reader yaw
    :initarg :yaw
    :type cl:float
    :initform 0.0)
   (pitch
    :reader pitch
    :initarg :pitch
    :type cl:float
    :initform 0.0)
   (mod
    :reader mod
    :initarg :mod
    :type cl:fixnum
    :initform 0)
   (red_blue
    :reader red_blue
    :initarg :red_blue
    :type cl:fixnum
    :initform 0)
   (shoot_speed_mod
    :reader shoot_speed_mod
    :initarg :shoot_speed_mod
    :type cl:fixnum
    :initform 0))
)

(cl:defclass uart_receive (<uart_receive>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <uart_receive>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'uart_receive)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name uart_process_2-msg:<uart_receive> is deprecated: use uart_process_2-msg:uart_receive instead.")))

(cl:ensure-generic-function 'yaw-val :lambda-list '(m))
(cl:defmethod yaw-val ((m <uart_receive>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uart_process_2-msg:yaw-val is deprecated.  Use uart_process_2-msg:yaw instead.")
  (yaw m))

(cl:ensure-generic-function 'pitch-val :lambda-list '(m))
(cl:defmethod pitch-val ((m <uart_receive>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uart_process_2-msg:pitch-val is deprecated.  Use uart_process_2-msg:pitch instead.")
  (pitch m))

(cl:ensure-generic-function 'mod-val :lambda-list '(m))
(cl:defmethod mod-val ((m <uart_receive>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uart_process_2-msg:mod-val is deprecated.  Use uart_process_2-msg:mod instead.")
  (mod m))

(cl:ensure-generic-function 'red_blue-val :lambda-list '(m))
(cl:defmethod red_blue-val ((m <uart_receive>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uart_process_2-msg:red_blue-val is deprecated.  Use uart_process_2-msg:red_blue instead.")
  (red_blue m))

(cl:ensure-generic-function 'shoot_speed_mod-val :lambda-list '(m))
(cl:defmethod shoot_speed_mod-val ((m <uart_receive>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uart_process_2-msg:shoot_speed_mod-val is deprecated.  Use uart_process_2-msg:shoot_speed_mod instead.")
  (shoot_speed_mod m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <uart_receive>) ostream)
  "Serializes a message object of type '<uart_receive>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'yaw))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'pitch))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'mod)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'red_blue)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'shoot_speed_mod)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <uart_receive>) istream)
  "Deserializes a message object of type '<uart_receive>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'yaw) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'pitch) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'mod)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'red_blue)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'shoot_speed_mod)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<uart_receive>)))
  "Returns string type for a message object of type '<uart_receive>"
  "uart_process_2/uart_receive")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'uart_receive)))
  "Returns string type for a message object of type 'uart_receive"
  "uart_process_2/uart_receive")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<uart_receive>)))
  "Returns md5sum for a message object of type '<uart_receive>"
  "9eb1c17f9d76fdce5a06ed519a258d0d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'uart_receive)))
  "Returns md5sum for a message object of type 'uart_receive"
  "9eb1c17f9d76fdce5a06ed519a258d0d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<uart_receive>)))
  "Returns full string definition for message of type '<uart_receive>"
  (cl:format cl:nil "float32 yaw~%float32 pitch~%uint8 mod~%uint8 red_blue~%uint8 shoot_speed_mod~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'uart_receive)))
  "Returns full string definition for message of type 'uart_receive"
  (cl:format cl:nil "float32 yaw~%float32 pitch~%uint8 mod~%uint8 red_blue~%uint8 shoot_speed_mod~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <uart_receive>))
  (cl:+ 0
     4
     4
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <uart_receive>))
  "Converts a ROS message object to a list"
  (cl:list 'uart_receive
    (cl:cons ':yaw (yaw msg))
    (cl:cons ':pitch (pitch msg))
    (cl:cons ':mod (mod msg))
    (cl:cons ':red_blue (red_blue msg))
    (cl:cons ':shoot_speed_mod (shoot_speed_mod msg))
))
