//Encoder_Decoder programm that takes a string and puts every 8 characters
//on the vertexes of cubes(more then one if more then 8 chars in string)
//programm allows either to input the string you to encode
//or input already encoded string and key for decoding

#include <iostream>
#include <vector>
#include <fstream>

const int VertexCube = 8;

class Cube
{
private:    
    std::string str;
public:
    Cube(std::string s) : str(s) {
        while(str.size() < VertexCube){
            str.push_back(' ');
        }
    }
    Cube() = delete;
    Cube(const Cube&) = delete;
    Cube& operator=(const Cube&) = delete;
    void rotate_right();
    void rotate_left();
    void rotate_up();
    void rotate_down();
    std::string get_cube() const {return str;}
};

namespace Utility 
{
    std::vector<std::string> mode_slicer(std::string mode) //need copy
    {
        std::vector<std::string> mode_str(10);
        for (size_t i = 0, k = 0; i < mode.size();)
        {
            for (size_t j = 0; j < 3; j++)
            {
                if(isalpha(mode[i])) {
                    mode_str[k].push_back(mode[i]);
                } else {
                    --j;
                }
                if(i == mode.size() || i > mode.size()){
                    break;
                }
                ++i;
            }
            ++k;
        }
        return mode_str;
    }

    std::string set_key(std::string mode) //need copy
    {
        std::string Key;
        std::vector<std::string> mode_str = mode_slicer(mode);
        std::vector<std::string> tmp = mode_str;
        for (size_t i = 0; i < mode_str.size(); i++)
        {
            for (size_t j = 0, k = 2; j < 3; j++, --k)
            {
                tmp[i][j] = mode_str[i][k];
                if(tmp[i][j] == 'U'){tmp[i][j] = 'D';}
                else if(tmp[i][j] == 'D'){tmp[i][j] = 'U';}
                else if(tmp[i][j] == 'L'){tmp[i][j] = 'R';}
                else if(tmp[i][j] == 'R'){tmp[i][j] = 'L';}
            }
            if (!mode_str[i].empty()) { Key += tmp[i]; }
        }
        for (size_t i = 0; i < Key.size(); i++)
        {
            if (isalpha(Key[i])) {
                Key.insert(i, 1, ':'); ++i;
            }       
        }
        for (size_t i = 0, j = 0; i < Key.size(); i += 7, j++)
        {
            Key.insert(i, 1, ('1' + j));
        }
        for (size_t i = 0; i < Key.size(); i++)
        {
            if(i > 0 && isdigit(Key[i])) {
                Key.insert(i, 1, ',' );
                ++i;
            }
        }   
        return Key;
    }

    std::string encode(std::string str, std::string mode) 
    {
        std::vector<std::string> vecstr(10);
        for (size_t i = 0, k = 0; i < str.size();)
        {       
            for (size_t j = 0; j < VertexCube; j++)
            {
                vecstr[k].push_back(str[i]);
                if(i == str.size() || i > str.size()) {
                    break;
                }
                ++i;
            }
            ++k; 
        }  

        std::vector<std::string> mode_str = mode_slicer(mode);  

        std::string Encoded_str;
        for (size_t i = 0; i < vecstr.size(); i++)
        {
            Cube obj(vecstr[i]);
            for (size_t k = 0; k < 3; k++)
            {
                if(mode_str[i][k] == 'R'){obj.rotate_right();}
                else if(mode_str[i][k] == 'D'){obj.rotate_down();}
                else if(mode_str[i][k] == 'U'){obj.rotate_up();}
                else if(mode_str[i][k] == 'L'){obj.rotate_left();}
                else{break;}            
            }        
            if (!vecstr[i].empty()) { Encoded_str += obj.get_cube(); }
        }
        return Encoded_str;
    } 

} //Utility namespace

void Cube::rotate_right() {
    std::string tmp (VertexCube, ' ');
    tmp[0] = str[4];
    tmp[1] = str[0];
    tmp[2] = str[6];
    tmp[3] = str[2];
    tmp[4] = str[5];
    tmp[5] = str[1];
    tmp[6] = str[7];
    tmp[7] = str[3];
    str = tmp;
}

void Cube::rotate_left() {
    std::string tmp (VertexCube, ' ');
    tmp[0] = str[1];
    tmp[1] = str[5];
    tmp[2] = str[3];
    tmp[3] = str[7];
    tmp[4] = str[0];
    tmp[5] = str[4];
    tmp[6] = str[2];
    tmp[7] = str[6];
    str = tmp;
}

void Cube::rotate_up() {
    std::string tmp (VertexCube, ' ');
    tmp[0] = str[2];
    tmp[1] = str[3];
    tmp[2] = str[6];
    tmp[3] = str[7];
    tmp[4] = str[0];
    tmp[5] = str[1];
    tmp[6] = str[4];
    tmp[7] = str[5];
    str = tmp;
}

void Cube::rotate_down() {
    std::string tmp (VertexCube, ' ');
    tmp[0] = str[4];
    tmp[1] = str[5];
    tmp[2] = str[0];
    tmp[3] = str[1];
    tmp[4] = str[6];
    tmp[5] = str[7];
    tmp[6] = str[2];
    tmp[7] = str[3];
    str = tmp;
}
int main(){
    std::ofstream fout;
    fout.open("encodes.txt", std::ofstream::app);
    std::cout<<"Hello and welcome to encoder!\n"
        <<"Do you have a sentence to encode or you want to use a default senctence?\n"
        <<"[ \'a\' for writing your own sentence]\t[ \'b\' if you want to type a encoded sentence and key getting the right sentence\")]\n"
        <<"Your choice: ";
    char choice; int count{1};
    while(std::cin>>choice){
        if(choice == 'a'){
            std::cin.get(); 
            std::string user_sentence;
            std::cout<<"Ok, then write your sentence you want to encode!\n";
            std::getline(std::cin, user_sentence);
            std::cout<<"Here is the way you have to encode\n"
                <<"1:U:D:L,2:U:R:D,3:L:R:D\t this is an example(you should know the rules!\n";
            std::string encoder_mode;
            std::getline(std::cin, encoder_mode);
            std::cout<<"Here is the result of encoding:\n";
            std::cout<<Utility::encode(user_sentence, encoder_mode);
            std::cout<<"\nHere is the key for decoding your sentence:\n";
            std::cout<<Utility::set_key(encoder_mode);
            if(fout.is_open()){
                fout<<count<<": "<<"User sentence: "<<user_sentence<<"\tEncoded mode: "<<encoder_mode<<std::endl;
                fout<<"  "<<"Encoded: "<<Utility::encode(user_sentence, encoder_mode)<<"\tKey for decoding: "<<Utility::set_key(encoder_mode)<<std::endl;
            } else {
                throw std::invalid_argument("Couldn't open the file\n, Bye\n");
                exit(EXIT_FAILURE);
            }
            std::string yes_no;
            std::cout<<"\nDo you want to encode more sentences?[yes]/[no]\n";
            std::getline(std::cin, yes_no);
            if(yes_no == "yes"){count++;std::cout<<"Enter a choice: ";continue;}
            else if(yes_no == "no"){std::cout<<"Now your encodes are in encode.txt file, Bye!\n";break;}
            else{std::cout<<"learn how to type man!, Bye\n"; break;}
        } else if (choice == 'b'){
            std::cout<<"So you want to decode a sentence?\n"
                <<"Ok, give me the sentence: ";
                std::string sentence_for_decode;
                std::cin.get();
                std::getline(std::cin, sentence_for_decode);
                std::cout<<"A key please: ";
                std::string key;
                std::getline(std::cin, key);
                std::cout<<"Here is your decoded sentence:\n";
                std::cout<<Utility::encode(sentence_for_decode, key)<<std::endl;
                std::cout<<"More sentence for decoding? [yes/no]";
                std::string yes_no;
                std::getline(std::cin, yes_no);
                if(yes_no == "yes"){continue;}
                else if(yes_no == "no"){std::cout<<"Bye!\n";break;}
                else{std::cout<<"learn how to type man!, Bye\n"; break;}
        }
        else{
            std::cout<<"Invalid choice"<<std::endl;
            std::cin.clear();
        }        
    }

        return 0;
}