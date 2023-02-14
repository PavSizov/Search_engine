#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>

#include "InvertedIndex.h"

struct RelativeIndex
{
    size_t doc_id;
    float rank;
    size_t absoluteIndex = 0; // Added for convenience.

    bool operator ==(const RelativeIndex& other) const 
    {
        return (doc_id == other.doc_id && rank == other.rank);
    }
    bool operator > (const RelativeIndex& other) const
    {
        return (rank > other.rank || (rank == other.rank && doc_id < other.doc_id));
    }
};

class SearchServer 
{
    public:
    
    /**
    * @param idx - ссылка на экземпляр InvertedIndex
    * чтобы SearchServer мог узнать частоту слов в запросах
    */
    SearchServer(InvertedIndex& idx) : _index(idx){ };

    /**
    * Метод обработки поисковых запросов
    * @param [in] queries_input - поиск запросов из requests.json
    * @return возвращает отсортированный список соответствующих ответов
    */
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);

    /**
    * Метод установки максимального количеств ответов с поискового сервера
    * @param [in] newMaxResponses - новое значение для максимального количества ответов
    */
    void setMaxResponses(const int& newMaxResponses);

    private:

    InvertedIndex _index;
    int maxResponses {5};

    /**
     * Метод получение уникальных слов из строки запроса
     * @param [in] request - отдельная строка из request.jso
     * @return возвращает набор уникальных слов
     */
    std::set<std::string> getUniqueWords(const std::string& request);

    /**
     * Метод позволяет получить vector записей для набора слов
     * @param [in] words - набор слов
     * @return возвращает vector записей
     */
    std::vector<std::pair<std::string, size_t>> getWordsEntries(const std::set<std::string>& words);

    /**
     * Метод сортировки vector записей в направлении возрастания количества записей
     * @param [in/out] wordsEntries -  vector записей
     */
    void sortWordsAscendingToEntries(std::vector<std::pair<std::string, size_t>>& wordsEntries);

    /**
     * Метод получения списка документов, в которых можно найти все слова из запроса
     * @param [in] words - vector пар "слово(word) - количество записей (entry count)"
     * @return возвращает vector идентификаторов документов, в которых можно найти все слова
     */
    std::vector<size_t> getAllDocumentsWithWords(const std::vector<std::pair<std::string, size_t>>& words);

    /**
     * Метод вычисления абсолютной релевантности документа для определенных слов
     * @param [in] docId - идентификатор документа
     * @param [in] uniqueWords - запрос слов в vector
     * @return возвращает абсолютную релевантность
     */
    size_t getAbsoluteRelevanceForDocument (size_t docId, std::set<std::string>& uniqueWords);
};