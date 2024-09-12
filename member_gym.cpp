/*
  judul : membuat program menejemen kasir member di sebuah gym 
  oleh  : rico 
  waktu : semarang, tembalang 17 februari 2024 - bertahap

  program ini menyakup 
    -pendaftaran menjadi member   sudah
    -penjadwalan pembayaran member belum
    -pemantauan waktu member  belum
    -cek data member   sudah
    -jenis keanggotaan   sudah
    -penjadwalan pembayaran   belum
    -pendataan pengunjung   sudah
    -penbayaran pengunjung  sudah
*/
#include<iostream> 
#include<iomanip>
#include<string>
#include<vector>//library untuk menggunakan vector untuk menyimpan data 
#include<ctime> //library untuk menampilkan waktu
#include<chrono>
#include<sstream>
using namespace std; 

//membuat tipe data bentukan untuk formulir pengisian data 
struct formulir{

  string nama,alamat,email, no_tlp,no_ktp,tanggal_pendaftaran,masamember;
  int berat_badan, tinggi_badan,umur,nomor_kartu; 
  bool status_pembayaran;
  string status_bayar;
  
};


int durasi_bulan;

//untuk mengambil tanggal bulan waktu secara real time 
string getTimeStr(){

    auto now = chrono::system_clock::now(); //mengambil waktu saat ini dari sistem
    auto now_time_t = chrono::system_clock::to_time_t(now);//mengkonversi time_point yang diambil ke dalam bentuk time_t
    tm* time_info = localtime(&now_time_t);//mengonversi time_t ke dalam std::tm yang berupa pointer ke struct std::tm yang menyimpan struktur waktu dalam format yang lebih terperinci

    //mengubah ke dalam format tanggal yang di inginkan 
    stringstream ss;
    ss << put_time(time_info, "%d %B %Y");
    return ss.str();
}

//fungsi untuk mengonversi string yang berformat tanggal ke dalam bentuk Tm 
tm stringToTm(const string& tanggal){
  //tm adalah struktur yang menyimpan informasi waktu, jam, menit, detik, tahun, bulan, hari, 
  tm tm = {}; //membuat object tm yang diinisialisasi 0 pada semua bidangnya 
  stringstream ss(tanggal); //inisialisasi object stringstream dengan nama ss dan input yang diambil dari parameter tanggal
  ss >> get_time(&tm, "%d %B %Y");//parsing string tanggal menggunakan format yang sudah di tentukan 
  //fungsi get_time adalah mencocokkan tanggal dengan format yang sudah diberikan, lalu disimpan didalam tm

  tm.tm_isdst = -1; 
  return tm; 
}

//konversi struktur tm yang isinya informasi waktu dalam format internal ke dalam bentuk string 
string tmToString(const tm& time_info){

  stringstream ss; // inisialisasi object stringstream dengan nama ss
  ss << put_time(&time_info, "%d %B %Y"); //fungsi put_time untuk konversi object time_info ke dalam format yang ditentukan 

  return ss.str();
}

//fungsi ini adalah untuk mendapatkan durasi waktu yang dibutuhkan 
string bulan(const string& tanggal, const int durasi){
  tm tm1 = stringToTm(tanggal); //membuat object tm yang diinisialisasi hasil dari fungsi strinToTm(tanggal)

  tm1.tm_mon += durasi; //menambahkan bulan ke dalam 
  mktime(&tm1);
  return tmToString(tm1);
}

//untuk menampilkan garis pemisah agar tampilan tidak terlalu amburadul
//garis single 
void single(){
  //kamus lokal 
  int x;
  //deskripsi 
  while(x < 60 )
  {
    cout << "-";
    x = x + 1 ;
  }
    cout << endl;
}
void garis(){
  //kamus lokal 
  int x;
  //deskripsi 
  while(x < 60 )
  {
    cout << "=";
    x = x + 1 ;
  }
    cout << endl;
}

//fungsi untuk membersihkan layar ketika masuk ke menu selanjutnuya
void clearscreen(){
  system("cls");
}

vector <formulir> member; //vector untuk menaruh data member
bool status_pembayaran_pengunjung;
int totalharga; 
int nomorkartu = 1; //variabel untuk inisialisasi nomor kartu member
int jumlahpendaftar = 0;

//fungsi untuk mengisi data formulir dan memasukkan data ke dalam array
void pendaftaran_member(vector<formulir>& member,formulir data,int &nomorkartu){
  //mengisi data formulir pendaftaran member sesuai jumlah orang yang daftar
  cout << "DAFTAR MEMBER :) \n";
  single();
  cout << "MOHON ISI DATA YANG DIMINTA !!\n";
  garis();
    cout << "formulir pendaftaran !! \n";
    cout << endl;
    cout << "masukkan nama " << setw(14) << ": ";
    getline(cin, data.nama);
    cout << "masukkan umur " << setw(14) << ": ";
    cin >> data.umur;
    cout << "masukkan berat "<< setw(13) << ": "; 
    cin >> data.berat_badan;
    cout << "masukkan tinggi " << setw(12) << ": ";
    cin >> data.tinggi_badan; 
    cin.ignore();//untuk mengabaikan karakter newline setelah membeca tipe data non-string
    cout << "masukkan alamat " << setw(12) << ": "; 
    getline(cin, data.alamat);
    cout << "masukkan no-telpon anda " << setw(4) << ": ";
    getline(cin, data.no_tlp);
    cout << "masukkan no-ktp anda " << setw(7) << ": ";
    getline(cin, data.no_ktp);
    cout << "masukkan e-mail anda " << setw(7) << ": ";
    getline(cin, data.email);
    single();
    cout << "INI no-kartu member anda " << setw(3) << ": " << nomorkartu << endl; 
    data.tanggal_pendaftaran = getTimeStr(); //mengambil data waktu secara real time 
    cout << data.tanggal_pendaftaran << endl;
    cout << endl;
    single();

    //logika penambahan data ke dalam vector dan ke menambahkan nomor kartu
    data.nomor_kartu = nomorkartu; 
    nomorkartu++; 
    member.push_back(data); //memasukkan data pendaftar ke dalam vector member belakang 
    cout << "Selamat pendaftaran berhasil!!" << endl; 
    garis();
}

void pembayaran(int &totalharga){

  int totalpembayaran = 0; // variabel untuk menyimpan nominal pembayaran 
  
    do {
        cout << "Pembayaran saat ini " << setw(5) << ": ";
        int pembayaranSaatIni; //variabel untuk nominal pertama 
        cin >> pembayaranSaatIni;

        if (pembayaranSaatIni > 0) {
            totalpembayaran += pembayaranSaatIni;

            if (totalpembayaran < totalharga) {
                
              cout << "yahh uang kamu kurang nihh !!\n";
              cout << "uang kamu sekarang " << setw(6) << ": "<< totalpembayaran << endl;
              int sudahbayar = (totalharga - pembayaranSaatIni); 
              cout << "uang kamu kurang " << setw(8)  << ": " << sudahbayar << endl; 
              totalharga = sudahbayar; 
              sudahbayar = 0;
              pembayaranSaatIni = 0;
              totalpembayaran = 0; 
            }
        } else {
            cout << "Pembayaran harus lebih dari 0.\n";
        }

    } while (totalpembayaran < totalharga);
  
  cout << "kembalian " << setw(15) << ": " << totalpembayaran - totalharga << endl;
  cout << "transaksi berhasil :)\n";
  
  status_pembayaran_pengunjung = true;
}

void bayar(const formulir &data, int &jumlahpendaftar, int dataharga[],int p){

  const formulir &pendaftar = member.back();
  
  cout << "anda memilih memilih pilihan " << p << endl; 

  cout << "Nama " << setw(17) << ":" << pendaftar.nama << endl; 
  cout << "Alamat " << setw(15) << ":" << pendaftar.alamat << endl; 
  cout << "No-telpon " << setw(12) << ":" << pendaftar.no_tlp << endl;
  cout << "Masa aktif " << setw(11) << ":"<< data.masamember << endl;
  cout << endl; 
  cout << "berikut harga yang harus anda bayar" << endl; 
  p--;
  totalharga = (dataharga[p] * jumlahpendaftar);
  cout << "Total Harga : " << totalharga << endl; 
  cin.ignore(); 
  single();
  pembayaran(totalharga);

}

//prosedur pemilihan jenis member 
/*

  ada 5 penawaran member
  - 1 bulan   = 445.000   
  - 3 bulan   = 385.000   
  - 6 bulan   = 325.000

*/

//array data harga
int dataharga[3] = {445000,385000,325000};

void harga_member( int &jumlahpendaftar,int durasi_bulan){

  //kamus lokal 
  int pilih;
  formulir &data = member.back(); //mengakses vector member paling bawah dan melakukan perubahan 

  //deskripsi
  cout << "Daftar membership MAK GYM" << endl; 
  garis();
  cout << "pilihan 1 \n" "\t1(satu) bulan\n" "\t\t 445.000\n";
  single();
  cout << "pilihan 2 \n" "\t3(tiga) bulan\n" "\t\t 385.000\n";
  single();
  cout << "pilihan 3 \n" "\t6(enam) bulan\n" "\t\t 325.000\n";
  garis();
  cout << "Silahkan tentukan pilihan anda !!" << endl; 
  cout << "Pilih : " ; cin >> pilih;  

  //kondisi jika kita memilih dari tiga pilihan di atas 
  string masa_aktif; 
  if(pilih == 1){
    single();
    data.masamember = bulan(data.tanggal_pendaftaran,1);  
    bayar(data,jumlahpendaftar,dataharga,pilih);
  }else if(pilih == 2){
    single();
    data.masamember = bulan(data.tanggal_pendaftaran,3); //  
    bayar(data,jumlahpendaftar,dataharga,pilih);
  }else if(pilih == 3){
    single();    
    data.masamember = bulan(data.tanggal_pendaftaran,6);    
    bayar(data,jumlahpendaftar,dataharga,pilih);    
  }else {
    cout << "pilihan yang anda masukan tidak tersedia !!" << endl; 
    cout << "MATANE PICEK TA RA ONO BLOQ " << endl; 
  }

}

//menampilkan menu 
void tampildata(const formulir &data){
  
  cout << "nama " << setw(17) << ": " <<data.nama << endl;
  cout << "umur " << setw(17) << ": " << data.umur << endl; 
  cout << "berat badan " <<  setw(10) << ": " << data.berat_badan << endl; 
  cout << "tinggi badan " << setw(9) << ": " << data.tinggi_badan << endl; 
  cout << "alamat " << setw(15) << ": " << data.alamat << endl; 
  cout << "no-telpon " << setw(12) << ": " << data.no_tlp << endl; 
  cout << "no-ktp " << setw(15) << ": " << data.no_ktp << endl; 
  cout << "e-mail " << setw(15) << ": " << data.email << endl;      
  cout << "no-kartu member " << setw(6) << ": " << data.nomor_kartu << endl;  
  cout << "tanggal mendaftar " << setw(4) << ": " << data.tanggal_pendaftaran << endl; 
  cout << "Masa aktif member " << setw(4) << ": " << data.masamember << endl; 
  cout << endl; 
}

string mencarinama;
//untuk mencari nama member
void carimember( const vector<formulir>& member, string &mencarinama, const formulir &data){

  //kamus lokal 
  bool terdaftar = false; 
  string cari;
  //deskripsi
  cout << "Cek Data Member \n";
  garis(); 
  cout << "masukkan nama yang ingin di cek : ";
  getline(cin, mencarinama);
  cout << "Tunggu sebentar :)\n"; 
  single(); 
  for(const auto& data : member){
    if(data.nama.find(mencarinama) !=string::npos){
      cout << "Data di temukan!! \n";
      tampildata(data);
      terdaftar = true; 
      break;
    }
  }
  // kondisi jika tidak di temukan 
  if(!terdaftar){
    single();
    cout << "data tidak di temukan untuk nama : " << mencarinama << endl; 
    cout << "data anda tidak terdaftar!! \n";
  }

}

//membuat prosedur yang menjalankan tiga prosedur di bawah ini 
void utama(vector<formulir>& member,formulir &data, int &nomorkartu,int &jumlahpendaftar ){
  //memanggil semua fungsi yang di butuhkan
  int a = 0; 
  garis();
  cout << "Masukkan Jumlah Pendaftar : "; cin >> jumlahpendaftar; cin.ignore();
  int pendaftar = jumlahpendaftar/jumlahpendaftar;
  while(a <= jumlahpendaftar){
    pendaftaran_member(member,data,nomorkartu);
    harga_member(pendaftar,durasi_bulan);
    a++; 
    jumlahpendaftar--;
    cin.ignore();
  }
  
}

//vector untuk menyimpan data pengunjung
vector <formulir> data_pengunjung;
int jumlah_data;

//daftar harga
int harga_kunjungan = 30000;
int total_pengunjung; // menyimpan data berapa orang yang berkunjung ke gym

//prosedur untuk mengisi data jika ada pengunjung/single visit 
void pengunjung(vector <formulir>& data_pengunjung, vector<formulir>& member,formulir &data,bool &status_pembayaran_pengunjung, int &total_pengunjung){

  //kamus lokal 
  formulir data_kunjung;
  string daftar;
  string main;
  int pengunjung; 
  string membayar; 
  //deskripsi 
  //penawaran masuk member atau tidak 
  cout << "HAI ANDA BELUM MEMBER \n";
  cout << "apakah anda ingin menjadi anggota member ? \n";
  cout << "-DAFTAR \n" "-Tidak \n";
  cout << "jawaban : " ;
  cin >> daftar;
  cin.ignore();
  if(daftar == "daftar"){

    //memanggil prosedur pendaftaran member
    utama(member,data,nomorkartu,jumlahpendaftar);
   
  }else if(daftar == "tidak"){

      //mengisi data formulir pendaftaran member berdasarkan berapa orang yang berkunjung
      single();
      cout << "Form pengunjung \n";
      cout << "masukkan total pengunjung : "; cin >> total_pengunjung;cin.ignore();
      
        for(int x = 1;x <= total_pengunjung; x++){
          cout << endl;
          cout << "MOHON ISI DATA YANG DIMINTA !!\n";
          garis();
          cout << "masukkan nama pengunjung ke " << x << " : " ;
          getline(cin, data_kunjung.nama);
          cout << "masukkan alamat " << setw(16) << ": "; 
          getline(cin, data_kunjung.alamat);
          cout << "masukkan no-telpon anda " << setw(8) << ": ";
          getline(cin, data_kunjung.no_tlp);
          data_pengunjung.push_back(data_kunjung);
          garis();

        }

      cout << "harga kunjungan per-orang : " << harga_kunjungan << endl;
      int total_tagihan = (harga_kunjungan * total_pengunjung);
      cout << "total tagihan anda " << setw(9) << ": " << total_tagihan << endl; 
      cout << "bayar sekarang/ \n" "nanti saat check out " << setw(7) << ": ";
      cin >> membayar;
      if(membayar == "sekarang"){
        pembayaran(total_tagihan);
          for(formulir &pengunjung : data_pengunjung){
            pengunjung.status_pembayaran = true;
            pengunjung.status_bayar = "sudah bayar";
          }
        status_pembayaran_pengunjung = true; 
      }else if(membayar == "nanti"){
        for(formulir &pengunjung : data_pengunjung){
          pengunjung.status_pembayaran = false;
          pengunjung.status_bayar = "belum bayar";
        }
        status_pembayaran_pengunjung = false; 
      }
    }
  else{
   
    cout << "pilihane ra ono cok!!\n";
    cout << "MATANE PICEK TA, ISO NDELOK PO ORA!!!\n";
  }
  

}


//untuk mencari data pengunjung
void cari_pengunjung( const vector<formulir>& data_pengunjung, const string &nama_pengunjung, bool &status_pembayaran_pengunjung,const int &total_pengunjung){

  //kamus lokal 
  bool terdata = false; 
  //deskripsi 

  //melakukan perulangan dengan menyertakan kondisi di dalam perulangan tersebut 
  for(const auto&formulir : data_pengunjung){
    //kondisi untuk menampilkan dan mencari nama yang sesuai dengan yang di inputkan 
    if(formulir.nama.find(nama_pengunjung) !=string::npos){

      cout << "Data di temukan!!" << endl; 
      cout << "nama " << setw(17) << ":" << formulir.nama << endl;
      cout << "alamat " << setw(15) << ":" << formulir.alamat << endl; 
      cout << "no-telpon " << setw(12) << ":" << formulir.no_tlp << endl;
      cout << "status pembayaran " << setw(5) << ":" << formulir.status_bayar << endl;
      terdata = true; 
      if(status_pembayaran_pengunjung== true){
        break;
      }else if(status_pembayaran_pengunjung == false){
        cout << endl; 
        cout << "anda belum bayar tagihan " << endl; 
        int tagihan = (harga_kunjungan*total_pengunjung);
        cout << "total tagihan anda " << setw(6) << ": " << tagihan << endl; 
        pembayaran(tagihan);
        status_pembayaran_pengunjung = true;
        
      }
    }else if(!terdata){
      //logika jika nama yang di cari tidak terdata atau tidak ada di dalam vector
      cout << "Data tidak di temukan atas nama : " << nama_pengunjung << endl; 
      cout << "Anda tidak terdaftar !! :_( \n"; 

    }else {
      cout << "yahh mau kabur yahh \n";
    }

  }

};

//deksripsi
int main(){

  formulir data;  
  while (true){

    string pilihan;
    //variabel yang diunakan untuk parameter pencarian member dan pengunjung 
    string nama_pengunjung;
    string memilih; 
    //memanggil prosedur pembukaan 
    garis();
    cout << "SELAMAT DATANG DI MAK GYM :) \n";
    garis();
    cout << "Silahkan Pilih Program Yang Kamu Ingin :) \n";
    single();
    cout << "-MEMBER \n";
    cout << "-PENGUNJUNG \n";
    single();
    cout << "-KELUAR <-- \n";
    cout << "Masukan Pilihan Anda : ";
    cin >> pilihan;cin.ignore();
    cout << endl;
    //kondisi jika memilih program member 
    if(pilihan == "member"){
     
        //kamus lokal 
        string input,mencari;
      //melakukan perulangan pilihan member ini 
        clearscreen();
        while(true){
      
          //deskripsi 
          single();
          cout << "Selamat Datang Di MAK GYM!! :)" << endl; 
          single();
          cout << "Menu : \n";
          single();
          cout << "-Daftar Member \n" "-Cek Anggota Member\n" "-Lihat Data Keanggotaan\n" "-Kembali Menu Awal \n"; 
          cout << "Masukkan pilihan : "; cin >> input; cin.ignore();
          garis();

            //kondisi untuk ketiga pilihan tersebut 
            if(input == "cek"){
                
                clearscreen();
                carimember(member,mencarinama,data);
                string kembaliInput;        
                cout << "kembali : "; 
                cin >> kembaliInput;                  
                if(kembaliInput == "iya"){
                  clearscreen();                    
                }
                
              }else if(input == "daftar"){
                
                  clearscreen();
                  utama(member,data,nomorkartu,jumlahpendaftar);
                  single();      
                  string kembaliInput;        
                  cout << "kembali : "; 
                  cin >> kembaliInput;                  
                  if(kembaliInput == "iya"){
                    clearscreen();                    
                  }
              
                }else if(input == "lihat" ){
                
                    clearscreen();
                    cout << "Daftar Keanggotaan Member MAK GYM !! \n";
                    single();
                      for(const auto &data : member){
                        tampildata(data);
                      }
                    
                    string kembaliInput;        
                    cout << "kembali : "; 
                    cin >> kembaliInput;                  
                    if(kembaliInput == "iya"){
                      clearscreen();                    
                    }
                   
                  }else if(input == "kembali"){
                      
                    clearscreen();
                    break;
                  }
            else{
              cout << "Pilihan Tidak Tersedia" << endl; 
              cout << "WOI COK MATANE DELOK EN RA ONO COK !!!" << endl; 
              string kembaliInput;        
                    cout << "kembali : "; 
                    cin >> kembaliInput;                  
                    if(kembaliInput == "iya"){
                      clearscreen();                    
                    }
            }          
        }        
      }else if(pilihan == "pengunjung"){

            clearscreen();
            while(true){
              single();
              cout << "Data pengunjung MAK GYM" << endl; 
              cout << "MENU \n" "-Masuk\n" "-Keluar\n" "kembali\n";
              cout << "pilih : "; cin >> memilih; 
              cin.ignore();
              //kondisi untuk menjalankan menu di atas tersebut 
            
                if(memilih == "masuk"){
                  clearscreen();
                  //memanggil prosedur pengunjung 
                  garis();
                  pengunjung(data_pengunjung,member,data,status_pembayaran_pengunjung,total_pengunjung);                                

                  string back;
                  cout << "kembali : ";
                  cin >> back; 
                  cin.ignore();
                    if(back == "iya"){
                      clearscreen();
                      
                    }
                                  
                }else if(memilih == "keluar"){
                    clearscreen();
                    cout << "Cek data pengunjung" << endl; 
                    garis();
                    cout << "Masukkan nama pengunjung : " ;
                    getline(cin, nama_pengunjung);
                    cout << "tunggu sebentar!!" << endl;
                    cari_pengunjung(data_pengunjung, nama_pengunjung,status_pembayaran_pengunjung,total_pengunjung);
                    string back;

                    cout << "kembali : ";
                    cin >> back; 
                      if(back == "iya"){
                        clearscreen();                      
                      }
                  }else if(memilih == "kembali"){
                      clearscreen();
                      break;
                    }
                else{
                  cout << "PILIHAN YANG ANDA MASUKKAN TIDAK ADA!!\n";
                  cout << "goblok ta COK, wes ngerti ra ono malah di pilih tolol \n"; 
                  string back;
                  cout << "kembali : ";
                  cin >> back; 
                  cin.ignore();
                    if(back == "iya"){
                      clearscreen();
                      
                    }
                }
            }

        }else if(pilihan == "keluar"){
          break;
          }
      else{

        cout << "PILIHAN YANG ANDA MASUKKAN TIDAK ADA!!\n";
        string back;
        cout << "keluar : ";
        cin >> back; 
        cin.ignore();
          if(back == "ya"){
            clearscreen();
            break;
          }
      }    
  }
}