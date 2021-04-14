;; Auto-generated. Do not edit!


(when (boundp 'uart_process_2::uart_receive)
  (if (not (find-package "UART_PROCESS_2"))
    (make-package "UART_PROCESS_2"))
  (shadow 'uart_receive (find-package "UART_PROCESS_2")))
(unless (find-package "UART_PROCESS_2::UART_RECEIVE")
  (make-package "UART_PROCESS_2::UART_RECEIVE"))

(in-package "ROS")
;;//! \htmlinclude uart_receive.msg.html


(defclass uart_process_2::uart_receive
  :super ros::object
  :slots (_yaw _pitch _mod _red_blue _shoot_speed_mod ))

(defmethod uart_process_2::uart_receive
  (:init
   (&key
    ((:yaw __yaw) 0.0)
    ((:pitch __pitch) 0.0)
    ((:mod __mod) 0)
    ((:red_blue __red_blue) 0)
    ((:shoot_speed_mod __shoot_speed_mod) 0)
    )
   (send-super :init)
   (setq _yaw (float __yaw))
   (setq _pitch (float __pitch))
   (setq _mod (round __mod))
   (setq _red_blue (round __red_blue))
   (setq _shoot_speed_mod (round __shoot_speed_mod))
   self)
  (:yaw
   (&optional __yaw)
   (if __yaw (setq _yaw __yaw)) _yaw)
  (:pitch
   (&optional __pitch)
   (if __pitch (setq _pitch __pitch)) _pitch)
  (:mod
   (&optional __mod)
   (if __mod (setq _mod __mod)) _mod)
  (:red_blue
   (&optional __red_blue)
   (if __red_blue (setq _red_blue __red_blue)) _red_blue)
  (:shoot_speed_mod
   (&optional __shoot_speed_mod)
   (if __shoot_speed_mod (setq _shoot_speed_mod __shoot_speed_mod)) _shoot_speed_mod)
  (:serialization-length
   ()
   (+
    ;; float32 _yaw
    4
    ;; float32 _pitch
    4
    ;; uint8 _mod
    1
    ;; uint8 _red_blue
    1
    ;; uint8 _shoot_speed_mod
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _yaw
       (sys::poke _yaw (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _pitch
       (sys::poke _pitch (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint8 _mod
       (write-byte _mod s)
     ;; uint8 _red_blue
       (write-byte _red_blue s)
     ;; uint8 _shoot_speed_mod
       (write-byte _shoot_speed_mod s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _yaw
     (setq _yaw (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _pitch
     (setq _pitch (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint8 _mod
     (setq _mod (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _red_blue
     (setq _red_blue (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _shoot_speed_mod
     (setq _shoot_speed_mod (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get uart_process_2::uart_receive :md5sum-) "9eb1c17f9d76fdce5a06ed519a258d0d")
(setf (get uart_process_2::uart_receive :datatype-) "uart_process_2/uart_receive")
(setf (get uart_process_2::uart_receive :definition-)
      "float32 yaw
float32 pitch
uint8 mod
uint8 red_blue
uint8 shoot_speed_mod
")



(provide :uart_process_2/uart_receive "9eb1c17f9d76fdce5a06ed519a258d0d")


