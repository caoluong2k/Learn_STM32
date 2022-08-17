# Soft_UART_STM32
<p> Project này được triển khai trên kit STM32F103C8T6. <br>
<p> Thư viện chính được đặt trong folder <a href="https://github.com/caoluong2k/Soft_UART_STM32/tree/main/Soft_UART_Lite" title=" The best blog ever">Soft_UART_Lite</a> <br>
<p> Thư viện dùng cho việc truyền dữ liệu, có thể sử dụng bất cứ chân nào của STM32F13C8T6 để truyền dữ liệu <br>
<h2> Xử lý Baudrate và thiết lập các thông số UART 2</h1>
<p> Hàm <code>SoftUartHandler</code> được gọi sau 1/Baudrate (second) thông qua ngắt của TIMER
<p> Để điều chỉnh các thống số như baudrate, data length, stop bit, chọn chân TX ta chỉ cần sửa đổi các lệnh <code>#define</code> trong file <a href="https://github.com/caoluong2k/Soft_UART_STM32/blob/main/Soft_UART_Lite/Soft_UART_Lite_Inc/Soft_UART_Lite.h" title=" The best blog ever">Soft_UART_Lite.h</a>
<h2> Cấu hình TIMER 2</h1>
<p> Timer clock: 72 MHz. <br>
<p> Counter Period (AutoReload Register - 16 bits value ) : 49 <br>
<p> Tim global interrupt: enable <br>

<h2> Note 2</h1>
<p> Để thay đổi nội dung bản tin ta sửa trong file <code>main.h</code>. <r>
<p> Chi tiết quá trình thực hiện, file báo cáo và kết quả mọi người có thể liên hệ mình: <code>caoluong522000@gmail.com</code> .<br>
<p> Tuy nhiên, mình vẫn chưa giải quyết được vấn đề truyền data trên nhiều nhiều chân cùng lúc (1 chân truyền đi được đúng bản tin, các chân còn lại bản tin truyền đi bị sai)
<p> Project này dựa trên project của https://github.com/liyanboy74, mình chỉnh sửa thêm để phù hợp với bài tập lớn môn Nhúng của mình <br>
