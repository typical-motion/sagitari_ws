
(cl:in-package :asdf)

(defsystem "uart_process_2-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "uart_receive" :depends-on ("_package_uart_receive"))
    (:file "_package_uart_receive" :depends-on ("_package"))
    (:file "uart_send" :depends-on ("_package_uart_send"))
    (:file "_package_uart_send" :depends-on ("_package"))
  ))