#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include <mutex>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

struct Entry 
{
    size_t doc_id, count;

    // Тесты:
    bool operator ==(const Entry& other) const 
    {
        return (doc_id == other.doc_id && count == other.count);
    }
};

class InvertedIndex 
{
    public:

    InvertedIndex() = default;

    /**
    * Обновите или заполните базу документов, в которых будет выполняться поиск
    * @param [in] texts_input - содержимое документов
    */
    void updateDocumentBase(const std::vector<std::string>& input_docs);
    
    /**
    * Метод определяет количествл вхождений слова word в загруженный базе документов
    * @param [in] word - слово, для которого должна быть определена частота ввода
    * @return подготовленный список с частотой слов
    */
    std::vector<Entry> getWordCount(const std::string& word);

    /**
     * Метод получения количества слов в определенном документе
     * @param [in] word - слово, которое нужно учитывать в документе
     * @param [in] doc_id - идентификатор документа для поиска
     * @return возвращает количество слов в определенном документ
     */
    size_t getWordCountInDoc(const std::string& word, const size_t doc_id) const; // ADDITIONAL METHOD

    private:

    /**
     * Метод индексации отдельного файла
     * @param [in] fileContent - std::string с содержимым файла
     * @param [in] docId - идентификатор файла
     */
    void indexTheFile(const std::string& fileContent, size_t docId);

    std::map<int, std::string> document_list; // map of documents (unique id and file name) для поиска в
    static std::mutex mutexIndexMap; // доступ к index map
    std::map<std::string, std::vector<Entry>> frequencyDictionary; //  частотный словарь
    bool indexingIsOngoing;
};