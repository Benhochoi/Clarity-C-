#include<bits/stdc++.h>     
using namespace std;

// Ham chuyen chuoi ve chu thuong de so sanh khong phan biet hoa thuong
string toLowerStr(string s){
    for(char &c: s) c = (char)tolower((unsigned char)c);
    return s;
}

// Ham kiem tra xem chuoi hay co chua needle (khong phan biet hoa thuong)
bool containsCaseInsensitive(const string& hay, const string& needle){
    string a = toLowerStr(hay), b = toLowerStr(needle);
    return a.find(b) != string::npos;
}

// ham kiem tra so dien thoai 
// Dieu kien: 10-11 ky tu, toan so, bat dau bang '0'
bool kiemTraSDT(const string& sdt) {
    if (sdt.length() < 10 || sdt.length() > 11) return false;
    
    for (char c : sdt) {
        if (!isdigit(c)) return false;
    }
    
    // SDT Viet Nam bat dau bang 0
    if (sdt[0] != '0') return false;
    
    return true;
}

// ==================== LOP NGUOI ====================
// lop truu tuong
// Dung lam lop co so cho KhachHang, NhanVien
class Nguoi {
protected:
    string hoTen;
    string ngaySinh;  
    string gioiTinh;
    string diaChi;
    string soDienThoai;

public:
    Nguoi() : hoTen(""), ngaySinh(""), gioiTinh(""), diaChi(""), soDienThoai("") {}// Khoi tao mac dinh
    Nguoi(string ht, string ns, string gt, string dc, string sdt)
        : hoTen(ht), ngaySinh(ns), gioiTinh(gt), diaChi(dc), soDienThoai(sdt) {}// Khoi tao voi tham so

    virtual void xuat() const = 0;// Ham xuat thong tin nguoi (virtual cho lop con)

    string getHoTen() const { return hoTen; }  // Lay ten
    string getSoDienThoai() const { return soDienThoai; } // Lay so dien thoai
    string getNgaySinh() const { return ngaySinh; } // Lay ngay sinh

    virtual ~Nguoi() {} // Destructor de giai phong tai nguyen
};

// ==================== LOP KHACH HANG ====================
// Quan ly thong tin khach hang, ke thua tu Nguoi
class KhachHang : public Nguoi {
private:
    string maKH;
    string loaiKH;     // TU DONG theo diemTichLuy
    double diemTichLuy;
    
    // Cap nhat loai khach hang tu diem tich luy
    // >200 diem => VIP, nguoc lai Thuong
    void capNhatLoaiKH() {
        loaiKH = (diemTichLuy > 200) ? "VIP" : "Thuong";
    }

// Khoi tao mac dinh
public:
    KhachHang() : Nguoi(), maKH(""), loaiKH("Thuong"), diemTichLuy(0) {}

    KhachHang(string ma, string ht, string ns, string gt, string dc, string sdt, double diem)
        : Nguoi(ht, ns, gt, dc, sdt), maKH(ma), diemTichLuy(diem) {// Khoi tao voi tham so
        capNhatLoaiKH(); // Cap nhat loai sau khi gan diem
    }

    // Khai bao nap chong toan tu nhap xuat cho KhachHang
    friend istream& operator>>(istream& is, KhachHang& kh);
	friend ostream& operator<<(ostream& os, const KhachHang& kh);

    // Set ma khach hang
    void setMaKH(const string& ma) { maKH = ma; }
    string getMaKH() const { return maKH; }

    // Ham nhap voi tham so la danh sach KH de kiem tra trung maKH
    void nhap(const vector<KhachHang>& dsKH) {
        cout << "\n--- NHAP THONG TIN KHACH HANG ---\n";

        // Kiem tra maKH trung
        do {
            cout << "Ma khach hang: ";
            getline(cin, maKH);

            bool trung = false;
            for (size_t i = 0; i < dsKH.size(); ++i) {
                if (dsKH[i].getMaKH() == maKH) { trung = true; break; }
            }

            if (trung) cout << "=> LOI: Ma khach hang da ton tai! Vui long nhap lai.\n";
            else break;
        } while (true);

        cout << "Ho ten: "; getline(cin, hoTen);
        cout << "Ngay sinh (dd/mm/yyyy): "; getline(cin, ngaySinh);
        cout << "Gioi tinh: "; getline(cin, gioiTinh);
        cout << "Dia chi: "; getline(cin, diaChi);

        // Nhap so dien thoai co kiem tra dinh dang
        cout << "So dien thoai: ";
		do {
		    getline(cin, soDienThoai);
		    if (!kiemTraSDT(soDienThoai)) {
		        cout << "=> LOI: So dien thoai khong hop le (10 so, bat dau bang 0)!\n";
		        cout << "Nhap lai: ";
		    } else break;
		} while (true);

        cout << "Diem tich luy: ";
        cin >> diemTichLuy;
        // Rang buoc nhap diemtichLuy phai lon hon 0
    	while(diemTichLuy <= 0){
    		cout <<"Diem tich luy phai lon hon 0 !\n";
    		cout << "Diem tich luy: ";
    		cin >> diemTichLuy;
    	}
        cin.ignore();
        capNhatLoaiKH();
        // Thong bao sau khi nhap diem
        cout << "Hang hien tai cua khach hang la: " << loaiKH << "\n";
    }
    
    // Xuat thong tin khach hang
    void xuat() const override {
        cout << left << setw(12) << maKH
             << setw(25) << hoTen
             << setw(12) << ngaySinh
             << setw(10) << gioiTinh
             << setw(30) << diaChi
             << setw(12) << soDienThoai
             << setw(15) << loaiKH
             << setw(15) << fixed << setprecision(1) << diemTichLuy << endl;
    }

	
    string getLoaiKH() const { return loaiKH; } // Lay loai khach hang 	
    double getDiemTichLuy() const { return diemTichLuy; } // Lay diem tich luy

	// Cap nhat loai khach hang sau khi tang diem
    void tangDiemTichLuy(double diem) {
        diemTichLuy += diem;
        capNhatLoaiKH();
    }

	// Set diem tich luy va cap nhat loai khach hang
    void setDiemTichLuy(double diem) {
        diemTichLuy = diem;
        capNhatLoaiKH();
    }

    // Cho phep cac ham doc/ghi file truy cap vao truong private
    friend void ghiFileKhachHang(const vector<KhachHang>&, const string&);
    friend void docFileKhachHang(vector<KhachHang>&, const string&);
};

	// nap chong toan tu nhap
	// Luu y: ham nay KHONG kiem tra trung maKH vi khong co danh sach truyen vao
	istream& operator>>(istream& is, KhachHang& kh) {
	    cout << "\n--- NHAP THONG TIN KHACH HANG ---\n";
	    cout << "Ma khach hang: ";
	    getline(is, kh.maKH);
	    cout << "Ho ten: ";
	    getline(is, kh.hoTen);
	    cout << "Ngay sinh (dd/mm/yyyy): ";
	    getline(is, kh.ngaySinh);
	    cout << "Gioi tinh: ";
	    getline(is, kh.gioiTinh);
	    cout << "Dia chi: ";
	    getline(is, kh.diaChi);
	    
	    // Nhap va kiem tra so dien thoai
	    do {
	        cout << "So dien thoai: ";
	        getline(is, kh.soDienThoai);
	        if (!kiemTraSDT(kh.soDienThoai)) {
	            cout << "=> LOI: So dien thoai khong hop le (10 so, bat dau bang 0)!\n";
	            cout << "Nhap lai: ";
	        } else break;
	    } while (true);
	    
	    cout << "Diem tich luy: ";
	    is >> kh.diemTichLuy;
	    is.ignore();
	    
	    // Cap nhat loai khach hang
	    kh.loaiKH = (kh.diemTichLuy > 200) ? "VIP" : "Thuong";
	    cout << "Hang hien tai cua khach hang la: " << kh.loaiKH << "\n";
	    
	    return is;
	}

// nap chong toan tu xuat
// In theo dinh dang bang, dung setw de can le
ostream& operator<<(ostream& os, const KhachHang& kh) {
    os << left << setw(12) << kh.maKH
       << setw(25) << kh.hoTen
       << setw(12) << kh.ngaySinh
       << setw(10) << kh.gioiTinh
       << setw(30) << kh.diaChi
       << setw(12) << kh.soDienThoai
       << setw(15) << kh.loaiKH
       << setw(15) << fixed << setprecision(1) << kh.diemTichLuy;
    return os;
}

// Tim khach hang theo ma
// Tra ve index trong vector, -1 neu khong tim thay
int findKhachHang(const vector<KhachHang>& ds, const string& ma){
    for (size_t i = 0; i < ds.size(); ++i) 
        if (ds[i].getMaKH() == ma) 
            return (int)i;
    return -1;
}

// Sua khach hang
// Tao danh sach tam khong chua phan tu dang sua de kiem tra trung ma
void suaKhachHang(vector<KhachHang>& dsKH){
    cin.ignore();
    string ma; 
    cout << "Nhap ma khach hang can sua: "; 
    getline(cin, ma);
    
    int idx = findKhachHang(dsKH, ma);
    if (idx == -1) { 
        cout << "=> Khong tim thay!\n"; 
        return; 
    }
    
    cout << "=> Nhap lai thong tin:\n";
    
    // Tao danh sach tam cho kiem tra trung ma
    vector<KhachHang> dsTemp;
    for (size_t i = 0; i < dsKH.size(); ++i) {
        if ((int)i != idx) {
            dsTemp.push_back(dsKH[i]);
        }
    }
    
    dsKH[idx].nhap(dsTemp);  // Truyen danh sach tam de kiem tra trung
    cout << "=> Sua thanh cong!\n";
}

// Xoa khach hang theo ma
void xoaKhachHang(vector<KhachHang>& dsKH){
    cin.ignore();
    string ma; 
    cout << "Nhap ma khach hang can xoa: "; 
    getline(cin, ma);
    
    int idx = findKhachHang(dsKH, ma);
    if (idx == -1) { 
        cout << "=> Khong tim thay!\n"; 
        return; 
    }
    
    dsKH.erase(dsKH.begin() + idx);
    cout << "=> Xoa thanh cong!\n";
}

// Cap nhat diem khach hang (cong them diem)
void capNhatDiemKhachHang(vector<KhachHang>& dsKH){
    cin.ignore();
    string ma; 
    cout << "Nhap ma khach hang: "; 
    getline(cin, ma);
    
    int idx = findKhachHang(dsKH, ma);
    if (idx == -1) { 
        cout << "=> Khong tim thay!\n"; 
        return; 
    }
    
    double cong; 
    cout << "Cong them bao nhieu diem? "; 
    cin >> cong;
    
    dsKH[idx].tangDiemTichLuy(cong);
    cout << "=> Cap nhat diem thanh cong!\n";
}

// Ham ghi file khach hang
// Dinh dang: dong dau tien la so luong, moi dong: ma|ho ten|ngay sinh|gioi tinh|dia chi|sdt|diem
void ghiFileKhachHang(const vector<KhachHang>& ds, const string& tenFile) {
    ofstream f(tenFile);
    if (!f.is_open()) {
        cout << "LOI: Khong the mo file!\n";
        return;
    }
    f << ds.size() << endl;
    for (const auto& kh : ds) {
        f << kh.maKH << "|" << kh.hoTen << "|" << kh.ngaySinh << "|"
          << kh.gioiTinh << "|" << kh.diaChi << "|" << kh.soDienThoai << "|"
          << kh.diemTichLuy << endl; 
    }
    f.close();
    cout << "=> Ghi file thanh cong!\n";
}

// Ham doc file khach hang
// Doc lai dung dinh dang da ghi o tren
void docFileKhachHang(vector<KhachHang>& ds, const string& tenFile) {
    ifstream f(tenFile);
    if (!f.is_open()) {
        cout << "LOI: Khong the mo file!\n";
        return;
    }
    int n;
    f >> n;
    f.ignore();
    ds.clear();
    for (int i = 0; i < n; i++) {
        string line;
        getline(f, line);
        size_t pos = 0;
        vector<string> tokens;
        // Tach chuoi theo ky tu '|'
        while ((pos = line.find('|')) != string::npos) {
            tokens.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        tokens.push_back(line);
        if (tokens.size() == 7) {
            KhachHang kh(tokens[0], tokens[1], tokens[2], tokens[3],
                         tokens[4], tokens[5],  stod(tokens[6]));
            ds.push_back(kh);
        }
    }
    f.close();
    cout << "=> Doc file thanh cong!\n";
}

// ==================== LOP NHAN VIEN ====================
// Quan ly thong tin nhan vien, ke thua tu Nguoi
class NhanVien : public Nguoi {
private:
    string maNV;
	string email;
    string chucVu;
    double luongCoBan;
    double phuCap;
	// ham khoi tao mac dinh cua lop nhan vien
public:
    NhanVien() : Nguoi(), maNV(""), chucVu(""), email(""), luongCoBan(0), phuCap(0) {}
    NhanVien(string ma, string ht, string ns, string gt, string dc, string sdt,string mail, string cv, double lcb, double pc)
        : Nguoi(ht, ns, gt, dc, sdt), maNV(ma), chucVu(cv), luongCoBan(lcb), phuCap(pc), email(mail) {} // ham khoi tao tham so

	string getEmail() const { return email; }

	// Nap chong toan tu nhap xuat
	friend istream& operator>>(istream& is, NhanVien& nv);
	friend ostream& operator<<(ostream& os, const NhanVien& nv);

    // Ham nhap co kiem tra trung maNV va email
    void nhap(const vector<NhanVien>& dsNV) { 
        cout << "\n--- NHAP THONG TIN NHAN VIEN ---\n";
        // Kiem tra ma nhan vien co trung nhau khong
        do {
            cout << "Ma nhan vien: "; 
            getline(cin, maNV);
            bool trung = false;
            for (size_t i = 0; i < dsNV.size(); ++i) {
                if (dsNV[i].getMaNV() == maNV) {
                    trung = true;
                    break;
                }
            }
            
            if (trung) {
                cout << "=> LOI: Ma nhan vien da ton tai! Vui long nhap lai.\n";
            } else {
                break;  // Ma hop le, thoat vong lap
            }
        } while (true);
        
        cout << "Ho ten: "; getline(cin, hoTen);
        cout << "Ngay sinh (dd/mm/yyyy): "; getline(cin, ngaySinh);
        cout << "Gioi tinh: "; getline(cin, gioiTinh);
        cout << "Dia chi: "; getline(cin, diaChi);

        // Nhap va kiem tra so dien thoai
        cout << "So dien thoai: ";
		do {
		    getline(cin, soDienThoai);
		    if (!kiemTraSDT(soDienThoai)) {
		        cout << "=> LOI: So dien thoai khong hop le (10 so, bat dau bang 0)!\n";
		        cout << "Nhap lai: ";
		    } else break;
		} while (true);

        // Nhap va kiem tra email (co @, khong trung email)
        do {
            cout << "Email: ";
            getline(cin, email);
            
            if (email.find('@') == string::npos) {
                cout << "=> LOI: Email phai chua ky tu '@'! Vui long nhap lai.\n";
                continue;
            }

            bool trung = false;
            for (size_t i = 0; i < dsNV.size(); ++i) {
                if (toLowerStr(dsNV[i].getEmail()) == toLowerStr(email)) {
                    trung = true;
                    break;
                }
            }
            
            if (trung) {
                cout << "=> LOI: Email da ton tai trong he thong! Vui long nhap lai.\n";
                continue;
            }
            
            break;
        } while (true);

        cout << "Chuc vu: "; getline(cin, chucVu);
        cout << "Luong co ban: "; cin >> luongCoBan;
        // Rang buoc dieu kien luongCoBan phai lon hon 0
            	while(luongCoBan <= 0){
    		cout <<"Luong co ban phai lon hon 0 !\n";
    		cout << "Luong co ban: "; cin >> luongCoBan;
    	}
    }

    // Xuat thong tin nhan vien
    void xuat() const override {
        cout << left << setw(12) << maNV
             << setw(25) << hoTen
             << setw(12) << ngaySinh
             << setw(10) << gioiTinh
             << setw(30) << diaChi
             << setw(12) << soDienThoai
             << setw(15) << email
             << setw(15) << chucVu
             << setw(12) << fixed << setprecision(0) << luongCoBan
             << setw(12) << phuCap
             << setw(12) << tinhLuong() << endl;
    }

    // Tinh tong luong = luong co ban * 3 + phu cap
    double tinhLuong() const {
        return luongCoBan * 3 + phuCap;
    }

    string getMaNV() const { return maNV; }
	
// Khai bao ham ban de ham ghiFileNhanVien co the truy cap truc tiep
    // vao cac thuoc tinh private/protected cua lop NhanVien khi ghi file
    friend void ghiFileNhanVien(const vector<NhanVien>&, const string&);
    
    // Khai bao ham ban de ham docFileNhanVien co the truy cap truc tiep
    // vao cac thuoc tinh private/protected cua lop NhanVien khi doc file
    friend void docFileNhanVien(vector<NhanVien>&, const string&);
    
    // Nap chong toan tu so sanh '>' giua 2 doi tuong NhanVien
    // (co the dung de so sanh luong, phu cap, ho ten... tuy theo cach dinh nghia)
    friend bool operator>(const NhanVien& nv1, const NhanVien& nv2);
};

// nhap chong toan tu nhap
// Day la phien ban khong kiem tra trung ma va email
istream& operator>>(istream& is, NhanVien& nv) {
    cout << "\n--- NHAP THONG TIN NHAN VIEN ---\n";
    cout << "Ma nhan vien: ";
    getline(is, nv.maNV);
    cout << "Ho ten: ";
    getline(is, nv.hoTen);
    cout << "Ngay sinh (dd/mm/yyyy): ";
    getline(is, nv.ngaySinh);
    cout << "Gioi tinh: ";
    getline(is, nv.gioiTinh);
    cout << "Dia chi: ";
    getline(is, nv.diaChi);
    
    // Nhap va kiem tra so dien thoai
    do {
        cout << "So dien thoai: ";
        getline(is, nv.soDienThoai);
        if (!kiemTraSDT(nv.soDienThoai)) {
            cout << "=> LOI: So dien thoai khong hop le (10 so, bat dau bang 0)!\n";
            cout << "Nhap lai: ";
        } else break;
    } while (true);
    
    // Nhap va kiem tra email
    do {
        cout << "Email: ";
        getline(is, nv.email);
        if (nv.email.find('@') == string::npos) {
            cout << "=> LOI: Email phai chua ky tu '@'! Vui long nhap lai.\n";
        } else break;
    } while (true);
    
    cout << "Chuc vu: ";
    getline(is, nv.chucVu);
    cout << "Luong co ban: ";
    is >> nv.luongCoBan;
    cout << "Phu cap: ";
    is >> nv.phuCap;
    is.ignore();
    
    return is;
}

// nap chong toan tu xuat
ostream& operator<<(ostream& os, const NhanVien& nv) {
    os << left << setw(12) << nv.maNV
       << setw(25) << nv.hoTen
       << setw(12) << nv.ngaySinh
       << setw(10) << nv.gioiTinh
       << setw(30) << nv.diaChi
       << setw(12) << nv.soDienThoai
       << setw(15) << nv.email
       << setw(15) << nv.chucVu
       << setw(12) << fixed << setprecision(0) << nv.luongCoBan
       << setw(12) << nv.phuCap
       << setw(12) << nv.tinhLuong();
    return os;
}

// Tim nhan vien theo ma
int findNhanVien(const vector<NhanVien>& ds, const string& ma){
    for (size_t i=0;i<ds.size();++i) if (ds[i].getMaNV()==ma) return (int)i;
    return -1;
}

//sua nhan vien
// Tuong tu suaKhachHang: tao ds tam de kiem tra trung ma/email
void suaNhanVien(vector<NhanVien>& dsNV){
    cin.ignore();
    string ma; 
    cout << "Nhap ma nhan vien can sua: "; 
    getline(cin, ma);
    
    int idx = findNhanVien(dsNV, ma);
    if (idx == -1) { 
        cout << "=> Khong tim thay!\n"; 
        return; 
    }
    
    cout << "=> Nhap lai thong tin nhan vien:\n";
    // Tao danh sach tam khong chua nhan vien dang sua (de kiem tra trung)
    vector<NhanVien> dsTemp;
    for (size_t i = 0; i < dsNV.size(); ++i) {
        if ((int)i != idx) {
            dsTemp.push_back(dsNV[i]);
        }
    }
    dsNV[idx].nhap(dsTemp);  // truyen dstemp 
    cout << "=> Sua thanh cong!\n";
}

//xoa nhan vien
void xoaNhanVien(vector<NhanVien>& dsNV){
    cin.ignore();
    string ma; cout << "Nhap ma nhan vien can xoa: "; getline(cin, ma);
    int idx = findNhanVien(dsNV, ma);
    if (idx == -1){ cout << "=> Khong tim thay!\n"; return; }
    dsNV.erase(dsNV.begin()+idx);
    cout << "=> Xoa thanh cong!\n";
}

// HAM GHI FILE NHAN VIEN
// Dinh dang: n dong => ma|ho ten|ns|gt|dc|sdt|email|chuc vu|luongcb|phu cap
void ghiFileNhanVien(const vector<NhanVien>& ds, const string& tenFile) {
    ofstream f(tenFile);
    if (!f.is_open()) {
        cout << "LOI: Khong the mo file!\n";
        return;
    }
    f << ds.size() << endl;
    for (const auto& nv : ds) {
        f << nv.maNV << "|" << nv.hoTen << "|" << nv.ngaySinh << "|"
          << nv.gioiTinh << "|" << nv.diaChi << "|" << nv.soDienThoai << "|"
          << nv.email << "|"<< nv.chucVu << "|" << nv.luongCoBan << "|" 
		  << nv.phuCap << endl;
    }
    f.close();
    cout << "=> Ghi file thanh cong!\n";
}

// HAM DOC FILE NHAN VIEN
// Muc dich: doc du lieu nhan vien tu file van ban (tenFile) vao vector ds
void docFileNhanVien(vector<NhanVien>& ds, const string& tenFile) {
    ifstream f(tenFile);                 // Mo file de doc
    if (!f.is_open()) {                  // Neu mo file that bai
        cout << "LOI: Khong the mo file!\n";
        return;                          // Thoat ham, khong lam gi tiep
    }

    int n;
    f >> n;                              // Doc so luong nhan vien duoc ghi o dong dau
    f.ignore();                          // Bo qua ky tu xuong dong con sot lai sau khi doc n

    ds.clear();                          // Xoa danh sach cu truoc khi nap du lieu moi

    // Vong lap doc tung dong thong tin nhan vien
    for (int i = 0; i < n; i++) {
        string line;
        getline(f, line);                // Doc mot dong du lieu (mot nhan vien)

        size_t pos = 0;
        vector<string> tokens;           // Mang luu cac truong sau khi tach bang dau '|'

        // Tach chuoi line thanh cac truong, su dung ky tu '|' lam phan tach
        while ((pos = line.find('|')) != string::npos) {
            tokens.push_back(line.substr(0, pos)); // Lay tu dau chuoi den truoc '|' dua vao tokens
            line.erase(0, pos + 1);                // Xoa phan vua lay + ky tu '|'
        }
        tokens.push_back(line);          // Day phan con lai cuoi cung vao tokens

        // File nhan vien duoc ghi voi 10 truong:
        // 0: maNV, 1: hoTen, 2: ngaySinh, 3: gioiTinh, 4: diaChi,
        // 5: soDienThoai, 6: email, 7: chucVu, 8: luongCoBan, 9: phuCap
        if (tokens.size() == 10) {
            NhanVien nv(
                tokens[0], tokens[1], tokens[2],               
                tokens[3], tokens[4], tokens[5], tokens[6],              
                tokens[7],stod(tokens[8]),stod(tokens[9])         
            );
            ds.push_back(nv);       // Them doi tuong nv vao danh sach
        }
        // Neu tokens.size() != 10 thi dong du lieu bi sai dinh dang -> bo qua
    }

    f.close();                           // Dong file sau khi doc xong
    cout << "=> Doc file thanh cong!\n";
}


// ==================== LOP NHA CUNG CAP ====================
// Quan ly thong tin nha cung cap
class NhaCungCap {
private:
	// thuoc tinh nha cung cap
    string maNCC;
    string tenNCC;
    string diaChi;
    string soDienThoai;
    string email;

public:
    NhaCungCap() : maNCC(""), tenNCC(""), diaChi(""), soDienThoai(""), email("") {} // Constructor mac dinh: Khoi tao cac gia tri rong
    NhaCungCap(string ma, string ten, string dc, string sdt, string mail) // Constructor co tham so: Khoi tao voi gia tri truyen vao
        : maNCC(ma), tenNCC(ten), diaChi(dc), soDienThoai(sdt), email(mail) {}
    
    string getEmail() const { return email; }    // Cac ham Getter de lay thong tin private
    string getMaNCC() const { return maNCC; }
    string getTenNCC() const { return tenNCC; }
    string getSoDienThoai() const { return soDienThoai; }
    
    // Ham nhap thong tin nha cung cap co kiem tra logic (trung ma, format), dsNCC: ds hien tai de ktra trung lap
    void nhapnhacungcap(const vector<NhaCungCap>& dsNCC) { 
        cout << "\n--- NHAP THONG TIN NHA CUNG CAP ---\n";
        do {
            cout << "Ma NCC: ";
            getline(cin, maNCC);
            
            bool trung = false; // Nhap va kiem tra trung Ma NCC
            for (size_t i = 0; i < dsNCC.size(); ++i) { // duyet ds xem co ton tai hay khong
                if (dsNCC[i].getMaNCC() == maNCC) {
                    trung = true;
                    break; // lenh break thoat vong lap khi hop le
                }
            }
            
            if (trung) {
                cout << "=> LOI: Ma NCC da ton tai! Vui long nhap lai.\n";
            } else {
                break; // lenh break thoat vong lap khi ma hop le
            }
        } while (true);
        
        cout << "Ten NCC: "; getline(cin, tenNCC);
        cout << "Dia chi: "; getline(cin, diaChi);
        
        // Kiem tra so dien thoai nha cung cap
        do {
            cout << "So dien thoai: "; // Nhap va kiem tra dinh dang So dien thoai
            getline(cin, soDienThoai);
            if (!kiemTraSDT(soDienThoai)) { 
                cout << "=> LOI: So dien thoai khong hop le (10 so, bat dau bang 0)!\n";
                cout << "Nhap lai ";
            } else break;
        } while (true);
        
        // Kiem tra email nha cung cap (co @, khong trung)
        do {
            cout << "Email: ";
            getline(cin, email); // Nhap va kiem tra Email
            
            if (email.find('@') == string::npos) {
                cout << "=> LOI: Email phai chua ky tu '@'! Vui long nhap lai.\n";
                continue;
            }
            
            bool trung = false; // trung = Kiem tra trung Email trong danh sach
            for (size_t i = 0; i < dsNCC.size(); ++i) {
                if (toLowerStr(dsNCC[i].getEmail()) == toLowerStr(email)) { //toLowerStr dung de chuyen chu thuong de so sanh khong phan biet hoa thuong
                    trung = true;
                    break;
                }
            }
            
            if (trung) {
                cout << "=> LOI: Email da ton tai trong he thong! Vui long nhap lai.\n";
                continue;
            }
            
            break; // lenh break thoat vong lap khi ma hop le
        } while (true);
    }

    // Nap chong toan tu nhap (cin >> ncc)
    // Phien ban don gian, khong kiem tra trung
    friend istream& operator>>(istream& is, NhaCungCap& ncc) {
        cout << "\n--- NHAP THONG TIN NHA CUNG CAP ---\n";
        cout << "Ma NCC: "; getline(is, ncc.maNCC);
        cout << "Ten NCC: "; getline(is, ncc.tenNCC);
        cout << "Dia chi: "; getline(is, ncc.diaChi);
        
        // Kiem tra so dien thoai
        do {
            cout << "So dien thoai: ";
            getline(is, ncc.soDienThoai);
            if (!kiemTraSDT(ncc.soDienThoai)) {
                cout << "=> LOI: So dien thoai khong hop le (10 so, bat dau bang 0)!\n";
                cout << "Nhap lai ";
            } else break;
        } while (true);
        
        // Kiem tra email
        do {
            cout << "Email: ";
            getline(is, ncc.email);
            if (ncc.email.find('@') == string::npos) {
                cout << "=> LOI: Email phai chua ky tu '@'! Vui long nhap lai.\n";
            } else break;
        } while (true);
        
        return is;
    }

    // Nap chong toan tu xuat (cout << ncc)
    // setw de canh le
    friend ostream& operator<<(ostream& os, const NhaCungCap& ncc) {
        os << left << setw(12) << ncc.maNCC
           << setw(30) << ncc.tenNCC
           << setw(30) << ncc.diaChi
           << setw(15) << ncc.soDienThoai
           << setw(25) << ncc.email;
        return os;
    }

    // Khai bao ham ban de tu do truy cap private khi doc ghi
    friend void ghiFileNhaCungCap(const vector<NhaCungCap>&, const string&);
    friend void docFileNhaCungCap(vector<NhaCungCap>&, const string&);
};

// Ham tim kiem Nha cung cap theo Ma
// Tra ve index trong vector neu thay, -1 neu khong thay
int findNhaCungCap(const vector<NhaCungCap>& ds, const string& ma){
    for (size_t i=0;i<ds.size();++i) 
        if (ds[i].getMaNCC()==ma) 
            return (int)i;
    return -1;
}

// Ham sua thong tin Nha cung cap
void suaNhaCungCap(vector<NhaCungCap>& dsNCC){
    cin.ignore();
    string ma; 
    cout << "Nhap ma NCC can sua: "; 
    getline(cin, ma);
    // Tim vi tri can sua
    int idx = findNhaCungCap(dsNCC, ma);
    if (idx == -1) { 
        cout << "=> Khong tim thay!\n"; 
        return; 
    }
    
    cout << "=> Nhap lai thong tin NCC:\n";
    // Tao mot danh sach tam thoi KHONG CHUA phan tu dang sua
    //Muc dich: De khi nhap lai, neu nguoi dung giu nguyen Ma hoac Email cu thi vong lap kiem tra trung se k bao loi
    vector<NhaCungCap> dsTemp;
    for (size_t i = 0; i < dsNCC.size(); ++i) {
        if ((int)i != idx) {
            dsTemp.push_back(dsNCC[i]);
        }
    }
    // Goi ham nhap de len phan tu tai vi tri idx
    dsNCC[idx].nhapnhacungcap(dsTemp);
    
    cout << "=> Sua thanh cong!\n";
}

// ham xoa nha cung cap
void xoaNhaCungCap(vector<NhaCungCap>& dsNCC){
    cin.ignore();
    string ma; 
    cout << "Nhap ma NCC can xoa: "; 
    getline(cin, ma);
    
    int idx = findNhaCungCap(dsNCC, ma);
    if (idx == -1) { 
        cout << "=> Khong tim thay!\n"; 
        return; 
    }
    // Xoa phan tu tai vi tri tim thay
    dsNCC.erase(dsNCC.begin()+idx);
    cout << "=> Xoa thanh cong!\n";
}

// ham ghi file nha cung cap .txt
// Dinh dang: n dong, moi dong: ma|ten|dia chi|sdt|email
void ghiFileNhaCungCap(const vector<NhaCungCap>& ds, const string& tenFile) {
    ofstream f(tenFile);
    if (!f.is_open()) {
        cout << "LOI: Khong the mo file!\n"; return;
    }
    f << ds.size() << '\n'; //// Ghi so luong phan tu truoc
    for (const auto& ncc : ds) { // Duyet va ghi tung doi tuong
        f << ncc.maNCC << '|' << ncc.tenNCC << '|' << ncc.diaChi << '|'
          << ncc.soDienThoai << '|' << ncc.email << '\n';
    }
    f.close();
    cout << "=> Ghi file thanh cong!\n";
}

// ham doc file nha cung cap
void docFileNhaCungCap(vector<NhaCungCap>& ds, const string& tenFile) {
    ifstream f(tenFile);
    if (!f.is_open()) {
        cout << "LOI: Khong the mo file!\n"; return;
    }
    int n; f >> n; f.ignore(); // Doc so luong phan tu
    ds.clear(); // Xoa danh sach hien tai
    for (int i = 0; i < n; i++) {
        string line; getline(f, line);	
        vector<string> tok;
		size_t pos=0;
        while((pos=line.find('|'))!=string::npos){ tok.push_back(line.substr(0,pos)); line.erase(0,pos+1); }
        tok.push_back(line);
        if(tok.size()==5){
            ds.emplace_back(tok[0],tok[1],tok[2],tok[3],tok[4]);
        }
    }
    f.close();
    cout << "=> Doc file thanh cong!\n";
}

// ==================== LOP THUOC ====================
// Quan ly thong tin thuoc, lien ket toi NhaCungCap qua maNCC
class Thuoc {
private:
    string maThuoc;
    string tenThuoc;
    string loaiThuoc;
    string maNCC;
	string ngaynhap;  
    string hanSuDung;
    double giaNhap;
    double giaBan;
    int soLuongTon;

public:
	// ham khoi tao gia tri ban dau
    Thuoc() : maThuoc(""), tenThuoc(""), loaiThuoc(""), maNCC(""), ngaynhap(""), hanSuDung(""), giaNhap(0), giaBan(0), soLuongTon(0) {}
	// ham khoi tao tham so
    Thuoc(string ma, string ten, string loai, string maNCC, string nn, string hsd,double gianh, double giab, int sl) 
    : maThuoc(ma), tenThuoc(ten), loaiThuoc(loai), maNCC(maNCC), ngaynhap(nn), hanSuDung(hsd), giaNhap(gianh), giaBan(giab), soLuongTon(sl) {}

    // Ham nhap thong tin thuoc, kiem tra trung maThuoc va ton tai maNCC
    void nhap(const vector<NhaCungCap>& dsNCC, const vector<Thuoc>& dsThuoc) {
        cout << "\n--- NHAP THONG TIN THUOC ---\n";
        // kiem tra ma thuoc trung
        do {
            cout << "Ma thuoc: ";
            getline(cin, maThuoc);
            
            bool trung = false;
            for (size_t i = 0; i < dsThuoc.size(); ++i) {
                if (dsThuoc[i].getMaThuoc() == maThuoc) {
                    trung = true;
                    break;
                }
            }
            
            if (trung) {
                cout << "=> LOI: Ma thuoc da ton tai! Vui long nhap lai.\n";
            } else {
                break;
            }
        } while (true);
        
        cout << "Ten thuoc: "; getline(cin, tenThuoc);
        cout << "Loai thuoc: "; getline(cin, loaiThuoc);
        
        // Kiem tra ma nha cung cap ton tai
        bool found = false;
        do {
            cout << "Ma nha cung cap: "; 
            getline(cin, maNCC);
            
            found = false;
            for (const auto& ncc : dsNCC) {
                if (ncc.getMaNCC() == maNCC) {
                    found = true;
                    break;
                }
            }
            
            if (!found) {
                cout << "=> LOI: Ma nha cung cap khong ton tai! Vui long nhap lai.\n";
            }
        } while (!found);
        
        cout << "Ngay nhap (dd/mm/yyyy): "; getline(cin, ngaynhap);
        cout << "Han su dung (dd/mm/yyyy): "; getline(cin, hanSuDung);
        cout << "Gia nhap: "; cin >> giaNhap;
        // Rang buoc gia nhap phai lon hon 0
        while(giaNhap <= 0){
    		cout <<"Gia nhap phai lon hon 0 !\n";
			cout << "Gia nhap: "; cin >> giaNhap;
    	}
    	// Rang buoc gia ban phai lon hon 0
        cout << "Gia ban: "; cin >> giaBan;
        while(giaBan <= 0){
    		cout <<"Gia ban phai lon hon 0 !\n";
			cout << "Gia ban: "; cin >> giaBan;
    	}
        // Kiem tra gia ban 
        while(giaNhap > giaBan){
            cout << "=> LOI: Gia ban phai lon hon gia nhap!\n";
            cout << "Nhap lai gia ban: "; cin >> giaBan;
        }
        
        cout << "So luong ton: "; cin >> soLuongTon;
    }

    // Xuat thong tin thuoc ra bang
    void xuat() const {
        cout << left << setw(12) << maThuoc
             << setw(30) << tenThuoc
             << setw(20) << loaiThuoc
             << setw(12) << maNCC      
			 << setw(12) << ngaynhap 
             << setw(12) << hanSuDung
             // in so thap phan theo dinh dang
             << setw(12) << fixed << setprecision(0) << giaNhap
             // in so thap phan theo dinh dang
             << setw(12) << fixed << setprecision(0) << giaBan
             << setw(10) << soLuongTon << endl;
    }
	// tra ve thong tin thuoc (phuc vu tim kiem, hien thi, xu ly)
    string getMaThuoc() const { return maThuoc; }
	string getMaNCC() const { return maNCC; }
    string getTenThuoc() const { return tenThuoc; }
    double getGiaBan() const { return giaBan; }
    int getSoLuongTon() const { return soLuongTon; }

    // Giam so luong ton khi ban, khong cho am
    void giamSoLuong(int sl) { soLuongTon -= sl; if (soLuongTon < 0) soLuongTon = 0; }

    // Tang so luong ton khi nhap kho hoac hoan tra
    void tangSoLuong(int sl) { soLuongTon += sl; }
	// cho phep ham ben ngoai lop truy cap truc tiep ma thuoc, ten thuoc, ... du chung la private
    friend void ghiFileThuoc(const vector<Thuoc>&, const string&);
    friend void docFileThuoc(vector<Thuoc>&, const string&);
};

// Tim thuoc theo ma, tra ve index
int findThuoc(const vector<Thuoc>& ds, const string& ma) {
    for (size_t i = 0; i < ds.size(); ++i)
        if (ds[i].getMaThuoc() == ma)
            return (int)i;
    return -1;
}

//sua thuoc 
// Tao ds tam de kiem tra trung maThuoc khi sua
void suaThuoc(vector<Thuoc>& dsThuoc, const vector<NhaCungCap>& dsNCC) {
    cin.ignore();
    string ma; 
    cout << "Nhap ma thuoc can sua: "; 
    getline(cin, ma);
    
    int idx = findThuoc(dsThuoc, ma);
    if (idx == -1) {
        cout << "=> Khong tim thay thuoc!\n";
        return;
    }
    
    cout << "=> Nhap lai thong tin thuoc (ghi de ban cu):\n";
    
    // tao danh sach tam khong chua thuoc dang sua de kiem tra ma thuoc trung
    vector<Thuoc> dsTemp;
    for (size_t i = 0; i < dsThuoc.size(); ++i) {
        if ((int)i != idx) {
            dsTemp.push_back(dsThuoc[i]);
        }
    }
    
    dsThuoc[idx].nhap(dsNCC, dsTemp);  // Truyen dstemp de kiem tra ma trung
    cout << "=> Sua thanh cong!\n";
}

// xoa thuoc
void xoaThuoc(vector<Thuoc>& dsThuoc) {
    cin.ignore();
    string ma;
    cout << "Nhap ma thuoc can xoa: ";
    getline(cin, ma);

    int idx = findThuoc(dsThuoc, ma);
    if (idx == -1) {
        cout << "=> Khong tim thay thuoc!\n";
        return;
    }

    dsThuoc.erase(dsThuoc.begin() + idx);
    cout << "=> Xoa thanh cong!\n";
}

//cap nhat so luong thuoc (set so luong moi)
void capNhatSoLuongThuoc(vector<Thuoc>& dsThuoc) {
    cin.ignore();
    string ma;
    cout << "Nhap ma thuoc can cap nhat so luong: ";
    getline(cin, ma);

    int idx = findThuoc(dsThuoc, ma);
    if (idx == -1) {
        cout << "=> Khong tim thay thuoc!\n";
        return;
    }

    cout << "So luong ton hien tai: " << dsThuoc[idx].getSoLuongTon() << endl;
    int slmoi;
    cout << "Nhap so luong moi: ";
    cin >> slmoi;
    if (slmoi < 0) {
        cout << "=> So luong khong hop le!\n";
        return;
    }

    // Cap nhat: tangSoLuong theo (slmoi - hien tai)
    dsThuoc[idx].tangSoLuong(slmoi - dsThuoc[idx].getSoLuongTon());
    cout << "=> Cap nhat so luong thanh cong!\n";
}

// HAM GHI FILE THUOC
// Dinh dang: n dong => ma|ten|loai|maNCC|ngaynhap|HSD|giaNhap|giaBan|soLuong
void ghiFileThuoc(const vector<Thuoc>& ds, const string& tenFile) {
    ofstream f(tenFile);
    if (!f.is_open()) {
        cout << "LOI: Khong the mo file!\n";
        return;
    }
    f << ds.size() << endl;
    for (const auto& t : ds) {
        f << t.maThuoc << "|" << t.tenThuoc << "|" << t.loaiThuoc << "|"
  			<< t.maNCC << "|" << t.ngaynhap << "|" << t.hanSuDung << "|" 
  			<< t.giaNhap << "|" << t.giaBan << "|" << t.soLuongTon << endl;
    }
    f.close();
    cout << "=> Ghi file thanh cong!\n";
}

// HAM DOC FILE THUOC
void docFileThuoc(vector<Thuoc>& ds, const string& tenFile) {
    ifstream f(tenFile);
    if (!f.is_open()) {
        cout << "LOI: Khong the mo file!\n";
        return;
    }
    int n;
    f >> n;
    f.ignore();
    ds.clear();
    for (int i = 0; i < n; i++) {
        string line;
        getline(f, line);
        size_t pos = 0;
        vector<string> tokens;
        while ((pos = line.find('|')) != string::npos) {
            tokens.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        tokens.push_back(line);
        if (tokens.size() == 9) {
            Thuoc t(tokens[0], tokens[1], tokens[2], tokens[3],
                    tokens[4],tokens[5], stod(tokens[6]),stod(tokens[7]), stoi(tokens[8]));
            ds.push_back(t);
        }
    }
    f.close();
    cout << "=> Doc file thanh cong!\n";
}

// ==================== CHI TIET HOA DON ====================
// Luu thong tin tung dong thuoc trong hoa don
class ChiTietHoaDon {
protected:
    string maThuoc;
    string tenThuoc;
    int soLuong;
    double donGia;

public:
    // Constructor day du tham so: dung khi tao chi tiet hoa don voi du lieu cu the
    ChiTietHoaDon(string ma, string ten, int sl, double gia)
        : maThuoc(ma), tenThuoc(ten), soLuong(sl), donGia(gia) {};

    // Lay ma thuoc trong chi tiet hoa don (phuc vu tra cuu, lien ket voi danh sach thuoc)
    const string& getMaThuoc()  const { return maThuoc; }
    const string& getTenThuoc() const { return tenThuoc; }
    int           getSoLuong()  const { return soLuong; }
    double        getDonGia()   const { return donGia; }
    ChiTietHoaDon() : maThuoc(""), tenThuoc(""), soLuong(0), donGia(0) {};


    // Tinh thanh tien = so luong * don gia
    double tinhThanhTien() const {
        return soLuong * donGia;
    }

    // Xuat 1 dong chi tiet thuoc trong hoa don
    void xuat() const {
        cout << left << setw(12) << maThuoc
             << setw(30) << tenThuoc
             << setw(10) << soLuong
             << setw(15) << fixed << setprecision(0) << donGia
             << setw(15) << tinhThanhTien() << endl;
    }

    friend class HoaDon;
};

// ==================== HOA DON ====================
// Quan ly thong tin hoa don, chua danh sach ChiTietHoaDon
class HoaDon {
private:
    string maHD;
    string maKH;
    string maNV;
    string ngayLap; // dd/mm/yyyy
    vector<ChiTietHoaDon> danhSachThuoc;
    double tongTien;
    double giamGia;
    double thanhToan;

public:
    HoaDon() : maHD(""), maKH(""), maNV(""), ngayLap(""), tongTien(0), giamGia(0), thanhToan(0) {}
        
	// Hoa don hop le khi co it nhat 1 thuoc
	bool hopLe() const {
        return !danhSachThuoc.empty();
    }

    // Ham nhap hoa don moi
    // - Kiem tra trung maHD
    // - Kiem tra ton tai maKH, maNV
    // - Nhap danh sach thuoc, tru so luong trong kho
    // - Cap nhat diem tich luy va giam gia neu KH VIP
    void nhap(vector<HoaDon>& dsHD, vector<Thuoc>& dsThuoc, vector<KhachHang>& dsKH, vector<NhanVien>& dsNV) {  
        cout << "\n========== TAO HOA DON MOI ==========\n";
        // Kiem tra ma hoa don co bi trung khong
        do {
            cout << "Ma hoa don: ";
            getline(cin, maHD);
            
            bool trung = false;
            for (size_t i = 0; i < dsHD.size(); ++i) {
                if (dsHD[i].getMaHD() == maHD) {
                    trung = true;
                    break;
                }
            }
            
            if (trung) {
                cout << "=> LOI: Ma hoa don da ton tai! Vui long nhap lai.\n";
            } else {
                break;
            }
        } while (true);
        
        // Kiem tra ma khach hang co ton tai khong
        do {
            cout << "Ma khach hang: "; 
            getline(cin, maKH);
            
            bool foundKH = false;
            for (const auto& kh : dsKH) {
                if (kh.getMaKH() == maKH) {
                    foundKH = true;
                    break;
                }
            }
            
            if (!foundKH) {
                cout << "=> LOI: Ma khach hang khong ton tai! Vui long nhap lai.\n";
            } else {
                break;
            }
        } while (true);
        
        // Kiem tra ma nhan vien co ton tai khong
        do {
            cout << "Ma nhan vien: "; 
            getline(cin, maNV);
            
            bool foundNV = false;
            for (const auto& nv : dsNV) {
                if (nv.getMaNV() == maNV) {
                    foundNV = true;
                    break;
                }
            }
            
            if (!foundNV) {
                cout << "=> LOI: Ma nhan vien khong ton tai! Vui long nhap lai.\n";
            } else {
                break;
            }
        } while (true);

        cout << "Ngay lap (dd/mm/yyyy): "; 
        getline(cin, ngayLap);
        
        // Nhap thong tin thuoc
        int n;
        cout << "So loai thuoc mua: "; 
        cin >> n;
        cin.ignore();
        
        // Bien de kiem tra co loi khi nhap thuoc hay khong
        bool coLoiNhapThuoc = false; // logic chinh la kiem tra danhSachThuoc.empty()
        
        for (int i = 0; i < n; i++) {
            string maThuoc;
            int soLuong;
            cout << "\n--- Thuoc thu " << i + 1 << " ---\n";
            
            // VONG LAP NHAP LAI MA THUOC NEU KHONG TIM THAY
            bool timThayThuoc = false;
            do {
                cout << "Ma thuoc: "; 
                getline(cin, maThuoc);

                timThayThuoc = false;
                for (auto& thuoc : dsThuoc) {
                    if (thuoc.getMaThuoc() == maThuoc) {
                        timThayThuoc = true;
                        cout << "Ten thuoc: " << thuoc.getTenThuoc() << endl;
                        cout << "Gia ban: " << thuoc.getGiaBan() << " VND" << endl;
                        cout << "So luong ton: " << thuoc.getSoLuongTon() << endl;
                        
                        // Nhap so luong
                        do {
                            cout << "So luong mua: "; 
                            cin >> soLuong;
                            cin.ignore();

                            if (soLuong <= 0) {
                                cout << "=> LOI: So luong phai lon hon 0! Nhap lai.\n";
                                continue;
                            }
                            
                            if (soLuong > thuoc.getSoLuongTon()) {
                                cout << "=> LOI: Khong du thuoc trong kho (chi con " 
                                     << thuoc.getSoLuongTon() << ")! Nhap lai.\n";
                                continue;
                            }
                            
                            // Hop le -> them vao danh sach
                            ChiTietHoaDon ct(maThuoc, thuoc.getTenThuoc(), soLuong, thuoc.getGiaBan());
                            danhSachThuoc.push_back(ct);
                            thuoc.giamSoLuong(soLuong);
                            cout << "-> Them thanh cong!\n";
                            break;
                            
                        } while (true);
                        
                        break; // Thoat vong lap tim thuoc
                    }
                }
                
                // THONG BAO KHONG TIM THAY VA NHAP LAI
                if (!timThayThuoc) {
                    cout << "=> LOI: Khong tim thay thuoc co ma \"" << maThuoc 
                         << "\"! Vui long nhap lai.\n";
                }
                
            } while (!timThayThuoc); // Lap lai cho den khi tim thay thuoc
        }
        
        // Chi tinh tien khi khong co loi
        if (danhSachThuoc.empty()) {
            cout << "\n=> LOI: Hoa don khong co thuoc nao! Huy tao hoa don.\n";
            return;
        }

        tinhTongTien();

        // Cap nhat diem tich luy cho khach hang va ap dung giam gia neu VIP
        for (auto& kh : dsKH) {
            if (kh.getMaKH() == maKH) {
                if (kh.getLoaiKH() == "VIP") {
                    apDungGiamGia(10);
                    cout << "\n=> Ap dung giam gia 10% cho khach hang VIP!\n";
                } else {
                    apDungGiamGia(0);
                }
                // Cong diem tich luy theo 1% so tien thanh toan
                kh.tangDiemTichLuy(thanhToan * 0.01);
                break;
            }
        }
    }

    // Tinh tongTien tu danhSachThuoc
    void tinhTongTien() {
        tongTien = 0;
        for (const auto& ct : danhSachThuoc) {
            tongTien += ct.tinhThanhTien();
        }
        thanhToan = tongTien;
    }

    // Ap dung giam gia theo phan tram
    void apDungGiamGia(double phanTram) {
        giamGia = tongTien * phanTram / 100.0;
        thanhToan = tongTien - giamGia;
    }

    // In thong tin hoa don chi tiet
    void xuat() const {
        cout << "\n============== HOA DON ==============\n";
        cout << "Ma hoa don: " << maHD << endl;
        cout << "Ma khach hang: " << maKH << endl;
        cout << "Ma nhan vien: " << maNV << endl;
        cout << "Ngay lap: " << ngayLap << endl;
        cout << "-------------------------------------\n";
        cout << left << setw(12) << "Ma thuoc"
             << setw(30) << "Ten thuoc"
             << setw(10) << "SL"
             << setw(15) << "Don gia"
             << setw(15) << "Thanh tien" << endl;
        cout << string(82, '-') << endl;

        for (const auto& ct : danhSachThuoc) {
            ct.xuat();
        }

        cout << string(82, '-') << endl;
        cout << fixed << setprecision(0);
        cout << "TONG TIEN:        " << setw(20) << right << tongTien << " VND\n";
        cout << "GIAM GIA:         " << setw(20) << right << giamGia << " VND\n";
        cout << "THANH TOAN:       " << setw(20) << right << thanhToan << " VND\n";
        cout << "=====================================\n";
    }

    // Cac ham getter cua hoa don:
    // - getMaKH()      : tra ve ma khach hang gan voi hoa don
    // - getThanhToan(): tra ve so tien cuoi cung khach phai thanh toan (sau giam gia)
    // - getMaHD()      : tra ve ma hoa don (dung de tim kiem, xoa, sua)
    // - getChiTiet()   : tra ve danh sach cac dong chi tiet hoa don (danhSachThuoc)
    // - getNgayLap()   : tra ve ngay lap hoa don (dung cho thong ke doanh thu theo ngay, tim kiem)
    string getMaKH() const { return maKH; }
    double getThanhToan() const { return thanhToan; }
    string getMaHD() const { return maHD; }
    const vector<ChiTietHoaDon>& getChiTiet() const { return danhSachThuoc; }
    const string& getNgayLap() const { return ngayLap; }
	

    // Cho phep ham doc/ghi file truy cap
    friend void ghiFileHoaDon(const vector<HoaDon>&, const string&);
    friend void docFileHoaDon(vector<HoaDon>&, const string&);
};

// Tim hoa don theo ma
int findHoaDon(const vector<HoaDon>& ds, const string& ma) {
    for (size_t i = 0; i < ds.size(); ++i)
        if (ds[i].getMaHD() == ma)
            return (int)i;
    return -1;
}

// Xoa hoa don
// - Hien thi truoc khi xoa
// - Hoi xac nhan
// - Hoan tra so luong thuoc ve kho
void xoaHoaDon(vector<HoaDon>& dsHD, vector<Thuoc>& dsThuoc) {
    cin.ignore();
    string ma;
    cout << "Nhap ma hoa don can xoa: ";
    getline(cin, ma);
    
    int idx = findHoaDon(dsHD, ma);
    if (idx == -1) {
        cout << "=> Khong tim thay hoa don!\n";
        return;
    }
    
    // Hien thi thong tin hoa don truoc khi xoa
    cout << "\n--- Thong tin hoa don se xoa ---\n";
    dsHD[idx].xuat();
    
    // Xac nhan xoa
    char confirm;
    cout << "\nBan co chac chan muon xoa hoa don nay? (Y/N): ";
    cin >> confirm;
    cin.ignore();
    
    if (confirm != 'Y' && confirm != 'y') {
        cout << "=> Da huy xoa!\n";
        return;
    }
    
    // Hoan tra so luong thuoc ve kho
    const vector<ChiTietHoaDon>& chiTiet = dsHD[idx].getChiTiet();
    for (size_t i = 0; i < chiTiet.size(); ++i) {
        const ChiTietHoaDon& ct = chiTiet[i];
        
        // Tim thuoc trong kho va hoan tra so luong
        for (auto& thuoc : dsThuoc) {
            if (thuoc.getMaThuoc() == ct.getMaThuoc()) {
                thuoc.tangSoLuong(ct.getSoLuong());
                cout << "=> Hoan tra " << ct.getSoLuong() 
                     << " " << ct.getTenThuoc() << " ve kho\n";
                break;
            }
        }
    }
    
    // Xoa hoa don
    dsHD.erase(dsHD.begin() + idx);
    cout << "=> Xoa hoa don thanh cong!\n";
}

// HAM GHI FILE HOA DON
// Dinh dang:
// HD:maHD|maKH|maNV|ngayLap|tongTien|giamGia|thanhToan
// CT:maThuoc|tenThuoc|soLuong|donGia
void ghiFileHoaDon(const vector<HoaDon>& ds, const string& tenFile) {
    ofstream f(tenFile);
    if (!f.is_open()) {
        cout << "LOI: Khong the mo file!\n";
        return;
    }
    for (const auto& hd : ds) {
        f << "HD:" << hd.maHD << "|" << hd.maKH << "|" << hd.maNV << "|"
          << hd.ngayLap << "|" << hd.tongTien << "|" << hd.giamGia << "|"
          << hd.thanhToan << endl;
        for (const auto& ct : hd.danhSachThuoc) {
            f << "CT:" << ct.getMaThuoc() << "|" << ct.getTenThuoc() << "|"
              << ct.getSoLuong() << "|" << ct.getDonGia() << endl;
        }
    }
    f.close();
    cout << "=> Ghi file hoa don thanh cong!\n";
}

// HAM DOC FILE HOA DON
// Doc dung dinh dang do ghiFileHoaDon tao ra
void docFileHoaDon(vector<HoaDon>& ds, const string& tenFile) {
    ifstream f(tenFile);
    if (!f.is_open()) {
        cout << "LOI: Khong the mo file!\n";
        return;
    }
    
    ds.clear(); 
    string line;
    HoaDon hd; 
    bool trongHoaDon = false;

    while (getline(f, line)) {
        if (line.empty()) continue;

        if (line.rfind("HD:", 0) == 0) {
            // Luu hoa don cu truoc khi tao moi 
            if (trongHoaDon && !hd.danhSachThuoc.empty()) {  // Kiem tra them
                ds.push_back(hd);
            }

            trongHoaDon = true;
            hd = HoaDon(); 

            line = line.substr(3); 
            vector<string> t;
            size_t pos = 0;
            while ((pos = line.find('|')) != string::npos) {
                t.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            t.push_back(line);

            if (t.size() == 7) {
                hd.maHD        = t[0];
                hd.maKH        = t[1];
                hd.maNV        = t[2];
                hd.ngayLap     = t[3];
                hd.tongTien    = stod(t[4]);
                hd.giamGia     = stod(t[5]);
                hd.thanhToan   = stod(t[6]);
            }
        }
        else if (line.rfind("CT:", 0) == 0 && trongHoaDon) { 
            line = line.substr(3);
            vector<string> c;
            size_t pos = 0;
            while ((pos = line.find('|')) != string::npos) {
                c.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            c.push_back(line);

            if (c.size() == 4) {
                ChiTietHoaDon ct(c[0], c[1], stoi(c[2]), stod(c[3]));
                hd.danhSachThuoc.push_back(ct);
            }
        }
    }

    // Luu hoa don cuoi cung
    if (trongHoaDon && !hd.danhSachThuoc.empty()) { 
        ds.push_back(hd);
    }

    f.close();
    cout << "=> Doc file hoa don thanh cong! (" << ds.size() << " hoa don)\n";
}

// ==================== MENU QUAN LY ====================
// Menu quan ly khach hang: them, xem, tim, sua, xoa, cap nhat diem, doc/ghi file
void menuKhachHang(vector<KhachHang>& dsKH) {
    int choice;
    do {
        cout << "\n========== QUAN LY KHACH HANG ==========\n";
        cout << "1. Them khach hang\n";
        cout << "2. Hien thi danh sach\n";
        cout << "3. Tim kiem khach hang\n";
        cout << "4. Sua khach hang\n";    
        cout << "5. Xoa khach hang\n";        
        cout << "6. Cap nhat diem tich luy\n"; 
		cout << "7. Ghi file\n";
        cout << "8. Doc file\n"; 
        cout << "0. Quay lai\n";
        cout << "Chon: "; cin >> choice;

        switch (choice) {
            case 1: {
			    KhachHang kh;
			    cin.ignore();
			    string maKH;
			    kh.nhap(dsKH);
			    dsKH.push_back(kh);
			    cout << "\n=> Them thanh cong!\n";
			    break;
			    }
            case 2: {
                if (dsKH.empty()) {
                    cout << "\n=> Danh sach trong!\n";
                    break;
                }
                cout << "\n========== DANH SACH KHACH HANG ==========\n";
                cout << left << setw(12) << "Ma KH" << setw(25) << "Ho ten"
                     << setw(12) << "Ngay sinh" << setw(10) << "Gioi tinh"
                     << setw(25) << "Dia chi" << setw(12) << "SDT"
                     << setw(15) << "Hang" << setw(15) << "Diem" << endl;
                cout << string(120, '-') << endl;
                for (const auto& kh : dsKH) cout << kh << endl;
                break;
            }
			case 3: {
			    cin.ignore();
			    string ma;
			    cout << "Nhap ma khach hang: ";
			    getline(cin, ma);
			    bool found = false;
			    
			    cout << left << setw(12) << "Ma KH" << setw(25) << "Ho ten"
			         << setw(12) << "Ngay sinh" << setw(10) << "Gioi tinh"
			         << setw(30) << "Dia chi" << setw(12) << "SDT"
			         << setw(15) << "Hang" << setw(15) << "Diem" << "\n"
			         << string(120,'-') << "\n";
			         
			    for (const auto& kh : dsKH) {
			        if (kh.getMaKH() == ma) {
			            cout << kh << endl; 
			            found = true;
			            break;
			        }
			    }
			    if (!found) cout << "\n=> Khong tim thay!\n";
			    break;
			}
            case 4: suaKhachHang(dsKH); break;   
            case 5: xoaKhachHang(dsKH); break;     
            case 6: capNhatDiemKhachHang(dsKH); break;
			case 7: ghiFileKhachHang(dsKH, "khachhang.txt"); break;
            case 8: docFileKhachHang(dsKH, "khachhang.txt"); break;
        }
    } while (choice != 0);
}

// Menu quan ly nhan vien
void menuNhanVien(vector<NhanVien>& dsNV) {
    int choice;
    do {
        cout << "\n========== QUAN LY NHAN VIEN ==========\n";
        cout << "1. Them nhan vien\n";
        cout << "2. Hien thi danh sach\n";
        cout << "3. Tim kiem nhan vien theo ma\n";
        cout << "4. Sua nhan vien\n";
        cout << "5. Xoa nhan vien\n";
        cout << "6. Ghi file\n";
        cout << "7. Doc file\n";
        cout << "0. Quay lai\n";
        cout << "========================================\n";
        cout << "Chon: "; cin >> choice;

        switch (choice) {
			case 1: {
			    NhanVien nv;
			    cin.ignore();
			    nv.nhap(dsNV);
			    dsNV.push_back(nv);
			    cout << "\n=> Them thanh cong!\n";
			    break;
			}
            case 2: {
                if (dsNV.empty()) {
                    cout << "\n=> Danh sach trong!\n";
                    break;
                }
                cout << "\n========== DANH SACH NHAN VIEN ==========\n";
                cout << left << setw(12) << "Ma NV" << setw(25) << "Ho ten"
                     << setw(12) << "Ngay sinh" << setw(10) << "Gioi tinh"
                     << setw(30) << "Dia chi" << setw(12) << "SDT"
                     << setw(15) << "Email" << setw(12) << "Chuc vu" << setw(12) << "Luong CB"
                     << setw(12) << "Phu cap" << setw(12) << "Tong luong" << endl;
                cout << string(165, '-') << endl;
                for (const auto& nv : dsNV) cout << nv << endl;
                break;
				}
			case 3: {
			    cin.ignore();
			    string ma;
			    cout << "Nhap ma nhan vien: ";
			    getline(cin, ma);
			    bool found = false;
			    cout << left << setw(12) << "Ma NV" << setw(25) << "Ho ten"
                     << setw(12) << "Ngay sinh" << setw(10) << "Gioi tinh"
                     << setw(30) << "Dia chi" << setw(12) << "SDT"
                     << setw(15) << "Email" << setw(12) << "Chuc vu" << setw(12) << "Luong CB"
                     << setw(12) << "Phu cap" << setw(12) << "Tong luong" << endl;
                cout << string(165, '-') << endl;
			    for (const auto& nv : dsNV) {
			        if (nv.getMaNV() == ma) {
			            cout << nv << endl; 
			            found = true;
			            break;
			        }
			    }
			    if (!found) cout << "\n=> Khong tim thay!\n";
			    break;
			}
            case 4: suaNhanVien(dsNV); break;  
            case 5: xoaNhanVien(dsNV); break; 
            case 6: ghiFileNhanVien(dsNV, "nhanvien.txt"); break;
            case 7: docFileNhanVien(dsNV, "nhanvien.txt"); break;
            }

        }
		 while (choice != 0);
}

// Menu quan ly nha cung cap
void menuNhaCungCap(vector<NhaCungCap>& dsNCC) {
    int ch;
    do {
    	//// Hien thi menu chuc nang quan ly nha cung cap
        cout << "\n========== QUAN LY NHA CUNG CAP ==========\n";
    	cout << "1. Them nha cung cap\n";
        cout << "2. Hien thi danh sach\n";
        cout << "3. Tim kiem theo ma/ten\n";
        cout << "4. Sua nha cung cap\n";
        cout << "5. Xoa nha cung cap\n";
        cout << "6. Ghi file\n";
        cout << "7. Doc file\n";
        cout << "0. Quay lai\n";
        cout << "==========================================\n";
        cout << "Chon: ";
		cin>>ch;

        switch(ch){
            case 1:{
            	// --- Them moi nha cung cap 
                NhaCungCap ncc;
				cin.ignore(); // Xoa bo nho dem
				ncc.nhapnhacungcap(dsNCC); // Goi ham nhap co kiem tra trung lap
				dsNCC.push_back(ncc); // Them doi tuong vao danh sach vector
                cout << "=> Them thanh cong!\n"; break;
            }
            // su dung nap chong toan tu xuat
			case 2: {// Hien thi danh sach 
			    if (dsNCC.empty()) { 
			        break; 
			    }
			    
			    // In header setw de can dong
			    cout << left << setw(12) << "Ma NCC" 
			         << setw(30) << "Ten NCC"
			         << setw(30) << "Dia chi" 
			         << setw(15) << "SDT" 
			         << setw(25) << "Email" << '\n';
			    cout << string(112, '-') << '\n'; // Ke duong ngang phan cach
			    
			    // Duyet va in tung phan tu su dung nap chong toan tu xuat (<<)
			    for (const auto& ncc : dsNCC) { 
			        cout << ncc << '\n';  
			    }
			    break;
			}
			// Su dung nap chong toan tu xuat
		    case 3: {
		    	// Tim kiem ncc theo ma hoac ten (tim mo)
		        cin.ignore();
		        string key; 
		        cout << "Nhap tu khoa: "; 
		        getline(cin, key);
		        
		        bool found = false; // Bien co danh dau xem co tim thay khong
				
				// In header bang ket qua
		        cout << left << setw(12) << "Ma NCC" 
		             << setw(30) << "Ten NCC"	
		             << setw(30) << "Dia chi" 
		             << setw(15) << "SDT" 
		             << setw(25) << "Email" << '\n';
		        cout << string(112, '-') << '\n';
		        
		        //Su dung nap chong toan tu xuat
		        for (const auto& ncc : dsNCC) {
		            if (containsCaseInsensitive(ncc.getMaNCC(), key)
		             || containsCaseInsensitive(ncc.getTenNCC(), key)) {
		                cout << ncc << '\n';
		                found = true;
		            }
		        }
		        
		        if (!found) cout << "=> Khong tim thay!\n";
		        break;
		    }
            case 4: suaNhaCungCap(dsNCC); break;  // Goi ham sua thong tin
            case 5: xoaNhaCungCap(dsNCC); break;  // Goi ham xoa  thong tin
            case 6: ghiFileNhaCungCap(dsNCC,"nhacungcap.txt"); break; // Ghi du lieu xuong file cung
            case 7: docFileNhaCungCap(dsNCC,"nhacungcap.txt"); break;// Doc du lieu tu file len vector
        }
    }while(ch!=0); // Lap lai den khi nguoi dung chon 0
}

// Menu quan ly thuoc
void menuThuoc(std::vector<Thuoc>& dsThuoc, const std::vector<NhaCungCap>& dsNCC) {
    int choice;
    do {
        cout << "\n========== QUAN LY THUOC ==========\n";
        cout << "1. Them thuoc\n";
        cout << "2. Hien thi danh sach\n";
        cout << "3. Tim kiem thuoc\n";
        cout << "4. Cap nhat so luong ton\n";
        cout << "5. Sua thong tin thuoc\n";  
        cout << "6. Xoa thuoc\n";  
		cout << "7. Ghi file\n";
        cout << "8. Doc file\n";          
        cout << "0. Quay lai\n";
        cout << "=====================================\n";
        cout << "Chon: "; cin >> choice;

        switch(choice) {
			case 1: {
			    Thuoc t; 
				cin.ignore(); 
			    t.nhap(dsNCC, dsThuoc);
			    dsThuoc.push_back(t);
			    cout << "=> Them thanh cong!\n";
			    break;
			}
           case 2: {
    			if (dsThuoc.empty()) { cout << "=> Danh sach trong!\n"; break; }
			    cout << left << setw(12) << "Ma Thuoc"
			         << setw(30) << "Ten Thuoc"
			         << setw(20) << "Loai"
			         << setw(12) << "Ma NCC" 
					 << setw(12) << "Ngay nhap"    
			         << setw(12) << "HSD"
			         << setw(12) << "Gia Ban"
			         << setw(12) << "Gia Nhap"
			         << setw(10) << "So Luong" << endl;
			    cout << string(128, '-') << endl;
			    for (const auto& t : dsThuoc) t.xuat();
			    break;
			}
            case 3: {
                cin.ignore();
                string ma; cout << "Nhap ma thuoc can tim: "; getline(cin, ma);
                bool found = false;
                
			    cout << left << setw(12) << "Ma Thuoc"
			         << setw(30) << "Ten Thuoc"
			         << setw(20) << "Loai"
			         << setw(12) << "Ma NCC" 
					 << setw(12) << "Ngay nhap"    
			         << setw(12) << "HSD"
			         << setw(12) << "Gia Ban"
			         << setw(12) << "Gia Nhap"
			         << setw(10) << "So Luong" << endl;
			    cout << string(128, '-') << endl;
                for (const auto& t : dsThuoc)
                    if (t.getMaThuoc() == ma) { t.xuat(); found = true; break; }
                if (!found) cout << "=> Khong tim thay!\n";
                break;
            }
            case 4: capNhatSoLuongThuoc(dsThuoc); break;
			case 5: suaThuoc(dsThuoc,dsNCC); break; 
			case 6: xoaThuoc(dsThuoc); break;
            case 7: ghiFileThuoc(dsThuoc, "thuoc.txt"); break;
            case 8: docFileThuoc(dsThuoc, "thuoc.txt"); break;
        }
    } while(choice != 0);
}

// menu chon cua hoa don 
void menuHoaDon(vector<HoaDon>& dsHD, vector<Thuoc>& dsThuoc, 
                vector<KhachHang>& dsKH, vector<NhanVien>& dsNV) {
    int choice;
    do {
        cout << "\n========== QUAN LY HOA DON ==========\n";
        cout << "1. Tao hoa don moi\n";
        cout << "2. Hien thi tat ca hoa don\n";
        cout << "3. Tim hoa don\n";
        cout << "4. Xoa hoa don\n";             
        cout << "5. Ghi file hoa don\n";
        cout << "6. Doc file hoa don\n";
        cout << "0. Quay lai\n";
        cout << "=====================================\n";
        cout << "Chon: "; 
        cin >> choice;

        switch (choice) {
            case 1: {
                cin.ignore();
                HoaDon hd;
                hd.nhap(dsHD, dsThuoc, dsKH, dsNV);
                
                if (hd.hopLe()) {
                    dsHD.push_back(hd);
                    cout << "\n=> Tao hoa don thanh cong!\n";
                    hd.xuat();
                }
                break;
            }
            case 2: {
                if (dsHD.empty()) { 
                    cout << "\n=> Chua co hoa don!\n"; 
                    break; 
                }
                for (const auto& hd : dsHD) hd.xuat();
                break;
            }
            case 3: {
                cin.ignore();
                string ma;
                cout << "Nhap ma hoa don: ";
                getline(cin, ma);
                bool found = false;
                for (const auto& hd : dsHD) {
                    if (hd.getMaHD() == ma) {
                        hd.xuat();
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "\n=> Khong tim thay!\n";
                break;
            }
            case 4: {                           
                xoaHoaDon(dsHD, dsThuoc);
                break;
            }
            case 5: {
                ghiFileHoaDon(dsHD, "hoadon.txt");
                break;
            }
            case 6: {
                docFileHoaDon(dsHD, "hoadon.txt");
                break;
            }
        }
    } while (choice != 0);
}

// ======= SEARCH SERVICE =======
// Cung cap cac ham tim kiem theo tu khoa cho cac doi tuong trong he thong
// Bao gom: khach hang, nhan vien, thuoc, hoa don
class SearchService {
public:
    // Tim khach hang theo tu khoa: co the nhap ten, so dien thoai hoac ngay sinh
    static void  TimKhachHang(const vector<KhachHang>& ds){
        cin.ignore();                 // Xoa bo dem newline con lai truoc khi getline
        string key;         
        bool found=false;
        cout << "Nhap tu khoa (ten/sdt/ngay sinh): " ; 
        getline(cin, key);           // Nhan chuoi tu khoa tim kiem

        // In tieu de bang ket qua
        cout << left << setw(12) << "Ma KH" << setw(25) << "Ho ten"
             << setw(12) << "Ngay sinh" << setw(10) << "Gioi tinh"
             << setw(30) << "Dia chi" << setw(12) << "SDT"
             << setw(15) << "Loai" << setw(15) << "Diem" << "\n"
             << string(121,'-') << "\n";
                
        // Duyet toan bo danh sach khach hang va so sanh khong phan biet hoa thuong
        for (const KhachHang& kh : ds){
            if (containsCaseInsensitive(kh.getHoTen(), key)      // tim theo ten
             || containsCaseInsensitive(kh.getSoDienThoai(), key) // tim theo SDT
             || containsCaseInsensitive(kh.getNgaySinh(), key)) { // tim theo ngay sinh
                cout << kh << endl; // su dung toan tu << da nap chong
                found=true;
            }
        }
        if(!found){
            cout << "=> Khong tim thay!\n";
        }
    }

    // Tim nhan vien theo tu khoa: ten, so dien thoai hoac ngay sinh
    static void TimNhanVien(const vector<NhanVien>& ds){
        cin.ignore();                 // Xoa bo dem truoc khi getline
        string key; 
        cout << "Nhap tu khoa (ten/sdt/ngay sinh): " << flush; 
        getline(cin, key);

        bool found=false;

        // In tieu de bang ket qua
        cout << left << setw(12) << "Ma NV" << setw(25) << "Ho ten"
             << setw(12) << "Ngay sinh" << setw(10) << "Gioi tinh"
             << setw(30) << "Dia chi" << setw(12) << "SDT"
             << setw(15) << "Email" << setw(12) << "Chuc vu" << setw(12) << "Luong CB"
             << setw(12) << "Phu cap" << setw(12) << "Tong luong" << endl;
        cout << string(120, '-') << endl;

        // Duyet danh sach nhan vien va tim theo ten/SDT/ngay sinh (khong phan biet hoa thuong)
        for (const NhanVien& nv : ds){
            if (containsCaseInsensitive(nv.getHoTen(), key)
             || containsCaseInsensitive(nv.getSoDienThoai(), key)
             || containsCaseInsensitive(nv.getNgaySinh(), key)) {
                cout << nv << endl;    // In thong tin nhan vien
                found=true;
            }
        }
        if(!found) 
            cout << "=> Khong tim thay!\n";
    }

    // Tim thuoc theo ma hoac ten (co the nhap mot phan ma/ten)
    static void TimThuoc(const vector<Thuoc>& ds){
        cin.ignore();                 // Xoa bo dem truoc khi getline
        string key; 
        cout << "Nhap tu khoa (ma/ten): " << flush; 
        getline(cin, key);

        bool found=false;

        // In tieu de bang hien thi danh sach thuoc
        cout << left << setw(12) << "Ma Thuoc"
             << setw(30) << "Ten Thuoc"
             << setw(20) << "Loai"
             << setw(12) << "Ma NCC" 
             << setw(12) << "Ngay nhap"    
             << setw(12) << "HSD"
             << setw(12) << "Gia Ban"
             << setw(12) << "Gia Nhap"
             << setw(10) << "So Luong" << "\n";
        cout << string(128, '-') << "\n";

        // Duyet danh sach thuoc va tim kiem theo ma hoac ten thuoc
        for (const Thuoc& t : ds){
            if (containsCaseInsensitive(t.getMaThuoc(), key)
             || containsCaseInsensitive(t.getTenThuoc(), key)) {
                t.xuat();             // Goi ham xuat() cua Thuoc
                found=true;
            }
        }
        if(!found) 
            cout << "=> Khong tim thay!\n";
    }

    // Tim hoa don theo ma hoa don hoac theo ngay lap
    static void TimHoaDon(const vector<HoaDon>& ds){
        cin.ignore();                 // Xoa bo dem truoc khi getline
        string key; 
        cout << "Nhap tu khoa (maHD/ngay lap(dd/mm/yy)): " << flush; 
        getline(cin, key);
		
        bool found=false;

        // Duyet danh sach hoa don va tim theo ma hoa don hoac ngay lap
        for (const HoaDon& hd : ds){
            if (containsCaseInsensitive(hd.getMaHD(), key)
             || containsCaseInsensitive(hd.getNgayLap(), key)) {
                hd.xuat();            // In chi tiet hoa don
                found=true;
            }
        }
        if(!found) 
            cout << "=> Khong tim thay!\n";
    }
};


// ======= STATS SERVICE =======
// Cung cap cac thong ke doanh thu, khach hang, thuoc
// Lop dich vu (Service) chuyen lam thong ke, bao cao
// Tat ca ham deu la static --> khong can tao doi tuong StartService, chi can goi:
// StatsService::DoanhThuTong(dsHD);
// StatsService::TopThuocBanChay(dsHD, 5)
class StatsService {
public:
    // Tinh tong doanh thu tat ca hoa don
    static void DoanhThuTong(const vector<HoaDon>& ds){
        double s = 0.0;
        for (const HoaDon& hd : ds) s += hd.getThanhToan();
        cout << "Tong doanh thu: " << fixed << setprecision(0) << s << " VND\n";
    }
	// Dung map de luu: ngay -> tong doanh thu cua ngay do.
	// Key: string (dinh dang ngay "dd/mm/yyyy").
	// Value: double (tong so tien cua ngay do).
    // Thong ke doanh thu theo tung ngay lap hoa don
    static void DoanhThuTheoNgay(const vector<HoaDon>& ds){
        map<string,double> byDay; // dd/mm/yyyy -> amount
        for (const HoaDon& hd : ds) byDay[hd.getNgayLap()] += hd.getThanhToan();

        cout << left << setw(15) << "Ngay" << right << setw(20) << "Doanh thu (VND)" << '\n'
             << string(35,'-') << '\n';
        for (map<string,double>::const_iterator it = byDay.begin(); it != byDay.end(); ++it){
            cout << left << setw(15) << it->first
                 << right << setw(20) << fixed << setprecision(0) << it->second << '\n';
        }
    }

    // Top N thuoc ban chay nhat (theo so luong ban ra)
    static void TopThuocBanChay(const vector<HoaDon>& ds, int topN){
        map<string, long long> slTheoMa;  // maThuoc -> so luong
        map<string, string>    tenTheoMa; // maThuoc -> ten

        for (const HoaDon& hd : ds){
            const vector<ChiTietHoaDon>& chiTiet = hd.getChiTiet();
            for (size_t i=0;i<chiTiet.size();++i){
                const ChiTietHoaDon& ct = chiTiet[i];
                slTheoMa[ct.getMaThuoc()] += ct.getSoLuong();
                tenTheoMa[ct.getMaThuoc()]  = ct.getTenThuoc();
            }
        }
        vector< pair<string,long long> > v(slTheoMa.begin(), slTheoMa.end());
        sort(v.begin(), v.end(),
             [](const pair<string,long long>& a, const pair<string,long long>& b){
                 return a.second > b.second;
             });

        cout << left << setw(12) << "Ma thuoc" << setw(30) << "Ten thuoc" << right << setw(10) << "SL ban" << '\n'
             << string(54,'-') << '\n';
        int cnt = 0;
        for (size_t i=0;i<v.size() && cnt<topN;++i,++cnt){
            const string& ma = v[i].first;
            cout << left << setw(12) << ma
                 << setw(30) << tenTheoMa[ma]
                 << right << setw(10) << v[i].second << '\n';
        }
        if (v.empty()) cout << "Chua co du lieu hoa don.\n";
    }
        // Ham thong ke thong tin khach hang (so luong VIP, Thuong, diem tich luy, diem TB)
	static void ThongKeKhachHang(const vector<KhachHang>& ds) {
	    int tongKH = ds.size();              // Tong so khach hang
	    int soVIP = 0, soThuong = 0;         // Dem so khach hang VIP va Thuong
	    double tongDiem = 0;                 // Tong diem tich luy cua tat ca khach hang
	    
	    // Duyet danh sach khach hang de tinh toan
	    for (const auto& kh : ds) {
	        if (kh.getLoaiKH() == "VIP")     // Neu loai KH la VIP thi tang bien dem VIP
                soVIP++;
	        else 
                soThuong++;                  // Nguoc lai la khach hang Thuong
	        
            tongDiem += kh.getDiemTichLuy(); // Cong don diem tich luy
	    }
	    
	    // In ket qua thong ke ra man hinh
	    cout << "\n========== THONG KE KHACH HANG ==========\n";
	    cout << "Tong so khach hang: " << tongKH << endl;
	    cout << "Khach hang VIP: " << soVIP 
	         << " (" << fixed << setprecision(1) 
	         // Neu tongKH > 0 thi moi tinh %, neu khong thi tranh chia cho 0
	         << (tongKH > 0 ? soVIP * 100.0 / tongKH : 0) << "%)" << endl;
	    cout << "Khach hang Thuong: " << soThuong 
	         << " (" << (tongKH > 0 ? soThuong * 100.0 / tongKH : 0) << "%)" << endl;
	    
        // In tong diem tich luy va diem trung binh tren moi khach hang
	    cout << "Tong diem tich luy: " << setprecision(0) << tongDiem << endl;
	    if (tongKH > 0) {
	        cout << "Diem trung binh: " << setprecision(1) 
	             << tongDiem / tongKH << " diem/khach" << endl;
	    }
	    cout << "========================================\n";
	}
	
    // Ham thong ke cac thuoc sap het hang, so luong ton < nguongToiThieu
	static void ThuocSapHet(const vector<Thuoc>& ds, int nguongToiThieu = 10) {
	    cout << "\n========== THUOC SAP HET (< " << nguongToiThieu << ") ==========\n";
	    cout << left << setw(12) << "Ma Thuoc"
	         << setw(30) << "Ten Thuoc"
	         << setw(10) << "Ton kho" << endl;
	    cout << string(52, '-') << endl;
	    
	    bool coThuoc = false; // Co it nhat 1 thuoc thoa dieu kien hay khong
	    
        // Duyet danh sach thuoc de tim nhung thuoc co so luong ton < nguong
	    for (const auto& t : ds) {
	        if (t.getSoLuongTon() < nguongToiThieu) {
	            cout << left << setw(12) << t.getMaThuoc()
	                 << setw(30) << t.getTenThuoc()
	                 << setw(10) << t.getSoLuongTon() << endl;
	            coThuoc = true;
	        }
	    }
	    
	    // Neu khong co thuoc nao sap het thi thong bao
	    if (!coThuoc) cout << "Tat ca thuoc deu du so luong.\n";
}
};

// Menu chuc nang tim kiem cho toan he thong
// Cho phep tim khach hang, nhan vien, thuoc, hoa don theo tu khoa
void menuTimKiem(const vector<KhachHang>& dsKH,
                 const vector<NhanVien>& dsNV,
                 const vector<Thuoc>& dsThuoc,
                 const vector<HoaDon>& dsHD)
{
    int c;
    do{
        cout << "\n========== TIM KIEM ==========\n"
             << "1. Khach hang\n"
             << "2. Nhan vien\n"
             << "3. Thuoc\n"
             << "4. Hoa don\n"
             << "0. Quay lai\n"
             << "==============================\n"
             << "Chon: " << flush;
        
        // Neu nhap khong phai so thi reset trang thai cin va nhap lai
        if(!(cin >> c)){ 
            cin.clear();      // Xoa co loi tren stream
            cin.ignore();     // Bo ky tu con lai trong buffer
            continue; 
        }

        // Xu ly lua chon tim kiem
        switch(c){
            case 1: 
                // Tim kiem khach hang theo tu khoa
                SearchService::TimKhachHang(dsKH); 
                break;
            case 2: 
                // Tim kiem nhan vien theo tu khoa
                SearchService::TimNhanVien(dsNV);  
                break;
            case 3: 
                // Tim kiem thuoc theo ma hoac ten
                SearchService::TimThuoc(dsThuoc);  
                break;
            case 4: 
                // Tim kiem hoa don theo ma hoac ngay lap
                SearchService::TimHoaDon(dsHD);    
                break;
        }
    }while(c != 0); // Lap lai den khi chon 0 de quay lai
}

// Menu thong ke va bao cao
// Gom cac chuc nang: doanh thu, top thuoc ban chay, thong ke khach hang, thuoc sap het hang
void menuThongKe(const vector<HoaDon>& dsHD,
                 const vector<Thuoc>& dsThuoc,
                 const vector<KhachHang>& dsKH)
{
    int c;
    do{
        cout << "\n========== THONG KE & BAO CAO ==========\n"
             << "1. Doanh thu tong\n"
             << "2. Doanh thu theo ngay\n"
             << "3. Top N thuoc ban chay\n"
             << "4. Thong ke khach hang\n"              
             << "5. Thuoc sap het hang\n"               
             << "0. Quay lai\n"
             << "========================================\n"
             << "Chon: " << flush;
        
        // Kiem tra dau vao, neu sai thi cho nhap lai
        if(!(cin >> c)){ 
            cin.clear(); 
            cin.ignore(); 
            continue; 
        }

        // Xu ly tung chuc nang thong ke
        switch(c){
            case 1: 
                // Tinh va in tong doanh thu
                StatsService::DoanhThuTong(dsHD); 
                break;
            case 2: 
                // Thong ke doanh thu theo tung ngay
                StatsService::DoanhThuTheoNgay(dsHD); 
                break;
            case 3: {
                // Thong ke top N thuoc ban chay nhat
                int n; 
                cout << "Nhap N: " << flush; 
                cin >> n;
                if(n<1) n=1;  // Dam bao N toi thieu la 1
                StatsService::TopThuocBanChay(dsHD, n);
                break;
            }
            case 4: 
                // Thong ke khach hang (VIP, Thuong, diem)
                StatsService::ThongKeKhachHang(dsKH); 
                break;
            case 5: {
                // Thong ke thuoc sap het hang theo nguong nhap vao
                int nguong;
                cout << "Nhap nguong toi thieu (mac dinh 10): ";
                cin >> nguong;
                if (nguong < 0) nguong = 10; // Neu nguong am thi lay lai mac dinh 10
                StatsService::ThuocSapHet(dsThuoc, nguong);
                break;
            }
        }
    }while(c != 0); // Thoat khi chon 0
}


// ==================== MAIN ====================
int main() {
    ios::sync_with_stdio(false); // Toi uu toc do I/O (khong dong bo voi C I/O)
                                 // => Giup cin/cout chay nhanh hon khi doc/ghi nhieu du lieu

    // Cac vector luu tru du lieu chinh cua he thong
    vector<KhachHang> dsKH;      // Danh sach khach hang
    vector<NhanVien>  dsNV;      // Danh sach nhan vien
    vector<Thuoc>     dsThuoc;   // Danh sach thuoc
    vector<HoaDon>    dsHD;      // Danh sach hoa don
	vector<NhaCungCap> dsNCC;    // Danh sach nha cung cap
    
    int choice;
    do {
        // Menu chinh cua chuong trinh
        cout << "\n============= MENU CHINH =============\n";
        cout << "1. Quan ly khach hang\n";
        cout << "2. Quan ly nhan vien\n";
        cout << "3. Quan ly thuoc\n";
        cout << "4. Quan ly hoa don\n";
        cout << "5. Quan ly nha cung cap\n";
        cout << "6. Tim kiem\n";               
        cout << "7. Thong ke\n";               
        cout << "0. Thoat\n";
        cout << "======================================\n";
        cout << "Chon: " << flush;

        // Kiem tra gia tri nhap vao cho choice
        if (!(cin >> choice)) {
            cin.clear();   // Xoa co loi
            cin.ignore();  // Bo ky tu khong hop le
            cout << "Lua chon khong hop le!\n";
            continue;
        }

        // Xu ly lua chon cua nguoi dung
        switch (choice) {
            case 1: 
                // Vao menu quan ly khach hang
                menuKhachHang(dsKH); 
                break;
            case 2: 
                // Vao menu quan ly nhan vien
                menuNhanVien(dsNV); 
                break;
            case 3: 
                // Vao menu quan ly thuoc (truyen ca danh sach NCC de rang buoc maNCC)
                menuThuoc(dsThuoc, dsNCC); 
                break;
            case 4: 
                // Vao menu quan ly hoa don
                menuHoaDon(dsHD, dsThuoc, dsKH, dsNV); 
                break;
            case 5: 
                // Vao menu quan ly nha cung cap
                menuNhaCungCap(dsNCC); 
                break;
            case 6: 
                // Menu tim kiem tong hop
                menuTimKiem(dsKH, dsNV, dsThuoc, dsHD); 
                break;
            case 7: 
                // Menu thong ke va bao cao
                menuThongKe(dsHD, dsThuoc, dsKH); 
                break;
            case 0:
                // Thoat chuong trinh
                cout << "Thoat chuong trinh...\n";
                break;
            default:
                // Truong hop nhap lua chon khong co trong menu
                cout << "Lua chon khong hop le!\n";
                break;
        }
    } while (choice != 0); // Lap lai den khi nguoi dung chon 0

    return 0;
}

