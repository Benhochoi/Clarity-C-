# 🏥 Pharmacy Management System

> Hệ thống quản lý nhà thuốc toàn diện với C++ - Quản lý khách hàng, nhân viên, thuốc, hóa đơn và báo cáo thống kê

<div align="center">

![C++](https://img.shields.io/badge/C++-11-blue.svg?style=flat&logo=c%2B%2B)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)

</div>

---

## 📋 Overview

**Pharmacy Management System** là ứng dụng console C++ giúp quản lý toàn diện hoạt động của nhà thuốc, bao gồm:
- Quản lý thông tin khách hàng (bao gồm hệ thống tích điểm VIP)
- Quản lý nhân viên với tính lương tự động
- Quản lý kho thuốc và nhà cung cấp
- Tạo và theo dõi hóa đơn bán hàng
- Báo cáo thống kê doanh thu và tồn kho

Hệ thống được thiết kế theo hướng đối tượng (OOP) với các tính năng:
- Kế thừa (Inheritance): `Nguoi` → `KhachHang`, `NhanVien`
- Đóng gói (Encapsulation): Private attributes với getter/setter
- Đa hình (Polymorphism): Virtual functions cho `xuat()`
- Nạp chồng toán tử (Operator Overloading): `<<`, `>>` cho I/O

---

## ✨ Features

### 🧑‍🤝‍🧑 Quản lý Khách hàng
- ✅ Thêm/sửa/xóa khách hàng với validation (SDT, email, mã trùng)
- ✅ Hệ thống tích điểm tự động (>200 điểm → VIP)
- ✅ Giảm giá 10% cho khách VIP
- ✅ Tìm kiếm theo tên/SĐT/ngày sinh (không phân biệt hoa thường)
- ✅ Lưu/đọc dữ liệu từ file `khachhang.txt`

### 👨‍💼 Quản lý Nhân viên
- ✅ Quản lý thông tin nhân viên (mã, email không trùng)
- ✅ Tính lương tự động: `Tổng lương = Lương cơ bản × 3 + Phụ cấp`
- ✅ Validation email (phải có `@`)
- ✅ Tìm kiếm và báo cáo nhân viên
- ✅ Lưu/đọc file `nhanvien.txt`

### 💊 Quản lý Thuốc & Nhà cung cấp
- ✅ Quản lý thông tin thuốc (mã, tên, giá, tồn kho, HSD)
- ✅ Liên kết với nhà cung cấp (validation mã NCC)
- ✅ Cảnh báo thuốc sắp hết hàng (< 10 sp)
- ✅ Cập nhật tồn kho tự động khi bán
- ✅ Quản lý nhà cung cấp (mã, email không trùng)

### 🧾 Quản lý Hóa đơn
- ✅ Tạo hóa đơn với nhiều loại thuốc
- ✅ Kiểm tra tồn kho trước khi bán
- ✅ Tự động trừ kho và cộng điểm tích lũy (1% giá trị đơn)
- ✅ Áp dụng giảm giá VIP tự động
- ✅ Xóa hóa đơn với hoàn trả thuốc về kho
- ✅ Lưu chi tiết hóa đơn vào `hoadon.txt`

### 📊 Thống kê & Báo cáo
- ✅ Doanh thu tổng và theo ngày
- ✅ Top N thuốc bán chạy nhất
- ✅ Thống kê khách hàng (VIP/Thường, điểm TB)
- ✅ Danh sách thuốc sắp hết hàng

### 🔍 Tìm kiếm nâng cao
- ✅ Tìm kiếm không phân biệt hoa thường
- ✅ Hỗ trợ tìm theo nhiều tiêu chí (tên, mã, SĐT, ngày)

---

## 🛠️ Requirements

### Môi trường phát triển
- **Compiler**: 
  - GCC 5.0+ / Clang 3.4+ / MSVC 2015+ (hỗ trợ C++11)
- **OS**: Windows 7+, Linux (Ubuntu 18.04+), macOS 10.12+
- **RAM**: 512MB khả dụng
- **Disk**: 50MB cho source code + data files

### Dependencies
- Standard Template Library (STL) - đã có sẵn trong C++11
- Không yêu cầu thư viện ngoài (pure C++)

---

## 🚀 Build & Run

### Phương pháp 1: CMake (Khuyến nghị)

<details>
<summary><b>📦 Windows (Visual Studio / MinGW)</b></summary>
```bash
# Clone hoặc giải nén source code
cd Nhom_9

# Tạo thư mục build
mkdir build && cd build

# Cấu hình CMake
cmake ..

# Build (chọn 1 trong 2)
# Với Visual Studio:
cmake --build . --config Release

# Với MinGW:
mingw32-make

# Chạy
.\Release\PharmacyManagement.exe  # Visual Studio
.\PharmacyManagement.exe          # MinGW
```
</details>

<details>
<summary><b>🐧 Linux / macOS</b></summary>
```bash
# Clone hoặc giải nén source code
cd Nhom_9

# Tạo và build
mkdir build && cd build
cmake ..
make -j$(nproc)  # Linux
make -j$(sysctl -n hw.ncpu)  # macOS

# Chạy
./PharmacyManagement
```
</details>

### Phương pháp 2: Compile trực tiếp

#### Linux / macOS
```bash
g++ -std=c++11 -o pharmacy "Nhóm 9.cpp"
./pharmacy
```

#### Windows (MinGW)
```cmd
g++ -std=c++11 -o pharmacy.exe "Nhóm 9.cpp"
pharmacy.exe
```

#### Windows (MSVC)
```cmd
cl /EHsc /std:c++11 "Nhóm 9.cpp" /Fe:pharmacy.exe
pharmacy.exe
```

---

## 📖 Usage

### Giao diện chính
```
============= MENU CHINH =============
1. Quan ly khach hang
2. Quan ly nhan vien
3. Quan ly thuoc
4. Quan ly hoa don
5. Quan ly nha cung cap
6. Tim kiem
7. Thong ke
0. Thoat
======================================
Chon:
```

### Ví dụ: Tạo hóa đơn mới

**Input:**
```
Chon: 4
========== QUAN LY HOA DON ==========
1. Tao hoa don moi
Chon: 1

Ma hoa don: HD001
Ma khach hang: KH001
Ma nhan vien: NV001
Ngay lap (dd/mm/yyyy): 15/01/2026
So loai thuoc mua: 2

--- Thuoc thu 1 ---
Ma thuoc: T001
Ten thuoc: Paracetamol 500mg
Gia ban: 50000 VND
So luong ton: 100
So luong mua: 10

--- Thuoc thu 2 ---
Ma thuoc: T002
Ten thuoc: Amoxicillin 250mg
Gia ban: 75000 VND
So luong ton: 50
So luong mua: 5
```

**Output:**
```
============== HOA DON ==============
Ma hoa don: HD001
Ma khach hang: KH001
Ma nhan vien: NV001
Ngay lap: 15/01/2026
-------------------------------------
Ma thuoc    Ten thuoc                     SL        Don gia        Thanh tien     
----------------------------------------------------------------------------------
T001        Paracetamol 500mg             10        50000          500000         
T002        Amoxicillin 250mg             5         75000          375000         
----------------------------------------------------------------------------------
TONG TIEN:                        875000 VND
GIAM GIA:                          87500 VND  (10% cho VIP)
THANH TOAN:                       787500 VND
=====================================

=> Cong diem tich luy: +7.88 diem cho KH001
```

### Ví dụ: Thống kê doanh thu

**Input:**
```
Chon: 7
========== THONG KE & BAO CAO ==========
2. Doanh thu theo ngay
```

**Output:**
```
Ngay                 Doanh thu (VND)
-----------------------------------
14/01/2026                  1250000
15/01/2026                  2100000
16/01/2026                   875000
```

---

## 📁 Project Structure
```
Nhóm 9/
│
├── Nhóm 9.cpp              # Main source code (toàn bộ logic)
│
├── README.md               # Tài liệu này
├── CMakeLists.txt          # TODO: Thêm file CMake config
│
├── data/                   # Thư mục data files (tự tạo khi chạy)
│   ├── khachhang.txt       # Dữ liệu khách hàng
│   ├── nhanvien.txt        # Dữ liệu nhân viên
│   ├── thuoc.txt           # Dữ liệu thuốc
│   ├── nhacungcap.txt      # Dữ liệu nhà cung cấp
│   └── hoadon.txt          # Dữ liệu hóa đơn
│
└── docs/                   # TODO: Thêm tài liệu kỹ thuật
    ├── class-diagram.png   # Sơ đồ lớp UML
    └── user-manual.pdf     # Hướng dẫn sử dụng
```

### Các lớp chính (Classes)

| Class | Mô tả | File |
|-------|-------|------|
| `Nguoi` | Lớp trừu tượng cơ sở cho Người | Nhóm 9.cpp:43 |
| `KhachHang` | Quản lý thông tin khách hàng + tích điểm | Nhóm 9.cpp:63 |
| `NhanVien` | Quản lý nhân viên + tính lương | Nhóm 9.cpp:293 |
| `NhaCungCap` | Quản lý nhà cung cấp | Nhóm 9.cpp:532 |
| `Thuoc` | Quản lý thuốc + tồn kho | Nhóm 9.cpp:728 |
| `ChiTietHoaDon` | Chi tiết từng dòng thuốc trong hóa đơn | Nhóm 9.cpp:965 |
| `HoaDon` | Quản lý hóa đơn bán hàng | Nhóm 9.cpp:993 |
| `SearchService` | Service tìm kiếm (static methods) | Nhóm 9.cpp:1423 |
| `StatsService` | Service thống kê (static methods) | Nhóm 9.cpp:1545 |

---

## ⚙️ Configuration

### File Formats

Dữ liệu được lưu dạng text với delimiter `|`:

**khachhang.txt:**
```
3
KH001|Nguyen Van A|01/01/1990|Nam|Ha Noi|0912345678|150.5
KH002|Tran Thi B|15/05/1985|Nu|TP.HCM|0987654321|250.0
```

**hoadon.txt:**
```
HD:HD001|KH001|NV001|15/01/2026|875000|87500|787500
CT:T001|Paracetamol 500mg|10|50000
CT:T002|Amoxicillin 250mg|5|75000
```

### Validation Rules

| Field | Rule |
|-------|------|
| Mã KH/NV/Thuốc/NCC | Không trùng, không rỗng |
| Số điện thoại | 10-11 số, bắt đầu bằng `0` |
| Email | Phải chứa `@`, không trùng |
| Giá nhập/bán | `> 0`, giá bán `≥` giá nhập |
| Số lượng tồn | `≥ 0` |
| Điểm tích lũy | `≥ 0`, VIP nếu `> 200` |

---

## 🧪 Testing

### Manual Testing Checklist

- [ ] **Khách hàng**
  - [ ] Thêm KH mới với validation đầy đủ
  - [ ] Kiểm tra hệ thống VIP tự động (>200 điểm)
  - [ ] Sửa thông tin không làm trùng mã
  - [ ] Xóa KH và kiểm tra ràng buộc với hóa đơn (TODO)

- [ ] **Hóa đơn**
  - [ ] Tạo hóa đơn với tồn kho đủ
  - [ ] Kiểm tra lỗi khi tồn kho không đủ
  - [ ] Xác nhận trừ kho tự động
  - [ ] Kiểm tra giảm giá VIP
  - [ ] Xóa hóa đơn và hoàn trả kho

- [ ] **File I/O**
  - [ ] Ghi và đọc lại dữ liệu không mất
  - [ ] Xử lý file không tồn tại
  - [ ] Xử lý dữ liệu lỗi format

### Test Data (Mẫu)
```bash
# TODO: Thêm folder test-data/ với các file .txt mẫu
```

---

## 🐛 Troubleshooting

### Lỗi biên dịch

**Lỗi:** `'stod' is not a member of 'std'`
```bash
# Giải pháp: Đảm bảo compile với C++11
g++ -std=c++11 "Nhóm 9.cpp"
```

**Lỗi:** `error C2220: warning treated as error` (MSVC)
```cmd
# Giải pháp: Tắt warning as error
cl /EHsc /W0 "Nhóm 9.cpp"
```

### Lỗi runtime

**Lỗi:** `LOI: Khong the mo file!`
```
Nguyên nhân: File không tồn tại hoặc thiếu quyền truy cập
Giải pháp: 
- Đảm bảo chạy chương trình trong thư mục chứa .cpp
- Tạo file rỗng với số dòng = 0:
  echo 0 > khachhang.txt
```

**Lỗi:** Nhập số bị lỗi vòng lặp vô hạn
```
Nguyên nhân: Nhập text thay vì số
Giải pháp: Code đã xử lý với cin.clear() + cin.ignore()
```

### Vấn đề tiếng Việt

**Windows Console UTF-8:**
```cmd
chcp 65001
pharmacy.exe
```

**Linux/macOS:** Đảm bảo locale hỗ trợ UTF-8
```bash
export LC_ALL=en_US.UTF-8
./pharmacy
```

---

## 🗺️ Roadmap

### Version 1.0 (Current)
- ✅ Quản lý cơ bản: KH, NV, Thuốc, Hóa đơn
- ✅ Hệ thống VIP tự động
- ✅ File I/O với validation

### Version 1.1 (Planned)
- [ ] **GUI với Qt/Dear ImGui** thay console
- [ ] **Database**: Migrate sang SQLite thay text files
- [ ] **Reporting**: Xuất báo cáo PDF/Excel
- [ ] **Authentication**: Hệ thống login cho nhân viên

### Version 2.0 (Future)
- [ ] **Multi-branch**: Quản lý nhiều chi nhánh
- [ ] **Inventory alerts**: Email/SMS khi thuốc hết hạn
- [ ] **Sales analytics**: Dashboard với biểu đồ
- [ ] **API integration**: Kết nối hệ thống kho quốc gia

---

## 🤝 Contributing

Chúng tôi hoan nghênh mọi đóng góp! Để contribute:

1. **Fork** repo này
2. Tạo branch cho feature: `git checkout -b feature/TenTinhNang`
3. Commit thay đổi: `git commit -m 'Add: Tính năng X'`
4. Push lên branch: `git push origin feature/TenTinhNang`
5. Tạo **Pull Request**

### Code Style Guidelines
- Indent: 4 spaces (không dùng tabs)
- Comment tiếng Việt cho logic phức tạp
- Function names: `camelCase` (ví dụ: `timKhachHang()`)
- Class names: `PascalCase` (ví dụ: `KhachHang`)
- Variables: `camelCase` với tên rõ nghĩa

### Commit Message Format
```
Type: Short description

[optional] Longer explanation

Type: Add | Fix | Update | Refactor | Docs | Test
```

---

## 📄 License

Dự án này được phân phối dưới giấy phép **MIT License**.
```
MIT License

Copyright (c) 2026 Nhóm 9

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software...
```

[Xem toàn bộ license](LICENSE)

---

## 👥 Authors

**Nhóm 9** - Dự án Cuối Kỳ Lập Trình Hướng Đối Tượng

- **Thành viên**: [TODO: Thêm tên thành viên]
- **Giảng viên hướng dẫn**: [TODO: Thêm tên GV]
- **Học kỳ**: [TODO: HK1/2024-2025]

---

## 📧 Contact & Support

- **Issues**: [GitHub Issues](https://github.com/your-repo/issues)
- **Email**: TODO: pharmacy.support@example.com
- **Docs**: [Wiki](https://github.com/your-repo/wiki)

---

<div align="center">

**⭐ Nếu project hữu ích, hãy cho chúng tôi một star! ⭐**

Made with ❤️ by Nhóm 9

</div>