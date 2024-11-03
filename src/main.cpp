#include "../include/includes.h"
#include "../include/array.h"
#include "../include/list.h"
#include "../include/stack.h"
#include "../include/queue.h"
#include "../include/hashtable.h"
#include "../include/tree.h"

// Вспомогательные ф-ии
string Fulltext (string& filename, string& nameStruct) { // ф-ия сохранения фулл текста файла без нужной структуры
    string str, textfull;
    ifstream fileinput;
    fileinput.open(filename);
    while(getline(fileinput, str)) { // сохранение фулл текста в переменную
        stringstream ss(str);
        string token;
        getline(ss, token, ' ');
        if (token != nameStruct) {
            textfull += str + "\n";
        }
    }
    fileinput.close();
    return textfull;
}
void writefile (string& filename, string& textfull) { // ф-ия записи данных в файл
    ofstream fileoutput;
    fileoutput.open(filename);
    fileoutput << textfull;
    fileoutput.close();
}

// Массив
Array<string> Mreadfile (string& filename, string& name) { // ф-ия чтения массива из файла
    Array<string> nums;
    string str;
    ifstream fileinput;
    fileinput.open(filename);
    while (getline(fileinput, str)) { // добавления значения в массив
        stringstream ss(str);
        string token;
        getline(ss, token, ' ');
        if (token == name) {
            while (getline(ss, token, ' ')) {
                nums.add(token);
            }
        }
    }
    fileinput.close();
    return nums;
}
void MADD(string& name, string& value, string& filename) {
    string textfull = Fulltext(filename, name);
    Array<string> nums = Mreadfile(filename, name);

    string str;
    if (nums.length() != 0) {
        nums.add(value);
        str = name + ' ';
        for (int i = 0; i < nums.length(); ++i) {
            str += nums.get(i) + ' ';
        }
        textfull += str;
        writefile(filename, textfull);
    } else { // создание массива, если его нет
        str = name + ' ' + value;
        textfull += str;
        writefile(filename, textfull);
    }
}
void MADDAT(string& name, string& value, int& index, string& filename) {
    string textfull = Fulltext(filename, name);
    Array<string> nums = Mreadfile(filename, name);

    string str;
    if (nums.length() != 0 && index < nums.length()) {
        nums.addAt(index, value);
        str = name + ' ';
        for (int i = 0; i < nums.length(); ++i) {
            str += nums.get(i) + ' ';
        }
        textfull += str;
        writefile(filename, textfull);
    } else if (nums.length() == 0 && index == 0){ // создание массива, если его нет
        str = name + ' ' + value;
        textfull += str;
        writefile(filename, textfull);
    } else {
        cout << "Ошибка, индекс выходит за размеры массива!" << endl;
        exit(1);
    }
}
void MREMOVE (string& name, int& index, string& filename) {
    string textfull = Fulltext(filename, name);
    Array<string> nums = Mreadfile(filename, name);

    string str;
    if (nums.length() != 0 && index < nums.length()) {
        nums.remove(index);
        str = name + ' ';
        for (int i = 0; i < nums.length(); ++i) {
            str += nums.get(i) + ' ';
        }
        textfull += str;
        writefile(filename, textfull);
    } else {
        cout << "Ошибка, нет такого массива или он пуст!" << endl;
        exit(1);
    }
}
void MREPLACE (string& name, string& value, int& index, string& filename) {
    string textfull = Fulltext(filename, name); // весь файл
    Array<string> nums = Mreadfile(filename, name);

    string str;
    if (nums.length() != 0 && index < nums.length()) {
        nums.replace(index, value);
        str = name + ' ';
        for (int i = 0; i < nums.length(); ++i) {
            str += nums.get(i) + ' ';
        }
        textfull += str;
        writefile(filename, textfull);
    } else {
        cout << "Ошибка, нет такого массива или индекс выходит за его размеры!" << endl;
        exit(1);
    }
}
void MGET (string& name, int& index, string& filename) {
    Array<string> nums = Mreadfile(filename, name);

    string str;
    if (nums.length() != 0 && index < nums.length()) {
        cout << nums.get(index) << endl;
    } else {
        cout << "Нет такого массива или индекс выходит за его размеры!" << endl;
        exit(1);
    }
}
void MSIZE(string& name, string& filename) {
    Array<string> nums = Mreadfile(filename, name);

    if (nums.length() != 0) {
        cout << nums.length() << endl;
    } else {
        cout << "Ошибка, нет такого массива или он пуст!" << endl;
        exit(1);
    }
}
void MPRINT(string& name, string& filename) {
    Array<string> nums = Mreadfile(filename, name);

    string str;
    if (nums.length() != 0) {
        nums.print();
    } else {
        cout << "Ошибка, нет такого массива или он пуст!" << endl;
        exit(1);
    }
}
void Mprocessing(string& command, string& filename) { // ф-ия обработки команд массива
    string name, value;
    int index;
    if (command.substr(0, 5) == "MADD ") {
        stringstream stream(command.substr(5));;
        stream >> name >> value;
        MADD(name, value, filename);
    } else if (command.substr(0, 7) == "MADDAT ") {
        stringstream stream(command.substr(7));
        stream >> name >> value >> index;
        MADDAT(name, value, index, filename);
    } else if (command.substr(0, 8) == "MREMOVE ") {
        stringstream stream(command.substr(8));
        stream >> name >> index;
        MREMOVE(name, index, filename);
    } else if (command.substr(0, 9) == "MREPLACE ") {
        stringstream stream(command.substr(9));
        stream >> name >> value >> index;
        MREPLACE(name, value, index, filename);
    } else if (command.substr(0, 5) == "MGET ") {
        stringstream stream(command.substr(5));
        stream >> name >> index;
        MGET(name, index, filename);
    } else if (command.substr(0, 6) == "MSIZE ") {
        stringstream stream(command.substr(6));
        stream >> name;
        MSIZE(name, filename);
    } else if (command.substr(0, 7) == "MPRINT ") {
        stringstream stream(command.substr(7));
        stream >> name;
        MPRINT(name, filename);
    } else {
        cout << "Ошибка, нет такой команды!" << endl;
        exit(1);
    }
}

// Сингл лист
SinglyLinkedList<string> LSreadfile(string& filename, string& name) { // ф-ия чтения списка из файла
    SinglyLinkedList<string> nums;
    string str;
    ifstream fileinput;
    fileinput.open(filename);
    while (getline(fileinput, str)) { // добавления значения в массив
        stringstream ss(str);
        string token;
        getline(ss, token, ' ');
        if (token == name) {
            while (getline(ss, token, ' ')) {
                nums.push_back(token);
            }
        }
    }
    fileinput.close();
    return nums;
}
void LSPUSH(string& name, string& value, string& filename, string check) {
    string textfull = Fulltext(filename, name);
    SinglyLinkedList<string> nums = LSreadfile(filename, name);

    string str;
    if (nums.size != 0) {
        if (check == "back") nums.push_back(value);
        else nums.push_front(value);
        str = name + ' ';
        for (int i = 0; i < nums.size; ++i) {
            str += nums.getvalue(i) + ' ';
        }
        textfull += str;
        writefile(filename, textfull);
    } else { // создание списка, если его нет
        str = name + ' ' + value;
        textfull += str;
        writefile(filename, textfull);
    }
}
void LSPOP(string& name, string& filename, string check) {
    string textfull = Fulltext(filename, name);
    SinglyLinkedList<string> nums = LSreadfile(filename, name);

    string str;
    if (nums.size != 0) {
        if (check == "back") nums.pop_back();
        else nums.pop_front();
        str = name + ' ';
        for (int i = 0; i < nums.size; ++i) {
            str += nums.getvalue(i) + ' ';
        }
        textfull += str;
        writefile(filename, textfull);
    } else {
        cout << "Ошибка, нет такого списка или он пуст!" << endl;
        exit(1);
    }
}
void LSREMOVE(string& name, string& value, string& filename) {
    string textfull = Fulltext(filename, name);
    SinglyLinkedList<string> nums = LSreadfile(filename, name);

    string str;
    if (nums.size != 0) {
        if (nums.remove(value)) {
            str = name + ' ';
            for (int i = 0; i < nums.size; ++i) {
                str += nums.getvalue(i) + ' ';
            }
            textfull += str;
            writefile(filename, textfull);
        } else {
            cout << "Ошибка, такой элемент в списке не найден!" << endl;
            exit(1);
        }
    } else {
        cout << "Ошибка, нет такого списка или он пуст!" << endl;
        exit(1);
    }
}
void LSGET(string& name, string& value, string& filename) {
    SinglyLinkedList<string> nums = LSreadfile(filename, name);

    string str;
    if (nums.size != 0) {
        if (nums.getindex(value) == -1) {
            cout << "Нет такого значения в списке!" << endl;
            exit(1);
        }
        cout << nums.getindex(value) << endl;
    } else {
        cout << "Ошибка, нет такого списка!" << endl;
        exit(1);
    }
}
void LSPRINT(string& name, string& filename) {
    SinglyLinkedList<string> nums = LSreadfile(filename, name);

    string str;
    if (nums.size != 0) {
        nums.print();
    } else {
        cout << "Ошибка, нет такого списка или он пуст!" << endl;
        exit(1);
    }
}
void LSprocessing(string& command, string& filename) { // ф-ия обработки команд списка
    string name, value;

    if (command.substr(0, 8) == "LSPUSHB ") {
        stringstream stream(command.substr(8));;
        stream >> name >> value;
        LSPUSH(name, value, filename, "back"); 
    } else if (command.substr(0, 8) == "LSPUSHF ") {
        stringstream stream(command.substr(8));;
        stream >> name >> value;
        LSPUSH(name, value, filename, "front");
    } else if (command.substr(0, 7) == "LSPOPB ") {
        stringstream stream(command.substr(7));;
        stream >> name;
        LSPOP(name, filename, "back");
    } else if (command.substr(0, 7) == "LSPOPF ") {
        stringstream stream(command.substr(7));;
        stream >> name;
        LSPOP(name, filename, "front");
    } else if (command.substr(0, 9) == "LSREMOVE ") {
        stringstream stream(command.substr(9));;
        stream >> name >> value;
        LSREMOVE(name, value, filename);
    } else if (command.substr(0, 6) == "LSGET ") {
        stringstream stream(command.substr(6));;
        stream >> name >> value;
        LSGET(name, value, filename);
    } else if (command.substr(0, 8) == "LSPRINT ") {
        stringstream stream(command.substr(8));;
        stream >> name;
        LSPRINT(name, filename);
    } else {
        cout << "Ошибка, нет такой команды!" << endl;
        exit(1); 
    }
}

// Дабл лист
DoublyLinkedList<string> LDreadfile(string& filename, string& name) { // ф-ия чтения списка из файла
    DoublyLinkedList<string> nums;
    string str;
    ifstream fileinput;
    fileinput.open(filename);
    while (getline(fileinput, str)) { // добавления значения в массив
        stringstream ss(str);
        string token;
        getline(ss, token, ' ');
        if (token == name) {
            while (getline(ss, token, ' ')) {
                nums.push_back(token);
            }
        }
    }
    fileinput.close();
    return nums;
}
void LDPUSH(string& name, string& value, string& filename, string check) {
    string textfull = Fulltext(filename, name);
    DoublyLinkedList<string> nums = LDreadfile(filename, name);

    string str;
    if (nums.size != 0) {
        if (check == "back") nums.push_back(value);
        else nums.push_front(value);
        str = name + ' ';
        for (int i = 0; i < nums.size; ++i) {
            str += nums.getvalue(i) + ' ';
        }
        textfull += str;
        writefile(filename, textfull);
    } else { // создание списка, если его нет
        str = name + ' ' + value;
        textfull += str;
        writefile(filename, textfull);
    }
}
void LDPOP(string& name, string& filename, string check) {
    string textfull = Fulltext(filename, name);
    DoublyLinkedList<string> nums = LDreadfile(filename, name);

    string str;
    if (nums.size != 0) {
        if (check == "back") nums.pop_back();
        else nums.pop_front();
        str = name + ' ';
        for (int i = 0; i < nums.size; ++i) {
            str += nums.getvalue(i) + ' ';
        }
        textfull += str;
        writefile(filename, textfull);
    } else {
        cout << "Ошибка, нет такого списка или он пуст!" << endl;
        exit(1);
    }
}
void LDREMOVE(string& name, string& value, string& filename) {
    string textfull = Fulltext(filename, name);
    DoublyLinkedList<string> nums = LDreadfile(filename, name);

    string str;
    if (nums.size != 0) {
        if (nums.remove(value)) {
            str = name + ' ';
            for (int i = 0; i < nums.size; ++i) {
                str += nums.getvalue(i) + ' ';
            }
            textfull += str;
            writefile(filename, textfull);
        } else {
            cout << "Ошибка, такой элемент в списке не найден!" << endl;
            exit(1);
        }
    } else {
        cout << "Ошибка, нет такого списка или он пуст!" << endl;
        exit(1);
    }
}
void LDGET(string& name, string& value, string& filename) {
    DoublyLinkedList<string> nums = LDreadfile(filename, name);

    string str;
    if (nums.size != 0) {
        if (nums.getindex(value) == -1) {
            cout << "Нет такого значения в списке!" << endl;
            exit(1);
        }
        cout << nums.getindex(value) << endl;
    } else {
        cout << "Ошибка, нет такого списка!" << endl;
        exit(1);
    }
}
void LDPRINT(string& name, string& filename) {
    DoublyLinkedList<string> nums = LDreadfile(filename, name);

    string str;
    if (nums.size != 0) {
        nums.print();
    } else {
        cout << "Ошибка, нет такого списка или он пуст!" << endl;
        exit(1);
    }
}
void LDprocessing(string& command, string& filename) { // ф-ия обработки команд списка
    string name, value;

    if (command.substr(0, 8) == "LDPUSHB ") {
        stringstream stream(command.substr(8));;
        stream >> name >> value;
        LDPUSH(name, value, filename, "back"); 
    } else if (command.substr(0, 8) == "LDPUSHF ") {
        stringstream stream(command.substr(8));;
        stream >> name >> value;
        LDPUSH(name, value, filename, "front");
    } else if (command.substr(0, 7) == "LDPOPB ") {
        stringstream stream(command.substr(7));;
        stream >> name;
        LDPOP(name, filename, "back");
    } else if (command.substr(0, 7) == "LDPOPF ") {
        stringstream stream(command.substr(7));;
        stream >> name;
        LDPOP(name, filename, "front");
    } else if (command.substr(0, 9) == "LDREMOVE ") {
        stringstream stream(command.substr(9));;
        stream >> name >> value;
        LDREMOVE(name, value, filename);
    } else if (command.substr(0, 6) == "LDGET ") {
        stringstream stream(command.substr(6));;
        stream >> name >> value;
        LDGET(name, value, filename);
    } else if (command.substr(0, 8) == "LDPRINT ") {
        stringstream stream(command.substr(8));;
        stream >> name;
        LDPRINT(name, filename);
    } else {
        cout << "Ошибка, нет такой команды!" << endl;
        exit(1); 
    }
}

// Стек
void Sreadfile(string& filename, string& name, Stack<string>& nums) { // ф-ия чтения стека из файла
    Stack<string> copy(30);
    string str;
    ifstream fileinput;
    fileinput.open(filename);
    while (getline(fileinput, str)) {
        stringstream ss(str);
        string token;
        getline(ss, token, ' ');
        if (token == name) {
            while (getline(ss, token, ' ')) {
                copy.push(token);
            }
            while (copy.size() != 0) {
                nums.push(copy.peek());
                copy.pop();
            }
        }
    }
    fileinput.close();
}
void SPUSH(string& name, string& value, string& filename) {
    string textfull = Fulltext(filename, name);
    Stack<string> nums(30);
    Sreadfile(filename, name, nums);
    
    string str;
    if (nums.size() != 0) {
        nums.push(value);
        str = name + ' ';
        while(nums.size() != 0) {
            str += nums.peek() + ' ';
            nums.pop();
        }
        textfull += str;
        writefile(filename, textfull);
    } else {
        str = name + ' ' + value;
        textfull += str;
        writefile(filename, textfull);
    }
}
void SPOP(string& name, string& filename) {
    string textfull = Fulltext(filename, name);
    Stack<string> nums(30);
    Sreadfile(filename, name, nums);

    string str;
    if (nums.size() != 0) {
        nums.pop();
        str = name + ' ';
        while(nums.size() != 0) {
            str += nums.peek() + ' ';
            nums.pop();
        }
        textfull += str;
        writefile(filename, textfull);
    } else {
        cout << "Ошибка, нет такого стека или он пуст!" << endl;
        exit(1);
    }
}
void SPRINT (string& name, string& filename) {
    Stack<string> nums(30);
    Sreadfile(filename, name, nums);

    string str;
    if (nums.size() != 0) {
        while (nums.size() != 0) {
            cout << nums.peek() << " ";
            nums.pop();
        }
        cout << endl;
    } else {
        cout << "Нет такого стэка или он пуст!" << endl;
        exit(1);
    } 
}
void Sprocessing(string& command, string& filename) { // ф-ия обработки команд стека
    string name, value;

    if (command.substr(0, 6) == "SPUSH ") {
        stringstream stream(command.substr(6));
        stream >> name >> value;
        SPUSH(name, value, filename);
    } else if (command.substr(0, 5) == "SPOP ") {
        stringstream stream(command.substr(5));
        stream >> name;
        SPOP(name, filename);
    } else if (command.substr(0, 7) == "SPRINT ") {
        stringstream stream(command.substr(7));
        stream >> name;
        SPRINT(name, filename);
    } else {
        cout << "Ошибка, нет такой команды!" << endl;
        exit(1); 
    }
}

// Очередь
void Qreadfile(string& filename, string& name, Queue<string>& nums) { // ф-ия чтения очереди из файла
    string str;
    ifstream fileinput;
    fileinput.open(filename);
    while (getline(fileinput, str)) {
        stringstream ss(str);
        string token;
        getline(ss, token, ' ');
        if (token == name) {
            while (getline(ss, token, ' ')) {
                nums.push(token);
            }
        }
    }
    fileinput.close();
}
void QPUSH(string& name, string& value, string& filename) {
    string textfull = Fulltext(filename, name);
    Queue<string> nums(30);
    Qreadfile(filename, name, nums);
    
    string str;
    if (nums.Size() != 0) {
        nums.push(value);
        str = name + ' ';
        while(nums.Size() != 0) {
            str += nums.peek() + ' ';
            nums.pop();
        }
        textfull += str;
        writefile(filename, textfull);
    } else {
        str = name + ' ' + value;
        textfull += str;
        writefile(filename, textfull);
    }
}
void QPOP(string& name, string& filename) {
    string textfull = Fulltext(filename, name);
    Queue<string> nums(30);
    Qreadfile(filename, name, nums);

    string str;
    if (nums.Size() != 0) {
        nums.pop();
        str = name + ' ';
        while(nums.Size() != 0) {
            str += nums.peek() + ' ';
            nums.pop();
        }
        textfull += str;
        writefile(filename, textfull);
    } else {
        cout << "Ошибка, нет такой очереди или она пуста!" << endl;
        exit(1);
    }
}
void QPRINT (string& name, string& filename) {
    Queue<string> nums(30);
    Qreadfile(filename, name, nums);

    string str;
    if (nums.Size() != 0) {
        while (nums.Size() != 0) {
            cout << nums.peek() << " ";
            nums.pop();
        }
        cout << endl;
    } else {
        cout << "Нет такого стэка или он пуст!" << endl;
        exit(1);
    } 
}
void Qprocessing(string& command, string& filename) { // ф-ия обработки команд очереди
    string name, value;

    if (command.substr(0, 6) == "QPUSH ") {
        stringstream stream(command.substr(6));
        stream >> name >> value;
        QPUSH(name, value, filename);
    } else if (command.substr(0, 5) == "QPOP ") {
        stringstream stream(command.substr(5));
        stream >> name;
        QPOP(name, filename);
    } else if (command.substr(0, 7) == "QPRINT ") {
        stringstream stream(command.substr(7));
        stream >> name;
        QPRINT(name, filename);
    } else {
        cout << "Ошибка, нет такой команды!" << endl;
        exit(1); 
    }
}

// Хеш-таблица
template<typename T>
string printHashTable(const HashTable<T>& ht, string& name) { // Функция для перебора всех элементов хеш-таблицы
    string str = name + ' ';
    for (int i = 0; i < TABLE_SIZE; ++i) {
        KeyValuePair<T>* current = ht.table[i];
        while (current) {
            str += current->key + ':' + current->value + ' ';
            current = current->next;
        }
    }
    return str;
}
HashTable<string> Hreadfile(string& filename, string& name) { // ф-ия чтения Хеш-таблицы из файла
    HashTable<string> nums;
    string str;
    ifstream fileinput;
    fileinput.open(filename);
    while (getline(fileinput, str)) {
        stringstream ss(str);
        string token;
        getline(ss, token, ' ');
        if (token == name) {
            while (getline(ss, token, ' ')) {
                int position = token.find_first_of(':');
                token.replace(position, 1, " ");
                stringstream iss(token);
                string key, value;
                iss >> key >> value;
                nums.insert(key, value);
            }
        }
    }
    fileinput.close();
    return nums;
}
void HPUSH(string& name, string& key, string& value, string& filename) {
    string textfull = Fulltext(filename, name);
    HashTable<string> nums = Hreadfile(filename, name);
    
    string str;
    if (nums.sizetable != 0) {
        nums.insert(key, value);
        str = printHashTable(nums, name);
        textfull += str;
        writefile(filename, textfull);
    } else {
        str = name + ' ' + key + ':' + value;
        textfull += str;
        writefile(filename, textfull);
    }
}
void HPOP(string& name, string& key, string& filename) {
    string textfull = Fulltext(filename, name);
    HashTable<string> nums = Hreadfile(filename, name);

    string str;
    if (nums.sizetable != 0) {
        if (nums.remove(key)) {
            str = printHashTable(nums, name);
            textfull += str;
            writefile(filename, textfull);
        } else {
            cout << "Ошибка, нет такого ключа!" << endl;
            exit(1);
        }
    } else {
        cout << "Ошибка, нет такой таблицы или она пуста!" << endl;
        exit(1);
    }
}
void HGET(string& name, string& key, string& filename) {
    HashTable<string> nums = Hreadfile(filename, name);

    string str;
    if (nums.sizetable != 0) {
        if (!nums.get(key)) {
            cout << "Ошибка, нет такого ключа!" << endl;
            exit(1);
        }
    } else {
        cout << "Ошибка, нет такой таблицы или она пуста!" << endl;
        exit(1);
    }
}
void Hprocessing(string& command, string& filename) { // ф-ия обработки команд Хеш-таблицы
    string name, key, value;

    if (command.substr(0, 6) == "HPUSH ") {
        stringstream stream(command.substr(6));
        stream >> name >> key >> value;
        HPUSH(name, key, value, filename);
    } else if (command.substr(0, 5) == "HPOP ") {
        stringstream stream(command.substr(5));
        stream >> name >> key;
        HPOP(name, key, filename);
    } else if (command.substr(0, 5) == "HGET ") {
        stringstream stream(command.substr(5));
        stream >> name >> key;
        HGET(name, key, filename);
    } else {
        cout << "Ошибка, нет такой команды!" << endl;
        exit(1); 
    }
}

// Дерево
BinaryTree Treadfile(string& filename, string& name) {
    BinaryTree nums;
    string str;
    ifstream fileinput;
    fileinput.open(filename);
    while (getline(fileinput, str)) {
        stringstream ss(str);
        string token;
        getline(ss, token, ' ');
        if (token == name) {
            while (getline(ss, token, ' ')) {
                nums.insert(stoi(token));
            }
        }
    }
    fileinput.close();
    return nums;
}
void TPUSH(string& name, int& value, string& filename) {
    string textfull = Fulltext(filename, name);
    BinaryTree nums = Treadfile(filename, name);
    
    string str;
    if (nums.size != 0) {
        nums.insert(value);
        str = name + ' ' + nums.toString();
        textfull += str;
        writefile(filename, textfull);
    } else {
        str = name + ' ' + to_string(value);
        textfull += str;
        writefile(filename, textfull);
    }
}
void TSEARCH(string& name, int& value, string& filename) {
    BinaryTree nums = Treadfile(filename, name);

    if (nums.size != 0) {
        bool check = nums.search(value);
        if (check) cout << "True" << endl;
        else cout << "false" << endl;
    } else {
        cout << "Ошибка, нет такого дерева или оно пусто!" << endl;
        exit(1);
    }
}
void TCHECK(string& name, string& filename) {
    BinaryTree nums = Treadfile(filename, name);

    if (nums.size != 0) {
        if (nums.isComplete()) cout << "True" << endl;
        else if (!nums.isComplete()) cout << "False" << endl;
    } else {
        cout << "Ошибка, нет такого дерева или оно пусто!" << endl;
        exit(1);
    }
}
void TPRINT(string& name, string& filename) {
    BinaryTree nums = Treadfile(filename, name);

    if (nums.size != 0) {
        nums.print();
    } else {
        cout << "Ошибка, нет такого дерева или оно пусто!" << endl;
        exit(1);
    }
}
void Tprocessing(string& command, string& filename) { // ф-ия обработки команд дерева
    string name;
    int value;

    if (command.substr(0, 6) == "TPUSH ") {
        stringstream stream(command.substr(6));
        stream >> name >> value;
        TPUSH(name, value, filename);
    } else if (command.substr(0, 8) == "TSEARCH ") {
        stringstream stream(command.substr(8));
        stream >> name >> value;
        TSEARCH(name, value, filename);
    } else if (command.substr(0, 7) == "TCHECK ") {
        stringstream stream(command.substr(7));
        stream >> name;
        TCHECK(name, filename);
    } else if (command.substr(0, 7) == "TPRINT ") {
        stringstream stream(command.substr(7));
        stream >> name;
        TPRINT(name, filename);
    } else {
        cout << "Ошибка, нет такой команды!" << endl;
        exit(1); 
    }
}


int main(int argc, char* argv[]) {
    if (argc != 5) {
        cerr << "Использование: " << argv[0] << " --file <filename> --query '<command>'" << endl;
        return 1;
    }

    // Разбор аргументов командной строки
    string filename;
    string query;
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "--file") {
            filename = argv[++i];
        } else if (string(argv[i]) == "--query") {
            query = argv[++i];
        }
    }

    // Обработка команды
    string name;
    int value, index;
    if (query.substr(0, 1) == "M") { // Массив
        Mprocessing(query, filename);
    } else if (query.substr(0, 2) == "LS") { // Список
        LSprocessing(query, filename);
    } else if (query.substr(0, 2) == "LD") { // Список
        LDprocessing(query, filename);
    } else if (query.substr(0, 1) == "S") { // Стек
        Sprocessing(query, filename);
    } else if (query.substr(0, 1) == "Q") { // Очередь
        Qprocessing(query, filename);
    } else if (query.substr(0, 1) == "H") { // Хеш-таблица
        Hprocessing(query, filename);
    } else if (query.substr(0, 1) == "T") { // Дерево
        Tprocessing(query, filename);
    } else {
        cout << "Ошибка, неизвестная принадлежность структуры данных!" << endl;
        return 1;
    }

    return 0;
}
