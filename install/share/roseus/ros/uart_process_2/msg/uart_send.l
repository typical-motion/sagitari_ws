;; Auto-generated. Do not edit!


(when (boundp 'uart_process_2::uart_send)
  (if (not (find-package "UART_PROCESS_2"))
    (make-package "UART_PROCESS_2"))
  (shadow 'uart_send (find-package "UART_PROCESS_2")))
(unless (find-package "UART_PROCESS_2::UART_SEND")
  (make-package "UART_PROCESS_2::UART_SEND"))

(in-package "ROS")
;;//! \htmlinclude uart_send.msg.html


(defclass uart_process_2::uart_send
  :super ros::object
  :slots (_xdata _ydata _zdata _tdata _Cmdata ))

(defmethod uart_process_2::uart_send
  (:init
   (&key
    ((:xdata __xdata) 0.0)
    ((:ydata __ydata) 0.0)
    ((:zdata __zdata) 0.0)
    ((:tdata __tdata) 0.0)
    ((:Cmdata __Cmdata) 0)
    )
   (send-super :init)
   (setq _xdata (float __xdata))
   (setq _ydata (float __ydata))
   (setq _zdata (float __zdata))
   (setq _tdata (float __tdata))
   (setq _Cmdata (round __Cmdata))
   self)
  (:xdata
   (&optional __xdata)
   (if __xdata (setq _xdata __xdata)) _xdata)
  (:ydata
   (&optional __ydata)
   (if __ydata (setq _ydata __ydata)) _ydata)
  (:zdata
   (&optional __zdata)
   (if __zdata (setq _zdata __zdata)) _zdata)
  (:tdata
   (&optional __tdata)
   (if __tdata (setq _tdata __tdata)) _tdata)
  (:Cmdata
   (&optional __Cmdata)
   (if __Cmdata (setq _Cmdata __Cmdata)) _Cmdata)
  (:serialization-length
   ()
   (+
    ;; float32 _xdata
    4
    ;; float32 _ydata
    4
    ;; float32 _zdata
    4
    ;; float32 _tdata
    4
    ;; uint8 _Cmdata
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _xdata
       (sys::poke _xdata (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _ydata
       (sys::poke _ydata (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _zdata
       (sys::poke _zdata (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _tdata
       (sys::poke _tdata (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint8 _Cmdata
       (write-byte _Cmdata s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _xdata
     (setq _xdata (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _ydata
     (setq _ydata (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _zdata
     (setq _zdata (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _tdata
     (setq _tdata (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint8 _Cmdata
     (setq _Cmdata (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get uart_process_2::uart_send :md5sum-) "128b179fa20ccd12168b588fea92e3a7")
(setf (get uart_process_2::uart_send :datatype-) "uart_process_2/uart_send")
(setf (get uart_process_2::uart_send :definition-)
      "float32 xdata
float32 ydata
float32 zdata
float32 tdata
uint8 Cmdata
")



(provide :uart_process_2/uart_send "128b179fa20ccd12168b588fea92e3a7")


