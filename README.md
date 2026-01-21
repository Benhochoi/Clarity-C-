# 🏪 Hệ Thống Quản Lý Siêu Thị

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Version](https://img.shields.io/badge/version-1.0.0-green.svg)
![Status](https://img.shields.io/badge/status-active-success.svg)

---

## 📖 Mô Tả Dự Án

**Hệ Thống Quản Lý Siêu Thị** là một ứng dụng console được phát triển bằng C++ nhằm hỗ trợ quản lý toàn diện các hoạt động của một siêu thị/cửa hàng bán lẻ. Dự án được xây dựng theo mô hình hướng đối tượng (OOP) với đầy đủ các tính năng quản lý cơ bản.

### ✨ Tính Năng Chính

- 👥 **Quản Lý Khách Hàng**: Thêm, sửa, xóa, tìm kiếm thông tin khách hàng
- 👔 **Quản Lý Nhân Viên**: Quản lý hồ sơ nhân viên, lương, chức vụ, ngày vào làm
- 🏢 **Quản Lý Nhà Cung Cấp**: Quản lý thông tin NCC, theo dõi giao dịch nhập hàng
- 📦 **Quản Lý Hàng Hóa**: Theo dõi tồn kho, giá bán, giảm giá, hạn sử dụng
- 🧾 **Quản Lý Hóa Đơn**: Tạo hóa đơn, thanh toán, theo dõi doanh thu
- 📊 **Thống Kê & Báo Cáo**: Doanh thu theo ngày, hàng bán chạy, tồn kho, giá trị theo NCC

### 🎯 Lý Do Chọn Công Nghệ

- **C++ với OOP**: Áp dụng đầy đủ các tính chất kế thừa, đóng gói, đa hình
- **STL (Standard Template Library)**: Sử dụng `vector`, `string`, `fstream` để quản lý dữ liệu hiệu quả
- **File-based Storage**: Lưu trữ dữ liệu dạng CSV, dễ dàng backup và di chuyển
- **Validation**: Hệ thống kiểm tra dữ liệu đầu vào nghiêm ngặt (email, số điện thoại, ngày tháng...)

### 🚧 Thách Thức & Kế Hoạch Tương Lai

**Thách thức đã giải quyết:**
- ✅ Xử lý nhập liệu sai từ người dùng (số âm, ký tự đặc biệt, định dạng sai)
- ✅ Đồng bộ dữ liệu giữa các module (khách hàng - hóa đơn, hàng hóa - nhà cung cấp)
- ✅ Tránh xóa dữ liệu liên quan (cascade delete prevention)
- ✅ Tính toán giá bán tự động (markup 30% từ giá nhập)

**Dự định phát triển:**
- 🔄 Chuyển sang database (SQLite/MySQL)
- 🔐 Hệ thống phân quyền người dùng (Admin, Quản lý, Nhân viên)
- 📱 Xây dựng GUI (Qt/wxWidgets)
- 📈 Biểu đồ thống kê trực quan
- 🔍 Tìm kiếm nâng cao với filters
- 📤 Xuất báo cáo PDF/Excel

---

## 📑 Mục Lục

- [Mô Tả Dự Án](#-mô-tả-dự-án)
- [Cài Đặt & Thiết Lập](#-cài-đặt--thiết-lập)
- [Cách Sử Dụng](#-cách-sử-dụng)
- [Cấu Trúc Dự Án](#-cấu-trúc-dự-án)
- [Các Tính Năng Chi Tiết](#-các-tính-năng-chi-tiết)
- [Đóng Góp](#-đóng-góp)
- [Thành Viên](#-thành-viên)
- [Giấy Phép](#-giấy-phép)

---

## 🛠 Cài Đặt & Thiết Lập

### Yêu Cầu Hệ Thống

- **Compiler**: GCC/G++ 7.0+ hoặc Visual Studio 2017+
- **C++ Standard**: C++11 trở lên
- **OS**: Windows, Linux, macOS

### Các Bước Cài Đặt

1. **Clone repository về máy:**

```bash
git clone https://github.com/[TODO-username]/quan-ly-sieu-thi.git
cd quan-ly-sieu-thi
```

2. **Biên dịch chương trình:**

**Trên Linux/macOS:**
```bash
g++ -std=c++11 "Quan ly sieu thi.cpp" -o QuanLySieuThi
```

**Trên Windows (MinGW):**
```bash
g++ -std=c++11 "Quan ly sieu thi.cpp" -o QuanLySieuThi.exe
```

**Trên Visual Studio:**
- Mở file `.cpp` bằng Visual Studio
- Nhấn `Ctrl+F5` hoặc chọn `Debug > Start Without Debugging`

3. **Chạy chương trình:**

**Linux/macOS:**
```bash
./QuanLySieuThi
```

**Windows:**
```bash
QuanLySieuThi.exe
```

---

## 🚀 Cách Sử Dụng

### Đăng Nhập

Khi khởi động, hệ thống yêu cầu nhập mật khẩu:

```
=====================================================
            DANG NHAP HE THONG QUAN LY               
=====================================================

Nhap mat khau (Lan thu 1/3): ********
```

**Mật khẩu mặc định:** `admin123`

> ⚠️ **Lưu ý:** Bạn có tối đa 3 lần thử. Sai quá 3 lần, chương trình sẽ tự động thoát.

### Menu Chính

Sau khi đăng nhập thành công, bạn sẽ thấy menu chính:

```
=====================================================
                 HE THONG QUAN LY                    
=====================================================
  [1]  Quan ly Khach hang
  [2]  Quan ly Nhan vien
  [3]  Quan ly Nha cung cap
  [4]  Quan ly Hang hoa
  [5]  Quan ly Hoa don
  [6]  Thong ke
  [0]  Thoat chuong trinh
-----------------------------------------------------
```

### Ví Dụ Workflow Điển Hình

1. **Thêm Nhà Cung Cấp** (Menu 3 → Option 2)
2. **Nhập Hàng Hóa** (Menu 4 → Option 2) hoặc qua NCC (Menu 3 → Option giao dịch)
3. **Thêm Khách Hàng** (Menu 1 → Option 2)
4. **Tạo Hóa Đơn** (Menu 5 → Option 2)
5. **Thanh Toán** (Menu 5 → Option 5)
6. **Xem Thống Kê** (Menu 6)

### Screenshots

<!-- TODO: Thêm ảnh chụp màn hình -->
```
[TODO: Thêm ảnh minh họa giao diện menu chính]
[TODO: Thêm ảnh ví dụ về quản lý hàng hóa]
[TODO: Thêm ảnh ví dụ về hóa đơn]
```

---

## 📁 Cấu Trúc Dự Án

```
quan-ly-sieu-thi/
│
├── Quan ly sieu thi.cpp    # File source code chính
├── README.md               # File tài liệu này
│
├── khachhang.txt          # Database khách hàng (CSV)
├── nhanvien.txt           # Database nhân viên (CSV)
├── nhacungcap.txt         # Database nhà cung cấp (CSV)
├── hanghoa.txt            # Database hàng hóa (CSV)
└── hoadon.txt             # Database hóa đơn (CSV)
```

### Class Diagram (Sơ Đồ Lớp)

```
         Nguoi (Abstract)
              |
      +-------+-------+
      |               |
  KhachHang      NhanVien

  NhaCungCap     HangHoa

                HoaDon
                   |
           ChiTietHoaDon

              QuanLy
```

---

## 🔍 Các Tính Năng Chi Tiết

### 1. Quản Lý Khách Hàng
- Thêm khách hàng mới với validation (SDT không chứa ký tự chữ, không âm)
- Sửa thông tin (tên, địa chỉ, SDT)
- Xóa khách hàng (kiểm tra hóa đơn liên quan)
- Tìm kiếm theo mã

### 2. Quản Lý Nhân Viên
- Quản lý hồ sơ: tuổi (18-100), email (@), lương theo giờ
- Xem chi tiết nhân viên dạng form
- Validation nghiêm ngặt cho tất cả trường

### 3. Quản Lý Nhà Cung Cấp
- Nhập hàng trực tiếp từ NCC
- Tự động cập nhật kho hoặc thêm mặt hàng mới
- Tính tổng giá trị hàng hóa theo từng NCC
- Chi tiết thông tin liên hệ

### 4. Quản Lý Hàng Hóa
- Theo dõi tồn kho, giá nhập, giá bán (auto x1.3), giảm giá %
- Ngày nhập, hạn sử dụng (validation logic)
- Tìm kiếm theo mã/tên
- Xem hàng tồn nhiều nhất/ít nhất
- Cập nhật số lượng từ NCC

### 5. Quản Lý Hóa Đơn
- Tạo hóa đơn với nhiều mặt hàng
- Tự động tính tiền gốc, tiền giảm, thành tiền
- Sửa hóa đơn chưa thanh toán
- Thanh toán → tự động trừ tồn kho
- Ngăn xóa/sửa hóa đơn đã thanh toán

### 6. Thống Kê
- Doanh thu theo ngày/tổng thể
- Số lượng nhân viên, NCC, hàng hóa
- Hóa đơn/khách hàng trong ngày
- Tổng giá trị hàng hóa theo NCC

---

## 🤝 Đóng Góp

Mọi đóng góp đều được chào đón! Nếu bạn muốn cải thiện dự án:

1. Fork repository này
2. Tạo branch mới (`git checkout -b feature/TenTinhNang`)
3. Commit thay đổi (`git commit -m 'Thêm tính năng XYZ'`)
4. Push lên branch (`git push origin feature/TenTinhNang`)
5. Tạo Pull Request

### Quy Tắc Coding Style
- Sử dụng tiếng Việt có dấu cho tên biến/hàm (giữ tính nhất quán với code hiện tại)
- Indent: 4 spaces
- Comment đầy đủ cho các hàm quan trọng
- Tuân thủ nguyên tắc OOP

---

## 👨‍💻 Thành Viên

| Họ Tên | Vai Trò | GitHub | Email |
|--------|---------|--------|-------|
| [TODO: Tên thành viên 1] | Lead Developer | [@TODO] | [TODO@email.com] |
| [TODO: Tên thành viên 2] | Developer | [@TODO] | [TODO@email.com] |
| [TODO: Tên thành viên 3] | Tester | [@TODO] | [TODO@email.com] |

### Tài Liệu Tham Khảo
- [cppreference.com](https://en.cppreference.com/) - C++ Standard Library
- [LearnCpp.com](https://www.learncpp.com/) - OOP Concepts
- [TODO: Thêm tài liệu khác nếu có]

---

## 📄 Giấy Phép

Dự án này được phân phối dưới giấy phép **MIT License** - xem file [LICENSE](LICENSE) để biết thêm chi tiết.

```
MIT License

Copyright (c) 2025 [TODO: Tên tổ chức/cá nhân]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction...
```

---

## 📞 Liên Hệ & Hỗ Trợ

Nếu bạn gặp vấn đề hoặc có câu hỏi:

- 🐛 Báo lỗi: [Issues](https://github.com/[TODO]/issues)
- 💬 Thảo luận: [Discussions](https://github.com/[TODO]/discussions)
- 📧 Email: [TODO@email.com]

---

<div align="center">

⭐ **Nếu dự án hữu ích, đừng quên để lại một sao!** ⭐

Made with ❤️ by [TODO: Team Name]

</div>
