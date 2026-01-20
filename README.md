🏥 Pharmacy Management System
Afficher l'image
Afficher l'image
Afficher l'image
Afficher l'image
📋 Table of Contents

About The Project
Key Features
Technology Stack
System Architecture
Installation & Setup
Usage Guide
Project Structure
Design Patterns
Challenges & Solutions
Future Roadmap
Contributing
Team
License


🎯 About The Project
The Pharmacy Management System is a comprehensive console-based application designed to streamline pharmacy operations. Built with C++, this system provides a robust solution for managing customers, employees, suppliers, medications, and sales transactions with an emphasis on data integrity and user-friendly workflows.
Why This Project?

Real-world Application: Addresses actual pharmacy management challenges
Educational Value: Demonstrates OOP principles, file I/O, and data structures
Scalable Design: Modular architecture allows easy feature expansion
Data Persistence: File-based storage ensures data retention across sessions


✨ Key Features
👥 Customer Management

Add, edit, delete, and search customers
Automatic VIP classification based on loyalty points (>200 points)
Track customer purchase history and rewards
Phone number and duplicate ID validation

👔 Employee Management

Complete employee records with salary calculations
Automatic salary computation (Base Salary × 3 + Allowances)
Email validation with duplicate prevention
Role-based information tracking

💊 Medication Management

Comprehensive drug inventory system
Supplier linking and traceability
Expiration date tracking
Stock level monitoring with low-stock alerts
Price validation (selling price must exceed purchase price)

📦 Supplier Management

Supplier database with contact information
Email and phone validation
Linked medication tracking
Duplicate prevention mechanisms

🧾 Invoice System

Multi-item invoice creation
Automatic stock deduction upon sale
VIP customer discount application (10% for VIP)
Loyalty points accrual (1% of total)
Invoice deletion with stock restoration

🔍 Advanced Search Capabilities

Case-insensitive search across all entities
Multi-field search (name, phone, date, ID)
Real-time search results display

📊 Analytics & Reporting

Revenue Analytics:

Total revenue calculation
Daily revenue breakdown
Date-range analysis


Product Analytics:

Top N best-selling medications
Sales volume tracking
Low-stock alerts (customizable threshold)


Customer Analytics:

VIP vs. Regular customer ratios
Average loyalty points
Total loyalty points distribution



💾 Data Persistence

Text-based file storage for all entities
Automatic data loading on startup
Manual save/load functionality
Data integrity validation


🛠 Technology Stack
Core Technologies
TechnologyPurposeJustificationC++ (STL)Primary languagePerformance, memory control, OOP supportStandard LibraryData structuresVectors, maps for efficient data managementFile I/O StreamsData persistenceSimple, portable text-based storage
Why C++ & STL?

Performance: Native compilation for fast execution
Memory Management: Direct control over resources
OOP Support: Perfect for modeling real-world entities
Cross-Platform: Runs on Windows, Linux, macOS
Educational: Demonstrates core CS concepts


🏗 System Architecture
Class Hierarchy
Nguoi (Abstract Base Class)
├── KhachHang (Customer)
└── NhanVien (Employee)

Independent Classes:
├── NhaCungCap (Supplier)
├── Thuoc (Medication)
├── HoaDon (Invoice)
└── ChiTietHoaDon (Invoice Detail)

Service Classes:
├── SearchService
└── StatsService
Key Relationships

Customer ↔ Invoice: One-to-many relationship
Employee ↔ Invoice: One-to-many relationship
Medication ↔ Supplier: Many-to-one relationship
Invoice ↔ Invoice Details: One-to-many composition
Invoice Detail ↔ Medication: Many-to-one reference


📥 Installation & Setup
Prerequisites

C++ Compiler: GCC 7.0+ or MSVC 2017+ or Clang 5.0+
Operating System: Windows, Linux, or macOS
RAM: Minimum 512MB
Storage: 10MB free space

Installation Steps

Clone the repository

bash   git clone https://github.com/yourusername/pharmacy-management-system.git
   cd pharmacy-management-system

Compile the program
Using GCC (Linux/macOS):

bash   g++ -std=c++11 -o pharmacy "Nhóm 9.cpp"
Using MSVC (Windows):
cmd   cl /EHsc /std:c++11 "Nhóm 9.cpp" /Fe:pharmacy.exe
Using Make (if Makefile provided):
bash   make

Run the application
Linux/macOS:

bash   ./pharmacy
Windows:
cmd   pharmacy.exe
```

### File Structure After First Run
```
pharmacy-management-system/
├── Nhóm 9.cpp          # Main source file
├── pharmacy            # Compiled executable (Linux/macOS)
├── pharmacy.exe        # Compiled executable (Windows)
├── khachhang.txt       # Customer data file
├── nhanvien.txt        # Employee data file
├── thuoc.txt           # Medication data file
├── nhacungcap.txt      # Supplier data file
├── hoadon.txt          # Invoice data file
└── README.md           # This file
```

---

## 📖 Usage Guide

### Main Menu Navigation

Upon launching, you'll see the main menu:
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
```

### Quick Start Workflow

#### 1. **Setting Up Suppliers**
   - Navigate to `5. Quan ly nha cung cap`
   - Add suppliers before adding medications
   - Ensure unique supplier IDs and emails

#### 2. **Adding Medications**
   - Navigate to `3. Quan ly thuoc`
   - Link medications to existing suppliers
   - Set purchase and selling prices (selling > purchase)

#### 3. **Registering Customers**
   - Navigate to `1. Quan ly khach hang`
   - Enter customer details with valid phone format (10-11 digits, starts with 0)
   - Initial loyalty points determine classification

#### 4. **Adding Employees**
   - Navigate to `2. Quan ly nhan vien`
   - Provide complete employee information
   - System calculates total salary automatically

#### 5. **Creating Invoices**
   - Navigate to `4. Quan ly hoa don`
   - Select existing customer and employee IDs
   - Add medications by ID (stock checked automatically)
   - System applies VIP discounts and updates loyalty points

### Data Management

#### Saving Data
- Select the "Ghi file" option in each management menu
- Data is saved to respective `.txt` files
- All current data is overwritten

#### Loading Data
- Select the "Doc file" option in each management menu
- Loads data from `.txt` files
- Validates data format before loading

### Search Functionality

**Customer Search Example:**
```
Nhap tu khoa (ten/sdt/ngay sinh): Nguyen
```
- Searches across name, phone, and birth date fields
- Case-insensitive matching
- Displays all matching records

### Analytics Examples

**Top Selling Medications:**
```
Nhap N: 5
```
Returns the top 5 best-selling medications by quantity.

**Low Stock Alert:**
```
Nhap nguong toi thieu (mac dinh 10): 15
Lists all medications with stock below 15 units.

📂 Project Structure
Core Components
cpp// Abstract Base Class
class Nguoi {
    protected:
        string hoTen, ngaySinh, gioiTinh, diaChi, soDienThoai;
    public:
        virtual void xuat() const = 0;  // Pure virtual function
};

// Customer with Loyalty System
class KhachHang : public Nguoi {
    private:
        string maKH, loaiKH;
        double diemTichLuy;
        void capNhatLoaiKH();  // Auto VIP classification
};

// Invoice with Details
class HoaDon {
    private:
        vector<ChiTietHoaDon> danhSachThuoc;
        double tongTien, giamGia, thanhToan;
    public:
        void apDungGiamGia(double phanTram);
};
Validation Functions
cpp// Phone validation: 10-11 digits, starts with '0'
bool kiemTraSDT(const string& sdt);

// Case-insensitive search
bool containsCaseInsensitive(const string& hay, const string& needle);

// String normalization
string toLowerStr(string s);

🎨 Design Patterns
1. Inheritance & Polymorphism

Nguoi abstract base class for KhachHang and NhanVien
Virtual functions for extensibility

2. Composition

HoaDon contains ChiTietHoaDon objects
Strong ownership relationship

3. Service Layer Pattern

SearchService: Centralized search functionality
StatsService: Centralized analytics logic
Separation of concerns

4. Operator Overloading

operator>> and operator<< for intuitive I/O
Consistent interface across all entity classes

5. Friend Functions

File I/O functions access private members directly
Maintains encapsulation while enabling serialization


💡 Challenges & Solutions
Challenge 1: Data Integrity Across Files
Problem: Maintaining referential integrity (e.g., invoice references valid customer/employee/medication IDs)
Solution:

Validation checks before entity creation
ID existence verification across linked entities
Transaction-like operations for invoice creation (rollback on error)

Challenge 2: Vietnamese Character Encoding
Problem: Console display issues with Vietnamese diacritics
Solution:

UTF-8 encoding in source files
Platform-specific console configuration hints in comments
ASCII-safe ID fields for core functionality

Challenge 3: Data Persistence Format
Problem: Balancing human readability and parsing efficiency
Solution:

Pipe-delimited (|) text format
First line contains entity count for efficient allocation
Hierarchical format for complex objects (invoices with details)

Challenge 4: Stock Management in Invoice Deletion
Problem: Ensuring stock is restored when invoices are deleted
Solution:

xoaHoaDon() function iterates through invoice details
Calls tangSoLuong() on each medication before deletion
Confirmation prompt to prevent accidental data loss

Challenge 5: Loyalty Points & VIP Classification
Problem: Automatic classification updates when points change
Solution:

capNhatLoaiKH() private method called after point modifications
Threshold-based logic (>200 points = VIP)
Immediate feedback to users on classification changes


🚀 Future Roadmap
Phase 1: Enhanced User Experience

 GUI Development: Qt or wxWidgets-based interface
 Multi-language Support: English, Vietnamese localization
 User Roles & Permissions: Admin, Pharmacist, Cashier roles
 Session Management: User login and activity logging

Phase 2: Advanced Features

 Database Integration: Migrate to SQLite or MySQL
 Prescription Management: Doctor prescription tracking
 Expiration Alerts: Automated notifications for expiring medications
 Barcode Scanning: Integration with barcode readers
 Receipt Printing: Thermal printer support

Phase 3: Analytics & Reporting

 Visual Reports: Charts and graphs (matplotlib C++ binding or export to CSV)
 Sales Forecasting: Predictive analytics for inventory
 Profit Analysis: Cost vs. revenue tracking
 Export Functionality: PDF/Excel report generation

Phase 4: Integration & Scalability

 REST API: Backend service for web/mobile clients
 Cloud Sync: Multi-branch data synchronization
 Backup Automation: Scheduled backups to cloud storage
 Audit Trail: Complete transaction history logging


🤝 Contributing
We welcome contributions from the community! Here's how you can help:
Getting Started

Fork the repository
Create a feature branch

bash   git checkout -b feature/AmazingFeature

Commit your changes

bash   git commit -m "Add some AmazingFeature"

Push to the branch

bash   git push origin feature/AmazingFeature

Open a Pull Request

Contribution Guidelines

Follow existing code style and naming conventions
Add comments for complex logic (preferably in English)
Update documentation for new features
Test thoroughly before submitting PR
Include unit tests if applicable

Code Style
cpp// Use camelCase for variables and functions
int soLuongTon;
void capNhatGiaTri();

// Use PascalCase for classes
class KhachHang;

// Use UPPER_CASE for constants
const int MAX_ITEMS = 100;

// Add comments for non-obvious logic
// Rang buoc: gia ban phai lon hon gia nhap
while(giaNhap > giaBan) {
    // ...
}
Reporting Bugs
Use GitHub Issues with the following template:
markdown**Bug Description**: [Clear description]
**Steps to Reproduce**: [Numbered steps]
**Expected Behavior**: [What should happen]
**Actual Behavior**: [What actually happens]
**Environment**: [OS, Compiler version]
**Screenshots**: [If applicable]
```

---

## 👥 Team

### Development Team

| Name | Role | GitHub |
|------|------|--------|
| **[Member 1]** | Team Lead / Backend Developer | [@username1](https://github.com/username1) |
| **[Member 2]** | Core Developer / Data Management | [@username2](https://github.com/username2) |
| **[Member 3]** | UI/UX / Testing | [@username3](https://github.com/username3) |
| **[Member 4]** | Documentation / QA | [@username4](https://github.com/username4) |

### Acknowledgments

- **C++ Community**: For extensive STL documentation and best practices
- **Stack Overflow**: For problem-solving assistance during development
- **Open Source Contributors**: For inspiration from similar projects

---

## 📄 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

### MIT License Summary
```
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

📞 Support & Contact

Issues: GitHub Issues
Discussions: GitHub Discussions
Email: support@yourproject.com


⭐ Show Your Support
If this project helped you, please give it a ⭐️! It motivates us to continue improving.

<div align="center">
Made with ❤️ by [Team Name]
⬆ Back to Top
</div>Claude est une IA et peut faire des erreurs. Veuillez vérifier les réponses.
