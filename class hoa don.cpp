#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

class HoaDon {
private:
    string mahd;
    string makh;
    string manv;
    string ngaylap;
    string mathuoc;
    string tenthuoc;
    int soluong;
    double dongia;
    double tongtien;
    double giamgia;
    double thanhtoan;

public:
    // Constructor
    HoaDon() {
        mahd = "";
        makh = "";
        manv = "";
        ngaylap = "";
        mathuoc = "";
        tenthuoc = "";
        soluong = 0;
        dongia = 0;
        tongtien = 0;
        giamgia = 0;
        thanhtoan = 0;
    }

    // Nhap thong tin
    void nhap() {
        cout << "\n===== NHAP HOA DON =====\n";
        cout << "Ma hoa don: ";
        getline(cin, mahd);
        cout << "Ma khach hang: ";
        getline(cin, makh);
        cout << "Ma nhan vien: ";
        getline(cin, manv);
        cout << "Ngay lap (dd/mm/yyyy): ";
        getline(cin, ngaylap);
        cout << "Ma thuoc: ";
        getline(cin, mathuoc);
        cout << "Ten thuoc: ";
        getline(cin, tenthuoc);
        cout << "So luong: ";
        cin >> soluong;
        cout << "Don gia: ";
        cin >> dongia;
        cout << "Giam gia (%): ";
        cin >> giamgia;
        cin.ignore();
        
        tongtien = soluong * dongia;
        thanhtoan = tongtien - (tongtien * giamgia / 100);
    }

    // Xuat thong tin
    void xuat() const {
        cout << "\n========== HOA DON ==========\n";
        cout << "Ma HD      : " << mahd << endl;
        cout << "Ma KH      : " << makh << endl;
        cout << "Ma NV      : " << manv << endl;
        cout << "Ngay lap   : " << ngaylap << endl;
        cout << "----------------------------\n";
        cout << "Ma thuoc   : " << mathuoc << endl;
        cout << "Ten thuoc  : " << tenthuoc << endl;
        cout << "So luong   : " << soluong << endl;
        cout << fixed << setprecision(2);
        cout << "Don gia    : " << dongia << " VND\n";
        cout << "Tong tien  : " << tongtien << " VND\n";
        cout << "Giam gia   : " << giamgia << "%\n";
        cout << "Thanh toan : " << thanhtoan << " VND\n";
        cout << "============================\n";
    }

    // Getter
    string getMaHD() const { return mahd; }
    string getMaKH() const { return makh; }
    string getTenThuoc() const { return tenthuoc; }
    double getThanhToan() const { return thanhtoan; }
    
    // Ham ghi mot hoa don vao file
    void ghiFile(ofstream& f) const {
        f << mahd << "|" << makh << "|" << manv << "|" << ngaylap << "|"
          << mathuoc << "|" << tenthuoc << "|" << soluong << "|"
          << dongia << "|" << tongtien << "|" << giamgia << "|" << thanhtoan << endl;
    }
    
    // Ham doc mot hoa don tu file
    void docFile(ifstream& f) {
        string line;
        getline(f, line);
        
        size_t pos = 0;
        vector<string> tokens;
        
        while ((pos = line.find('|')) != string::npos) {
            tokens.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        tokens.push_back(line);
        
        if (tokens.size() == 11) {
            mahd = tokens[0];
            makh = tokens[1];
            manv = tokens[2];
            ngaylap = tokens[3];
            mathuoc = tokens[4];
            tenthuoc = tokens[5];
            soluong = stoi(tokens[6]);
            dongia = stod(tokens[7]);
            tongtien = stod(tokens[8]);
            giamgia = stod(tokens[9]);
            thanhtoan = stod(tokens[10]);
        }
    }
};

// Ham tim hoa don theo ma
int timHoaDon(const vector<HoaDon>& ds, const string& ma) {
    for (int i = 0; i < ds.size(); i++) {
        if (ds[i].getMaHD() == ma) {
            return i;
        }
    }
    return -1;
}

// Ham hien thi danh sach hoa don
void hienThiDanhSach(const vector<HoaDon>& ds) {
    if (ds.empty()) {
        cout << "\n=> Danh sach rong!\n";
        return;
    }
    
    cout << "\n===== DANH SACH HOA DON =====\n";
    cout << left << setw(12) << "Ma HD" 
         << setw(12) << "Ma KH" 
         << setw(20) << "Ten thuoc"
         << setw(12) << "Ngay lap"
         << right << setw(15) << "Thanh toan" << endl;
    cout << string(71, '-') << endl;
    
    for (const auto& hd : ds) {
        cout << left << setw(12) << hd.getMaHD()
             << setw(12) << hd.getMaKH()
             << setw(20) << hd.getTenThuoc()
             << setw(12) << "N/A"
             << right << setw(15) << fixed << setprecision(0) 
             << hd.getThanhToan() << endl;
    }
    cout << "==============================\n";
}

// Ham ghi file
void ghiFile(const vector<HoaDon>& ds, const string& tenfile) {
    ofstream f(tenfile);
    if (!f.is_open()) {
        cout << "\n=> LOI: Khong the mo file de ghi!\n";
        return;
    }
    
    for (const auto& hd : ds) {
        hd.ghiFile(f);
    }
    
    f.close();
    cout << "\n=> Ghi file thanh cong! (" << ds.size() << " hoa don)\n";
}

// Ham doc file
void docFile(vector<HoaDon>& ds, const string& tenfile) {
    ifstream f(tenfile);
    if (!f.is_open()) {
        cout << "\n=> LOI: Khong the mo file de doc!\n";
        return;
    }
    
    ds.clear();
    
    while (!f.eof()) {
        HoaDon hd;
        hd.docFile(f);
        if (hd.getMaHD() != "") {
            ds.push_back(hd);
        }
    }
    
    f.close();
    cout << "\n=> Doc file thanh cong! (" << ds.size() << " hoa don)\n";
}

// Ham menu
void menu() {
    cout << "\n===== QUAN LY HOA DON =====\n";
    cout << "1. Them hoa don\n";
    cout << "2. Hien thi danh sach\n";
    cout << "3. Tim hoa don\n";
    cout << "4. Ghi file\n";
    cout << "5. Doc file\n";
    cout << "6. Thoat\n";
    cout << "===========================\n";
    cout << "Chon: ";
}

int main() {
    vector<HoaDon> danhSach;
    int chon;
    
    do {
        menu();
        cin >> chon;
        cin.ignore();
        
        switch(chon) {
            case 1: {
                HoaDon hd;
                hd.nhap();
                danhSach.push_back(hd);
                cout << "\n=> Them hoa don thanh cong!\n";
                break;
            }
            
            case 2: {
                hienThiDanhSach(danhSach);
                break;
            }
            
            case 3: {
                string ma;
                cout << "\nNhap ma hoa don can tim: ";
                getline(cin, ma);
                
                int idx = timHoaDon(danhSach, ma);
                if (idx != -1) {
                    danhSach[idx].xuat();
                } else {
                    cout << "\n=> Khong tim thay hoa don!\n";
                }
                break;
            }
            
            case 4: {
                string tenfile;
                cout << "\nNhap ten file: ";
                getline(cin, tenfile);
                ghiFile(danhSach, tenfile);
                break;
            }
            
            case 5: {
                string tenfile;
                cout << "\nNhap ten file: ";
                getline(cin, tenfile);
                docFile(danhSach, tenfile);
                break;
            }
            
            case 6: {
                cout << "\n=> Tam biet!\n";
                break;
            }
            
            default: {
                cout << "\n=> Lua chon khong hop le!\n";
                break;
            }
        }
        
    } while(chon != 6);
    
    return 0;
}
