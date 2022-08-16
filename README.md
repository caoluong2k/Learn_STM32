# Soft_UART_STM32
<p> Project này được triển khai trên kit STM32F103C8T6. <br>
<p> Thư viện chính được đặt trong folder (https://github.com/caoluong2k/Soft_UART_STM32/tree/main/Soft_UART_Lite) <br>
<p> Thư viện dùng cho việc truyền dữ liệu, có thể sử dụng bất cứ chân nào của STM32F13C8T6 để truyền dữ liệu <br>
## Xử lý Baudrate
<p> Hàm `SoftUartHandler` được gọi sau 1/Baudrate (second) thông qua ngắt của TIMER
## Cấu hình TIMER
<p> Timer clock: 72 MHz. <br>
<p> Counter Period (AutoReload Register - 16 bits value ) : 49 <br>
<p> Tim global interrupt: enable <br>

  **Note**
<p> Để chọn baudrate, chế độ stop bit, chiều dài data ta chỉ cần sửa các lệnh `#define` trong file `Soft_UART_Lite.h`.
<p> Để thay đổi nội dung bản tin ta sửa trong file `main.h`. <r>
