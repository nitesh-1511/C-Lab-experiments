#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <memory>
using namespace std;
struct FileRecord {
    char name[50];
    int size;
};
template<class T>
class CustomAllocator {
public:
    using value_type = T;
    CustomAllocator() = default;
    template<class U>
    CustomAllocator(const CustomAllocator<U>&) {}
    T* allocate(size_t n) {
        cout << "[Memory] Allocating " << n << " object(s)\n";
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }
    void deallocate(T* p, size_t) {
        cout << "[Memory] Released\n";
        ::operator delete(p);
    }
};
using FileList = vector<FileRecord, CustomAllocator<FileRecord>>;
void loadFiles(FileList& files) {
    ifstream in("filesystem.dat", ios::binary);
    FileRecord f;
    while(in.read(reinterpret_cast<char*>(&f), sizeof(f)))
        files.push_back(f);
}
void saveFiles(const FileList& files) {
    ofstream out("filesystem.dat", ios::binary | ios::trunc);
    for(const auto& f : files)
        out.write(reinterpret_cast<const char*>(&f), sizeof(f));
}
void addFile(FileList& files) {
    FileRecord f{};
    cout << "File name: ";
    cin >> ws;
    cin.getline(f.name, 50);
    cout << "File size (KB): ";
    cin >> f.size;
    if(cin.fail() || f.size <= 0) {
        cout << "Invalid file size!\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }
    files.push_back(f);
    saveFiles(files);
    cout << "File Added Successfully!\n";
}
void displayFiles(const FileList& files) {
    cout << "\n--- FILE RECORDS ---\n";
    if(files.empty()) {
        cout << "No files found.\n";
        return;
    }
    for(const auto& f : files)
        cout << f.name << " | " << f.size << " KB\n";
}
void searchFile(const FileList& files) {
    char name[50];
    cout << "Enter file name: ";
    cin >> ws;
    cin.getline(name, 50);
    for(const auto& f : files) {
        if(strcmp(f.name, name) == 0) {
            cout << "Found: " << f.name
                 << " (" << f.size << " KB)\n";
            return;
        }
    }
    cout << "File Not Found!\n";
}
void deleteFile(FileList& files) {
    char name[50];
    cout << "Enter file name to delete: ";
    cin >> ws;
    cin.getline(name, 50);
    auto it = find_if(files.begin(), files.end(),
        [&](const FileRecord& f) {
            return strcmp(f.name, name) == 0;
        });
    if(it == files.end()) {
        cout << "File Not Found!\n";
        return;
    }
    files.erase(it);
    saveFiles(files);
    cout << "File Deleted Successfully!\n";
}
void statistics(const FileList& files) {
    if(files.empty()) {
        cout << "No storage data available.\n";
        return;
    }
    int total = 0;
    const FileRecord* largest = &files[0];
    for(const auto& f : files) {
        total += f.size;
        if(f.size > largest->size)
            largest = &f;
    }
    cout << "\n--- STORAGE ANALYTICS ---\n";
    cout << "Total Files : " << files.size() << endl;
    cout << "Used Space  : " << total << " KB\n";
    cout << "Largest File: " << largest->name << endl;
}
void sortFiles(FileList& files) {
    sort(files.begin(), files.end(),
        [](const FileRecord& a, const FileRecord& b) {
            return a.size > b.size;
        });
    saveFiles(files);
    cout << "Files Sorted by Size!\n";
}
int main() {
    FileList files;
    loadFiles(files);
    int choice;
    do {
        cout << "\n===== SMART FILE SYSTEM =====\n";
        cout << "1. Add File\n";
        cout << "2. Display Files\n";
        cout << "3. Search File\n";
        cout << "4. Delete File\n";
        cout << "5. Storage Analytics\n";
        cout << "6. Sort Files\n";
        cout << "7. Exit\n";
        cout << "Choice: ";
        if(!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input!\n";
            continue;
        }
        switch(choice) {
            case 1: addFile(files); break;
            case 2: displayFiles(files); break;
            case 3: searchFile(files); break;
            case 4: deleteFile(files); break;
            case 5: statistics(files); break;
            case 6: sortFiles(files); break;
            case 7: cout << "System Closed!\n"; break;
            default: cout << "Invalid Choice!\n";
        }
    } while(choice != 7);

    return 0;
}
