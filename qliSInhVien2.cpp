#include <bits/stdc++.h>
using namespace std;

class Student {
    private:
        string id;
        string name;
        int age;
        float score;

    public:
        Student(string id = "", string name = "", int age = 0, float score = 0.0) {
            this->id = id;
            this->name = name;
            this->age = age;
            this->score = score;
        }

        // Getters
        string getId()  { return id; }
        string getName()  { return name; }
        int getAge()  { return age; }
        float getScore()  { return score; }

        // Setters
        void setId( string &id) { this->id = id; }
        void setName( string &name) { this->name = name; }
        void setAge(int age) { this->age = age; }
        void setScore(float score) { this->score = score; }

        friend istream& operator>>(istream &in, Student &s) {
            string id, name;
            int age;
            float score;
            cout << "Nhap ID: "; in >> id;
            cout << "Nhap ten: "; in.ignore(); getline(in, name);
            cout << "Nhap tuoi: "; in >> age;
            cout << "Nhap diem: "; in >> score;
            s.setId(id);
            s.setName(name);
            s.setAge(age);
            s.setScore(score);
            return in;
        }

        friend ostream& operator<<(ostream &out,  Student &s) {
            out << "ID: " << s.getId() << ", Ten: " << s.getName() 
                << ", Tuoi: " << s.getAge() << ", Diem: " << s.getScore();
            return out;
        }

        bool operator<( Student &other)  {
            if (id != other.id) {
                return id < other.id;
            } else if (score != other.score) {
                return score < other.score;
            } else {
                return age < other.age;
            }
        }
};

class StudentList {
    private:
        list<Student> students;

    public:
        void addStudent( Student &s) {
            students.push_back(s);
        }

        void removeStudent( string &id) {
            students.remove_if([&id]( Student &s) { return s.getId() == id; });
            cout << "Da xoa thanh cong sinh vien co id "<< id;
        }

        Student findMaxScore() {
            return *max_element(students.begin(), students.end(), []( Student &a,  Student &b) {
                                    return a.getScore() < b.getScore();
                                    }
                                );
        }

        Student findMinScore() {
            return *min_element(students.begin(), students.end(), []( Student &a,  Student &b) {
                                    return a.getScore() < b.getScore();
                                });
        }

        Student* findStudentById( string &id) {
            for (list<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                if (it->getId() == id)return &(*it);
            }
            return nullptr;
        }

        void sortStudents() {
            students.sort();
        }

        void displayAll()  {
            sortStudents();
            for (list<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                cout << *it << endl;
            }
        }

        void readFromFile( string &filename) {
            ifstream file(filename);
            if (!file) {
                cout << "Khong the mo file: " << filename << endl;
                return;
            }

            string id, name;
            int age;
            float score;
            while (file >> id) {
                file.ignore();
                getline(file, name);
                file >> age >> score;
                Student s(id, name, age, score);
                addStudent(s);
            }

            file.close();
            cout << "Da doc du lieu tu file " << filename << " thanh cong.\n";
        }
};

class App {
private:
    StudentList studentList;

public:
    void menu() {
        int choice;
        do {
            cout << "\n===== MENU =====\n";
            cout << "1. Them sinh vien\n";
            cout << "2. Xoa sinh vien theo ID\n";
            cout << "3. Tim sinh vien co diem cao nhat\n";
            cout << "4. Tim sinh vien co diem thap nhat\n";
            cout << "5. Tim sinh vien theo ID\n";
            cout << "6. Hien thi danh sach sinh vien\n";
            cout << "7. Lay danh sach sinh vien co san\n";
            cout << "0. Thoat\n";
            cout << "Lua chon: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    Student s;
                    cin >> s;
                    studentList.addStudent(s);
                    break;
                }
                case 2: {
                    string id;
                    cout << "\nNhap ID sinh vien can xoa: ";
                    cin >> id;
                    studentList.removeStudent(id);
                    break;
                }
                case 3: {
                    Student maxStudent = studentList.findMaxScore();
                    cout << "\nSinh vien co diem cao nhat:\n" << maxStudent << endl;
                    break;
                }
                case 4: {
                    Student minStudent = studentList.findMinScore();
                    cout << "\nSinh vien co diem thap nhat:\n" << minStudent << endl;
                    break;
                }
                case 5: {
                    string id;
                    cout << "\nNhap ID sinh vien can tim: ";
                    cin >> id;
                    Student* s = studentList.findStudentById(id);
                    if (s) cout << "Thong tin sinh vien:\n" << *s << endl;
                    else cout << "Khong tim thay sinh vien co ID " << id << endl;
                    break;
                }
                case 6: {
                    cout << "\nDanh sach sinh vien:\n";
                    studentList.displayAll();
                    break;
                }
                case 7: {
                    string filename;
                    cout << "\nNhap ten file: ";
                    cin >> filename;
                    studentList.readFromFile(filename);
                    break;
                }
                case 0:
                    cout << "Thoat chuong trinh.\n";
                    break;
                default:
                    cout << "Lua chon khong hop le!\n";
                    break;
            }
        } while (choice != 0);
    }
};

int main() {
    App app;
    app.menu();
    return 0;
}