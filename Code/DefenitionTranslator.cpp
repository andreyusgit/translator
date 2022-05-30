#include "AnnounProgram.h"

Translator::Translator()
{
}

Translator::~Translator()
{
}

vector<string> split(string, string);

void Translator::FromConsole(Translator& Class)
{
    string temp = "@";
    cout << "Enter your code in this window\nLine by line\nIf you want to stop, enter \"@\"\n";
    do {
        std::getline(std::cin, temp);
        if (temp == "@") break;
        Class.StringsInFile.push_back(temp);
    } while (temp != "@");
    Class.StringsInFile.push_back("~");
}

void Translator::FromFile(Translator& Class)
{
    string line;
    try {
        ifstream in("c:\\Users\\Andrey\\source\\repos\\Translator\\code.txt"); // окрываем файл для чтения
        if (in)
        {
            while (getline(in, line))
            {
                Class.StringsInFile.push_back(line);
            }
        }
        in.close();
    }
    catch (exception& ex) {
        cout << ex.what() << "\n";
    }
    Class.StringsInFile.push_back("~");
}

void Translator::FromFile(Translator& Class, string path)
{
    string line;
    try {
        ifstream in(path);
        if (in)
        {
            while (getline(in, line))
            {
                Class.StringsInFile.push_back(line);
            }
        }
        in.close();
    }
    catch (exception& ex) {
        cout << ex.what() << "\n";
    }
    Class.StringsInFile.push_back("~");
}

std::ostream& operator<<(std::ostream& os, const Translator& translator)
{
    for (int i = 0; i < translator.StringsInFile.size() - 1; i++) {
        os << translator.StringsInFile[i] << "\n";
    }
    return os;
}

void Translator::Translate(Translator& translate) {
    int i = 0;
    vector<string> variables;
    remove("result.cpp");
    std::string filename = "result.cpp";
    {
        ofstream ostrm(filename, std::ios::binary);
        ostrm << "#include <iostream>\n#include <string>\n\nint code()\n{\ntry{\n";
        while (translate.StringsInFile[i] != "~")
        {
            string coppyline = "";
            vector<string> line = split(translate.StringsInFile[i]," ");
            for (int k = 0; k < line.size(); k++) {
                try {
                    std::size_t found = line[k].find(".");
                    std::size_t found2 = line[k].find("(");
                    string console = line[k].substr(found + 1, found2 - found - 1);
                    if (console == "Write") {
                        coppyline = translate.StringsInFile[i];
                        line[k] = "Wri";
                    }
                    else if (console == "WriteLine") {
                        coppyline = translate.StringsInFile[i];
                        line[k] = "Con";
                    }
                }
                catch (...)
                {
                }
                switch (dictionary[line[k]])
                {
                case 1: {
                    k++;
                    string temp = line[k];  
                    k++;
                    if (line[k] == "=") {
                        k++;
                        variables.push_back(temp);
                        ostrm << "auto" << " " << temp << " = ";
                        for (int l = k; l < line.size(); l++)
                        {
                            ostrm << line[l] << " ";
                            k = l;
                        }
                        ostrm << ";\n";
                    }
                    else {
                        k++;
                        variables.push_back(temp);
                        ostrm << Translator::GetType(line[k]) << " " << temp << " ";
                        k++;
                        if ((line.size() > k)) {
                            if ((line[k] == "=")) {
                                for (int l = k; l < line.size(); l++)
                                {
                                    ostrm << line[l] << " ";
                                    k = l;
                                }
                            }
                        }
                        ostrm << ";\n";
                    }
                    k = line.size();
                    break;
                }
                case 2: { 
                    ostrm << "}\nelse "; 
                    line[k] = "If";
                    k--;
                    break;
                }
                case 3: {
                    ostrm << " if(( "; 
                    for (int l = k+1; l < line.size() - 1; l++) {
                        switch (dictionary[line[l]])
                        {
                        case 9:
                            ostrm << " == ";
                            break;
                        case 4: ostrm << ") && (";
                            break;
                        case 5: ostrm << ") || (";
                            break;
                        default:
                            ostrm << line[l];
                                break;
                        }
                    }
                    k = line.size() - 2;

                }
                    break;
                case 6: ostrm << " // ";
                {
                    for (int l = k + 1; l < line.size(); l++)
                    {
                        ostrm << line[l] << " ";
                        k = l;
                    }
                    ostrm << "\n";
                    break;
                }
                case 7: {
                    ostrm << " std::cout <<  ";
                    std::size_t found = coppyline.find("(");
                    std::size_t found2 = coppyline.find(")");
                    vector<string> lines = split(coppyline.substr(found + 1, found2 - found - 1), " ");
                    for (int l = k; l < lines.size(); l++)
                    {
                        if (lines[l] == "+") ostrm << " << ";
                        else ostrm << lines[l] << " ";
                        k = l;
                    }
                    ostrm << " << std::endl;\n";
                    break;
                }
                case 8: {
                    ostrm << " std::cout <<  ";
                    std::size_t found = coppyline.find("(");
                    std::size_t found2 = coppyline.find(")");
                    ostrm << coppyline.substr(found + 1, found2 - found - 1);
                    ostrm << " ;\n";
                    break;
                }
                case 10: {
                    ostrm << " )) {\n ";
                    break;
                }
                case 11: {
                    ostrm << " }\n ";
                    k = line.size();
                    break;
                }
                case 12: {
                    string nameOfVar;
                    bool check = false; 
                    ostrm << "for(";
                    k += 2;
                    if (line[k] == "=") {
                        k--;
                        nameOfVar = line[k];
                        ostrm << "int ";
                        k += 2;
                    }
                    else {
                        k++;
                        ostrm << Translator::GetType(line[k]);
                        k -= 2; 
                        nameOfVar = line[k];
                        k += 4;
                    }
                    int firstbord = stoi(line[k]);
                    k += 2;
                    int secondbord = stoi(line[k]);
                    ostrm << nameOfVar << " = ";
                    if (firstbord < secondbord) {
                        ostrm << firstbord << "; " << nameOfVar << " <= " << secondbord << ";" << nameOfVar;
                        check = true;
                    }
                    else {
                        ostrm << firstbord << "; " << nameOfVar << " >= " << secondbord << ";" << nameOfVar;
                    }
                    k++;
                    if ((line.size() > 8) || ((line.size() > 6) && (line[k] == "Step"))) {
                        k ++; 
                        ostrm << " = " << nameOfVar << " + (" << line[k] << ")) {\n";
                    }
                    else {
                        if (check) ostrm << "++;) {\n";
                        else ostrm << "--;) {\n";
                    }
                    k = line.size();
                    break;
                }                
                case 13: {
                    ostrm << " }\n ";
                    break;
                }
                default:
                {
                    for (int i = 0; i < variables.size(); i++) {
                        if (line[k] == variables[i]) {
                            k += 2;
                            std::size_t found = line[k].find(".");
                            std::size_t found2 = line[k].find("(");
                            string console = line[k].substr(found + 1, found2 - found - 1);
                            if (console == "ReadLine") {
                                ostrm << "std::cin >> ";
                                ostrm << variables[i];
                            }
                            else {
                                ostrm << variables[i] << " = ";
                                for (int l = k; l < line.size(); l++)
                                {
                                    ostrm << line[l] << " ";
                                    k = l;
                                }
                            }
                            ostrm << " ;\n";
                        }
                    }
                    k = line.size();
                    break;
                }
                }
            }
            i++;
        }
        ostrm << "}\ncatch(...)\n{\nstd::cout << \"Error\";\n}\nreturn 0; \n}";
    }
}

vector<string> split(string line, string t) {
    vector<string> arr;
    string delim = t;
    size_t prev = 0;
    size_t next;
    size_t delta = delim.length();
    string temp = line.substr(0, 3);
    while (true) {
        if (line[0] == ' ') {
            line.erase(line.begin());
        }
        else break; 
    }
    if (temp != "Con" || temp != "Wri") {
        while ((next = line.find(delim, prev)) != string::npos) {
            arr.push_back(line.substr(prev, next - prev));
            prev = next + delta;
        }
        arr.push_back(line.substr(prev));
    }
    else {
        arr.push_back(line);
    }
    return arr;
}

string Translator::GetType(string line) {
    switch (types[line])
    {
    case 1: return "int";
    case 2: return "bool";
    case 3: return "char";
    case 4: return "double";
    case 5: return "long";
    case 6: return "std::string";
    case 7: return "short";
    default:
        break;
    }
    return "auto";
}
