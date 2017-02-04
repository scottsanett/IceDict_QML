#include "dictionary.h"

Dictionary::Dictionary(QObject * arg1, QObject * arg2) {
    Q_INIT_RESOURCE(resource);
    root = arg1;
    item1 = arg2;
    inflectionals = mapptrvecptr_t(new mapptrvec_t);
    definitions = mapptrvecptr_t(new mapptrvec_t);
    originals = mapptrvecptr_t(new mapptrvec_t);
    wordindex = strsetptr_t(new strset_t);
    dictionaries = strvecptrmapptrvecptr_t(new strvecptrmapptrvec_t);
    forms = strsetptr_t(new strset_t);
    for (int i = 0; i < 7; ++i) {
        inflectionals->push_back(mapptr_t(new map_t));
        originals->push_back(mapptr_t(new map_t));
    }
    for (int i = 0; i < 2; ++i) {
        definitions->push_back(mapptr_t(new map_t));
        dictionaries->push_back(strvecptrmapptr_t(new strvecptrmap_t));
    }
    importWordIndex();
//    importForms();
    importOriginal();
    importDictionary();
    importInflections();
}

Dictionary::~Dictionary() { }

std::string Dictionary::addStyleToResults(std::string line) {
    std::istringstream iss(line);
    std::string key;
    iss >> key;
    if (key.back() != ';') {
        std::string temp;
        iss >> temp;
        key += ' ' + temp;
    }
    else {
        key = key.substr(0, key.length() - 1);
    }
    key = "<th>" + key + "</th>";
    std::string arg2;
    iss >> arg2;
    arg2 = arg2.substr(0, arg2.length() - 1);
    arg2 = "<td>" + arg2 + "</td>";
    std::string arg3;
    iss >> arg3;
    arg3 = arg3.substr(0, arg3.length() - 1);
    arg3 = "<td><font color=\"red\">" + arg3 + "</font></td>";
    std::string arg4;
    std::string temp;
    while (iss >> temp) {
        arg4 += temp + ' ';
    }
    arg4 = arg4.substr(0, arg4.length() - 1);
    arg4 = "<td>" + arg4 + "</td>";
    line = "<tr>" + key + arg2 + arg3 + arg4 + "</tr>";
    return line;
}


std::string Dictionary::wordToWrite(std::string str) {
    for (auto && i : writeRules) {
        while (str.find(i.first) != std::string::npos) {
            auto pos = str.find(i.first);
            str.replace(pos, i.first.length(), i.second);
        }
    }
    return str;
}

void Dictionary::importForms() {
    QFile f(":/alphabet/forms");
    f.open(QIODevice::ReadOnly);
    QString qfile = f.readAll();
    std::istringstream file(qfile.toStdString());
    std::string line;
    while (std::getline(file, line)) {
        forms->insert(line);
    }
    f.close();
}

/* import the index for all words in the two dictionaries */

void Dictionary::importWordIndex() {
    QFile wd(":/alphabet/wordindex");
    wd.open(QIODevice::ReadOnly);
    QString file = wd.readAll();
    std::istringstream wordindexfile(file.toStdString());
    std::string line;
    while (std::getline(wordindexfile, line)) {
        wordindex->insert(line);
    }
    wd.close();
}

void Dictionary::importInflections() {
    for (auto i = 1; i <= 7; ++i) {
        importInflectionsThread(inflectionals, i);
    }
}

/*import all the inflection forms and its position*/
void Dictionary::importInflectionsThread(mapptrvecptr_t mapvec, int i) {
    std::string filename = ":/alphabet/source_reverse_index/part" + to_string(i);
    QFile f(filename.c_str());
    f.open(QIODevice::ReadOnly);
    QString qfile = f.readAll();
    std::istringstream file(qfile.toStdString());
    std::string line;
    int index = 0;
    auto thisMap = mapvec->at(i - 1);
    while (std::getline(file, line)) {
        thisMap->insert(std::make_pair(line, index));
        ++index;
    }
    f.close();
}

void Dictionary::importOriginalThread(mapptrvecptr_t mapvec, int i) {
    std::string filename = ":/alphabet/sources_index/part" + to_string(i);
    QFile f(filename.c_str());
    f.open(QIODevice::ReadOnly);
    QString qfile = f.readAll();
    std::istringstream file(qfile.toStdString());
    std::string line;
    auto thisMap = mapvec->at(i - 1);
    while (std::getline(file, line)) {
        std::string key;
        std::istringstream iss(line);
        iss >> key;
        if (key.back() != ';') {
            std::string temp;
            iss >> temp;
            key += " " + temp;
        }
        std::string index;
        iss >> index;
        auto index_number = strtol(index.c_str(), 0, 10);
        thisMap->insert(std::make_pair(key, index_number));
//        thisMap->insert(std::make_pair(key, std::stoul(index)));
    }
    f.close();
}

void Dictionary::importOriginal() {
    for (auto i = 1; i <= 7; ++i) {
        importOriginalThread(originals, i);
    }
}

void Dictionary::importDictionary() {
    importDictionaryThread("zoega", 0);
    importDictionaryThread("vifgusson", 1);
}

void Dictionary::importDictionaryThread(std::string const name, int i) {
    std::string filename = ":/alphabet/" + name;
    QFile f(filename.c_str());
    f.open(QIODevice::ReadOnly);
    QString qfile = f.readAll();
    std::istringstream file(qfile.toStdString());
    std::string line;
    auto thisMap = dictionaries->at(i);
    while (std::getline(file, line)) {
        auto entry = strvecptr_t(new strvec_t);
        std::istringstream iss(line);
        std::string key;
        iss >> key;
        std::string sense;
        std::string temp;
        while (iss >> temp) {
            sense += ' ' + temp;
            if (temp.back() == ';') {
               sense += '\n';
               entry->push_back(sense);
               sense = "";
            }
        }
        thisMap->insert(std::make_pair(key, entry));
    }
    f.close();
}

void Dictionary::textChanged(QString str) {
    definitionResults.clear();
    stored.clear();
    std::string word = str.toStdString();
    auto item3 = root->findChild<QObject*>("item3");
    if (word.length() > 1) {
        for (auto && entry : *wordindex) {
            auto pos = entry.find(word);
            if (pos == 0) {
                stored.push_back(entry);
                QMetaObject::invokeMethod(item3, "addItemToList", Q_ARG(QVariant, entry.c_str()));
            }
        }
    }
}

void Dictionary::findDefinition(QString str) {
    stored.clear();
    definitionResults.clear();
    auto item3 = root->findChild<QObject*>("item3");
    QMetaObject::invokeMethod(item3, "clearList");
    flags = {0, 0, 1, 0, 0, 0, 0};
    std::string word = "<b>" + str.toStdString() + "</b>";
    auto zisspair = dictionaries->at(0)->equal_range(word);
    auto visspair = dictionaries->at(1)->equal_range(word);
    if ((zisspair.first == zisspair.second) && (visspair.first == visspair.second)) {
        /*
         * Word not found
         */
        return;
    }
    for(auto itr = zisspair.first; itr != zisspair.second; ++itr) {
        auto key = itr->first;
        auto thisEntry = *itr->second;
        definitionResults.insert(std::make_pair(key, thisEntry));
    }
    for (auto itr = visspair.first; itr != visspair.second; ++itr) {
        auto key = itr->first;
        auto thisEntry = *itr->second;
        definitionResults.insert(std::make_pair(key, thisEntry));
    }
    for (auto && i : definitionResults) {
        std::string key = i.first.c_str();
        key = key.substr(3, key.length() - 7);
        auto item3 = root->findChild<QObject*>("item3");
        QMetaObject::invokeMethod(item3, "addItemToList", Q_ARG(QVariant, key.c_str()));
    }
    findDefinitionPrint(0);
}

void Dictionary::findDefSelected(int index) {
    if (definitionResults.size() == 0) {
        findDefinition(stored[index].c_str());
    }
    else {
        findDefinitionPrint(index);
    }
}

void Dictionary::findDefinitionPrint(int index) {
    auto itr = definitionResults.begin();
    for(int i = 0; i < index; ++i) {
        itr = std::next(itr);
    }
    std::string key = itr->first;
    std::string value;
    for (auto i : itr->second) {
        value += i + '\n';
    }
    std::string display = key + ' ' + value;
    display = "<p align=\"justify\"><span style=\"font-family: Perpetua; font-size: 16pt;\">" + display + "</span></p>";
    auto textarea3 = root->findChild<QObject*>("textArea3");
    QMetaObject::invokeMethod(textarea3, "clear");
    QMetaObject::invokeMethod(textarea3, "append", Q_ARG(QString, display.c_str()));
}

void Dictionary::findInflection(QString str) {
    std::string word = str.toStdString();
    auto results = ptrvecstrvecptr_t(new vecstrvecptr_t);
    for (auto i = 0; i < 7; ++i) {
        results->push_back(strvecptr_t(new strvec_t));
    }
    for (auto i = 0; i < 7; ++i) {
        findInflectionThread(results, word, i);
    }
    auto resultSize = [&]() { int sz = 0; for (auto i : *results) { sz += i->size(); } return sz; }();
    if (resultSize == 0) {
        /*
        auto * tabActive = dynamic_cast<QTextBrowser*>(ui->resultsTab->currentWidget());
        tabActive->setText("Word not found");
        */
        return;
    }
    std::string toprint;
    for (auto && i : *results) {
        for (auto && j : *i) {
            j = addStyleToResults(j);
            toprint += j + "\n\n";
        }
    }
    toprint = "<span style=\"font-family: Perpetua; font-size: 16pt;\"><p align=\"center\"><table border=\"0.5\" cellpadding=\"10\">" + toprint + "</table></p></span>";
    auto textarea5 = root->findChild<QObject*>("textArea5");
    QMetaObject::invokeMethod(textarea5, "clear");
    QMetaObject::invokeMethod(textarea5, "append", Q_ARG(QString, toprint.c_str()));
}

void Dictionary::findInflectionThread(ptrvecstrvecptr_t results, std::string word, int index) {
    auto thisDic = inflectionals->at(index);
    auto thisResult = results->at(index);
    auto itr = thisDic->find(word);
    if (itr == thisDic->end()) { return; }
    std::string filename = ":/alphabet/sources/part" + to_string(index + 1);
    QFile file(filename.c_str());
    file.open(QIODevice::ReadOnly);
    auto qfile = file.readAll();
    std::istringstream issfile(qfile.toStdString());
    std::string line;
    auto key = itr->first;
    auto pos = itr->second;
    int currentPos = 0;
    while (std::getline(issfile, line)) {
        if (currentPos != pos) {
            ++currentPos;
            continue; }
        else {
            if (itr->first != key) { break; }
            thisResult->push_back(line);
            itr = std::next(itr);
            ++currentPos;
            pos = itr->second;
        }
    }
    file.close();
}

void Dictionary::textualSearch(QString str) {
    textualResults.clear();
    auto item4 = root->findChild<QObject*>("item4");
    QMetaObject::invokeMethod(item4, "clearList");
    std::string word = str.toStdString();
    textualSearchThread(word, 0);
    textualSearchThread(word, 1);
    if (textualResults.size() == 0) {
/*
 * no results's been found
 */
        return;
    }
    for (auto i : textualResults) {
        std::string key = i.first;
        if (key.length() > 7) {
            key = key.substr(3, key.length() - 7);
            QMetaObject::invokeMethod(item4, "addItemToList", Q_ARG(QVariant, key.c_str()));
        }
    }
}

void Dictionary::textualSearchThread(std::string word, int index) {
    auto thisDic = dictionaries->at(index);
    for (auto && i : *thisDic) {
        std::string key = i.first;
        for (auto && j : *i.second) {
            auto pos = j.find(word);
            if (pos != std::string::npos) {
                auto subsitute = "<b><span style=\"color:#ff0000;\">" + word + "</span></b>";
                j.replace(pos, word.length(), subsitute);
                std::string value = key + ' ' + j;
                textualResults.insert(std::make_pair(key, value));
                break;
            }
        }
    }
}

void Dictionary::textualSearchSelected(int index) {
    auto itr = textualResults.begin();
    for (auto i = 0; i < index; ++i) {
        itr = std::next(itr);
    }
    std::string key = itr->first;
    std::string display = itr->second;
    display = "<p align=\"justify\"><span style=\"font-family: Perpetua; font-size: 16pt;\">" + display + "</span></p>";
    auto textarea4 = root->findChild<QObject*>("textArea4");
    QMetaObject::invokeMethod(textarea4, "clear");
    QMetaObject::invokeMethod(textarea4, "append", Q_ARG(QString, display.c_str()));
}

void Dictionary::printAll(QString str) {
    auto item6 = root->findChild<QObject*>("item6");
    QMetaObject::invokeMethod(item6, "clearList");
    resultsToPrint.clear();
    std::string word = str.toStdString() + ';';
    auto & results = resultsToPrint;
    for (auto i = 0; i < 7; ++i) {
        printAllThread(word, i);
    }
    auto resultSize = [&]() { int sz = 0; for (auto i : results) { sz += i.second.size(); } return sz; }();
    if (resultSize == 0) {
        /*
        auto * tabActive = dynamic_cast<QTextBrowser*>(ui->resultsTab->currentWidget());
        tabActive->setText("Word not found.");
        */
        return;
    }
    for (auto && i : results) {
        QMetaObject::invokeMethod(item6, "addItemToList", Q_ARG(QVariant, i.first.c_str()));
    }
    printAllSelected(0);
}

void Dictionary::printAllThread(std::string word, int index) {
    auto thisDic = originals->at(index);
    auto & thisResult = resultsToPrint;
    auto range = thisDic->equal_range(word);
    auto count = thisDic->count(word);
    if (count == 0) { return; }
    std::string filename = ":/alphabet/sources/part" + to_string(index + 1);
    QFile file(filename.c_str());
    file.open(QIODevice::ReadOnly);
    auto qfile = file.readAll();
    std::istringstream issfile(qfile.toStdString());
    std::string line, partOfSpeech;
    int currentPos = 0;
    for (auto itr = range.first; itr != range.second; ++itr) {
        auto key = itr->first;
        strvec_t thisEntry;
        auto pos = itr->second;
        while (std::getline(issfile, line)) {
            if (currentPos < pos) { ++currentPos; continue; }
            else {
                std::istringstream iss(line);
                std::string temp1;
                iss >> temp1;
                std::string temp2;
                iss >> temp2;
                if (currentPos == pos) { partOfSpeech = temp2; }
                if (temp1 != key) {
                    ++currentPos;
                    break;
                }
                else if (temp2 != partOfSpeech) {
                    ++currentPos;
                    partOfSpeech = temp2;
                    thisResult.insert(std::make_pair(key, thisEntry));
                    thisEntry.clear();
                    thisEntry.push_back(line);
                    continue;
                }
                thisEntry.push_back(line);
                ++currentPos;
            }
        }
        thisResult.insert(std::make_pair(key, thisEntry));
    }
    file.close();
}

void Dictionary::printAllSelected(int index) {
    auto itr = resultsToPrint.begin();
    for (auto i = 0; i < index; ++i) {
        itr = std::next(itr);
    }
    auto thisResult = *itr;
    std::string toprint;
    for (auto i : thisResult.second) {
       std::string temp = addStyleToResults(i);
       toprint += temp;
    }
    toprint = "<span style=\"font-family: Perpetua; font-size: 15pt;\"><p align=\"center\"><table border=\"0.5\" cellpadding=\"5\">" + toprint + "</table></p></span>";
    auto textarea6 = root->findChild<QObject*>("textArea6");
    QMetaObject::invokeMethod(textarea6, "clear");
    QMetaObject::invokeMethod(textarea6, "append", Q_ARG(QString, toprint.c_str()));
}

void Dictionary::onlineText(QString str) {
    flags = {0, 1, 0, 0, 0, 0, 0};
    onlineTextEntries.clear();
    std::string word = str.toStdString();
    inputted = word;
    std::string newWord = wordToWrite(word);
    std::string url = textUrl1 + newWord + textUrl2;
    downloadPageTextual(url.c_str());
}

void Dictionary::onlineTextSelected(int index) {
    auto itr = onlineTextEntries.begin();
    for (auto i = 0; i < index; ++i) {
        itr = std::next(itr);
    }
    auto url = itr->second;
    downloadPageTextual(url);
}

void Dictionary::onlineDefinition(QString str) {
    flags = {1, 0, 0, 0, 0, 0, 0};
    onlineEntries.clear();
    std::string word = str.toStdString();
    std::string newWord = wordToWrite(word);
    std::string url = writeUrl1 + newWord + writeUrl2;
    downloadPageDefinition(url.c_str());
}

void Dictionary::onlineDefSelected(int key) {
    auto itr= onlineEntries.begin();
    for (auto i = 0; i < key; ++i) {
        itr = std::next(itr);
    }
    auto url = itr->second;
    downloadPageDefinition(url);
}


void Dictionary::downloadPageDefinition(std::string url) {
    QUrl pageUrl(url.c_str());
    pageControl = new PageDownloader(pageUrl, this);
    connect(pageControl, SIGNAL(downloaded()), this, SLOT(loadPageDefinition()));
}

void Dictionary::downloadPageTextual(std::string url) {
    QUrl pageUrl(url.c_str());
    pageControl = new PageDownloader(pageUrl, this);
    connect(pageControl, SIGNAL(downloaded()), this, SLOT(loadPageTextual()));
}

void Dictionary::loadPageDefinition() {
    QByteArray qPage = (pageControl->downloadedData());
    QString str = QString::fromLatin1(qPage);
    webpage = str.toStdString();
    parsePageDefinition();
    webpage = "<span style=\"font-family: Perpetua; font-size: 16pt;\">" + webpage + "</span>";
    auto textarea = root->findChild<QObject*>("textArea");
    QMetaObject::invokeMethod(textarea, "clear");
    QMetaObject::invokeMethod(textarea, "append", Q_ARG(QString, webpage.c_str()));
    webpage.clear();
}

void Dictionary::loadPageTextual() {
    QByteArray qPage = (pageControl->downloadedData());
    QString str = QString::fromLatin1(qPage);
    webpage = str.toStdString();
    parsePageTextual();
    webpage = "<span style=\"font-family: Perpetua; font-size: 16pt;\">" + webpage + "</span>";
    auto textarea2 = root->findChild<QObject*>("textArea2");
    QMetaObject::invokeMethod(textarea2, "clear");
    QMetaObject::invokeMethod(textarea2, "append", Q_ARG(QString, webpage.c_str()));
    webpage.clear();
}

void Dictionary::parsePageDefinition() {
    if (webpage.find("produced no results.") != std::string::npos) {
        auto pos = webpage.find("<h3>While searching in Icelandic Online Dictionary and Readings</h3>");
        if (pos != std::string::npos) webpage = webpage.substr(pos, webpage.length() - pos);
        pos = webpage.find("<div class=\"mainBackground\">");
        if (pos != std::string::npos) webpage = webpage.substr(0, pos);
    }
    else if (webpage.find("<div class=\"results\">") != std::string::npos) {
        auto pos = webpage.find("<div class=\"results\">");
        if (pos != std::string::npos) webpage = webpage.substr(pos, webpage.length() - pos);
        pos = webpage.find("</div> <!-- results -->");
        if (pos != std::string::npos) webpage = webpage.substr(0, pos);
        std::vector<std::string> toBeDeleted = {
            "<div class=\"results\">", "<div class=\"nestlevel\">", "<span class=\"lemma\">",
            "<small><sup>", "</sup></small>", "</a></span>", "<span class=\"pos\">", "</span>",
            "</div>", "<!-- results -->", "<a href=\""
        };
        auto results = webpage;
        for (auto && i : toBeDeleted) {
            while (results.find(i) != std::string::npos) {
                auto pos = results.find(i);
                if (pos != std::string::npos) { results.erase(pos, i.length()); }
            }
        }
        std::istringstream iss(results);
        std::vector<std::string> entries;
        std::string line;
        while (std::getline(iss, line)) {
            if (line.length() > 0) {
                pos = line.find("\">");
                if (pos != std::string::npos) {
                    line.replace(pos, 2, " ");
                }
                entries.push_back(line);
            }
        }
        for (auto i : entries) {
            std::istringstream iss(i);
            std::string link, key;
            iss >> link;
            link = "http://digicoll.library.wisc.edu" + link;
//            std::string temp;
            iss >> key;
            if (key.back() == ',') {
                std::string temp;
                iss >> temp;
                key += ' ' + temp;
            }
            onlineEntries.insert(std::make_pair(key, link));
        }
        for (auto && i : onlineEntries) {
            QVariant str = i.first.c_str();
            QMetaObject::invokeMethod(item1, "addItemToList", Q_ARG(QVariant, str));
        }
    }
    else {
        auto pos = webpage.find("<div class=\"entry\">");
        if (pos != std::string::npos) { webpage = webpage.substr(pos, webpage.length() - pos); }
        pos = webpage.find("</div><!-- entry -->");
        if (pos != std::string::npos) { webpage = webpage.substr(0, pos); }
        pos = webpage.find("<span class=\"lemma\">");
        if (pos != std::string::npos) {
            std::string tag = "<span class=\"lemma\">";
            webpage.replace(pos, tag.length(), "<span style=\" font-weight:600; font-size:24pt;\" class=\"lemma\">");
        }
        while (webpage.find("<span class=\"orth\">") != std::string::npos) {
            std::string tag = "<span class=\"orth\">";
            auto pos = webpage.find(tag);
            if (pos != std::string::npos) {
                webpage.replace(pos, tag.length(), "<span style=\" font-weight:600;\" class=\"orth\">");
            }
        }
        while (webpage.find("<span class=\"trans\">") != std::string::npos) {
            std::string tag = "<span class=\"trans\">";
            auto pos = webpage.find(tag);
            if (pos != std::string::npos) {
                webpage.replace(pos, tag.length(), "<span style=\" font-style:italic;\" class=\"trans\">");
            }
        }
    }
}

void Dictionary::parsePageTextual() {
    if (webpage.find("produced no results.") != std::string::npos) {
        auto pos = webpage.find("<h3>While searching in Icelandic Online Dictionary and Readings</h3>");
        if (pos != std::string::npos) webpage = webpage.substr(pos, webpage.length() - pos);
        pos = webpage.find("<div class=\"mainBackground\">");
        if (pos != std::string::npos) webpage = webpage.substr(0, pos);
    }
    else if (webpage.find("<div class=\"results\">") != std::string::npos) {
        auto pos = webpage.find("<div class=\"results\">");
        if (pos != std::string::npos) webpage = webpage.substr(pos, webpage.length() - pos);
        pos = webpage.find("</div> <!-- results -->");
        if (pos != std::string::npos) webpage = webpage.substr(0, pos);
        std::vector<std::string> toBeDeleted = {
            "<div class=\"results\">", "<div class=\"nestlevel\">", "<span class=\"lemma\">",
            "<small><sup>", "</sup></small>", "</a></span>", "<span class=\"pos\">", "</span>",
            "</div>", "<!-- results -->", "<a href=\""
        };
        auto results = webpage;
        for (auto && i : toBeDeleted) {
            while (results.find(i) != std::string::npos) {
                auto pos = results.find(i);
                if (pos != std::string::npos) { results.erase(pos, i.length()); }
            }
        }
        std::istringstream iss(results);
        std::vector<std::string> entries;
        std::string line;
        while (std::getline(iss, line)) {
            if (line.length() > 0) {
                pos = line.find("\">");
                if (pos != std::string::npos) {
                    line.replace(pos, 2, " ");
                }
                entries.push_back(line);
            }
        }
        for (auto i : entries) {
            std::istringstream iss(i);
            std::string link, key;
            iss >> link;
            link = "http://digicoll.library.wisc.edu" + link;
//            std::string temp;
            iss >> key;
            if (key.back() == ',') {
                std::string temp;
                iss >> temp;
                key += ' ' + temp;
            }
            onlineTextEntries.insert(std::make_pair(key, link));
        }
        auto item2 = root->findChild<QObject*>("item2");
        for (auto && i : onlineTextEntries) {
            QVariant str = i.first.c_str();
            QMetaObject::invokeMethod(item2, "addItemToList", Q_ARG(QVariant, str));
        }
    }
    else {
        auto pos = webpage.find("<div class=\"entry\">");
        if (pos != std::string::npos) { webpage = webpage.substr(pos, webpage.length() - pos); }
        pos = webpage.find("</div><!-- entry -->");
        if (pos != std::string::npos) { webpage = webpage.substr(0, pos); }
        pos = webpage.find("<span class=\"lemma\">");
        if (pos != std::string::npos) {
            std::string tag = "<span class=\"lemma\">";
            webpage.replace(pos, tag.length(), "<span style=\" font-weight:600; font-size:24pt;\" class=\"lemma\">");
        }
        while (webpage.find("<span class=\"orth\">") != std::string::npos) {
            std::string tag = "<span class=\"orth\">";
            auto pos = webpage.find(tag);
            if (pos != std::string::npos) {
                webpage.replace(pos, tag.length(), "<span style=\" font-weight:600;\" class=\"orth\">");
            }
        }
        while (webpage.find("<span class=\"trans\">") != std::string::npos) {
            std::string tag = "<span class=\"trans\">";
            auto pos = webpage.find(tag);
            if (pos != std::string::npos) {
                webpage.replace(pos, tag.length(), "<span style=\" font-style:italic;\" class=\"trans\">");
            }
        }
        auto pos2 = webpage.find(inputted);
        if (pos2 != std::string::npos) {
            webpage.replace(pos2, inputted.length(), "<span style=\" font-weight:600; color:#ff0000;\">" + inputted + "</span>");
        }
    }
}
