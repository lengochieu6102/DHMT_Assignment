# DHMT_Assignment
MÔ HÌNH THIẾT BỊ CƠ KHÍ ĐƠN GIẢN
Mô hình gồm sàn nhà và thiết bị cơ khí. Tham khảo hình sau:














Hình 1. Demo kết quả

Thiết bị gồm các bộ phận tạm gọi như sau: (1) Giá đỡ, (2) Bàn quay, (3) Tay quay, (4)  Thanh liên kết, (5) Chốt1, chốt 2, chốt 3 (6) Gối đỡ, (7) Thanh chữ U, (8) Thanh trượt












Hình 2. Mô hình thiết bị cơ khí

-	Giá đỡ hình chữ I được tạo bởi 3 hình hộp.
-	Bàn quay hình trụ được gắn vào giá đỡ. Khi bàn quay này quay xung quanh trục của nó  khiến cho tay quay chuyển động  khiến cho thanh liên kết chuyển động  khiến cho thanh chữ U và thanh trượt chuyển động.
-	Tay quay được gắn cố định trên bàn quay.
-	Chốt 3 là hình trụ, được gắn cố định vào giá đỡ.
-	Thanh kiên kết có thể quay xung quanh chốt 3.
-	Có 2 gối đỡ được gắn cố định vào giá đỡ. 
-	Thanh chữ U được gắn cố định vào thanh trượt.
-	Thanh trượt có thể trượt trong gối đỡ.
-	Chốt 1 và chốt 2 được cấu tạo từ một hình hộp chữ nhật và một hình trụ. Hình hộp chữ nhật có thể xoay xung quanh hình trụ.
-	Vị trí của chốt 2 có thể được điều chỉnh

Nền nhà được lát ngẫu nhiên bởi 4 loại viên gạch sau (kiểu lát nền này được gọi là Truchet Tiling, sinh viên có thể tham khảo trên mạng bằng cách tra từ khóa Truchet Tiles)



















Hình 3 - Một phần của nền nhà

III.	TƯƠNG TÁC VỚI CHƯƠNG TRÌNH

Người sử dụng tương tác với chương trình thông qua các phím bấm. Việc tương tác này nhằm mục đích điều khiển camera và chuyển động các bộ phận của robot.

1)	Điều khiển camera (Tham khảo phần IV và Lab 4) 
Trong bài tập lớn này, ta sẽ cho phép (a) điều khiển camera quay xung quanh trục Oy, (b) thay đổi độ cao của camera (so với mặt phẳng xOz), (c) thay đổi khoảng cách giữa camera với trục Oy. Đặt 3 biến:
camera_angle: Góc quay camera xung quanh trục Oy
camera_height: Chiều cao camera so với mặt phẳng xOz
	camera_dis: Khoảng cách đến trục Oy

Người sử dụng thay đổi các giá trị trên thông qua việc bấm phím. Mỗi lần thay đổi, thì các tham số của hàm gluLookAt đều được tính lại. Trong bài thực hành này, giá trị 6 tham số cuối của hàm gluLookAt được giữ cố định. Chỉ cần tính lại 3 tham số đầu, tức là 3 tham số vị trí của camera.

2)	Điều khiển thiết bị cơ khí: 
a.	Nhấn phím 1, 2 để xoay bàn quay ngược chiều (cùng chiều) kim đồng hồ.
b.	Nhấn phím 3, 4 để điều chỉnh vị trí của chốt 2
3)	Bật tắt nguồn sáng:
Nhấn phím ‘D’ hoặc ‘d’ để bật/tắt nguồn sáng thứ hai. Nguồn sáng thứ nhất luôn luôn bật.


