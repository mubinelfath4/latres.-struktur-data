#include <iostream>
using namespace std;

struct nodeQueue{
  int codeEnergi;
  string namaEnergi;
  nodeQueue* next;  
};
struct nodeStack{
    int codeEnergi;
    string namaEnergi;
    nodeStack* next;
};

struct nodeTree{
    int codeEnergi;
    string namaEnergi;
    nodeTree* kiri;
    nodeTree* kanan;
};

nodeQueue* front = nullptr;
nodeQueue* last = nullptr;
nodeStack* top = nullptr;
nodeTree* root = nullptr;

nodeTree* tambahtree(nodeTree* akar, int codeEnergi, string namaEnergi){
    if (akar ==  nullptr){
        return new nodeTree{codeEnergi, namaEnergi, nullptr, nullptr};
    }
    if(codeEnergi< akar->codeEnergi){
akar->kiri = tambahtree(akar->kiri, codeEnergi, namaEnergi);
    }else{
        akar->kanan= tambahtree(akar->kanan, codeEnergi, namaEnergi);
    }
    return akar;
}
nodeTree* caritree(nodeTree* akar, int codeEnergi){
    if(akar == nullptr || akar->codeEnergi == codeEnergi ){
        return akar;
    }
    if(codeEnergi < akar->codeEnergi){
        return caritree(akar->kiri, codeEnergi);
    }
    return caritree(akar->kanan, codeEnergi);
}
nodeTree* hapustree(nodeTree* akar, int codeEnergi){
    if(akar == nullptr){
        return nullptr;
    }
    if(codeEnergi < akar->codeEnergi){
        akar->kiri = hapustree(akar->kiri, codeEnergi);
    }else if(codeEnergi > akar->codeEnergi){
        akar->kanan=hapustree(akar->kanan, codeEnergi);
    }else if(akar->kiri == nullptr){
        nodeTree* sisa = akar->kanan;
        delete akar;
        return sisa;
    }else if(akar->kanan == nullptr){
        nodeTree* sisa = akar->kiri;
        delete akar;
        return sisa;
    }else{
        nodeTree* pengganti = akar->kanan;
        while(pengganti->kiri != nullptr){
            pengganti = pengganti->kiri;
        }
        akar->codeEnergi = pengganti->codeEnergi;
        akar->namaEnergi = pengganti->namaEnergi;
        akar->kanan = hapustree(akar->kanan, pengganti->codeEnergi);
    }
    return akar;
}

void preorder(nodeTree* akar, int& no){
    if(akar == nullptr){
        return;
    }
    cout << no <<". {" << akar->codeEnergi << "} " << akar->namaEnergi << endl;
    no++;
    preorder(akar->kiri, no);
    preorder(akar->kanan, no);
}

void inorder(nodeTree* akar, int&no){
    if (akar == nullptr){
        return;
    }inorder(akar->kiri, no);
    cout << no << ". {" << akar->codeEnergi << "} " << akar->namaEnergi << endl;
    no++;
    inorder(akar->kanan, no);
}
void postorder(nodeTree* akar, int& no){
    if(akar == nullptr){
        return;
    }
    postorder(akar->kiri , no);
    postorder(akar->kanan, no);
    cout << no << ". {" <<akar->codeEnergi<< "} " << akar->namaEnergi << endl;
    no++;
}
void tambahEnergi(){
    int codeEnergi;
    string namaEnergi;
    cout <<"masukkan kode energi: ";
    cin>> codeEnergi;
    if(cin.fail() || codeEnergi < 0){
        cin.clear();
        cin.ignore(1000, '\n');
            cout << "code energi harus lebih dari 0!" << endl << endl;
            return;
    } 
    nodeQueue* q = front;
    while(q != nullptr) {
        if(q->codeEnergi == codeEnergi){
            cout << "code energi sudah digunakan!" << endl << endl;
            return;
        }
        q = q->next;
    }
    nodeStack* s = top;
    while(s != nullptr){
        if (s->codeEnergi == codeEnergi){
            cout << "code energi sudah digunakan!" << endl << endl;
            return;
        }
        s =s->next;
    }
    cout << "masukkan nama energi: ";
    cin.ignore();
    getline(cin, namaEnergi);
    if(namaEnergi.empty()){
        cout << "nama tidak boleh kosong!" << endl << endl;
        return;
    }
    nodeQueue* nb = new nodeQueue{codeEnergi, namaEnergi, nullptr};
    if(front == nullptr){
        front = last = nb;
    }else{
        last->next = nb;
        last = nb;
    }
    cout << "berhasil memasukkan energi" <<endl << endl;
}
void lihatAntrian(){
    if(front == nullptr){
        cout << "antrean masih kosong!" << endl<< endl;
        return;
    }
    cout << "=== ENERGI DALAM ANTREAN ==="<< endl << endl;
    nodeQueue* nb = front;
    int no = 1;
    while(nb !=nullptr){
        cout<< no << ". {" << nb->codeEnergi << "} " << nb->namaEnergi << endl << endl;
        nb = nb->next;
        no++;
    }
    cout << endl;
}
void prosesEnergi(){
    if(front == nullptr){
        cout << "antrian masih kosong!" << endl << endl;
        return;
    }
    nodeQueue* hapus = front;
    nodeStack* nb = new nodeStack{hapus->codeEnergi, hapus->namaEnergi, top};
    top = nb;
    root = tambahtree(root, hapus->codeEnergi, hapus->namaEnergi);
    cout << "berhasil memproses energi " << hapus->namaEnergi<<"!" << endl << endl;
    front = hapus->next;
    if(front == nullptr){
        last = nullptr;
    }
    delete hapus;
}
void lihatRiwayat(){
    if(top == nullptr){
    cout << "belum ada energi yang terserap!" << endl << endl;
    return;
    }
    cout << "=== ENERGI YANG SUDAH TERSERAP ===" << endl << endl;
    nodeStack* nb = top;
    int no = 1;
    while(nb != nullptr){
        cout << no <<". {" << nb->codeEnergi << "} " << nb->namaEnergi << endl << endl;
        nb = nb->next;
        no++;
    }
    cout << endl;
}
void hapusRiwayat(){
     nodeQueue* hapus = front;
    nodeStack* nb = new nodeStack{hapus->codeEnergi, hapus->namaEnergi, top};
    top = nb;
    root = tambahtree(root, hapus->codeEnergi, hapus->namaEnergi);
    cout << "berhasil memproses energi " << hapus->namaEnergi<<"!" << endl << endl;
    front = hapus->next;
    if(front == nullptr){
        last = nullptr;
    }
    delete hapus;
}
int main(){
    char pil = '0';
    while(pil !=9){
        cout << "=== sistem organ inti nirwana ===" << endl << endl;
        cout << "1. Tambah energi" << endl;
        cout << "2. lihat energi dalam antrean" << endl;
        cout << "3. proses energi" << endl;
        cout << "4. lihat enrgi yang sudah terserap" << endl;
        cout << "5. hapus riwayat energi teratas" << endl;
        cout << "6. cari energi didalam organ" << endl;
        cout << "7. lihat isi organ" << endl;
        cout << "8. gunakan energi" << endl;
        cout << "9. keluar" << endl;
    }
    cin >> pil;
    switch(pil){
        case '1' :{
            char pil_tambah = 'y';
            while(pil_tambah== 'y' || pil_tambah== 'Y'){
                tambahEnergi();
                cout << "apakah anda ingin menambahkan cucian lagi?" << endll;
                cin >> pil; 
            }
        }
    }
}