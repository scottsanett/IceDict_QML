#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <QResource>
#include <QFile>
#include "pagedownloader.h"

using map_t = std::multimap<std::string, int>;
using mapptr_t = std::shared_ptr<map_t>;
using mapptrvec_t = std::vector<mapptr_t>;
using mapptrvecptr_t = std::shared_ptr<mapptrvec_t>;
using strset_t = std::set<std::string>;
using strsetptr_t = std::shared_ptr<strset_t>;
using strptr_t = std::shared_ptr<std::string>;
using strvec_t = std::vector<std::string>;
using strvecptr_t = std::shared_ptr<strvec_t>;
using vecstrvecptr_t = std::vector<strvecptr_t>;
using ptrvecstrvecptr_t = std::shared_ptr<vecstrvecptr_t>;
using strvecptrmap_t = std::multimap<std::string, strvecptr_t>;
using strvecptrmapptr_t = std::shared_ptr<strvecptrmap_t>;
using strvecptrmapptrvec_t = std::vector<strvecptrmapptr_t>;
using strvecptrmapptrvecptr_t = std::shared_ptr<strvecptrmapptrvec_t>;
using vecpair_t = std::vector<std::pair<std::string, strvec_t>>;

class Dictionary: public QObject
{
    Q_OBJECT
public:
    Dictionary();
    ~Dictionary();
    void setRoot(QObject*, QObject*);

public slots:
    void loadPageDefinition();
    void loadPageTextual();
    void onlineDefinition(QString);
    void onlineDefSelected(int);
    void onlineText(QString);
    void onlineTextSelected(int);
    void findDefinition(QString);
    void findDefSelected(int);
    void textualSearch(QString);
    void textualSearchSelected(int);
    void findInflection(QString);
    void printAll(QString);
    void printAllSelected(int);
    void textChanged(QString);

private:
    QObject * root;
    QObject * item1;
    PageDownloader * pageControl;
    std::string webpage;
    std::string inputted;
    std::map<std::string, std::string> writeRules = {
        std::make_pair("á", "%E1"), std::make_pair("é", "%E9"), std::make_pair("í", "%ED"), std::make_pair("ó", "%F3"),
        std::make_pair("ú", "%FA"), std::make_pair("ý", "%FD"), std::make_pair("Á", "%C1"), std::make_pair("É", "%C9"),
        std::make_pair("Í", "%CD"), std::make_pair("Ó", "%D3"), std::make_pair("Ú", "%DA"), std::make_pair("Ý", "%DD"),
        std::make_pair("æ", "%E6"), std::make_pair("ö", "%F6"), std::make_pair("Æ", "%C6"), std::make_pair("Ö", "%D6"),
        std::make_pair("þ", "%FE"), std::make_pair("ð", "%F0"), std::make_pair("Þ", "%DE"), std::make_pair("Ð", "%D0"),
    };
    std::string writeUrl1 = "http://digicoll.library.wisc.edu/cgi-bin/IcelOnline/IcelOnline.TEId-idx?type=simple&size=First+100&rgn=lemma&q1=";
    std::string writeUrl2 = "&submit=Search";
    std::string textUrl1 = "http://digicoll.library.wisc.edu/cgi-bin/IcelOnline/IcelOnline.TEId-idx?type=simple&size=First+100&rgn=dentry&q1=";
    std::string textUrl2 = "&submit=Search";
    std::string printOneWord;
    std::string printOneForm;
    bool textReady = false;
    int typeTimes = 0;
    std::vector<std::string> stored;
    std::vector<bool> flags = {0, 0, 0, 0, 0, 0, 0};
    mapptrvecptr_t inflectionals;
    mapptrvecptr_t definitions;
    mapptrvecptr_t originals;
    strvecptrmapptrvecptr_t dictionaries;
    strsetptr_t forms;
    strsetptr_t wordindex;
    std::string addStyleToResults(std::string str);
    std::string wordToWrite(std::string);
    std::map<std::string, std::string> onlineEntries;
    std::map<std::string, std::string> onlineTextEntries;
    std::multimap<std::string, std::vector<std::string>> definitionResults;
    std::multimap<std::string, std::vector<std::string>> resultsToPrint;
    std::multimap<std::string, std::string> textualResults;
    void downloadPageDefinition(std::string url);
    void downloadPageTextual(std::string url);
    void parsePageDefinition();
    void parsePageTextual();
    void buttonChangeColor();
    void importWordIndex();
    void importForms();
    void importInflections();
    void importInflectionsThread(mapptrvecptr_t mapvec, int i);
    void importWordIndexThread(mapptrvecptr_t mapvec, std::string const name, int i);
    void importOriginal();
    void importOriginalThread(mapptrvecptr_t mapvec, int i);
    void importDictionary();
    void importDictionaryThread(std::string const name, int i);

    void findInflectionThread(ptrvecstrvecptr_t dics, std::string word, int index);

    void findDefinitionPrint(int index);
    void textualSearchThread(std::string word, int index);
    void textualSearchPrint(int index);

    void printAllThread(std::string word, int index);
};


template <typename T>
std::string to_string(T value)
{
  std::ostringstream os ;
  os << value ;
  return os.str() ;
}


#endif // DICTIONARY_H
