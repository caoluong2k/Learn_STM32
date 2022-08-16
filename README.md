# Soft_UART_STM32
<p> Project này được triển khai trên kit STM32F103C8T6. <r>
<p> Thư viện chính được đặt trong folder https://github.com/caoluong2k/Soft_UART_STM32/tree/main/Soft_UART_Lite <r>
<p> Thư viện dùng cho việc truyền dữ liệu, có thể sử dụng bất cứ chân nào của STM32F13C8T6 để truyền dữ liệu <r>

## Xử lý Baudrate
<p> Hàm `SoftUartHandler` được gọi sau 1/Baudrate (second) thông qua ngắt của TIMER <r>
