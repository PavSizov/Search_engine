#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "nlohmann/json.hpp"


class ConverterJSON
{
    public:

    /**
    * Получить объект экземпляра класса ConverterJSON
    * @return возвращает экземпляр of the singleton
    */
    static ConverterJSON* getInstance();

    /**
     *  Метод получения содержимого файлов
     * @return возвращает содержимое файлов, перечисленных в config.json
     */
    std::vector<std::string> getTextDocuments();

    /**
     * Получить максимальное количество ответов на запрос
     * @return
     */
    int getResponsesLimit() const;

    /**
     * Метод получения запросов из requests.json
     * @return возвращает список запросов из файла requests.json
     */
    std::vector<std::string> getRequests();

    /**
     * Положить в файл answers.json результаты поисковых запросов

     */
    void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);

    /**
     * Прочитать файл config.json
     */
    void readConfigFile(std::string path = "config.json");

    /**
     * Прочитать файл requests.json
     */
    void readRequestFile(std::string path = "requests.json");

    /**
     * Метод получения максимального количества ответов, которые могут быть возвращены поисковым сервером
     * @return возвращает максимальное количество ответов
     */
    int getMaxResponses() const;

    private:
    ConverterJSON() = default; // private constructor for singleton realization
    static ConverterJSON* instance;
    const std::string ANSWERS_FILE_PATH = "answers.json";
    std::string applicationName;
    std::string applicationVersion;
    int maxResponses  {5};
    std::vector<std::string> resourcesPaths;
    std::vector<std::string> textDocuments;
    std::vector<std::string> requests;

};
