; Auto-generated. Do not edit!


(cl:in-package uart_process_2-msg)


;//! \htmlinclude uart_send.msg.html

(cl:defclass <uart_send> (roslisp-msg-protocol:ros-message)
  ((xdata
    :reader xdata
    :initarg :xdata
    :type cl:float
    :initform 0.0)
   (ydata
    :reader ydata
    :initarg :ydata
    :type cl:float
    :initform 0.0)
   (zdata
    :reader zdata
    :initarg :zdata
    :type cl:float
    :initform 0.0)
   (tdata
    :reader tdata
    :initarg :tdata
    :type cl:float
    :initform 0.0)
   (Cmdata
    :reader Cmdata
    :initarg :Cmdata
    :type cl:fixnum
    :initform 0))
)

(cl:defclass uart_send (<uart_send>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <uart_send>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'uart_send)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name uart_process_2-msg:<uart_send> is deprecated: use uart_process_2-msg:uart_send instead.")))

(cl:ensure-generic-function 'xdata-val :lambda-list '(m))
(cl:defmethod xdata-val ((m <uart_send>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uart_process_2-msg:xdata-val is deprecated.  Use uart_process_2-msg:xdata instead.")
  (xdata m))

(cl:ensure-generic-function 'ydata-val :lambda-list '(m))
(cl:defmethod ydata-val ((m <uart_send>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uart_process_2-msg:ydata-val is deprecated.  Use uart_process_2-msg:ydata instead.")
  (ydata m))

(cl:ensure-generic-function 'zdata-val :lambda-list '(m))
(cl:defmethod zdata-val ((m <uart_send>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uart_process_2-msg:zdata-val is deprecated.  Use uart_process_2-msg:zdata instead.")
  (zdata m))

(cl:ensure-generic-function 'tdata-val :lambda-list '(m))
(cl:defmethod tdata-val ((m <uart_send>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uart_process_2-msg:tdata-val is deprecated.  Use uart_process_2-msg:tdata instead.")
  (tdata m))

(cl:ensure-generic-function 'Cmdata-val :lambda-list '(m))
(cl:defmethod Cmdata-val ((m <uart_send>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uart_process_2-msg:Cmdata-val is deprecated.  Use uart_process_2-msg:Cmdata instead.")
  (Cmdata m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <uart_send>) ostream)
  "Serializes a message object of type '<uart_send>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'xdata))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ydata))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'zdata))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'tdata))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Cmdata)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <uart_send>) istream)
  "Deserializes a message object of type '<uart_send>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'xdata) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ydata) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'zdata) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'tdata) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Cmdata)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<uart_send>)))
  "Returns string type for a message object of type '<uart_send>"
  "uart_process_2/uart_send")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'uart_send)))
  "Returns string type for a message object of type 'uart_send"
  "uart_process_2/uart_send")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<uart_send>)))
  "Returns md5sum for a message object of type '<uart_send>"
  "128b179fa20ccd12168b588fea92e3a7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'uart_send)))
  "Returns md5sum for a message object of type 'uart_send"
  "128b179fa20ccd12168b588fea92e3a7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<uart_send>)))
  "Returns full string definition for message of type '<uart_send>"
  (cl:format cl:nil "float32 xdata~%float32 ydata~%float32 zdata~%float32 tdata~%uint8 Cmdata~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'uart_send)))
  "Returns full string definition for message of type 'uart_send"
  (cl:format cl:nil "float32 xdata~%float32 ydata~%float32 zdata~%float32 tdata~%uint8 Cmdata~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <uart_send>))
  (cl:+ 0
     4
     4
     4
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <uart_send>))
  "Converts a ROS message object to a list"
  (cl:list 'uart_send
    (cl:cons ':xdata (xdata msg))
    (cl:cons ':ydata (ydata msg))
    (cl:cons ':zdata (zdata msg))
    (cl:cons ':tdata (tdata msg))
    (cl:cons ':Cmdata (Cmdata msg))
))
