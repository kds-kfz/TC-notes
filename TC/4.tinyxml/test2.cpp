#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cassert>

#include "tinyxml/tinyxml.h"

using namespace std;

struct StruXmlInfo{
    string id;
    string name;
    string range;
};

int XmlExp(const char* xmlpath)
{
    TiXmlDocument docXml;
    TiXmlElement* element = NULL;
    TiXmlAttribute *attr = NULL;
    StruXmlInfo StruTemp;
    vector<StruXmlInfo> VecXmlInfo;
    VecXmlInfo.clear();
    if (docXml.LoadFile(xmlpath) == true)
    {
        docXml.Print();
        cout<<"\n以下是解析\n"<<endl;
        element = docXml.RootElement();
        TiXmlElement *ele_result = element->FirstChildElement();
        TiXmlElement *element2 = ele_result->FirstChildElement();
//        for(; ele_result != NULL; ele_result = ele_result->NextSiblingElement()){
            while (element2)
            {
                TiXmlElement *element3 = element2->FirstChildElement();
                printf("[%s]\n", ele_result->Value());
                for (int i = 0; i < 3; i++)
                {
                    const char* pContent = element3->GetText();
                    if (i == 0)
                    {
                        StruTemp.id = pContent;
                        //printf("%s\n", pContent);
                    }
                    if (i == 1)
                    {
                        StruTemp.name = pContent;
                        //printf("%s\n", pContent);
                    }
                    if (i == 2)
                    {
                        StruTemp.range = pContent;
                        //printf("%s\n", pContent);
                    }
                    printf("[%s]:[%s]\n", element3->Value(), pContent);
                    element3 = element3->NextSiblingElement();
                }
                cout<<"----------"<<endl;
                VecXmlInfo.push_back(StruTemp);
                element2 = element2->NextSiblingElement();
            }
            element2 = ele_result->FirstChildElement();
            printf("[/%s]\n", ele_result->Value());
//        }
        ele_result = ele_result->NextSiblingElement();
        printf("[%s]\n", ele_result->Value());
        element2 = ele_result->FirstChildElement();
        printf("[%s]:[%s]\n", element2->Value(), element2->GetText());
        printf("[/%s]\n", ele_result->Value());
        cout<<"----------"<<endl;


        /*while (element3)
          {
          const char* pContent = element3->GetText();
          StruTemp.id = pContent;

          printf("%s\n", pContent);
          element3 = element3->NextSiblingElement();      
          }*/


    }
    return 0;
}

int main(int argc, char *argv[]){
    if(argc < 2){
        cout<<"缺少参数"<<endl;
        exit(-1);
    }
    int ret = XmlExp(argv[1]);
    if(ret == 0){
        cout<<"解析xml成功"<<endl;
    }

    return 0;
}
